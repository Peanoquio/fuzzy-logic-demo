/******************************************************************************/
/*!
\file GameObjectManager.cpp
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

#include "GameObjectManager.h"
#include "../File/FileIO.h"
#include "../File/TGALoader.h"
#include "../File/CustomFileHandler.h"
#include "../ErrorHandling/MessageBox.h"


namespace
{
	const unsigned START_SIZE = 100;
}


namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the GameObjectManager class
	\param
	\return
	*/
	/******************************************************************************/
	GameObjectManager::GameObjectManager( void )
		: m_gameObjVector(),
		m_baseGeometryBuilderMap()
	{
		//allocate the initial capacity
		this->m_gameObjVector.reserve( START_SIZE );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the GameObjectManager class
	\param
	\return
	*/
	/******************************************************************************/
	GameObjectManager::~GameObjectManager( void )
	{
		this->ClearGameObjects();

		BaseGeometryBuilderMap::iterator itor = this->m_baseGeometryBuilderMap.begin();
		BaseGeometryBuilderMap::iterator end = this->m_baseGeometryBuilderMap.end();

		//loop through the BaseGeometryBuilderMap iterator
		while ( itor != end )
		{
			//delete from the heap memory
			delete itor->second;
			itor->second = 0;

			++itor;
		}//end while loop

		this->m_baseGeometryBuilderMap.clear();
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
	void GameObjectManager::LoadMeshObjects( GraphicsFramework::GraphicsInterface* const /*graphicsInterfacePtr*/ )
	{
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
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::GeneratePendingGameObject( const unsigned /*gameObjIdentifier*/, const unsigned /*objectType*/, 
		GraphicsFramework::GraphicsInterface* const /*graphicsInterfacePtr*/ )
	{
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
	void GameObjectManager::GeneratePendingGameObject( const unsigned /*gameObjIdentifier*/, const unsigned /*objectType*/, 
		GraphicsFramework::GraphicsInterface* const /*graphicsInterfacePtr*/,
		const PhysicsFramework::PhysicsObject /*physicsVal*/,
		const Light::Material /*materialVal*/,
		const GameFramework::GameObjCategory /*gameObjCategory*/, 
		const bool /*moveInitialFlag*/ )
	{
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
	\param position
	the position of the object
	\param velocity
	the velocity of the object
	\param scale
	the scale of the object
	\param angleDegrees
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
	\param index
	the index of the game object
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::GeneratePendingGameObject( const unsigned /*gameObjIdentifier*/, const unsigned /*objectType*/, 
		GraphicsFramework::GraphicsInterface* const /*graphicsInterfacePtr*/, 
		const Math::Vector4 & /*position*/,
		const Math::Vector4 & /*velocity*/,
		const Math::Vector4 & /*scale*/,
		const Math::Vector4 & /*rotation*/,			
		const float	/*movementSpeed*/,
		const float	/*rotationalSpeed*/,
		const float	/*acceleration*/,
		const float	/*mass*/,
		const bool /*moveInitialFlag*/,
		const unsigned /*row*/, 
		const unsigned /*column*/, 
		const unsigned /*index*/)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the game object
	\param graphicsObj
	the graphics object that contains the graphics properties of the game object
	\param physicsObj
	the physics object that contains the physics properties of the game object
	\return GameObject
	the game object
	*/
	/******************************************************************************/
	GameObject GameObjectManager::CreateGameObject( const GraphicsFramework::GraphicsObject & graphicsObj, 
		const PhysicsFramework::PhysicsObject & physicsObj ) const
	{
		GameObject gameObj;
		//store the data
		gameObj.SetGraphicsObj( graphicsObj );
		gameObj.SetPhysicsObj( physicsObj );

		return gameObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Add the created game objects from the object manager to the new list that will be used by the game
	\param gameObjectVector
	the game object vector that will contain the list of game objects
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::AddGameObjects( GameObjectVector & gameObjectVector )
	{
		unsigned pendingSize = this->m_gameObjVector.size();
		unsigned currListSize = gameObjectVector.size();
		unsigned currIndex = 0;

		//copy all of the objects from the pending list to the current list
		for ( unsigned i = 0; i < pendingSize; ++i )
		{
			//check if there are any inactive slots available in the current list
			for ( ; currIndex < currListSize; ++currIndex )
			{
				//if the slot is inactive, replace the element
				if ( gameObjectVector.at( currIndex ).IsActive() == false )
				{
					gameObjectVector.at( currIndex ) = this->m_gameObjVector.at( i );
					gameObjectVector.at( currIndex ).SetId( currIndex );
					break;
				}
			}//end for loop

			//otherwise add it to the end of the list
			if ( currIndex == currListSize )
			{
				this->m_gameObjVector.at( i ).SetId( gameObjectVector.size() );
				gameObjectVector.push_back( this->m_gameObjVector.at( i ) );
			}

		}//end for loop

		this->m_gameObjVector.clear();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Add the created game objects from the object manager to the new list that will be used by the game
	Take note that the pending objects will be added to the current list in reverse order since we are using back() and pop_back()
	\param gameObjectVector
	the game object vector that will contain the list of game objects
	\param gameObjCategory
	the game object category that will be used for filtering
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::AddGameObjects( GameObjectVector & currGameObjectVector, const GameObjCategory gameObjCategory )
	{
		unsigned pendingSize = this->m_gameObjVector.size();
		unsigned currListSize = currGameObjectVector.size();
		unsigned currIndex = 0;

		//copy all of the objects from the pending list to the current list
		for ( unsigned i = 0; i < pendingSize; ++i )
		{
			//filter based on the game object category
			if ( this->m_gameObjVector.back().GetCategory() == gameObjCategory )
			{
				//check if there are any inactive slots available in the current list
				for ( ; currIndex < currListSize; ++currIndex )
				{
					//if the slot is inactive, replace the element
					if ( currGameObjectVector.at( currIndex ).IsActive() == false )
					{
						currGameObjectVector.at( currIndex ) = this->m_gameObjVector.back();
						currGameObjectVector.at( currIndex ).SetId( currIndex );
						break;
					}
				}//end for loop

				//otherwise add it to the end of the list
				if ( currIndex == currListSize )
				{
					this->m_gameObjVector.back().SetId( currGameObjectVector.size() );
					currGameObjectVector.push_back( this->m_gameObjVector.back() );
				}

				//pop the element after is has been added
				this->m_gameObjVector.pop_back();
			}

		}//end for loop
		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Contain the gameObj object
	\param gameObj
	the game object
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::ContainGameObject( const GameObject gameObj )
	{
		//add the game object
		this->m_gameObjVector.push_back( gameObj );
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Clear the game objects
	\param
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::ClearGameObjects( void )
	{
		this->m_gameObjVector.clear();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the physics object
	\param position
	the position of the object
	\param velocity
	the velocity of the object
	\param scale
	the scale of the object
	\param rotation
	the angle in degrees at which the object can rotate
	\param mass
	the mass of the object	
	\param movementSpeed
	the movementSpeed of the object
	\param rotationalSpeed
	the rotationalSpeed of the object
	\param acceleration
	the acceleration of the object
	\param computeDirectionFlag
	the flag to determine whether to compute the direction based on the angle
	\return PhysicsObject
	the physics object that contains the physics properties of the game object
	*/
	/******************************************************************************/
	PhysicsFramework::PhysicsObject GameObjectManager::CreatePhysicsObject( 
		const Math::Vector4 & position,
		const Math::Vector4 & velocity,
		const Math::Vector4 & scale,
		const Math::Vector4 & rotation,
		const float mass,
		const float movementSpeed,
		const float rotationalSpeed,
		const float acceleration,
		const bool computeDirectionFlag ) const
	{
		PhysicsFramework::PhysicsObject physicsObj;

		//store the data
		physicsObj.SetPosition( position );
		physicsObj.SetVelocity( velocity );
		physicsObj.SetScale( scale );
		
		physicsObj.SetAngleDegreesX( rotation.GetFloatX() );
		physicsObj.SetAngleDegreesY( rotation.GetFloatY() );
		physicsObj.SetAngleDegreesZ( rotation.GetFloatZ() );

		//for directional movement in 2D on the XY plane
		if ( computeDirectionFlag == true )
		{
			//get the normalized direction vector based on the sin and cos of the angle
			physicsObj.SetDirection( 
				Math::Vector4( cosf( Math::DegreeToRadian( rotation.GetFloatZ() ) ), 
				sinf( Math::DegreeToRadian( rotation.GetFloatZ() ) ), 
				0.0F, 0.0F ).GetNormalized()
			);
		}

		physicsObj.SetMass( mass );
		physicsObj.SetMovementSpeed( movementSpeed );
		physicsObj.SetRotationalSpeed( rotationalSpeed );
		physicsObj.SetAcceleration( acceleration );

		return physicsObj;
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Generate the vertices and indices of the mesh
	\param meshParameterContainer
	the container that contains the parameters needed to build the mesh
	\param baseGeometryBuilder
	the pointer to the BaseGeometryBuilder
	\param mesh
	the mesh
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::GenerateMesh( const GraphicsFramework::MeshParameterContainer & meshParameterContainer, 
		GraphicsFramework::BaseGeometryBuilder * const baseGeometryBuilder,
		GraphicsFramework::Mesh & mesh ) const
	{
		//compute the boundary and offset values
		baseGeometryBuilder->ComputeGeometryBoundaryAndOffset( meshParameterContainer );
		//generate the vertices of the mesh
		baseGeometryBuilder->LoadGeometryVertices( mesh, meshParameterContainer );

		/*
		for ( unsigned index = 0; index < mesh.GetNumberOfVertices(); ++index )
		{
			GraphicsFramework::Vertex vert = mesh.GetVertexArray()[index];
			int hi = 0;
		}
		*/

		//generate the indices of the mesh
		baseGeometryBuilder->GenerateGeometryIndices( mesh, meshParameterContainer );

		/*
		for ( unsigned index = 0; index < mesh.GetNumberOfIndices(); ++index )
		{
			GLushort indexVal = mesh.GetIndexArray()[index];
			int hi = 0;
		}
		*/
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the VAO, VBO and IBO of the graphics object
	\param objectType
	the object type
	\param graphicsInterface
	the graphics interface
	\param mesh
	the mesh
	\return GraphicsObject
	the graphics object that contains the graphics properties
	*/
	/******************************************************************************/
	GraphicsFramework::GraphicsObject GameObjectManager::CreateGraphicsObject( const unsigned objectType,
		GraphicsFramework::GraphicsInterface * const graphicsInterface,
		GraphicsFramework::Mesh & mesh ) const
	{
		//validate if the mesh is empty
		ASSERT( mesh.GetVertexArray() == NULL || mesh.GetIndexArray() == NULL, 
			"The mesh is empty" );

		GraphicsFramework::GraphicsObject graphicsObj;

		//load the mesh to the buffer and store the VAO, VBO and IBO in the graphics object
		graphicsInterface->LoadToBuffer( graphicsObj, mesh );

		//add the graphics object to the graphics object map in the graphics interface
		graphicsInterface->ContainGraphicsObject( objectType, graphicsObj );

		return graphicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the VAO, VBO and IBO as well as the texture of the graphics object
	\param objectType
	the object type
	\param graphicsInterface
	the graphics interface
	\param mesh
	the mesh
	\param envTextureName
	the name of the environment texture
	\param textureName
	the array containing the name of the textures
	\param arrSize
	the array size
	\return GraphicsObject
	the graphics object that contains the graphics properties
	*/
	/******************************************************************************/
	GraphicsFramework::GraphicsObject GameObjectManager::CreateGraphicsObject( const unsigned objectType,
		GraphicsFramework::GraphicsInterface * const graphicsInterface,
		GraphicsFramework::Mesh & mesh,
		const char * envTextureName,
		const char ** textureName, const unsigned arrSize ) const
	{
		//validate if the mesh is empty
		ASSERT( mesh.GetVertexArray() == NULL || mesh.GetIndexArray() == NULL, 
			"The mesh is empty" );

		GraphicsFramework::GraphicsObject graphicsObj;

		//load the mesh to the buffer and store the VAO, VBO and IBO in the graphics object
		graphicsInterface->LoadToBuffer( graphicsObj, mesh );

		//store the textures
		for ( unsigned index = 0; index < arrSize; ++index )
		{
			//retrieve the texture id based on the name
			unsigned textureId = graphicsInterface->GetTexture( textureName[index] );
			//store the texture id in the graphics object
			graphicsObj.SetTextureId( textureId, index );
		}//end for loop

		if ( envTextureName != 0 )
		{
			//retrieve the environment texture id based on the name
			unsigned envTextureId = graphicsInterface->GetEnvTexture( envTextureName );
			//store the environment texture id
			graphicsObj.SetEnvTextureId( envTextureId );
		}

		//add the graphics object to the graphics object map in the graphics interface
		graphicsInterface->ContainGraphicsObject( objectType, graphicsObj );

		return graphicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load the texture image
	\param graphicsInterface
	the graphics interface
	\param textureName
	the name of the texture
	\param filename
	the file name
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::LoadTextureImage( GraphicsFramework::GraphicsInterface * const graphicsInterface,
		const char * textureName, const char* fileName ) const
	{
		GraphicsFramework::ImageObj imageObj;

		//load the texture image from file
		this->LoadImageFromFile( imageObj, textureName, fileName );		

		//load the image data found in the mesh to the buffer
		graphicsInterface->LoadImageToBuffer( textureName, imageObj );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load the cube map images that will be used for environment mapping
	\param graphicsInterface
	the graphics interface
	\param cubeMapName
	the name of the cube map
	\param rightTextureName
	the name of the texture for the right face
	\param rightImgFilename
	the file name of the image for the right face
	\param leftTextureName
	the name of the texture for the left face
	\param leftImgFilename
	the file name of the image for the left face
	\param topTextureName
	the name of the texture for the top face
	\param topImgFilename
	the file name of the image for the top face
	\param bottomTextureName
	the name of the texture for the bottom face
	\param bottomImgFilename
	the file name of the image for the bottom face
	\param frontTextureName
	the name of the texture for the front face
	\param frontImgFilename
	the file name of the image for the front face
	\param backTextureName
	the name of the texture for the back face
	\param backImgFilename
	the file name of the image for the back face
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::LoadCubeMapImages( GraphicsFramework::GraphicsInterface * const graphicsInterface, const char * cubeMapName,
		const char * rightTextureName, const char* rightImgFilename,
		const char * leftTextureName, const char* leftImgFilename,
		const char * topTextureName, const char* topImgFilename,
		const char * bottomTextureName, const char* bottomImgFilename,
		const char * frontTextureName, const char* frontImgFilename,
		const char * backTextureName, const char* backImgFilename
		) const
	{
		GraphicsFramework::ImageObj rightImageObj;
		GraphicsFramework::ImageObj leftImageObj;
		GraphicsFramework::ImageObj topImageObj;
		GraphicsFramework::ImageObj bottomImageObj;
		GraphicsFramework::ImageObj frontImageObj;
		GraphicsFramework::ImageObj backImageObj;

		//load the texture images from file
		this->LoadImageFromFile( rightImageObj, rightTextureName, rightImgFilename );
		this->LoadImageFromFile( leftImageObj, leftTextureName, leftImgFilename );
		this->LoadImageFromFile( topImageObj, topTextureName, topImgFilename );
		this->LoadImageFromFile( bottomImageObj, bottomTextureName, bottomImgFilename );
		this->LoadImageFromFile( frontImageObj, frontTextureName, frontImgFilename );
		this->LoadImageFromFile( backImageObj, backTextureName, backImgFilename );

		//store the image object in the array
		GraphicsFramework::ImageObj * imageObjArr = new GraphicsFramework::ImageObj[ 6 ];
		imageObjArr[ 0 ] = 	rightImageObj;
		imageObjArr[ 1 ] = 	leftImageObj;
		imageObjArr[ 2 ] = 	topImageObj;
		imageObjArr[ 3 ] = 	bottomImageObj;
		imageObjArr[ 4 ] = 	frontImageObj;
		imageObjArr[ 5 ] = 	backImageObj;

		//store the image names in the array
		const char ** imageNameArr = new const char*[ 6 ];
		imageNameArr[ 0 ] = rightTextureName;
		imageNameArr[ 1 ] = leftTextureName;
		imageNameArr[ 2 ] = topTextureName;
		imageNameArr[ 3 ] = bottomTextureName;
		imageNameArr[ 4 ] = frontTextureName;
		imageNameArr[ 5 ] = backTextureName;

		//load the image data found in the mesh to the buffer
		graphicsInterface->LoadCubeMapToBuffer( cubeMapName, imageNameArr, imageObjArr, 6 );

		//load the cube map to the FBO
		graphicsInterface->LoadTexMapToFBO( cubeMapName, rightImageObj.GetImageWidth(), rightImageObj.GetImageHeight() );

		delete [] imageNameArr;
		delete [] imageObjArr;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load the dual paraboloid map images that will be used for environment mapping
	\param graphicsInterface
	the graphics interface
	\param frontTextureName
	the name of the texture for the front face
	\param frontImgFilename
	the file name of the image for the front face
	\param backTextureName
	the name of the texture for the back face
	\param backImgFilename
	the file name of the image for the back face
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::LoadDualParaboloidImages( GraphicsFramework::GraphicsInterface * const graphicsInterface,
		const char * frontTextureName, const char* /*frontImgFilename*/,
		const char * backTextureName, const char* /*backImgFilename*/
		) const
	{
		//GraphicsFramework::ImageObj frontImageObj;
		//GraphicsFramework::ImageObj backImageObj;

		//load the texture images from file
		//this->LoadImageFromFile( frontImageObj, frontTextureName, frontImgFilename );
		//this->LoadImageFromFile( backImageObj, backTextureName, backImgFilename );

		//load the image data found in the mesh to the buffer
		//graphicsInterface->LoadImageToBuffer( frontTextureName, frontImageObj );
		//graphicsInterface->LoadImageToBuffer( backTextureName, backImageObj );
		graphicsInterface->AllocateImageToBuffer( frontTextureName, GraphicsFramework::ENVMAP_VIEWPORT_SIZE, GraphicsFramework::ENVMAP_VIEWPORT_SIZE );
		graphicsInterface->AllocateImageToBuffer( backTextureName, GraphicsFramework::ENVMAP_VIEWPORT_SIZE, GraphicsFramework::ENVMAP_VIEWPORT_SIZE );

		//load the dual paraboloid maps to the FBO
		graphicsInterface->LoadTexMapToFBO( frontTextureName, GraphicsFramework::ENVMAP_VIEWPORT_SIZE, GraphicsFramework::ENVMAP_VIEWPORT_SIZE );
		graphicsInterface->LoadTexMapToFBO( backTextureName, GraphicsFramework::ENVMAP_VIEWPORT_SIZE, GraphicsFramework::ENVMAP_VIEWPORT_SIZE );
		//graphicsInterface->LoadTexMapToFBO( frontTextureName, frontImageObj.GetImageWidth(), frontImageObj.GetImageHeight() );
		//graphicsInterface->LoadTexMapToFBO( backTextureName, backImageObj.GetImageWidth(), backImageObj.GetImageHeight() );

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load the texture image from file to the mesh
	\param mesh
	the mesh that will contain the image data
	\param textureName
	the name of the texture
	\param filename
	the file name
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::LoadImageFromFile( GraphicsFramework::ImageObj & imageObj, const char * textureName, const char* filename ) const
	{
		//read from the compressed version of the file
		File::CustomFileHandler fileHandler;
		if ( fileHandler.ReadFile( textureName ) == true )
		{
			imageObj.SetImageData( fileHandler.GetFileData() );
			imageObj.SetImageWidth( fileHandler.GetImageWidth() );
			imageObj.SetImageHeight( fileHandler.GetImageHeight() );
			imageObj.SetImageSize( fileHandler.GetFileDataSize() );
			imageObj.SetInternalFormat( fileHandler.GetInternalFormat() );
		}
		else
		{
			//load and store the texture information from the uncompressed TGA format
			File::TGALoader tgaLoader;
			tgaLoader.Load( filename );
			imageObj.SetImageData( tgaLoader.GetImageData() );
			imageObj.SetImageTypeCode( tgaLoader.GetImageTypeCode() );
			imageObj.SetImageBpp( tgaLoader.GetImageBpp() );
			imageObj.SetImageWidth( tgaLoader.GetImageWidth() );
			imageObj.SetImageHeight( tgaLoader.GetImageHeight() );
			imageObj.SetImageSize( tgaLoader.GetImageWidth() * tgaLoader.GetImageHeight() * ( tgaLoader.GetImageBpp() / 8 ) );	
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Contain the base geometry builder
	\param objectType
	the type of object
	\param baseGeometryBuilder*
	the pointer to the base geometry builder
	\return
	*/
	/******************************************************************************/
	void GameObjectManager::ContainBaseGeometryBuilder( const unsigned objectType, GraphicsFramework::BaseGeometryBuilder * const baseGeometryBuilder )
	{
		//insert the base geometry builder
		this->m_baseGeometryBuilderMap.insert( std::make_pair( objectType, baseGeometryBuilder ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Retrieve the pointer to the base geometry builder
	\param objectType
	the type of object
	\return BaseGeometryBuilder*
	the pointer to the base geometry builder
	*/
	/******************************************************************************/
	const GraphicsFramework::BaseGeometryBuilder * const GameObjectManager::RetrieveBaseGeometryBuilder( const unsigned objectType )
	{
		//retrieve the value from the map
		return this->m_baseGeometryBuilderMap.find( objectType )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the map that contains pointers to base geometry builders
	\param 
	\return BaseGeometryBuilderMap &
	the reference to the map that contains pointers to base geometry builders
	*/
	/******************************************************************************/
	const BaseGeometryBuilderMap & GameObjectManager::GetBaseGeometryBuilderMap( void ) const
	{
		return this->m_baseGeometryBuilderMap;
	}


} //end namespace GameFramework