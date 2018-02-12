//This code is on the client (visual engine) side
//It will help you to get a good idea of how we're using the NPuzzle class on the client side - you can implement similar code if you want

//this structure is used to save and add data of different solutions
struct PathInfo
{
	PathInfo() {size = 0; numberOfNodes = 0; numberOfElements = 0;}
	unsigned int size;
	unsigned int numberOfNodes;//total of all elements
	unsigned int numberOfElements;//of the same size
};

void StressTest()
{
	unsigned int tn = npuzzle->GetTilesNumber();
	unsigned int * array = new unsigned int [tn];

	unsigned int numberOfDifferentSolutions = 1000;

	bool res;

	paths.clear();//paths is a vector
	unsigned long startTime, endTime;
	startTime = timeGetTime();
	for(unsigned int loop = 0; loop < numberOfDifferentSolutions; ++loop)
	{
		while(1)//until having a legal set
		{
			GenerateNRandomNumbers(array,tn);
			if(npuzzle->CheckLegalTilesPositions(array))
				break;
		}
	
		SetTiles(array);
		ExtractStateFromTiles();
		npuzzle->SetState(visualState, npuzzle->GetTilesNumber());
		res = npuzzle->SearchForSolution(solverMethod);//0 = DFS and 1 = ASTAR	

		if(res)
		{
			PathInfo pi;
			pi.size = npuzzle->GetSolution().size() - 1;
			pi.numberOfNodes = npuzzle->GetStatistics()->m_nodesGenerated;
			pi.numberOfElements = 1;
	
			unsigned int sz = paths.size();
			bool newone = true;
			for(unsigned int p = 0; p < sz; ++p)
			{
				if(paths[p].size == pi.size)
				{
					paths[p].numberOfElements++;
					paths[p].numberOfNodes += pi.numberOfNodes;
					newone = false;
					break;
				}
			}
			if(newone)
			{
				paths.push_back(pi);
			}
		}
	}

	endTime = timeGetTime();
	unsigned int diffInMilliSeconds = endTime - startTime;


	//sort the paths by sizes
	std::sort(paths.begin(), paths.end(), LevelClass::PathInfoSorting);


	//display same solution sizes (nodes generated) average
	
	unsigned int sz = paths.size();
	for(unsigned int ss = 0; ss < sz; ++ss)
	{
		Display("Size: " + paths[ss].size + " - Problems: " + paths[ss].numberOfElements + " - Avg nodes: " + paths[ss].numberOfNodes / paths[ss].numberOfElements + "\n");
	}
	
	Display("Time taken to solve " +  numberOfDifferentSolutions + " different solutions = " + diffInMilliSeconds + " milliSeconds");


	delete [] array;
}