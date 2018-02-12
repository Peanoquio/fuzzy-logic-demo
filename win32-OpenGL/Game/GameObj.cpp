/******************************************************************************/
/*!
\file GameObj.cpp
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

#include "GameObj.h"

namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the GameObject class
	\param
	\return
	*/
	/******************************************************************************/
	GameObject::GameObject( void )
		: m_graphicsObj(),
		m_physicsObj(),
		m_id( 0 ),
		m_type( 0 ),
		m_identifier( 0 ),
		m_activeFlag( true ),
		m_category( NORMAL_CATEGORY ),
		m_index( 0 ),
		m_row( 0 ),
		m_column( 0 ),
		m_moveTile( false ),
		m_moveTileDirection( NONE )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the graphics object
	\param
	\return GraphicsObject
	the graphics object that contains graphic related properties
	*/
	/******************************************************************************/
	GraphicsFramework::GraphicsObject & GameObject::GetGraphicsObj( void )
	{
		return this->m_graphicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the physics object
	\param
	\return PhysicsObject
	the physics object that contains physics related properties
	*/
	/******************************************************************************/
	PhysicsFramework::PhysicsObject & GameObject::GetPhysicsObj( void )
	{
		return this->m_physicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the game object id
	\param
	\return unsigned
	the game object id
	*/
	/******************************************************************************/
	const unsigned GameObject::GetId( void ) const
	{
		return this->m_id;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the game object type
	\param
	\return unsigned
	the game object type
	*/
	/******************************************************************************/
	const unsigned GameObject::GetType( void ) const
	{
		return this->m_type;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the game object identifier
	\param
	\return unsigned
	the game object identifier
	*/
	/******************************************************************************/
	const unsigned GameObject::GetIdentifier( void ) const
	{
		return this->m_identifier;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Indicates if the game object is active
	\param
	\return bool
	the game object active flag
	*/
	/******************************************************************************/
	const bool GameObject::IsActive( void ) const
	{
		return this->m_activeFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the game object category
	\param
	\return GameObjCategory
	the game object category
	*/
	/******************************************************************************/
	const GameObjCategory GameObject::GetCategory( void ) const
	{
		return this->m_category;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the index
	\param
	\return unsigned
	the game object index
	*/
	/******************************************************************************/
	const unsigned GameObject::GetIndex( void ) const
	{
		return this->m_index;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the row
	\param
	\return unsigned
	the game object row
	*/
	/******************************************************************************/
	const unsigned GameObject::GetRow( void ) const
	{
		return this->m_row;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the column
	\param
	\return unsigned
	the game object column
	*/
	/******************************************************************************/
	const unsigned GameObject::GetColumn( void ) const
	{
		return this->m_column;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the grahics object
	\param GraphicsObject
	the graphics object that contains graphics related properties
	\return
	*/
	/******************************************************************************/
	void GameObject::SetGraphicsObj( const GraphicsFramework::GraphicsObject graphicsObj )
	{
		this->m_graphicsObj = graphicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the physics object
	\param PhysicsObject
	the physics object that contains physics related properties
	\return
	*/
	/******************************************************************************/
	void GameObject::SetPhysicsObj( const PhysicsFramework::PhysicsObject physicsObj )
	{
		this->m_physicsObj = physicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object id
	\param unsigned
	the game object id
	\return
	*/
	/******************************************************************************/
	void GameObject::SetId( const unsigned id )
	{
		this->m_id = id;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object type
	\param unsigned
	the game object type
	\return
	*/
	/******************************************************************************/
	void GameObject::SetType( const unsigned type )
	{
		this->m_type = type;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object identifier
	\param unsigned
	the game object identifier
	\return
	*/
	/******************************************************************************/
	void GameObject::SetIdentifier( const unsigned identifier )
	{
		this->m_identifier = identifier;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object active flag
	\param unsigned
	the game object active flag
	\return
	*/
	/******************************************************************************/
	void GameObject::SetActive( const bool activeFlag )
	{
		this->m_activeFlag = activeFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object category
	\param unsigned
	the game object category
	\return
	*/
	/******************************************************************************/
	void GameObject::SetCategory( const GameObjCategory category )
	{
		this->m_category = category;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object index
	\param unsigned
	the game object index
	\return
	*/
	/******************************************************************************/
	void GameObject::SetIndex( const unsigned index )
	{
		this->m_index = index;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object row
	\param unsigned
	the game object row
	\return
	*/
	/******************************************************************************/
	void GameObject::SetRow( const unsigned row )
	{
		this->m_row = row;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the game object column
	\param unsigned
	the game object column
	\return
	*/
	/******************************************************************************/
	void GameObject::SetColumn( const unsigned column )
	{
		this->m_column = column;
	}

} //end namespace GameFramework