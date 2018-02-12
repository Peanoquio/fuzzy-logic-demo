/******************************************************************************/
/*!
\file GameManager.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 21/12/2011
\brief
This is a base class game manager that manages the different game states that is structured like a linked list
This was researched through the site: http://gamedevgeek.com/tutorials/managing-game-states-in-c/
This was also referenced from the previous Advanced Certificate for Game Programmers class

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "GameManager.h"
#include "../Game/GameState.h"
#include "../ErrorHandling/MessageBox.h"
#include <cassert>


namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the GameManager class
	\param
	\return
	*/
	/******************************************************************************/
	GameManager::GameManager( void )
		: m_current( 0 ),
		m_initial( 0 ),
		m_prev( 0 ),
		m_next( 0 ),
		m_quit( false ),
		m_restartState( false )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the GameManager class
	\param
	\return
	*/
	/******************************************************************************/
	GameManager::~GameManager( void )
	{
		//Get beginning and end iterators of the hash map
		StateMapItor itor = this->m_gameStates.begin();
		StateMapItor end  = this->m_gameStates.end();

		//loop through map
		while ( itor != end )
		{
			//delete the pointer to the GameState
			delete itor->second;
			itor->second = 0;
			//traverse to the next element in the iterator
			++itor;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the initial state
	\param
	\return
	*/
	/******************************************************************************/
	GameState* GameManager::GetInitialState( void )
	{
		return this->m_initial;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Change the state
	\param
	\return
	*/
	/******************************************************************************/
	GameState* GameManager::ChangeState( void )
	{
		//store the current state as the previous state so we can revert back
		this->m_prev = this->m_current;
		//set the next state as the new current state
		this->m_current = this->m_next;

		return this->m_current;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the initial state based on the state ID being passed
	\param stateID
	the stateID that identifies the game state
	\return
	*/
	/******************************************************************************/
	void GameManager::SetInitialState( const std::string& stateID )
	{
		//find the state in the map based on the stateID
		StateMapItor itor = this->m_gameStates.find( stateID );

		//validate if the state requested exists
		ASSERT( itor == this->m_gameStates.end(), 
			"Trying to set an initial state that doesn't exist!" );

		//set the game state pointers to the requested game state from the map
		this->m_initial = itor->second;
		this->m_current = itor->second;
		this->m_prev = itor->second;
		this->m_next = itor->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Adds a game state
	\param state
	the pointer to the game state to be added
	\return
	*/
	/******************************************************************************/
	void GameManager::AddState( GameState* state )
	{
		//validate that the state is not null
		ASSERT( state == NULL, 
			"Adding a gamestate that is NULL" );

		//cache the name of this state
		const std::string& stateName = state->GetStateName();

		//validate if this state is already existing in the map
		StateMapItor itor = this->m_gameStates.find( stateName );
		ASSERT( itor != this->m_gameStates.end(), 
			"Trying to add a gamestate that already exists" );

		//add the game state to the map
		this->m_gameStates.insert( std::make_pair( stateName, state ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set quit flag of the game manager 
	\param quit
	the quit flag of the game manager
	\return
	*/
	/******************************************************************************/
	void GameManager::SetQuit( bool quit )
	{
		this->m_quit = quit;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set restart flag of the game manager
	\param restart
	the restart flag of the game manager
	\return
	*/
	/******************************************************************************/
	void GameManager::SetRestartState( bool restart )
	{
		this->m_restartState = restart;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the next state based on the state ID being passed
	\param restart
	the restart flag of the game manager
	\return
	*/
	/******************************************************************************/
	void GameManager::SetNextState( const std::string& stateID )
	{
		//find the state in the map based on the stateID
		StateMapItor itor = this->m_gameStates.find( stateID );

		//validate if the state requested exists
		ASSERT( itor == this->m_gameStates.end(), 
			"Trying to set a state that doesn't exist" );

		//set the next state pointer to the requested game state from the map
		this->m_next = itor->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the quit flag boolean value
	\param
	\return bool
	the quit flag: if true, quit requested, otherwise false
	*/
	/******************************************************************************/
	bool GameManager::QuitRequested( void ) const
	{
		return this->m_quit;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the restart flag boolean value
	\param
	\return bool
	the restart flag: if true, restart requested, otherwise false
	*/
	/******************************************************************************/
	bool GameManager::RestartStateRequested( void ) const
	{
		return this->m_restartState;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the restart flag boolean value
	There is a change of stateif either of the following conditions have been satisfied
	1. the current state is not equal to the next state
	2. quit has been requested
	3. restart state has been requested
	\param
	\return bool
	if true, change of state has been requested, otherwise false
	*/
	/******************************************************************************/
	bool GameManager::ChangeStateRequested( void ) const
	{
		//there is a change of state if either of the following conditions have been satisfied
		//1. the current state is not equal to the next state
		//2. quit has been requested
		//3. restart state has been requested
		return ( ( this->m_current != this->m_next ) || this->m_quit || this->m_restartState );
	}
	

} //end namespace GameFramework