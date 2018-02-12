/******************************************************************************/
/*!
\file Graph.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 01/03/2012
\brief
This is the graph class that will be used to generate the graph to be used by the algorithm to find the shortest path

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "Graph.h"
#include "MathUtility.h"

//Edge class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The constructor for the Edge class

\param

\return
*/
/******************************************************************************/
Edge::Edge()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The destructor for the Edge class

\param

\return
*/
/******************************************************************************/
Edge::~Edge()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The copy constructor for the Edge class

\param ed
the Edge class to be assigned

\return
*/
/******************************************************************************/
Edge::Edge(const Edge & ed)
{
	from = ed.from;
	to = ed.to;		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The assignment operator overload for the Edge class

\param ed
the Edge class to be assigned

\return Edge
the Edge
*/
/******************************************************************************/
Edge & Edge::operator=(const Edge & ed)
{
	if(this != &ed)
	{
		from = ed.from;
		to = ed.to;
	}
	return *this;
}


//State class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The constructor for the State class

\param

\return
*/
/******************************************************************************/
State::State()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The destructor for the State class

\param

\return
*/
/******************************************************************************/
State::~State()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The copy constructor for the State class

\param st
the State class to be assigned

\return
*/
/******************************************************************************/
State::State(const State & st)
{
	worldPositionX = st.worldPositionX;
	worldPositionY = st.worldPositionY;
	
	edges = st.edges;		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The assignment operator overload for the State class

\param st
the State class to be assigned

\return State
the State
*/
/******************************************************************************/
State & State::operator=(const State & st)
{
	if(this != &st)
	{
		worldPositionX = st.worldPositionX;
		worldPositionY = st.worldPositionY;
	
		edges = st.edges;		
	}
	return *this;
}


//Path class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The constructor for the Path class

\param

\return
*/
/******************************************************************************/
Path::Path()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The destructor for the Path class

\param

\return
*/
/******************************************************************************/
Path::~Path()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The assignment operator overload for the Path class

\param pa1
the Path class to be assigned

\return Path
the Path
*/
/******************************************************************************/
Path & Path::operator=(Path & pa1)
{
	if(this != &pa1)
	{
	}
	return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Initializes the distance and path matrices based on the number of states in the path

\param

\return
*/
/******************************************************************************/
void Path::InitMatrix( void )
{
	unsigned noOfStates = this->states.size();

	//initialize the distance matrix based on the number of states in the path
	
	std::vector< float > floatVec;
	floatVec.reserve( noOfStates );	
	std::vector< int > intVec;
	intVec.reserve( noOfStates );	

	for ( unsigned int y = 0; y < noOfStates; ++y )
	{
		floatVec.push_back( MAX_DISTANCE );		
		intVec.push_back( NO_LINK );
	}//end for loop

	this->m_distanceMtx.reserve( noOfStates );
	this->m_pathMtx.reserve( noOfStates );

	for ( unsigned int x = 0; x < noOfStates; ++x )
	{
		this->m_distanceMtx.push_back( floatVec );
		this->m_pathMtx.push_back( intVec );
	}//end for loop

	//set to identity
	for ( unsigned int x = 0; x < noOfStates; ++x )
	{
		for ( unsigned int y = 0; y < noOfStates; ++y )
		{
			if ( x == y )
			{
				this->m_distanceMtx.at( x ).at( y ) = 0;
				this->m_pathMtx.at( x ).at( y ) = DIRECT_LINK;
				break;
			}
		}//end for loop
	}//end for loop

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Populates the distance and path matrices based on the edges of each state in the path

\param

\return
*/
/******************************************************************************/
void Path::PopulateMatrix( void )
{
	unsigned noOfStates = this->states.size();

	//populate the distance matrix based on the edges of each state in the path

	//loop through the states
	for ( unsigned stateIndex = 0; stateIndex < noOfStates; ++stateIndex )
	{
		//get the current state
		const State & currState = this->states.at( stateIndex );
		
		//loop through the edges
		for ( unsigned edgeIndex = 0; edgeIndex < currState.edges.size(); ++edgeIndex )
		{
			//get the current edge
			const Edge & currEdge = currState.edges.at( edgeIndex );
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//traverse the row
			for ( unsigned x = 0; x < this->m_distanceMtx.size(); ++x )
			{
				//if row found ( from )
				if ( currEdge.from == static_cast<int>( x ) )
				{
					std::vector< float > & colVecDM = this->m_distanceMtx.at( x );
					std::vector< int> & colVecPath = this->m_pathMtx.at( x );

					//traverse the column
					for ( unsigned y = 0; colVecDM.size(); ++y )
					{
						//if column found ( to )
						if ( currEdge.to == static_cast<int>( y ) )
						{
							//get the x and y positions of the from and to states 
							const State & fromState = this->states.at( currEdge.from );
							const State & toState = this->states.at( currEdge.to );
							//compute the distance between from and to states
							float xDiff = toState.worldPositionX - fromState.worldPositionX;
							float yDiff = toState.worldPositionY - fromState.worldPositionY;
							float distanceSquared = ( xDiff * xDiff ) + ( yDiff * yDiff );
							//store the distance ( cost ) between the states
							colVecDM.at( y ) = distanceSquared;

							//to identify a direct path between states
							colVecPath.at( y ) = DIRECT_LINK;

							break;
						}
					}//end for loop

					break;				
				}
			}//end for loop

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}
	
	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Generate the distance and path matrices to be used by Floyd's algorithm

\param

\return
*/
/******************************************************************************/
void Path::GenerateMatrix( void )
{		
	this->InitMatrix();

	this->PopulateMatrix();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Floyd (or Floyd-Warshall) algorithm is a dynamic algorithm that finds the shortest paths between all pairs in a graph.

\param

\return
*/
/******************************************************************************/
void Path::FloydAlgorithm( void )
{
	unsigned noOfStates = this->states.size();

	//loop through the intermediate nodes that could possible provide the shortest path
	for ( unsigned interIndex = 0; interIndex < noOfStates; ++interIndex )
	{
		for ( unsigned fromIndex = 0; fromIndex < noOfStates; ++fromIndex )
		{
			for ( unsigned toIndex = 0; toIndex < noOfStates; ++toIndex )
			{
				float distFromTo = this->m_distanceMtx.at( fromIndex).at( toIndex );
				float distFromInter = this->m_distanceMtx.at( fromIndex ).at( interIndex );
				float distInterTo = this->m_distanceMtx.at( interIndex ).at( toIndex );

				//validate if the intermediate state node will give a shorter path to the destination
				if ( distFromTo > distFromInter + distInterTo )
				{
					//update the distance cost based on the new shorter path
					distFromTo = distFromInter + distInterTo;
					this->m_distanceMtx.at( fromIndex).at( toIndex ) = distFromTo;

					//update the path
					this->m_pathMtx.at( fromIndex ).at( toIndex ) = interIndex;
				}
			
			}//end for loop

		}//end for loop

	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Finds the shortest path based on the start and end indices.
This uses the path matrix generated by Floyd's algorithm

\param startIndex
the start index of the path
\param endIndex
the end index of the path

\return
*/
/******************************************************************************/
void Path::ComputeShortestPath( const int startIndex, const int endIndex )
{
	//get the path node index based on the start and end index
	int pathNodeIndex = this->m_pathMtx.at( startIndex ).at( endIndex );

	//if there is no path
	if ( pathNodeIndex == NO_LINK )
	{
		//do nothing
	}
	//if there is a direct path from start to end
	else if ( pathNodeIndex == DIRECT_LINK ) 
	{
		//add the starting state
		this->shortestPathIndices.push_back( startIndex );
		//add the ending state
		this->shortestPathIndices.push_back( endIndex );	
	}
	//if there is an intermediate node
	else
	{
		//find the intermediate nodes between the start and the middle state
		this->FindIntermediateNodes( startIndex, pathNodeIndex, true );

		//find the intermediate nodes between the middle and end state
		this->FindIntermediateNodes( pathNodeIndex, endIndex, false );

		//add the starting state
		//this->shortestPathIndices.push_back( startIndex );

		//add the intermediate nodes
		for ( unsigned index = 0; index < this->intermediateNodes.size(); ++index )
		{
			this->shortestPathIndices.push_back( this->intermediateNodes.at( index ) );
		}//end for loop

		//clear the intermediate nodes
		this->intermediateNodes.clear();

		//add the ending state
		//this->shortestPathIndices.push_back( endIndex );	
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Finds the intermediate nodes between a specified start and end state

\param startIndex
the start index of the path
\param endIndex
the end index of the path
\param leftToRight
if true, traverse nodes from left to right.
if false, traverse from right to left 

\return
*/
/******************************************************************************/
void Path::FindIntermediateNodes( const int startIndex, const int endIndex, bool leftToRight )
{
	//get the path node index based on the start and end index
	int pathNodeIndex = this->m_pathMtx.at( startIndex ).at( endIndex );

	//if there is no path
	if ( pathNodeIndex == NO_LINK )
	{
		//do nothing
	}
	//if there is a direct path from start to end
	else if ( pathNodeIndex == DIRECT_LINK ) 
	{
		int firstStateIndex = 0;
		int secondStateIndex = 0;

		if ( leftToRight == true )
		{
			firstStateIndex = startIndex;
			secondStateIndex = endIndex;
		}
		else
		{
			firstStateIndex = endIndex;
			secondStateIndex = startIndex;
		}

		this->AddNodeIndex( firstStateIndex );
		this->AddNodeIndex( secondStateIndex );
	}
	//if there is an intermediate node
	else
	{
		//invoke function recursively to check for possible succeeding intermediate nodes
		this->FindIntermediateNodes( startIndex, pathNodeIndex, true );
		this->FindIntermediateNodes( pathNodeIndex, endIndex, false );		
	}		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Adds the state node index to the list

\param stateIndex
the state node index of the path

\return
*/
/******************************************************************************/
void Path::AddNodeIndex( const int stateIndex )
{
	bool isExisting = false;
	//validate if the node to be is already existing
	for ( unsigned index = 0; index < this->intermediateNodes.size(); ++index )
	{
		if ( stateIndex == this->intermediateNodes.at( index ) )
		{
			isExisting = true;
			break;
		}
	}//end for loop

	if ( isExisting == false )
	{
		this->intermediateNodes.push_back( stateIndex );
	}
}