/******************************************************************************/
/*!
\file MiniMaxSearch.h
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


#ifndef _MINIMAXSEARCH_H_
#define _MINIMAXSEARCH_H_

#define MIN_VALUE		-9
#define MAX_VALUE		9
#define NEG_INFINITY	-999
#define INFINITY		999


#include <vector>


struct MoveCoord
{
	MoveCoord( const unsigned row, const unsigned col );

	unsigned m_row;
	unsigned m_col;
};


class TicTacToe
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	static const int		CELL_DEFAULT_VALUE = -1;
	static const unsigned	NUM_OF_ROWS = 3;
	static const unsigned	NUM_OF_COLS = 3;

	int						Board[NUM_OF_ROWS][NUM_OF_COLS];
	
	int			m_currentDepth;
	unsigned	m_nextMoveRow;
	unsigned	m_nextMoveCol;	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//MiniMax
	void Place( int row, int column, int turn );
	void UnPlace( int row, int column, int turn );

	//helper functions
	bool CheckRow( const unsigned row, const int value, const bool checkEmptySpace = true ) const;
	bool CheckColumn( const unsigned column, const int value, const bool checkEmptySpace = true ) const;
	bool CheckDiagonal( const bool leftToRight, const int value, const bool checkEmptySpace = true ) const;
	bool FindNextMove( std::vector< MoveCoord > & moveList ) const;	
	int CountPossibleWinStates( const int value ) const;

public:
	enum TURN
	{
		PLAYER = 0,
		COMPUTER
	};

	TURN m_currentTurn;

	TicTacToe( void );
	~TicTacToe( void ); 
	
	bool WinTest();
	bool LooseTest();
	bool DrawTest();
	
	//MiniMax
	bool MiniMax( unsigned int depth = 9 );
	int X( int r, int c, int depth, int alpha, int beta );
	int O( int r, int c, int depth, int alpha, int beta );
	bool TerminalTest( int & terminalValue, int depth );
	int EvaluationTest();

	//helper functions
	void InitBoard( void );	
	bool IsBoardCellOccupied( const unsigned row, const unsigned col ) const;
	//getters
	void GetNextMove( unsigned & row, unsigned & col ) const;
	//setters
	void SetBoardCell( const unsigned row, const unsigned column, const int value );
};

#endif