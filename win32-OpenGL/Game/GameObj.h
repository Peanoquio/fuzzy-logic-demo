/******************************************************************************/
/*!
\file GameObj.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 19/12/2011
\brief
This is the game object that will contain game related properties

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef GAMEOBJ_H
#define GAMEOBJ_H
////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include "../Graphics/GraphicsObj.h"
#include "../Physics/PhysicsObj.h"

namespace GameFramework
{
	enum MoveTileDirection
	{
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT
	};


	enum GameObjCategory
	{
		NORMAL_CATEGORY,
		LIGHTED_CATEGORY,
		LIGHT_SOURCE_CATEGORY,
		REFLECTIVE_CATEGORY,
		REFRACTIVE_CATEGORY,
		REFRACTIVE_CD_CATEGORY,
		FRESNEL_CATEGORY,
		PROJECTED_CATEGORY		
	};


	class GameObject
	{
	public:
		GameObject( void );

		GraphicsFramework::GraphicsObject &			GetGraphicsObj( void );
		PhysicsFramework::PhysicsObject &			GetPhysicsObj( void );
		const unsigned								GetId( void ) const;		
		const unsigned								GetType( void ) const;
		const unsigned								GetIdentifier( void ) const;
		const bool									IsActive( void ) const;
		const GameObjCategory						GetCategory( void ) const;

		const unsigned								GetIndex( void ) const;
		const unsigned								GetRow( void ) const;
		const unsigned								GetColumn( void ) const;

		void									SetGraphicsObj( const GraphicsFramework::GraphicsObject graphicsObj );
		void									SetPhysicsObj( const PhysicsFramework::PhysicsObject physicsObj );
		void									SetId( const unsigned id );		
		void									SetType( const unsigned type );
		void									SetIdentifier( const unsigned identifier );
		void									SetActive( const bool activeFlag );
		void									SetCategory( const GameObjCategory category );

		void									SetIndex( const unsigned index );
		void									SetRow( const unsigned row );
		void									SetColumn( const unsigned column );

		float								m_targetXpos;
		float								m_targetYpos;
		bool								m_moveTile;
		MoveTileDirection					m_moveTileDirection;

	private:
		GraphicsFramework::GraphicsObject	m_graphicsObj;
		PhysicsFramework::PhysicsObject		m_physicsObj;
		unsigned							m_id;
		unsigned							m_type;
		unsigned							m_identifier;
		bool								m_activeFlag;
		GameObjCategory						m_category;

		unsigned							m_index;
		unsigned							m_row;
		unsigned							m_column;			
	};

} //end namespace GameFramework

#endif
////////////////////////////////////////////////////////////////////////////////