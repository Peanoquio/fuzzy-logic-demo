/******************************************************************************/
/*!
\file MyGeometryState.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150 / CS380
\par Project #01
\date 08/02/2012
\brief
This is the geometry game state

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "MyGeometryState.h"
#include "MyGeometryGM.h"
#include "MyGeometryOM.h"
#include "Physics\CollisionDetection.h"
#include "Utility\Utility.h"

#include "Effects\NoEffect.h"
#include "Effects\LightingEffect.h"
#include "Effects\ReflectiveEffect.h"
#include "Effects\RefractiveEffect.h"
#include "Effects\FresnelEffect.h"
#include "Effects\RefractiveChromDispEffect.h"
#include "Effects\DualParaboloidEffect.h"
#include "Effects\DualParaboloidReflectiveEffect.h"

#include <iostream>
#include <iomanip>


namespace
{
	const unsigned START_SIZE = 100;
	const unsigned SPEED_DAMP = 100;
	const float LOOKAT_DAMP = 5.0F;
}


namespace MyGeometryGame
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the MyGeometryState class
	\param stateName
	the name of the game state
	\param parentGM
	the parent game manager of this state
	\return
	*/
	/******************************************************************************/
	MyGeometryState::MyGeometryState( const std::string & stateName, MyGeometryGM & parentGM )
		: GameFramework::GameState( stateName ),
		m_parentGM( parentGM ),
		m_currGameObjList(),
		m_lightedGameObjList(),
		m_lightSourceGameObjList(),
		m_reflectiveGameObjList(),
		m_refractiveGameObjList(),
		m_refractiveChromDispGameObjList(),
		m_fresnelGameObjList(),
		m_nPuzzle( 0 ),
		m_board(),
		m_timer()		
	{
		//allocate the initial capacity
		m_currGameObjList.reserve( START_SIZE );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the MyGeometryState class
	\param
	\return
	*/
	/******************************************************************************/
	MyGeometryState::~MyGeometryState( void )
	{
		this->Shutdown();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the plane for the missile game
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitPlane( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		float xWorldPt = 0.0F;
		float yWorldPt = 0.0F;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set and store the radius
		this->m_missileGame.m_plane.m_radius = this->m_missileGame.m_plane.m_radius * WORLD_SCALE;
		float planeRadius = this->m_missileGame.m_plane.m_radius;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Point2D planePos = this->m_missileGame.m_plane.m_position;
		float planePosX = planePos.x;
		float planePosY = planePos.y;

		//convert screen to world coordinates
		this->m_parentGM.m_graphicsInterfacePtr->ConvertScreenToWorld( planePosX, planePosY, xWorldPt, yWorldPt );
		//replace the plane screen coordinates with the world coordinates
		this->m_missileGame.m_plane.m_position.x = xWorldPt;
		this->m_missileGame.m_plane.m_position.y = yWorldPt;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//initialize the light position
		Math::Vector4 position( xWorldPt, yWorldPt, 1.0F, 1.0F );
		this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( position );
		this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( position );
		this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( position );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		unsigned int gameObjIdentifier = MyGeometryGame::LIGHT_SOURCE_GAMEOBJ;
		unsigned int objType = MyGeometryGame::SPHERE2_OBJTYPE;
		GameFramework::GameObjCategory gameObjCategory = GameFramework::LIGHT_SOURCE_CATEGORY; 
		GameFramework::GameObjectVector * gameObjVec = &this->m_lightedGameObjList;

		physicsObj.SetPosition( position );	
		physicsObj.SetScale( Math::Vector4( planeRadius, planeRadius, planeRadius, 0.0F ) );

		Math::Vector4 Ka( 0.25F, 0.20725F, 0.20725F, 1.0F );		
		Math::Vector4 Ke( 1.0F, 1.0F, 1.0F, 1.0F );
		Math::Vector4 Kd( 1.0F, 0.829F, 0.829F, 1.0F );
		Math::Vector4 Ks( 0.296648F, 0.296648F, 0.296648F, 1.0F );
		material.SetMaterialProperties( Ka, Ke, Kd, Ks, 11.264F );

		//generate the pending game object
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( gameObjIdentifier, objType, 
			this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, gameObjCategory );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( *gameObjVec, gameObjCategory );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the missile for the missile game
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitMissile( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		float missileRadius = this->m_missileGame.m_plane.m_radius;

		/*
		float xWorldPt = 0.0F;
		float yWorldPt = 0.0F;		

		Point2D missilePos = this->m_missileGame.m_missile.m_position;
		float missilePosX = missilePos.x;
		float missilePosY = missilePos.y;

		//convert screen to world coordinates
		this->m_parentGM.m_graphicsInterfacePtr->ConvertScreenToWorld( missilePosX, missilePosY, xWorldPt, yWorldPt );
		//replace the missile screen coordinates with the world coordinates
		this->m_missileGame.m_missile.m_position.x = xWorldPt;
		this->m_missileGame.m_missile.m_position.y = yWorldPt;
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		unsigned int gameObjIdentifier = MyGeometryGame::MISSILE_GAMEOBJ;
		unsigned int objType = MyGeometryGame::SPHERE2_OBJTYPE;
		GameFramework::GameObjCategory gameObjCategory = GameFramework::LIGHTED_CATEGORY; 
		GameFramework::GameObjectVector * gameObjVec = &this->m_lightedGameObjList;

		physicsObj.SetPosition( Math::Vector4( this->m_missileGame.m_missile.m_position.x, this->m_missileGame.m_missile.m_position.y, 1.0F, 1.0F ) );
		physicsObj.SetScale( Math::Vector4( missileRadius, missileRadius, missileRadius, 0.0F ) );

		//generate the pending game object
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( gameObjIdentifier, objType, 
			this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, gameObjCategory );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( *gameObjVec, gameObjCategory );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the zones for the missile game
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitMissileGameZones( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		float xWorldPt = 0.0F;
		float yWorldPt = 0.0F;

		Point2D cityPos;
		float cityPosX = 0.0F;
		float cityPosY = 0.0F;
		float cityRadius = 0.0F;

		unsigned int gameObjIdentifier = MyGeometryGame::ZONE_GAMEOBJ;
		unsigned int objType = MyGeometryGame::SPHERE_OBJTYPE;
		GameFramework::GameObjCategory gameObjCategory = GameFramework::LIGHTED_CATEGORY; 
		GameFramework::GameObjectVector * gameObjVec = 0;

		//loop through the zones
		for ( unsigned index = 0; index < CITYNUMBER; ++index )
		{
			cityPos = this->m_missileGame.m_cities[index].position;
			cityPosX = cityPos.x;
			cityPosY = cityPos.y;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//set and store the radius
			this->m_missileGame.m_cities[index].radius = this->m_missileGame.m_cities[index].radius * WORLD_SCALE;
			cityRadius = this->m_missileGame.m_cities[index].radius;
			//cityRadius = cityRadius / MAX_RADIUS;	
			//this->m_missileGame.m_cities[index].radius = cityRadius;
			//convert screen to world coordinates
			//this->m_parentGM.m_graphicsInterfacePtr->ConvertScreenToWorld( 0.0F, cityRadius, xWorldPt, yWorldPt );
			//cityRadius = std::abs( xWorldPt - yWorldPt );						

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//convert screen to world coordinates
			this->m_parentGM.m_graphicsInterfacePtr->ConvertScreenToWorld( cityPosX, cityPosY, xWorldPt, yWorldPt );
			//replace the city screen coordinates with the world coordinates
			this->m_missileGame.m_cities[index].position.x = xWorldPt;
			this->m_missileGame.m_cities[index].position.y = -yWorldPt;

			//render zone
			physicsObj.ResetValues();
			physicsObj.SetPosition( Math::Vector4( xWorldPt, -yWorldPt, 0.0F, 1.0F ) );
			physicsObj.SetScale( Math::Vector4( cityRadius, cityRadius, cityRadius, 1.0F ) );

			if ( index == 0 )
			{
				//chrome
				Math::Vector4 Ka( 0.25F, 0.25F, 0.25F, 1.0F );		
				Math::Vector4 Ke( 0.7F, 0.7F, 0.7F, 1.0F );
				Math::Vector4 Kd( 0.4F, 0.4F, 0.4F, 1.0F );
				Math::Vector4 Ks( 0.774597F, 0.774597F, 0.774597F, 1.0F );
				material.SetMaterialProperties( Ka, Ke, Kd, Ks, 76.8F );

				objType = MyGeometryGame::SPHERE_OBJTYPE;
				gameObjCategory = GameFramework::REFLECTIVE_CATEGORY; 
				gameObjVec = & this->m_reflectiveGameObjList;
			}
			else if ( index == 1 )
			{
				//pearl
				Math::Vector4 Ka( 0.25F, 0.20725F, 0.20725F, 1.0F );		
				Math::Vector4 Ke( 0.2F, 0.2F, 0.2F, 1.0F );
				Math::Vector4 Kd( 1.0F, 0.829F, 0.829F, 1.0F );
				Math::Vector4 Ks( 0.296648F, 0.296648F, 0.296648F, 1.0F );
				material.SetMaterialProperties( Ka, Ke, Kd, Ks, 11.264F );

				objType = MyGeometryGame::SPHERE3_OBJTYPE;
				gameObjCategory = GameFramework::LIGHTED_CATEGORY; 
				gameObjVec = & this->m_lightedGameObjList;
			}
			else if ( index == 2 )
			{
				//silver
				Math::Vector4 Ka( 0.19225F, 0.19225F, 0.19225F, 1.0F );		
				Math::Vector4 Ke( 0.0F, 0.0F, 0.0F, 1.0F );
				Math::Vector4 Kd( 0.50754F, 0.50754F, 0.50754F, 1.0F );
				Math::Vector4 Ks( 0.508273F, 0.508273F, 0.508273F, 1.0F );
				material.SetMaterialProperties( Ka, Ke, Kd, Ks, 51.2F );

				objType = MyGeometryGame::SPHERE_OBJTYPE;
				gameObjCategory = GameFramework::LIGHTED_CATEGORY;
				gameObjVec = & this->m_lightedGameObjList;
			}
			else if ( index == 3 )
			{		
				//chrome
				Math::Vector4 Ka( 0.25F, 0.25F, 0.25F, 1.0F );		
				Math::Vector4 Ke( 0.7F, 0.7F, 0.7F, 1.0F );
				Math::Vector4 Kd( 0.4F, 0.4F, 0.4F, 1.0F );
				Math::Vector4 Ks( 0.774597F, 0.774597F, 0.774597F, 1.0F );
				material.SetMaterialProperties( Ka, Ke, Kd, Ks, 76.8F );

				objType = MyGeometryGame::SPHERE_OBJTYPE;
				gameObjCategory = GameFramework::FRESNEL_CATEGORY; 
				gameObjVec = & this->m_fresnelGameObjList;
			}
			else if ( index == 4 )
			{
				//brass
				Math::Vector4 Ka( 0.329412F, 0.223529F, 0.027451F, 1.0F );		
				Math::Vector4 Ke( 0.0F, 0.0F, 0.0F, 1.0F );
				Math::Vector4 Kd( 0.780392F, 0.568627F, 0.113725F, 1.0F );
				Math::Vector4 Ks( 0.992157F, 0.941176F, 0.807843F, 1.0F );
				material.SetMaterialProperties( Ka, Ke, Kd, Ks, 27.8974F );

				objType = MyGeometryGame::SPHERE_OBJTYPE;
				gameObjCategory = GameFramework::LIGHTED_CATEGORY;
				gameObjVec = & this->m_lightedGameObjList;
			}

			//generate the pending game object
			this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( gameObjIdentifier, objType, 
				this->m_parentGM.m_graphicsInterfacePtr, 
				physicsObj, material, gameObjCategory );

			//add the game objects from the game object manager to the current object list of the state
			this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( *gameObjVec, gameObjCategory );

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the objects
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//RIGHT
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 15.0F, 0.0F, 0.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ) );
		physicsObj.SetRotationY( -90.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID2_OBJTYPE, GRID2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::NORMAL_CATEGORY );
		
		//LEFT
		physicsObj.SetPosition( Math::Vector4( -15.0F, 0.0F, 0.0F, 1.0F ) );
		physicsObj.SetRotationY( 90.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID3_OBJTYPE, GRID3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::NORMAL_CATEGORY );

		//TOP
		physicsObj.SetPosition( Math::Vector4( 0.0F, 15.0F, 0.0F, 1.0F ) );
		physicsObj.SetRotationY( 0.0F );	
		physicsObj.SetRotationX( 90.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID4_OBJTYPE, GRID4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::NORMAL_CATEGORY );

		//BOTTOM
		physicsObj.SetPosition( Math::Vector4( 0.0F, -15.0F, 0.0F, 1.0F ) );
		physicsObj.SetRotationY( 0.0F );	
		physicsObj.SetRotationX( -90.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID5_OBJTYPE, GRID5_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::NORMAL_CATEGORY );

		//FRONT
		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.0F, -15.0F, 1.0F ) );
		physicsObj.SetRotationX( 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID6_OBJTYPE, GRID6_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::NORMAL_CATEGORY );

		//BACK
		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.0F, 15.0F, 1.0F ) );
		physicsObj.SetRotationX( 0.0F );
		physicsObj.SetRotationY( -180.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID7_OBJTYPE, GRID7_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::NORMAL_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_currGameObjList, GameFramework::NORMAL_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the light source objects
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitLightSourceObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;	

		//MOON SPHERE
		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.0F, 3.0F, 1.0F ) );		

		Math::Vector4 Ka( 0.25F, 0.20725F, 0.20725F, 1.0F );		
		Math::Vector4 Ke( 1.0F, 1.0F, 1.0F, 1.0F );
		//Math::Vector4 Ke( 0.0F, 0.0F, 0.0F, 1.0F );
		Math::Vector4 Kd( 1.0F, 0.829F, 0.829F, 1.0F );
		Math::Vector4 Ks( 0.296648F, 0.296648F, 0.296648F, 1.0F );
		material.SetMaterialProperties( Ka, Ke, Kd, Ks, 11.264F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( LIGHT_SOURCE_GAMEOBJ, SPHERE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHT_SOURCE_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		//this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_lightSourceGameObjList, GameFramework::LIGHT_SOURCE_CATEGORY );
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_lightedGameObjList, GameFramework::LIGHT_SOURCE_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the objects with lighting effect
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitLightedObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//RIGHT
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 45.0F, 0.0F, 0.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 3.01F, 3.01F, 3.01F, 0.0F ) );
		physicsObj.SetRotationY( -90.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID2_OBJTYPE, GRID2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );
		
		//LEFT
		physicsObj.SetPosition( Math::Vector4( -45.0F, 0.0F, 0.0F, 1.0F ) );
		physicsObj.SetRotationY( 90.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID3_OBJTYPE, GRID3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//TOP
		physicsObj.SetPosition( Math::Vector4( 0.0F, 45.0F, 0.0F, 1.0F ) );
		physicsObj.SetRotationY( -90.0F );	
		physicsObj.SetRotationX( 90.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID4_OBJTYPE, GRID4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//BOTTOM
		physicsObj.SetPosition( Math::Vector4( 0.0F, -45.0F, 0.0F, 1.0F ) );
		physicsObj.SetRotationY( 0.0F );	
		physicsObj.SetRotationX( -90.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID5_OBJTYPE, GRID5_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//FRONT
		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.0F, -45.0F, 1.0F ) );
		physicsObj.SetRotationX( 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID6_OBJTYPE, GRID6_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//BACK
		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.0F, 45.0F, 1.0F ) );
		physicsObj.SetRotationX( 0.0F );
		physicsObj.SetRotationY( -180.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID7_OBJTYPE, GRID7_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 2.5F, 0.0F, 0.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CUBE_OBJTYPE, CUBE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		physicsObj.SetPosition( Math::Vector4( 0.0F, 2.5F, 0.0F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CUBE3_OBJTYPE, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		physicsObj.ResetValues();

		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.0F, -2.5F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( SPHERE3_OBJTYPE, SPHERE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		physicsObj.SetPosition( Math::Vector4( -2.5F, 0.0F, 0.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 45.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CONE_OBJTYPE, CONE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );
		
		physicsObj.SetPosition( Math::Vector4( 0.0F, -2.5F, 0.0F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CYLINDER3_OBJTYPE, CYLINDER3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );
		*/

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_lightedGameObjList, GameFramework::LIGHTED_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the objects with reflective effect
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitReflectiveObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//REFLECTIVE SPHERE
		physicsObj.SetPosition( Math::Vector4( 0.0F, -0.75F, 0.0F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( REFLECTIVE_GAMEOBJ, SPHERE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::REFLECTIVE_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_reflectiveGameObjList, GameFramework::REFLECTIVE_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the objects with refractive effect
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitRefractiveObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//REFRACTIVE SPHERE
		physicsObj.SetPosition( Math::Vector4( -1.0F, -0.75F, 0.0F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( REFRACTIVE_GAMEOBJ, SPHERE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::REFRACTIVE_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_refractiveGameObjList, GameFramework::REFRACTIVE_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the objects with refraction with chromatic dispersion effect
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitRefractiveChromDispObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//REFRACTIVE SPHERE WITH CHROMATIC DISPERSION
		physicsObj.SetPosition( Math::Vector4( -1.0F, 0.75F, 0.0F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( REFRACTIVE_CD_GAMEOBJ, SPHERE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::REFRACTIVE_CD_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_refractiveChromDispGameObjList, GameFramework::REFRACTIVE_CD_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the objects with Fresnel effect
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitFresnelObjects( void )
	{
		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//FRESNEL SPHERE
		physicsObj.SetPosition( Math::Vector4( 0.0F, 0.75F, 0.0F, 1.0F ) );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( FRESNEL_GAMEOBJ, SPHERE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::FRESNEL_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_fresnelGameObjList, GameFramework::FRESNEL_CATEGORY );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Initialize the state
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::Init( void )
	{		
		glPointSize( 5.0F );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*
		//DEBUG
		for ( int angle = -180; angle < 180; ++angle )
		{			
			this->m_missileGame.m_fuzzyLogicMissile.GetDeltaAngle( angle );
		}//end for loop
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Math::Vector4 cameraPosition( 0.0F, 0.0F, CAMERA_DISTANCE_FROM_NEAR_PLANE, 1.0f );
		Math::Vector4 target( 0.0F, 0.0F, 0.0F, 1.0f );
		Math::Vector4 upVector( 0.0F, 1.0F, 0.0F, 0.0f );

		this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( cameraPosition );
		this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraTarget( target );
		this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetWorldUpVector( upVector );	
		this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector( target - cameraPosition );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set up the effects
		GraphicsFramework::Effects * noEffectPtr = new GraphicsFramework::NoEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::NORMAL, noEffectPtr );

		GraphicsFramework::Effects * lightingEffectPtr = new GraphicsFramework::LightingEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::LIGHT, lightingEffectPtr );

		GraphicsFramework::Effects * lightingFragEffectPtr = new GraphicsFramework::LightingEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::LIGHT_FRAG, lightingFragEffectPtr, false );

		GraphicsFramework::Effects * reflectiveEffectPtr = new GraphicsFramework::ReflectiveEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::REFLECTIVE, reflectiveEffectPtr );

		GraphicsFramework::Effects * reflectiveFragEffectPtr = new GraphicsFramework::ReflectiveEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::REFLECTIVE_FRAG, reflectiveFragEffectPtr, false );

		GraphicsFramework::Effects * refractiveEffectPtr = new GraphicsFramework::RefractiveEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::REFRACTIVE, refractiveEffectPtr );

		GraphicsFramework::Effects * refractiveFragEffectPtr = new GraphicsFramework::RefractiveEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::REFRACTIVE_FRAG, refractiveFragEffectPtr, false );

		GraphicsFramework::Effects * refractiveChromDispEffectPtr = new GraphicsFramework::RefractiveChromDispEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::REFRACTIVE_CD, refractiveChromDispEffectPtr );

		GraphicsFramework::Effects * refractiveChromDispFragEffectPtr = new GraphicsFramework::RefractiveChromDispEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::REFRACTIVE_CD_FRAG, refractiveChromDispFragEffectPtr, false );

		GraphicsFramework::Effects * fresnelEffectPtr = new GraphicsFramework::FresnelEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::FRESNEL, fresnelEffectPtr );

		GraphicsFramework::Effects * fresnelFragEffectPtr = new GraphicsFramework::FresnelEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::FRESNEL_FRAG, fresnelFragEffectPtr, false );

		GraphicsFramework::Effects * dualParaboloidEffectPtr = new GraphicsFramework::DualParaboloidEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::DUAL_PARABOLOID_GENERATION, dualParaboloidEffectPtr );	

		GraphicsFramework::Effects * dualParaboloidReflectiveEffectPtr = new GraphicsFramework::DualParaboloidReflectiveEffect;
		this->m_parentGM.m_renderMgr.InitEffect( GraphicsFramework::DUAL_PARABOLOID_REFLECTIVE, dualParaboloidReflectiveEffectPtr );	

		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set up the projector
		this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( Math::Vector4( 0.0F, 0.0F, 2.0F, 1.0F ) );
		this->m_parentGM.m_renderMgr.GetProjector().SetLookAtTarget( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
		this->m_parentGM.m_renderMgr.GetProjector().SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set up the directional light
		this->m_parentGM.m_renderMgr.GetDirectionalLight().SetLookAtViewDirectionVector( Math::Vector4( 0.0F, 0.0F, -3.0F, 0.0F ).GetNormalized() );


		//set up the omni light
		this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtViewDirectionVector( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( Math::Vector4( 0.0F, 0.0F, 3.0F, 1.0F ) );
		this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtTarget( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
		this->m_parentGM.m_renderMgr.GetOmniLight().SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) );


		//set up the spot light
		this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtViewDirectionVector( ( Math::Vector4( 0.0F, 0.0F, -3.0F, 0.0F ).GetNormalized() ) );
		this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( Math::Vector4( 0.0F, 0.0F, 3.0F, 1.0F ) );		
		this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtTarget( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
		this->m_parentGM.m_renderMgr.GetSpotLight().SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) );
		this->m_parentGM.m_renderMgr.GetSpotLight().SetInnerConeAngleDegrees( std::cosf( Math::DegreeToRadian( 8.0F ) ) );
		this->m_parentGM.m_renderMgr.GetSpotLight().SetOuterConeAngleDegrees( std::cosf( Math::DegreeToRadian( 30.0F ) ) );		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//this->InitObjects();
		//this->InitLightSourceObjects();
		this->InitLightedObjects();
		/*
		this->InitReflectiveObjects();
		this->InitRefractiveObjects();
		this->InitRefractiveChromDispObjects();		
		this->InitFresnelObjects();	
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		this->m_missileGame.InitGame();
		//this->m_missileGame.RenderZones( & this->m_parentGM );	
		this->InitPlane();
		this->InitMissileGameZones();
		//this->InitMissile();			

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		const int numOfTilesPerSide = this->m_parentGM.m_noOfTilesPerSide;
		const float m_boardSideLength = 3.0F;

		//initialize the tile board
		this->InitializeTileBoard( numOfTilesPerSide, m_boardSideLength );
		//create the tiles
		this->CreateTiles();

		//allocate the N Puzzle in the heap
		this->m_nPuzzle = new NPuzzle( numOfTilesPerSide, NORMAL );
		//set the initial state of the N Puzzle
		this->m_nPuzzle->SetState( this->m_board.m_currTileArrangement, this->m_board.m_tilesNumber + 1 );
		//solve the N Puzzle
		//this->m_nPuzzle->SearchForSolution( DFS );

		//BUTTON_SEARCH_METHOD_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_SEARCH_METHOD_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, 2.0F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );

		//BUTTON_RESET_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_RESET_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, 1.35F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );

		//BUTTON_RANDOM_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_RANDOM_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, 0.70F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );

		//BUTTON_SOLVE_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_SOLVE_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, 0.05F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );

		//BUTTON_ANIMATION_SPEED_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_ANIMATION_SPEED_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, -0.60F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );

		//BUTTON_STRESS_TEST_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_STRESS_TEST_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, -1.25F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );

		//BUTTON_MENU_GAMEOBJ
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BUTTON_MENU_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.75F, -1.95F, -0.15F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.65F, 0.5F, 0.25F, 0.0F ), 0.0F );
		*/

		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID_OBJTYPE, GRID_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr );
		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( POLYGON_OBJTYPE, POLYGON_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr );
		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CUBE_OBJTYPE, CUBE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr );
		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CYLINDER_OBJTYPE, CYLINDER_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr );
		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CONE_OBJTYPE, CONE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr );
		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( SPHERE_OBJTYPE, SPHERE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr );		


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( GRID_OBJTYPE, GRID_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			//Math::Vector4( 0.0F, 0.0F, -1.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), Math::Vector4( 0.0F, 0.0F, 45.0F, 0.0F ) );

		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( POLYGON_OBJTYPE, POLYGON_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			//Math::Vector4( 0.0F, -1.5F, 1.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), Math::Vector4( -90.0F, 0.0F, 45.0F, 0.0F ) );

		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CUBE_OBJTYPE, CUBE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			//Math::Vector4( 1.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );

		//this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CYLINDER_OBJTYPE, CYLINDER_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			//Math::Vector4( -1.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), Math::Vector4( 0.0F, 0.0F, 45.0F, 0.0F ) );

		/*
		//MIRROR
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( MIRROR_GAMEOBJ, GRID_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 1.0F, -3.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 3.0F, 1.0F, 0.0F ), 45.0F );		

		//CRATE
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CRATE_GAMEOBJ, CUBE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), 0.0F );
		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CAN_GAMEOBJ, CYLINDER_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			Math::Vector4( 1.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), 0.0F );
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Light::Material material;
		PhysicsFramework::PhysicsObject physicsObj;

		//GANTRY
		//TOP BORDER
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 0.0F, 3.0F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 5.0F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 0.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//BOTTOM BORDER
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 0.0F, -3.0F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 5.0F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 180.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );
		
		//LEFT BORDER	
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( -3.5F, 0.0F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 4.0F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 90.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//RIGHT BORDER	
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 3.5F, 0.0F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 4.0F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( -90.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//RIGHT TOP CORNER BORDER
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 3.0F, 2.5F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.45F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( -44.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//RIGHT BOTTOM CORNER BORDER
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( 3.0F, -2.5F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.45F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 225.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//LEFT TOP CORNER BORDER
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( -3.0F, 2.5F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.45F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( 44.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//LEFT BOTTOM CORNER BORDER
		physicsObj.ResetValues();
		physicsObj.SetPosition( Math::Vector4( -3.0F, -2.5F, 1.0F, 1.0F ) );
		physicsObj.SetVelocity( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
		physicsObj.SetScale( Math::Vector4( 1.45F, 0.10F, 1.0F, 0.0F ) );
		physicsObj.SetRotationZ( -225.0F );		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			physicsObj, material, GameFramework::LIGHTED_CATEGORY );

		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_lightedGameObjList, GameFramework::LIGHTED_CATEGORY );

		/*
		//RIGHT TOP CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.50F, 1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), -28.0F );
		//RIGHT BOTTOM CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.50F, -1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), 208.0F );
		//LEFT TOP CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -2.50F, 1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), 28.0F );
		//LEFT BOTTOM CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -2.50F, -1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), -208.0F );	
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*
		//ROAD
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( ROAD_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, -1.5F, 3.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.05F, 3.0F, 0.0F ), 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( ROAD_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, -1.5F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.05F, 3.0F, 0.0F ), 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( ROAD_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, -1.5F, -3.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.05F, 3.0F, 0.0F ), 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( ROAD_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, -1.5F, -6.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.05F, 3.0F, 0.0F ), 0.0F );
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( ROAD_GAMEOBJ, CUBE2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, -1.5F, -9.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.05F, 3.0F, 0.0F ), 0.0F );
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*
		//SATELLITE
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( SATELLITE_GAMEOBJ, SATELLITE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.3F, 0.3F, 0.3F, 0.0F ), 0.0F );

		//CIRCLE PILLAR CENTER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( CIRCLEPILLAR_GAMEOBJ, SPHERE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
			Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.4F, 0.4F, 0.4F, 0.0F ), 0.0F, 
			0.0F, 0.0F, 0.0F, 1.0F, false );
		*/

		/*
		//WINDOW
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WINDOW_GAMEOBJ, CUBE4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 0.5F, 1.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 6.0F, 1.5F, 0.10F, 0.0F ), 0.0F );
		*/

		//add the game objects from the game object manager to the current object list of the state
		//this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_currGameObjList );

		/*
		//TESTING
		//unsigned int newTileArr[] = { 4, 6, 13, 7, 11, 8, 1, 15, 12, 0, 3, 9, 14, 2, 5, 10, 9 };
		//unsigned int newTileArr[] = { 1, 3, 2, 0, 3 };
		//DFS
		//unsigned int newTileArr[] = { 3, 8, 7, 0, 2, 1, 5, 6, 4, 3 };
		//unsigned int newTileArr[] = { 8, 4, 1, 5, 7, 6, 0, 3, 2, 6 };
		//A STAR
		//unsigned int newTileArr[] = { 8, 3, 6, 7, 5, 4, 1, 0, 2, 7 };
		//unsigned int newTileArr[] = { 2, 0, 5, 3, 1, 7, 4, 8, 6, 1 };
		
		for ( unsigned index = 0; index < this->m_board.m_tilesNumber + 1; ++index )
		{
			this->m_board.m_currTileArrangement[index] = newTileArr[index];
			//unsigned int testVal = this->m_board.m_currTileArrangement[index];
		}

		//plot the tiles based on the current tile arrangement data
		this->PlotTiles();
		*/
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the state
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::Update( float startTime, float dt )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set up the lighting effect
		Light::LIGHT_EFFECT lightEffect = Light::POINT;
		if ( this->m_parentGM.m_lighting == Light::DIRECTIONAL )
			lightEffect = Light::DIRECTIONAL;
		else if ( this->m_parentGM.m_lighting == Light::POINT )
			lightEffect = Light::POINT;
		else if ( this->m_parentGM.m_lighting == Light::SPOT )
			lightEffect = Light::SPOT;

		char * projTexName = "";
		if ( this->m_parentGM.m_showProjTex == true )
		{
			projTexName = "EthanCochardLongboard";
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( this->m_missileGame.m_launchMissile == true )
		{
			//reads and updates the damage value once the plane enter the city
			this->m_missileGame.ReadDamageValue();
			//graudally consumes the fuel
			this->m_missileGame.ConsumeFuel();

			//calculate the fuzzy attack rate
			this->m_missileGame.m_fuzzyLogicMissile.CalculateAttackRate();
			//update the missile direciton through Fuzzy Logic
			this->m_missileGame.m_fuzzyLogicMissile.UpdateCorrection( &this->m_missileGame.m_missile, &this->m_missileGame.m_plane );

			//check the game status
			bool gameOver = this->m_missileGame.CheckGameStatus( this->m_parentGM.m_graphicsInterfacePtr );

			if ( gameOver == true )
			{	
				for ( unsigned index = 0; index < this->m_lightedGameObjList.size(); ++index )
				{
					GameFramework::GameObject & gameObj = this->m_lightedGameObjList.at( index );
					
					//deactivate the missile
					if ( gameObj.GetIdentifier() == MyGeometryGame::MISSILE_GAMEOBJ )
					{
						gameObj.SetActive( false );
					}

					//reset the plane
					if ( gameObj.GetIdentifier() == MyGeometryGame::LIGHT_SOURCE_GAMEOBJ )
					{
						gameObj.SetActive( false );								
					}

					//deactivate zones
					if ( gameObj.GetIdentifier() == MyGeometryGame::ZONE_GAMEOBJ )
					{
						gameObj.SetActive( false );												
					}

				}//end for loop

				for ( unsigned index = 0; index < this->m_reflectiveGameObjList.size(); ++index )
				{
					GameFramework::GameObject & gameObj = this->m_reflectiveGameObjList.at( index );
					//deactivate zones
					if ( gameObj.GetIdentifier() == MyGeometryGame::ZONE_GAMEOBJ )
					{
						gameObj.SetActive( false );												
					}
				}//end for loop

				for ( unsigned index = 0; index < this->m_fresnelGameObjList.size(); ++index )
				{
					GameFramework::GameObject & gameObj = this->m_fresnelGameObjList.at( index );
					//deactivate zones
					if ( gameObj.GetIdentifier() == MyGeometryGame::ZONE_GAMEOBJ )
					{
						gameObj.SetActive( false );												
					}
				}//end for loop

				//reinitialize	
				this->InitPlane();
				this->InitMissileGameZones();

				std::cout << std::setfill (' ') << std::setw( 0 ) << "lighted objects count : " << this->m_lightedGameObjList.size() << std::endl;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//updates the scene
		this->UpdateScene( dt );	

		//update the collision behavior of the object
		this->UpdateCollision( startTime, dt );

		//update the behavior of the object
		//this->UpdateBehavior( dt );	
		this->UpdateBehavior( dt, this->m_lightedGameObjList );		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//start the graphics interface for drawing
		this->m_parentGM.m_graphicsInterfacePtr->StartDrawing();

		/*
		//clear the open gl color, depth, stencil buffer
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		this->m_parentGM.m_graphicsInterfacePtr->SetViewPort( 0, 0, GraphicsFramework::ENVMAP_VIEWPORT_SIZE, GraphicsFramework::ENVMAP_VIEWPORT_SIZE );

		//generate the cube map
		this->m_parentGM.m_renderMgr.GenerateCubeMap( "TestEnvMap", GraphicsFramework::LIGHT, lightEffect, projTexName, this->m_lightedGameObjList );
		*/

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*
		//clear the open gl color, depth, stencil buffer
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		this->m_parentGM.m_graphicsInterfacePtr->SetViewPort( 0, 0, 
			static_cast<unsigned>( this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() ), 
			static_cast<unsigned>( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() ) );
		*/			

		//draw/render the objects
		this->DrawMain( dt );		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//end the graphics interface for drawing
		this->m_parentGM.m_graphicsInterfacePtr->EndDrawing();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Shut down the state by clearing the game objects from the state
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::Shutdown( void )
	{
		//clear the game objects from the state
		this->m_currGameObjList.clear();

		//delete from the heap
		if ( this->m_board.m_currTileArrangement != 0 )
		{
			delete [] this->m_board.m_currTileArrangement;
			this->m_board.m_currTileArrangement = 0;
		}

		if ( this->m_nPuzzle != 0 )
		{
			delete this->m_nPuzzle;	
			this->m_nPuzzle = 0;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the scene
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::UpdateScene( float dt )
	{
		const float speed = LOOKAT_DAMP * dt;

		//toggle anisotropic filtering
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::T ) )
		{
			if ( Utility::isExtensionSupported( "GL_EXT_texture_filter_anisotropic" ) == 1 )
			{
				//the maximum anisotropy is a float and it has to be greater than 1.0 when the extension should take effect
				float maximumAnisotropy = 1.1F;

				this->m_parentGM.m_enableAnisotropicFiltering = !this->m_parentGM.m_enableAnisotropicFiltering;
				if ( this->m_parentGM.m_enableAnisotropicFiltering == true  )
				{
					//get the maximum value supported by the graphics card
					glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy );
				}
				else
				{
					//disable anisotropic filtering
					maximumAnisotropy = 1.0F;
				}
				
				GraphicsFramework::TextureIdMap texMap = this->m_parentGM.m_graphicsInterfacePtr->GetTextureMap();
				//get the iterators of the map
				GraphicsFramework::TextureIdMap::iterator itor = texMap.begin();
				GraphicsFramework::TextureIdMap::iterator end = texMap.end();

				//loop through the textures
				while ( itor != end )
				{
					glBindTexture( GL_TEXTURE_2D, itor->second );
					//set the anisotropic filtering maximum value
					glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy );

					++itor;
				}//end while loop				
			}
		}


		//toggle the texture minification filter mode
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::F ) )
		{
			if ( this->m_parentGM.m_texMinFilterMode == GL_LINEAR )
				this->m_parentGM.m_texMinFilterMode = GL_NEAREST;
			else if ( this->m_parentGM.m_texMinFilterMode == GL_NEAREST )
				this->m_parentGM.m_texMinFilterMode = GL_LINEAR_MIPMAP_LINEAR;
			else if ( this->m_parentGM.m_texMinFilterMode == GL_LINEAR_MIPMAP_LINEAR )
				this->m_parentGM.m_texMinFilterMode = GL_NEAREST_MIPMAP_LINEAR;
			else if ( this->m_parentGM.m_texMinFilterMode == GL_NEAREST_MIPMAP_LINEAR )
				this->m_parentGM.m_texMinFilterMode = GL_LINEAR_MIPMAP_NEAREST;
			else if ( this->m_parentGM.m_texMinFilterMode == GL_LINEAR_MIPMAP_NEAREST )
				this->m_parentGM.m_texMinFilterMode = GL_NEAREST_MIPMAP_NEAREST;
			else
				this->m_parentGM.m_texMinFilterMode = GL_LINEAR;
			
			GraphicsFramework::TextureIdMap texMap = this->m_parentGM.m_graphicsInterfacePtr->GetTextureMap();
			//get the iterators of the map
			GraphicsFramework::TextureIdMap::iterator itor = texMap.begin();
			GraphicsFramework::TextureIdMap::iterator end = texMap.end();

			//loop through the textures
			while ( itor != end )
			{
				glBindTexture( GL_TEXTURE_2D, itor->second );
				//set the minification filter value
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_parentGM.m_texMinFilterMode );

				++itor;
			}//end while loop					
		}


		//toggle the texture magnification filter mode
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::G ) )
		{
			if ( this->m_parentGM.m_texMagFilterMode == GL_LINEAR )
				this->m_parentGM.m_texMagFilterMode = GL_NEAREST;
			else
				this->m_parentGM.m_texMagFilterMode = GL_LINEAR;

			GraphicsFramework::TextureIdMap texMap = this->m_parentGM.m_graphicsInterfacePtr->GetTextureMap();
			//get the iterators of the map
			GraphicsFramework::TextureIdMap::iterator itor = texMap.begin();
			GraphicsFramework::TextureIdMap::iterator end = texMap.end();

			//loop through the textures
			while ( itor != end )
			{
				glBindTexture( GL_TEXTURE_2D, itor->second );
				//set the magnification filter value
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_parentGM.m_texMagFilterMode );

				++itor;
			}//end while loop				
		}


		//toggle between perspective and orthographic projection
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::P ) )
		{
			Math::Mtx44 projMatrix;
			projMatrix.SetToIdentity();

			float FOV = this->m_parentGM.m_graphicsInterfacePtr->GetFieldOfView();
			float aspectRatio = this->m_parentGM.m_graphicsInterfacePtr->GetAspectRatio();

			this->m_parentGM.m_showOrthoProj = !this->m_parentGM.m_showOrthoProj;			

			//set the projection matrix
			this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::PROJECTION ) );
			
			if ( this->m_parentGM.m_showOrthoProj == true )
			{
				//projMatrix.Ortho ( -2.5F * aspectRatio, 2.5F * aspectRatio, -2.5F, 2.5F, -3.0F, 10.0F );
				projMatrix.Ortho ( -2.75F * aspectRatio, 2.75F * aspectRatio, -2.75F, 3.0F, -100.0F, 100.0F );
				//projMatrix.Ortho ( -3.25F * aspectRatio, 3.25F * aspectRatio, -3.25F, 3.5F, -200.0F, 200.0F );
			}
			else
			{
				projMatrix.Perspective ( FOV, aspectRatio, 0.1F, 200.0F );
			}

			//load the matrix
			this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack.LoadMatrix( projMatrix );
		}


		//toggle display of wall normal
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::N ) )
		{
			this->m_parentGM.m_showWallNormal = !this->m_parentGM.m_showWallNormal;
		}


		//set culling
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::C ) )
		{			
			this->m_parentGM.m_isBackFaceEnabled = !this->m_parentGM.m_isBackFaceEnabled;
			if( this->m_parentGM.m_isBackFaceEnabled  )
			{
				glEnable( GL_CULL_FACE );				
			}
			else
			{				
				glDisable( GL_CULL_FACE );
			}
		}


		//set the polygon mode
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::V ) )
		{
			if ( this->m_parentGM.m_polygonMode == GL_FILL )
				this->m_parentGM.m_polygonMode = GL_LINE;
			else if ( this->m_parentGM.m_polygonMode == GL_LINE )
				this->m_parentGM.m_polygonMode = GL_POINT;
			else
				this->m_parentGM.m_polygonMode = GL_FILL;

			glPolygonMode( GL_FRONT_AND_BACK, this->m_parentGM.m_polygonMode );
		}


		//reset the camera
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::R ) )
		{
			Math::Vector4 cameraPosition( 0.0F, 0.0F, CAMERA_DISTANCE_FROM_NEAR_PLANE, 1.0f );
			Math::Vector4 target( 0.0F, 0.0F, 0.0F, 1.0f );
			Math::Vector4 upVector( 0.0F, 1.0F, 0.0F, 0.0f );

			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( cameraPosition );
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraTarget( target );
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetWorldUpVector( upVector );	
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector( target - cameraPosition );

			this->m_parentGM.m_graphicsInterfacePtr->SetWorldLastX( 0.0F );
			this->m_parentGM.m_graphicsInterfacePtr->SetWorldLastY( 0.0F );

			this->m_parentGM.m_graphicsInterfacePtr->m_camera.m_xOrientation = 0.0F;
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.m_yOrientation = -90.0F;
		}				

		//move camera forward		
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::ARROW_UP ) || this->m_parentGM.m_input.IsRepeating( InputMap::ARROW_UP ) )
		{
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() 
				+ ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraViewDirectionVector() ) );

			/*
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector(
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget() 
				- this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() );
			*/
		}


		//move camera backward
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::ARROW_DOWN ) || this->m_parentGM.m_input.IsRepeating( InputMap::ARROW_DOWN ) )
		{
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() 
				- ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraViewDirectionVector() ) );

			/*
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector(
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget() 
				- this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() );
			*/
		}


		//move camera left
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::ARROW_LEFT ) || this->m_parentGM.m_input.IsRepeating( InputMap::ARROW_LEFT ) )
		{
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() 
				- ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraSideVector() ) );

			/*
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraTarget( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget() 
				- ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraSideVector() ) );
			*/
			/*
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget() 
				- this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() );
			*/
		}


		//move camera right
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::ARROW_RIGHT ) || this->m_parentGM.m_input.IsRepeating( InputMap::ARROW_RIGHT ) )
		{
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() 
				+ ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraSideVector() ) );

			/*
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraTarget( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget() 
				+ ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraSideVector() ) );
			*/
			/*
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget() 
				- this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() );
			*/
		}


		//move camera upwards
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::PAGE_UP ) || this->m_parentGM.m_input.IsRepeating( InputMap::PAGE_UP ) )
		{
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() 
				+ ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraUpVector() ) );
		}


		//move camera downwards
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::PAGE_DOWN ) || this->m_parentGM.m_input.IsRepeating( InputMap::PAGE_DOWN ) )
		{
			this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraPosition( 
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() 
				- ( speed * this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraUpVector() ) );
		}


		/*
		//toggle the tile animation
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::E ) )
		{
			this->m_board.m_stopAnimation = true;
			//unlock the other buttons
			this->m_board.m_lockButtons = false;
			//unlock the tiles
			this->m_board.m_lockTiles = false;
		}
		*/


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//toggle render effect
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::K ) )
		{
			if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFLECTIVE )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE_CD;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE_CD )
				this->m_parentGM.m_renderEffect = GraphicsFramework::FRESNEL;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::FRESNEL )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFLECTIVE;

			if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFLECTIVE_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE_CD_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE_CD_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::FRESNEL_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::FRESNEL_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFLECTIVE_FRAG;
		}

		//toggle lighting effect
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::L ) )
		{
			if ( this->m_parentGM.m_lighting == Light::DIRECTIONAL )
				this->m_parentGM.m_lighting = Light::POINT;
			else if ( this->m_parentGM.m_lighting == Light::POINT )
				this->m_parentGM.m_lighting = Light::SPOT;
			else if ( this->m_parentGM.m_lighting == Light::SPOT )
				this->m_parentGM.m_lighting = Light::DIRECTIONAL;
		}

		//toggle between vertex and fragment shader effect
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::J ) )
		{
			if ( this->m_parentGM.m_lightingEffect == GraphicsFramework::LIGHT )
				this->m_parentGM.m_lightingEffect = GraphicsFramework::LIGHT_FRAG;
			else if ( this->m_parentGM.m_lightingEffect == GraphicsFramework::LIGHT_FRAG )
				this->m_parentGM.m_lightingEffect = GraphicsFramework::LIGHT;

			if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFLECTIVE )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFLECTIVE_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFLECTIVE_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFLECTIVE;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE_CD )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE_CD_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::REFRACTIVE_CD_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::REFRACTIVE_CD;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::FRESNEL )
				this->m_parentGM.m_renderEffect = GraphicsFramework::FRESNEL_FRAG;
			else if ( this->m_parentGM.m_renderEffect == GraphicsFramework::FRESNEL_FRAG )
				this->m_parentGM.m_renderEffect = GraphicsFramework::FRESNEL;
		}


		//toggle lighting attenuation
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::U ) )
		{
			this->m_parentGM.m_enableAttenuation = !this->m_parentGM.m_enableAttenuation;

			this->m_parentGM.m_renderMgr.GetSpotLight().SetAttenuationFlag( this->m_parentGM.m_enableAttenuation );
			this->m_parentGM.m_renderMgr.GetOmniLight().SetAttenuationFlag( this->m_parentGM.m_enableAttenuation );
		}

		//toggle object to move
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::N_1 ) )
		{
			unsigned noOfMovableObj = 2;

			++this->m_parentGM.m_objectToMove;

			//reset the object to move counter
			if ( this->m_parentGM.m_objectToMove == noOfMovableObj )
				this->m_parentGM.m_objectToMove = 0;
		}

		//reset light position and orientation
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::Z ) || this->m_parentGM.m_input.IsRepeating( InputMap::Z ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				//set up the projector
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtViewDirectionVector( ( Math::Vector4( 0.0F, 0.0F, -2.0F, 0.0F ).GetNormalized() ) );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( Math::Vector4( 0.0F, 0.0F, 2.0F, 1.0F ) );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtTarget( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
				this->m_parentGM.m_renderMgr.GetProjector().SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) );
				this->m_parentGM.m_renderMgr.GetProjector().m_xOrientation = 0.0F;
				this->m_parentGM.m_renderMgr.GetProjector().m_yOrientation = -90.0F;

				//set up the directional light
				this->m_parentGM.m_renderMgr.GetDirectionalLight().SetLookAtViewDirectionVector( Math::Vector4( 0.0F, 0.0F, -3.0F, 0.0F ).GetNormalized() );
				this->m_parentGM.m_renderMgr.GetDirectionalLight().m_xOrientation = 0.0F;
				this->m_parentGM.m_renderMgr.GetDirectionalLight().m_yOrientation = -90.0F;

				//set up the omni light
				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtViewDirectionVector( Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ) );
				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( Math::Vector4( 0.0F, 0.0F, 3.0F, 1.0F ) );
				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtTarget( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
				this->m_parentGM.m_renderMgr.GetOmniLight().SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) );

				//set up the spot light
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtViewDirectionVector( ( Math::Vector4( 0.0F, 0.0F, -3.0F, 0.0F ).GetNormalized() ) );
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( Math::Vector4( 0.0F, 0.0F, 3.0F, 1.0F ) );		
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtTarget( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0F ) );
				this->m_parentGM.m_renderMgr.GetSpotLight().SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) );
				this->m_parentGM.m_renderMgr.GetSpotLight().m_xOrientation = 0.0F;
				this->m_parentGM.m_renderMgr.GetSpotLight().m_yOrientation = -90.0F;

				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPosition( 0.0F, 0.0F, 3.0F );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPosition( 0.0F, 0.0F, 3.0F );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( 0.0F, 0.75F, 0.0F );
			}

		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//plane and missile control

		//launch missile
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::RETURN ) )
		{			
			if ( this->m_missileGame.m_setMissileDirection == true )
			{
				this->InitMissile();
				this->m_missileGame.m_setMissileDirection = false;
				this->m_missileGame.m_launchMissile = true;
			}
		}
		
		//up
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::W ) )
		{
			if ( this->m_missileGame.m_setMissileDirection == false )
			{
				this->m_missileGame.m_plane.m_direction.x = 0.0F;
				this->m_missileGame.m_plane.m_direction.y = 1.0F;
			}
		}

		//down
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::S ) )
		{
			if ( this->m_missileGame.m_setMissileDirection == false )
			{
				this->m_missileGame.m_plane.m_direction.x = 0.0F;
				this->m_missileGame.m_plane.m_direction.y = -1.0F;
			}
		}

		//left
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::A ) || this->m_parentGM.m_input.IsRepeating( InputMap::A ) )
		{
			if ( this->m_missileGame.m_setMissileDirection == true )
			{
				//increment the angle
				++this->m_missileGame.m_missileLaunchAngle;
				//cap the angle
				if ( this->m_missileGame.m_missileLaunchAngle > 360.0F )
					this->m_missileGame.m_missileLaunchAngle = 360.0F;				
			}
			else
			{
				this->m_missileGame.m_plane.m_direction.x = -1.0F;
				this->m_missileGame.m_plane.m_direction.y = 0.0F;
			}
		}

		//right
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::D ) || this->m_parentGM.m_input.IsRepeating( InputMap::D ) )
		{
			if ( this->m_missileGame.m_setMissileDirection == true )
			{
				//increment the angle
				--this->m_missileGame.m_missileLaunchAngle;
				//cap the angle
				if ( this->m_missileGame.m_missileLaunchAngle < -360.0F )
					this->m_missileGame.m_missileLaunchAngle = -360.0F;				
			}
			else
			{
				this->m_missileGame.m_plane.m_direction.x = 1.0F;
				this->m_missileGame.m_plane.m_direction.y = 0.0F;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*
		//move the light forward
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::W ) || this->m_parentGM.m_input.IsRepeating( InputMap::W ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( 
					this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition()
					+ ( speed * this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtViewDirectionVector() ) );

				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				
				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPositionZ( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatZ() );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPositionZ( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatZ() );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( this->m_fresnelGameObjList.front().GetPhysicsObj().GetPosition()
					- ( speed * Math::Vector4( 0.0F, 0.0F, 1.0F, 0.0F ) ) );
			}
		}

		//move the light backward
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::S ) || this->m_parentGM.m_input.IsRepeating( InputMap::S ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( 
					this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition()
					- ( speed * this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtViewDirectionVector() ) );

				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );

				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPositionZ( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatZ() );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPositionZ( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatZ() );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( this->m_fresnelGameObjList.front().GetPhysicsObj().GetPosition()
					+ ( speed * Math::Vector4( 0.0F, 0.0F, 1.0F, 0.0F ) ) );
			}
		}

		//move the light to the right
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::A ) || this->m_parentGM.m_input.IsRepeating( InputMap::A ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( 
					this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition()
					- ( speed * this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtSideVector() ) );

				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				
				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPositionX( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatX() );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPositionX( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatX() );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( this->m_fresnelGameObjList.front().GetPhysicsObj().GetPosition()
					- ( speed * Math::Vector4( 1.0F, 0.0F, 0.0F, 0.0F ) ) );
			}
		}

		//move the light to the right
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::D ) || this->m_parentGM.m_input.IsRepeating( InputMap::D ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( 
					this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition()
					+ ( speed * this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtSideVector() ) );

				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				
				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPositionX( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatX() );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPositionX( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatX() );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( this->m_fresnelGameObjList.front().GetPhysicsObj().GetPosition()
					+ ( speed * Math::Vector4( 1.0F, 0.0F, 0.0F, 0.0F ) ) );
			}
		}

		//move the light upwards
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::Q ) || this->m_parentGM.m_input.IsRepeating( InputMap::Q ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( 
					this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition()
					+ ( speed * Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) ) );

				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				
				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPositionY( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatY() );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPositionY( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatY() );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( this->m_fresnelGameObjList.front().GetPhysicsObj().GetPosition()
					+ ( speed * Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) ) );
			}
		}

		//move the light downwards
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::E ) || this->m_parentGM.m_input.IsRepeating( InputMap::E ) )
		{
			if ( this->m_parentGM.m_objectToMove == 0 )
			{
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( 
					this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition()
					- ( speed * Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) ) );

				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition() );

				//this->m_lightSourceGameObjList.front().GetPhysicsObj().SetPositionY( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatY() );
				this->m_lightedGameObjList.front().GetPhysicsObj().SetPositionY( this->m_parentGM.m_renderMgr.GetSpotLight().GetLookAtPosition().GetFloatY() );
			}
			else
			{
				this->m_fresnelGameObjList.front().GetPhysicsObj().SetPosition( this->m_fresnelGameObjList.front().GetPhysicsObj().GetPosition()
					- ( speed * Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0F ) ) );
			}
		}
		*/


		//toggle projective texture
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::O ) )
		{
			this->m_parentGM.m_showProjTex = !this->m_parentGM.m_showProjTex;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//mouse click
		if ( this->m_parentGM.m_input.IsPressed( InputMap::MOUSE_LEFT ) || this->m_parentGM.m_input.IsPressed( InputMap::MOUSE_RIGHT ) )
		{						
			float worldX = this->m_parentGM.m_graphicsInterfacePtr->GetWorldX();
			float worldY = this->m_parentGM.m_graphicsInterfacePtr->GetWorldY();			

			POINT point;
			point.x = this->m_parentGM.m_input.GetMouseX();
			point.y = this->m_parentGM.m_input.GetMouseY();

			//convert screen to world coordinates
			this->m_parentGM.m_graphicsInterfacePtr->ConvertScreenToWorld( static_cast<float>( point.x ), static_cast<float>( point.y ), worldX, worldY );	
			worldY *= -1.0f;

			if ( this->m_parentGM.m_input.IsTriggered( InputMap::MOUSE_LEFT ) )
			{
				if ( this->m_missileGame.m_launchMissile == false )
				{
					//set the missile starting position
					this->m_missileGame.m_missile.m_position.x = worldX;
					this->m_missileGame.m_missile.m_position.y = worldY;
					this->m_missileGame.m_setMissileDirection = true;
				}

			/*
			if ( this->m_parentGM.m_input.IsPressed( InputMap::MOUSE_LEFT ) )
			{
				//METHOD: spherical Cartesian coordinates
				float diffX = static_cast<float>( this->m_parentGM.m_input.GetMouseDX() );
				float diffY = static_cast<float>( this->m_parentGM.m_input.GetMouseDY() );

				this->m_parentGM.m_renderMgr.GetDirectionalLight().m_xOrientation += speed * diffX;
				this->m_parentGM.m_renderMgr.GetSpotLight().m_xOrientation += speed * diffX;
				this->m_parentGM.m_renderMgr.GetProjector().m_xOrientation += speed * diffX;

				float lightRotX = this->m_parentGM.m_renderMgr.GetSpotLight().m_xOrientation;
				if ( ( lightRotX > 360.0f ) || ( lightRotX < -360.0f ) )
				{
					lightRotX = 0.0f;
				}

				this->m_parentGM.m_renderMgr.GetDirectionalLight().m_yOrientation += speed * diffY;
				this->m_parentGM.m_renderMgr.GetSpotLight().m_yOrientation += speed * diffY;
				this->m_parentGM.m_renderMgr.GetProjector().m_yOrientation += speed * diffY;

				float lightRotY = this->m_parentGM.m_renderMgr.GetSpotLight().m_yOrientation;
				if ( ( lightRotY > 360.0f ) || ( lightRotY < -360.0f ) )
				{
					lightRotY = 0.0f;
				}

				float inclinationRadianValTemp = Math::DegreeToRadian( lightRotY );
				float azimuthRadianValTemp = Math::DegreeToRadian( lightRotX );

				Math::Vector4 lightOrientation;
				//formula for the spherical Cartesian coordinates
				lightOrientation.SetFloatX( -sin( inclinationRadianValTemp ) * sin( azimuthRadianValTemp ) );
				lightOrientation.SetFloatY( -cos( inclinationRadianValTemp ) );
				lightOrientation.SetFloatZ( sin( inclinationRadianValTemp ) * cos( azimuthRadianValTemp ) );
				lightOrientation.Normalize();

				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtViewDirectionVector( lightOrientation );
				this->m_parentGM.m_renderMgr.GetDirectionalLight().SetLookAtViewDirectionVector( lightOrientation );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtViewDirectionVector( lightOrientation );

				/*
				GameFramework::GameObject * gameObjEmptyTile = 0;

				//loop through the game objects of the state
				for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
				{
					//the current game object
					GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

					//validate if the game object is active
					if ( gameObj.IsActive() == false )
					{
						continue;
					}

					float posOffset = this->m_board.m_tileSize / 2.0F;
					float xPosGameObj = gameObj.GetPhysicsObj().GetPosition().GetFloatX();
					float yPosGameObj = gameObj.GetPhysicsObj().GetPosition().GetFloatY();

					//solve button
					if ( gameObj.GetIdentifier() == BUTTON_SOLVE_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) 
							&& this->m_board.m_lockButtons == false )
						{
							//enable tile animation
							this->m_board.m_stopAnimation = false;

							//lock the other buttons
							this->m_board.m_lockButtons = true;
							//lock the tiles
							this->m_board.m_lockTiles = true;	

							//clear initial state from the heap memory
							//this->CleanNode( this->m_nPuzzle->m_initialState );
							//clear target state from the heap memory
							//this->CleanNode( this->m_nPuzzle->m_targetState );

							//release the frontier from the heap memory
							this->m_nPuzzle->CleanFrontier();
							//release the explored set from the heap memory
							this->m_nPuzzle->CleanExploredSet();
							//release the left over resulting nodes from the heap memory
							this->m_nPuzzle->CleanResultingNodes();	
							//release the solution from the heap memory
							this->m_nPuzzle->CleanSolution();

							//set the initial state of the N Puzzle
							this->m_nPuzzle->SetState( this->m_board.m_currTileArrangement, this->m_board.m_tilesNumber + 1 );
							
							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//get start of frame
							this->m_timer.StartFrame();

							//solve the N Puzzle
							bool solutionFound = this->m_nPuzzle->SearchForSolution( this->m_nPuzzle->m_searchMethod );	

							//get end of frame
							this->m_timer.EndFrame();

							//float frameTime = this->m_timer.GetFrameTime();
							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

							if ( solutionFound == true && this->m_nPuzzle->m_solution.size() > 0 )
							{
								this->m_nPuzzle->m_solutionType = SOLUTION_WITH_DATA;

								this->m_board.m_holeReachedTarget = false;
								this->m_board.m_tileReachedTarget = false;

								//get the state data starting from the end of the solution vector
								unsigned int * stateData = this->m_nPuzzle->m_solution.back();
					
								//rearrange the tiles based on the state data
								this->ArrangeTiles( stateData );
							}
							else if ( solutionFound == true && this->m_nPuzzle->m_solution.size() == 0 )
							{
								this->m_nPuzzle->m_solutionType = SOLUTION_IS_INITIAL_STATE;
								//unlock the other buttons
								this->m_board.m_lockButtons = false;
								//unlock the tiles
								this->m_board.m_lockTiles = false;
							}
							else if ( solutionFound == false )
							{
								this->m_nPuzzle->m_solutionType = NO_SOLUTION;
								//unlock the other buttons
								this->m_board.m_lockButtons = false;
								//unlock the tiles
								this->m_board.m_lockTiles = false;
							}
							
							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////
					
					//search method button
					else if ( gameObj.GetIdentifier() == BUTTON_SEARCH_METHOD_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) 
							&& this->m_board.m_lockButtons == false )
						{
							if ( this->m_nPuzzle->m_searchMethod == DFS )
							{
								this->m_nPuzzle->m_searchMethod = ASTAR;
							}
							else
							{
								this->m_nPuzzle->m_searchMethod = DFS;
							}
							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////
					
					//reset tiles button
					else if ( gameObj.GetIdentifier() == BUTTON_RESET_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) 
							&& this->m_board.m_lockButtons == false )
						{
							//reset the tile board
							this->ResetTiles();
							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////
					
					//randomize tiles button
					else if ( gameObj.GetIdentifier() == BUTTON_RANDOM_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) 
							&& this->m_board.m_lockButtons == false )
						{
							//randomize the tile board
							this->RandomizeTiles();
							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////

					//animation speed button
					else if ( gameObj.GetIdentifier() == BUTTON_ANIMATION_SPEED_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) )
						{
							if ( this->m_board.m_tileSpeed == SLOW )
								this->m_board.m_tileSpeed = FAST;
							else if ( this->m_board.m_tileSpeed == FAST )
								this->m_board.m_tileSpeed = TELEPORT;
							else if ( this->m_board.m_tileSpeed == TELEPORT )
								this->m_board.m_tileSpeed = SLOW;

							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////
					
					//stress test button
					else if ( gameObj.GetIdentifier() == BUTTON_STRESS_TEST_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) 
							&& this->m_board.m_lockButtons == false )
						{
							//go to the next state
							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////
					
					//menu button
					else if ( gameObj.GetIdentifier() == BUTTON_MENU_GAMEOBJ )
					{
						//validate if the mouse world position is within the world coordinates of the button
						if ( ( worldX >= ( xPosGameObj - (posOffset * 1.75F) ) ) && ( worldX <= ( xPosGameObj + (posOffset * 1.5F) ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset / 2.75F) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) 
							&& this->m_board.m_lockButtons == false )
						{
							//go to the next state
							this->m_parentGM.SetNextState( "Menu" );
							break;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////

					//get the empty tile
					else if ( gameObj.GetIdentifier() == BLOCK_0_GAMEOBJ )
					{
						gameObjEmptyTile = &gameObj;
					}

					//validate tile blocks only if there is no animation for the block tiles and empty tile
					else if ( ( gameObj.GetIdentifier() == BLOCK_1_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_2_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_3_GAMEOBJ 
						|| gameObj.GetIdentifier() == BLOCK_4_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_5_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_6_GAMEOBJ
						|| gameObj.GetIdentifier() == BLOCK_7_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_8_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_9_GAMEOBJ
						|| gameObj.GetIdentifier() == BLOCK_10_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_11_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_12_GAMEOBJ
						|| gameObj.GetIdentifier() == BLOCK_13_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_14_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_15_GAMEOBJ 
						|| gameObj.GetIdentifier() == BLOCK_16_GAMEOBJ )
						&& ( gameObj.m_moveTile == false && gameObjEmptyTile->m_moveTile == false )
						&& ( this->m_board.m_holeReachedTarget == true && this->m_board.m_tileReachedTarget == true )
						)
					{
						//validate if the mouse world position is within the world coordinates of the tile
						if ( ( worldX >= ( xPosGameObj - posOffset ) ) && ( worldX <= ( xPosGameObj + posOffset ) ) 
							&& ( worldY >= ( yPosGameObj - (posOffset * 0.5F) ) ) && ( worldY <= ( yPosGameObj + (posOffset * 1.75F) ) ) )
						{
							//validate if tiles are adjacent
							if ( this->AreTilesAdjacent( gameObjEmptyTile, gameObj ) == true )
							{
								//swap the positions between the tiles
								this->SwapPositions( gameObjEmptyTile, gameObj, this->m_board.m_tileSpeed );
							}	

							break;
						}
					}

				}//end for loop

				*/

			}
			else if ( this->m_parentGM.m_input.IsPressed( InputMap::MOUSE_RIGHT ) )
			{
				//METHOD: spherical Cartesian coordinates
				float diffX = static_cast<float>( this->m_parentGM.m_input.GetMouseDX() );
				float diffY = static_cast<float>( this->m_parentGM.m_input.GetMouseDY() );

				this->m_parentGM.m_graphicsInterfacePtr->m_camera.m_xOrientation += speed * diffX;

				float cameraRotX = this->m_parentGM.m_graphicsInterfacePtr->m_camera.m_xOrientation;
				if ( ( cameraRotX > 360.0f ) || ( cameraRotX < -360.0f ) )
				{
					cameraRotX = 0.0f;
				}

				this->m_parentGM.m_graphicsInterfacePtr->m_camera.m_yOrientation += speed * diffY;

				float cameraRotY = this->m_parentGM.m_graphicsInterfacePtr->m_camera.m_yOrientation;
				if ( ( cameraRotY > 360.0f ) || ( cameraRotY < -360.0f ) )
				{
					cameraRotY = -90.0f;
				}

				float inclinationRadianValTemp = Math::DegreeToRadian( cameraRotY );
				float azimuthRadianValTemp = Math::DegreeToRadian( cameraRotX );

				Math::Vector4 cameraOrientation;
				//formula for the spherical Cartesian coordinates
				cameraOrientation.SetFloatX( -sin( inclinationRadianValTemp ) * sin( azimuthRadianValTemp ) );
				cameraOrientation.SetFloatY( -cos( inclinationRadianValTemp ) );
				cameraOrientation.SetFloatZ( sin( inclinationRadianValTemp ) * cos( azimuthRadianValTemp ) );
				cameraOrientation.Normalize();

				this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector( cameraOrientation );


				/*
				//METHOD #1 : use the converted screen to world coordinates as the new camera target
				float diffX = worldX - this->m_parentGM.m_graphicsInterfacePtr->GetWorldLastX();
				float diffY = worldY - this->m_parentGM.m_graphicsInterfacePtr->GetWorldLastY();

				float newCameraTargetX = ( this->m_parentGM.m_graphicsInterfacePtr->GetWorldLastX() + diffX );
				float newCameraTargetY = ( this->m_parentGM.m_graphicsInterfacePtr->GetWorldLastY() + diffY );
				this->m_parentGM.m_graphicsInterfacePtr->SetWorldLastX( newCameraTargetX );
				this->m_parentGM.m_graphicsInterfacePtr->SetWorldLastY( newCameraTargetY );

				//recompute the camera target and view vector
				Math::Vector4 newCameraTarget;
				newCameraTarget.SetFloatX( newCameraTargetX );
				newCameraTarget.SetFloatY( newCameraTargetY );
				newCameraTarget.SetFloatZ( this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraTarget().GetFloatZ() );
				//newCameraTarget.SetFloatZ( this->m_parentGM.m_graphicsInterfacePtr->m_projector.GetLookAtTarget().GetFloatZ() );
				//newCameraTarget.SetFloatZ( this->m_parentGM.m_graphicsInterfacePtr->m_spotLight.GetLookAtTarget().GetFloatZ() );
				newCameraTarget.SetFloatW( 1.0F );	

				this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraTarget( newCameraTarget );
				//this->m_parentGM.m_graphicsInterfacePtr->m_camera.RecomputeViewDirectionVector();
				this->m_parentGM.m_graphicsInterfacePtr->m_camera.SetCameraViewDirectionVector( 
					newCameraTarget - this->m_parentGM.m_graphicsInterfacePtr->m_camera.GetCameraPosition() );
				*/

				/*
				this->m_parentGM.m_graphicsInterfacePtr->m_projector.SetLookAtTarget( newCameraTarget );
				this->m_parentGM.m_graphicsInterfacePtr->m_projector.SetLookAtViewDirectionVector( 
					newCameraTarget - this->m_parentGM.m_graphicsInterfacePtr->m_projector.GetLookAtPosition() );
				*/
				/*
				this->m_parentGM.m_graphicsInterfacePtr->m_spotLight.SetLookAtTarget( newCameraTarget );
				this->m_parentGM.m_graphicsInterfacePtr->m_spotLight.SetLookAtViewDirectionVector( 
					newCameraTarget - this->m_parentGM.m_graphicsInterfacePtr->m_spotLight.GetLookAtPosition() );
				*/
			}
		}


		/*
		//fire a ball into the cage
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::SPACE ) )
		{
			//SMALL BALL
			this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BALL_GAMEOBJ, SPHERE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr,
				Math::Vector4( 0.0F, -2.5F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.15F, 0.15F, 0.15F, 0.0F ), 90.0F, 
				2.0F, 2.0F, 1.0F, 0.1F );
		}
		*/
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the behavior of the object

	\param dt
	the frame time
	\param gameObjVec
	the reference to the game object vector

	\return
	*/
	/******************************************************************************/
	void MyGeometryState::UpdateBehavior( float dt, GameFramework::GameObjectVector & gameObjVec )
	{
		//loop through the game objects
		for ( unsigned index = 0; index < gameObjVec.size(); ++index )
		{
			//the current game object
			GameFramework::GameObject& gameObj = gameObjVec.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false )
			{
				continue;
			}	

			switch ( gameObj.GetIdentifier() )
			{
				/*
			case LIGHT_SOURCE_GAMEOBJ:
				{
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//use the values from the plane for the missile game
					//set the velocity based on the computed direction
					gameObj.GetPhysicsObj().SetVelocityX( this->m_missileGame.m_plane.m_direction.x );
					gameObj.GetPhysicsObj().SetVelocityY( this->m_missileGame.m_plane.m_direction.y );
					//set the speed
					gameObj.GetPhysicsObj().SetMovementSpeed( this->m_missileGame.m_plane.m_speed );
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					//update the position
					Math::Vector4 position( gameObj.GetPhysicsObj().GetPosition() );
					//new position is: current position + normalized velocity * speed * elapsed time
					position += gameObj.GetPhysicsObj().GetVelocity() * gameObj.GetPhysicsObj().GetMovementSpeed() * dt; 
					gameObj.GetPhysicsObj().SetPosition( position );	

					//update the light position
					this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( position );
					this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( position );
					this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( position );

					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//update the plane position
					this->m_missileGame.m_plane.m_position.x = position.GetFloatX();
					this->m_missileGame.m_plane.m_position.y = position.GetFloatY();

					break;
				}				
				*/
			case MISSILE_GAMEOBJ:
				{									
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//use the values from the missile for the missile game
					//set the velocity based on the computed direction
					gameObj.GetPhysicsObj().SetVelocityX( this->m_missileGame.m_missile.m_direction.x );
					gameObj.GetPhysicsObj().SetVelocityY( this->m_missileGame.m_missile.m_direction.y );
					//set the speed
					gameObj.GetPhysicsObj().SetMovementSpeed( this->m_missileGame.m_missile.m_speed );
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
					//update the position
					Math::Vector4 position( gameObj.GetPhysicsObj().GetPosition() );
					//new position is: current position + normalized velocity * speed * elapsed time
					position += gameObj.GetPhysicsObj().GetVelocity() * gameObj.GetPhysicsObj().GetMovementSpeed() * dt; 
					gameObj.GetPhysicsObj().SetPosition( position );

					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//update the missile position
					this->m_missileGame.m_missile.m_position.x = position.GetFloatX();
					this->m_missileGame.m_missile.m_position.y = position.GetFloatY();					

					break;
				}				

			default:
				break;

			}//end switch	

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the behavior of the object
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::UpdateBehavior( float /*dt*/ )
	{
		//const GraphicsFramework::BaseGeometryBuilder* baseGeometryBuilderPtr = 0;
		
		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index )
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false)
			{
				continue;
			}			

			/*
			switch ( gameObj.GetIdentifier() )
			{

			case SATELLITE_GAMEOBJ:
				{
					//get the pointer to the base geometry builder based on the object type to be rendered
					baseGeometryBuilderPtr = this->m_parentGM.m_gameObjMgrPtr->RetrieveBaseGeometryBuilder( gameObj.GetType() );

					//update the game object
					this->m_parentGM.m_graphicsInterfacePtr->Update( dt, baseGeometryBuilderPtr );					

					break;
				}

			default:
				break;

			}//end switch	
			*/

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the collision behavior of the object
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::UpdateCollision( float startTime, float dt )
	{
		PhysicsFramework::CollisionDetection collision;
		float recomputedDt = dt;
		bool collideFlag = false;

		//size_t size = this->m_currGameObjList.size();		
		size_t size = this->m_lightedGameObjList.size();	

		//loop through the vector containing game objects
		for ( size_t x = 0; x < size; ++x )
		{
			//get the current object
			//GameFramework::GameObject & currentObj = this->m_currGameObjList[x];
			GameFramework::GameObject & currentObj = this->m_lightedGameObjList[x];

			//skip inactive objects
			if ( currentObj.IsActive() == false )
				continue;			

			//loop through the vector containing game objects
			for ( size_t y = 0; y < size; ++y )
			{
				//GameFramework::GameObject & obj = this->m_currGameObjList[y];
				GameFramework::GameObject & obj = this->m_lightedGameObjList[y];

				//skip inactive objects
				if ( obj.IsActive() == false )
					continue;	

				//validate that the current object is being compared to other objects other than itself
				if ( &currentObj != &obj )
				{					
					//validate between light source and wall
					if ( currentObj.GetIdentifier() == LIGHT_SOURCE_GAMEOBJ && obj.GetIdentifier() == WALL_GAMEOBJ )
					{
						//check for ball and wall collision
						collideFlag = collision.CheckCollisionCircleToWall( startTime, dt, recomputedDt, currentObj, obj, false, true );
						if ( collideFlag == true ) 
							break;
					}

					/*
					//validate between ball and wall
					if ( currentObj.GetIdentifier() == BALL_GAMEOBJ && obj.GetIdentifier() == WALL_GAMEOBJ )
					{
						//check for ball and wall collision
						collideFlag = collision.CheckCollisionCircleToWall( startTime, dt, recomputedDt, currentObj, obj, false, true );
						if ( collideFlag == true ) 
							break;
					}	
					
					//validate between ball and wall pillar
					if ( currentObj.GetIdentifier() == BALL_GAMEOBJ && obj.GetIdentifier() == WALLPILLAR_GAMEOBJ )
					{
						//check for ball and wall pillar collision
						collideFlag = collision.CheckCollisionCircleToWall( startTime, dt, recomputedDt, currentObj, obj, true, false );
						if ( collideFlag == true ) 
							break;
					}	

					//validate between ball and circle pillar
					if ( currentObj.GetIdentifier() == BALL_GAMEOBJ && obj.GetIdentifier() == CIRCLEPILLAR_GAMEOBJ )
					{
						//check for ball and circle pillar
						collideFlag = collision.CheckCollisionCircleToCirclePillar( startTime, dt, recomputedDt, currentObj, obj );
						if ( collideFlag == true ) 
							break;
					}

					//validate between ball and another ball
					if ( currentObj.GetIdentifier() == BALL_GAMEOBJ && obj.GetIdentifier() == BALL_GAMEOBJ )
					{
						//check for ball and another ball
						collideFlag = collision.CheckCollisionCircleToCircle( startTime, dt, recomputedDt, currentObj, obj );
						if ( collideFlag == true ) 
							break;
					}	
					*/
				}

			}//end for loop


			if ( currentObj.GetIdentifier() == LIGHT_SOURCE_GAMEOBJ )
			{
				if ( collideFlag == true )
				{
					//set the velocity based on the computed direction
					Math::Vector4 velocity( currentObj.GetPhysicsObj().GetVelocity() );
					velocity = currentObj.GetPhysicsObj().GetDirection();
					currentObj.GetPhysicsObj().SetVelocity( velocity );

					//update the plane direction
					this->m_missileGame.m_plane.m_direction.x = velocity.GetFloatX();
					this->m_missileGame.m_plane.m_direction.y = velocity.GetFloatY();
				}
				else
				{
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//use the values from the plane for the missile game
					//set the velocity based on the computed direction
					currentObj.GetPhysicsObj().SetVelocityX( this->m_missileGame.m_plane.m_direction.x );
					currentObj.GetPhysicsObj().SetVelocityY( this->m_missileGame.m_plane.m_direction.y );
					//set the speed
					currentObj.GetPhysicsObj().SetMovementSpeed( this->m_missileGame.m_plane.m_speed );
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//update the position
				Math::Vector4 position( currentObj.GetPhysicsObj().GetPosition() );
				//new position is: current position + normalized velocity * speed * elapsed time
				if ( collideFlag == true )
				{
					position += currentObj.GetPhysicsObj().GetVelocity() * currentObj.GetPhysicsObj().GetMovementSpeed() * recomputedDt; 
				}
				else
				{
					position += currentObj.GetPhysicsObj().GetVelocity() * currentObj.GetPhysicsObj().GetMovementSpeed() * dt;
				}
				currentObj.GetPhysicsObj().SetPosition( position );	
					
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//update the light position
				this->m_parentGM.m_renderMgr.GetSpotLight().SetLookAtPosition( position );
				this->m_parentGM.m_renderMgr.GetOmniLight().SetLookAtPosition( position );
				this->m_parentGM.m_renderMgr.GetProjector().SetLookAtPosition( position );

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//update the plane position
				this->m_missileGame.m_plane.m_position.x = position.GetFloatX();
				this->m_missileGame.m_plane.m_position.y = position.GetFloatY();

				//validate if object is out of bounds
				//this->InactivateOutOfBoundsObj( currentObj );

				break;
			}		

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The main draw function
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::DrawMain( float dt )
	{
		//start the graphics interface for drawing
		//this->m_parentGM.m_graphicsInterfacePtr->StartDrawing();		

		//get pointer to the matrix stack
		Utility::MatrixStack * matrixStack = &( this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack );	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set the projection matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::PROJECTION ) );
		matrixStack->MatrixMode( Utility::PROJECTION );
		//store the projection matrix
		Math::Mtx44 projMtx = matrixStack->Top();
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		
		//set the model view matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::MODELVIEW ) );	
		matrixStack->MatrixMode( Utility::MODELVIEW );
		//generate the camera view matrix
		Math::Mtx44 viewMtx = this->m_parentGM.m_graphicsInterfacePtr->m_camera.GenerateViewTransformMtx();		

		matrixStack->Push();			

			//pass the view transformation matrix
			matrixStack->MultMatrix ( viewMtx );				

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//set up the render effect
			GraphicsFramework::RENDER_EFFECT renderEffect = this->m_parentGM.m_renderEffect;

			//set up the lighting effect
			Light::LIGHT_EFFECT lightEffect = this->m_parentGM.m_lighting;
			GraphicsFramework::RENDER_EFFECT lightRenderEffect = this->m_parentGM.m_lightingEffect;

			//toggle projective texture
			char * projTexName = "";
			if ( this->m_parentGM.m_showProjTex == true )
			{
				projTexName = "EthanCochardLongboard";
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			

			//draw the objects based on the light and render effects

			//this->m_parentGM.m_renderMgr.DrawObjects( dt, GraphicsFramework::NORMAL, Light::NONE, projTexName, this->m_currGameObjList, projMtx, viewMtx );
			//this->m_parentGM.m_renderMgr.DrawObjects( dt, lightRenderEffect, lightEffect, projTexName, this->m_lightSourceGameObjList, projMtx, viewMtx );
			this->m_parentGM.m_renderMgr.DrawObjects( dt, lightRenderEffect, lightEffect, projTexName, this->m_lightedGameObjList, projMtx, viewMtx );
			//this->m_parentGM.m_renderMgr.DrawObjects( dt, GraphicsFramework::LIGHT, lightEffect, projTexName, this->m_lightedGameObjList, projMtx, viewMtx );
			//this->m_parentGM.m_renderMgr.DrawObjects( dt, GraphicsFramework::REFLECTIVE, lightEffect, projTexName, this->m_reflectiveGameObjList, projMtx, viewMtx );
			//this->m_parentGM.m_renderMgr.DrawObjects( dt, GraphicsFramework::REFRACTIVE, lightEffect, projTexName, this->m_refractiveGameObjList, projMtx, viewMtx );
			//this->m_parentGM.m_renderMgr.DrawObjects( dt, GraphicsFramework::REFRACTIVE_CD, lightEffect, projTexName, this->m_refractiveChromDispGameObjList, projMtx, viewMtx );
			//this->m_parentGM.m_renderMgr.DrawObjects( dt, GraphicsFramework::FRESNEL, lightEffect, projTexName, this->m_fresnelGameObjList, projMtx, viewMtx );				

			/*
			//draw the distance vector between city and plane
			glBegin( GL_LINES );
				glVertex3f( this->m_missileGame.m_missile.m_position.x, this->m_missileGame.m_missile.m_position.y, 0.0F );
				glVertex3f( this->m_missileGame.m_cities[0].position.x, this->m_missileGame.m_cities[0].position.y, 0.0F );
			glEnd();

			//draw the missile direction
			glBegin( GL_LINES );
				glVertex3f( this->m_missileGame.m_missile.m_position.x, this->m_missileGame.m_missile.m_position.y, 0.0F );
				glVertex3f( this->m_missileGame.m_missile.m_position.x + this->m_missileGame.m_missile.m_direction.x, 
					this->m_missileGame.m_missile.m_position.y + this->m_missileGame.m_missile.m_direction.y, 0.0F );
			glEnd();

			//draw the vector between the plane and the missile
			glBegin( GL_LINES );
				glVertex3f( this->m_missileGame.m_missile.m_position.x, this->m_missileGame.m_missile.m_position.y, 0.0F );
				glVertex3f( this->m_missileGame.m_plane.m_position.x, this->m_missileGame.m_plane.m_position.y, 0.0F );				
				//glVertex3f( this->m_missileGame.m_plane.m_vecBetwnPlaneAndMissile.x, this->m_missileGame.m_plane.m_vecBetwnPlaneAndMissile.y, 0.0F );				
			glEnd();
			*/

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			char * envMapName = "TestEnvMap";

			this->m_parentGM.m_renderMgr.DrawObjects( dt, envMapName, lightRenderEffect, renderEffect, lightEffect, projTexName, 
				this->m_fresnelGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );

			//this->m_parentGM.m_renderMgr.DrawObjects( dt, envMapName, GraphicsFramework::NORMAL, renderEffect, Light::NONE, projTexName, 
				//this->m_fresnelGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );

			char * frontFaceMapName = "TestFrontFaceEnvMap";
			char * backFaceMapName = "TestBackFaceEnvMap";

			this->m_parentGM.m_renderMgr.DrawObjects( dt, frontFaceMapName, backFaceMapName, GraphicsFramework::DUAL_PARABOLOID_GENERATION, 
				GraphicsFramework::DUAL_PARABOLOID_REFLECTIVE, lightEffect, projTexName, 
				this->m_reflectiveGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			/*
			this->m_parentGM.m_renderMgr.DrawObjects( dt, envMapName, GraphicsFramework::LIGHT, GraphicsFramework::REFLECTIVE, lightEffect, projTexName, 
				this->m_reflectiveGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );
			this->m_parentGM.m_renderMgr.DrawObjects( dt, envMapName, GraphicsFramework::LIGHT, GraphicsFramework::REFRACTIVE, lightEffect, projTexName, 
				this->m_refractiveGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );
			this->m_parentGM.m_renderMgr.DrawObjects( dt, envMapName, GraphicsFramework::LIGHT, GraphicsFramework::REFRACTIVE_CD, lightEffect, projTexName, 
				this->m_refractiveChromDispGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );
			this->m_parentGM.m_renderMgr.DrawObjects( dt, envMapName, GraphicsFramework::LIGHT, GraphicsFramework::FRESNEL, lightEffect, projTexName, 
				this->m_fresnelGameObjList, this->m_lightedGameObjList, projMtx, viewMtx );
			*/

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//draw the stencil
			//this->DrawStencil( dt );

			//draw the reflected objects
			//this->DrawReflection( dt );				

			//render/draw the objects
			//this->DrawObjects( dt );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//this step is important so we can render text and lines properly
			//retrieve the effect 
			GraphicsFramework::Effects * effectsPtr = this->m_parentGM.m_renderMgr.GetEffect( renderEffect );
			//disable vertex shader
			Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( "vtxShader" )->second;
			vtxShader.DisableProfile();
			//disable fragment shader
			Shader::Shader fragShader = effectsPtr->GetShaderMap().find( "fragShader" )->second;
			fragShader.DisableProfile();

		matrixStack->Pop();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//draw the text
		this->DrawTextToScreen( dt );			

		//end the graphics interface for drawing
		//this->m_parentGM.m_graphicsInterfacePtr->EndDrawing();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render/draw the text
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::DrawTextToScreen( float dt )
	{
		std::stringstream ss;

		Math::Mtx44 mvp;
		Math::Mtx44 projMtx;
		Math::Mtx44 tranformMtx;

		//get pointer to the matrix stack
		Utility::MatrixStack * matrixStack = &( this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//set the projection matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::PROJECTION ) );
		matrixStack->MatrixMode( Utility::PROJECTION );
		//store the projection matrix
		projMtx = matrixStack->Top();
		this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( projMtx );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set the model view matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::MODELVIEW ) );
		matrixStack->MatrixMode( Utility::MODELVIEW );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//dynamic camera
		Math::Mtx44 viewMtx = this->m_parentGM.m_graphicsInterfacePtr->m_camera.GenerateViewTransformMtx();	
		matrixStack->Push();

			//pass the view transformation matrix
			matrixStack->MultMatrix ( viewMtx );
			//concatenate to form the model-view-projection matrix
			mvp = projMtx * matrixStack->Top();	
			//explicitly call the graphics API to load the matrix transformation
			this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( mvp );			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			//display the damage of each zone
			this->m_missileGame.ShowZoneDamage( this->m_parentGM.m_graphicsInterfacePtr );

			//draw the missile direction
			if ( this->m_missileGame.m_setMissileDirection == true )
			{
				this->m_missileGame.DrawMissileLaunchDirection();
			}	

			//draw the missile path
			if ( this->m_missileGame.m_launchMissile == true )
			{
				this->m_missileGame.DrawMissilePath();
			}

			//draw the missile launch position
			if ( this->m_missileGame.m_launchMissile == false )
			{		
				POINT point;
				point.x = this->m_parentGM.m_input.GetMouseX();
				point.y = this->m_parentGM.m_input.GetMouseY();

				this->m_missileGame.DrawMissileLaunchPosition( this->m_parentGM.m_graphicsInterfacePtr, 
					static_cast<float>( point.x ), static_cast<float>( point.y ) );
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//DEBUG
			if ( this->m_parentGM.m_showWallNormal == true )
			{
				for ( unsigned index = 0; index < this->m_lightedGameObjList.size(); ++index )
				{
					GameFramework::GameObject & gameObj = this->m_lightedGameObjList.at( index );
					if ( gameObj.GetIdentifier() == MyGeometryGame::WALL_GAMEOBJ )
					{
						this->ShowNormal( gameObj );
					}
				}//end for loop
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		matrixStack->Pop();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//set the fixed camera
		Math::Vector4 cameraPosition ( 0.0F, 0.0F, 4.0F, 1.0f );
		Math::Vector4 target ( 0.0F, 0.0F, 0.0F, 1.0f );
		Math::Vector4 upVector  ( 0.0F, 1.0F, 0.0F, 0.0f );
		//set up the camera		
		Camera::Camera fixedCam;
		fixedCam.SetCameraPosition ( cameraPosition );
		fixedCam.SetCameraTarget ( target );
		fixedCam.SetWorldUpVector ( upVector );		
		//generate the camera view matrix
		viewMtx = fixedCam.GenerateViewTransformMtx();		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		matrixStack->Push();

			//tranformMtx.SetToTranslation( 0.0F, 0.0F, 1.0F );
			//pass the object transformation matrix					
			//matrixStack->MultMatrix ( tranformMtx );

			//pass the view transformation matrix
			matrixStack->MultMatrix ( viewMtx );

			//concatenate to form the model-view-projection matrix
			mvp = projMtx * matrixStack->Top();					

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//explicitly call the graphics API to load the matrix transformation
			this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( mvp );

			//this->InvokeVertexShader( "vtxShader", "modelViewProjMatrix", mvp.GetMatrixArr() );
			//this->InvokeFragmentShader( "fragShader", "texId", textureId );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						
			char * text = "";
			//unsigned int noOfNodes = 0;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			ss.str("");
			ss << "Frame rate : " << 1 / dt;		
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				10, this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() - 10, 
				GraphicsFramework::TS_SCREEN );

			text = "Damage : ";
			ss.str("");
			ss << text << this->m_missileGame.m_fuzzyLogicMissile.GetDamageValue(),	
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				10, 40, 
				GraphicsFramework::TS_SCREEN );

			text = "Fuel : ";
			ss.str("");
			ss << text << this->m_missileGame.m_fuzzyLogicMissile.GetFuelValue(),	
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 2.5F, 40, 
				GraphicsFramework::TS_SCREEN );

			text = "Attack : ";
			ss.str("");
			ss << text << this->m_missileGame.m_fuzzyLogicMissile.GetAttackValue(),	
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 200.0F, 40, 
				GraphicsFramework::TS_SCREEN );				

			/*
			if ( this->m_theBoard.m_searchDepth == 0 )
			{
				text = "Press any key from 1-9 to specify the maximum depth of MiniMax.";
				ss.str("");
				ss << text,	
					this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 4.0F, 60, 
					GraphicsFramework::TS_SCREEN );					
			}
			else
			{
				text = "The maximum MiniMax search depth : ";
				ss.str("");
				ss << text << this->m_theBoard.m_searchDepth,	
					this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 3.0F, 60, 
					GraphicsFramework::TS_SCREEN );	

				text = "Press SPACE to return to main menu.";
				ss.str("");
				ss << text,	
					this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 3.0F,
					this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() - 30, 
					GraphicsFramework::TS_SCREEN );	


				if ( this->m_theBoard.m_endGameState == GameFramework::WIN 
					|| this->m_theBoard.m_endGameState == GameFramework::LOSE
					|| this->m_theBoard.m_endGameState == GameFramework::DRAW )
				{
					text = "Press ENTER to restart the game.";
					ss.str("");
					ss << text,	
						this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
						this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 3.0F,
						this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() - 60, 
						GraphicsFramework::TS_SCREEN );
				}

				if ( this->m_theBoard.m_endGameState == GameFramework::WIN )
				{
					text = "COMPUTER WINS! Try again.";					
				}
				else if ( this->m_theBoard.m_endGameState == GameFramework::LOSE )
				{
					text = "YOU WIN! Good job!";
				}
				else if ( this->m_theBoard.m_endGameState == GameFramework::DRAW )
				{
					text = "DRAW! Try again.";					
				}
				else
				{
					if ( this->m_theBoard.m_ticTacToe.m_currentTurn == TicTacToe::COMPUTER )
					{
						text = "turn: COMPUTER";
					}
					else
					{
						text = "turn: PLAYER";
					}					
				}

				ss.str("");
				ss << text,	
					this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 2.5F, 90, 
					GraphicsFramework::TS_SCREEN );
			}
			*/


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//DEBUG
			/*
			ss.str("");
			ss << "Tile Arrangement : " << this->m_nPuzzle->GenerateStateKey( this->m_board.m_currTileArrangement );		
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				10, 50, 
				GraphicsFramework::TS_SCREEN );	

			ss.str("");
			ss << "Hole Position : " << this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ];		
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				10, 70, 
				GraphicsFramework::TS_SCREEN );	
			*/

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//BUTTONS
			/*
			if ( this->m_nPuzzle->m_searchMethod == DFS )
			{
				text = "DFS";
				noOfNodes = this->m_nPuzzle->m_frontier.size();
			}
			else if ( this->m_nPuzzle->m_searchMethod == ASTAR )
			{
				text = "A Star";
				//noOfNodes = this->m_nPuzzle->m_frontierSorted.size();
				noOfNodes = this->m_nPuzzle->m_frontier.size();
			}

			ss.str("");
			ss << "Search Method: ";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 235, 100,
				GraphicsFramework::TS_SCREEN );	
			ss.str("");
			ss << text;
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 175, 130,
				GraphicsFramework::TS_SCREEN, 0, 0, 255, 255 );	

			ss.str("");
			ss << "Reset";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 180, 210,
				GraphicsFramework::TS_SCREEN );	

			ss.str("");
			ss << "Randomize";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 200, 290,
				GraphicsFramework::TS_SCREEN );	

			ss.str("");
			ss << "Solve";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 180, 380,
				GraphicsFramework::TS_SCREEN );	

			if ( this->m_board.m_tileSpeed == SLOW )
				text = "SLOW";
			else if ( this->m_board.m_tileSpeed == FAST )
				text = "FAST";
			else if ( this->m_board.m_tileSpeed == TELEPORT )
				text = "TELEPORT";

			ss.str("");
			ss << "Animation Speed: ";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 250, 455, 
				GraphicsFramework::TS_SCREEN );	
			ss.str("");
			ss << text;
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 190, 485, 
				GraphicsFramework::TS_SCREEN, 0, 0, 255, 255 );

			ss.str("");
			ss << "Stress";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 180, 560,
				GraphicsFramework::TS_SCREEN );	

			ss.str("");
			ss << "Menu";
			this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
				this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() - 180, 650,
				GraphicsFramework::TS_SCREEN );
			*/

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//STATISTICS
			/*
			if ( this->m_nPuzzle->m_solutionType == SOLUTION_IS_INITIAL_STATE )
			{			
				ss.str("");
				ss << "The initial state is the same as the solution.";
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					10, ( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() / 2 ) + 325, 
					GraphicsFramework::TS_SCREEN, 255, 255, 255, 255 );	
			}
			else if ( this->m_nPuzzle->m_solutionType == NO_SOLUTION )
			{
				ss.str("");
				ss << "No solution found.";
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					10, ( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() / 2 ) + 325, 
					GraphicsFramework::TS_SCREEN, 255, 0, 0, 255 );	
			}
			else if ( this->m_nPuzzle->m_solutionType == SOLUTION_WITH_DATA )
			{
				ss.str("");
				ss << "No. of solution steps : " << this->m_nPuzzle->m_noOfSolutionSteps;
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					10, ( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() / 2 ) + 325, 
					GraphicsFramework::TS_SCREEN, 255, 255, 255, 255 );	

				ss.str("");
				ss << "Steps left : " << this->m_nPuzzle->m_solution.size();
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					10, ( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() / 2 ) + 350, 
					GraphicsFramework::TS_SCREEN, 255, 255, 255, 255 );	

				ss.str("");
				ss << "Solution time : " << this->m_timer.GetFrameTime() * 1000 << " msecs";		
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					( this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 2 ), ( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() / 2 ) + 325, 
					GraphicsFramework::TS_SCREEN, 255, 255, 255, 255 );

				ss.str("");
				ss << "No. of nodes generated : " << noOfNodes;
				this->m_parentGM.m_graphicsInterfacePtr->PrintText( ss.str().c_str(), 
					( this->m_parentGM.m_graphicsInterfacePtr->GetScreenWidth() / 2 ), ( this->m_parentGM.m_graphicsInterfacePtr->GetScreenHeight() / 2 ) + 350, 
					GraphicsFramework::TS_SCREEN, 255, 255, 255, 255 );
			}
			*/

		matrixStack->Pop();
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render/draw the objects
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::DrawObjects( float /*dt*/ )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//enable vertex shader ( reflective computation on the vertex shader )
		//Shader::Shader vtxShader = this->m_parentGM.m_graphicsInterfacePtr->GetShaderMap().find( "vtxShader" )->second;
		//vtxShader.BindProgram();
		//enable fragment shader
		//Shader::Shader fragShader = this->m_parentGM.m_graphicsInterfacePtr->GetShaderMap().find( "fragShader" )->second;
		//fragShader.BindProgram();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		//render/draw the object
		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false)
			{
				continue;
			}

			/*
			if ( gameObj.GetIdentifier() == MIRROR_GAMEOBJ )
			{
				glEnable( GL_BLEND );									// Enable Blending (Otherwise The Reflected Object Wont Show)
				glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );	// Blending Based On Source Alpha And 1 Minus Dest Alpha				
			}
			else if ( gameObj.GetIdentifier() == WINDOW_GAMEOBJ )
			{
				//glEnable(GL_POLYGON_STIPPLE);
				//glPolygonStipple();
				glEnable( GL_BLEND );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );					// Set Blending Mode To Mix Based On SRC Alpha
			}
			*/			

			//animate the tiles
			//this->AnimateTiles( dt, gameObj );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			//render the game object
			//this->RenderObject( gameObj );			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//FOR DEBUGGING ONLY
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//draw the normal of the wall
			if ( this->m_parentGM.m_showWallNormal == true )
			{
				this->ShowNormal( gameObj );
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render/draw the stencil
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::DrawStencil( float /*dt*/ )
	{
		//Disable color and depth buffers
		glColorMask( false, false, false, false );			//Disable writting in color buffer
		glDepthMask( false );								//Disable writting in depth buffer

		glEnable( GL_STENCIL_TEST );						//Enable Stencil test

		/*
		set front and back function and reference value for stencil testing
		parameters:
		func
		Specifies the test function. Eight symbolic constants are valid: GL_NEVER, GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL, GL_NOTEQUAL, and GL_ALWAYS. The initial value is GL_ALWAYS.
		ref
		Specifies the reference value for the stencil test. ref is clamped to the range 0 2 n - 1 , where n is the number of bitplanes in the stencil buffer. The initial value is 0.
		mask
		Specifies a mask that is ANDed with both the reference value and the stored stencil value when the test is done. The initial value is all 1's.
		*/
		//Test always success, value written 1
		glStencilFunc( GL_ALWAYS, 1, 1 );                   

		/*
		set front and back stencil test actions
		parameters:
		sfail
		Specifies the action to take when the stencil test fails. Eight symbolic constants are accepted: GL_KEEP, GL_ZERO, GL_REPLACE, GL_INCR, GL_INCR_WRAP, GL_DECR, GL_DECR_WRAP, and GL_INVERT. The initial value is GL_KEEP.
		dpfail
		Specifies the stencil action when the stencil test passes, but the depth test fails. dpfail accepts the same symbolic constants as sfail. The initial value is GL_KEEP.
		dppass
		Specifies the stencil action when both the stencil test and the depth test pass, or when the stencil test passes and either there is no depth buffer or depth testing is not enabled. dppass accepts the same symbolic constants as sfail. The initial value is GL_KEEP.
		*/
		//Stencil & Depth test passes => replace existing value
		glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE );


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//render/draw the object
		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false)
			{
				continue;
			}

			//the draw the mirror to the stencil
			if ( gameObj.GetIdentifier() == MIRROR_GAMEOBJ )
			{
				//render the game object
				//this->RenderObject( gameObj );

				break;
			}

		}//end for loop
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		glDepthMask( true );
		glColorMask( true, true, true, true );	//Enable drawing of r, g, b & a		
		glDisable( GL_STENCIL_TEST );			//Disable Stencil test	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render/draw the reflection objects
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::DrawReflection( float /*dt*/ )
	{
		//set back face culling
		glFrontFace( GL_CW );
		glCullFace( GL_BACK );

		glEnable( GL_STENCIL_TEST );		//Enable Stencil test	
		//GL_EQUAL: Passes if ( ref & mask ) = ( stencil & mask )
		glStencilFunc( GL_EQUAL, 1, 1 );				//Draw only where stencil buffer is 1
		glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );		//Stencil buffer read only

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
		//enable reflection 
		this->ActivateReflection();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//render/draw the object
		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false)
			{
				continue;
			}

			if ( gameObj.GetIdentifier() == WINDOW_GAMEOBJ )
			{
				glEnable( GL_BLEND );
				glBlendFunc( GL_SRC_ALPHA, GL_ONE );			// Set Blending Mode To Mix Based On SRC Alpha
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			if ( gameObj.GetIdentifier() != MIRROR_GAMEOBJ )
			{
				//render the game object
				//this->RenderObject( gameObj );
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
			if ( gameObj.GetIdentifier() == WINDOW_GAMEOBJ )
			{
				glDisable( GL_BLEND );
			}

		}//end for loop
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//disable reflection
		this->DeactivateReflection();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		glDisable( GL_STENCIL_TEST );		//Disable Stencil test	

		//set back face culling
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Show the normals of the game object
	\param gameObj
	the game object
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::ShowNormal( GameFramework::GameObject & gameObj ) const
	{
		if ( gameObj.GetIdentifier() == WALL_GAMEOBJ || gameObj.GetIdentifier() == WALLPILLAR_GAMEOBJ )
		{
			Math::Vector4 normalStartPt = gameObj.GetPhysicsObj().GetTail();
			Math::Vector4 normalEndPt = normalStartPt + gameObj.GetPhysicsObj().GetNormal();
			Math::Vector4 normalVec = normalEndPt - normalStartPt;

			//explicitly call graphics API function to load the matrix
			//this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( matrixStack->Top() );

			glLineWidth( 2.0 );
			glBegin(GL_LINES);
				glVertex3f( normalStartPt.GetFloatX(), normalStartPt.GetFloatY(), 0.0F ); // origin of the FIRST line
				glVertex3f( normalEndPt.GetFloatX(), normalEndPt.GetFloatY(), 0.0F ); // ending point of the FIRST line
			glEnd( );	
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Inactivate objects which are out of bounds
	\param gameObj
	the game object
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InactivateOutOfBoundsObj( GameFramework::GameObject & gameObj )
	{
		float xPos = gameObj.GetPhysicsObj().GetPosition().GetFloatX();
		float yPos = gameObj.GetPhysicsObj().GetPosition().GetFloatY();

		//check if the particles went off the screen
		if ( xPos > this->m_parentGM.m_graphicsInterfacePtr->GetWorldMaxX()
			|| yPos > this->m_parentGM.m_graphicsInterfacePtr->GetWorldMaxY()
			|| xPos < this->m_parentGM.m_graphicsInterfacePtr->GetWorldMinX()
			|| yPos < this->m_parentGM.m_graphicsInterfacePtr->GetWorldMinY() )
		{
			//set the particles to inactive
			gameObj.SetActive( false );
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Enables reflection in the scene if there is a mirror object
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::ActivateReflection( void )
	{
		Math::Mtx44 reflectionMtx;

		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false)
			{
				continue;
			}

			if ( gameObj.GetIdentifier() == MIRROR_GAMEOBJ )
			{
				//set the planar reflection
				reflectionMtx.SetPlanarReflection( gameObj.GetPhysicsObj().GetCenterPt(), gameObj.GetPhysicsObj().GetNormal() );
				
				//pass the reflection matrix
				this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack.MatrixMode( Utility::MODELVIEW );
				this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack.Push();
				this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack.MultMatrix( reflectionMtx );

				break;
			}			

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Disables reflection in the scene
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::DeactivateReflection( void )
	{
		this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack.MatrixMode( Utility::MODELVIEW );
		this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack.Pop();
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Initializes the tile board
	\param numOfTilesPerSide
	the number of tiles per side
	\param boardSideLength
	the length of the side of the board
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::InitializeTileBoard( const unsigned numOfTilesPerSide, const float boardSideLength )
	{
		//initialize the board values
		this->m_board.m_boardSideLength = boardSideLength;
		this->m_board.m_numOfTilesPerSide = numOfTilesPerSide;
		this->m_board.m_tileSize = this->m_board.m_boardSideLength / this->m_board.m_numOfTilesPerSide;

		this->m_board.m_maxRow = static_cast<unsigned>( this->m_board.m_numOfTilesPerSide );
		this->m_board.m_maxCol = static_cast<unsigned>( this->m_board.m_numOfTilesPerSide );
		this->m_board.m_tilesNumber = this->m_board.m_maxRow * this->m_board.m_maxCol;

		this->m_board.m_xLimit = this->m_board.m_boardSideLength / 2.0F;
		this->m_board.m_yLimit = this->m_board.m_boardSideLength / 2.0F;		

		this->m_board.m_holeReachedTarget = true;
		this->m_board.m_tileReachedTarget = true;

		this->m_board.m_tileSpeed = SLOW;

		this->m_board.m_lockButtons = false;
		this->m_board.m_lockTiles = false;
		this->m_board.m_stopAnimation = false;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the tiles
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::CreateTiles( void )
	{
		float xPos = -this->m_board.m_xLimit + ( this->m_board.m_tileSize / 2.0F );
		float yPos = this->m_board.m_yLimit - ( this->m_board.m_tileSize / 2.0F );

		//allocate in the heap memory
		//add one to the buffer size to include the last index containing the hole position
		this->m_board.m_currTileArrangement = new unsigned int[ this->m_board.m_tilesNumber + 1 ];

		unsigned index = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_board.m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_board.m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				index = ( j * this->m_board.m_maxCol ) + i;

				//set the index positions of the blocks
				this->m_board.m_currTileArrangement[index] = index;				

				//on the first iteration
				if ( index == 0 )
				{
					//EMPTY BLOCK
					this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( index, CUBE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
						Math::Vector4( xPos, yPos, -0.5F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), 
						Math::Vector4( this->m_board.m_tileSize, this->m_board.m_tileSize, 0.25F, 0.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ),
						static_cast<float>( this->m_board.m_tileSpeed ), 0.0F, 0.0F, 1.0F, false, j, i, index );
				}
				else
				{
					//TILE BLOCK
					this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( index, index, this->m_parentGM.m_graphicsInterfacePtr, 
						Math::Vector4( xPos, yPos, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), 
						Math::Vector4( this->m_board.m_tileSize, this->m_board.m_tileSize, this->m_board.m_tileSize, 0.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ),
						static_cast<float>( this->m_board.m_tileSpeed ), 0.0F, 0.0F, 1.0F, false, j, i, index );
				}	

				//increment the x position
				xPos += this->m_board.m_tileSize;

			} //end for loop	

			//decrement the y position
			yPos -= this->m_board.m_tileSize;
			
			//reset the x position
			xPos = -this->m_board.m_xLimit + ( this->m_board.m_tileSize / 2.0F );

		}//end for loop

		//set the initial hole position
		this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ] = 0;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Arranges the tiles
	\param tileArrangementData
	the tile arrangement data from where the tiles will follow this arrangement order
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::ArrangeTiles( const unsigned int * tileArrangementData )
	{
		bool holeFound = false;
		bool tileFound = false;

		//get the current/original hole position
		unsigned int currHolePos = this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ];
		//use the current/original hole position to check the new tile it contains based on the new tile arrangement data
		unsigned int newTile = tileArrangementData[ currHolePos ];

		GameFramework::GameObject * gameObjEmptyTile = 0;

		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false )
			{
				continue;
			}

			//get the hole / empty tile
			if ( gameObj.GetIdentifier() == BLOCK_0_GAMEOBJ )
			{
				gameObjEmptyTile = &gameObj;
				holeFound = true;
			}
			//get the block tile			
			else if ( gameObj.GetIdentifier() == newTile )
			{
				tileFound = true;
			}
			//validate if the new tile value is also the hole
			else if ( newTile == BLOCK_0_GAMEOBJ )
			{
				//tileFound = true;
			}

			//if the hole and the tile to be swapped with are found
			if ( holeFound == true && tileFound == true )
			{
				//swap the hole and the tile
				this->SwapPositions( gameObjEmptyTile, gameObj, this->m_board.m_tileSpeed );
				break;
			}

		}//end for loop	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Plots the tiles on the board
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::PlotTiles( void )
	{
		float xPos = -this->m_board.m_xLimit + ( this->m_board.m_tileSize / 2.0F );
		float yPos = this->m_board.m_yLimit - ( this->m_board.m_tileSize / 2.0F );

		unsigned indexPos = 0;
		unsigned tileValue = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_board.m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_board.m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				indexPos = ( j * this->m_board.m_maxCol ) + i;
				tileValue = this->m_board.m_currTileArrangement[indexPos];

				//loop through the game objects of the state
				for ( size_t indexGO = 0; indexGO < this->m_currGameObjList.size(); ++indexGO)
				{
					//the current game object
					GameFramework::GameObject& gameObj = this->m_currGameObjList.at( indexGO );

					//reposition the tile game object
					if ( gameObj.GetIdentifier() == tileValue )
					{
						gameObj.GetPhysicsObj().SetPositionX( xPos );
						gameObj.GetPhysicsObj().SetPositionY( yPos );
						gameObj.SetRow( j );
						gameObj.SetColumn( i );
						gameObj.SetIndex( indexPos );
						break;
					}
				}//end for loop

				//increment the x position
				xPos += this->m_board.m_tileSize;

			} //end for loop	

			//decrement the y position
			yPos -= this->m_board.m_tileSize;
			
			//reset the x position
			xPos = -this->m_board.m_xLimit + ( this->m_board.m_tileSize / 2.0F );

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Resets the tiles on the board
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::ResetTiles( void )
	{
		unsigned index = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_board.m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_board.m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				index = ( j * this->m_board.m_maxCol ) + i;

				//set the index positions of the blocks
				this->m_board.m_currTileArrangement[index] = index;		

			}//end for loop
		}//end for loop

		//set the reset hole position
		this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ] = 0;

		//plot the tiles accordingly
		this->PlotTiles();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Randomizes the tiles on the board
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::RandomizeTiles( void )
	{
		unsigned holePosition = 0;

		unsigned index = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_board.m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_board.m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				index = ( j * this->m_board.m_maxCol ) + i;

				//set the index positions of the blocks
				this->m_board.m_currTileArrangement[index] = index;		

			}//end for loop
		}//end for loop

		//set the reset hole position
		this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ] = 0;

		//loop through the tiles of the board again
		for ( unsigned index = 0; index < this->m_board.m_tilesNumber; ++index )
		{
			unsigned randomPosVal = Utility::GenerateRandomNumber( this->m_board.m_tilesNumber );
			unsigned randomTileVal = this->m_board.m_currTileArrangement[ randomPosVal ];

			unsigned tilePos = this->m_board.m_tilesNumber - 1 - index;
			unsigned tileVal = this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber - 1 - index ];
			
			//swap the values
			this->m_board.m_currTileArrangement[ randomPosVal ] = tileVal;
			this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber - 1 - index ] = randomTileVal;	

			//check if its a hole then get the hole position
			if ( randomTileVal == BLOCK_0_GAMEOBJ )
			{
				holePosition = tilePos;
			}
			else if ( tileVal == BLOCK_0_GAMEOBJ )
			{
				holePosition = randomPosVal;			
			}

		}//end for loop

		//set the hole position
		this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ] = holePosition;

		//plot the tiles accordingly
		this->PlotTiles();
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Generates random tiles on the board
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::GenerateRandomTiles( void )
	{
		unsigned randomVal = 0;
		unsigned holePosition = 0;

		//initialize the tiles
		for ( unsigned indexVal = 0; indexVal < this->m_board.m_tilesNumber; ++indexVal )
		{
			this->m_board.m_currTileArrangement[indexVal] = this->m_board.m_tilesNumber;
		}//end for loop

		unsigned index = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_board.m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_board.m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				index = ( j * this->m_board.m_maxCol ) + i;

				//validate if the random number is already existing
				do
				{
					//generate a random number
					randomVal = Utility::GenerateRandomNumber( this->m_board.m_tilesNumber );
				}
				while ( this->IsTileExisting( randomVal ) == true );

				//check if it is the hole
				if ( randomVal == BLOCK_0_GAMEOBJ )
				{
					//store the hole position
					holePosition = index;
				}

				//set the tile values
				this->m_board.m_currTileArrangement[index] = randomVal;
				
			}//end for loop
		}//end for loop

		//set the hole position
		this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ] = holePosition;

		//plot the tiles accordingly
		this->PlotTiles();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validates if the tile is existing
	\param tileNumber
	the tile number
	\return bool
	if true, the tile is existing, otherwise false
	*/
	/******************************************************************************/
	bool MyGeometryState::IsTileExisting( const unsigned int tileNumber ) const
	{
		bool tileExisting = false;

		//validate if the tile number is already existing
		for ( unsigned indexVal = 0; indexVal < this->m_board.m_tilesNumber; ++indexVal )
		{
			if ( this->m_board.m_currTileArrangement[indexVal] == tileNumber )
			{
				tileExisting = true;
				break;
			}					
		}

		return tileExisting;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Animates the tiles by changing its position based on the movement direction
	\param gameObj
	the tile game object
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::AnimateTiles( float /*dt*/, GameFramework::GameObject& gameObj )
	{
		//animate the tiles
		if ( ( gameObj.GetIdentifier() == BLOCK_1_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_2_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_3_GAMEOBJ 
			|| gameObj.GetIdentifier() == BLOCK_4_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_5_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_6_GAMEOBJ
			|| gameObj.GetIdentifier() == BLOCK_7_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_8_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_9_GAMEOBJ
			|| gameObj.GetIdentifier() == BLOCK_10_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_11_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_12_GAMEOBJ
			|| gameObj.GetIdentifier() == BLOCK_13_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_14_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_15_GAMEOBJ 
			|| gameObj.GetIdentifier() == BLOCK_16_GAMEOBJ || gameObj.GetIdentifier() == BLOCK_0_GAMEOBJ ) 
			&& gameObj.m_moveTile == true
			)
		{
			//set the velocity based on the computed direction
			Math::Vector4 velocity( gameObj.GetPhysicsObj().GetVelocity() );
			velocity = gameObj.GetPhysicsObj().GetDirection();
			gameObj.GetPhysicsObj().SetVelocity( velocity );

			//update the position
			Math::Vector4 position( gameObj.GetPhysicsObj().GetPosition() );
			//new position is: current position + normalized velocity * speed * elapsed time
			//position += gameObj.GetPhysicsObj().GetVelocity() * gameObj.GetPhysicsObj().GetMovementSpeed() * dt; 
			position += gameObj.GetPhysicsObj().GetVelocity() * gameObj.GetPhysicsObj().GetMovementSpeed(); 

			//validate the new position with the target position based on the direction
			if ( gameObj.m_moveTileDirection == GameFramework::UP )
			{
				if ( position.GetFloatY() > gameObj.m_targetYpos )
				{
					position.SetFloatY( gameObj.m_targetYpos );	
					//validate the target position
					this->ValidateTargetPosition( gameObj );
				}
			}
			else if ( gameObj.m_moveTileDirection == GameFramework::DOWN )
			{
				if ( position.GetFloatY() < gameObj.m_targetYpos )
				{
					position.SetFloatY( gameObj.m_targetYpos );	
					//validate the target position
					this->ValidateTargetPosition( gameObj );
				}
			}
			else if ( gameObj.m_moveTileDirection == GameFramework::LEFT )
			{
				if ( position.GetFloatX() < gameObj.m_targetXpos )
				{
					position.SetFloatX( gameObj.m_targetXpos );	
					//validate the target position
					this->ValidateTargetPosition( gameObj );
				}
			}
			else if ( gameObj.m_moveTileDirection == GameFramework::RIGHT )
			{
				if ( position.GetFloatX() > gameObj.m_targetXpos )
				{
					position.SetFloatX( gameObj.m_targetXpos );	
					//validate the target position
					this->ValidateTargetPosition( gameObj );
				}
			}					

			gameObj.GetPhysicsObj().SetPosition( position );
				
		}	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validates whether the tile game object has reached its target desitination
	\param gameObj
	the tile game object
	\return bool
	if true, the target destination has been reached, otherwise false
	*/
	/******************************************************************************/
	bool MyGeometryState::ValidateTargetPosition( GameFramework::GameObject & gameObj )
	{
		bool targetPostionValidated = false;

		//stop the animation once the hole or tile has reached their target position
		if ( gameObj.m_moveTileDirection == GameFramework::RIGHT || gameObj.m_moveTileDirection == GameFramework::LEFT )
		{
			gameObj.GetPhysicsObj().SetVelocityX( 0.0F );
			gameObj.GetPhysicsObj().SetDirectionX( 0.0F );
		}
		else if ( gameObj.m_moveTileDirection == GameFramework::UP || gameObj.m_moveTileDirection == GameFramework::DOWN )
		{
			gameObj.GetPhysicsObj().SetVelocityY( 0.0F );
			gameObj.GetPhysicsObj().SetDirectionY( 0.0F );
		}

		gameObj.m_moveTileDirection = GameFramework::NONE;
		gameObj.m_moveTile = false;

		if ( gameObj.GetIdentifier() == BLOCK_0_GAMEOBJ )
		{
			this->m_board.m_holeReachedTarget = true;
		}
		else				
		{
			this->m_board.m_tileReachedTarget = true;
		}


		//if both the hole and the tile reached their target positions
		if ( this->m_board.m_holeReachedTarget == true && this->m_board.m_tileReachedTarget == true )
		{
			if ( this->m_board.m_stopAnimation == false )
			{
				if ( this->m_nPuzzle->m_solution.size() > 0 )
				{
					//pop the recently read state data
					this->m_nPuzzle->m_solution.pop_back();

					if ( this->m_nPuzzle->m_solution.size() > 0 )
					{
						//get the state state data starting from the end of the solution vector
						unsigned int * stateData = this->m_nPuzzle->m_solution.back();
					
						//rearrange the tiles based on the state data
						this->ArrangeTiles( stateData );

						//reset the target position flags
						this->m_board.m_holeReachedTarget = false;
						this->m_board.m_tileReachedTarget = false;
					}
					else
					{
						//unlock the buttons after the tile animation
						this->m_board.m_lockButtons = false;
						//unlock the tiles for manual movement
						this->m_board.m_lockTiles = false;
					}
				}

			}
			else
			{
				//unlock the buttons after the tile animation
				this->m_board.m_lockButtons = false;
				//unlock the tiles for manual movement
				this->m_board.m_lockTiles = false;
			}

			targetPostionValidated = true;
		}

		return targetPostionValidated;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks if two tiles are adjacent to each other
	\param emptyTile
	the hole game object
	\param blockTile
	the block tile object
	\return bool
	if true, both the game object are adjacent to each other, otherwise false
	*/
	/******************************************************************************/
	bool MyGeometryState::AreTilesAdjacent( const GameFramework::GameObject * emptyTile, const GameFramework::GameObject & blockTile ) const
	{
		bool areTilesAdjacent = false; 

		unsigned colDiff = 0;
		unsigned rowDiff = 0;							

		//if the block tile and the empty tile are on the same row
		if ( blockTile.GetRow() == emptyTile->GetRow() )
		{
			//check if the tiles are adjacent to each other
			colDiff = blockTile.GetColumn() - emptyTile->GetColumn();
			if ( colDiff == 1 || colDiff == -1 )
			{
				areTilesAdjacent = true;
			}
								
		}
		//if the block tile and the empty tile are on the same column
		else if ( blockTile.GetColumn() == emptyTile->GetColumn() ) 
		{
			//check if the tiles are adjacent to each other
			rowDiff = blockTile.GetRow() - emptyTile->GetRow();
			if ( rowDiff == 1 || rowDiff == -1 )
			{
				areTilesAdjacent = true;
			}
		}

		return areTilesAdjacent;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Swaps the positions of two tile game objects
	\param emptyTile
	the hole game object
	\param blockTile
	the block tile object
	\param tileSpeed
	the tile movement speed
	\return
	*/
	/******************************************************************************/
	void MyGeometryState::SwapPositions( GameFramework::GameObject * emptyTile, GameFramework::GameObject & blockTile, const TILESPEED tileSpeed )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////						 
		//SWAPPING THE INDICES
		unsigned blockTileIndex = blockTile.GetIndex();
		unsigned emptyTileIndex = emptyTile->GetIndex();

		//update the hole and tile values of the tile arrangement data
		this->m_board.m_currTileArrangement[ emptyTileIndex ] =  blockTile.GetIdentifier();
		this->m_board.m_currTileArrangement[ blockTileIndex ] = emptyTile->GetIdentifier();

		//set the new index of the empty tile
		//the last element indicates the empty tile index
		//this->m_board.m_currTileArrangement[ this->m_board.m_currTileArrangement.size() - 1 ] = blockTileIndex;
		this->m_board.m_currTileArrangement[ this->m_board.m_tilesNumber ] = blockTileIndex;

		//swap the index of the tiles
		blockTile.SetIndex( emptyTileIndex );
		emptyTile->SetIndex( blockTileIndex );


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SWAPPING ROWS AND COLUMNS

		unsigned blockTileRow = 0;
		unsigned blockTileColumn = 0;
		unsigned emptyTileRow = 0;
		unsigned emptyTileColumn = 0;

		emptyTileRow = emptyTile->GetRow();
		emptyTileColumn = emptyTile->GetColumn();
		blockTileRow = blockTile.GetRow();
		blockTileColumn = blockTile.GetColumn();		

		//swap the row and column values
		emptyTile->SetRow( blockTileRow );
		emptyTile->SetColumn( blockTileColumn );
		blockTile.SetRow( emptyTileRow );
		blockTile.SetColumn( emptyTileColumn );	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SWAPPING POSITIONS

		float emptyTileXpos = 0.0F;
		float emptyTileYpos = 0.0F;
		float emptyTileZpos = 0.0F;

		float blockTileXpos = 0.0F;
		float blockTileYpos = 0.0F;
		float blockTileZpos = 0.0F;

		emptyTileXpos = emptyTile->GetPhysicsObj().GetPosition().GetFloatX();
		emptyTileYpos = emptyTile->GetPhysicsObj().GetPosition().GetFloatY();
		emptyTileZpos = emptyTile->GetPhysicsObj().GetPosition().GetFloatZ();

		blockTileXpos = blockTile.GetPhysicsObj().GetPosition().GetFloatX();
		blockTileYpos = blockTile.GetPhysicsObj().GetPosition().GetFloatY();
		blockTileZpos = blockTile.GetPhysicsObj().GetPosition().GetFloatZ();

		//swap only the x and y positions						
		emptyTile->m_targetXpos = blockTileXpos;
		emptyTile->m_targetYpos = blockTileYpos;		
		blockTile.m_targetXpos = emptyTileXpos;
		blockTile.m_targetYpos = emptyTileYpos;

		/*
		if ( tileSpeed == TELEPORT )
		{
		//instantaneously swap the hole and the tile
		//emptyTile->GetPhysicsObj().SetPosition( blockTileXpos, blockTileYpos, emptyTileZpos );
		emptyTile->GetPhysicsObj().SetPositionX( blockTileXpos );
		emptyTile->GetPhysicsObj().SetPositionY( blockTileYpos );
		//blockTile.GetPhysicsObj().SetPosition( emptyTileXpos, emptyTileYpos, blockTileZpos );
		blockTile.GetPhysicsObj().SetPositionX( emptyTileXpos );
		blockTile.GetPhysicsObj().SetPositionY( emptyTileYpos );		
		}
		else if ( tileSpeed == SLOW || tileSpeed == FAST )
		{
		*/
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//SETTING THE MOVEMENT DIRECTION OF THE TILES

		float posDiff = 0.0F;
		//float framePerSec = 1.0F;
		float directionVal = this->m_board.m_tileSize / SPEED_DAMP;

		//same row
		if ( emptyTileRow == blockTileRow )
		{
			//set the direction values of the tile movement
			posDiff = blockTileXpos - emptyTileXpos;

			if ( Math::FloatValueSame( posDiff, 0.0F ) == false )
			{
				if ( posDiff < 0.0F )
				{
					directionVal = -directionVal;
					blockTile.m_moveTileDirection = GameFramework::RIGHT;
					emptyTile->m_moveTileDirection = GameFramework::LEFT;
				}
				else
				{
					blockTile.m_moveTileDirection = GameFramework::LEFT;
					emptyTile->m_moveTileDirection = GameFramework::RIGHT;
				}
			}

			//directionVal = posDiff / framePerSec;
			blockTile.GetPhysicsObj().SetDirectionX( -directionVal );
			emptyTile->GetPhysicsObj().SetDirectionX( directionVal );
		}
		//same column
		else if ( emptyTileColumn == blockTileColumn )
		{
			//set the direction values of the tile movement
			posDiff = blockTileYpos - emptyTileYpos;

			if ( Math::FloatValueSame( posDiff, 0.0F ) == false )
			{
				if ( posDiff < 0.0F )
				{
					directionVal = -directionVal;
					blockTile.m_moveTileDirection = GameFramework::UP;
					emptyTile->m_moveTileDirection = GameFramework::DOWN;
				}
				else
				{
					blockTile.m_moveTileDirection = GameFramework::DOWN;
					emptyTile->m_moveTileDirection = GameFramework::UP;
				}
			}

			//directionVal = posDiff / framePerSec;
			blockTile.GetPhysicsObj().SetDirectionY( -directionVal );
			emptyTile->GetPhysicsObj().SetDirectionY( directionVal );
		}

		//set the speed
		blockTile.GetPhysicsObj().SetMovementSpeed( static_cast<float>( tileSpeed ) );
		emptyTile->GetPhysicsObj().SetMovementSpeed( static_cast<float>( tileSpeed ) );

		blockTile.m_moveTile = true;
		emptyTile->m_moveTile = true;

		//}//end if ( tileSpeed == SLOW || tileSpeed == FAST )					
	}

} //end namespace MyGeometryGame