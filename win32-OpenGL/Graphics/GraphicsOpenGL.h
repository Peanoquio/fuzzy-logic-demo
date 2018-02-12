/******************************************************************************/
/*!
\file GraphicsOpenGL.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 21/12/2011
\brief
This is the OpenGL graphics interface for drawing and for initializing/destroying the render context

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef GRAPHICS_OPENGL_H
#define GRAPHICS_OPENGL_H
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsInterface.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/GLU.h>


namespace GraphicsFramework
{

	class GraphicsOpenGL : public GraphicsInterface
	{
	public:
		GraphicsOpenGL( void );
		virtual ~GraphicsOpenGL( void );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//these functions deal with the functionalities of the graphics interface

		virtual void Init( HWND win, float width, float height );
		virtual void Shutdown( void );
		virtual void StartDrawing( void );
		virtual void EndDrawing( void );	

		virtual void LoadToBuffer( GraphicsObject & graphicsObj, Mesh & mesh ) const;
		virtual void LoadImageToBuffer( const char * textureName, ImageObj & imageObj );
		virtual void AllocateImageToBuffer( const char * textureName, const unsigned width, const unsigned height );
		virtual void LoadCubeMapToBuffer( const char * cubeMapTextureName, const char ** imageTextureNameArr, ImageObj * imageObjArr, const unsigned imageObjCount );
		virtual void LoadTexMapToFBO( const char * textureMapName, const unsigned imageWidgth, const unsigned imageHeight );
		
		virtual void Draw( const GLuint VAO, const BaseGeometryBuilder * baseGeometryBuilder ) const;
		virtual void Draw( const GLuint VAO, const BaseGeometryBuilder * baseGeometryBuilder, const GLuint textureId ) const;
		virtual void Update( float dt, const BaseGeometryBuilder * baseGeometryBuilder ) const;

		virtual unsigned PackColor( unsigned char r,
								   unsigned char g,
								   unsigned char b,
								   unsigned char a );
		virtual void PrintText( const char* text, float x, float y, TextSpace space,
							   unsigned char r = 255,
							   unsigned char g = 255,
							   unsigned char b = 255,
							   unsigned char a = 255 );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//these functions deal with setting up the projections based on the graphics interface used

		void SetViewPort( const int x, const int y, const unsigned width, const unsigned height ) const;
		void SetMatrixMode( const unsigned matrixMode );
		void LoadMatrixToGraphicsInterface( const Math::Mtx44 & matrix );

	private:
		HGLRC						m_renderContext;
		HDC							m_deviceContext;
		HFONT						m_font;
		GLuint						m_textList;
		char						m_currGLVersion;
		char						m_newGLVersion;			

		void InitialiseOpenGLState( void );
		void InitializeText( void );
		void LoadCompressedImageToFile( const char * fileName, ImageObj & imageObj ) const; 
		

		//make the copy constructor private
		GraphicsOpenGL( const GraphicsOpenGL & graphicsOpenGL );
		//make the assignment operator private
		GraphicsOpenGL & operator=( const GraphicsOpenGL & graphicsOpenGL );
	};

} //end namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////