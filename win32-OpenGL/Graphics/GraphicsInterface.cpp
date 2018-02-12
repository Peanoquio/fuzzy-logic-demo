/******************************************************************************/
/*!
\file GraphicsInterface.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 21/12/2011
\brief
This is the generic graphics interface for drawing and for initializing/destroying the render context

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "GraphicsInterface.h"
#include "../Math/MyMath.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*! 
	\brief 
	The constructor for the GraphicsInterface class

	\param
	\return
	*/
	/******************************************************************************/
	GraphicsInterface::GraphicsInterface( void )
		: m_windowHandle( 0 ),
		m_worldX( 0.0F ),
		m_worldY( 0.0F ),
		m_worldLastX( 0.0F ),
		m_worldLastY( 0.0F ),
		m_worldMinX( 0.0F ),
		m_worldMaxX( 0.0F ),
		m_worldMinY( 0.0F ),
		m_worldMaxY( 0.0F ),
		m_screenWidth( 1024.0F ),
		m_screenHeight( 768.0F ),
		m_FOV( 90.F ),
		m_aspectRatio( m_screenWidth / m_screenHeight ),
		m_graphicsObjMap(),
		m_textureIdMap(),
		m_camera(),
		m_matrixStack()
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The destructor for the GraphicsInterface class

	\param
	\return
	*/
	/******************************************************************************/
	GraphicsInterface::~GraphicsInterface( void )
	{
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Retrieves the handle to the window

	\param
	\return
	*/
	/******************************************************************************/
	const HWND & GraphicsInterface::GetWindowHandle( void ) const
	{
		return this->m_windowHandle;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Stores the texture
	\param textureName
	the name of the texture
	\param textureId
	the texture id
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::StoreTexture( const char * textureName, const unsigned textureId )
	{
		this->m_textureIdMap.insert( std::make_pair( textureName, textureId ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Stores the texture for the environment map
	\param textureName
	the name of the texture
	\param textureId
	the texture id
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::StoreEnvironmentTexture( const char * textureName, const unsigned textureId )
	{
		this->m_environmentTexIdMap.insert( std::make_pair( textureName, textureId ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Stores the depth texture for the environment map
	\param textureName
	the name of the texture
	\param depthTextureId
	the depth texture id
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::StoreEnvironmentDepthTexture( const char * textureName, const unsigned depthTextureId )
	{
		this->m_environmentDepthTexIdMap.insert( std::make_pair( textureName, depthTextureId ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Stores the texture FBO id for the environment map
	\param textureName
	the name of the texture
	\param fboId
	the FBO id
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::StoreEnvironmentTextureFBO( const char * textureName, const unsigned fboId )
	{
		this->m_environmentTexFBOIdMap.insert( std::make_pair( textureName, fboId ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Stores the texture RBO id for the environment map
	\param textureName
	the name of the texture
	\param rboId
	the RBO id
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::StoreEnvironmentTextureRBO( const char * textureName, const unsigned rboId )
	{
		this->m_environmentTexRBOIdMap.insert( std::make_pair( textureName, rboId ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the texture
	\param textureName
	the name of the texture
	\return unsigned
	the texture id
	*/
	/******************************************************************************/
	const unsigned GraphicsInterface::GetTexture( const char * textureName ) const
	{
		return this->m_textureIdMap.find( textureName )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the environment texture
	\param envTextureName
	the name of the environment texture
	\return unsigned
	the environment texture id
	*/
	/******************************************************************************/
	const unsigned GraphicsInterface::GetEnvTexture( const char * envTextureName ) const
	{
		return this->m_environmentTexIdMap.find( envTextureName )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the environment depth texture
	\param envTextureName
	the name of the environment depth texture
	\return unsigned
	the environment depth texture id
	*/
	/******************************************************************************/
	const unsigned GraphicsInterface::GetEnvDepthTexture( const char * envTextureName ) const
	{
		return this->m_environmentDepthTexIdMap.find( envTextureName )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the environment texture FBO
	\param envTextureName
	the name of the environment texture
	\return unsigned
	the environment texture FBO id
	*/
	/******************************************************************************/
	const unsigned GraphicsInterface::GetEnvTextureFBO( const char * envTextureName ) const
	{
		return this->m_environmentTexFBOIdMap.find( envTextureName )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the environment texture RBO
	\param envTextureName
	the name of the environment texture
	\return unsigned
	the environment texture RBO id
	*/
	/******************************************************************************/
	const unsigned GraphicsInterface::GetEnvTextureRBO( const char * envTextureName ) const
	{
		return this->m_environmentTexRBOIdMap.find( envTextureName )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Stores the texture
	\param
	\return TextureIdMap
	the map containing the texture ids
	*/
	/******************************************************************************/
	const TextureIdMap GraphicsInterface::GetTextureMap( void ) const
	{
		return this->m_textureIdMap;
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
	const Math::Mtx44 GraphicsInterface::CreateTexGenMtx( const Math::Mtx44 & modelMtx, const Math::Mtx44 & viewMtx, const Math::Mtx44 & projMtx ) const
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
	Contain the gameObj object
	\param objectType
	the type of object
	\param graphicsObject
	the graphics object
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::ContainGraphicsObject( const unsigned objectType, const GraphicsObject graphicsObject )
	{
		//insert the graphics object
		this->m_graphicsObjMap.insert( std::make_pair( objectType, graphicsObject ) );
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Retrieve the gameObj object
	\param objectType
	the type of object
	\return GraphicsObject
	the graphics object
	*/
	/******************************************************************************/
	const GraphicsObject GraphicsInterface::RetrieveGraphicsObject( const unsigned objectType )
	{
		//retrieve the value from the map
		return this->m_graphicsObjMap.find( objectType )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the map that contains pointers to graphic objects
	\param 
	\return GraphicsObjectMap &
	the reference to the map that contains pointers to graphic objects
	*/
	/******************************************************************************/
	const GraphicsObjectMap & GraphicsInterface::GetGraphicsObjectMap( void ) const
	{
		return this->m_graphicsObjMap;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Computes the dimensions of the world based on the field of view, aspect ratio and 
	the camera distance from the near plane

	\param fieldOfView
	the field of view in degrees
	\param aspectRatio
	the aspect ratio
	\param cameraDistanceFromNearPlane
	the camera distance from the near plane
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::ComputeWorldDimension ( const float fieldOfView, const float aspectRatio, const float cameraDistanceFromNearPlane )
	{
		//compute for the world max Y which is derived from:
		//worldMaxY / cameraDistanceFromNearPlane = sin (FOVdeg/2) / cos (FOVdeg/2)
		//worldMaxY / cameraDistanceFromNearPlane = tan (FOVdeg/2)
		this->m_worldMaxY = tanf ( Math::DegreeToRadian(fieldOfView) / 2.0F ) * cameraDistanceFromNearPlane;

		//compute for the world max X based on its aspect ratio with world max Y
		this->m_worldMaxX = this->m_worldMaxY * aspectRatio;

		//compute for the min values simply by negating the max values
		this->m_worldMinY = -this->m_worldMaxY;
		this->m_worldMinX = -this->m_worldMaxX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Converts the screen coordinates to world coordinates

	\param screenX
	the screen x coordinate
	\param screenY
	the screen y coordinate
	\param worldX
	reference to the world x coordinate that will be populated with the computed data
	\param worldY
	reference to the world y coordinate that will be populated with the computed data
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::ConvertScreenToWorld ( const float screenX, const float screenY, float& worldX, float& worldY )
	{
		//compute for the world width and height
		float worldWidth = this->m_worldMaxX - this->m_worldMinX;
		float worldHeight = this->m_worldMaxY - this->m_worldMinY;

		//ratio between the screen and the world dimensions
		float screenWorldWidthRatio = this->m_screenWidth / worldWidth;
		float screenWorldHeightRatio = this->m_screenHeight / worldHeight;

		//compute for the screen center since (0,0) starts at the top-left
		float screenCenterX = this->m_screenWidth / 2.0F;
		float screenCenterY = this->m_screenHeight / 2.0F;

		//compute for the screen x and y negative/positive values based on the screen center
		//then convert it to world coordinates based on the screen/world ratio
		this->m_worldX = (screenX - screenCenterX) / screenWorldWidthRatio;
		this->m_worldY = (screenY - screenCenterY) / screenWorldHeightRatio;

		worldX = this->m_worldX;
		worldY = this->m_worldY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Converts the world coordinates to screen coordinates

	\param worldX
	the world x coordinate
	\param worldY
	the world y coordinate
	\param screenX
	reference to the screen x coordinate that will be populated with the computed data
	\param screenY
	reference to the screen y coordinate that will be populated with the computed data
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::ConvertWorldToScreen ( const float worldX, const float worldY, float& screenX, float& screenY )
	{
		//compute for the world width and height
		float worldWidth = this->m_worldMaxX - this->m_worldMinX;
		float worldHeight = this->m_worldMaxY - this->m_worldMinY;

		//ratio between the screen and the world dimensions
		float screenWorldWidthRatio = this->m_screenWidth / worldWidth;
		float screenWorldHeightRatio = this->m_screenHeight / worldHeight;

		//compute for the screen center since (0,0) starts at the top-left
		float screenCenterX = this->m_screenWidth / 2.0F;
		float screenCenterY = this->m_screenHeight / 2.0F;

		//convert it to screen coordinates based on the screen/world ratio
		//compute for the screen x and y negative/positive values based on the screen center		
		screenX = (worldX * screenWorldWidthRatio) + screenCenterX;
		screenY = (worldY * screenWorldHeightRatio) + screenCenterY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the world last x coordinate

	\param worldLastX
	the world last x coordinate
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetWorldLastX ( const float worldLastX )
	{
		this->m_worldLastX = worldLastX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the world last y coordinate

	\param worldLastY
	the world last y coordinate
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetWorldLastY ( const float worldLastY )
	{
		this->m_worldLastY = worldLastY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the world minimum x coordinate

	\param worldMinX
	the world minimum x coordinate
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetWorldMinX ( const float worldMinX )
	{
		this->m_worldMinX = worldMinX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the world maximum x coordinate

	\param worldMaxX
	the world maximum x coordinate
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetWorldMaxX ( const float worldMaxX )
	{
		this->m_worldMaxX = worldMaxX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the world minimum y coordinate

	\param worldMinY
	the world minimum y coordinate
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetWorldMinY ( const float worldMinY )
	{
		this->m_worldMinY = worldMinY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the world maximum y coordinate

	\param worldMaxY
	the world maximum y coordinate
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetWorldMaxY ( const float worldMaxY )
	{
		this->m_worldMaxY = worldMaxY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the screen width

	\param screenWidth
	the screen width
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetScreenWidth ( const float screenWidth )
	{
		this->m_screenWidth = screenWidth;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the screen height

	\param screenHeight
	the screen height
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetScreenHeight ( const float screenHeight )
	{
		this->m_screenHeight = screenHeight;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the field of view

	\param FOV
	the field of view for a perspective projection
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetFieldOfView ( const float FOV )
	{
		this->m_FOV = FOV;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Set the aspect ratio

	\param FOV
	the aspect ratio for a perspective projection
	\return
	*/
	/******************************************************************************/
	void GraphicsInterface::SetAspectRatio ( const float aspectRatio )
	{
		this->m_aspectRatio = aspectRatio;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the last world x coordinate

	\param
	\return
	float - the last world x coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldLastX ( void ) const
	{
		return this->m_worldLastX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the last world y coordinate

	\param
	\return
	float - the last world y coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldLastY ( void ) const
	{
		return this->m_worldLastY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the world x coordinate

	\param
	\return
	float - the world x coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldX ( void ) const
	{
		return this->m_worldX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the world y coordinate

	\param
	\return
	float - the world y coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldY ( void ) const
	{
		return this->m_worldY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the world minimum x coordinate

	\param
	\return
	float - the world minimum x coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldMinX ( void ) const
	{
		return this->m_worldMinX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the world maximum x coordinate

	\param
	\return
	float - the world maximum x coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldMaxX ( void ) const
	{
		return this->m_worldMaxX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the world minimum y coordinate

	\param
	\return
	float - the world minimum y coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldMinY ( void ) const
	{
		return this->m_worldMinY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the world maximum y coordinate

	\param
	\return
	float - the world maximum y coordinate
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetWorldMaxY ( void ) const
	{
		return this->m_worldMaxY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the screen width

	\param
	\return
	float - the screen width
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetScreenWidth ( void ) const
	{
		return this->m_screenWidth;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the screen height

	\param
	\return
	float - the screen height
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetScreenHeight ( void ) const
	{
		return this->m_screenHeight;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the field of view

	\param
	\return
	float - the field of view
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetFieldOfView ( void ) const
	{
		return this->m_FOV;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the aspect ratio

	\param
	\return
	float - the aspect ratio
	*/
	/******************************************************************************/
	const float GraphicsInterface::GetAspectRatio ( void ) const
	{
		return this->m_aspectRatio;
	}


} //end namespace GraphicsFramework