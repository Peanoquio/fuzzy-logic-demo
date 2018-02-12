#include "NPuzzle.h"
#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This is the global less than operator which has been overloaded to compare MyNode objects.
Take note that the resulting boolean has been negated in such a way that less than becomes greater than.

\param lhsNode
the left-hand side node
\param rhsNode
the right hand side node
\return bool
if true, the left-hand side node is greater than the right-hand side node, otherwise false
*/
/******************************************************************************/
/*
bool operator< ( const MyNode & lhsNode, const MyNode & rhsNode )
{
	return !( lhsNode.m_totalCost < rhsNode.m_totalCost );
}
*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This is the operator which has been overloaded to compare MyNode objects.
Take note that the resulting boolean has been negated in such a way that less than becomes greater than.

\param lhsNode
the left-hand side node
\param rhsNode
the right hand side node
\return bool
if true, the left-hand side node is greater than the right-hand side node, otherwise false
*/
/******************************************************************************/
bool CompareNode::operator() ( const MyNode * lhsNode, const MyNode * rhsNode )
{
	if ( lhsNode->m_totalCost == rhsNode->m_totalCost )
	{
		return false;
	}
	else
	{
		return !( lhsNode->m_totalCost < rhsNode->m_totalCost );
	}
	//return lhsNode->m_totalCost < rhsNode->m_totalCost;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This is the operator which has been overloaded to compare MyNode objects.
Take note that the resulting boolean has been negated in such a way that less than becomes greater than.

\param lhsNodeKey
the left-hand side node key
\param rhsNodeKey
the right hand side node key
\return bool
if true, the left-hand side node is greater than the right-hand side node, otherwise false
*/
/******************************************************************************/
bool CompareNodeByKey::operator() ( const unsigned long long lhsNodeKey, const unsigned long long rhsNodeKey )
{
	if ( lhsNodeKey == rhsNodeKey )
	{
		return false;
	}
	else
	{
		return !( lhsNodeKey < rhsNodeKey );
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This is the only constructor of the NPuzzle class
It takes the sideSize as first argument and the kind of the puzzle to be used 
(notice that we are only using one kind of puzzles which is the normal one).

\param sideSize
the number of tiles per side
\param PUZZLE_KIND
the type of puzzle
\return
*/
/******************************************************************************/
NPuzzle::NPuzzle( unsigned sideSize, PUZZLE_KIND puzzleKind )
	: m_sideSize ( sideSize ),	
	m_totalTilesNumber( sideSize * sideSize ),
	m_stateSize( m_totalTilesNumber + 1 ),
	m_initialState( 0 ),
	m_currentState( 0 ),
	m_targetState( 0 ),
	m_searchMethod( ASTAR ),
	m_tempSolutionNodePtr( 0 ),
	m_solution(),
	m_solutionTime( 0 ),
	m_noOfSolutionSteps( 0 ),
	m_solutionType( SEARCH_NOT_STARTED ),
	m_frontier(),
	m_exploredSet()
{
	//set the goal/target state
	if ( puzzleKind == NORMAL )
	{
		//allocate the node and the data in heap memory
		this->m_targetState = new MyNode;
		this->m_targetState->m_data = new unsigned int[ this->m_totalTilesNumber ];

		//populate the target state
		//a normal 3 x 3 puzzle will have a target state of { 0, 1, 2, 3, 4, 5, 6, 7, 8 }
		for ( unsigned int index = 0; index < this->m_totalTilesNumber; ++index )
		{
			this->m_targetState->m_data[index] = index;		
		}//end for loop
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This is the destructor of the NPuzzle class

\param
\return
*/
/******************************************************************************/
NPuzzle::~NPuzzle()
{
	//clear initial state from the heap memory
	this->CleanNode( this->m_initialState );

	//clear target state from the heap memory
	this->CleanNode( this->m_targetState );

	//release the explored set from the heap memory
	this->CleanExploredSet();

	//release the frontier from the heap memory
	this->CleanFrontier();

	//release the left over resulting nodes from the heap memory
	this->CleanResultingNodes();	

	//release the solution from the heap memory
	this->CleanSolution();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function will set state as the initial current internal state. 

\param state
an array of numbers that represents the order of the tiles in the puzzle
\param bufferSize
The buffer should be of size equals to the total number of tiles (including the empty space tile).
\return bool
true if setting the state is successful, otherwise false
*/
/******************************************************************************/
bool NPuzzle::SetState( const unsigned int * state, unsigned int bufferSize )
{
	bool setStateFlag = true;

	if ( this->m_initialState == 0 )
	{
		//allocate the node and the data in heap memory
		this->m_initialState = new MyNode;
		//The buffer size is equal to m_totalTilesNumber. This integers buffer saves always what was the latest user input (using SetState function).
		//The initial state will not store the position of the hole in the last index of the state data???
		this->m_initialState->m_data = new unsigned int[ bufferSize ];	
	}

	//perform a deep copy of the state values
	this->CopyStateValues( state, this->m_initialState->m_data, bufferSize );

	//the initial state has no parent
	this->m_initialState->m_parent = 0;

	//set the initial cost
	this->m_initialState->m_currentActualCost = NODE_COST;
	this->m_initialState->m_totalCost = NODE_COST;	

	return setStateFlag;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function returns the current initial internal state (before the run of any search algorithm). 
The buffer should be of size equals to the total number of tiles (including the empty space tile).

\param 
\return unsigned int *
the initial state which is an array of numbers that represents the order of the tiles in the puzzle
*/
/******************************************************************************/
const unsigned int * NPuzzle::GetState( void )
{
	return this->m_initialState->m_data;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function will call the specified algorithm to make a search for a possible solution (0 = DFS, 1 = ASTAR).

\param searchMethod
the search algorithm to use
\return bool
true if the solution is found, otherwise false
*/
/******************************************************************************/
bool NPuzzle::SearchForSolution( unsigned int searchMethod )
{
	//store the search method
	this->m_searchMethod = searchMethod;	

	//initialize the solution, frontier and explored set
	bool solutionFound = false;	
	this->m_tempSolutionNodePtr = 0;
	//this->CleanNode( this->m_tempSolutionNodePtr );
	/*
	this->CleanSolution();
	this->CleanFrontier();
	this->CleanExploredSet();
	this->CleanResultingNodes();
	*/

	//the Depth-First Seaerch Algorithm
	if ( searchMethod == DFS )
	{
		solutionFound = this->DepthFirstSearch();
	}
	//the A-Star Algorithm
	else if ( searchMethod == ASTAR )
	{
		solutionFound = this->AstarSearch();
	}

	return solutionFound;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function is the A Star Search Algorithm

\param
\return bool
true if the solution was found, otherwise false
*/
/******************************************************************************/
bool NPuzzle::AstarSearch( void )
{
	bool solutionFound = false;
	bool expandSuccess = false;

	//if initial state node is same as goal/target state node of a normal puzzle
	if ( this->CheckLegalTilesPositions( this->m_initialState->m_data ) == true )
	{
		solutionFound = true;
		return solutionFound;
	}
	else
	{		
		//duplicate initial state
		MyNode * tempInitState = new MyNode;
		unsigned int * tempInitStateData = new unsigned int[ this->m_stateSize ];
		tempInitState->m_parent = this->m_initialState->m_parent;
		tempInitState->m_currentActualCost = this->m_initialState->m_currentActualCost;
		tempInitState->m_totalCost = this->m_initialState->m_totalCost;
		tempInitState->m_data = tempInitStateData;
		this->CopyStateValues( this->m_initialState->m_data, tempInitState->m_data, this->m_stateSize );

		this->m_frontier.push_back( tempInitState );

		//add the initial state node to the frontier priority queue
		//this->m_frontier.push_back( this->m_initialState );
		std::make_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
		std::push_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
		//this->m_frontierSorted.push( this->m_initialState );
		//unsigned long long stateKey = this->GenerateStateKey( this->m_initialState );
		//this->m_frontierSorted.insert( std::make_pair( stateKey, this->m_initialState ) );		


		//keep on looping so long as there is a state node in the frontier
		while ( !this->m_frontier.empty() )
		{
			//if the frontier is empty and if there is no solution found
			if ( this->m_frontier.empty() && this->m_tempSolutionNodePtr == 0 )
			{
				solutionFound = false;
				break;
			}
			else if ( this->m_frontier.empty() && this->m_tempSolutionNodePtr != 0 ) 
			{
				//generate the solution
				this->GenerateSolution( this->m_tempSolutionNodePtr );
				solutionFound = true;
				break;
			}

			//get the most recent state node from the frontier and set it as the current node			
			//std::sort_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
			//std::make_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
			this->m_currentState = this->m_frontier.front();
			//this->m_currentState = this->m_frontier.back();
			//this->m_currentState = this->m_frontierSorted.top();
			//this->m_currentState = this->m_frontierSorted.end()->second;

			//expand the current state node
			expandSuccess = this->ExpandCurrentState();

			//remove the state node from the frontier 
			std::pop_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
			this->m_frontier.pop_back();			
			//this->m_frontierSorted.pop();
			//this->m_frontierSorted.erase( this->m_frontierSorted.end()->first );

			//generate the state key
			unsigned long long stateKeyVal = this->GenerateStateKey( this->m_currentState->m_data );				
			//move the state node to the explored set
			this->m_exploredSet.insert( std::make_pair( stateKeyVal, this->m_currentState ) );

			if ( expandSuccess == true )
			{
				//retrieve the resulting state values from the expansion
				ResultingNodeMap::iterator itor = this->m_resultingNodeMap.begin();
				ResultingNodeMap::iterator end = this->m_resultingNodeMap.end();

				while ( itor != end )
				{
					//unsigned int tileMovementDirection = itor->first;
					MyNode * resultingStateNode = itor->second;

					//if current state is same as goal/target state of a normal puzzle
					if ( this->CheckLegalTilesPositions( resultingStateNode->m_data ) == true )
					{				
						//check if there is already an existing solution
						if ( this->m_tempSolutionNodePtr != 0 )
						{
							//if the new found solution has a lower cost, set it as the new solution
							if ( resultingStateNode->m_totalCost < this->m_tempSolutionNodePtr->m_totalCost )
							{
								//store the solution with the lower cost
								this->m_tempSolutionNodePtr = resultingStateNode;
							}
						}
						else
						{
							//store the initial solution
							this->m_tempSolutionNodePtr = resultingStateNode;
						}

						//check the frontier if there is another path with a lower cost than the current solution						
						//if ( this->m_frontierSorted.top()->m_totalCost < this->m_tempSolutionNodePtr->m_totalCost )
						//if ( this->m_frontierSorted.end()->second->m_totalCost < this->m_tempSolutionNodePtr->m_totalCost )
						if ( this->m_frontier.size() != 0 && ( this->m_frontier.front()->m_totalCost < this->m_tempSolutionNodePtr->m_totalCost ) )
						{
							break;
						}
						else
						{
							//generate the solution
							this->GenerateSolution( this->m_tempSolutionNodePtr );
							solutionFound = true;	
						}

						//generate the solution
						//this->GenerateSolution( resultingStateNode );
						//solutionFound = true;	

						//delete the resulting node since solution has already been found
						/*
						delete [] resultingStateNode->m_data;
						resultingStateNode->m_data = 0;
						delete resultingStateNode;
						resultingStateNode = 0;
						*/
					}
					else
					{
						if ( solutionFound == true )
						{
							//delete the subsequent resulting nodes since solution has already been found
							//this->CleanNode( resultingStateNode );
						}
						else
						{
							//add the resulting node to the frontier
							this->m_frontier.push_back( resultingStateNode );
							std::push_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
							//this->m_frontierSorted.push( resultingStateNode );
							//unsigned long long stateKey = this->GenerateStateKey( resultingStateNode );
							//this->m_frontierSorted.insert( std::make_pair( stateKey, resultingStateNode ) );
						}
					}

					++itor;
				}//end while loop	

				//if solution found, report it
				if ( solutionFound == true )
				{
					return solutionFound;
				}
			}

		}//end while loop

	}	

	return solutionFound;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function is the Depth-First Search Algorithm

\param
\return bool
true if the solution was found, otherwise false
*/
/******************************************************************************/
bool NPuzzle::DepthFirstSearch( void )
{
	bool solutionFound = false;
	bool expandSuccess = false;

	//if initial state node is same as goal/target state node of a normal puzzle
	if ( this->CheckLegalTilesPositions( this->m_initialState->m_data ) == true )
	{
		solutionFound = true;
		return solutionFound;
	}
	else
	{
		//add the initial state node to the frontier
		this->m_frontier.push_back( this->m_initialState );

		//keep on looping so long as there is a state node in the frontier
		while ( !this->m_frontier.empty() )
		{
			//if the frontier is empty, there is no solution found
			if ( this->m_frontier.empty() )
			{
				solutionFound = false;
				break;
			}

			//get the most recent state node from the frontier and set it as the current node
			this->m_currentState = this->m_frontier.back();

			//expand the current state node
			expandSuccess = this->ExpandCurrentState();

			//remove the state node from the frontier 
			this->m_frontier.pop_back();
			//generate the state key
			unsigned long long stateKeyVal = this->GenerateStateKey( this->m_currentState->m_data );				
			//move the state node to the explored set
			this->m_exploredSet.insert( std::make_pair( stateKeyVal, this->m_currentState ) );

			if ( expandSuccess == true )
			{
				//retrieve the resulting state values from the expansion
				ResultingNodeMap::iterator itor = this->m_resultingNodeMap.begin();
				ResultingNodeMap::iterator end = this->m_resultingNodeMap.end();

				while ( itor != end )
				{
					//unsigned int tileMovementDirection = itor->first;
					MyNode * resultingStateNode = itor->second;

					//if current state is same as goal/target state of a normal puzzle
					if ( this->CheckLegalTilesPositions( resultingStateNode->m_data ) == true )
					{						
						//generate the solution
						this->GenerateSolution( resultingStateNode );	
						solutionFound = true;	

						//delete the resulting node since solution has already been found
						/*
						delete [] resultingStateNode->m_data;
						resultingStateNode->m_data = 0;
						delete resultingStateNode;
						resultingStateNode = 0;
						*/
					}
					else
					{
						if ( solutionFound == true )
						{
							//delete the subsequent resulting nodes since solution has already been found
							//this->CleanNode( resultingStateNode );
						}
						else
						{
							//add the resulting node to the frontier
							this->m_frontier.push_back( resultingStateNode );
						}
					}

					++itor;
				}//end while loop	

				//if solution found, report it
				if ( solutionFound == true )
				{
					return solutionFound;
				}
			}

		}//end while loop

	}	

	return solutionFound;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function will expand the current state

\param
\return bool
true if the current state can be expanded, otherwise false
*/
/******************************************************************************/
bool NPuzzle::ExpandCurrentState( void )
{
	bool expandSuccessful = true;
	bool expandLeft = false;
	bool expandRight = false;
	bool expandUp = false;
	bool expandDown = false;

	//refresh the resulting node map
	this->m_resultingNodeMap.clear();
	
	unsigned int * expandedStateData = 0;

	//get the position of the hole/empty tile
	unsigned int holePosition = this->m_currentState->m_data[ this->m_stateSize - 1 ];
	unsigned int holeRow = holePosition / this->m_sideSize;
	unsigned int holeColumn = holePosition % this->m_sideSize;

	unsigned index = 0;
	//loop through the one-dimensional 3D matrix
	for ( unsigned row = 0; row < this->m_sideSize; ++row )		
	{
		for ( unsigned col = 0; col < this->m_sideSize; ++col )
		{
			//index to simulate a two-dimensional matrix
			index = ( row * this->m_sideSize ) + col;

			//check only the tile blocks
			if ( index != holePosition )
			{
				//if the the tile and the hole are on the same row
				if ( row == holeRow )
				{
					//move tile to the right
					if ( ( col - holeColumn ) == 1 )
					{	
						//generate the resulting nodes
						expandLeft = this->ExpandCurrentStateHelper( LEFT, expandedStateData, holePosition, index );
												
					}
					//move tile to the left
					else if ( ( col - holeColumn ) == -1 )
					{
						//generate the resulting nodes
						expandRight = this->ExpandCurrentStateHelper( RIGHT, expandedStateData, holePosition, index );
					}				
				}
				//if the the tile and the hole are on the same column
				else if ( col == holeColumn )
				{
					//move the tile down
					if ( ( row - holeRow ) == -1 )
					{
						//generate the resulting nodes
						expandDown = this->ExpandCurrentStateHelper( DOWN, expandedStateData, holePosition, index );
					}
					//move the tile up
					else if ( ( row - holeRow ) == 1 )
					{
						//generate the resulting nodes
						expandUp = this->ExpandCurrentStateHelper( UP, expandedStateData, holePosition, index );
					}
				}			
			}

		}//end for loop

	}//end for loop

	if ( expandLeft == true || expandRight == true || expandUp == true || expandDown == true )
	{
		expandSuccessful = true;
	}
	
	return expandSuccessful;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function will generate possible resulting states from expanded current state

\param tileMovement
defines the tile movement direction
\param state
the array values of the state
\param holePosition
the position of the hole
\param tilePosition
the position of the tile
\return bool
if true, there are resulting states generated through the expansion, otherwise false
*/
/******************************************************************************/
bool NPuzzle::ExpandCurrentStateHelper( const TILE_MOVEMENT tileMovement, unsigned int * state, const unsigned int holePosition, const unsigned int tilePosition )
{
	bool expanded = false;

	//create a deep copy of the current state which will be used to generate the array values of the expanded state
	state = new unsigned int[ this->m_stateSize ];
	this->CopyStateValues( this->m_currentState->m_data, state, this->m_stateSize );

	//swap the hole and the tile values
	this->SwapHoleAndTile( state, holePosition, tilePosition );

	//generate the state key
	unsigned long long stateKey = this->GenerateStateKey( state );

	//validate if the state is existing either in explored set or the frontier
	if ( this->IsStateExistingInExploredSet( stateKey ) == false 
		&& this->IsStateExistingInFrontier( state ) == false )
	{
		//generate the resulting node
		MyNode * resultingNode = this->GenerateStateNode( state, this->m_currentState );

		//add the resulting node with the tile movement as defined by the change in the state array values
		this->m_resultingNodeMap.insert( std::make_pair( tileMovement, resultingNode ) );	
		expanded = true;
	}	
	else
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//if A Star Algorithm
		if ( this->m_searchMethod == ASTAR )
		{
			unsigned matchingFrontierIndex = 0;
			unsigned matchingFrontierCost = 0;

			//check if the state is already in the frontier
			if ( this->IsStateExistingInFrontier( state, matchingFrontierIndex, matchingFrontierCost ) == true )
			{
				//generate the resulting node
				MyNode * resultingNode = this->GenerateStateNode( state, this->m_currentState );

				//check the cost
				if ( resultingNode->m_totalCost < matchingFrontierCost )
				{
					//replace the values of the matching frontier node
					this->m_frontier.at( matchingFrontierIndex )->m_totalCost = resultingNode->m_totalCost;
					this->m_frontier.at( matchingFrontierIndex )->m_currentActualCost = resultingNode->m_currentActualCost;
					this->m_frontier.at( matchingFrontierIndex )->m_parent = resultingNode->m_parent;

					//synch up with the heap to ensure proper sorting				
					//std::sort_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );
					std::make_heap( this->m_frontier.begin(), this->m_frontier.end(), CompareNode() );				
				}

				//destroy the resulting node
				this->CleanNode( resultingNode );
			}
			else
			{
				delete [] state;
				state = 0;
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else
		{
			delete [] state;
			state = 0;
		}
	}

	return expanded;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function generates the resulting node

\param state
an array of numbers that represents the order of the tiles in the puzzle
\param parentNode
the parent of the resulting node
\return MyNode *
the pointer to the resulting node
*/
/******************************************************************************/
MyNode * NPuzzle::GenerateStateNode( unsigned int * state, MyNode * parentNode )
{
	//generate the state node
	MyNode * resultingNode = new MyNode;
	//store the resulting state data
	resultingNode->m_data = state;
	//set the parent of the resulting node
	resultingNode->m_parent = parentNode;

	if ( this->m_searchMethod == ASTAR )
	{
		//set the actual cost of the resulting node
		resultingNode->m_currentActualCost = NODE_COST + resultingNode->m_parent->m_currentActualCost;
		//compute for the total cost
		unsigned int estimatedCost = this->Heuristic( resultingNode );
		resultingNode->m_totalCost = resultingNode->m_currentActualCost + estimatedCost;
	}
	else
	{
		resultingNode->m_currentActualCost = 0;
		resultingNode->m_totalCost = 0;
	}

	return resultingNode;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function is using the Manhattan Distance heuristic that never overestimate the actual number of moves required 
to reach the target state from the current state n. This function is admissible and consistent.

\param node
the node that will contain the tile arrangement data
\return unsigned int
the estimated cost
*/
/******************************************************************************/
const unsigned int NPuzzle::Heuristic( const MyNode * node ) const
{
	unsigned int estimatedCost = 0;
	unsigned int tileNumber = 0;
	unsigned int targetRowVal = 0;
	unsigned int targetColVal = 0;
	int rowDiff = 0;
	int colDiff = 0;

	unsigned index = 0;
	//loop through the one-dimensional 3D matrix
	for ( unsigned row = 0; row < this->m_sideSize; ++row )		
	{
		for ( unsigned col = 0; col < this->m_sideSize; ++col )
		{
			//index to simulate a two-dimensional matrix
			index = ( row * this->m_sideSize ) + col;

			//get the tile number from the state node data based on the current index
			tileNumber = node->m_data[index];	

			//ignore the empty tile / hole
			if ( tileNumber != 0 )
			{
				//get the row and column of the tile in the target state
				this->DeriveRowCol( this->m_targetState, tileNumber, targetRowVal, targetColVal );

				//get the row and column value difference between the tile in its current state and its target state
				rowDiff = row - targetRowVal;
				colDiff = col - targetColVal;

				//the row and column distance of the tile from its current state to the target state will be the Manhattan Distance heuristic estimated cost
				estimatedCost += abs( rowDiff ) + abs( colDiff );
			}

		}//end for loop

	}//end for loop

	return estimatedCost;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function derives the corresponding row and column of the tile in the target state

\param node
the node that will contain the tile arrangement data
\param tileNumber
the tile number
\param rowVal
the row value of the tile
\param colVal
the column value of the tile
\return
*/
/******************************************************************************/
void NPuzzle::DeriveRowCol( const MyNode * node, const unsigned int tileNumber, unsigned int & rowVal, unsigned int & colVal ) const
{
	unsigned index = 0;
	//loop through the one-dimensional 3D matrix
	for ( unsigned row = 0; row < this->m_sideSize; ++row )		
	{
		for ( unsigned col = 0; col < this->m_sideSize; ++col )
		{
			//index to simulate a two-dimensional matrix
			index = ( row * this->m_sideSize ) + col;

			//if the tile has been found in the tile arrangement data of the node
			if ( tileNumber == node->m_data[ index ] )
			{
				//get the corresponding row and column based on the specified tile number
				rowVal = row;
				colVal = col;
				return;
			}

		}//end for loop

	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
This function checks if the arrangement provided in the array is legal for the selected goal group of states. 
For our case we can only check for the normal puzzle kind (because we are not using the circular one).

\param state
an array of numbers that represents the order of the tiles in the puzzle
\param PUZZLE_KIND
the type of puzzle
\return bool
true if the passed array values matches the array values of the goal/target state
*/
/******************************************************************************/
bool NPuzzle::CheckLegalTilesPositions( const unsigned int * state, PUZZLE_KIND /*puzzleKind*/ )
{
	bool matchingTilePattern = true;

	//compare the values of the state with that of the goal/target state
	for ( unsigned int index = 0; index < this->m_totalTilesNumber; ++index )
	{
		if ( state[index] != this->m_targetState->m_data[index] )
		{
			matchingTilePattern = false;
			break;
		}
	
	}//end for loop

	return matchingTilePattern;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Returns the number of numbered cells

\param
\return unsigned int
the number of tiles
*/
/******************************************************************************/
unsigned int NPuzzle::GetTilesNumber( void )
{
	return this->m_totalTilesNumber;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Returns the number of cells (or columns)

\param
\return unsigned int
the number of tiles per side
*/
/******************************************************************************/
unsigned int NPuzzle::GetSideSize()
{
	return this->m_sideSize;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Perform a deep copy of the state array values

\param sourceState
the array values of the source state
\param destinationState
the array values of the destination state
\param bufferSize
the buffer size of the destination state array
\return
*/
/******************************************************************************/
void NPuzzle::CopyStateValues( const unsigned int * sourceState, unsigned int * destinationState, unsigned int bufferSize ) const
{
	for ( unsigned int index = 0; index < bufferSize; ++index )
	{
		destinationState[ index ] = sourceState[ index ];
	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Compare the state array values

\param rhsState
the array values of the state
\param lhsState
the array values of the state
\param bufferSize
the buffer size of the destination state array
\return bool
if true, the state array values are the same, otherwise false
*/
/******************************************************************************/
bool NPuzzle::CompareStateValues( const unsigned int * rhsState, const unsigned int * lhsState, unsigned int bufferSize ) const
{
	bool same = true;

	for ( unsigned int index = 0; index < bufferSize; ++index )
	{	
		//compare the state values
		if ( rhsState[ index ] != lhsState[ index ] )
		{
			same = false;
			break;
		}
	}//end for loop

	return same;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Swap the values between the hole and the tile

\param state
the array values of the state
\param holePosition
the position of the hole
\param tilePosition
the position of the tile
\return
*/
/******************************************************************************/
void NPuzzle::SwapHoleAndTile( unsigned int * state, const unsigned int holePosition, const unsigned int tilePosition ) const
{
	//swap the hole and the tile values
	state[ holePosition ] = this->m_currentState->m_data[ tilePosition ];
	state[ tilePosition ] = this->m_currentState->m_data[ holePosition ];
	//store the new hole position
	state[ this->m_stateSize - 1 ] = tilePosition;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Generates the key for the state based on its array values
If the state array values are { 1, 2, 0, 3 } the generated key will be 1203

\param state
the array values of the state
\return unsigned long long
the state key
*/
/******************************************************************************/
unsigned long long NPuzzle::GenerateStateKey( const unsigned int * state ) const
{
	unsigned long long stateKey = 0;
	//char charBuffer [10];
	//std::string strStateKey;

	for ( unsigned int index = 0; index < this->m_totalTilesNumber; ++index )
	{
		//append the tile values to generate the state key
		stateKey += state[ index ];

		//convert integer to characters
		//_itoa_s( stateKey, charBuffer, 10 );
		
		//on the last iteration
		if ( index == this->m_totalTilesNumber - 1 )
		{
			//do nothing
		}
		else
		{
			//multiply by 10 to traverse to the next least significant digit
			stateKey *= 10;
		}
	}//end for loop

	//store the character array in the string
	//strStateKey.append( charBuffer );

	return stateKey;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Validates if the state is existing in the explored set

\param stateKey
the state key that is used to check against the keys found in the explored set map
\return bool
if true, the state is existing in the explored set, otherwise false
*/
/******************************************************************************/
bool NPuzzle::IsStateExistingInExploredSet( const unsigned long long stateKey ) const
{
	bool isStateExistingInExploredSet = true;

	//validate if the expanded state values are already in the explored set
	ExploredSetMap::const_iterator itor = this->m_exploredSet.find( stateKey );						
	//if not found
	if ( itor == this->m_exploredSet.end() )
	{		
		isStateExistingInExploredSet = false;
	}

	return isStateExistingInExploredSet;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Validates if the state is existing in the frontier

\param state
the array values of the state
\return bool
if true, the state is existing in the frontier, otherwise false
*/
/******************************************************************************/
bool NPuzzle::IsStateExistingInFrontier( const unsigned int * state ) const
{
	bool isStateExistingInFrontier = false;

	//validate if the expanded state values are already in the frontier
	for ( unsigned int index = 0; index < this->m_frontier.size(); ++index )
	{
		//get the frontier data
		unsigned int * frontierStateData = this->m_frontier.at( index )->m_data;
		//compare the state data
		if ( this->CompareStateValues( frontierStateData, state, this->m_totalTilesNumber ) == true )
		{
			isStateExistingInFrontier = true;
			break;
		}
	}//end for loop

	return isStateExistingInFrontier;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Validates if the state is existing in the frontier

\param state
the array values of the state
\param frontierIndex
the index of the frontier state
\param frontierCost
the cost of the frontier state
\return bool
if true, the state is existing in the frontier, otherwise false
*/
/******************************************************************************/
bool NPuzzle::IsStateExistingInFrontier( const unsigned int * state, unsigned & frontierIndex, unsigned & frontierCost ) const
{
	bool isStateExistingInFrontier = false;

	//validate if the expanded state values are already in the frontier
	for ( unsigned int index = 0; index < this->m_frontier.size(); ++index )
	{
		//get the frontier data
		unsigned int * frontierStateData = this->m_frontier.at( index )->m_data;
		//compare the state data
		if ( this->CompareStateValues( frontierStateData, state, this->m_totalTilesNumber ) == true )
		{
			isStateExistingInFrontier = true;
			//get the index and the cost of the matching frontier state
			frontierIndex = index;
			frontierCost = this->m_frontier.at( index )->m_totalCost;
			break;
		}
	}//end for loop

	return isStateExistingInFrontier;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Generates and stores the solution by traversing upwards through the nodes as linked together by the parent node

\param resultingNode
the resulting node that leads to the goal/target state node
\return
*/
/******************************************************************************/
void NPuzzle::GenerateSolution( MyNode * resultingNode )
{
	MyNode * tempNode = 0;

	unsigned index = 0;
	//keep on looping while the node has a parent
	while ( resultingNode->m_parent != 0 )
	{
		//on the first iteration, do not include the target/goal state in the solution
		//if ( index != 0 )
		//{
			//append the resulting node state data to the solution
			this->m_solution.push_back( resultingNode->m_data );
		//}

		//store the pointer to the resulting node in a temporary container
		tempNode = resultingNode;
		//traverse the solution by going through the parent
		resultingNode = tempNode->m_parent;

		++index;

	}//end while loop

	this->m_noOfSolutionSteps = this->m_solution.size();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Cleans the solution to free memory

\param
\return
*/
/******************************************************************************/
void NPuzzle::CleanSolution( void )
{
	for ( unsigned int index = 0; index < this->m_solution.size(); ++index )
	{
		if ( this->m_solution.at( index ) != 0 )
		{
			delete [] this->m_solution.at( index );
			this->m_solution.at( index ) = 0;
		}
	}//end for loop

	this->m_solution.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Cleans the frontier to free memory

\param
\return
*/
/******************************************************************************/
void NPuzzle::CleanFrontier( void )
{
	for ( unsigned int index = 0; index < this->m_frontier.size(); ++index )
	{
		if ( this->m_frontier.at( index )->m_data != 0 )
		{
			delete [] this->m_frontier.at( index )->m_data;
			this->m_frontier.at( index )->m_data = 0;
		}
		if ( this->m_frontier.at( index ) != 0 )
		{
			delete this->m_frontier.at( index );
			this->m_frontier.at( index ) = 0;
		}
	}//end for loop

	this->m_frontier.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Cleans the explored set to free memory

\param
\return
*/
/******************************************************************************/
void NPuzzle::CleanExploredSet( void )
{
	//release the explored set from the heap memory
	ExploredSetMap::iterator itorEs = this->m_exploredSet.begin();
	ExploredSetMap::iterator endEs = this->m_exploredSet.end();
	while ( itorEs != endEs )
	{
		if ( itorEs->second->m_data != 0 )
		{
			delete [] itorEs->second->m_data;
			itorEs->second->m_data = 0;
		}
		if ( itorEs->second != 0 )
		{
			delete itorEs->second;
			itorEs->second = 0;
		}

		++itorEs;
	}//end while loop

	this->m_exploredSet.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Cleans the resulting nodes set to free memory

\param
\return
*/
/******************************************************************************/
void NPuzzle::CleanResultingNodes( void )
{
	//release the left over resulting nodes from the heap memory
	ResultingNodeMap::iterator itor = this->m_resultingNodeMap.begin();
	ResultingNodeMap::iterator end = this->m_resultingNodeMap.end();
	while ( itor != end )
	{
		if ( itor->second->m_data != 0 )
		{
			delete [] itor->second->m_data;
			itor->second->m_data = 0;
		}
		if ( itor->second != 0 )
		{
			delete itor->second;
			itor->second = 0;
		}

		++itor;
	}//end while loop

	this->m_resultingNodeMap.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*! 
\brief 
Cleans the node set to free memory

\param
\return
*/
/******************************************************************************/
void NPuzzle::CleanNode( MyNode * node ) const
{
	if ( node != 0 )
	{
		if ( node->m_data != 0 )
		{
			delete [] node->m_data;
			node->m_data = 0;
		}

		delete node;
		node = 0;
	}
}