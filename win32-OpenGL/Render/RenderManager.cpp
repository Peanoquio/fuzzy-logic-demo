/******************************************************************************/
/*!
\file RenderManager.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 18/02/2012
\brief
This is the render manager responsible for rendering different effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "RenderManager.h"
#include "../Graphics/GraphicsInterface.h"


namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The constructor of the RenderManager class

	\param
	\return
	*/
	/******************************************************************************/
	RenderManager::RenderManager( void )
		:m_cgContext(),
		m_graphicsInterfacePtr( 0 ),
		m_gameObjMgrPtr( 0 ),
		m_effectsMap(),
		m_projector(),
		m_directionalLight(),
		m_omniLight(),
		m_spotLight()
	{	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The destructor of the RenderManager class

	\param
	\return
	*/
	/******************************************************************************/
	RenderManager::~RenderManager( void )
	{
		this->Shutdown();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the render manager

	\param graphicsInterfacePtr
	the pointer to the graphics interface
	\param gameObjMgrPtr
	the pointer to the game object manager
	\return
	*/
	/******************************************************************************/
	void RenderManager::Init( GraphicsInterface * graphicsInterfacePtr, GameFramework::GameObjectManager * gameObjMgrPtr )
	{
		//store the pointers
		this->m_graphicsInterfacePtr = graphicsInterfacePtr;
		this->m_gameObjMgrPtr = gameObjMgrPtr;

		// 1. create a CG context
		this->m_cgContext = cgCreateContext();

		// TODO: error checking
		//CGerror error;
		//const char* errorString = cgGetLastErrorString( &error );		
		//errorString = cgGetErrorString( error );
		//ASSERT ( error != NULL, errorString );		

		#ifdef _DEBUG
		// 2. set debug flag on/off
		cgGLSetDebugMode( CG_TRUE );
		#endif

		// 3. set parameter mode
		cgSetParameterSettingMode( this->m_cgContext, CG_DEFERRED_PARAMETER_SETTING );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Shut down the render manager

	\param
	\return
	*/
	/******************************************************************************/
	void RenderManager::Shutdown( void )
	{
		//release the effects
		//get the iterators of the map
		EffectsMap::iterator effectsMapItor = this->m_effectsMap.begin();
		EffectsMap::iterator effectsMapEnd = this->m_effectsMap.end();

		//loop through the iterator
		while ( effectsMapItor != effectsMapEnd )
		{
			//release the effect
			effectsMapItor->second->Release();
			//remove from heap
			delete effectsMapItor->second;
			effectsMapItor->second = 0;

			++effectsMapItor;
		}//end while loop

		this->m_effectsMap.clear();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the effect

	\param renderEffect
	the render effect to serve as the identifier
	\param effectsPtr
	the pointer to the effect
	\return
	*/
	/******************************************************************************/
	void RenderManager::InitEffect( const RENDER_EFFECT renderEffect, Effects * effectsPtr )
	{
		effectsPtr->Init( this->m_cgContext );

		//store the effect
		this->m_effectsMap.insert( std::make_pair( renderEffect, effectsPtr ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initialize the effect

	\param renderEffect
	the render effect to serve as the identifier
	\param effectsPtr
	the pointer to the effect
	\param vtxEffectFlag
	if true, it will be a vertex effect, otherwise it's a fragment effect
	\return
	*/
	/******************************************************************************/
	void RenderManager::InitEffect( const RENDER_EFFECT renderEffect, Effects * effectsPtr, bool vtxEffectFlag )
	{
		effectsPtr->Init( this->m_cgContext, vtxEffectFlag );

		//store the effect
		this->m_effectsMap.insert( std::make_pair( renderEffect, effectsPtr ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Retrieves the pointer to the desired effect

	\param renderEffect
	the render effect type
	\return Effects *
	the pointer to the effect
	*/
	/******************************************************************************/
	Effects * RenderManager::GetEffect( const RENDER_EFFECT renderEffect ) const
	{
		return this->m_effectsMap.find( renderEffect )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the directional light

	\param
	\return DirectionalLight
	the directional light
	*/
	/******************************************************************************/
	Light::DirectionalLight & RenderManager::GetDirectionalLight( void )
	{
		return this->m_directionalLight;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the omni-directional point light

	\param
	\return OmniLight
	the omni-directional point light
	*/
	/******************************************************************************/
	Light::OmniLight & RenderManager::GetOmniLight( void )
	{
		return this->m_omniLight;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the spot light

	\param
	\return SpotLight
	the spot light
	*/
	/******************************************************************************/
	Light::SpotLight & RenderManager::GetSpotLight( void )
	{
		return this->m_spotLight;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the projector

	\param
	\return LookAt
	the projector
	*/
	/******************************************************************************/
	LookAt::LookAt & RenderManager::GetProjector( void )
	{
		return this->m_projector;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Apply the transformation of the game object
	\param gameObj
	the game object
	\return Mtx44
	the object transformation matrix
	*/
	/******************************************************************************/
	const Math::Mtx44 RenderManager::GetObjectTransformation( GameFramework::GameObject & gameObj ) const
	{
		Math::Mtx44 xRotateMtx;
		Math::Mtx44 yRotateMtx;
		Math::Mtx44 zRotateMtx;
		Math::Mtx44 scaleMtx;
		Math::Mtx44 translateMtx;

		//Math::Mtx44 negScaleMtx;
		//negScaleMtx.SetToScale( 1.0F, 1.0F, -1.0F );

		//set scale
		scaleMtx.SetToScale( 
			gameObj.GetPhysicsObj().GetScale().GetFloatX(), 
			gameObj.GetPhysicsObj().GetScale().GetFloatY(), 
			gameObj.GetPhysicsObj().GetScale().GetFloatZ() );
		//set rotation
		xRotateMtx.SetToRotationDegreesX( gameObj.GetPhysicsObj().GetAngleDegreesX() );
		yRotateMtx.SetToRotationDegreesY( gameObj.GetPhysicsObj().GetAngleDegreesY() );		
		zRotateMtx.SetToRotationDegreesZ( gameObj.GetPhysicsObj().GetAngleDegreesZ() );			
		//set translation
		translateMtx.SetToTranslation( 
			gameObj.GetPhysicsObj().GetPosition().GetFloatX(), 
			gameObj.GetPhysicsObj().GetPosition().GetFloatY(), 
			gameObj.GetPhysicsObj().GetPosition().GetFloatZ() );

		//return the concatenated transformation matrices
		return ( translateMtx * zRotateMtx * yRotateMtx * xRotateMtx * scaleMtx );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Create the texture generator matrix
	\param modelMtx
	the model matrix
	\param viewMtx
	the view matrix
	\param projMtx
	the projection matrix
	\return
	*/
	/******************************************************************************/
	const Math::Mtx44 RenderManager::CreateTexGenMtx( const Math::Mtx44 & modelMtx, const Math::Mtx44 & viewMtx, const Math::Mtx44 & projMtx ) const
	{
		//construct the matrix to contrain the values of the computed matrix within 0 to 1 range
		const Math::Mtx44 halfMtx( 0.5F, 0.0F, 0.0F, 0.0F, 
									0.0F, 0.5F, 0.0F, 0.0F,
									0.0F, 0.0F, 0.5F, 0.0F,
									0.5F, 0.5F, 0.5F, 1.0F );

		return ( halfMtx * projMtx * viewMtx * modelMtx );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Generates the dynamic cube map environment

	\param cubeMapTextureName
	the cube map texture name
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::GenerateCubeMap( const char * cubeMapTextureName, 
		const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector )
	{
		unsigned textureId = this->m_graphicsInterfacePtr->GetEnvTexture( cubeMapTextureName );
		//unsigned depthTextureId = this->m_graphicsInterfacePtr->GetEnvDepthTexture( cubeMapTextureName );
		unsigned fboId = this->m_graphicsInterfacePtr->GetEnvTextureFBO( cubeMapTextureName );
		//unsigned rboId = this->m_graphicsInterfacePtr->GetEnvTextureRBO( cubeMapTextureName );

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fboId );
		//glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, rboId );

		float dt = 0;

		//set up the projection matrix     
		float FOV = 90.0F;
		float aspectRatio = 1.0F;
		Math::Mtx44 projMatrix;
		projMatrix.Perspective ( FOV, aspectRatio, 0.1F, 100.0F );

		//set up the camera view matrix with respect to the position of the current game object
		Camera::Camera viewMatrix;
		viewMatrix.SetCameraPosition( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0f ) );	
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		//loop through the six faces of the cube
		for ( unsigned index = 0; index < 6; ++index )
		{
			GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + index;

			//tell the OpenGL to render to the FBO instead of the frame budder
			// attach the texture to FBO color attachment point
			glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, face, textureId, 0 );				

			// attach the renderbuffer to depth attachment point
			//glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboId );			

			//synch the camera orientation with cube face then generate the view matrix
			if ( face == GL_TEXTURE_CUBE_MAP_POSITIVE_X )
			{
				//right
				viewMatrix.SetCameraTarget( Math::Vector4( 1.0F, 0.0F, 0.0F, 1.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_NEGATIVE_X )
			{
				//left
				viewMatrix.SetCameraTarget( Math::Vector4( -1.0F, 0.0F, 0.0F, 1.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_POSITIVE_Y )
			{
				//up
				viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, 1.0F, 0.0F, 1.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, 0.0F, 1.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y )
			{
				//down
				viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, -1.0F, 0.0F, 1.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, 0.0F, -1.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_POSITIVE_Z )
			{
				//back
				viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, 0.0F, 1.0F, 1.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_NEGATIVE_Z )
			{
				//front
				viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, 0.0F, -1.0F, 1.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}

			viewMatrix.RecomputeViewDirectionVector();

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			//draw/render the objects on the cube face
			this->DrawObjects( dt, renderEffect, lightEffect, projTexName,
				currGameObjectVector, 
				projMatrix, viewMatrix.GenerateViewTransformMtx() );

		}//end for loop	

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool fboUsed = true;
		// check FBO status
		GLenum status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
		if ( status != GL_FRAMEBUFFER_COMPLETE_EXT )
			fboUsed = false;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		// switch back to window-system-provided framebuffer
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
		//glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_CUBE_MAP, textureId );
		glEnable( GL_TEXTURE_CUBE_MAP );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Mipmaps of a texture can be automatically generated with the glGenerateMipmap function. 
		//OpenGL 3.0 or greater is required for this function (or the extension GL_ARB_framebuffer_object).
		//glGenerateMipmap( GL_TEXTURE_CUBE_MAP );  //Generate mipmaps now!!!
		//In GL 3.0, GL_GENERATE_MIPMAP is deprecated, and in 3.1 and above, it was removed. So for those versions, you must use glGenerateMipmap.
		//glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE ); 
		glGenerateMipmapEXT( GL_TEXTURE_CUBE_MAP );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Generates the dynamic cube map environment

	\param cubeMapTextureName
	the cube map texture name
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	\param sourcePosition
	the position of the game object from where the camera will take the snap shot of the environment
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::GenerateCubeMap( const char * cubeMapTextureName, 
		const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector,
		const Math::Vector4 & sourcePosition )
	{
		this->m_graphicsInterfacePtr->SetViewPort( 0, 0, ENVMAP_VIEWPORT_SIZE, ENVMAP_VIEWPORT_SIZE );

		unsigned textureId = this->m_graphicsInterfacePtr->GetEnvTexture( cubeMapTextureName );
		//unsigned depthTextureId = this->m_graphicsInterfacePtr->GetEnvDepthTexture( cubeMapTextureName );
		unsigned fboId = this->m_graphicsInterfacePtr->GetEnvTextureFBO( cubeMapTextureName );
		//unsigned rboId = this->m_graphicsInterfacePtr->GetEnvTextureRBO( cubeMapTextureName );

		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fboId );
		//glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, rboId );

		float dt = 0;

		//set up the projection matrix     
		float FOV = 90.0F;
		float aspectRatio = 1.0F;
		Math::Mtx44 projMatrix;
		projMatrix.Perspective ( FOV, aspectRatio, 0.1F, 100.0F );

		//set up the camera view matrix with respect to the position of the current game object
		Camera::Camera viewMatrix;
		//viewMatrix.SetCameraPosition( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0f ) );	
		viewMatrix.SetCameraPosition( sourcePosition );		
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		//loop through the six faces of the cube
		for ( unsigned index = 0; index < 6; ++index )
		{
			GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + index;

			//tell the OpenGL to render to the FBO instead of the frame budder
			// attach the texture to FBO color attachment point
			glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, face, textureId, 0 );				

			// attach the renderbuffer to depth attachment point
			//glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboId );			

			//synch the camera orientation with cube face then generate the view matrix
			if ( face == GL_TEXTURE_CUBE_MAP_POSITIVE_X )
			{
				//right
				//viewMatrix.SetCameraTarget( Math::Vector4( 1.0F, 0.0F, 0.0F, 1.0f ) );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 1.0F, 0.0F, 0.0F, 0.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_NEGATIVE_X )
			{
				//left
				//viewMatrix.SetCameraTarget( Math::Vector4( -1.0F, 0.0F, 0.0F, 1.0f ) );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( -1.0F, 0.0F, 0.0F, 0.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_POSITIVE_Y )
			{
				//up
				//viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, 1.0F, 0.0F, 1.0f ) );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, 0.0F, 1.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y )
			{
				//down
				//viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, -1.0F, 0.0F, 1.0f ) );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, 0.0F, -1.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_POSITIVE_Z )
			{
				//back
				//viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, 0.0F, 1.0F, 1.0f ) );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 0.0F, 0.0F, 1.0F, 0.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}
			else if ( face == GL_TEXTURE_CUBE_MAP_NEGATIVE_Z )
			{
				//front
				//viewMatrix.SetCameraTarget( Math::Vector4( 0.0F, 0.0F, -1.0F, 1.0f ) );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 0.0F, 0.0F, -1.0F, 0.0f ) );
				viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, -1.0F, 0.0F, 0.0f ) );
			}

			//viewMatrix.RecomputeViewDirectionVector();

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			//draw/render the objects on the cube face
			this->DrawObjects( dt, renderEffect, lightEffect, projTexName,
				currGameObjectVector, 
				projMatrix, viewMatrix.GenerateViewTransformMtx() );

		}//end for loop	

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool fboUsed = true;
		// check FBO status
		GLenum status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
		if ( status != GL_FRAMEBUFFER_COMPLETE_EXT )
			fboUsed = false;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		// switch back to window-system-provided framebuffer
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
		//glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_CUBE_MAP, textureId );
		glEnable( GL_TEXTURE_CUBE_MAP );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Mipmaps of a texture can be automatically generated with the glGenerateMipmap function. 
		//OpenGL 3.0 or greater is required for this function (or the extension GL_ARB_framebuffer_object).
		//glGenerateMipmap( GL_TEXTURE_CUBE_MAP );  //Generate mipmaps now!!!
		//In GL 3.0, GL_GENERATE_MIPMAP is deprecated, and in 3.1 and above, it was removed. So for those versions, you must use glGenerateMipmap.
		//glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE ); 
		glGenerateMipmapEXT( GL_TEXTURE_CUBE_MAP );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Generates the dynamic paraboloid map environment

	\param frontMapTextureName
	the front map texture name
	\param backMapTextureName
	the back map texture name
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	\param sourcePosition
	the position of the game object from where the camera will take the snap shot of the environment
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::GenerateDualParaboloidMap( const char * frontMapTextureName, const char * backMapTextureName,
		const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector, 
		const Math::Vector4 & sourcePosition )
	{
		//glClearColor( 0, 0, 0, 0 );

		this->m_graphicsInterfacePtr->SetViewPort( 0, 0, ENVMAP_VIEWPORT_SIZE, ENVMAP_VIEWPORT_SIZE );
		
		unsigned fboId = 0;
		unsigned rboId = 0;
		unsigned textureId = 0;
		int faceValue = 1;		

		//render to the front and back face of the paraboloid map
		for ( unsigned index = 0; index < 2; ++index )
		{
			bool fboUsed = true;
			GLenum status;

			float dt = 0;

			//set up the projection matrix     
			float FOV = 90.0F;
			float aspectRatio = 1.0F;
			Math::Mtx44 projMatrix;
			projMatrix.Perspective ( FOV, aspectRatio, 0.1F, 100.0F );

			//set up the camera view matrix with respect to the position of the current game object
			Camera::Camera viewMatrix;
			//viewMatrix.SetCameraPosition( Math::Vector4( 0.0F, 0.0F, 0.0F, 1.0f ) );	
			viewMatrix.SetCameraPosition( sourcePosition );	

			viewMatrix.SetWorldUpVector( Math::Vector4( 0.0F, 1.0F, 0.0F, 0.0f ) );

			if ( index == 0 )
			{				
				//front
				fboId = this->m_graphicsInterfacePtr->GetEnvTextureFBO( frontMapTextureName );
				rboId = this->m_graphicsInterfacePtr->GetEnvTextureRBO( frontMapTextureName );
				textureId = this->m_graphicsInterfacePtr->GetTexture( frontMapTextureName );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 0.0F, 0.0F, -1.0F, 0.0f ) );
				faceValue = -1;
			}
			else
			{
				//back
				fboId = this->m_graphicsInterfacePtr->GetEnvTextureFBO( backMapTextureName );
				rboId = this->m_graphicsInterfacePtr->GetEnvTextureRBO( backMapTextureName );
				textureId = this->m_graphicsInterfacePtr->GetTexture( backMapTextureName );
				viewMatrix.SetCameraViewDirectionVector( Math::Vector4( 0.0F, 0.0F, 1.0F, 0.0f ) );
				faceValue = -1;
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////			

			//tell the OpenGL to render to the FBO instead of the frame budder
			// attach the texture to FBO color attachment point
			glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fboId );
			glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureId, 0 );

			//bind the rbo for depth testing
			glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, rboId );
			glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, GraphicsFramework::ENVMAP_VIEWPORT_SIZE, GraphicsFramework::ENVMAP_VIEWPORT_SIZE );
			// attach the renderbuffer to depth attachment point
			glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboId );

			// check FBO status
			status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
			if ( status != GL_FRAMEBUFFER_COMPLETE_EXT )
				fboUsed = false;			

			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			// check FBO status
			status = glCheckFramebufferStatusEXT( GL_FRAMEBUFFER_EXT );
			if ( status != GL_FRAMEBUFFER_COMPLETE_EXT )
				fboUsed = false;

			//draw/render the objects on the face
			this->DrawObjectsToDualParaboloid( dt, renderEffect, lightEffect, projTexName,
				currGameObjectVector, 
				projMatrix, viewMatrix.GenerateViewTransformMtx(), faceValue );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// bind the texture name to the texture target
			glBindTexture( GL_TEXTURE_2D, textureId );
			glEnable( GL_TEXTURE_2D );
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Mipmaps of a texture can be automatically generated with the glGenerateMipmap function. 
			//OpenGL 3.0 or greater is required for this function (or the extension GL_ARB_framebuffer_object).
			//glGenerateMipmap( GL_TEXTURE_2D );  //Generate mipmaps now!!!
			//In GL 3.0, GL_GENERATE_MIPMAP is deprecated, and in 3.1 and above, it was removed. So for those versions, you must use glGenerateMipmap.
			//glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE ); 
			glGenerateMipmapEXT( GL_TEXTURE_2D );
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// bind the texture name to the texture target
			glBindTexture( GL_TEXTURE_2D, 0 );
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// switch back to window-system-provided framebuffer
			glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
			glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );

		}//end for loop
		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws/renders the objects based on the render and lighting effects

	\param dt
	the frame time
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	\param projMatrix
	the projection matrix
	\param viewMatrix
	the view matrix
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::DrawObjects( float /*dt*/, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector, 
		const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//retrieve the effect 
		Effects * effectsPtr = this->GetEffect( renderEffect );

		//enable vertex shader
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( "vtxShader" )->second;
		vtxShader.EnableProfile();
		vtxShader.BindProgram();
		//enable fragment shader
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( "fragShader" )->second;
		fragShader.EnableProfile();
		fragShader.BindProgram();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		//render/draw the object
		//loop through the game objects
		for ( size_t index = 0; index < currGameObjectVector.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = currGameObjectVector.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false )
			{
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			//render the game object
			this->RenderObject( effectsPtr, renderEffect, lightEffect, projTexName, gameObj, projMatrix, viewMatrix );			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws/renders the objects based on the render and lighting effects to the dual paraboloid map

	\param dt
	the frame time
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	\param projMatrix
	the projection matrix
	\param viewMatrix
	the view matrix
	\param faceValue
	determines which face of the dual paraboloid to render: 0 = front, 1 = back
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::DrawObjectsToDualParaboloid( float /*dt*/, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector, 
		const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix, const int faceValue )
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//retrieve the effect 
		Effects * effectsPtr = this->GetEffect( renderEffect );

		//enable vertex shader
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( "vtxShader" )->second;
		vtxShader.EnableProfile();
		vtxShader.BindProgram();
		//enable fragment shader
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( "fragShader" )->second;
		fragShader.EnableProfile();
		fragShader.BindProgram();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		//render/draw the object
		//loop through the game objects
		for ( size_t index = 0; index < currGameObjectVector.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = currGameObjectVector.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false )
			{
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			//render the game object to the dual paraboloid map
			this->RenderToDualParaboloid( effectsPtr, renderEffect, lightEffect, projTexName, gameObj, projMatrix, viewMatrix, faceValue );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws/renders the objects based on the render and lighting effects on the cube map

	\param dt
	the frame time
	\param cubeMapTextureName
	the name of the cube map texture
	\param sampleRenderEffect
	the render effect of the objects to be sampled to the cube map
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	\param sampleGameObjectVector
	the vector that contains game objects to be sampled to the cube map
	\param projMatrix
	the projection matrix
	\param viewMatrix
	the view matrix
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::DrawObjects( float /*dt*/, const char * cubeMapTextureName, const RENDER_EFFECT sampleRenderEffect,
		const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector, GameObjVector & sampleGameObjectVector,
		const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix )
	{
		//loop through the game objects
		for ( size_t index = 0; index < currGameObjectVector.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = currGameObjectVector.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false )
			{
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//generate the cube map
			this->GenerateCubeMap( cubeMapTextureName, sampleRenderEffect, lightEffect, projTexName, sampleGameObjectVector, gameObj.GetPhysicsObj().GetPosition() );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
			//retrieve the effect 
			Effects * effectsPtr = this->GetEffect( renderEffect );

			//enable vertex shader
			Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( "vtxShader" )->second;
			vtxShader.EnableProfile();
			vtxShader.BindProgram();
			//enable fragment shader
			Shader::Shader fragShader = effectsPtr->GetShaderMap().find( "fragShader" )->second;
			fragShader.EnableProfile();
			fragShader.BindProgram();

			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			this->m_graphicsInterfacePtr->SetViewPort( 0, 0, 
				static_cast<unsigned>( this->m_graphicsInterfacePtr->GetScreenWidth() ), 
				static_cast<unsigned>( this->m_graphicsInterfacePtr->GetScreenHeight() ) );

			//render the game object
			this->RenderObject( effectsPtr, renderEffect, lightEffect, projTexName, gameObj, projMatrix, viewMatrix );			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws/renders the objects based on the render and lighting effects on the dual paraboloid map

	\param dt
	the frame time
	\param frontMapTextureName
	the name of the front map texture
	\param backMapTextureName
	the name of the back map texture
	\param sampleRenderEffect
	the render effect of the objects to be sampled to the dual paraboloid map
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param currGameObjectVector
	the vector that contains game objects
	\param sampleGameObjectVector
	the vector that contains game objects to be sampled to the dual paraboloid map
	\param projMatrix
	the projection matrix
	\param viewMatrix
	the view matrix
	
	\return
	*/
	/******************************************************************************/
	void RenderManager::DrawObjects( float /*dt*/, const char * frontMapTextureName, const char * backMapTextureName, const RENDER_EFFECT sampleRenderEffect,
		const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameObjVector & currGameObjectVector, GameObjVector & sampleGameObjectVector,
		const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix )
	{
		//loop through the game objects
		for ( size_t index = 0; index < currGameObjectVector.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = currGameObjectVector.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false )
			{
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//generate the paraboloid map
			this->GenerateDualParaboloidMap( frontMapTextureName, backMapTextureName, 
				sampleRenderEffect, lightEffect, projTexName, sampleGameObjectVector, gameObj.GetPhysicsObj().GetPosition() );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			unsigned frontFaceTextureId = this->m_graphicsInterfacePtr->GetTexture( frontMapTextureName );
			unsigned backFaceTextureId = this->m_graphicsInterfacePtr->GetTexture( backMapTextureName );

			gameObj.GetGraphicsObj().SetFrontFaceEnvTextureId( frontFaceTextureId );
			gameObj.GetGraphicsObj().SetBackFaceEnvTextureId( backFaceTextureId );

			/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
			//retrieve the effect 
			Effects * effectsPtr = this->GetEffect( renderEffect );

			//enable vertex shader
			Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( "vtxShader" )->second;
			vtxShader.EnableProfile();
			vtxShader.BindProgram();
			//enable fragment shader
			Shader::Shader fragShader = effectsPtr->GetShaderMap().find( "fragShader" )->second;
			fragShader.EnableProfile();
			fragShader.BindProgram();

			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			this->m_graphicsInterfacePtr->SetViewPort( 0, 0, 
				static_cast<unsigned>( this->m_graphicsInterfacePtr->GetScreenWidth() ), 
				static_cast<unsigned>( this->m_graphicsInterfacePtr->GetScreenHeight() ) );

			//render the game object
			this->RenderObject( effectsPtr, renderEffect, lightEffect, projTexName, gameObj, projMatrix, viewMatrix );			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//vtxShader.DisableProfile();
			//fragShader.DisableProfile();

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws/renders the object

	\param effectsPtr
	the pointer to the effect
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param gameObj
	the game object
	\param projMatrix
	the projection matrix
	\param viewMatrix
	the view matrix

	\return
	*/
	/******************************************************************************/
	void RenderManager::RenderObject( const Effects * effectsPtr, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect, 
		const char * projTexName,
		GameFramework::GameObject & gameObj, 
		const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix )
	{
		Math::Mtx44 mvpMatrix;
		Math::Mtx44 modelViewMatrix;
		Math::Mtx44 modelMatrix;
	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//set up the matrix transformations

		//store the model matrix
		modelMatrix = this->GetObjectTransformation( gameObj );
		//set the model view matrix
		modelViewMatrix = viewMatrix * modelMatrix;

		//set the model-view-projection matrix
		mvpMatrix = projMatrix * modelViewMatrix;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//create the texture generation matrix
		Math::Mtx44 texGenMtx = this->CreateTexGenMtx( 
			modelMatrix, 
			this->m_projector.GenerateViewTransformMtx(), 
			projMatrix );

		//GLuint projTextureId = this->m_graphicsInterfacePtr->GetTexture( "EthanCochardLongboard" );
		GLuint projTextureId = this->m_graphicsInterfacePtr->GetTexture( projTexName );
		if ( gameObj.GetCategory() == GameFramework::LIGHT_SOURCE_CATEGORY )
			projTextureId = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		const GraphicsFramework::BaseGeometryBuilder* baseGeometryBuilderPtr = 0;
		GLuint VAO = 0;
		GLuint textureId = 0;
		GLuint envTextureId = 0;			

		//get the VAO of the current game object
		VAO = gameObj.GetGraphicsObj().GetNameOfVAO();
		//get the pointer to the base geometry builder based on the object type to be rendered
		baseGeometryBuilderPtr = this->m_gameObjMgrPtr->RetrieveBaseGeometryBuilder( gameObj.GetType() );	
		//get the texture name of the current game object
		textureId = gameObj.GetGraphicsObj().GetTextureId( 0 );
		//get the environment texture id
		envTextureId = gameObj.GetGraphicsObj().GetEnvTextureId();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if ( renderEffect == GraphicsFramework::NORMAL )
		{
			this->InvokeVertexShader( effectsPtr, "vtxShader", 
				"mvpMatrix", mvpMatrix.GetMatrixArr(), 
				"textureMatrix", texGenMtx.GetMatrixArr() ); 

			this->InvokeFragmentShader( effectsPtr, "fragShader",
				"texId", textureId, "projTexId", projTextureId );
		}
		else
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			float spotLightInnerCone = 0;
			float spotLightOuterCone = 0;

			Light::Light & light = this->m_directionalLight;
			if ( lightEffect == Light::DIRECTIONAL )
			{
				light = this->m_directionalLight;
			}
			else if ( lightEffect == Light::POINT )
			{
				light = this->m_omniLight;
			}
			else if ( lightEffect == Light::SPOT )
			{
				light = this->m_spotLight;
				spotLightInnerCone = this->m_spotLight.GetInnerConeAngleDegrees();
				spotLightOuterCone = this->m_spotLight.GetOuterConeAngleDegrees();
			}		

			int lightAttenuationFlag = 0;
			if ( light.GetAttenuationFlag() == true )
			{
				lightAttenuationFlag = 1;
			}

			Math::Vector4 globalAmbient = light.GetGlobalAmbient();
			Math::Vector4 lightColor = light.GetLightColor();
			Math::Vector4 lightDirection = light.GetLookAtViewDirectionVector();
			Math::Vector4 lightPosition = light.GetLookAtPosition();	
			Math::Vector4 eyePosition = this->m_graphicsInterfacePtr->m_camera.GetCameraPosition();

			//place the light in view space
			lightDirection = viewMatrix * lightDirection;
			lightPosition = viewMatrix * lightPosition;

			Math::Vector4 Ke = gameObj.GetGraphicsObj().GetMaterial().GetEmissive();
			Math::Vector4 Ka = gameObj.GetGraphicsObj().GetMaterial().GetAmbient();
			Math::Vector4 Kd = gameObj.GetGraphicsObj().GetMaterial().GetDiffuse();
			Math::Vector4 Ks = gameObj.GetGraphicsObj().GetMaterial().GetSpecular();
		
			float shininess = gameObj.GetGraphicsObj().GetMaterial().GetShininess();

			float constantCoeff = light.GetConstantCoeff();
			float linearCoeff = light.GetLinearCoeff();
			float quadraticCoeff = light.GetQuadraticCoeff();

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if ( renderEffect == GraphicsFramework::LIGHT )
			{
				this->InvokePerVtxLightVertexShader( effectsPtr, "vtxShader", 
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr(), 
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

				this->InvokePerVtxLightFragmentShader( effectsPtr, "fragShader",
					"textureFlag", "texId", textureId, "projTexId", projTextureId );

			}
			else if ( renderEffect == GraphicsFramework::LIGHT_FRAG )
			{
				this->InvokeLightVertexShader( effectsPtr, "vtxShader", 
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr() );

				this->InvokeLightFragmentShader( effectsPtr, "fragShader", "textureFlag", "texId", textureId, "projTexId", projTextureId, 
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

			}
			else if ( renderEffect == GraphicsFramework::REFLECTIVE || renderEffect == GraphicsFramework::REFLECTIVE_FRAG )
			{
				float reflectivity = gameObj.GetGraphicsObj().GetMaterial().GetReflectivity();

				this->InvokeReflectiveVertexShader( effectsPtr, "vtxShader", 
					"modelWorldMatrix", modelMatrix.GetMatrixArr(), 
					"modelWorldITMatrix", modelMatrix.GetMatrixArr(),
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr(), 
					"eyePosition", eyePosition );

				this->InvokeReflectiveFragmentShader( effectsPtr, "fragShader", 
					"textureFlag", "texId", textureId, 
					"projTexId", projTextureId,
					"cubeMapTexId", envTextureId,
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone,  
					"reflectivity", reflectivity, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

			}
			else if ( renderEffect == GraphicsFramework::REFRACTIVE || renderEffect == GraphicsFramework::REFRACTIVE_FRAG )
			{
				float transmittance = gameObj.GetGraphicsObj().GetMaterial().GetTransmittance();
				float etaRatio = gameObj.GetGraphicsObj().GetMaterial().GetEtaRatio();

				this->InvokeRefractiveVertexShader( effectsPtr, "vtxShader", 
					"modelWorldMatrix", modelMatrix.GetMatrixArr(), 
					"modelWorldITMatrix", modelMatrix.GetMatrixArr(),
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr(), 
					"eyePosition", eyePosition, 
					"etaRatio", etaRatio );

				this->InvokeRefractiveFragmentShader( effectsPtr, "fragShader", 
					"textureFlag", "texId", textureId, 
					"projTexId", projTextureId,
					"cubeMapTexId", envTextureId,
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone, 
					"transmittance", transmittance, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

			}
			else if ( renderEffect == GraphicsFramework::REFRACTIVE_CD || renderEffect == GraphicsFramework::REFRACTIVE_CD_FRAG )
			{
				float transmittance = gameObj.GetGraphicsObj().GetMaterial().GetTransmittance();
				Math::Vector4 chromaticDispersionEtaRatio( 
					gameObj.GetGraphicsObj().GetMaterial().GetChromaticDispersionEtaRed(),
					gameObj.GetGraphicsObj().GetMaterial().GetChromaticDispersionEtaGreen(),
					gameObj.GetGraphicsObj().GetMaterial().GetChromaticDispersionEtaBlue(),
					0.0F );

				this->InvokeRefractiveChromDispVertexShader( effectsPtr, "vtxShader", 
					"modelWorldMatrix", modelMatrix.GetMatrixArr(), 
					"modelWorldITMatrix", modelMatrix.GetMatrixArr(),
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr(), 
					"eyePosition", eyePosition, 
					"etaRatio", chromaticDispersionEtaRatio );

				this->InvokeRefractiveFragmentShader( effectsPtr, "fragShader", 
					"textureFlag", "texId", textureId, 
					"projTexId", projTextureId,
					"cubeMapTexId", envTextureId,
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone, 
					"transmittance", transmittance, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

			}
			else if ( renderEffect == GraphicsFramework::FRESNEL || renderEffect == GraphicsFramework::FRESNEL_FRAG )
			{
				Math::Vector4 chromaticDispersionEtaRatio( 
					gameObj.GetGraphicsObj().GetMaterial().GetChromaticDispersionEtaRed(),
					gameObj.GetGraphicsObj().GetMaterial().GetChromaticDispersionEtaGreen(),
					gameObj.GetGraphicsObj().GetMaterial().GetChromaticDispersionEtaBlue(),
					0.0F );

				float fresnelBias = gameObj.GetGraphicsObj().GetMaterial().GetFresnelBias();
				float fresnelScale = gameObj.GetGraphicsObj().GetMaterial().GetFresnelScale();
				float fresnelPower = gameObj.GetGraphicsObj().GetMaterial().GetFresnelPower();

				this->InvokeFresnelVertexShader( effectsPtr, "vtxShader", 
					"modelWorldMatrix", modelMatrix.GetMatrixArr(), 
					"modelWorldITMatrix", modelMatrix.GetMatrixArr(),
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr(), 
					"eyePosition", eyePosition, 
					"etaRatio", chromaticDispersionEtaRatio, 
					"fresnelBias", fresnelBias, "fresnelScale", fresnelScale, "fresnelPower", fresnelPower );

				this->InvokeFresnelFragmentShader( effectsPtr, "fragShader", 
					"textureFlag", "texId", textureId, 
					"projTexId", projTextureId, 
					"cubeMapTexId", envTextureId,
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

			}
			else if ( renderEffect == GraphicsFramework::DUAL_PARABOLOID_REFLECTIVE )
			{
				float reflectivity = gameObj.GetGraphicsObj().GetMaterial().GetReflectivity();
				unsigned frontFaceTextureId = gameObj.GetGraphicsObj().GetFrontFaceEnvTextureId();
				unsigned backFaceTextureId = gameObj.GetGraphicsObj().GetBackFaceEnvTextureId();

				this->InvokeReflectiveVertexShader( effectsPtr, "vtxShader", 
					"modelWorldMatrix", modelMatrix.GetMatrixArr(), 
					"modelWorldITMatrix", modelMatrix.GetMatrixArr(),
					"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
					"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
					"mvpMatrix", mvpMatrix.GetMatrixArr(), 
					"textureMatrix", texGenMtx.GetMatrixArr(), 
					"eyePosition", eyePosition );

				this->InvokeDualParaboloidReflectiveFragmentShader( effectsPtr, "fragShader", 
					"textureFlag", "texId", textureId, 
					"projTexId", projTextureId,
					"frontMapTexId", frontFaceTextureId,
					"backMapTexId", backFaceTextureId,
					"globalAmbient", globalAmbient, "lightColor", lightColor,
					"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
					"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
					"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
					"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone,  
					"reflectivity", reflectivity, 
					"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );

			}
			
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//render the game object
		this->m_graphicsInterfacePtr->Draw( VAO, baseGeometryBuilderPtr );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws/renders the dual paraboloid object

	\param effectsPtr
	the pointer to the effect
	\param renderEffect
	the render effect
	\param lightEffect
	the lighting effect
	\param projTexName
	the projection texture name
	\param gameObj
	the game object
	\param projMatrix
	the projection matrix
	\param viewMatrix
	the view matrix
	\param faceValue
	determines which face of the dual paraboloid to render: 0 = front, 1 = back

	\return
	*/
	/******************************************************************************/
	void RenderManager::RenderToDualParaboloid( const Effects * effectsPtr, const RENDER_EFFECT renderEffect, const Light::LIGHT_EFFECT lightEffect,
		const char * projTexName,
		GameFramework::GameObject & gameObj, 
		const Math::Mtx44 & projMatrix, const Math::Mtx44 & viewMatrix, 
		const int faceValue )
	{
		Math::Mtx44 mvpMatrix;
		Math::Mtx44 modelViewMatrix;
		Math::Mtx44 modelMatrix;
	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//set up the matrix transformations

		//store the model matrix
		modelMatrix = this->GetObjectTransformation( gameObj );
		//set the model view matrix
		modelViewMatrix = viewMatrix * modelMatrix;

		//set the model-view-projection matrix
		mvpMatrix = projMatrix * modelViewMatrix;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//create the texture generation matrix
		Math::Mtx44 texGenMtx = this->CreateTexGenMtx( 
			modelMatrix, 
			this->m_projector.GenerateViewTransformMtx(), 
			projMatrix );

		//GLuint projTextureId = this->m_graphicsInterfacePtr->GetTexture( "EthanCochardLongboard" );
		GLuint projTextureId = this->m_graphicsInterfacePtr->GetTexture( projTexName );
		if ( gameObj.GetCategory() == GameFramework::LIGHT_SOURCE_CATEGORY )
			projTextureId = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		const GraphicsFramework::BaseGeometryBuilder* baseGeometryBuilderPtr = 0;
		GLuint VAO = 0;
		GLuint textureId = 0;
		GLuint envTextureId = 0;			

		//get the VAO of the current game object
		VAO = gameObj.GetGraphicsObj().GetNameOfVAO();
		//get the pointer to the base geometry builder based on the object type to be rendered
		baseGeometryBuilderPtr = this->m_gameObjMgrPtr->RetrieveBaseGeometryBuilder( gameObj.GetType() );	
		//get the texture name of the current game object
		textureId = gameObj.GetGraphicsObj().GetTextureId( 0 );
		//get the environment texture id
		envTextureId = gameObj.GetGraphicsObj().GetEnvTextureId();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
		float spotLightInnerCone = 0;
		float spotLightOuterCone = 0;

		Light::Light & light = this->m_directionalLight;
		if ( lightEffect == Light::DIRECTIONAL )
		{
			light = this->m_directionalLight;
		}
		else if ( lightEffect == Light::POINT )
		{
			light = this->m_omniLight;
		}
		else if ( lightEffect == Light::SPOT )
		{
			light = this->m_spotLight;
			spotLightInnerCone = this->m_spotLight.GetInnerConeAngleDegrees();
			spotLightOuterCone = this->m_spotLight.GetOuterConeAngleDegrees();
		}		

		int lightAttenuationFlag = 0;
		if ( light.GetAttenuationFlag() == true )
		{
			lightAttenuationFlag = 1;
		}

		Math::Vector4 globalAmbient = light.GetGlobalAmbient();
		Math::Vector4 lightColor = light.GetLightColor();
		Math::Vector4 lightDirection = light.GetLookAtViewDirectionVector();
		Math::Vector4 lightPosition = light.GetLookAtPosition();	
		Math::Vector4 eyePosition = this->m_graphicsInterfacePtr->m_camera.GetCameraPosition();

		//place the light in view space
		lightDirection = viewMatrix * lightDirection;
		lightPosition = viewMatrix * lightPosition;

		Math::Vector4 Ke = gameObj.GetGraphicsObj().GetMaterial().GetEmissive();
		Math::Vector4 Ka = gameObj.GetGraphicsObj().GetMaterial().GetAmbient();
		Math::Vector4 Kd = gameObj.GetGraphicsObj().GetMaterial().GetDiffuse();
		Math::Vector4 Ks = gameObj.GetGraphicsObj().GetMaterial().GetSpecular();
		
		float shininess = gameObj.GetGraphicsObj().GetMaterial().GetShininess();

		float constantCoeff = light.GetConstantCoeff();
		float linearCoeff = light.GetLinearCoeff();
		float quadraticCoeff = light.GetQuadraticCoeff();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if ( renderEffect == GraphicsFramework::DUAL_PARABOLOID_GENERATION )
		{
			this->InvokeDualParaboloidGenerationVertexShader( effectsPtr, "vtxShader", 
				"modelViewMatrix", modelViewMatrix.GetMatrixArr(),
				"modelViewITMatrix", modelViewMatrix.GetMatrixArr(),
				"mvpMatrix", mvpMatrix.GetMatrixArr(), 
				"textureMatrix", texGenMtx.GetMatrixArr(), 
				"nearPlane", 0.1F, 
				"farPlane", 100.0F, 
				"faceValue", faceValue );

			this->InvokeLightFragmentShader( effectsPtr, "fragShader", "textureFlag", "texId", textureId, "projTexId", projTextureId, 
				"globalAmbient", globalAmbient, "lightColor", lightColor,
				"lightDirection", lightDirection, "lightPosition", lightPosition, "eyePosition", eyePosition, 
				"Ke", Ke, "Ka", Ka, "Kd", Kd, "Ks", Ks, "shininess", shininess, 
				"constantCoeff", constantCoeff, "linearCoeff", linearCoeff, "quadraticCoeff", quadraticCoeff, 
				"spotLightInnerCone", spotLightInnerCone, "spotLightOuterCone", spotLightOuterCone, 
				"lightType", lightEffect, "lightAttenuationFlag", lightAttenuationFlag );
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//render the game object
		this->m_graphicsInterfacePtr->Draw( VAO, baseGeometryBuilderPtr );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	/******************************************************************************/
	/*!
	Invoke the dual paraboloid generation vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\param vtxShaderParamName5
	the name of the vertex shader parameter
	\param nearPlane
	the near plane value

	\param vtxShaderParamName6
	the name of the vertex shader parameter
	\param farPlane
	the far plane value

	\param vtxShaderParamName7
	the name of the vertex shader parameter
	\param faceValue
	the face value: 0 for front, 1 for back

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeDualParaboloidGenerationVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelViewMatrixVal,
		const char * vtxShaderParamName2, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName3, const float * mvpMatrixVal, 
		const char * vtxShaderParamName4, const float * texGenMatrixVal,
		const char * vtxShaderParamName5, const float nearPlane,
		const char * vtxShaderParamName6, const float farPlane,
		const char * vtxShaderParamName7, const int faceValue ) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set the model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );

		//set the near plane
		vtxShader.SetFloatParam( nearPlane, vtxShader.GetParam( vtxShaderParamName5 ) );
		//set the far plane
		vtxShader.SetFloatParam( farPlane, vtxShader.GetParam( vtxShaderParamName6 ) );

		//set the face value
		vtxShader.SetIntParam( faceValue, vtxShader.GetParam( vtxShaderParamName7 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeVertexShader( const Effects * effectsPtr, const char * vtxShaderName,
		const char * vtxShaderParamName1, const float * mvpMatrixVal,
		const char * vtxShaderParamName2, const float * texGenMatrixVal	) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the lighting vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeLightVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelViewMatrixVal,
		const char * vtxShaderParamName2, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName3, const float * mvpMatrixVal,
		const char * vtxShaderParamName4, const float * texGenMatrixVal	) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set the model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the per fragment lighting vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\param fragShaderParamName5
	the name of the fragment shader parameter
	\param globalAmbient
	the global ambient value
	\param fragShaderParamName6
	the name of the fragment shader parameter
	\param lightColor
	the color of the light
	\param fragShaderParamName7
	the name of the fragment shader parameter
	\param lightDirection
	the direction of the light
	\param fragShaderParamName8
	the name of the fragment shader parameter
	\param lightPosition
	the position of the light
	\param fragShaderParamName9
	the name of the fragment shader parameter
	\param eyePosition
	the position of the eye

	\param fragShaderParamName10
	the name of the fragment shader parameter
	\param Ke
	the emissive value
	\param fragShaderParamName11
	the name of the fragment shader parameter
	\param Ka
	the ambient value
	\param fragShaderParamName12
	the name of the fragment shader parameter
	\param Kd
	the diffuse value
	\param fragShaderParamName13
	the name of the fragment shader parameter
	\param Ks
	the specular value
	\param fragShaderParamName14
	the name of the fragment shader parameter
	\param shininess
	the shininess value

	\param fragShaderParamName15
	the name of the fragment shader parameter
	\param constantCoeff
	the constant attenuation coefficient
	\param fragShaderParamName16
	the name of the fragment shader parameter
	\param linearCoeff
	the linear attenuation coefficient
	\param fragShaderParamName17
	the name of the fragment shader parameter
	\param quadraticCoeff
	the quadratic attenuation coefficient

	\param fragShaderParamName18
	the name of the fragment shader parameter
	\param spotLightInnerCone
	the angle of the spot light inner cone
	\param fragShaderParamName19
	the name of the fragment shader parameter
	\param spotLightOuterCone
	the angle of the spot light outer cone

	\param fragShaderParamName20
	the name of the fragment shader parameter
	\param lightType
	the type of light

	\param fragShaderParamName21
	the name of the fragment shader parameter
	\param lightAttenuationFlag
	the flag to indicate whether attenuation is turned on

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokePerVtxLightVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelViewMatrixVal,
		const char * vtxShaderParamName2, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName3, const float * mvpMatrixVal, 
		const char * vtxShaderParamName4, const float * texGenMatrixVal,
		const char * vtxShaderParamName5, const Math::Vector4 globalAmbient, 
		const char * vtxShaderParamName6, const Math::Vector4 lightColor, 
		const char * vtxShaderParamName7, const Math::Vector4 lightDirection, 
		const char * vtxShaderParamName8, const Math::Vector4 lightPosition, 
		const char * vtxShaderParamName9, const Math::Vector4 eyePosition, 
		const char * vtxShaderParamName10, const Math::Vector4 Ke, 
		const char * vtxShaderParamName11, const Math::Vector4 Ka, 
		const char * vtxShaderParamName12, const Math::Vector4 Kd, 
		const char * vtxShaderParamName13, const Math::Vector4 Ks, 
		const char * vtxShaderParamName14, const float shininess,
		const char * vtxShaderParamName15, const float constantCoeff, 
		const char * vtxShaderParamName16, const float linearCoeff, 
		const char * vtxShaderParamName17, const float quadraticCoeff, 
		const char * vtxShaderParamName18, const float spotLightInnerCone, 
		const char * vtxShaderParamName19, const float spotLightOuterCone, 
		const char * vtxShaderParamName20, const int lightType, 
		const char * vtxShaderParamName21, const int lightAttenuationFlag ) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set the model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );

		// set the parameters needed for the lighting equation
		vtxShader.SetFloat3Param( globalAmbient.GetFloatX(), globalAmbient.GetFloatY(), globalAmbient.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName5 ) );
		vtxShader.SetFloat3Param( lightColor.GetFloatX(), lightColor.GetFloatY(), lightColor.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName6 ) );
		vtxShader.SetFloat3Param( lightDirection.GetFloatX(), lightDirection.GetFloatY(), lightDirection.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName7 ) );
		vtxShader.SetFloat3Param( lightPosition.GetFloatX(), lightPosition.GetFloatY(), lightPosition.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName8 ) );
		vtxShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName9 ) );

		//set the material values
		vtxShader.SetFloat3Param( Ke.GetFloatX(), Ke.GetFloatY(), Ke.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName10 ) );
		vtxShader.SetFloat3Param( Ka.GetFloatX(), Ka.GetFloatY(), Ka.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName11 ) );
		vtxShader.SetFloat3Param( Kd.GetFloatX(), Kd.GetFloatY(), Kd.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName12 ) );
		vtxShader.SetFloat3Param( Ks.GetFloatX(), Ks.GetFloatY(), Ks.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName13 ) );
		vtxShader.SetFloatParam( shininess, vtxShader.GetParam( vtxShaderParamName14 ) );

		//set the attenuation values
		vtxShader.SetFloatParam( constantCoeff, vtxShader.GetParam( vtxShaderParamName15 ) );
		vtxShader.SetFloatParam( linearCoeff, vtxShader.GetParam( vtxShaderParamName16 ) );
		vtxShader.SetFloatParam( quadraticCoeff, vtxShader.GetParam( vtxShaderParamName17 ) );

		//set the spot light cone
		vtxShader.SetFloatParam( spotLightInnerCone, vtxShader.GetParam( vtxShaderParamName18 ) );
		vtxShader.SetFloatParam( spotLightOuterCone, vtxShader.GetParam( vtxShaderParamName19 ) );

		//set the light type
		vtxShader.SetIntParam( lightType, vtxShader.GetParam( vtxShaderParamName20 ) );

		//set the light attenuation flag
		vtxShader.SetIntParam( lightAttenuationFlag, vtxShader.GetParam( vtxShaderParamName21 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the reflective vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelMatrixVal
	the values of the model to world matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelITMatrixVal
	the values of the model to world inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix	

	\param vtxShaderParamName5
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName6
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\param vtxShaderParamName7
	the name of the vertex shader parameter
	\param eyePosition
	the eye position in the world

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeReflectiveVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelMatrixVal,
		const char * vtxShaderParamName2, const float * modelITMatrixVal,
		const char * vtxShaderParamName3, const float * modelViewMatrixVal,
		const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName5, const float * mvpMatrixVal,
		const char * vtxShaderParamName6, const float * texGenMatrixVal, 
		const char * vtxShaderParamName7, const Math::Vector4 eyePosition ) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set model to world matrix
		vtxShader.SetMatrixParam( modelMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set model to world inverse transpose matrix
		vtxShader.SetMatrixParam( modelITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName5 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName6 ) );

		//set the eye position
		vtxShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName7 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the refractive vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelMatrixVal
	the values of the model to world matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelITMatrixVal
	the values of the model to world inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix	

	\param vtxShaderParamName5
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName6
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\param vtxShaderParamName7
	the name of the vertex shader parameter
	\param eyePosition
	the eye position in the world

	\param vtxShaderParamName8
	the name of the vertex shader parameter
	\param etaRatio
	the index of refraction

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeRefractiveVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelMatrixVal,
		const char * vtxShaderParamName2, const float * modelITMatrixVal,
		const char * vtxShaderParamName3, const float * modelViewMatrixVal,
		const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName5, const float * mvpMatrixVal,
		const char * vtxShaderParamName6, const float * texGenMatrixVal, 
		const char * vtxShaderParamName7, const Math::Vector4 eyePosition, 
		const char * vtxShaderParamName8, const float etaRatio ) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set model to world matrix
		vtxShader.SetMatrixParam( modelMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set model to world inverse transpose matrix
		vtxShader.SetMatrixParam( modelITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName5 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName6 ) );

		//set the eye position
		vtxShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName7 ) );

		// set the index of refraction
		vtxShader.SetFloatParam( etaRatio, vtxShader.GetParam( vtxShaderParamName8 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the refraction with chromatic dispersion vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelMatrixVal
	the values of the model to world matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelITMatrixVal
	the values of the model to world inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix	

	\param vtxShaderParamName5
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName6
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\param vtxShaderParamName7
	the name of the vertex shader parameter
	\param eyePosition
	the eye position in the world

	\param vtxShaderParamName8
	the name of the vertex shader parameter
	\param etaRatio
	the index of refraction for each primary color in the light spectrum

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeRefractiveChromDispVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelMatrixVal,
		const char * vtxShaderParamName2, const float * modelITMatrixVal,
		const char * vtxShaderParamName3, const float * modelViewMatrixVal,
		const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName5, const float * mvpMatrixVal, 
		const char * vtxShaderParamName6, const float * texGenMatrixVal, 
		const char * vtxShaderParamName7, const Math::Vector4 eyePosition,
		const char * vtxShaderParamName8, const Math::Vector4 etaRatio ) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set model to world matrix
		vtxShader.SetMatrixParam( modelMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set model to world inverse transpose matrix
		vtxShader.SetMatrixParam( modelITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName5 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName6 ) );

		//set the eye position
		vtxShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName7 ) );

		// set the index of refraction
		vtxShader.SetFloat3Param( etaRatio.GetFloatX(), etaRatio.GetFloatY(), etaRatio.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName8 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the Fresnel vertex shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param vtxShaderName
	the name of the vertex shader

	\param vtxShaderParamName1
	the name of the vertex shader parameter
	\param modelMatrixVal
	the values of the model to world matrix

	\param vtxShaderParamName2
	the name of the vertex shader parameter
	\param modelITMatrixVal
	the values of the model to world inverse transpose matrix

	\param vtxShaderParamName3
	the name of the vertex shader parameter
	\param modelViewMatrixVal
	the values of the model view matrix

	\param vtxShaderParamName4
	the name of the vertex shader parameter
	\param modelViewITMatrixVal
	the values of the model view inverse transpose matrix	

	\param vtxShaderParamName5
	the name of the vertex shader parameter
	\param mvpMatrixVal
	the values of the model view projection matrix

	\param vtxShaderParamName6
	the name of the vertex shader parameter
	\param texGenMatrixVal
	the values of the texture generation matrix

	\param vtxShaderParamName7
	the name of the vertex shader parameter
	\param eyePosition
	the eye position in the world

	\param vtxShaderParamName8
	the name of the vertex shader parameter
	\param etaRatio
	the index of refraction for each primary color in the light spectrum

	\param vtxShaderParamName9
	the name of the vertex shader parameter
	\param fresnelBias
	the Fresnel bias

	\param vtxShaderParamName10
	the name of the vertex shader parameter
	\param fresnelScale
	the Fresnel linear dependency

	\param vtxShaderParamName11
	the name of the vertex shader parameter
	\param fresnelPower
	the Fresnel power ( sharpness )

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeFresnelVertexShader( const Effects * effectsPtr, const char * vtxShaderName, 
		const char * vtxShaderParamName1, const float * modelMatrixVal,
		const char * vtxShaderParamName2, const float * modelITMatrixVal,
		const char * vtxShaderParamName3, const float * modelViewMatrixVal,
		const char * vtxShaderParamName4, const float * modelViewITMatrixVal,
		const char * vtxShaderParamName5, const float * mvpMatrixVal, 
		const char * vtxShaderParamName6, const float * texGenMatrixVal, 
		const char * vtxShaderParamName7, const Math::Vector4 eyePosition,
		const char * vtxShaderParamName8, const Math::Vector4 etaRatio, 
		const char * vtxShaderParamName9, const float fresnelBias, 
		const char * vtxShaderParamName10, const float fresnelScale, 
		const char * vtxShaderParamName11, const float fresnelPower ) const
	{
		Shader::Shader vtxShader = effectsPtr->GetShaderMap().find( vtxShaderName )->second;

		// set model to world matrix
		vtxShader.SetMatrixParam( modelMatrixVal, vtxShader.GetParam( vtxShaderParamName1 ) );
		// set model to world inverse transpose matrix
		vtxShader.SetMatrixParam( modelITMatrixVal, vtxShader.GetParam( vtxShaderParamName2 ) );
		// set model view matrix
		vtxShader.SetMatrixParam( modelViewMatrixVal, vtxShader.GetParam( vtxShaderParamName3 ) );
		// set the model view inverse transpose matrix
		vtxShader.SetMatrixParam( modelViewITMatrixVal, vtxShader.GetParam( vtxShaderParamName4 ) );
		// set the model view projection matrix
		vtxShader.SetMatrixParam( mvpMatrixVal, vtxShader.GetParam( vtxShaderParamName5 ) );
		// set the texture generation matrix
		vtxShader.SetMatrixParam( texGenMatrixVal, vtxShader.GetParam( vtxShaderParamName6 ) );

		//set the eye position
		vtxShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName7 ) );

		// set the index of refraction
		vtxShader.SetFloat3Param( etaRatio.GetFloatX(), etaRatio.GetFloatY(), etaRatio.GetFloatZ(), vtxShader.GetParam( vtxShaderParamName8 ) );

		// set the Fresnel bias
		vtxShader.SetFloatParam( fresnelBias, vtxShader.GetParam( vtxShaderParamName9 ) );
		// set the Fresnel scale
		vtxShader.SetFloatParam( fresnelScale, vtxShader.GetParam( vtxShaderParamName10 ) );
		// set the Fresnel power
		vtxShader.SetFloatParam( fresnelPower, vtxShader.GetParam( vtxShaderParamName11 ) );

		// update the uniform parameters in the shader
		vtxShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader

	\param fragShaderParamName1
	the name of the fragment shader parameter
	\param textureId
	the texture id

	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const unsigned textureId,
		const char * fragShaderParamName2, const unsigned projTextureId ) const
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;

		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName2 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the per vertex lighting fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader

	\param fragShaderParamName1
	the name of the fragment shader parameter	
	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param textureId
	the texture id

	\param fragShaderParamName3
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokePerVtxLightFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
		const char * fragShaderParamName3, const unsigned projTextureId )
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;

		fragShader.SetIntParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );

		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName2 ) );		
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName3 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the lighting fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader
	\param fragShaderParamName1
	the name of the fragment shader parameter
	\param textureId
	the texture id
	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param textureFlag
	the flag to indicate that there is a texture	

	\param fragShaderParamName3
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id	

	\param fragShaderParamName4
	the name of the fragment shader parameter
	\param globalAmbient
	the global ambient value
	\param fragShaderParamName5
	the name of the fragment shader parameter
	\param lightColor
	the color of the light
	\param fragShaderParamName6
	the name of the fragment shader parameter
	\param lightDirection
	the direction of the light
	\param fragShaderParamName7
	the name of the fragment shader parameter
	\param lightPosition
	the position of the light
	\param fragShaderParamName8
	the name of the fragment shader parameter
	\param eyePosition
	the position of the eye

	\param fragShaderParamName9
	the name of the fragment shader parameter
	\param Ke
	the emissive value
	\param fragShaderParamName10
	the name of the fragment shader parameter
	\param Ka
	the ambient value
	\param fragShaderParamName11
	the name of the fragment shader parameter
	\param Kd
	the diffuse value
	\param fragShaderParamName12
	the name of the fragment shader parameter
	\param Ks
	the specular value
	\param fragShaderParamName13
	the name of the fragment shader parameter
	\param shininess
	the shininess value

	\param fragShaderParamName14
	the name of the fragment shader parameter
	\param constantCoeff
	the constant attenuation coefficient
	\param fragShaderParamName15
	the name of the fragment shader parameter
	\param linearCoeff
	the linear attenuation coefficient
	\param fragShaderParamName16
	the name of the fragment shader parameter
	\param quadraticCoeff
	the quadratic attenuation coefficient

	\param fragShaderParamName17
	the name of the fragment shader parameter
	\param spotLightInnerCone
	the angle of the spot light inner cone
	\param fragShaderParamName18
	the name of the fragment shader parameter
	\param spotLightOuterCone
	the angle of the spot light outer cone

	\param fragShaderParamName19
	the name of the fragment shader parameter
	\param lightType
	the type of light

	\param fragShaderParamName20
	the name of the fragment shader parameter
	\param lightAttenuationFlag
	the flag to indicate whether attenuation is turned on

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeLightFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
		const char * fragShaderParamName3, const unsigned projTextureId,		
		const char * fragShaderParamName4, const Math::Vector4 globalAmbient, 
		const char * fragShaderParamName5, const Math::Vector4 lightColor, 
		const char * fragShaderParamName6, const Math::Vector4 lightDirection, 
		const char * fragShaderParamName7, const Math::Vector4 lightPosition, 
		const char * fragShaderParamName8, const Math::Vector4 eyePosition, 
		const char * fragShaderParamName9, const Math::Vector4 Ke, 
		const char * fragShaderParamName10, const Math::Vector4 Ka, 
		const char * fragShaderParamName11, const Math::Vector4 Kd, 
		const char * fragShaderParamName12, const Math::Vector4 Ks, 
		const char * fragShaderParamName13, const float shininess,
		const char * fragShaderParamName14, const float constantCoeff, 
		const char * fragShaderParamName15, const float linearCoeff, 
		const char * fragShaderParamName16, const float quadraticCoeff, 
		const char * fragShaderParamName17, const float spotLightInnerCone, 
		const char * fragShaderParamName18, const float spotLightOuterCone, 
		const char * fragShaderParamName19, const int lightType, 
		const char * fragShaderParamName20, const int lightAttenuationFlag ) const
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;

		fragShader.SetIntParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );

		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName2 ) );		
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName3 ) );		

		// set the parameters needed for the lighting equation
		fragShader.SetFloat3Param( globalAmbient.GetFloatX(), globalAmbient.GetFloatY(), globalAmbient.GetFloatZ(), fragShader.GetParam( fragShaderParamName4 ) );
		fragShader.SetFloat3Param( lightColor.GetFloatX(), lightColor.GetFloatY(), lightColor.GetFloatZ(), fragShader.GetParam( fragShaderParamName5 ) );
		fragShader.SetFloat3Param( lightDirection.GetFloatX(), lightDirection.GetFloatY(), lightDirection.GetFloatZ(), fragShader.GetParam( fragShaderParamName6 ) );
		fragShader.SetFloat3Param( lightPosition.GetFloatX(), lightPosition.GetFloatY(), lightPosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName7 ) );
		fragShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName8 ) );

		//set the material values
		fragShader.SetFloat3Param( Ke.GetFloatX(), Ke.GetFloatY(), Ke.GetFloatZ(), fragShader.GetParam( fragShaderParamName9 ) );
		fragShader.SetFloat3Param( Ka.GetFloatX(), Ka.GetFloatY(), Ka.GetFloatZ(), fragShader.GetParam( fragShaderParamName10 ) );
		fragShader.SetFloat3Param( Kd.GetFloatX(), Kd.GetFloatY(), Kd.GetFloatZ(), fragShader.GetParam( fragShaderParamName11 ) );
		fragShader.SetFloat3Param( Ks.GetFloatX(), Ks.GetFloatY(), Ks.GetFloatZ(), fragShader.GetParam( fragShaderParamName12 ) );
		fragShader.SetFloatParam( shininess, fragShader.GetParam( fragShaderParamName13 ) );

		//set the attenuation values
		fragShader.SetFloatParam( constantCoeff, fragShader.GetParam( fragShaderParamName14 ) );
		fragShader.SetFloatParam( linearCoeff, fragShader.GetParam( fragShaderParamName15 ) );
		fragShader.SetFloatParam( quadraticCoeff, fragShader.GetParam( fragShaderParamName16 ) );

		//set the spot light cone
		fragShader.SetFloatParam( spotLightInnerCone, fragShader.GetParam( fragShaderParamName17 ) );
		fragShader.SetFloatParam( spotLightOuterCone, fragShader.GetParam( fragShaderParamName18 ) );

		//set the light type
		fragShader.SetIntParam( lightType, fragShader.GetParam( fragShaderParamName19 ) );

		//set the light attenuation flag
		fragShader.SetIntParam( lightAttenuationFlag, fragShader.GetParam( fragShaderParamName20 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the reflective fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader
	
	\param fragShaderParamName1
	the name of the fragment shader parameter
	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param textureId
	the texture id
	\param fragShaderParamName3
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id	
	\param fragShaderParamName4
	the name of the fragment shader parameter
	\param cubeMapTextureId
	the cube map texture id

	\param fragShaderParamName5
	the name of the fragment shader parameter
	\param globalAmbient
	the global ambient value
	\param fragShaderParamName6
	the name of the fragment shader parameter
	\param lightColor
	the color of the light
	\param fragShaderParamName7
	the name of the fragment shader parameter
	\param lightDirection
	the direction of the light
	\param fragShaderParamName8
	the name of the fragment shader parameter
	\param lightPosition
	the position of the light
	\param fragShaderParamName9
	the name of the fragment shader parameter
	\param eyePosition
	the position of the eye

	\param fragShaderParamName10
	the name of the fragment shader parameter
	\param Ke
	the emissive value
	\param fragShaderParamName11
	the name of the fragment shader parameter
	\param Ka
	the ambient value
	\param fragShaderParamName12
	the name of the fragment shader parameter
	\param Kd
	the diffuse value
	\param fragShaderParamName13
	the name of the fragment shader parameter
	\param Ks
	the specular value
	\param fragShaderParamName14
	the name of the fragment shader parameter
	\param shininess
	the shininess value

	\param fragShaderParamName15
	the name of the fragment shader parameter
	\param constantCoeff
	the constant attenuation coefficient
	\param fragShaderParamName16
	the name of the fragment shader parameter
	\param linearCoeff
	the linear attenuation coefficient
	\param fragShaderParamName17
	the name of the fragment shader parameter
	\param quadraticCoeff
	the quadratic attenuation coefficient

	\param fragShaderParamName18
	the name of the fragment shader parameter
	\param spotLightInnerCone
	the angle of the spot light inner cone
	\param fragShaderParamName19
	the name of the fragment shader parameter
	\param spotLightOuterCone
	the angle of the spot light outer cone

	\param fragShaderParamName20
	the name of the fragment shader parameter
	\param reflectivity
	the reflectivity value

	\param fragShaderParamName21
	the name of the fragment shader parameter
	\param lightType
	the type of light
	
	\param fragShaderParamName22
	the name of the fragment shader parameter
	\param lightAttenuationFlag
	the flag to enable/disable attenuation

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeReflectiveFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
		const char * fragShaderParamName3, const unsigned projTextureId,
		const char * fragShaderParamName4, const unsigned cubeMapTextureId,
		const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
		const char * fragShaderParamName6, const Math::Vector4 lightColor, 
		const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
		const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
		const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
		const char * fragShaderParamName10, const Math::Vector4 Ke, 
		const char * fragShaderParamName11, const Math::Vector4 Ka, 
		const char * fragShaderParamName12, const Math::Vector4 Kd,
		const char * fragShaderParamName13, const Math::Vector4 Ks, 
		const char * fragShaderParamName14, const float shininess,
		const char * fragShaderParamName15, const float constantCoeff, 
		const char * fragShaderParamName16, const float linearCoeff, 
		const char * fragShaderParamName17, const float quadraticCoeff, 
		const char * fragShaderParamName18, const float spotLightInnerCone, 
		const char * fragShaderParamName19, const float spotLightOuterCone, 
		const char * fragShaderParamName20, const float reflectivity, 
		const char * fragShaderParamName21, const int lightType, 
		const char * fragShaderParamName22, const int lightAttenuationFlag ) const
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;

		fragShader.SetIntParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );
		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName2 ) );
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName3 ) );

		//set the environment textures
		fragShader.SetTexSamplerParam( cubeMapTextureId, fragShader.GetParam( fragShaderParamName4 ) );

		// set the parameters needed for the lighting equation
		fragShader.SetFloat3Param( globalAmbient.GetFloatX(), globalAmbient.GetFloatY(), globalAmbient.GetFloatZ(), fragShader.GetParam( fragShaderParamName5 ) );
		fragShader.SetFloat3Param( lightColor.GetFloatX(), lightColor.GetFloatY(), lightColor.GetFloatZ(), fragShader.GetParam( fragShaderParamName6 ) );
		fragShader.SetFloat3Param( lightDirection.GetFloatX(), lightDirection.GetFloatY(), lightDirection.GetFloatZ(), fragShader.GetParam( fragShaderParamName7 ) );
		fragShader.SetFloat3Param( lightPosition.GetFloatX(), lightPosition.GetFloatY(), lightPosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName8 ) );
		fragShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName9 ) );

		//set the material values
		fragShader.SetFloat3Param( Ke.GetFloatX(), Ke.GetFloatY(), Ke.GetFloatZ(), fragShader.GetParam( fragShaderParamName10 ) );
		fragShader.SetFloat3Param( Ka.GetFloatX(), Ka.GetFloatY(), Ka.GetFloatZ(), fragShader.GetParam( fragShaderParamName11 ) );
		fragShader.SetFloat3Param( Kd.GetFloatX(), Kd.GetFloatY(), Kd.GetFloatZ(), fragShader.GetParam( fragShaderParamName12 ) );
		fragShader.SetFloat3Param( Ks.GetFloatX(), Ks.GetFloatY(), Ks.GetFloatZ(), fragShader.GetParam( fragShaderParamName13 ) );
		fragShader.SetFloatParam( shininess, fragShader.GetParam( fragShaderParamName14 ) );

		//set the attenuation values
		fragShader.SetFloatParam( constantCoeff, fragShader.GetParam( fragShaderParamName15 ) );
		fragShader.SetFloatParam( linearCoeff, fragShader.GetParam( fragShaderParamName16 ) );
		fragShader.SetFloatParam( quadraticCoeff, fragShader.GetParam( fragShaderParamName17 ) );

		//set the spot light cone
		fragShader.SetFloatParam( spotLightInnerCone, fragShader.GetParam( fragShaderParamName18 ) );
		fragShader.SetFloatParam( spotLightOuterCone, fragShader.GetParam( fragShaderParamName19 ) );

		//set the reflective properties
		fragShader.SetFloatParam( reflectivity, fragShader.GetParam( fragShaderParamName20 ) );

		//set the light type
		fragShader.SetIntParam( lightType, fragShader.GetParam( fragShaderParamName21 ) );

		//set the light attenuation flag
		fragShader.SetIntParam( lightAttenuationFlag, fragShader.GetParam( fragShaderParamName22 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the refractive effect fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader

	\param fragShaderParamName1
	the name of the fragment shader parameter
	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param textureId
	the texture id
	\param fragShaderParamName3
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id	
	\param fragShaderParamName4
	the name of the fragment shader parameter
	\param cubeMapTextureId
	the cube map texture id

	\param fragShaderParamName5
	the name of the fragment shader parameter
	\param globalAmbient
	the global ambient value
	\param fragShaderParamName6
	the name of the fragment shader parameter
	\param lightColor
	the color of the light
	\param fragShaderParamName7
	the name of the fragment shader parameter
	\param lightDirection
	the direction of the light
	\param fragShaderParamName8
	the name of the fragment shader parameter
	\param lightPosition
	the position of the light
	\param fragShaderParamName9
	the name of the fragment shader parameter
	\param eyePosition
	the position of the eye

	\param fragShaderParamName10
	the name of the fragment shader parameter
	\param Ke
	the emissive value
	\param fragShaderParamName11
	the name of the fragment shader parameter
	\param Ka
	the ambient value
	\param fragShaderParamName12
	the name of the fragment shader parameter
	\param Kd
	the diffuse value
	\param fragShaderParamName13
	the name of the fragment shader parameter
	\param Ks
	the specular value
	\param fragShaderParamName14
	the name of the fragment shader parameter
	\param shininess
	the shininess value

	\param fragShaderParamName15
	the name of the fragment shader parameter
	\param constantCoeff
	the constant attenuation coefficient
	\param fragShaderParamName16
	the name of the fragment shader parameter
	\param linearCoeff
	the linear attenuation coefficient
	\param fragShaderParamName17
	the name of the fragment shader parameter
	\param quadraticCoeff
	the quadratic attenuation coefficient

	\param fragShaderParamName18
	the name of the fragment shader parameter
	\param spotLightInnerCone
	the angle of the spot light inner cone
	\param fragShaderParamName19
	the name of the fragment shader parameter
	\param spotLightOuterCone
	the angle of the spot light outer cone

	\param fragShaderParamName20
	the name of the fragment shader parameter
	\param transmittance
	the transmittance value

	\param fragShaderParamName21
	the name of the fragment shader parameter
	\param lightType
	the type of light

	\param fragShaderParamName22
	the name of the fragment shader parameter
	\param lightAttenuationFlag
	the flag to enable/disable attenuation

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeRefractiveFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
		const char * fragShaderParamName3, const unsigned projTextureId,
		const char * fragShaderParamName4, const unsigned cubeMapTextureId,
		const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
		const char * fragShaderParamName6, const Math::Vector4 lightColor, 
		const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
		const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
		const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
		const char * fragShaderParamName10, const Math::Vector4 Ke, 
		const char * fragShaderParamName11, const Math::Vector4 Ka, 
		const char * fragShaderParamName12, const Math::Vector4 Kd,
		const char * fragShaderParamName13, const Math::Vector4 Ks, 
		const char * fragShaderParamName14, const float shininess,
		const char * fragShaderParamName15, const float constantCoeff, 
		const char * fragShaderParamName16, const float linearCoeff, 
		const char * fragShaderParamName17, const float quadraticCoeff, 
		const char * fragShaderParamName18, const float spotLightInnerCone, 
		const char * fragShaderParamName19, const float spotLightOuterCone, 
		const char * fragShaderParamName20, const float transmittance,
		const char * fragShaderParamName21, const int lightType, 
		const char * fragShaderParamName22, const int lightAttenuationFlag ) const
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;

		fragShader.SetIntParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );
		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName2 ) );
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName3 ) );

		//set the environment textures
		fragShader.SetTexSamplerParam( cubeMapTextureId, fragShader.GetParam( fragShaderParamName4 ) );

		// set the parameters needed for the lighting equation
		fragShader.SetFloat3Param( globalAmbient.GetFloatX(), globalAmbient.GetFloatY(), globalAmbient.GetFloatZ(), fragShader.GetParam( fragShaderParamName5 ) );
		fragShader.SetFloat3Param( lightColor.GetFloatX(), lightColor.GetFloatY(), lightColor.GetFloatZ(), fragShader.GetParam( fragShaderParamName6 ) );
		fragShader.SetFloat3Param( lightDirection.GetFloatX(), lightDirection.GetFloatY(), lightDirection.GetFloatZ(), fragShader.GetParam( fragShaderParamName7 ) );
		fragShader.SetFloat3Param( lightPosition.GetFloatX(), lightPosition.GetFloatY(), lightPosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName8 ) );
		fragShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName9 ) );

		//set the material values
		fragShader.SetFloat3Param( Ke.GetFloatX(), Ke.GetFloatY(), Ke.GetFloatZ(), fragShader.GetParam( fragShaderParamName10 ) );
		fragShader.SetFloat3Param( Ka.GetFloatX(), Ka.GetFloatY(), Ka.GetFloatZ(), fragShader.GetParam( fragShaderParamName11 ) );
		fragShader.SetFloat3Param( Kd.GetFloatX(), Kd.GetFloatY(), Kd.GetFloatZ(), fragShader.GetParam( fragShaderParamName12 ) );
		fragShader.SetFloat3Param( Ks.GetFloatX(), Ks.GetFloatY(), Ks.GetFloatZ(), fragShader.GetParam( fragShaderParamName13 ) );
		fragShader.SetFloatParam( shininess, fragShader.GetParam( fragShaderParamName14 ) );

		//set the attenuation values
		fragShader.SetFloatParam( constantCoeff, fragShader.GetParam( fragShaderParamName15 ) );
		fragShader.SetFloatParam( linearCoeff, fragShader.GetParam( fragShaderParamName16 ) );
		fragShader.SetFloatParam( quadraticCoeff, fragShader.GetParam( fragShaderParamName17 ) );

		//set the spot light cone
		fragShader.SetFloatParam( spotLightInnerCone, fragShader.GetParam( fragShaderParamName18 ) );
		fragShader.SetFloatParam( spotLightOuterCone, fragShader.GetParam( fragShaderParamName19 ) );

		//set the refractive properties
		fragShader.SetFloatParam( transmittance, fragShader.GetParam( fragShaderParamName20 ) );

		//set the light type
		fragShader.SetIntParam( lightType, fragShader.GetParam( fragShaderParamName21 ) );

		//set the light attenuation flag
		fragShader.SetIntParam( lightAttenuationFlag, fragShader.GetParam( fragShaderParamName22 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the Fresnel effect fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader

	\param fragShaderParamName1
	the name of the fragment shader parameter
	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param textureId
	the texture id
	\param fragShaderParamName3
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id	
	\param fragShaderParamName4
	the name of the fragment shader parameter
	\param cubeMapTextureId
	the cube map texture id

	\param fragShaderParamName5
	the name of the fragment shader parameter
	\param globalAmbient
	the global ambient value
	\param fragShaderParamName6
	the name of the fragment shader parameter
	\param lightColor
	the color of the light
	\param fragShaderParamName7
	the name of the fragment shader parameter
	\param lightDirection
	the direction of the light
	\param fragShaderParamName8
	the name of the fragment shader parameter
	\param lightPosition
	the position of the light
	\param fragShaderParamName9
	the name of the fragment shader parameter
	\param eyePosition
	the position of the eye

	\param fragShaderParamName10
	the name of the fragment shader parameter
	\param Ke
	the emissive value
	\param fragShaderParamName11
	the name of the fragment shader parameter
	\param Ka
	the ambient value
	\param fragShaderParamName12
	the name of the fragment shader parameter
	\param Kd
	the diffuse value
	\param fragShaderParamName13
	the name of the fragment shader parameter
	\param Ks
	the specular value
	\param fragShaderParamName14
	the name of the fragment shader parameter
	\param shininess
	the shininess value

	\param fragShaderParamName15
	the name of the fragment shader parameter
	\param constantCoeff
	the constant attenuation coefficient
	\param fragShaderParamName16
	the name of the fragment shader parameter
	\param linearCoeff
	the linear attenuation coefficient
	\param fragShaderParamName17
	the name of the fragment shader parameter
	\param quadraticCoeff
	the quadratic attenuation coefficient

	\param fragShaderParamName18
	the name of the fragment shader parameter
	\param spotLightInnerCone
	the angle of the spot light inner cone
	\param fragShaderParamName19
	the name of the fragment shader parameter
	\param spotLightOuterCone
	the angle of the spot light outer cone

	\param fragShaderParamName20
	the name of the fragment shader parameter
	\param lightType
	the type of light
	
	\param fragShaderParamName21
	the name of the fragment shader parameter
	\param lightAttenuationFlag
	the flag to enable/disable attenuation

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeFresnelFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
		const char * fragShaderParamName3, const unsigned projTextureId,
		const char * fragShaderParamName4, const unsigned cubeMapTextureId,
		const char * fragShaderParamName5, const Math::Vector4 globalAmbient, 
		const char * fragShaderParamName6, const Math::Vector4 lightColor, 
		const char * fragShaderParamName7, const Math::Vector4 lightDirection, 
		const char * fragShaderParamName8, const Math::Vector4 lightPosition, 
		const char * fragShaderParamName9, const Math::Vector4 eyePosition, 
		const char * fragShaderParamName10, const Math::Vector4 Ke, 
		const char * fragShaderParamName11, const Math::Vector4 Ka, 
		const char * fragShaderParamName12, const Math::Vector4 Kd,
		const char * fragShaderParamName13, const Math::Vector4 Ks, 
		const char * fragShaderParamName14, const float shininess,
		const char * fragShaderParamName15, const float constantCoeff, 
		const char * fragShaderParamName16, const float linearCoeff, 
		const char * fragShaderParamName17, const float quadraticCoeff, 
		const char * fragShaderParamName18, const float spotLightInnerCone, 
		const char * fragShaderParamName19, const float spotLightOuterCone, 			
		const char * fragShaderParamName20, const int lightType, 
		const char * fragShaderParamName21, const int lightAttenuationFlag ) const
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;
		
		fragShader.SetIntParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );
		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName2 ) );
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName3 ) );

		//set the environment textures
		fragShader.SetTexSamplerParam( cubeMapTextureId, fragShader.GetParam( fragShaderParamName4 ) );

		// set the parameters needed for the lighting equation
		fragShader.SetFloat3Param( globalAmbient.GetFloatX(), globalAmbient.GetFloatY(), globalAmbient.GetFloatZ(), fragShader.GetParam( fragShaderParamName5 ) );
		fragShader.SetFloat3Param( lightColor.GetFloatX(), lightColor.GetFloatY(), lightColor.GetFloatZ(), fragShader.GetParam( fragShaderParamName6 ) );
		fragShader.SetFloat3Param( lightDirection.GetFloatX(), lightDirection.GetFloatY(), lightDirection.GetFloatZ(), fragShader.GetParam( fragShaderParamName7 ) );
		fragShader.SetFloat3Param( lightPosition.GetFloatX(), lightPosition.GetFloatY(), lightPosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName8 ) );
		fragShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName9 ) );

		//set the material values
		fragShader.SetFloat3Param( Ke.GetFloatX(), Ke.GetFloatY(), Ke.GetFloatZ(), fragShader.GetParam( fragShaderParamName10 ) );
		fragShader.SetFloat3Param( Ka.GetFloatX(), Ka.GetFloatY(), Ka.GetFloatZ(), fragShader.GetParam( fragShaderParamName11 ) );
		fragShader.SetFloat3Param( Kd.GetFloatX(), Kd.GetFloatY(), Kd.GetFloatZ(), fragShader.GetParam( fragShaderParamName12 ) );
		fragShader.SetFloat3Param( Ks.GetFloatX(), Ks.GetFloatY(), Ks.GetFloatZ(), fragShader.GetParam( fragShaderParamName13 ) );
		fragShader.SetFloatParam( shininess, fragShader.GetParam( fragShaderParamName14 ) );

		//set the attenuation values
		fragShader.SetFloatParam( constantCoeff, fragShader.GetParam( fragShaderParamName15 ) );
		fragShader.SetFloatParam( linearCoeff, fragShader.GetParam( fragShaderParamName16 ) );
		fragShader.SetFloatParam( quadraticCoeff, fragShader.GetParam( fragShaderParamName17 ) );

		//set the spot light cone
		fragShader.SetFloatParam( spotLightInnerCone, fragShader.GetParam( fragShaderParamName18 ) );
		fragShader.SetFloatParam( spotLightOuterCone, fragShader.GetParam( fragShaderParamName19 ) );

		//set the light type
		fragShader.SetIntParam( lightType, fragShader.GetParam( fragShaderParamName20 ) );

		//set the light attenuation flag
		fragShader.SetIntParam( lightAttenuationFlag, fragShader.GetParam( fragShaderParamName21 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Invoke the reflective fragment shader for rendering

	\param effectsPtr
	the pointer to the effect
	\param fragShaderName
	the name of the fragment shader
	
	\param fragShaderParamName1
	the name of the fragment shader parameter
	\param fragShaderParamName2
	the name of the fragment shader parameter
	\param textureId
	the texture id
	\param fragShaderParamName3
	the name of the fragment shader parameter
	\param projTextureId
	the projective texture id	

	\param fragShaderParamName4
	the name of the fragment shader parameter
	\param frontMapTextureId
	the front map texture id
	\param fragShaderParamName4
	the name of the fragment shader parameter
	\param backMapTextureId
	the back map texture id

	\param fragShaderParamName5
	the name of the fragment shader parameter
	\param globalAmbient
	the global ambient value
	\param fragShaderParamName6
	the name of the fragment shader parameter
	\param lightColor
	the color of the light
	\param fragShaderParamName7
	the name of the fragment shader parameter
	\param lightDirection
	the direction of the light
	\param fragShaderParamName8
	the name of the fragment shader parameter
	\param lightPosition
	the position of the light
	\param fragShaderParamName9
	the name of the fragment shader parameter
	\param eyePosition
	the position of the eye

	\param fragShaderParamName10
	the name of the fragment shader parameter
	\param Ke
	the emissive value
	\param fragShaderParamName11
	the name of the fragment shader parameter
	\param Ka
	the ambient value
	\param fragShaderParamName12
	the name of the fragment shader parameter
	\param Kd
	the diffuse value
	\param fragShaderParamName13
	the name of the fragment shader parameter
	\param Ks
	the specular value
	\param fragShaderParamName14
	the name of the fragment shader parameter
	\param shininess
	the shininess value

	\param fragShaderParamName15
	the name of the fragment shader parameter
	\param constantCoeff
	the constant attenuation coefficient
	\param fragShaderParamName16
	the name of the fragment shader parameter
	\param linearCoeff
	the linear attenuation coefficient
	\param fragShaderParamName17
	the name of the fragment shader parameter
	\param quadraticCoeff
	the quadratic attenuation coefficient

	\param fragShaderParamName18
	the name of the fragment shader parameter
	\param spotLightInnerCone
	the angle of the spot light inner cone
	\param fragShaderParamName19
	the name of the fragment shader parameter
	\param spotLightOuterCone
	the angle of the spot light outer cone

	\param fragShaderParamName20
	the name of the fragment shader parameter
	\param reflectivity
	the reflectivity value

	\param fragShaderParamName21
	the name of the fragment shader parameter
	\param lightType
	the type of light
	
	\param fragShaderParamName22
	the name of the fragment shader parameter
	\param lightAttenuationFlag
	the flag to enable/disable attenuation

	\return
	*/
	/******************************************************************************/
	void RenderManager::InvokeDualParaboloidReflectiveFragmentShader( const Effects * effectsPtr, const char * fragShaderName, 
		const char * fragShaderParamName1, const char * fragShaderParamName2, const unsigned textureId,
		const char * fragShaderParamName3, const unsigned projTextureId,
		const char * fragShaderParamName4, const unsigned frontMapTextureId,
		const char * fragShaderParamName5, const unsigned backMapTextureId,
		const char * fragShaderParamName6, const Math::Vector4 globalAmbient, 
		const char * fragShaderParamName7, const Math::Vector4 lightColor, 
		const char * fragShaderParamName8, const Math::Vector4 lightDirection, 
		const char * fragShaderParamName9, const Math::Vector4 lightPosition, 
		const char * fragShaderParamName10, const Math::Vector4 eyePosition, 
		const char * fragShaderParamName11, const Math::Vector4 Ke, 
		const char * fragShaderParamName12, const Math::Vector4 Ka, 
		const char * fragShaderParamName13, const Math::Vector4 Kd,
		const char * fragShaderParamName14, const Math::Vector4 Ks, 
		const char * fragShaderParamName15, const float shininess,
		const char * fragShaderParamName16, const float constantCoeff, 
		const char * fragShaderParamName17, const float linearCoeff, 
		const char * fragShaderParamName18, const float quadraticCoeff, 
		const char * fragShaderParamName19, const float spotLightInnerCone, 
		const char * fragShaderParamName20, const float spotLightOuterCone, 
		const char * fragShaderParamName21, const float reflectivity, 
		const char * fragShaderParamName22, const int lightType, 
		const char * fragShaderParamName23, const int lightAttenuationFlag ) const
	{
		Shader::Shader fragShader = effectsPtr->GetShaderMap().find( fragShaderName )->second;

		fragShader.SetIntParam( textureId, fragShader.GetParam( fragShaderParamName1 ) );
		// set the 2D texture sampler
		fragShader.SetTexSamplerParam( textureId, fragShader.GetParam( fragShaderParamName2 ) );
		fragShader.SetTexSamplerParam( projTextureId, fragShader.GetParam( fragShaderParamName3 ) );

		//set the environment textures
		fragShader.SetTexSamplerParam( frontMapTextureId, fragShader.GetParam( fragShaderParamName4 ) );
		fragShader.SetTexSamplerParam( backMapTextureId, fragShader.GetParam( fragShaderParamName5 ) );

		// set the parameters needed for the lighting equation
		fragShader.SetFloat3Param( globalAmbient.GetFloatX(), globalAmbient.GetFloatY(), globalAmbient.GetFloatZ(), fragShader.GetParam( fragShaderParamName6 ) );
		fragShader.SetFloat3Param( lightColor.GetFloatX(), lightColor.GetFloatY(), lightColor.GetFloatZ(), fragShader.GetParam( fragShaderParamName7 ) );
		fragShader.SetFloat3Param( lightDirection.GetFloatX(), lightDirection.GetFloatY(), lightDirection.GetFloatZ(), fragShader.GetParam( fragShaderParamName8 ) );
		fragShader.SetFloat3Param( lightPosition.GetFloatX(), lightPosition.GetFloatY(), lightPosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName9 ) );
		fragShader.SetFloat3Param( eyePosition.GetFloatX(), eyePosition.GetFloatY(), eyePosition.GetFloatZ(), fragShader.GetParam( fragShaderParamName10 ) );

		//set the material values
		fragShader.SetFloat3Param( Ke.GetFloatX(), Ke.GetFloatY(), Ke.GetFloatZ(), fragShader.GetParam( fragShaderParamName11 ) );
		fragShader.SetFloat3Param( Ka.GetFloatX(), Ka.GetFloatY(), Ka.GetFloatZ(), fragShader.GetParam( fragShaderParamName12 ) );
		fragShader.SetFloat3Param( Kd.GetFloatX(), Kd.GetFloatY(), Kd.GetFloatZ(), fragShader.GetParam( fragShaderParamName13 ) );
		fragShader.SetFloat3Param( Ks.GetFloatX(), Ks.GetFloatY(), Ks.GetFloatZ(), fragShader.GetParam( fragShaderParamName14 ) );
		fragShader.SetFloatParam( shininess, fragShader.GetParam( fragShaderParamName15 ) );

		//set the attenuation values
		fragShader.SetFloatParam( constantCoeff, fragShader.GetParam( fragShaderParamName16 ) );
		fragShader.SetFloatParam( linearCoeff, fragShader.GetParam( fragShaderParamName17 ) );
		fragShader.SetFloatParam( quadraticCoeff, fragShader.GetParam( fragShaderParamName18 ) );

		//set the spot light cone
		fragShader.SetFloatParam( spotLightInnerCone, fragShader.GetParam( fragShaderParamName19 ) );
		fragShader.SetFloatParam( spotLightOuterCone, fragShader.GetParam( fragShaderParamName20 ) );

		//set the reflective properties
		fragShader.SetFloatParam( reflectivity, fragShader.GetParam( fragShaderParamName21 ) );

		//set the light type
		fragShader.SetIntParam( lightType, fragShader.GetParam( fragShaderParamName22 ) );

		//set the light attenuation flag
		fragShader.SetIntParam( lightAttenuationFlag, fragShader.GetParam( fragShaderParamName23 ) );

		// update the uniform parameters in the shader
		fragShader.UpdateProgramParams();
	}

} //end namespace GraphicsFramework