/******************************************************************************/
/*!
\file MissileGameDriver.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #04
\date 29/03/2012
\brief
This is the driver for the missile game

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "FuzzyLogicMissile.h"
#include "../Graphics/GraphicsInterface.h"

namespace
{
	const int CITYNUMBER = 5;
	const float DEFAULT_STARTING_DAMAGE = 50.0F;
	const float DEFAULT_DAMAGE_OUTSIDE_CITY = 10.0F;
	const float DEFAULT_STARTING_FUEL = 100.0F;
	const float FUEL_CONSUMPTION_RATE = 0.01F;
	const float MAX_RADIUS = 100.0F;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the City struct

\param 

\return
*/
/******************************************************************************/
struct City
{
	City( void );
	float	radius;
	Point2D position;
	float	damage;
	int		red;
	int		green;
	int		blue;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the MissileGame struct

\param 

\return
*/
/******************************************************************************/
struct MissileGame
{
	MissileGame( void );
	void ReadDamageValue( void );
	void ConsumeFuel( void );
	void InitGame( void );

	City				m_cities[CITYNUMBER];
	Missile				m_missile;
	Plane				m_plane;
	FuzzyLogic_Missile	m_fuzzyLogicMissile;

	//added by Oliver Chong - April 4, 2012
	std::list< Point2D > m_ptList;
	float m_missileLaunchAngle;
	bool m_launchMissile;	
	bool m_setMissileDirection;	

	bool CheckGameStatus( const GraphicsFramework::GraphicsInterface * gfx );
	void ShowZoneDamage( GraphicsFramework::GraphicsInterface * gfx );
	void DrawMissileLaunchPosition( GraphicsFramework::GraphicsInterface * gfx, const float xScreenPos, const float yScreenPos ) const;
	void DrawMissileLaunchDirection( void );
	void DrawMissilePath( void );	
};