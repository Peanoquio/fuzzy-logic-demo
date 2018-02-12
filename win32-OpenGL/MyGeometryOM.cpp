/******************************************************************************/
/*!
\file MyGeometryOM.cpp
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

#include "MyGeometryOM.h"
#include "File\FileIO.h"
//#include "File\TGALoader.h"

#include "GeometryBuilder\Grid2DBuilder.h"
#include "GeometryBuilder\Polygon2DBuilder.h"
#include "GeometryBuilder\CubeBuilder.h"
#include "GeometryBuilder\CylinderBuilder.h"
#include "GeometryBuilder\ConeBuilder.h"
#include "GeometryBuilder\SphereBuilder.h"
//#include "GeometryBuilder\SatelliteBuilder.h"

#include <iostream>
#include <iomanip>


namespace
{
	const char * FILE_NAME = "./File/GeometryParametersFile.txt";
}


namespace MyGeometryGame
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the MyGeometryOM class
	\param
	\return
	*/
	/******************************************************************************/
	MyGeometryOM::MyGeometryOM( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the MyGeometryOM class
	\param
	\return
	*/
	/******************************************************************************/
	MyGeometryOM::~MyGeometryOM( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Computes for the normal of a line
	\param objNameFromFile
	the object name that will be used to retrieve the geometry parameters from the file
	\param physicsObj
	the physics object that contains the physics properties of the game object
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::ComputeLineNormal( const std::string objNameFromFile, PhysicsFramework::PhysicsObject & physicsObj ) const
	{
		//get the values from the physics object
		const Math::Vector4 & scale = physicsObj.GetScale();
		const Math::Vector4 & position = physicsObj.GetPosition();
		const float angleDegrees = physicsObj.GetAngleDegreesZ();

		//get the mesh parameters from the file
		GraphicsFramework::MeshParameterContainer meshParameterContainer = this->GetMeshParametersFromFile( objNameFromFile, FILE_NAME );
		//float yLimit = meshParameterContainer.m_height / 2.0F;
		float xLimit = meshParameterContainer.m_width / 2.0F;

		//compute for the cube normal
		Math::Vector4 ptHead( xLimit, 0.0F, 0.0F, 1.0F );
		Math::Vector4 ptTail( -xLimit, 0.0F, 0.0F, 1.0F );

		Math::Mtx44 concatenatedMtx;
		Math::Mtx44 rotateMtx;
		Math::Mtx44 scaleMtx;
		Math::Mtx44 translateMtx;

		//set scale
		scaleMtx.SetToScale( 
			scale.GetFloatX(), 
			scale.GetFloatY(), 
			scale.GetFloatZ() );
		//set rotation
		rotateMtx.SetToRotationDegreesZ( angleDegrees );				
		//set translation
		translateMtx.SetToTranslation( 
			position.GetFloatX(), 
			position.GetFloatY(), 
			position.GetFloatZ() );

		//pass the physics matrix
		concatenatedMtx = translateMtx * rotateMtx * scaleMtx;	
		ptHead = concatenatedMtx * ptHead;
		ptTail = concatenatedMtx * ptTail;

		//compute for the normal
		physicsObj.ComputeNormal( ptHead, ptTail );

		/*
		std::cout << std::setfill (' ') << std::setw( 0 ) << "=============================================================================" << std::endl;
		std::cout << std::setfill (' ') << std::setw( 0 ) << "wall angle : " << angleDegrees << std::endl;
		std::cout << std::setfill (' ') << std::setw( 0 ) << "wall position : " << physicsObj.GetPosition().GetFloatX() << ", " 
			<< physicsObj.GetPosition().GetFloatY() << ", " << physicsObj.GetPosition().GetFloatZ() << std::endl;
		std::cout << std::setfill (' ') << std::setw( 0 ) << "wall scale : " << physicsObj.GetScale().GetFloatX() << ", " 
			<< physicsObj.GetScale().GetFloatY() << ", " << physicsObj.GetScale().GetFloatZ() << std::endl;
		std::cout << std::setfill (' ') << std::setw( 0 ) << "wall normal : " << physicsObj.GetNormal().GetFloatX() << ", " 
			<< physicsObj.GetNormal().GetFloatY() << std::endl;
		std::cout << std::setfill (' ') << std::setw( 0 ) << "wall span : " << ptTail.GetFloatX() << ", " 
			<< ptTail.GetFloatY() << " to " << ptHead.GetFloatX() << ", " << ptHead.GetFloatY() << std::endl;
		*/

		//test if vector is perpendicular to normal 
		//float val = physicsObj.GetNormal().Dot( ptHead - ptTail );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Computes for the normal of a plane
	\param objNameFromFile
	the object name that will be used to retrieve the geometry parameters from the file
	\param physicsObj
	the physics object that contains the physics properties of the game object
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::ComputePlaneNormal( const std::string objNameFromFile, PhysicsFramework::PhysicsObject & physicsObj ) const
	{
		//get the values from the physics object
		const Math::Vector4 & scale = physicsObj.GetScale();
		const Math::Vector4 & position = physicsObj.GetPosition();

		//get the mesh parameters from the file
		GraphicsFramework::MeshParameterContainer meshParameterContainer = this->GetMeshParametersFromFile( objNameFromFile, FILE_NAME );
		float yLimit = meshParameterContainer.m_height / 2.0F;
		float xLimit = meshParameterContainer.m_width / 2.0F;

		//compute for the plane normal
		Math::Vector4 ptHor( xLimit, 0.0F, 0.0F, 1.0F );
		Math::Vector4 ptVert( 0.0F, yLimit, 0.0F, 1.0F );
		Math::Vector4 ptCtr( 0.0F, 0.0F, 0.0F, 1.0F );

		Math::Mtx44 concatenatedMtx;
		Math::Mtx44 rotateMtx;
		Math::Mtx44 scaleMtx;
		Math::Mtx44 translateMtx;

		//set scale
		scaleMtx.SetToScale( 
			scale.GetFloatX(), 
			scale.GetFloatY(), 
			scale.GetFloatZ() );
		//set rotation
		rotateMtx.SetToRotationDegreesX( physicsObj.GetAngleDegreesX() );	
		rotateMtx.SetToRotationDegreesY( physicsObj.GetAngleDegreesY() );
		rotateMtx.SetToRotationDegreesZ( physicsObj.GetAngleDegreesZ() );
		//set translation
		translateMtx.SetToTranslation( 
			position.GetFloatX(), 
			position.GetFloatY(), 
			position.GetFloatZ() );

		//pass the physics matrix
		concatenatedMtx = translateMtx * rotateMtx * scaleMtx;	
		ptHor = concatenatedMtx * ptHor;
		ptVert = concatenatedMtx * ptVert;
		ptCtr = concatenatedMtx * ptCtr;

		//compute for the plane normal using the cross product
		Math::Vector4 vectorU = ptHor - ptCtr;
		Math::Vector4 vectorV = ptVert - ptCtr;
		Math::Vector4 planeNormal = vectorU.Cross( vectorV );
		planeNormal.Normalize();
		//store the computed normal
		physicsObj.SetNormal( planeNormal );
		//store the center vertex of the object
		physicsObj.SetCenterPt( ptCtr );		

		//test if vector is perpendicular to normal
		//float val = physicsObj.GetNormal().Dot( vectorU  );
		//val = physicsObj.GetNormal().Dot( vectorV  );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Generates the pending game object.
	This also adds the generated pending game object to the vector so it can be reused by the game
	\param gameObjIdentifier
	the identifier of the game object
	\param objectType
	the type of the geometry
	\param graphicsInterfacePtr
	the graphics interface
	\param position
	the position of the object
	\param velocity
	the velocity of the object
	\param scale
	the scale of the object
	\param rotation
	the rotational angle direction in degrees of the object
	\param movementSpeed
	the movement speed of the object
	\param rotationalSpeed
	the rotational speed of the object
	\param acceleration
	the acceleration of the object
	\param mass
	the mass of the object
	\param moveInitialFlag
	the indicator to determine if the object will move upon initial rendering
	\param row
	the row of the game object
	\param column
	the column of the game object
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
		GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
		const Math::Vector4 & position,
		const Math::Vector4 & velocity,
		const Math::Vector4 & scale,
		const Math::Vector4 & rotation,
		const float	movementSpeed,
		const float	rotationalSpeed,
		const float	acceleration,
		const float	mass,
		const bool moveInitialFlag,
		const unsigned row,
		const unsigned column,
		const unsigned index
		)
	{
		GraphicsFramework::GraphicsObject			graphicsObj;
		PhysicsFramework::PhysicsObject				physicsObj;
		GameFramework::GameObject					gameObj;

		//retrieve the graphics object
		graphicsObj = graphicsInterfacePtr->RetrieveGraphicsObject( objectType );

		//set up the physics object
		physicsObj = this->CreatePhysicsObject( position, velocity, scale, rotation, mass, movementSpeed, rotationalSpeed, acceleration, moveInitialFlag );


		//////////////////////////////////////////////////////////////////////////////////////////////////////////		
		if ( objectType == CUBE_OBJTYPE || objectType == CUBE2_OBJTYPE )
		{
			std::string objNameFromFile;
			if ( objectType == CUBE_OBJTYPE )
			{
				objNameFromFile = "cube";
			}
			else if ( objectType == CUBE2_OBJTYPE )
			{
				objNameFromFile = "cube2";
			}

			//compute for the line normal
			this->ComputeLineNormal( objNameFromFile, physicsObj );

		}
		else if ( objectType == GRID_OBJTYPE )
		{
			//compute for the plane normal
			this->ComputePlaneNormal( "grid2D", physicsObj );
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////


		//create the game object
		gameObj = this->CreateGameObject( graphicsObj, physicsObj );
		gameObj.SetType( objectType );
		gameObj.SetIdentifier( gameObjIdentifier );
		gameObj.SetRow( row );
		gameObj.SetColumn( column );
		gameObj.SetIndex( index );

		//contain the game object
		this->ContainGameObject( gameObj );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Generates the pending game object.
	This also adds the generated pending game object to the vector so it can be reused by the game
	\param gameObjIdentifier
	the identifier of the game object
	\param objectType
	the object type
	\param graphicsInterfacePtr
	the graphics interface
	\param physicsVal
	the physics properties of the game object
	\param materialVal
	the material properties of the game object
	\param gameObjCategory
	the category of the game object
	\param moveInitialFlag
	the indicator to determine if the object will move upon initial rendering
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
		GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
		const PhysicsFramework::PhysicsObject physicsVal,
		const Light::Material materialVal, 
		const GameFramework::GameObjCategory gameObjCategory, 
		const bool moveInitialFlag )
	{
		GraphicsFramework::GraphicsObject			graphicsObj;
		PhysicsFramework::PhysicsObject				physicsObj;
		GameFramework::GameObject					gameObj;

		//retrieve the graphics object
		graphicsObj = graphicsInterfacePtr->RetrieveGraphicsObject( objectType );
		//set the material properties
		graphicsObj.GetMaterial().SetMaterialProperties( materialVal.GetAmbient(), materialVal.GetEmissive(), materialVal.GetDiffuse(), 
			materialVal.GetSpecular(), materialVal.GetShininess() );

		//set up the physics object
		physicsObj = this->CreatePhysicsObject( physicsVal.GetPosition(), physicsVal.GetVelocity(), physicsVal.GetScale(), physicsVal.GetRotation(),
			physicsVal.GetMass(), physicsVal.GetMovementSpeed(), physicsVal.GetRotationalSpeed(), physicsVal.GetAcceleration(), moveInitialFlag );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////		
		if ( objectType == CUBE_OBJTYPE || objectType == CUBE2_OBJTYPE )
		{
			std::string objNameFromFile;
			if ( objectType == CUBE_OBJTYPE )
			{
				objNameFromFile = "cube";
			}
			else if ( objectType == CUBE2_OBJTYPE )
			{
				objNameFromFile = "cube2";
			}

			//compute for the line normal
			this->ComputeLineNormal( objNameFromFile, physicsObj );

		}
		else if ( objectType == GRID_OBJTYPE )
		{
			//compute for the plane normal
			this->ComputePlaneNormal( "grid2D", physicsObj );
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		//create the game object
		gameObj = this->CreateGameObject( graphicsObj, physicsObj );
		gameObj.SetType( objectType );
		gameObj.SetIdentifier( gameObjIdentifier );
		gameObj.SetCategory( gameObjCategory );

		//contain the game object
		this->ContainGameObject( gameObj );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Generates the pending game object.
	This also adds the generated pending game object to the vector so it can be reused by the game
	\param gameObjIdentifier
	the identifier of the game object
	\param objectType
	the type of the geometry
	\param graphicsInterfacePtr
	the graphics interface
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::GeneratePendingGameObject( const unsigned gameObjIdentifier, const unsigned objectType, 
		GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr )
	{
		GraphicsFramework::GraphicsObject			graphicsObj;
		PhysicsFramework::PhysicsObject				physicsObj;
		GameFramework::GameObject					gameObj;

		//retrieve the graphics object
		graphicsObj = graphicsInterfacePtr->RetrieveGraphicsObject( objectType );

		//create the game object
		gameObj = this->CreateGameObject( graphicsObj, physicsObj );
		gameObj.SetType( objectType );
		gameObj.SetIdentifier( gameObjIdentifier );

		//contain the game object
		this->ContainGameObject( gameObj );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load texture objects
	\param graphicsInterfacePtr
	the pointer to the graphics interface
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::LoadTextureObjects( GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//load the environment textures
		/*
		this->LoadCubeMapImages( graphicsInterfacePtr, "SpringCubeMap",
			"SpringCubeMapRight", "SpringCubeMapRight.tga",
			"SpringCubeMapLeft", "SpringCubeMapLeft.tga",
			"SpringCubeMapTop", "SpringCubeMapTop.tga",
			"SpringCubeMapBottom", "SpringCubeMapBottom.tga",
			"SpringCubeMapFront", "SpringCubeMapFront.tga",
			"SpringCubeMapBack", "SpringCubeMapBack.tga" );
		*/

		this->LoadDualParaboloidImages( graphicsInterfacePtr, 
			"TestFrontFaceEnvMap", "TestEnvMapFront.tga",
			"TestBackFaceEnvMap", "TestEnvMapBack.tga" );

		this->LoadCubeMapImages( graphicsInterfacePtr, "TestEnvMap",
			"TestEnvMapRight", "TestEnvMapRight.tga",
			"TestEnvMapLeft", "TestEnvMapLeft.tga",
			"TestEnvMapTop", "TestEnvMapTop.tga",
			"TestEnvMapBottom", "TestEnvMapBottom.tga",
			"TestEnvMapFront", "TestEnvMapFront.tga",
			"TestEnvMapBack", "TestEnvMapBack.tga" );

		this->LoadTextureImage( graphicsInterfacePtr, "TestEnvMapRight", "TestEnvMapRight.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "TestEnvMapLeft", "TestEnvMapLeft.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "TestEnvMapTop", "TestEnvMapTop.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "TestEnvMapBottom", "TestEnvMapBottom.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "TestEnvMapFront", "TestEnvMapFront.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "TestEnvMapBack", "TestEnvMapBack.tga" );

		this->LoadCubeMapImages( graphicsInterfacePtr, "StellarEnvMap",
			"StellarEnvMapRight", "interstellar_rt.tga",
			"StellarEnvMapLeft", "interstellar_lf.tga",
			"StellarEnvMapTop", "interstellar_up.tga",
			"StellarEnvMapBottom", "interstellar_dn.tga",
			"StellarEnvMapFront", "interstellar_bk.tga",
			"StellarEnvMapBack", "interstellar_ft.tga" );

		this->LoadTextureImage( graphicsInterfacePtr, "StellarEnvMapRight", "interstellar_rt.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "StellarEnvMapLeft", "interstellar_lf.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "StellarEnvMapTop", "interstellar_up.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "StellarEnvMapBottom", "interstellar_dn.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "StellarEnvMapFront", "interstellar_bk.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "StellarEnvMapBack", "interstellar_ft.tga" );		

		//this->LoadTextureImage( graphicsInterfacePtr, "SpringCubeMapRight", "SpringCubeMapRight.tga" );	

		this->LoadTextureImage( graphicsInterfacePtr, "EthanCochardLongboard", "EthanCochardLongboard.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "WoodenCrate", "WoodenCrate.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "Road", "Road.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "WallSpace", "WallSpace.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "CheckerStoneBlock", "CheckerStoneBlock.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "DirtyWindow", "DirtyWindow.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "EarthMap", "EarthMap.tga" );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		//load the textures for the N puzzle
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture1", "MarbleTexture1.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture2", "MarbleTexture2.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture3", "MarbleTexture3.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture4", "MarbleTexture4.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture5", "MarbleTexture5.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture6", "MarbleTexture6.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture7", "MarbleTexture7.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture8", "MarbleTexture8.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture9", "MarbleTexture9.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture10", "MarbleTexture10.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture11", "MarbleTexture11.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture12", "MarbleTexture12.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture13", "MarbleTexture13.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture14", "MarbleTexture14.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture15", "MarbleTexture15.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTexture16", "MarbleTexture16.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTextureP", "MarbleTextureP.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTextureU", "MarbleTextureU.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTextureZ", "MarbleTextureZ.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTextureL", "MarbleTextureL.tga" );
		this->LoadTextureImage( graphicsInterfacePtr, "MarbleTextureE", "MarbleTextureE.tga" );
		*/
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load object meshes
	\param graphicsInterfacePtr
	the pointer to the graphics interface
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::LoadMeshObjects( GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr )
	{
		//load the textures
		this->LoadTextureObjects( graphicsInterfacePtr );

		//Loads the mesh to the graphics object.
		//This also adds the generated graphics object to the map so it can be reused when creating game objects

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		//for mesh objects for the N puzzle
		const char * textureNamesBlock1[] = { "MarbleTexture1" };
		this->LoadMeshToGraphicsObject( BLOCK_1_OBJTYPE, graphicsInterfacePtr, textureNamesBlock1, 1 );
		const char * textureNamesBlock2[] = { "MarbleTexture2" };
		this->LoadMeshToGraphicsObject( BLOCK_2_OBJTYPE, graphicsInterfacePtr, textureNamesBlock2, 1 );
		const char * textureNamesBlock3[] = { "MarbleTexture3" };
		this->LoadMeshToGraphicsObject( BLOCK_3_OBJTYPE, graphicsInterfacePtr, textureNamesBlock3, 1 );
		const char * textureNamesBlock4[] = { "MarbleTexture4" };
		this->LoadMeshToGraphicsObject( BLOCK_4_OBJTYPE, graphicsInterfacePtr, textureNamesBlock4, 1 );
		const char * textureNamesBlock5[] = { "MarbleTexture5" };
		this->LoadMeshToGraphicsObject( BLOCK_5_OBJTYPE, graphicsInterfacePtr, textureNamesBlock5, 1 );
		const char * textureNamesBlock6[] = { "MarbleTexture6" };
		this->LoadMeshToGraphicsObject( BLOCK_6_OBJTYPE, graphicsInterfacePtr, textureNamesBlock6, 1 );
		const char * textureNamesBlock7[] = { "MarbleTexture7" };
		this->LoadMeshToGraphicsObject( BLOCK_7_OBJTYPE, graphicsInterfacePtr, textureNamesBlock7, 1 );
		const char * textureNamesBlock8[] = { "MarbleTexture8" };
		this->LoadMeshToGraphicsObject( BLOCK_8_OBJTYPE, graphicsInterfacePtr, textureNamesBlock8, 1 );
		const char * textureNamesBlock9[] = { "MarbleTexture9" };
		this->LoadMeshToGraphicsObject( BLOCK_9_OBJTYPE, graphicsInterfacePtr, textureNamesBlock9, 1 );
		const char * textureNamesBlock10[] = { "MarbleTexture10" };
		this->LoadMeshToGraphicsObject( BLOCK_10_OBJTYPE, graphicsInterfacePtr, textureNamesBlock10, 1 );
		const char * textureNamesBlock11[] = { "MarbleTexture11" };
		this->LoadMeshToGraphicsObject( BLOCK_11_OBJTYPE, graphicsInterfacePtr, textureNamesBlock11, 1 );
		const char * textureNamesBlock12[] = { "MarbleTexture12" };
		this->LoadMeshToGraphicsObject( BLOCK_12_OBJTYPE, graphicsInterfacePtr, textureNamesBlock12, 1 );
		const char * textureNamesBlock13[] = { "MarbleTexture13" };
		this->LoadMeshToGraphicsObject( BLOCK_13_OBJTYPE, graphicsInterfacePtr, textureNamesBlock13, 1 );
		const char * textureNamesBlock14[] = { "MarbleTexture14" };
		this->LoadMeshToGraphicsObject( BLOCK_14_OBJTYPE, graphicsInterfacePtr, textureNamesBlock14, 1 );
		const char * textureNamesBlock15[] = { "MarbleTexture15" };
		this->LoadMeshToGraphicsObject( BLOCK_15_OBJTYPE, graphicsInterfacePtr, textureNamesBlock15, 1 );
		const char * textureNamesBlock16[] = { "MarbleTexture16" };
		this->LoadMeshToGraphicsObject( BLOCK_16_OBJTYPE, graphicsInterfacePtr, textureNamesBlock16, 1 );

		const char * textureNamesBlockP[] = { "MarbleTextureP" };
		this->LoadMeshToGraphicsObject( BLOCK_P_OBJTYPE, graphicsInterfacePtr, textureNamesBlockP, 1 );
		const char * textureNamesBlockU[] = { "MarbleTextureU" };
		this->LoadMeshToGraphicsObject( BLOCK_U_OBJTYPE, graphicsInterfacePtr, textureNamesBlockU, 1 );
		const char * textureNamesBlockZ[] = { "MarbleTextureZ" };
		this->LoadMeshToGraphicsObject( BLOCK_Z_OBJTYPE, graphicsInterfacePtr, textureNamesBlockZ, 1 );
		const char * textureNamesBlockL[] = { "MarbleTextureL" };
		this->LoadMeshToGraphicsObject( BLOCK_L_OBJTYPE, graphicsInterfacePtr, textureNamesBlockL, 1 );
		const char * textureNamesBlockE[] = { "MarbleTextureE" };
		this->LoadMeshToGraphicsObject( BLOCK_E_OBJTYPE, graphicsInterfacePtr, textureNamesBlockE, 1 );
		*/
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		this->LoadMeshToGraphicsObject( GRID_OBJTYPE, graphicsInterfacePtr );
		/*
		const char * textureNamesFace1[] = { "TestEnvMapRight" };
		const char * textureNamesFace2[] = { "TestEnvMapLeft" };
		const char * textureNamesFace3[] = { "TestEnvMapTop" };
		const char * textureNamesFace4[] = { "TestEnvMapBottom" };
		const char * textureNamesFace5[] = { "TestEnvMapFront" };
		const char * textureNamesFace6[] = { "TestEnvMapBack" };
		*/
		const char * textureNamesFace1[] = { "StellarEnvMapRight" };
		const char * textureNamesFace2[] = { "StellarEnvMapLeft" };
		const char * textureNamesFace3[] = { "StellarEnvMapTop" };
		const char * textureNamesFace4[] = { "StellarEnvMapBottom" };
		const char * textureNamesFace5[] = { "StellarEnvMapFront" };
		const char * textureNamesFace6[] = { "StellarEnvMapBack" };
		this->LoadMeshToGraphicsObject( GRID2_OBJTYPE, graphicsInterfacePtr, 0, textureNamesFace1, 1 );
		this->LoadMeshToGraphicsObject( GRID3_OBJTYPE, graphicsInterfacePtr, 0, textureNamesFace2, 1 );
		this->LoadMeshToGraphicsObject( GRID4_OBJTYPE, graphicsInterfacePtr, 0, textureNamesFace3, 1 );
		this->LoadMeshToGraphicsObject( GRID5_OBJTYPE, graphicsInterfacePtr, 0, textureNamesFace4, 1 );
		this->LoadMeshToGraphicsObject( GRID6_OBJTYPE, graphicsInterfacePtr, 0, textureNamesFace5, 1 );
		this->LoadMeshToGraphicsObject( GRID7_OBJTYPE, graphicsInterfacePtr, 0, textureNamesFace6, 1 );


		//const char * textureNames[] = { "EthanCochardLongboard" };
		//this->LoadMeshToGraphicsObject( POLYGON_OBJTYPE, graphicsInterfacePtr, "SpringCubeMap", textureNames, 1 );
		this->LoadMeshToGraphicsObject( POLYGON_OBJTYPE, graphicsInterfacePtr, "TestEnvMap" );

		const char * textureNames2[] = { "WoodenCrate" };
		this->LoadMeshToGraphicsObject( CUBE_OBJTYPE, graphicsInterfacePtr, 0, textureNames2, 1 );
		const char * textureNames3[] = { "WallSpace" };
		this->LoadMeshToGraphicsObject( CUBE2_OBJTYPE, graphicsInterfacePtr, 0, textureNames3, 1 );	
		const char * textureNames4[] = { "Road" };
		this->LoadMeshToGraphicsObject( CUBE3_OBJTYPE, graphicsInterfacePtr, 0, textureNames4, 1 );
		this->LoadMeshToGraphicsObject( CUBE4_OBJTYPE, graphicsInterfacePtr, "TestEnvMap" );
		/*
		const char * textureNames3[] = { "Road" };
		this->LoadMeshToGraphicsObject( CUBE2_OBJTYPE, graphicsInterfacePtr, 0, textureNames3, 1 );	
		const char * textureNames4[] = { "WallSpace" };
		this->LoadMeshToGraphicsObject( CUBE3_OBJTYPE, graphicsInterfacePtr, 0, textureNames4, 1 );
		const char * textureNames5[] = { "DirtyWindow" };
		this->LoadMeshToGraphicsObject( CUBE4_OBJTYPE, graphicsInterfacePtr, 0, textureNames5, 1 );
		*/
		
		const char * textureNames6[] = { "CheckerStoneBlock", "WallSpace", "Road" };
		this->LoadMeshToGraphicsObject( CYLINDER_OBJTYPE, graphicsInterfacePtr, 0, textureNames6, 3 );
		this->LoadMeshToGraphicsObject( CYLINDER2_OBJTYPE, graphicsInterfacePtr, "TestEnvMap" );	
		const char * textureNames7[] = { "WallSpace" };
		this->LoadMeshToGraphicsObject( CYLINDER3_OBJTYPE, graphicsInterfacePtr, 0, textureNames7, 1 );
		const char * textureNames8[] = { "DirtyWindow" };
		this->LoadMeshToGraphicsObject( CYLINDER4_OBJTYPE, graphicsInterfacePtr, 0, textureNames8, 1 );	


		this->LoadMeshToGraphicsObject( SPHERE_OBJTYPE, graphicsInterfacePtr, "TestEnvMap" );
		this->LoadMeshToGraphicsObject( SPHERE2_OBJTYPE, graphicsInterfacePtr );
		const char * textureNames9[] = { "EarthMap" };
		this->LoadMeshToGraphicsObject( SPHERE3_OBJTYPE, graphicsInterfacePtr, 0, textureNames9, 1 );
		
		const char * textureNames10[] = { "CheckerStoneBlock" };
		this->LoadMeshToGraphicsObject( CONE_OBJTYPE, graphicsInterfacePtr, 0, textureNames10, 1 );

		/*
		this->LoadMeshToGraphicsObject( CONE_OBJTYPE, graphicsInterfacePtr );
		this->LoadMeshToGraphicsObject( CONE2_OBJTYPE, graphicsInterfacePtr );	

		this->LoadMeshToGraphicsObject( SPHERE_OBJTYPE, graphicsInterfacePtr );		
		this->LoadMeshToGraphicsObject( SPHERE2_OBJTYPE, graphicsInterfacePtr );	
		this->LoadMeshToGraphicsObject( SPHERE3_OBJTYPE, graphicsInterfacePtr );	
		this->LoadMeshToGraphicsObject( SPHERE4_OBJTYPE, graphicsInterfacePtr );

		this->LoadMeshToGraphicsObject( HEXASPHERE_OBJTYPE, graphicsInterfacePtr );	
		
		this->LoadMeshToGraphicsObject( SATELLITE_OBJTYPE, graphicsInterfacePtr );	
		*/
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The helper function to loadd the mesh to the graphics object.
	This also adds the generated graphics object to the map so it can be reused when creating game objects
	\param objName
	the name of the object
	\param geometryObjectType
	the type of the geometry
	\param graphicsInterfacePtr
	the pointer to the graphics interface
	\param baseGeometryBuilderPtr
	the pointer to the base geometry builder
	\param envTextureName
	the name of the environment texture
	\param textureName
	the array containing the name of the textures
	\param arrSize
	the array size
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::LoadMeshToGraphicsObjectHelper( const std::string objName, 
		const GeometryObjectType geometryObjectType, 
		GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr,
		GraphicsFramework::BaseGeometryBuilder* const baseGeometryBuilderPtr,
		const char * envTextureName,
		const char ** textureName, const unsigned arrSize )
	{
		GraphicsFramework::GraphicsObject			graphicsObj;
		GraphicsFramework::Mesh						mesh;

		//get the mesh parameters from the file
		GraphicsFramework::MeshParameterContainer meshParameterContainer = this->GetMeshParametersFromFile( objName, FILE_NAME );

		//generate the mesh		
		this->GenerateMesh( meshParameterContainer, baseGeometryBuilderPtr, mesh );	

		//validate if there is a texture name being passed
		if ( envTextureName == 0 && textureName == 0 && arrSize == 0 )
		{
			//create the graphics object
			graphicsObj = this->CreateGraphicsObject( static_cast<unsigned>( geometryObjectType ), graphicsInterfacePtr, mesh );
		}
		else
		{
			//create the graphics object
			graphicsObj = this->CreateGraphicsObject( static_cast<unsigned>( geometryObjectType ), graphicsInterfacePtr, mesh, envTextureName, textureName, arrSize );
		}

		//add the base geometry builder to the map
		this->ContainBaseGeometryBuilder( static_cast<unsigned>( geometryObjectType ), baseGeometryBuilderPtr );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Loads the mesh to the graphics object.
	\param geometryObjectType
	the type of the geometry
	\param graphicsInterfacePtr
	the pointer to the graphics interface
	\param envTextureName
	the environment texture name
	\param textureName
	the array containing the name of the textures
	\param arrSize
	the array size
	\return
	*/
	/******************************************************************************/
	void MyGeometryOM::LoadMeshToGraphicsObject( const GeometryObjectType geometryObjectType, 
		GraphicsFramework::GraphicsInterface* const graphicsInterfacePtr, 
		const char * envTextureName,
		const char ** textureName, const unsigned arrSize )
	{
		//these pointers will be destroyed by the game object manager base class destructor
		GraphicsFramework::Grid2DBuilder * gridBuilder = 0;
		GraphicsFramework::PolygonBuilder * polygonBuilder = 0;
		GraphicsFramework::CubeBuilder * cubeBuilder = 0;
		GraphicsFramework::CylinderBuilder * cylinderBuilder = 0;
		GraphicsFramework::ConeBuilder * coneBuilder = 0;
		GraphicsFramework::SphereBuilder * sphereBuilder = 0;
		//GraphicsFramework::SatelliteBuilder * satelliteBuilder = 0;


		if ( geometryObjectType == BLOCK_1_OBJTYPE || geometryObjectType == BLOCK_2_OBJTYPE || geometryObjectType == BLOCK_3_OBJTYPE || geometryObjectType == BLOCK_4_OBJTYPE
			|| geometryObjectType == BLOCK_5_OBJTYPE || geometryObjectType == BLOCK_6_OBJTYPE || geometryObjectType == BLOCK_7_OBJTYPE || geometryObjectType == BLOCK_8_OBJTYPE 
			|| geometryObjectType == BLOCK_9_OBJTYPE || geometryObjectType == BLOCK_10_OBJTYPE || geometryObjectType == BLOCK_11_OBJTYPE || geometryObjectType == BLOCK_12_OBJTYPE
			|| geometryObjectType == BLOCK_13_OBJTYPE || geometryObjectType == BLOCK_14_OBJTYPE || geometryObjectType == BLOCK_15_OBJTYPE || geometryObjectType == BLOCK_16_OBJTYPE 
			|| geometryObjectType == BLOCK_P_OBJTYPE || geometryObjectType == BLOCK_U_OBJTYPE || geometryObjectType == BLOCK_Z_OBJTYPE 
			|| geometryObjectType == BLOCK_L_OBJTYPE || geometryObjectType == BLOCK_E_OBJTYPE
			)
		{
			if ( cubeBuilder == 0 )
			{
				cubeBuilder = new GraphicsFramework::CubeBuilder();
			}
			this->LoadMeshToGraphicsObjectHelper( "cube", geometryObjectType, graphicsInterfacePtr, cubeBuilder, envTextureName, textureName, arrSize );
		}


		if ( geometryObjectType == GRID2_OBJTYPE || geometryObjectType == GRID3_OBJTYPE || geometryObjectType == GRID4_OBJTYPE 
			|| geometryObjectType == GRID5_OBJTYPE || geometryObjectType == GRID6_OBJTYPE || geometryObjectType == GRID7_OBJTYPE )
		{
			if ( gridBuilder == 0 )
			{
				gridBuilder = new GraphicsFramework::Grid2DBuilder();
			}
			this->LoadMeshToGraphicsObjectHelper( "grid2D", geometryObjectType, graphicsInterfacePtr, gridBuilder, envTextureName, textureName, arrSize );
		}


		switch ( geometryObjectType )
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case GRID_OBJTYPE:
			{
				if ( gridBuilder == 0 )
				{
					gridBuilder = new GraphicsFramework::Grid2DBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "grid2D", geometryObjectType, graphicsInterfacePtr, gridBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case POLYGON_OBJTYPE:
			{
				if ( polygonBuilder == 0 )
				{
					polygonBuilder = new GraphicsFramework::PolygonBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "poly2D", geometryObjectType, graphicsInterfacePtr, polygonBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CUBE_OBJTYPE:
			{
				if ( cubeBuilder == 0 )
				{
					cubeBuilder = new GraphicsFramework::CubeBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cube", geometryObjectType, graphicsInterfacePtr, cubeBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CYLINDER_OBJTYPE:
			{
				if ( cylinderBuilder == 0 )
				{
					cylinderBuilder = new GraphicsFramework::CylinderBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cylinder", geometryObjectType, graphicsInterfacePtr, cylinderBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CONE_OBJTYPE:
			{
				if ( coneBuilder == 0 )
				{
					coneBuilder = new GraphicsFramework::ConeBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cone", geometryObjectType, graphicsInterfacePtr, coneBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SPHERE_OBJTYPE:
			{
				if ( sphereBuilder == 0 )
				{
					sphereBuilder = new GraphicsFramework::SphereBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "sphere", geometryObjectType, graphicsInterfacePtr, sphereBuilder, envTextureName, textureName, arrSize );
				break;							
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CYLINDER2_OBJTYPE:
			{
				if ( cylinderBuilder == 0 )
				{
					cylinderBuilder = new GraphicsFramework::CylinderBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cylinder2", geometryObjectType, graphicsInterfacePtr, cylinderBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CYLINDER3_OBJTYPE:
			{
				if ( cylinderBuilder == 0 )
				{
					cylinderBuilder = new GraphicsFramework::CylinderBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cylinder3", geometryObjectType, graphicsInterfacePtr, cylinderBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CYLINDER4_OBJTYPE:
			{
				if ( cylinderBuilder == 0 )
				{
					cylinderBuilder = new GraphicsFramework::CylinderBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cylinder4", geometryObjectType, graphicsInterfacePtr, cylinderBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SPHERE2_OBJTYPE:
			{
				if ( sphereBuilder == 0 )
				{
					sphereBuilder = new GraphicsFramework::SphereBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "sphere2", geometryObjectType, graphicsInterfacePtr, sphereBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SPHERE3_OBJTYPE:
			{
				if ( sphereBuilder == 0 )
				{
					sphereBuilder = new GraphicsFramework::SphereBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "sphere3", geometryObjectType, graphicsInterfacePtr, sphereBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case SPHERE4_OBJTYPE:
			{
				if ( sphereBuilder == 0 )
				{
					sphereBuilder = new GraphicsFramework::SphereBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "sphere4", geometryObjectType, graphicsInterfacePtr, sphereBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case HEXASPHERE_OBJTYPE:
			{
				if ( sphereBuilder == 0 )
				{
					sphereBuilder = new GraphicsFramework::SphereBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "hexaSphere", geometryObjectType, graphicsInterfacePtr, sphereBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CUBE2_OBJTYPE:
			{
				if ( cubeBuilder == 0 )
				{
					cubeBuilder = new GraphicsFramework::CubeBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cube2", geometryObjectType, graphicsInterfacePtr, cubeBuilder, envTextureName, textureName, arrSize );
				break;
			}	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CUBE3_OBJTYPE:
			{
				if ( cubeBuilder == 0 )
				{
					cubeBuilder = new GraphicsFramework::CubeBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cube", geometryObjectType, graphicsInterfacePtr, cubeBuilder, envTextureName, textureName, arrSize );
				break;
			}	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CUBE4_OBJTYPE:
			{
				if ( cubeBuilder == 0 )
				{
					cubeBuilder = new GraphicsFramework::CubeBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cube3", geometryObjectType, graphicsInterfacePtr, cubeBuilder, envTextureName, textureName, arrSize );
				break;
			}	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case CONE2_OBJTYPE:
			{
				if ( coneBuilder == 0 )
				{
					coneBuilder = new GraphicsFramework::ConeBuilder();
				}
				this->LoadMeshToGraphicsObjectHelper( "cone2", geometryObjectType, graphicsInterfacePtr, coneBuilder, envTextureName, textureName, arrSize );
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		case SATELLITE_OBJTYPE:
			{
				satelliteBuilder = new GraphicsFramework::SatelliteBuilder( 
					graphicsInterfacePtr->m_matrixStack, 
					graphicsInterfacePtr->GetGraphicsObjectMap(), 
					this->GetBaseGeometryBuilderMap() );

				//add the graphics object to the graphics object map in the graphics interface
				graphicsInterfacePtr->ContainGraphicsObject( static_cast<unsigned>( geometryObjectType ), GraphicsFramework::GraphicsObject() );

				//add the base geometry builder to the map
				this->ContainBaseGeometryBuilder( static_cast<unsigned>( geometryObjectType ), satelliteBuilder );

				break;
			}
			*/
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		default:
			break;

		}//end switch
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Reads the mesh parameters from the file
	\param objName
	the name of the object in the file
	\param fileName
	the file name
	\return MeshParameterContainer
	the container of mesh parameters
	*/
	/******************************************************************************/
	const GraphicsFramework::MeshParameterContainer MyGeometryOM::GetMeshParametersFromFile( const std::string objName, const char * fileName ) const
	{
		GraphicsFramework::MeshParameterContainer meshParameterContainer;

		//read the data from file
		File::GeometryParameterContainer myGeomParam;
		File::File myFile;
		myFile.OpenFile( fileName, myGeomParam );	

		//get the mesh parameters needed to create the geometry
		myGeomParam = myFile.GetFileDataMap().find( objName )->second;
		meshParameterContainer.m_radius = myGeomParam.GetRadius();
		meshParameterContainer.m_width = myGeomParam.GetWidth();
		meshParameterContainer.m_height = myGeomParam.GetHeight();
		meshParameterContainer.m_xSubdivisions = myGeomParam.GetXSubdivisions();
		meshParameterContainer.m_ySubdivisions = myGeomParam.GetYSubdivisions();
		meshParameterContainer.m_slices = myGeomParam.GetSlices();
		meshParameterContainer.m_stacks = myGeomParam.GetStacks();
		meshParameterContainer.m_hasCenterPoint = myGeomParam.GetHasCenterPoint();
		meshParameterContainer.m_ctrPtVertPos = myGeomParam.GetCenterVerticalPosition();
		meshParameterContainer.m_verticalPos = myGeomParam.GetVerticalPosition();
		meshParameterContainer.m_red = myGeomParam.GetRed();
		meshParameterContainer.m_green = myGeomParam.GetGreen();
		meshParameterContainer.m_blue = myGeomParam.GetBlue();
		meshParameterContainer.m_alpha = myGeomParam.GetAlpha();

		return meshParameterContainer;
	}


} //end namespace MyGeometryGame