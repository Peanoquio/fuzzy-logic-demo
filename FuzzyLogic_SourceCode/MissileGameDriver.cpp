/******************************************************************************/
/*!
\file MissileGameDriver.cpp
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

//headers
#include "MissileGameDriver.h"

#include <iostream>
#include <iomanip>


#include "../ErrorHandling/MessageBox.h"

#include <sstream> // std::wstringstream
#if defined(UNICODE)
typedef std::wstringstream StringStream_t;
#else
typedef std::stringstream SringStream_t;
#endif // UNICODE




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the City struct

\param 

\return
*/
/******************************************************************************/
City::City( void )
	: red( 255 ), blue( 255 ), green( 255 )
{
	this->radius = 1.0f; 
	this->position = Point2D(); 
	this->damage = DEFAULT_STARTING_DAMAGE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the MissileGame struct

\param 

\return
*/
/******************************************************************************/
MissileGame::MissileGame( void )
	: m_missile(), m_plane(), 
	m_fuzzyLogicMissile( DEFAULT_STARTING_FUEL ),
	m_missileLaunchAngle( 0.0F ),
	m_launchMissile( false ),
	m_setMissileDirection( false )	
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This checks if the game ends either by:
the plane being hit by the missile
or the missile fuel being empty

\param gfx
the pointer to the graphics interface

\return bool
if true, the game is over, otherwise false
*/
/******************************************************************************/
bool MissileGame::CheckGameStatus( const GraphicsFramework::GraphicsInterface * gfx )
{
	bool gameOver = false;

	StringStream_t message;

	//hit target test
	float px = this->m_plane.m_position.x - this->m_missile.m_position.x;
	float py = this->m_plane.m_position.y - this->m_missile.m_position.y;
	float dist = std::sqrtf( px * px + py * py );

	//validate if plane is hit
	if ( dist < this->m_plane.m_radius )
	{
		message << "FAIL... Plane Hit!" << std::endl;
		gameOver = true;
	}

	//validate if fuel is empty
	if ( this->m_fuzzyLogicMissile.GetFuelValue() <= 0.0F ) 
	{
		message << "WIN!!! You're an ace pilot!" << std::endl;
		gameOver = true;
	}

	if ( gameOver == true )
	{
		//display status message
		MessageBox( gfx->GetWindowHandle(), 
			message.str().c_str(), (LPCWSTR)L"GAME STATUS", MB_OK );

		//restart the game
		this->InitGame();
	}

	return gameOver;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Displays the damage value for each zone

\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void MissileGame::ShowZoneDamage( GraphicsFramework::GraphicsInterface * gfx )
{
	std::stringstream ss;

	//loop through the zones
	for ( unsigned index = 0; index < CITYNUMBER; ++index )
	{
		ss.str("");
		ss << this->m_cities[index].damage,	
			gfx->PrintText( ss.str().c_str(), 
			this->m_cities[index].position.x, 
			this->m_cities[index].position.y + ( this->m_cities[index].radius / 2 ), 
			GraphicsFramework::TS_WORLD );	
	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Displays the damage value for each zone

\param gfx
the pointer to the graphics interface
\param xScreenPos
the x position in screen coordinates
\param yScreenPos
the y position in screen coordinates

\return
*/
/******************************************************************************/
void MissileGame::DrawMissileLaunchPosition( GraphicsFramework::GraphicsInterface * gfx, const float xScreenPos, const float yScreenPos ) const
{
	float worldX = gfx->GetWorldX();
	float worldY = gfx->GetWorldY();			

	//convert screen to world coordinates
	gfx->ConvertScreenToWorld( xScreenPos, yScreenPos, worldX, worldY );	
	worldY *= -1.0f;

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "worldX : " << worldX << " worldY : " << worldY << std::endl;

	glBegin( GL_POINTS );
		glVertex3f( worldX, worldY, 1.0F );
	glEnd();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Displays the missile launch direction

\param

\return
*/
/******************************************************************************/
void MissileGame::DrawMissileLaunchDirection( void )
{
	const float cosVal = std::cosf( DegreeToRadian( this->m_missileLaunchAngle ) );
	const float sinVal = std::sinf( DegreeToRadian( this->m_missileLaunchAngle ) );

	this->m_missile.m_direction.x = cosVal;
	this->m_missile.m_direction.y = sinVal;	
				
	//the rotation matrix approach is used so the rotation will be with respect to the direction of the missile
	//this->m_missile.m_direction.x = ( cosVal * this->m_missile.m_direction.x ) + ( -sinVal * this->m_missile.m_direction.y );
	//this->m_missile.m_direction.y = ( sinVal * this->m_missile.m_direction.x ) + ( cosVal * this->m_missile.m_direction.y );
								
	//normalize the direction
	this->m_missile.m_direction = NormalizeVector( this->m_missile.m_direction );	

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "missile launch angle : " << this->m_missileLaunchAngle << std::endl;
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "missile direction : " << this->m_missile.m_direction.x << " , " << this->m_missileGame.m_missile.m_direction.y << std::endl;

	glBegin( GL_LINES );		
		glVertex3f( this->m_missile.m_position.x, this->m_missile.m_position.y, 1.0F );					
		glVertex3f( this->m_missile.m_position.x + this->m_missile.m_direction.x, 
			this->m_missile.m_position.y + this->m_missile.m_direction.y, 1.0F );					
	glEnd();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Displays the missile movement path

\param

\return
*/
/******************************************************************************/
void MissileGame::DrawMissilePath( void )
{
	//draw the missile path
	this->m_ptList.push_back( this->m_missile.m_position );	

	std::list< Point2D >::const_iterator itor = this->m_ptList.begin();
	std::list< Point2D >::const_iterator end = this->m_ptList.end();

	glBegin( GL_LINE_STRIP );
		while ( itor != end )
		{
			glVertex3f( itor->x, itor->y, 1.0F );
			++itor;
		}//end while loop
	glEnd();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function reads and updates the damage value once the plane enter the city

\param 

\return
*/
/******************************************************************************/
void MissileGame::ReadDamageValue( void )
{
	//the default damage value outside any city
	float dm = DEFAULT_DAMAGE_OUTSIDE_CITY;
	//calculate dm using the position of the plane in an area
	float dist = 0.0f;

	for ( int i = 0; i < CITYNUMBER; i++ )
	{
		//compute for the distance between the city and the plane
		float dx = this->m_cities[i].position.x - this->m_plane.m_position.x;
		float dy = this->m_cities[i].position.y - this->m_plane.m_position.y;
        dist = std::sqrtf( dx * dx + dy * dy );

		//validate if the plane is within the city
		if ( dist < ( ( this->m_cities[i].radius + this->m_plane.m_radius ) / 2.0F ) )
		{
			//get the potential damage dealt to the city
			dm = this->m_cities[i].damage;

			/*
			std::cout << std::setfill (' ') << std::setw( 0 ) << "///////////////////////////////////////////////////" << std::endl;
			std::cout << std::setfill (' ') << std::setw( 0 ) << "city " << i <<  " damage : " << dm << std::endl;
			std::cout << std::setfill (' ') << std::setw( 0 ) << "city pos : " << this->m_cities[i].position.x << " , " << this->m_cities[i].position.y << std::endl;
			std::cout << std::setfill (' ') << std::setw( 0 ) << "plane pos : " << this->m_plane.m_position.x << " , " << this->m_plane.m_position.y << std::endl;
			std::cout << std::setfill (' ') << std::setw( 0 ) << "city radius : " << this->m_cities[i].radius << " plane radius : " <<  this->m_plane.m_radius << std::endl;
			std::cout << std::setfill (' ') << std::setw( 0 ) << "dist : " << dist << " check city plane radius : " << this->m_cities[i].radius + this->m_plane.m_radius << std::endl;
			*/

			break;
		}
	}//end for loop

	//update the damage value
	this->m_fuzzyLogicMissile.SetCorrectedDamageValue( dm );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function graudally consumes the fuel everytime it is invoked

\param 

\return
*/
/******************************************************************************/
void MissileGame::ConsumeFuel( void )
{
	float newFuelValue = this->m_fuzzyLogicMissile.GetFuelValue() - FUEL_CONSUMPTION_RATE;
	this->m_fuzzyLogicMissile.SetFuelValue( newFuelValue );	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This initializes the missile game

\param 

\return
*/
/******************************************************************************/
void MissileGame::InitGame( void )
{
	//reset the fuzzy set values
	this->m_fuzzyLogicMissile.SetFuelValue( DEFAULT_STARTING_FUEL );
	this->m_fuzzyLogicMissile.SetDamageValue( DEFAULT_STARTING_DAMAGE );
	this->m_fuzzyLogicMissile.SetAttackValue( 0.0F );

	//reset the missile launch
	this->m_missileLaunchAngle = 0.0F;
	this->m_launchMissile = false;
	this->m_setMissileDirection = false;	

	//clear the missile path
	this->m_ptList.clear();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	this->m_missile.m_position.x = 70.0F;
	this->m_missile.m_position.y = 70.0F;
	//this->m_missile.m_speed = 1.9F;
	this->m_missile.m_speed = 1.0F;
	this->m_missile.m_direction.x = 1.0F;
	this->m_missile.m_direction.y = 0.0F;
	this->m_missile.m_direction = NormalizeVector( this->m_missile.m_direction );

	this->m_plane.m_radius = PLANE_RADIUS;
	this->m_plane.m_position.x = 170.0F;
	this->m_plane.m_position.y = 400.0F;
	//this->m_plane.m_speed = 1.8F;
	this->m_plane.m_speed = 0.9F;
	this->m_plane.m_direction.x = 1.5F;
	this->m_plane.m_direction.y = -1.0F;
	this->m_plane.m_direction = NormalizeVector( this->m_plane.m_direction );
	
    //cities
	this->m_cities[0].radius = 60.0f;
	this->m_cities[0].damage = 50.0f;
	this->m_cities[0].position.x = 110;
	this->m_cities[0].position.y = 110;
	this->m_cities[0].red = 255;
	this->m_cities[0].green = 128;
	this->m_cities[0].blue = 128;

	this->m_cities[1].radius = 100.0F;
	this->m_cities[1].damage = 90.0f;
	this->m_cities[1].position.x = 300;
	this->m_cities[1].position.y = 200;
	this->m_cities[1].red = 255;
	this->m_cities[1].green = 8;
	this->m_cities[1].blue = 8;

	this->m_cities[2].radius = 60.0f;
	this->m_cities[2].damage = 45.0f;
	this->m_cities[2].position.x = 500;
	this->m_cities[2].position.y = 90;
	this->m_cities[2].red = 255;
	this->m_cities[2].green = 160;
	this->m_cities[2].blue = 160;

	this->m_cities[3].radius = 90.0f;
	this->m_cities[3].damage = 75.0f;
	this->m_cities[3].position.x = 495;
	this->m_cities[3].position.y = 350;
	this->m_cities[3].red = 255;
	this->m_cities[3].green = 55;
	this->m_cities[3].blue = 55;

	this->m_cities[4].radius = 44.0f;
	this->m_cities[4].damage = 83.0f;
	this->m_cities[4].position.x = 99;
	this->m_cities[4].position.y = 300;
	this->m_cities[4].red = 255;
	this->m_cities[4].green = 25;
	this->m_cities[4].blue = 25;
}