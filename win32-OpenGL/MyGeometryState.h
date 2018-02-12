/******************************************************************************/
/*!
\file MyGeometryState.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150 / CS380
\par Project #01
\date 08/02/2012
\brief
This is the geometry game state

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef MYGEOMETRY_STATE_H
#define MYGEOMETRY_STATE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "Game\GameState.h"
#include "Game\GameObjectManager.h"
#include "FrameRate\FrameRateController.h"
#include "Puzzle\NPuzzle.h"
#include "FuzzyLogic\MissileGameDriver.h"


namespace
{
	const float CAMERA_DISTANCE_FROM_NEAR_PLANE = 7.0F;
}


namespace MyGeometryGame
{
	enum TILESPEED
	{
		SLOW = 1,
		FAST = 10,
		TELEPORT = 100
	};

	struct MyBoard
	{
		float			m_boardSideLength;
		unsigned		m_numOfTilesPerSide;
		float			m_tileSize;	

		float			m_xLimit;
		float			m_yLimit;	

		unsigned		m_maxRow;
		unsigned		m_maxCol;
		unsigned		m_tilesNumber;	

		unsigned int *	m_currTileArrangement;

		bool			m_holeReachedTarget;
		bool			m_tileReachedTarget;
		TILESPEED		m_tileSpeed;

		bool			m_lockButtons;
		bool			m_lockTiles;
		bool			m_stopAnimation;
	};


	//forward declare
	class MyGeometryGM;

	class MyGeometryState : public GameFramework::GameState
	{
	public:
		MyGeometryState( const std::string & stateName, MyGeometryGM & parentGM );
		~MyGeometryState( void );

		virtual void Init( void );
		virtual void Update( float startTime, float dt = 0.0F );
		virtual void Shutdown( void );	

	private:
		MyGeometryGM&						m_parentGM;
		GameFramework::GameObjectVector		m_currGameObjList;	
		GameFramework::GameObjectVector		m_lightedGameObjList;
		GameFramework::GameObjectVector		m_lightSourceGameObjList;
		GameFramework::GameObjectVector		m_reflectiveGameObjList;	
		GameFramework::GameObjectVector		m_refractiveGameObjList;
		GameFramework::GameObjectVector		m_refractiveChromDispGameObjList;
		GameFramework::GameObjectVector		m_fresnelGameObjList;

		FrameRate::FrameRateController		m_timer;
		MyBoard								m_board;		
		NPuzzle	*							m_nPuzzle;
		MissileGame							m_missileGame;

		void InitMissileGameZones( void );
		void InitMissile( void );
		void InitPlane( void );

		void InitObjects( void );
		void InitLightedObjects( void );
		void InitLightSourceObjects( void );
		void InitReflectiveObjects( void );
		void InitRefractiveObjects( void );
		void InitRefractiveChromDispObjects( void );
		void InitFresnelObjects( void );

		void UpdateBehavior( float dt );
		void UpdateCollision( float startTime, float dt );
		void UpdateScene( float dt );

		void UpdateBehavior( float dt, GameFramework::GameObjectVector & gameObjVec );

		void DrawMain( float dt );
		void DrawObjects( float dt );

		void DrawStencil( float dt );
		void DrawReflection( float dt );
		void DrawTextToScreen( float dt );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		void ShowNormal( GameFramework::GameObject & gameObj ) const;
		void InactivateOutOfBoundsObj( GameFramework::GameObject & gameObj );

		void ActivateReflection( void );
		void DeactivateReflection( void );

		////////////////////////////////////////////////////////////////////////////////
		//helper functions for the N puzzle
		bool AreTilesAdjacent( const GameFramework::GameObject * emptyTile, const GameFramework::GameObject & blockTile ) const;
		void SwapPositions( GameFramework::GameObject * emptyTile, GameFramework::GameObject & blockTile, const TILESPEED tileSpeed );
		
		void InitializeTileBoard( const unsigned numOfTilesPerSide, const float boardSideLength );
		void CreateTiles( void );
		void ArrangeTiles( const unsigned int * tileArrangementData );
		void PlotTiles( void );
		void AnimateTiles( float dt, GameFramework::GameObject& gameObj );
		void ResetTiles( void );
		void GenerateRandomTiles( void );
		void RandomizeTiles( void );
		bool IsTileExisting( const unsigned int tileNumber ) const;
		
		bool ValidateTargetPosition( GameFramework::GameObject & gameObj );

		////////////////////////////////////////////////////////////////////////////////

		//make the copy constructor private
		MyGeometryState( const MyGeometryState & myGeometryState );
		//make the assignment operator private
		MyGeometryState & operator=( const MyGeometryState & myGeometryState );		
	};

} //end namespace MyGeometryGame


#endif
////////////////////////////////////////////////////////////////////////////////