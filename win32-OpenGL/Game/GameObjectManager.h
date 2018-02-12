/******************************************************************************/
/*!
\file GameObjectManager.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 22/12/2011
\brief
This is the game object manager that will manage the generation of game objects

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H
////////////////////////////////////////////////////////////////////////////////


#include "../Graphics/GraphicsInterface.h"
#include "../Graphics/MeshObj.h"
#include "../GeometryBuilder/BaseGeometryBuilder.h"
#include "GameObj.h"
#include "../Lighting/Material.h"
#include <unordered_map>
#include <string>


namespace GameFramework
{	
	typedef std::unordered_map< const unsigned, GraphicsFramework::BaseGeometryBuilder * > BaseGeometryBuilderMap;
	typedef std::vector< GameFramework::GameObject > GameObjectVector;
	

	class GameObjectManager
	{
	public:		
		GameObjectManager( void );
		~GameObjectManager( void );

		////////////////////////////////////////////////////////////////////////////////
		//pure virtual functions

		virtual void LoadMeshObjects( GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr ) = 0;
		virtual void GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr ) = 0;
		virtual void GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
			const PhysicsFramework::PhysicsObject physicsVal,
			const Light::Material materialVal,
			const GameFramework::GameObjCategory gameObjCategory,
			const bool moveInitialFlag = true ) = 0;
		virtual void GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
			const Math::Vector4 & position,
			const Math::Vector4 & velocity,
			const Math::Vector4 & scale,
			const Math::Vector4 & rotation,			
			const float	movementSpeed = 0.0F,
			const float	rotationalSpeed = 0.0F,
			const float	acceleration = 0.0F,
			const float	mass = 0.0F,
			const bool moveInitialFlag = true,
			const unsigned row = 0,
			const unsigned column = 0, 
			const unsigned index = 0
			) = 0;

		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the game object

		void AddGameObjects( GameObjectVector & gameObjectVector );		
		void AddGameObjects( GameObjectVector & gameObjectVector, const GameObjCategory gameObjCategory );	
		void ClearGameObjects( void );				

		////////////////////////////////////////////////////////////////////////////////	

		////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the graphics properties of the game object

		const GraphicsFramework::BaseGeometryBuilder * const RetrieveBaseGeometryBuilder( const unsigned objectType );
		const BaseGeometryBuilderMap & GetBaseGeometryBuilderMap( void ) const;

		////////////////////////////////////////////////////////////////////////////////
		

	protected:
		////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the game object

		GameObject CreateGameObject( const GraphicsFramework::GraphicsObject & graphicsObj, const PhysicsFramework::PhysicsObject & physicsObj ) const;
		void ContainGameObject( const GameObject gameObj );		

		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the physics properties of the game object

		PhysicsFramework::PhysicsObject CreatePhysicsObject( 
			const Math::Vector4 & position,
			const Math::Vector4 & velocity,
			const Math::Vector4 & scale,
			const Math::Vector4 & rotation,
			const float mass = 0.0F,			
			const float movementSpeed = 0.0F,
			const float rotationalSpeed = 0.0F,
			const float acceleration = 0.0F,
			const bool computeDirectionFlag = true ) const;

		////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the graphics properties of the game object

		void GenerateMesh( const GraphicsFramework::MeshParameterContainer & meshParameterContainer, 
			GraphicsFramework::BaseGeometryBuilder * const baseGeometryBuilder,
			GraphicsFramework::Mesh & mesh ) const;

		GraphicsFramework::GraphicsObject CreateGraphicsObject( const unsigned objectType,
			GraphicsFramework::GraphicsInterface * const graphicsInterface,
			GraphicsFramework::Mesh & mesh ) const;

		GraphicsFramework::GraphicsObject CreateGraphicsObject( const unsigned objectType,
			GraphicsFramework::GraphicsInterface * const graphicsInterface,
			GraphicsFramework::Mesh & mesh,
			const char * envTextureName,
			const char ** textureName, const unsigned arrSize = 0 
			 ) const;

		void ContainBaseGeometryBuilder( const unsigned objectType, GraphicsFramework::BaseGeometryBuilder * const baseGeometryBuilder );			
		
		////////////////////////////////////////////////////////////////////////////////
		//these functions deal with creating texture objects

		void LoadImageFromFile( GraphicsFramework::ImageObj & imageObj, const char * textureName, const char* filename ) const;
		void LoadTextureImage( GraphicsFramework::GraphicsInterface * const graphicsInterface,
			const char * textureName, const char* filename ) const;
		void LoadCubeMapImages( GraphicsFramework::GraphicsInterface * const graphicsInterface, const char * cubeMapName, 
			const char * rightTextureName, const char* rightImgFilename,
			const char * leftTextureName, const char* leftImgFilename,
			const char * topTextureName, const char* topImgFilename,
			const char * bottomTextureName, const char* bottomImgFilename,
			const char * frontTextureName, const char* frontImgFilename,
			const char * backTextureName, const char* backImgFilename
			) const;
		void LoadDualParaboloidImages( GraphicsFramework::GraphicsInterface * const graphicsInterface,
			const char * frontTextureName, const char* frontImgFilename,
			const char * backTextureName, const char* backImgFilename
			) const;

	private:
		GameObjectVector		m_gameObjVector;
		BaseGeometryBuilderMap	m_baseGeometryBuilderMap;		

		//make the copy constructor private
		GameObjectManager( const GameObjectManager & gameObjectManager );
		//make the assignment operator private
		GameObjectManager & operator=( const GameObjectManager & gameObjectManager );
	};

} //end namespace GameFramework

#endif
////////////////////////////////////////////////////////////////////////////////