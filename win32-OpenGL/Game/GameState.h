/******************************************************************************/
/*!
\file GameState.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 21/12/2011
\brief
This is a base class game state for levels, menus, etc.
This was researched through the site: http://gamedevgeek.com/tutorials/managing-game-states-in-c/
This was also referenced from the previous Advanced Certificate for Game Programmers class

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef GAME_STATE_H
#define GAME_STATE_H
////////////////////////////////////////////////////////////////////////////////

#include <string>

namespace GameFramework
{
	class GameState
	{
	public:
		GameState( const std::string & stateName );
		virtual ~GameState( void );

		virtual void Init( void )									= 0;
		virtual void Update( float startTime, float dt = 0.0F )		= 0;
		virtual void Shutdown( void )								= 0;

		const std::string& GetStateName( void ) const;

	private:
		std::string m_stateName;

		//make the copy constructor private
		GameState( const GameState & gameState );
		//make the assignment operator private
		GameState & operator=( const GameState & gameState );
	};

} //end namespace GameFramework

#endif
////////////////////////////////////////////////////////////////////////////////