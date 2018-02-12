/******************************************************************************/
/*!
\file GameManager.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <hash_map>

namespace GameFramework
{
	//forward declare
	class GameState;

	class GameManager
	{
	public:
		GameManager( void );
		~GameManager( void );

		//Application will use these
		GameState*	GetInitialState( void );
		GameState*	ChangeState( void );
		void		SetInitialState( const std::string& stateID );
		void		AddState( GameState* state );

		//GameStates will use these
		void		SetQuit( bool quit );
		void		SetRestartState( bool restart );
		void		SetNextState( const std::string& stateID );

		//Application will check these
		bool		QuitRequested( void ) const;
		bool		RestartStateRequested (void ) const;
		bool		ChangeStateRequested( void ) const;

	private:
		//the map will contain pointer to GameStates identified by its string name as the key
		typedef stdext::hash_map< std::string, GameState* >	StateMap;
		typedef StateMap::iterator							StateMapItor;

		GameState*	m_current;
		GameState*	m_initial;
		GameState*	m_prev;
		GameState*	m_next;
		StateMap	m_gameStates;
		bool		m_quit;
		bool		m_restartState;

		//make the copy constructor private
		GameManager( const GameManager & gameManager );
		//make the assignment operator private
		GameManager & operator=( const GameManager & gameManager );
	};

} //end namespace GameFramework

#endif
////////////////////////////////////////////////////////////////////////////////