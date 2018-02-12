/******************************************************************************/
/*!
\file MyGeometryOM.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 24/12/2011
\brief
This is the geometry object manager that will manage the generation of goemetries

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef MYGEOMETRY_OM_H
#define MYGEOMETRY_OM_H
////////////////////////////////////////////////////////////////////////////////

#include "Game\GameObjectManager.h"


namespace MyGeometryGame
{
	enum GameObjectName
	{
		BLOCK_0_GAMEOBJ,
		BLOCK_1_GAMEOBJ,
		BLOCK_2_GAMEOBJ,
		BLOCK_3_GAMEOBJ,
		BLOCK_4_GAMEOBJ,
		BLOCK_5_GAMEOBJ,
		BLOCK_6_GAMEOBJ,
		BLOCK_7_GAMEOBJ,
		BLOCK_8_GAMEOBJ,
		BLOCK_9_GAMEOBJ,
		BLOCK_10_GAMEOBJ,
		BLOCK_11_GAMEOBJ,
		BLOCK_12_GAMEOBJ,
		BLOCK_13_GAMEOBJ,
		BLOCK_14_GAMEOBJ,
		BLOCK_15_GAMEOBJ,
		BLOCK_16_GAMEOBJ,
		BLOCK_P_GAMEOBJ,
		BLOCK_U_GAMEOBJ,
		BLOCK_Z_GAMEOBJ,
		BLOCK_L_GAMEOBJ,
		BLOCK_E_GAMEOBJ,
		BLOCK_O_GAMEOBJ,
		BLOCK_X_GAMEOBJ,
		BUTTON_RESET_GAMEOBJ,
		BUTTON_RANDOM_GAMEOBJ,
		BUTTON_SOLVE_GAMEOBJ,
		BUTTON_SEARCH_METHOD_GAMEOBJ,
		BUTTON_ANIMATION_SPEED_GAMEOBJ,
		BUTTON_STRESS_TEST_GAMEOBJ,
		BUTTON_PUZZLE_MODE_GAMEOBJ,
		BUTTON_MENU_GAMEOBJ,
		////////////////////////////////////////////////////////////////////////////////
		BALL_GAMEOBJ,
		WALL_GAMEOBJ,
		CIRCLEPILLAR_GAMEOBJ,
		WALLPILLAR_GAMEOBJ,
		SATELLITE_GAMEOBJ,
		MIRROR_GAMEOBJ,
		WINDOW_GAMEOBJ,
		ROAD_GAMEOBJ,
		CAN_GAMEOBJ,
		CRATE_GAMEOBJ,
		////////////////////////////////////////////////////////////////////////////////
		LIGHT_SOURCE_GAMEOBJ,
		REFLECTIVE_GAMEOBJ,
		REFRACTIVE_GAMEOBJ,
		REFRACTIVE_CD_GAMEOBJ,
		FRESNEL_GAMEOBJ,
		////////////////////////////////////////////////////////////////////////////////
		PLANE_GAMEOBJ,
		MISSILE_GAMEOBJ,
		ZONE_GAMEOBJ
	};


	enum GeometryObjectType
	{		
		BLOCK_0_OBJTYPE,
		BLOCK_1_OBJTYPE,
		BLOCK_2_OBJTYPE,
		BLOCK_3_OBJTYPE,
		BLOCK_4_OBJTYPE,
		BLOCK_5_OBJTYPE,
		BLOCK_6_OBJTYPE,
		BLOCK_7_OBJTYPE,
		BLOCK_8_OBJTYPE,
		BLOCK_9_OBJTYPE,
		BLOCK_10_OBJTYPE,
		BLOCK_11_OBJTYPE,
		BLOCK_12_OBJTYPE,
		BLOCK_13_OBJTYPE,
		BLOCK_14_OBJTYPE,
		BLOCK_15_OBJTYPE,
		BLOCK_16_OBJTYPE,
		BLOCK_P_OBJTYPE,
		BLOCK_U_OBJTYPE,
		BLOCK_Z_OBJTYPE,
		BLOCK_L_OBJTYPE,
		BLOCK_E_OBJTYPE,
		BLOCK_O_OBJTYPE,
		BLOCK_X_OBJTYPE,
		////////////////////////////////////////////////////////////////////////////////
		GRID_OBJTYPE,
		GRID2_OBJTYPE,
		GRID3_OBJTYPE,
		GRID4_OBJTYPE,
		GRID5_OBJTYPE,
		GRID6_OBJTYPE,
		GRID7_OBJTYPE,
		POLYGON_OBJTYPE,
		CUBE_OBJTYPE,
		CUBE2_OBJTYPE,
		CUBE3_OBJTYPE,
		CUBE4_OBJTYPE,
		CYLINDER_OBJTYPE,
		CYLINDER2_OBJTYPE,
		CYLINDER3_OBJTYPE,
		CYLINDER4_OBJTYPE,
		CONE_OBJTYPE,
		CONE2_OBJTYPE,	
		SPHERE_OBJTYPE,
		SPHERE2_OBJTYPE,
		SPHERE3_OBJTYPE,
		SPHERE4_OBJTYPE,
		HEXASPHERE_OBJTYPE,			
		SATELLITE_OBJTYPE
	};


	class MyGeometryOM : public GameFramework::GameObjectManager
	{
	public:
		MyGeometryOM( void );
		~MyGeometryOM( void );

		virtual void LoadMeshObjects( GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr );
		virtual void GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr );
		virtual void GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
			const PhysicsFramework::PhysicsObject physicsVal,
			const Light::Material materialVal, 
			const GameFramework::GameObjCategory gameObjCategory, 
			const bool moveInitialFlag = true );
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
			);

	private:
		//make the copy constructor private
		MyGeometryOM( const MyGeometryOM & myGeometryOM );
		//make the assignment operator private
		MyGeometryOM & operator=( const MyGeometryOM & myGeometryOM );

		void LoadTextureObjects( GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr );

		void LoadMeshToGraphicsObject( const GeometryObjectType geometryObjectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr, 
			const char * envTextureName = 0,
			const char ** textureName = 0, const unsigned arrSize = 0 );

		void LoadMeshToGraphicsObjectHelper( const std::string objName, 
			const GeometryObjectType GeometryObjectType, 
			GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
			GraphicsFramework::BaseGeometryBuilder* const baseGeometryBuilderPtr, 
			const char * envTextureName = 0,
			const char ** textureName = 0, const unsigned arrSize = 0 );

		const GraphicsFramework::MeshParameterContainer GetMeshParametersFromFile( const std::string objName, const char * fileName ) const;

		void ComputeLineNormal( const std::string objNameFromFile, PhysicsFramework::PhysicsObject & physicsObj ) const;
		void ComputePlaneNormal( const std::string objNameFromFile, PhysicsFramework::PhysicsObject & physicsObj ) const; 
	};

} //end namespace MyGeometryGame


#endif
////////////////////////////////////////////////////////////////////////////////