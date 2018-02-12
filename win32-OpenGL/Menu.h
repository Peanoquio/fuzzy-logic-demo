/******************************************************************************/
/*!
\file Menu.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 25/12/2011
\brief
This is the menu state

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef MENU_STATE_H
#define MENU_STATE_H
////////////////////////////////////////////////////////////////////////////////

#include "Game\GameState.h"
#include "MyGeometryGM.h"
#include <string>
#include <vector>


namespace MyGeometryGame
{
	class MenuState : public GameFramework::GameState
	{
	public:
		enum MenuType
		{
			MT_PUZZLE2X2,
			MT_PUZZLE3X3,
			MT_PUZZLE4X4,
			MT_QUIT
		};

		MenuState( const std::string& stateName, MyGeometryGM & parentGM );
		~MenuState( void );

		void Init( void );
		void Update( float startTime, float dt = 0.0F );
		void Shutdown( void );	

	private:		
		void UpdateBehavior( float dt );

		void DrawMain( float dt );
		void DrawObjects( float dt );
		void DrawTextToScreen( void );
		void RenderObject( GameFramework::GameObject & gameObj ) const;
		const Math::Mtx44 GetObjectTransformation( GameFramework::GameObject & gameObj ) const;

		MyGeometryGM&						m_parentGM;
		GameFramework::GameObjectVector		m_currGameObjList;
		std::vector<std::string>			m_menuOptions;
		unsigned							m_currentMenuItem;

		MenuState& operator=( const MenuState& );
	};
}// namespace MyGeometryGame

#endif
////////////////////////////////////////////////////////////////////////////////