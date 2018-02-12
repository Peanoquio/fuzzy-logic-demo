/******************************************************************************/
/*!
\file Board.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #03
\date 13/03/2012
\brief
This is the board class that manages tile related functions

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef BOARD_H
#define BOARD_H
////////////////////////////////////////////////////////////////////////////////

#include "../MyGeometryGM.h"
#include "../Game/GameManager.h"
#include "../TicTacToe/MiniMaxSearch.h"


namespace GameFramework
{
	//forward declaration
	class MyGeometryGM;

	enum TILESPEED
	{
		SLOW = 1,
		FAST = 10,
		TELEPORT = 100
	};

	enum END_GAME_STATE
	{
		NA = 0,
		WIN,
		LOSE,
		DRAW		
	};

	class Board
	{
	public:
		void InitializeTileBoard( const unsigned numOfTilesPerSide, const float boardSideLength );
		void SetTilePosOffset( const float xOffsetValue, const float yOffsetValue );
		void SetTileSizeOffset( const float tileOffsetValue );		
		void CreateTicTacToeGrid( const MyGeometryGame::MyGeometryGM * gameMgrPtr );
		void CreateTicTacToeTiles( const MyGeometryGame::MyGeometryGM * gameMgrPtr );	
		void InactivateTicTacToeTiles( GameFramework::GameObjectVector & gameObjList ) const;
		void SelectAndActivateTicTacToeTilesEvent( GameFramework::GameObjectVector & gameObjList, const float worldX, const float worldY );
		void SetBoardState( const GameFramework::GameObject & gameObj, const TicTacToe::TURN turn );
		void ComputerTicTacToeMove( GameFramework::GameObjectVector & gameObjList );
		bool ValidateEndState( void );

		unsigned int *	m_currTileArrangement;

		float			m_tileSize;

		bool			m_holeReachedTarget;
		bool			m_tileReachedTarget;
		TILESPEED		m_tileSpeed;

		bool			m_lockButtons;
		bool			m_lockTiles;
		bool			m_stopAnimation;

		TicTacToe		m_ticTacToe;
		unsigned int	m_searchDepth;	
		END_GAME_STATE	m_endGameState;

	private:	
		float			m_boardSideLength;
		unsigned		m_numOfTilesPerSide;			
		float			m_tileSizeOffset;

		float			m_xLimit;
		float			m_yLimit;	
		float			m_xOffset;
		float			m_yOffset;

		unsigned		m_maxRow;
		unsigned		m_maxCol;
		unsigned		m_tilesNumber;			
	};

}//end namespace GameFramework

#endif
////////////////////////////////////////////////////////////////////////////////