/******************************************************************************/
/*!
\file GraphicsOpenGL.cpp
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


#include "GraphicsOpenGL.h"
#include "MeshObj.h"
#include "../Utility/Utility.h"
#include "../ErrorHandling/MessageBox.h"
#include "../File/CustomFileHandler.h"


#include <sstream> // std::wstringstream
#if defined(UNICODE)
typedef std::wstringstream StringStream_t;
#else
typedef std::stringstream SringStream_t;
#endif // UNICODE

// macro used to set the buffer offset of the OpenGL VBOs
#define BUFFER_OFFSET(bytes)(reinterpret_cast<const GLubyte *>(0) + bytes)


namespace GraphicsFramework
{
	/******************************************************************************/
	/*! 
	\brief 
	The constructor for the GraphicsOpenGL class

	\param
	\return
	*/
	/******************************************************************************/
	GraphicsOpenGL::GraphicsOpenGL( void )
		: m_renderContext( 0 ),
		m_deviceContext( 0 ),
		m_font( 0 ),
		m_textList( 0 ),
		m_currGLVersion( '0' ),
		m_newGLVersion( '3' )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The destructor for the GraphicsOpenGL class

	\param
	\return
	*/
	/******************************************************************************/
	GraphicsOpenGL::~GraphicsOpenGL( void )
	{
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets up the viewport

	\param x
	the x coordinate
	\param y
	the y coordinate
	\param width
	the width of the viewport
	\param height
	the height of the viewport
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::SetViewPort( const int x, const int y, const unsigned width, const unsigned height ) const
	{
		//invoke the OpenGL function
		glViewport( x, y, width, height );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets up the matrix mode

	\param matrixMode
	the matrix mode
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::SetMatrixMode( const unsigned matrixMode )
	{
		//invoke the OpenGL function to set the matrix mode
		//glMatrixMode( static_cast<GLenum>( matrixMode ) );
		//glLoadIdentity();

		//toggle the matrix mode for the custom matrix stack
		if ( matrixMode == Utility::PROJECTION )
			this->m_matrixStack.MatrixMode( Utility::PROJECTION );
		else if ( matrixMode == Utility::MODELVIEW )
			this->m_matrixStack.MatrixMode( Utility::MODELVIEW );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Loads the matrix to the graphics API

	\param matrix
	the matrix value
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::LoadMatrixToGraphicsInterface( const Math::Mtx44 & matrix )
	{
		//invoke the OpenGL function to load the matrix
		glLoadMatrixf( matrix.GetMatrixArr() );		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initializes the OpenGL render context for the window

	\param hWnd
	the handle to the window
	\param width
	the screen width
	\param height
	the screen height
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::Init( HWND hWnd, float width, float height )
	{
		const LPCTSTR LP_WINDOW_NAME = TEXT("Window to the World");
		const char * MY_GL_CURRENT_VERSION;
		const char MY_GL_NEW_VERSION = '3';
		char myGlCurrVersion;

		//set the handle to the window
		this->m_windowHandle = hWnd;
		//set the screen dimensions
		this->m_screenWidth = width;
		this->m_screenHeight = height;

		BOOL bResult = FALSE;
		HGLRC tmpHGLRC = NULL;


		//set up the pixel format descriptor
		const PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
			1,								// version number
			PFD_DRAW_TO_WINDOW |			// support window
			PFD_SUPPORT_OPENGL |			// support OpenGL
			PFD_DOUBLEBUFFER,				// double buffered
			PFD_TYPE_RGBA,					// RGBA type
			32,								// 32-bit color depth
			0, 0, 0, 0, 0, 0,				// color bits ignored
			0,								// no alpha buffer
			0,								// shift bit ignored
			0,								// no accumulation buffer
			0, 0, 0 ,0,						// accum bits ignored
			24,								// 24-bit z-buffer
			8,								// no stencil buffer
			0,								// no auxiliary buffer
			0,								// main layer
			0,								// reserved
			0, 0, 0							// layer masks ignored
		};


		//  Get device context only once
		this->m_deviceContext = GetDC ( this->m_windowHandle );

		// Pixel format
		int nPixelFormat = ChoosePixelFormat( this->m_deviceContext, &pfd );
		ASSERT ( nPixelFormat == 0, "Cannot choose pixel format." );

		bResult = SetPixelFormat( this->m_deviceContext, nPixelFormat, &pfd );
		ASSERT ( bResult == FALSE, "Cannot set pixel format." );

		// Create the OpenGL Rendering Context, which is suitable for drawing on the device referenced by hDC.
		// The rendering context has the same pixel format as the device context.
		tmpHGLRC = wglCreateContext( this->m_deviceContext );
		ASSERT ( tmpHGLRC == NULL, "Cannot create the OpenGL Rendering Context." );

		// Makes a specified OpenGL Rendering Context the calling thread's current rendering context.
		// All subsequent OpenGL calls made by the thread are drawn on the device identified by hDC
		bResult = wglMakeCurrent( this->m_deviceContext, tmpHGLRC );
		ASSERT ( tmpHGLRC == NULL, "Cannot make the specified OpenGL Rendering Context the calling thread's current rendering context." );		

		// Initialising OpenGL extensions
		GLenum err = glewInit();

		if (err != GLEW_OK)
		{
			ASSERT ( err != GLEW_OK, "Cannot initialize the OpenGL extensions" );
		}

		//Checking GL version
		MY_GL_CURRENT_VERSION = (char*)glGetString( GL_VERSION );
		//std::strcpy(MY_GL_CURRENT_VERSION, (char*)glGetString(GL_VERSION);
		myGlCurrVersion = MY_GL_CURRENT_VERSION[0];
		//this->m_currGLVersion = MY_GL_CURRENT_VERSION[0];
		// Display the OpenGL version
		StringStream_t ss;
		ss << TEXT( "OpenGL version: " )
			<< MY_GL_CURRENT_VERSION;

		MessageBox( this->m_windowHandle, ss.str().c_str(), LP_WINDOW_NAME, MB_OK );

		//check if the OpenGL version is 3.0 and above
		if ( myGlCurrVersion >= MY_GL_NEW_VERSION )
		{
			// Check if the create context for the new OpenGL is available
			if ( Utility::isExtensionSupported( "WGL_ARB_create_context" ) == 1 
				&& wglewIsSupported( "WGL_ARB_create_context" ) == 1 )
			{
				const int attribs[] =
				{
					WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 3,
					WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
					// WGL_CONTEXT_CORE_PROFILE_BIT_ARB
					WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0
				};

				this->m_renderContext = wglCreateContextAttribsARB( this->m_deviceContext, 0 , attribs );

				if (!this->m_renderContext)
				{
					// TODO: Perform error handling for wglCreateContextAttribsARB
				}

				wglMakeCurrent( NULL, NULL );
				wglDeleteContext( tmpHGLRC );
				wglMakeCurrent( this->m_deviceContext, this->m_renderContext );

				// Checking the OpenGL version
				int OpenGLVersion[2] = {0};
				glGetIntegerv( GL_MAJOR_VERSION, &OpenGLVersion[0] );
				glGetIntegerv( GL_MINOR_VERSION, &OpenGLVersion[1] );		

				// Display the OpenGL version
				StringStream_t ss;
				ss << TEXT( "OpenGL version: " )
					<< OpenGLVersion[0]
				<< TEXT( "." )
					<< OpenGLVersion[1];

				MessageBox( this->m_windowHandle, ss.str().c_str(), LP_WINDOW_NAME, MB_OK );
			}
			else
			{
				// not possible to make a GL3.x context so use the old style context (GL 2.1 and below)
				this->m_renderContext = tmpHGLRC;
			}
		}
		else
		{
			// not possible to make a GL3.x context so use the old style context (GL 2.1 and below)
			this->m_renderContext = tmpHGLRC;
		}

		ASSERT ( this->m_renderContext == NULL, "Cannot create OpenGL render context." );

		//initialize the OpenGL state
		this->InitialiseOpenGLState();

		//initialize text
		this->InitializeText();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initializes the OpenGL state for setting background color, enabling culling, etc.

	\param
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::InitialiseOpenGLState ( void )
	{
		const GLushort PRIMITIVE_RESTART_INDEX = 0xFFFF;

		// set background color
		glClearColor( 0.0F, 0.0F, 0.0F, 1.0F );

		// enabling depth test
		glEnable( GL_DEPTH_TEST );	// enable z-buffering
		glClearDepth( 1.0F );		// depth buffer setup
		glDepthFunc( GL_LEQUAL );

		// Really Nice Perspective Calculations
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST ); 

		// set the value used to clear the Stencil Buffer
		glClearStencil( 0 );	

		//set back face culling
		glFrontFace( GL_CCW );
		glCullFace( GL_BACK );	
		glEnable( GL_CULL_FACE );

		//check if the OpenGL version is 3.0 and above
		if ( this->m_currGLVersion >= this->m_newGLVersion )
		{
			// enabling primitive restart
			glPrimitiveRestartIndex( PRIMITIVE_RESTART_INDEX );
			glEnable( GL_PRIMITIVE_RESTART );
		}

		glEnable( GL_TEXTURE_2D ); // Enable Texture Mapping
		glShadeModel( GL_SMOOTH ); // Enable Smooth Shading

		ASSERT ( glGetError() != GL_NO_ERROR, "Error encountered when initializing the OpenGL state." );		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Deletes the buffer, render context and device context

	\param
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::Shutdown( void )
	{
		//delete the font text list that we used
		glDeleteLists( this->m_textList, 96 );

		//1. need to deallocate the OpenGL objects
		//unbind buffers
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		glBindVertexArray( 0 );

		GLuint myVAO;
		GLuint myVBO;
		GLuint myIBO;
		GLuint myTextureId;
		GLuint texIdArrSize;

		//get the iterators of the map
		GraphicsObjectMap::iterator itor = this->m_graphicsObjMap.begin();
		GraphicsObjectMap::iterator end = this->m_graphicsObjMap.end();

		//loop through the iterator
		while ( itor != end )
		{
			//get the values from the map
			myVAO = itor->second.GetNameOfVAO();
			myVBO = itor->second.GetNameOfVBO();
			myIBO = itor->second.GetNameOfIBO();			

			//delete the buffers from the graphics API
			glDeleteBuffers( 1, &myIBO );
			glDeleteBuffers( 1, &myVBO );
			glDeleteVertexArrays( 1, &myVAO );

			//delete the textures from the buffer
			texIdArrSize = itor->second.GetTextureIdArrSize();
			for ( GLuint index = 0; index < texIdArrSize; ++index )
			{
				myTextureId = itor->second.GetTextureId( index );
				//delete the textures from the graphics API
				glDeleteTextures( 1, &myTextureId );
			}//end for loop

			++itor;
		}//end while loop

		this->m_graphicsObjMap.clear();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//delete environment textures		
		TextureIdMap::iterator envItor = this->m_environmentTexIdMap.begin();
		TextureIdMap::iterator envEnd = this->m_environmentTexIdMap.end();

		GLuint envTexId = 0;

		while ( envItor != envEnd )
		{
			envTexId = envItor->second;
			glDeleteTextures( 1, &envTexId );
			++envItor;
		}//end while loop

		this->m_environmentTexIdMap.clear();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//delete textures
		TextureIdMap::iterator texItor = this->m_textureIdMap.begin();
		TextureIdMap::iterator texEnd = this->m_textureIdMap.end();

		GLuint texId = 0;

		while ( texItor != texEnd )
		{
			texId = texItor->second;
			glDeleteTextures( 1, &texId );
			++texItor;
		}//end while loop

		this->m_textureIdMap.clear();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//delete FBOs
		TextureIdMap::iterator fboItor = this->m_environmentTexFBOIdMap.begin();
		TextureIdMap::iterator fboEnd = this->m_environmentTexFBOIdMap.end();
		
		GLuint fboId = 0;

		while ( fboItor != fboEnd )
		{
			fboId = fboItor->second;
			glDeleteFramebuffersEXT( 1, &fboId );
			++fboItor;
		}//end while loop

		this->m_environmentTexFBOIdMap.clear();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//delete RBOs		
		TextureIdMap::iterator rboItor = this->m_environmentTexRBOIdMap.begin();
		TextureIdMap::iterator rboEnd = this->m_environmentTexRBOIdMap.end();
		
		GLuint rboId = 0;

		while ( rboItor != rboEnd )
		{
			rboId = rboItor->second;
			glDeleteRenderbuffersEXT( 1, &rboId );
			++rboItor;
		}//end while loop

		this->m_environmentTexRBOIdMap.clear();		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//3. need to delete the OpenGL Render Context
		if ( wglMakeCurrent( NULL, NULL ) == 0 )
		{
			ASSERT ( wglMakeCurrent( NULL, NULL ) == 0, "Cannot make WGL current to destroy it" );
		}
		if ( wglDeleteContext( this->m_renderContext ) == 0 )
		{
			ASSERT ( wglDeleteContext( this->m_renderContext ) == 0, "Cannot destroy WGL" );
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//4. destroy the Device Context
		ReleaseDC( this->m_windowHandle, this->m_deviceContext ); // not necessary but does not hurt

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Makes this render context as the current context for rendering

	\param
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::StartDrawing( void )
	{
		//get the windows device context
		this->m_deviceContext = GetDC( this->m_windowHandle );

		//set our render context as the current
		wglMakeCurrent( this->m_deviceContext, this->m_renderContext );

		//clear the open gl color, depth, stencil buffer
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Swaps the buffers and releases the device context after rendering

	\param
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::EndDrawing( void )	
	{
		//swap the buffers
		if ( SwapBuffers( this->m_deviceContext ) == 0 )
		{
			ASSERT ( SwapBuffers( this->m_deviceContext ) == 0, "Error encountered when swapping buffers." );
		}

		//give the device context back to windows
		ReleaseDC( this->m_windowHandle, this->m_deviceContext);
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Loads the mesh into the buffer

	\param graphicsObj
	the graphics object that will store the VAO, VBO and IBO
	it will also store the texture id
	\param mesh
	the mesh to be loaded into the buffer
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::LoadToBuffer ( GraphicsObject & graphicsObj, Mesh & mesh ) const
	{
		enum
		{
			VBO = 0,
			IBO,
			NUM_BUFFERS
		};

		GLuint VAO;					// Vertex array object
		GLuint VBOs[NUM_BUFFERS];	// Vertex buffer object		

		//calculate the offset
		const int ColorOffset = 0;
		const int PositionOffset = sizeof( Color4 );
		const int TextureCoordsOffset = sizeof( Color4 ) + sizeof( Point3 );
		const int NormalOffset = sizeof( Color4 ) + sizeof( Point3 ) + sizeof( TextureCoord );

		//get the binding semantics
		const GLuint POSITION_INDEX = 0;	// binding semantic for position
		const GLuint COLOR0_INDEX = 3;		// binding semantic for color0
		const GLuint TEXCOORD0_INDEX = 8;	// binding semantic for texcoord0
		const GLuint NORMAL_INDEX = 2;		// binding semantic for normal

		// Creating Vertex Array Object	
		glGenVertexArrays( 1, &VAO );
		graphicsObj.SetNameOfVAO( VAO );

		// Binding Vertex Array Object
		glBindVertexArray( VAO );

		// Creating VBOs
		glGenBuffers( NUM_BUFFERS, VBOs );		

		// Binding VBO
		glBindBuffer( GL_ARRAY_BUFFER, VBOs[VBO] );
		//store the VBO name
		graphicsObj.SetNameOfVBO( VBOs[VBO] );

		// Copying vertex array into data store
		glBufferData(
			GL_ARRAY_BUFFER,
			mesh.GetNumberOfVertices() * sizeof( Vertex ),
			reinterpret_cast<const GLvoid *>( mesh.GetVertexArray() ),
			GL_STATIC_DRAW
			);

		// Binding IBO
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, VBOs[IBO] );
		//store the IBO name
		graphicsObj.SetNameOfIBO ( VBOs[IBO] );

		// Copying index array into data store
		glBufferData (
			GL_ELEMENT_ARRAY_BUFFER,
			mesh.GetNumberOfIndices() * sizeof( GLushort ),
			reinterpret_cast<const GLvoid *>( mesh.GetIndexArray() ),
			GL_STATIC_DRAW
			);

		// setting position offset
		glVertexAttribPointer(
			POSITION_INDEX,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof( Vertex ),
			BUFFER_OFFSET( PositionOffset )
			);
		glEnableVertexAttribArray( POSITION_INDEX );

		// setting color offset
		glVertexAttribPointer(
			COLOR0_INDEX,
			4,
			GL_UNSIGNED_BYTE,
			GL_TRUE,
			sizeof( Vertex ),
			BUFFER_OFFSET( ColorOffset )
			);
		glEnableVertexAttribArray( COLOR0_INDEX );

		/*
		glColorPointer(
			4,
			GL_UNSIGNED_BYTE,
			sizeof( Vertex ),
			BUFFER_OFFSET( ColorOffset )
			);
		glEnableClientState( GL_COLOR_ARRAY );	
		*/

		// setting texture coordinates offset
		glVertexAttribPointer(
			TEXCOORD0_INDEX,
			2,
			GL_FLOAT,
			GL_TRUE,
			sizeof( Vertex ),
			BUFFER_OFFSET( TextureCoordsOffset )
			);
		glEnableVertexAttribArray( TEXCOORD0_INDEX );

		/*
		glTexCoordPointer(
			2,
			GL_FLOAT,
			sizeof( Vertex ),
			BUFFER_OFFSET( TextureCoordsOffset )
			);
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );	
		*/

		// setting normal offset
		glVertexAttribPointer(
			NORMAL_INDEX,
			3,
			GL_FLOAT,
			GL_TRUE,
			sizeof( Vertex ),
			BUFFER_OFFSET( NormalOffset )
			);
		glEnableVertexAttribArray( NORMAL_INDEX );

		glBindVertexArray( 0 );		

		if ( glGetError() != GL_NO_ERROR )
		{
			ASSERT ( glGetError() != GL_NO_ERROR, "Cannot render the object." );
		}
		else
		{
			//delete the vertex and index arrays of the mesh
			mesh.DeleteVertexArray();
			mesh.DeleteIndexArray();			
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Loads the images into the buffer

	\param textureName
	the name of the texture
	\param imageObj
	the image object containing the image data
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::LoadImageToBuffer( const char * textureName, ImageObj & imageObj )
	{
		//validate if the mesh contains a texture
		if ( imageObj.GetImageData() != NULL && imageObj.GetImageSize() > 0 )
		{
			GLuint textureId;			// Texture ID

			// generate the texture name
			glGenTextures( 1, &textureId );                  

			// bind the texture name to the texture target
			glBindTexture( GL_TEXTURE_2D, textureId );

			//store the texture name
			this->StoreTexture( textureName, static_cast<unsigned>( textureId ) );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*
			The four calls to glTexParameter*() specify how the texture is to be wrapped
			and how the colors are to be filtered if there isn’t an exact match between
			texels in the texture and pixels on the screen.
			*/
			/*
			Sets the wrap parameter for texture coordinate s / texture coordinate t to either GL_CLAMP, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, or GL_REPEAT. 
			GL_CLAMP causes s coordinates to be clamped to the range [0,1] and is useful for preventing wrapping artifacts when mapping a single image onto an object. 
			GL_CLAMP_TO_BORDER causes the s coordinate to be clamped to the range -1 2N 1 + 1 2N , where N is the size of the texture in the direction of clamping.
			GL_CLAMP_TO_EDGE causes s coordinates to be clamped to the range 1 2N 1 - 1 2N , where N is the size of the texture in the direction of clamping. 
			GL_REPEAT causes the integer part of the s coordinate to be ignored; the GL uses only the fractional part, thereby creating a repeating pattern. 
			GL_MIRRORED_REPEAT causes the s coordinate to be set to the fractional part of the texture coordinate if the integer part of s is even; 
			if the integer part of s is odd, then the s texture coordinate is set to 1 - frac ? s , where frac ? s represents the fractional part of s. 
			Border texture elements are accessed only if wrapping is set to GL_CLAMP or GL_CLAMP_TO_BORDER. 
			Initially, GL_TEXTURE_WRAP_S is set to GL_REPEAT.
			*/
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
			/*
			The next two lines tell OpenGL what type of filtering to use when the image is larger (GL_TEXTURE_MAG_FILTER) 
			or stretched on the screen than the original texture, or when it's smaller (GL_TEXTURE_MIN_FILTER) on the screen than the actual texture. 
			I usually use GL_LINEAR for both. This makes the texture look smooth way in the distance, and when it's up close to the screen. 
			Using GL_LINEAR requires alot of work from the processor/video card, so if your system is slow, you might want to use GL_NEAREST. 
			A texture that's filtered with GL_NEAREST will appear blocky when it's stretched. You can also try a combination of both. 
			Make it filter things up close, but not things in the distance.
			*/
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );	
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*
			Anisotropic filtering is an advanced filtering technique that takes more than one sample point and blends them together. 
			Exactly how this is done is implementation-dependent, but the control is a specific value: the maximum number of samples 
			that can be taken of the texture. More samples may slow down performance, but increase image quality. 
			Then again, it may not, depending on the angle you're looking at the surface. Implementations only take extra samples when needed.
			To use anisotropic filtering, set the GL_TEXTURE_MAX_ANISOTROPY_EXT parameter. This parameter is floating-point, and can be set between 1.0f 
			and an implementation-defined maximum anisotropy (queried with GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT). 
			Any value greater than 1.0f counts as a use of anisotropic filtering.
			Anisotropic filtering is not a replacement for mipmaps or mipmap filtering. 
			For best results, combine a anisotropic filtering with a GL_LINEAR_MIPMAP_LINEAR minification filter.
			*/
			//check whether extension string can be found
			if ( Utility::isExtensionSupported( "GL_EXT_texture_filter_anisotropic" ) == 1 )
			{
				//the maximum anisotropy is a float and it has to be greater than 1.0 when the extension should take effect
				float maximumAnisotropy = 1.1F;
				//get the maximum value supported by the graphics card
				glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy );
				glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy );
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//DOES NOT WORK ON ATI VIDEO CARD
			/*
			GLint * compressed_format = 0;
			GLint   num_compressed_format;
			// enumerate the supported Compressed Internal Format					
			glGetIntegerv( GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &num_compressed_format );
			compressed_format = ( GLint* )malloc( num_compressed_format * sizeof( GLint ) );
			glGetIntegerv( GL_COMPRESSED_TEXTURE_FORMATS_ARB, compressed_format );
			free( compressed_format );
			compressed_format = 0;
			*/
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//image with internal compression format
			if ( imageObj.GetInternalFormat() != 0 )
			{
				glCompressedTexImage2D( GL_TEXTURE_2D, 0, imageObj.GetInternalFormat(), imageObj.GetImageWidth(), imageObj.GetImageHeight(), 0, imageObj.GetImageSize(), imageObj.GetImageData() );
			}
			else
			{
				GLint internalFormat = GL_COMPRESSED_RGB_ARB;
				GLenum format = GL_BGR;

				if ( imageObj.GetImageBpp() == 24 )
				{
					internalFormat = GL_COMPRESSED_RGB_ARB;
					format = GL_BGR;
				}
				else if ( imageObj.GetImageBpp() == 32 )
				{
					internalFormat = GL_COMPRESSED_RGBA_ARB;
					format = GL_BGRA;
				}
				// Generate The Texture ( specify a two-dimensional texture image )
				glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, imageObj.GetImageWidth(), imageObj.GetImageHeight(), 0, format, GL_UNSIGNED_BYTE, imageObj.GetImageData() );
						
				//load the compressed image to file if applicable
				this->LoadCompressedImageToFile( textureName, imageObj );				
			}

			//delete the image data of the mesh
			imageObj.DeleteImageData();
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//Mipmaps of a texture can be automatically generated with the glGenerateMipmap function. 
			//OpenGL 3.0 or greater is required for this function (or the extension GL_ARB_framebuffer_object).
			//glGenerateMipmap( GL_TEXTURE_2D );  //Generate mipmaps now!!!
			//In GL 3.0, GL_GENERATE_MIPMAP is deprecated, and in 3.1 and above, it was removed. So for those versions, you must use glGenerateMipmap.
			//glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE ); 
			glEnable( GL_TEXTURE_2D );
			glGenerateMipmapEXT( GL_TEXTURE_2D );
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			glBindTexture( GL_TEXTURE_2D, 0 );
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Allocate the image into the buffer by reserving space

	\param textureName
	the name of the texture
	\param width
	the image width to be allocated
	\param height
	the image height to be allocated
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::AllocateImageToBuffer( const char * textureName, const unsigned width, const unsigned height )
	{
		GLuint textureId;			// Texture ID

		// generate the texture name
		glGenTextures( 1, &textureId );                  

		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_2D, textureId );

		//store the texture name
		this->StoreTexture( textureName, static_cast<unsigned>( textureId ) );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );	

		//check whether extension string can be found
		if ( Utility::isExtensionSupported( "GL_EXT_texture_filter_anisotropic" ) == 1 )
		{
			//the maximum anisotropy is a float and it has to be greater than 1.0 when the extension should take effect
			float maximumAnisotropy = 1.1F;
			//get the maximum value supported by the graphics card
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy );
		}

		// Generate The Texture ( specify a two-dimensional texture image )
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

		glBindTexture( GL_TEXTURE_2D, 0 );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Loads the cube map images into the buffer

	\param cubeMapTextureName
	the name of the cube map texture
	\param imageTextureNameArr
	the name of the images of the cube map faces
	\param imageObjArr
	the array of image objects containing the image data
	\param imageObjCount
	the number of image objects in the array
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::LoadCubeMapToBuffer( const char * cubeMapTextureName, const char ** /*imageTextureNameArr*/, 
		ImageObj * imageObjArr, const unsigned imageObjCount )
	{
		GLuint textureId;
		// generate the texture name
		glGenTextures( 1, &textureId );               
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_CUBE_MAP, textureId );

		//store the texture name of the cube map
		this->StoreEnvironmentTexture( cubeMapTextureName, static_cast<unsigned>( textureId ) );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		The four calls to glTexParameter*() specify how the texture is to be wrapped
		and how the colors are to be filtered if there isn’t an exact match between
		texels in the texture and pixels on the screen.
		*/
		if ( Utility::isExtensionSupported("GL_EXT_texture_edge_clamp") == 1 )
		{
			glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT );
			glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT );
		}
		else
		{
			glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP );
		}

		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set texture environment parameters
		//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//check whether extension string can be found
		if ( Utility::isExtensionSupported( "GL_EXT_texture_filter_anisotropic" ) == 1 )
		{
			//the maximum anisotropy is a float and it has to be greater than 1.0 when the extension should take effect
			float maximumAnisotropy = 1.1F;
			//get the maximum value supported by the graphics card
			glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy );
			glTexParameterf( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy );
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//DOES NOT WORK ON ATI VIDEO CARD
		/*
		GLint * compressed_format = 0;
		GLint   num_compressed_format;
		// enumerate the supported Compressed Internal Format					
		glGetIntegerv( GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &num_compressed_format );
		compressed_format = ( GLint* )malloc( num_compressed_format * sizeof( GLint ) );
		glGetIntegerv( GL_COMPRESSED_TEXTURE_FORMATS_ARB, compressed_format );
		free( compressed_format );
		compressed_format = 0;
		*/
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//process each face of the cube map
		for ( unsigned int index = 0; index < imageObjCount; ++index )
		{
			ImageObj imageObj = imageObjArr[index];
			/*
			To allocate storage for the 6 faces of the cubemap, bind the texture to GL_TEXTURE_CUBE_MAP. 
			Then call glTexImage2D 6 times, using the same size, mipmap level, and image format. 
			The target parameter specifies which of the 6 faces of the cubemap to specify. 
			These faces are:
			GL_TEXTURE_CUBE_MAP_POSITIVE_X
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
			*/
			GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + index;							

			GLint internalFormat = GL_RGB;
			GLenum format = GL_BGR;

			if ( imageObj.GetImageBpp() == 24 )
			{
				internalFormat = GL_RGB;
				format = GL_BGR;
			}
			else if ( imageObj.GetImageBpp() == 32 )
			{
				internalFormat = GL_RGBA;
				format = GL_BGRA;
			}
			//for static environment image map
			//glTexImage2D( face, 0, internalFormat, imageObj.GetImageWidth(), imageObj.GetImageHeight(), 0, format, GL_UNSIGNED_BYTE, imageObj.GetImageData() );
			
			//no image data is set here since it should be dynamically generated through the FBO
			glTexImage2D( face, 0, internalFormat, imageObj.GetImageWidth(), imageObj.GetImageHeight(), 0, format, GL_UNSIGNED_BYTE, 0 );

			//delete the image data of the mesh
			imageObj.DeleteImageData();

		}//end for loop

		glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Loads the environment texture map into the Frame Buffer Object

	\param textureMapName
	the name of the environment map texture
	\param imageWidgth
	the width of the image
	\param imageHeight
	the height of the image
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::LoadTexMapToFBO( const char * textureMapName, const unsigned imageWidgth, const unsigned imageHeight )
	{
		// create a framebuffer object
		GLuint fboId;
		glGenFramebuffersEXT( 1, &fboId );
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fboId );

		// create a renderbuffer object to store depth info
		GLuint rboId;
		glGenRenderbuffersEXT( 1, &rboId );
		glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, rboId );
		glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, imageWidgth, imageHeight );

		// attach the renderbuffer to depth attachment point
		glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rboId );

		//store the FBO id of the environment map
		this->StoreEnvironmentTextureFBO( textureMapName, fboId );	
		//store the RBO id of the environment map
		this->StoreEnvironmentTextureRBO( textureMapName, rboId );	

		//unbind the FBO
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
		glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, 0 );
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Writes to file

	\param fileName
	the file name
	\param imageObj
	the image object to contain the file image details
	*/
	/******************************************************************************/
	void GraphicsOpenGL::LoadCompressedImageToFile( const char * fileName, ImageObj & imageObj ) const
	{
		GLint compressed;	
		glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_ARB, &compressed );

		// if the compression has been successful
		if ( compressed == GL_TRUE )
		{	
			GLint internalformat;
			GLint compressed_size;
			GLubyte * imageDataPtr = 0;

			//Retrieve the internal image and the compressed size of the image
			glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalformat );
			glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE_ARB, &compressed_size );

			//imageDataPtr = ( unsigned char *)malloc( compressed_size * sizeof( unsigned char ) );
			imageDataPtr = new unsigned char[ compressed_size * sizeof( unsigned char ) ];
					
			//get the compressed image from the buffer
			glGetCompressedTexImageARB( GL_TEXTURE_2D, 0, imageDataPtr );
			//glCompressedTexImage2D( GL_TEXTURE_2D, 0, internalformat, imageObj.GetImageWidth(), imageObj.GetImageHeight(), 0, compressed_size, imageDataPtr );

			//set the parameters for writing to file
			File::file_header fileHeader;
			fileHeader.m_width = imageObj.GetImageWidth(); 
			fileHeader.m_height = imageObj.GetImageHeight();
			fileHeader.m_internalFormat = internalformat;
			fileHeader.m_fileDataSize = compressed_size * sizeof( unsigned char );

			//write the compressed image to file
			File::CustomFileHandler fileHandler;
			fileHandler.WriteFile( fileHeader, imageDataPtr, fileName );

			//free( imageDataPtr );
			delete [] imageDataPtr;
			imageDataPtr = 0;
		}	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws the geometry based on the VAO passed and the BaseGeometryBuilder being used

	\param VAO
	the Vertex Array Object
	\param baseGeometryBuilder
	the pointer to the BaseGeometryBuilder
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::Draw( const GLuint VAO, const BaseGeometryBuilder * baseGeometryBuilder ) const
	{
		//invoke the draw function of the geometry builder
		baseGeometryBuilder->DrawGeometry( VAO );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Draws the geometry based on the VAO passed and the BaseGeometryBuilder being used
	This also provides the texture Id so that the geometry will be texturized

	\param VAO
	the Vertex Array Object
	\param baseGeometryBuilder
	the pointer to the BaseGeometryBuilder
	\param textureId
	the texture Id 
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::Draw( const GLuint VAO, const BaseGeometryBuilder * baseGeometryBuilder, const GLuint textureId ) const
	{
		//invoke the draw function of the geometry builder
		baseGeometryBuilder->DrawGeometry( VAO, textureId );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Updates the geometry

	\param baseGeometryBuilder
	the pointer to the BaseGeometryBuilder
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::Update( float dt, const BaseGeometryBuilder * baseGeometryBuilder ) const
	{
		baseGeometryBuilder->UpdateBehavior( dt );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Packs the color

	\param r
	red
	\param g
	green
	\param b
	blue
	\param a
	alpha
	\return unsigned
	the resulting color
	*/
	/******************************************************************************/
	unsigned GraphicsOpenGL::PackColor( unsigned char r,
								   unsigned char g,
								   unsigned char b,
								   unsigned char a )
	{
		//use the bitwise operator to construct the color
		unsigned color = (a << 24) | (b << 16) | (g << 8) | r;
		return color;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Prints the text to the screen

	\param text
	the text to be displayed
	\param x
	the x coordinate
	\param y
	the y coordinate
	\param space
	the coordinate space
	\param r
	red
	\param g
	green
	\param b
	blue
	\param a
	alpha
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::PrintText( const char* text, float x, float y, TextSpace space, unsigned char r /*= 255*/,
																					unsigned char g /*= 255*/,
																					unsigned char b /*= 255*/,
																					unsigned char a /*= 255*/ )
	{
		//validate if there's text
		if ( !text )
			return;
		
		float finalX = x;
		float finalY = y;

		//the screen space
		if ( space == TS_SCREEN )
		{
			//convert screen space coordinates to world space coordinates
			this->ConvertScreenToWorld( x, y, finalX, finalY );
			finalY *= -1.0f; 
		}

		//finalY += 1;	//height of font in world space

		//glLoadIdentity();
		unsigned color = this->PackColor( r, g, b, a );
		glColor4ubv( reinterpret_cast< const GLubyte* >( &color ) );
		glRasterPos2f( finalX, finalY );

		glPushAttrib( GL_LIST_BIT );			// Pushes The Display List Bits
		glListBase( this->m_textList - 32 );	// Sets The Base Character to 32
		GLsizei len = static_cast<GLsizei>( strlen( text ) );
		glCallLists( len, GL_UNSIGNED_BYTE, text ); // Draws The Display List Text
		glPopAttrib(); // Pops The Display List Bits
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Initializes writing text

	\param
	\return
	*/
	/******************************************************************************/
	void GraphicsOpenGL::InitializeText( void )
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//create list to hold font images
		this->m_textList = glGenLists( 96 ); //Hold 96 images/letters

		this->m_font = CreateFont(
			12,						//height
			10,						//width
			0,						//angle of escapement
			0,						//orientation
			FW_BOLD,				//font weight
			false,					//italic
			false,					//underline
			false,					//strike out
			DEFAULT_CHARSET,		//character set identifier
			OUT_TT_PRECIS,			//output precision
			CLIP_DEFAULT_PRECIS,	//clipping precision
			ANTIALIASED_QUALITY,	//output quality
			DEFAULT_PITCH,			//family and pitch
			(LPCWSTR)L"Arial" );	//font name

		// Selects The Font We Want
		HFONT oldFont = static_cast<HFONT>( SelectObject( this->m_deviceContext, this->m_font ) );

		// Builds 96 Characters Starting At Character 32
		wglUseFontBitmaps( this->m_deviceContext,
						  32,						//starting ascii char
						  96,						//number of items in list
						  this->m_textList );		//the list to be filled

		 // Selects The Font We Want
		SelectObject( this->m_deviceContext, oldFont );
		// Delete The Font
		DeleteObject( this->m_font );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

} //end namespace GraphicsFramework