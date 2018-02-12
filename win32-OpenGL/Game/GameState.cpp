/******************************************************************************/
/*!
\file GameState.cpp
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

#include "GameState.h"

namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the GameState class
	\param stateName
	the name of the game state
	\return
	*/
	/******************************************************************************/
	GameState::GameState( const std::string& stateName )
		:m_stateName( stateName )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the GameState class
	\param
	\return
	*/
	/******************************************************************************/
	GameState::~GameState(void)
	{
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the name of the game state
	\param
	\return std::string&
	the name of the game state
	*/
	/******************************************************************************/
	const std::string& GameState::GetStateName(void) const
	{
		return m_stateName;
	}

} //end namespace GameFramework