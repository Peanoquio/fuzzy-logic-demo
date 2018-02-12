/******************************************************************************/
/*!
\file GraphicsInterface.h
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


////////////////////////////////////////////////////////////////////////////////
#ifndef GRAPHICS_INTERFACE_H
#define GRAPHICS_INTERFACE_H
////////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include <unordered_map>
#include "GraphicsObj.h"
#include "MeshObj.h"
#include "ImageObj.h"
#include "../GeometryBuilder/BaseGeometryBuilder.h"
#include "../Utility/MatrixStack.h"
#include "../Shaders/Shader.h"

#include "../Camera/Camera.h"


namespace GraphicsFramework
{
	enum TextSpace
	{
		TS_WORLD,
		TS_SCREEN
	};

	enum EnvMapViewPort
	{
		ENVMAP_VIEWPORT_SIZE = 512
	};

	typedef std::unordered_map< const unsigned, GraphicsFramework::GraphicsObject > GraphicsObjectMap;
	typedef std::hash_map< const char *, unsigned > TextureIdMap;

	class GraphicsInterface
	{
	public:
		GraphicsInterface( void );
		virtual ~GraphicsInterface( void );

		const HWND & GetWindowHandle( void ) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the functionalities of the graphics interface

		virtual void Init( HWND win, float width, float height ) = 0;
		virtual void Shutdown( void ) = 0;
		virtual void StartDrawing( void ) = 0;
		virtual void EndDrawing( void ) = 0;

		virtual void LoadToBuffer( GraphicsObject & graphicsObj, Mesh & mesh ) const = 0;
		virtual void LoadImageToBuffer( const char * textureName, ImageObj & imageObj ) = 0;
		virtual void AllocateImageToBuffer( const char * textureName, const unsigned width, const unsigned height ) = 0;
		virtual void LoadCubeMapToBuffer( const char * cubeMapTextureName, const char ** imageTextureNameArr, ImageObj * imageObjArr, const unsigned imageObjCount ) = 0;
		virtual void LoadTexMapToFBO( const char * textureMapName, const unsigned imageWidgth, const unsigned imageHeight ) = 0;
		
		virtual void Draw( const GLuint VAO, const BaseGeometryBuilder * baseGeometryBuilder ) const = 0;
		virtual void Draw( const GLuint VAO, const BaseGeometryBuilder * baseGeometryBuilder, const GLuint textureId ) const = 0;
		virtual void Update( float dt, const BaseGeometryBuilder * baseGeometryBuilder ) const = 0;

		virtual unsigned PackColor( unsigned char r,
								   unsigned char g,
								   unsigned char b,
								   unsigned char a ) = 0;
		virtual void PrintText( const char* text, float x, float y, TextSpace space,
							   unsigned char r = 255,
							   unsigned char g = 255,
							   unsigned char b = 255,
							   unsigned char a = 255 ) = 0;


		void StoreTexture( const char * textureName, const unsigned textureId );
		void StoreEnvironmentTexture( const char * textureName, const unsigned textureId );
		void StoreEnvironmentDepthTexture( const char * textureName, const unsigned depthTextureId );
		void StoreEnvironmentTextureFBO( const char * textureName, const unsigned fboId );
		void StoreEnvironmentTextureRBO( const char * textureName, const unsigned rboId );
		const TextureIdMap GetTextureMap( void ) const;
		const unsigned GetTexture( const char * textureName ) const;		
		const unsigned GetEnvTexture( const char * envTextureName ) const;
		const unsigned GetEnvDepthTexture( const char * envTextureName ) const;
		const unsigned GetEnvTextureFBO( const char * envTextureName ) const;
		const unsigned GetEnvTextureRBO( const char * envTextureName ) const;

		const Math::Mtx44 CreateTexGenMtx( const Math::Mtx44 & modelMtx, const Math::Mtx44 & viewMtx, const Math::Mtx44 & projMtx ) const; 
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//these functions deal with setting up the projections based on the graphics interface used

		virtual void SetViewPort( const int x, const int y, const unsigned width, const unsigned height ) const = 0;
		virtual void SetMatrixMode( const unsigned matrixMode ) = 0;
		virtual void LoadMatrixToGraphicsInterface( const Math::Mtx44 & matrix ) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//these functions deal with managing the graphics object

		void ContainGraphicsObject( const unsigned objectType, const GraphicsObject graphicsObject );
		const GraphicsObject RetrieveGraphicsObject( const unsigned objectType );
		const GraphicsObjectMap & GetGraphicsObjectMap( void ) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//these functions deal with world and screen dimensions

		void ComputeWorldDimension ( const float fieldOfView, const float aspectRatio, const float cameraDistanceFromNearPlane );
		void ConvertScreenToWorld ( const float screenX, const float screenY, float& worldX, float& worldY );
		void ConvertWorldToScreen ( const float worldX, const float worldY, float& screenX, float& screenY );
		
		void SetWorldLastX ( const float worldLastX );
		void SetWorldLastY ( const float worldLastY );

		void SetWorldMinX ( const float worldMinX );
		void SetWorldMaxX ( const float worldMaxX );
		void SetWorldMinY ( const float worldMinY );
		void SetWorldMaxY ( const float worldMaxY );	
		void SetScreenWidth ( const float screenWidth );
		void SetScreenHeight ( const float screenHeight );	
		void SetFieldOfView ( const float FOV );
		void SetAspectRatio ( const float aspectRatio );	

		const float GetWorldLastX ( void ) const;
		const float GetWorldLastY ( void ) const;

		const float GetWorldX ( void ) const;
		const float GetWorldY ( void ) const;
		const float GetWorldMinX ( void ) const;
		const float GetWorldMaxX ( void ) const;
		const float GetWorldMinY ( void ) const;
		const float GetWorldMaxY ( void ) const;
		const float GetScreenWidth ( void ) const;
		const float GetScreenHeight ( void ) const;	
		const float GetFieldOfView ( void ) const;
		const float GetAspectRatio ( void ) const;	
			
		Camera::Camera				m_camera;
		Utility::MatrixStack		m_matrixStack;
		

	protected:
		HWND						m_windowHandle;
		float						m_worldX;
		float						m_worldY;
		float						m_worldLastX;
		float						m_worldLastY;
		float						m_worldMinX;
		float						m_worldMaxX;
		float						m_worldMinY;
		float						m_worldMaxY;
		float						m_screenWidth;
		float						m_screenHeight;
		float						m_FOV;
		float						m_aspectRatio;

		GraphicsObjectMap			m_graphicsObjMap;	
		TextureIdMap				m_textureIdMap;
		TextureIdMap				m_environmentTexIdMap;
		TextureIdMap				m_environmentDepthTexIdMap;
		TextureIdMap				m_environmentTexFBOIdMap;
		TextureIdMap				m_environmentTexRBOIdMap;

	private:
		//make the copy constructor private
		GraphicsInterface( const GraphicsInterface & graphicsInterface );
		//make the assignment operator private
		GraphicsInterface & operator=( const GraphicsInterface & graphicsInterface );
	};

} //end namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////