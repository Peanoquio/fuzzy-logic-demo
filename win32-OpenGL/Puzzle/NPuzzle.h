#include <vector>
#include <map>
#include <unordered_map>
#include <queue>


namespace
{
	unsigned int NODE_COST = 1;
}


enum PUZZLE_KIND{ NORMAL, CIRCULAR };
enum SEARCH_METHOD{ DFS=0, ASTAR=1 };

enum TILE_MOVEMENT
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum SOLUTION_TYPE
{
	SEARCH_NOT_STARTED,
	SOLUTION_WITH_DATA,
	SOLUTION_IS_INITIAL_STATE,
	NO_SOLUTION
};

struct MyNode//no need to be updated
{
	MyNode() {
		m_data = 0; 
		m_parent = 0; 
		m_currentActualCost = 0;
		m_totalCost = 0;
	}
	unsigned int * m_data;//The array of integers represents the current order of the tiles in the puzzle. The last int (not for m_initialState) is to save the index in m_data of the hole in the puzzle.
	MyNode * m_parent;//The parent is needed to always have track of the current optimal solution and to be able to extract the result
	unsigned int m_currentActualCost;//Actual cost to reach this node state from the start (needed to save this variable separately because children nodes need this information)
	unsigned int m_totalCost;// = actual cost to reach this node state from the start + estimated heuristic cost from current node state to the goal state
};


//This is the global less than operator which has been overloaded to compare MyNode objects.
//Take note that the resulting boolean has been negated in such a way that less than becomes greater than.
//bool operator< ( const MyNode & lhsNode, const MyNode & rhsNode );

struct CompareNode
{
	bool operator() ( const MyNode * lhsNode, const MyNode * rhsNode );
};

struct CompareNodeByKey
{
	bool operator() ( const unsigned long long lhsNodeKey, const unsigned long long rhsNodeKey );
};


struct MyStatistics//no need to be updated
{
	MyStatistics() {m_nodesGenerated = 0;}
	unsigned int m_nodesGenerated;//How many times we created successful new nodes (that are added to the frontier) while doing one specific search
};

class NPuzzle
{
public://do not update the existing public functions

	//added by Oliver Chong - February 3, 2012
	typedef std::unordered_map< unsigned long long, MyNode * >					ExploredSetMap;
	typedef std::unordered_map< TILE_MOVEMENT, MyNode * >						ResultingNodeMap;
	typedef std::priority_queue< MyNode *, std::vector<MyNode*>, CompareNode >	FrontierPriorityQueue;
	typedef std::multimap< unsigned long long, MyNode *, CompareNodeByKey >		FrontierMultiMap;


	unsigned int									m_sideSize;
	unsigned int									m_searchMethod;
	
	MyNode *										m_tempSolutionNodePtr;	
	unsigned long									m_solutionTime;
	unsigned int									m_noOfSolutionSteps;
	SOLUTION_TYPE									m_solutionType;
	std::vector< unsigned int * >					m_solution;

	std::vector< MyNode * >																m_frontier;
	//FrontierPriorityQueue																m_frontierSorted;
	ExploredSetMap																		m_exploredSet;	
	ResultingNodeMap																	m_resultingNodeMap;
	//end - added by Oliver Chong - February 3, 2012

	//This is the only constructor to be used. It takes the sideSize as first argument and the kind of the puzzle to be used (notice that we are only using one kind of puzzles which is the normal one).
	NPuzzle(unsigned sideSize, PUZZLE_KIND puzzleKind = NORMAL);
	~NPuzzle();

	//The following setter and getter state buffer functions are for user use. The buffers should be of size = m_totalTilesNumber
	bool SetState(const unsigned int * state, unsigned int bufferSize);//This function will set state as the initial current internal state
	const unsigned int * GetState();//Returns the current initial internal state (before the run of any search algorithm)

	bool SearchForSolution(unsigned int searchMethod);//This function will call the specified algorithm to make a search for a possible solution (0 = DFS, 1 = ASTAR).

	bool CheckLegalTilesPositions(const unsigned int * state, PUZZLE_KIND puzzleKind = NORMAL);//This function checks if the arrangement provided in the array is legal for the selected goal group of states

	unsigned int GetTilesNumber();//Returns the number of numbered cells
	unsigned int GetSideSize();//Returns the number of cells (or columns)
	std::vector<unsigned int *> & GetSolution();//This function returns a solution, if any, after applying a search algorithm. The return buffer is a vector of integer arrays, where every integer array represents a specific state of the puzzle with N different tiles positions.
	MyStatistics * GetStatistics();	

	void CleanSolution( void );
	void CleanFrontier( void );
	void CleanExploredSet( void );
	void CleanResultingNodes( void );
	void CleanNode( MyNode * node ) const;

private:
	unsigned int m_totalTilesNumber;// This variable represents the number of tiles including the empty space hole tile
	unsigned int m_stateSize;// = m_totalTilesNumber + 1 (1 is for the last integer that holds the hole position). It represents the current state in a search algorithm.

	MyNode * m_initialState;// = m_totalTilesNumber. This integers buffer saves always what was the latest user input (using SetState function).
	MyNode * m_currentState;// = m_stateSize = m_totalTilesNumber + 1 (1 is for the last integer that holds the hole position). This state will always change while a search is happening. It is the state that is being extracted from the frontier to be tested and expanded if possible.
	MyNode * m_targetState;// = m_stateSize = m_totalTilesNumber + 1 (1 is for the last integer that holds the hole position). This integers buffer holds the target state that will always be compared will a search is happening.   

	//added by Oliver Chong - February 3, 2012
	bool ExpandCurrentState( void );
	bool ExpandCurrentStateHelper( const TILE_MOVEMENT tileMovement, unsigned int * state, const unsigned int holePosition, const unsigned int tilePosition );
	const unsigned int Heuristic( const MyNode * node ) const;
	void DeriveRowCol( const MyNode * node, const unsigned int tileNumber, unsigned int & rowVal, unsigned int & colVal ) const;
	MyNode * GenerateStateNode( unsigned int * state, MyNode * parentNode );
	void CopyStateValues( const unsigned int * sourceState, unsigned int * destinationState, unsigned int bufferSize ) const;
	bool CompareStateValues( const unsigned int * lhsState, const unsigned int * rhsState, unsigned int bufferSize ) const;
	void SwapHoleAndTile( unsigned int * state, const unsigned int holePosition, const unsigned int tilePosition ) const;
	unsigned long long GenerateStateKey( const unsigned int * state ) const;
	bool IsStateExistingInExploredSet( const unsigned long long stateKey ) const;
	bool IsStateExistingInFrontier( const unsigned int * state ) const;
	bool IsStateExistingInFrontier( const unsigned int * state, unsigned & frontierIndex, unsigned & frontierCost ) const;
	void GenerateSolution( MyNode * resultingNode );

	bool DepthFirstSearch( void );
	bool AstarSearch( void );
};