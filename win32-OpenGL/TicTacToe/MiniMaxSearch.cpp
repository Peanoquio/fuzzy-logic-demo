/******************************************************************************/
/*!
\file MiniMaxSearch.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #03
\date 15/03/2012
\brief
This is the class that contains the Minimax algorithm with Alpha-Beta pruning

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "MiniMaxSearch.h"
#include <algorithm>
#include <iostream>
#include <iomanip>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the MoveCoord struct

\param row
the row number
\param col
the column number

\return
*/
/******************************************************************************/
MoveCoord::MoveCoord( const unsigned row, const unsigned col )
{
	this->m_row = row;
	this->m_col = col;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the TicTacToe class

\param

\return
*/
/******************************************************************************/
TicTacToe::TicTacToe( void )
	:m_currentDepth( 0 ),
	m_currentTurn( PLAYER ),
	m_nextMoveRow( 0 ),
	m_nextMoveCol( 0 )
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the destructor of the TicTacToe class

\param

\return
*/
/******************************************************************************/
TicTacToe::~TicTacToe( void )
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This gets the next move of the computer based on the evaluation search done by the MiniMax algorithm

\param row
the row number of the computer's next move
\param col
the column number of the computer's next move

\return
*/
/******************************************************************************/
void TicTacToe::GetNextMove( unsigned & row, unsigned & col ) const
{
	row = this->m_nextMoveRow;
	col = this->m_nextMoveCol;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the main function of the MiniMax search algorithm that incorporates 
alpha-beta pruning and cutting-off the depth

\param depth
the depth of the tree which is actually the depth of the recursion'

\return bool
if true, the MiniMax search algorithm is successful, otherwise return false
*/
/******************************************************************************/
bool TicTacToe::MiniMax( unsigned int depth )
{
	int alpha = NEG_INFINITY; //computer to find the maximum of the lower bound
	int beta = INFINITY; //player to find the minimum of the upper bound
	int utilityVal = alpha;

	unsigned row = 0;
	unsigned col = 0;
	std::vector< MoveCoord > moveList;
	//find the next possible moves and store them in a list
	bool nextMoveFound = this->FindNextMove( moveList );

	//while there is a next move on the board
	if ( nextMoveFound == true )
	{
		for ( unsigned index = 0; index < moveList.size(); ++index )
		{
			row = moveList.at( index ).m_row;
			col = moveList.at( index ).m_col;

			//plot the computer move on the board
			this->Place( row, col, COMPUTER );	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			int terminalValue = 0;
			//if the terminal state has been reached
			if ( this->TerminalTest( terminalValue, depth ) == true )
			{
				//compare with the current alpha value
				if ( terminalValue >= alpha )
				{
					alpha = terminalValue;
					//store the potential next best move
					this->m_nextMoveRow = row;
					this->m_nextMoveCol = col;	

					//undo the move before moving one level up
					this->UnPlace( row, col, CELL_DEFAULT_VALUE );

					break;
				}
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else
			{
				//get the maximum of the lower bound based on the player's possible next move
				int utilO = this->O( static_cast<int>( row ), static_cast<int>( col ), depth, alpha, beta );
				utilityVal = std::max( utilityVal, utilO );
				
				//compare with the current alpha value
				if ( utilityVal > alpha )
				{
					alpha = utilityVal;
					//store the potential next best move
					this->m_nextMoveRow = row;
					this->m_nextMoveCol = col;						
				}
			}

			//undo the move before traversing to the next possible move in the loop
			this->UnPlace( row, col, CELL_DEFAULT_VALUE );

		}//end for loop

		//update the board with the computer's move
		this->SetBoardCell( this->m_nextMoveRow, this->m_nextMoveCol, COMPUTER );	
	}

	int offset = this->m_currentDepth;
	std::cout << std::setfill (' ') << std::setw( offset ) << "====================" << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << "depth : " << depth << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << "utility value : " << alpha << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << this->Board[0][0] << "  " << this->Board[0][1] << "  " << this->Board[0][2] << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << this->Board[1][0] << "  " << this->Board[1][1] << "  " << this->Board[1][2] << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << this->Board[2][0] << "  " << this->Board[2][1] << "  " << this->Board[2][2] << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << "====================" << std::endl;

	return nextMoveFound;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the computer's turn for performing the maximum search of the lower bound values returned by the player.
This incorporates alpha-beta pruning and cutting-off the depth search.

\param r
the row number
\param c
the column number
\param depth
the depth of the tree which is actually the depth of the recursion'
\param alpha
the computer's current maximum lower bound value based on the player's next move
\param beta
the player's current minimum upper bound value based on the computer's next move

\return
*/
/******************************************************************************/
int TicTacToe::X( int /*r*/, int /*c*/, int depth, int alpha, int beta )
{
	int utilityVal = NEG_INFINITY;			

	unsigned row = 0;
	unsigned col = 0;
	std::vector< MoveCoord > moveList;
	//find the next possible moves and store them in a list
	bool nextMoveFound = this->FindNextMove( moveList );

	//while there is a next move on the board
	if ( nextMoveFound == true )
	{
		for ( unsigned index = 0; index < moveList.size(); ++index )
		{
			row = moveList.at( index ).m_row;
			col = moveList.at( index ).m_col;

			//plot the computer move on the board
			this->Place( row, col, COMPUTER );	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			int terminalValue = 0;
			//if the terminal state has been reached
			if ( this->TerminalTest( terminalValue, depth ) == true )
			{
				//undo the move before moving one level up
				this->UnPlace( row, col, CELL_DEFAULT_VALUE );
				return terminalValue;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else
			{
				//get the maximum of the lower bound based on the player's possible next move
				int utilO = this->O( row, col, depth, alpha, beta );
				utilityVal = std::max( utilityVal, utilO );

				//if the value is out of bounds ( greater than or equal to the current minimum of the upper bound )
				if ( utilityVal >= beta )
				{
					//PRUNE THE BRANCH
					//undo the move before moving one level up
					this->UnPlace( row, col, CELL_DEFAULT_VALUE );
					return utilityVal;
				}
				else
				{
					//update the maximum value if applicable
					alpha = std::max( alpha, utilityVal );
				}
			}

			//undo the move as we traverse to the next possible action in the loop
			this->UnPlace( row, col, CELL_DEFAULT_VALUE );

		}//end for loop
	}

	return utilityVal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the player's turn for performing the minimum search of the upper bound values returned by the computer.
This incorporates alpha-beta pruning and cutting-off the depth search.

\param r
the row number
\param c
the column number
\param depth
the depth of the tree which is actually the depth of the recursion'
\param alpha
the computer's current maximum lower bound value based on the player's next move
\param beta
the player's current minimum upper bound value based on the computer's next move

\return
*/
/******************************************************************************/
int TicTacToe::O( int /*r*/, int /*c*/, int depth, int alpha, int beta )
{
	int utilityVal = INFINITY;			

	unsigned row = 0;
	unsigned col = 0;	
	std::vector< MoveCoord > moveList;
	//find the next possible moves and store them in a list
	bool nextMoveFound = this->FindNextMove( moveList );

	//while there is a next move on the board
	if ( nextMoveFound == true )
	{
		for ( unsigned index = 0; index < moveList.size(); ++index )
		{
			row = moveList.at( index ).m_row;
			col = moveList.at( index ).m_col;

			//plot the player move on the board
			this->Place( row, col, PLAYER );	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			int terminalValue = 0;
			//if the terminal state has been reached
			if ( this->TerminalTest( terminalValue, depth ) == true )
			{
				//undo the move before moving one level up
				this->UnPlace( row, col, CELL_DEFAULT_VALUE );
				return terminalValue;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			else
			{
				//get the minimum of the upper bound based on the computer's possible next move
				int utilX = this->X( row, col, depth, alpha, beta );
				utilityVal = std::min( utilityVal, utilX );

				//if the value is out of bounds ( less than or equal to the current maximum of the lower bound )
				if ( utilityVal <= alpha )
				{
					//PRUNE THE BRANCH
					//undo the move before moving one level up
					this->UnPlace( row, col, CELL_DEFAULT_VALUE );
					return utilityVal;
				}
				else
				{
					//update the minimum value if applicable
					beta = std::min( beta, utilityVal );
				}
			}

			//undo the move as we traverse to the next possible action in the loop
			this->UnPlace( row, col, CELL_DEFAULT_VALUE );

		}//end for loop
	}

	return utilityVal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Places a value in the board cell specified by the row and column

\param row
the row number
\param col
the column number
\param turn
the value to determine whether its the player or computer turn

\return
*/
/******************************************************************************/
void TicTacToe::Place( int row, int column, int turn )
{
	//increment the depth counter
	++this->m_currentDepth;

	this->SetBoardCell( row, column, turn );

	/*
	if ( turn == PLAYER )
	{
	this->SetBoardCell( row, column, turn );
	}
	else if ( turn == COMPUTER )
	{
	this->SetBoardCell( row, column, turn );
	}
	*/
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Undoes a value in the board cell specified by the row and column

\param row
the row number
\param col
the column number
\param turn
the value to determine whether its the player or computer turn

\return
*/
/******************************************************************************/
void TicTacToe::UnPlace( int row, int column, int /*turn*/ )
{
	//decrement the depth counter
	--this->m_currentDepth;

	this->SetBoardCell( row, column, CELL_DEFAULT_VALUE );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Validates if the computer wins the game by filling up any row, column or diagonal on the board

\param

\return bool 
if true, the computer wins the game, otherwise false
*/
/******************************************************************************/
bool TicTacToe::WinTest()
{
	bool winFlag = false;

	//validate the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		winFlag = this->CheckRow( rowIndex, COMPUTER );
		if ( winFlag == true )
		{
			return winFlag;
		}
	}//end for loop

	//validate the columns
	for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
	{
		winFlag = this->CheckColumn( colIndex, COMPUTER );
		if ( winFlag == true )
		{
			return winFlag;
		}
	}//end for loop

	//check diagonals from left to right
	winFlag = this->CheckDiagonal( true, COMPUTER );
	if ( winFlag == true )
	{
		return winFlag;
	}

	//check diagonals from right to left
	winFlag = this->CheckDiagonal( false, COMPUTER );
	if ( winFlag == true )
	{
		return winFlag;
	}

	return winFlag;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Validates if the player wins the game by filling up any row, column or diagonal on the board

\param

\return bool 
if true, the player wins the game, otherwise false
*/
/******************************************************************************/
bool TicTacToe::LooseTest()
{
	bool winFlag = false;

	//validate the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		winFlag = this->CheckRow( rowIndex, PLAYER );
		if ( winFlag == true )
		{
			return winFlag;
		}
	}//end for loop

	//validate the columns
	for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
	{
		winFlag = this->CheckColumn( colIndex, PLAYER );
		if ( winFlag == true )
		{
			return winFlag;
		}
	}//end for loop

	//check diagonals from left to right
	winFlag = this->CheckDiagonal( true, PLAYER );
	if ( winFlag == true )
	{
		return winFlag;
	}

	//check diagonals from right to left
	winFlag = this->CheckDiagonal( false, PLAYER );
	if ( winFlag == true )
	{
		return winFlag;
	}

	return winFlag;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function tests if all the cells are filled on the board and none of the players won. 
It is used as an else case after testing WinTest() and Loosetest() functions.

\param

\return bool 
if true, the board has been filled up, otherwise false
*/
/******************************************************************************/
bool TicTacToe::DrawTest()
{
	bool isBoardFilledUp = true;

	//iterate through the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		//iterate through the columns
		for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
		{
			//validate if every cell on the board has been filled up
			if ( this->Board[ rowIndex ][ colIndex ] == CELL_DEFAULT_VALUE )
			{
				isBoardFilledUp = false;
				return isBoardFilledUp;
			}
		}//end for loop

	}//end for loop

	return isBoardFilledUp;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function test if a leaf node (goal node) is achieved or if the maximum depth is reached and returns true. 
Otherwise it returns false.

\param terminalValue
this will contain the utility value if a goal state has been reached
otherwise, it will contain the evaluation value if a certain depth has been reached
\param depth
the depth of the recursion

\return bool 
if true, the board has been filled up, otherwise false
*/
/******************************************************************************/
bool TicTacToe::TerminalTest( int & terminalValue, int depth )
{
	bool reachedEnd = false;

	if ( this->WinTest() == true )
	{
		terminalValue = MAX_VALUE;
		reachedEnd = true;
	}
	else if ( this->LooseTest() == true )
	{
		terminalValue = MIN_VALUE;
		reachedEnd = true;
	}
	else if ( this->DrawTest() == true )
	{
		terminalValue = 0;
		reachedEnd = true;
	}
	else
	{
		//if the specified depth has been reached
		if ( this->m_currentDepth == depth )
		{
			//TODO: If the maximum depth is reached it returns the evaluation value of the state by calling EvaluationTest() function.
			terminalValue = this->EvaluationTest();

			reachedEnd = true;
		}
	}	

	/*
	if ( reachedEnd == true )
	{
		int offset = this->m_currentDepth * 7;
		std::cout << std::setfill (' ') << std::setw( offset ) << "====================" << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << "depth : " << this->m_currentDepth << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << "terminalValue : " << terminalValue << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << this->Board[0][0] << "  " << this->Board[0][1] << "  " << this->Board[0][2] << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << this->Board[1][0] << "  " << this->Board[1][1] << "  " << this->Board[1][2] << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << this->Board[2][0] << "  " << this->Board[2][1] << "  " << this->Board[2][2] << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << "====================" << std::endl;
	}
	*/

	return reachedEnd;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the heuristic evaluation for the TicTacToe game that estimates the utility of a move at a certain depth.
The heuristics is based on this:
(the number of lines that are still possible for computer to fill in total) - (the number of lines that are still possible for player to fill total)

\param

\return int
the estimated utility value
*/
/******************************************************************************/
int TicTacToe::EvaluationTest( void )
{
	int utilityValue = 0;

	//get the possible number of winning states for the computer and the player
	int computerWinStateCount = this->CountPossibleWinStates( COMPUTER );
	int playerWinStateCount = this->CountPossibleWinStates( PLAYER );

	//compute the heuristics
	utilityValue = computerWinStateCount - playerWinStateCount;

	return utilityValue;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This counts the number of possible winning states

\param value
the value placed by either the computer or the player

\return int
the number of possible winning states
*/
/******************************************************************************/
int TicTacToe::CountPossibleWinStates( const int value ) const
{
	int numOfWinStates = 0;
	bool winFlag = false;

	//validate the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		winFlag = this->CheckRow( rowIndex, value, false );
		if ( winFlag == true )
		{
			++numOfWinStates;
		}
	}//end for loop

	//validate the columns
	for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
	{
		winFlag = this->CheckColumn( colIndex, value, false );
		if ( winFlag == true )
		{
			++numOfWinStates;
		}
	}//end for loop

	//check diagonals from left to right
	winFlag = this->CheckDiagonal( true, value, false );
	if ( winFlag == true )
	{
		++numOfWinStates;
	}

	//check diagonals from right to left
	winFlag = this->CheckDiagonal( false, value, false );
	if ( winFlag == true )
	{
		++numOfWinStates;
	}

	return numOfWinStates;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Initialize the board values to be used by the MiniMax algorithm

\param

\return
*/
/******************************************************************************/
void TicTacToe::InitBoard( void )
{
	//iterate through the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		//iterate through the columns
		for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
		{
			this->Board[ rowIndex ][ colIndex ] = CELL_DEFAULT_VALUE;
		}//end for loop

	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Verifies if the board cell specified by the row and column is already occupied

\param row
the row number
\param col
the column number

\return bool
if true, the cell is already occupied, otherwise false
*/
/******************************************************************************/
bool TicTacToe::IsBoardCellOccupied( const unsigned row, const unsigned col ) const
{
	int cellVal = this->Board[ row ][ col ];

	if ( cellVal != CELL_DEFAULT_VALUE )
	{
		return true;
	}
	else
	{
		return false;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Stores a value in the board cell specified by the row and column

\param row
the row number
\param col
the column number
\param value
the value to be stored in the cell

\return
*/
/******************************************************************************/
void TicTacToe::SetBoardCell( const unsigned row, const unsigned col, const int value )
{
	//store the value in the cell
	this->Board[ row ][ col ] = value;

	/*
	//iterate through the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
	//if the row is found
	if ( row == rowIndex )
	{
	//iterate through the columns
	for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
	{
	//if the column is found
	if ( col == colIndex )
	{
	//store the value in the cell
	this->Board[ rowIndex ][ colIndex ] = value;
	break;
	}
	}//end for loop

	break;
	}

	}//end for loop
	*/
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Finds the next move on the board

\param moveList
the reference to the list of possible moves

\return bool
if true, there is a next move, otherwise false
*/
/******************************************************************************/
bool TicTacToe::FindNextMove( std::vector< MoveCoord > & moveList ) const
{
	bool nextMoveFound = false;

	//iterate through the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		//iterate through the columns
		for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
		{
			//if there is an empty cell
			if ( this->Board[ rowIndex ][ colIndex ] == CELL_DEFAULT_VALUE )
			{
				//add the possible moves to the list based on the current state
				moveList.push_back( MoveCoord( rowIndex, colIndex ) );				
			}
		}//end for loop

	}//end for loop

	if ( moveList.size() > 0 )
	{
		nextMoveFound = true;
	}

	return nextMoveFound;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Checks if all the cells along the row have the same values with the specified value

\param row
the row number
\param value
the value to be compared with

\return bool
if true, all the cells along the row have the same value, otherwise false
*/
/******************************************************************************/
bool TicTacToe::CheckRow( const unsigned row, const int value, const bool checkEmptySpace ) const
{
	bool sameValues = true;

	//iterate through the columns
	for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
	{
		//determine if we bypass the check for the empty spaces
		if ( checkEmptySpace == false && this->Board[ row ][ colIndex ] == CELL_DEFAULT_VALUE )
		{
			continue;
		}

		//validate the cell		
		if ( value != this->Board[ row ][ colIndex ] )
		{				
			sameValues = false;
			break;
		}
	}//end for loop

	return sameValues;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Checks if all the cells along the column have the same values with the specified value

\param column
the column number
\param value
the value to be compared with

\return
if true, all the cells along the column have the same value, otherwise false
*/
/******************************************************************************/
bool TicTacToe::CheckColumn( const unsigned column, const int value, const bool checkEmptySpace ) const
{
	bool sameValues = true;

	//iterate through the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		//determine if we bypass the check for the empty spaces
		if ( checkEmptySpace == false && this->Board[ rowIndex ][ column ] == CELL_DEFAULT_VALUE )
		{
			continue;
		}

		//validate the cell based on the specified column
		if ( value != this->Board[ rowIndex ][ column ] )
		{
			sameValues = false;
			break;
		}
	}//end for loop

	return sameValues;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Checks if all the cells along the diagonal line have the same values with the specified value

\param leftToRight
the flag to determine if we check the diagonal line from left to right if true, otherwise we check from right to left
\param value
the value to be compared with

\return
if true, all the cells along the diagonal have the same value, otherwise false
*/
/******************************************************************************/
bool TicTacToe::CheckDiagonal( const bool leftToRight, const int value, const bool checkEmptySpace ) const
{
	bool sameValues = true;

	unsigned numOfCols = this->NUM_OF_COLS;

	//iterate through the rows
	for ( unsigned rowIndex = 0; rowIndex < this->NUM_OF_ROWS; ++rowIndex )
	{
		//traverse diagonal from left to right
		if ( leftToRight == true )
		{
			//iterate through the columns
			for ( unsigned colIndex = 0; colIndex < this->NUM_OF_COLS; ++colIndex )
			{
				//traverse diagonally
				if ( rowIndex == colIndex )
				{
					//determine if we bypass the check for the empty spaces
					if ( checkEmptySpace == false && this->Board[ rowIndex ][ colIndex ] == CELL_DEFAULT_VALUE )
					{
						continue;
					}

					//validate the cell
					if ( value != this->Board[ rowIndex ][ colIndex ] )
					{
						sameValues = false;
						break;
					}
					break;
				}
			}//end for loop
		}
		//traverse diagonal from right to left
		else
		{
			--numOfCols;

			//determine if we bypass the check for the empty spaces
			if ( checkEmptySpace == false && this->Board[ rowIndex ][ numOfCols ] == CELL_DEFAULT_VALUE )
			{
				continue;
			}

			//validate the cell
			if ( value != this->Board[ rowIndex ][ numOfCols ] )
			{
				sameValues = false;
				break;
			}
		}

	}//end for loop

	return sameValues;
}
