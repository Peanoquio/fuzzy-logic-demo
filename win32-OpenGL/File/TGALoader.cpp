/******************************************************************************/
/*!
\file TGALoader.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #02
\date 19/01/2012
\brief
This is the TGA Loader:
1. can suppport 24BPP or 32BPP TGA images
2. does NOT support RLE Compression
For more information about TGA, refer to:
http://en.wikipedia.org/wiki/Truevision_TGA
http://paulbourke.net/dataformats/tga/
http://www.organicbit.com/closecombat/formats/tga.html

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "TGALoader.h"
#include "../ErrorHandling/MessageBox.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
// Standard header for MS Windows applications
#include <windows.h>	   
// Open Graphics Library (OpenGL) header
#include <GL/glew.h>
//#include <GL/wglew.h>
//#include <GL/GLU.h>


namespace File
{
	void TGALoader::Draw()
	{
		glPixelStorei( GL_UNPACK_ROW_LENGTH, this->m_tgaHeader.m_width );

		//if the bits per pixel is 32
		if ( this->m_tgaHeader.m_bpp == 32 )
		{
			glPixelStorei( GL_UNPACK_ALIGNMENT, 2 ); 
			glDrawPixels( this->m_tgaHeader.m_width, this->m_tgaHeader.m_height, GL_RGBA, GL_UNSIGNED_BYTE, this->m_imageDataPtr );
		}
		//if the bits per pixel is 24
		if ( this->m_tgaHeader.m_bpp == 24 )
		{
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 ); 
			glDrawPixels( this->m_tgaHeader.m_width, this->m_tgaHeader.m_height, GL_RGB, GL_UNSIGNED_BYTE, this->m_imageDataPtr );
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Release the pointer to the image data
	\param
	\return
	*/
	/******************************************************************************/
	void TGALoader::Release()
	{
		// Free image data from memory
		free( this->m_imageDataPtr );		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Load the image
	\param filename
	the file name of the image
	\return bool
	if true, image loading is successful, otherwise false if unsuccessful
	*/
	/******************************************************************************/
	bool TGALoader::Load( const char* filename )
	{
		std::fstream filestr;

		// open the file
		//allow input operations on the stream
		//consider stream as binary rather than text
		filestr.open( filename, std::ios::in | std::ios::binary );	

		// if the file is open, read the contents
		if ( filestr.is_open() )														
		{
			// read TGA header
			filestr.read( (char*) &this->m_tgaHeader , sizeof( struct tga_header ) );	

			//validate for error in reading the file
			if ( filestr.rdstate() == std::ios::eofbit )
			{
				ASSERT ( filestr.rdstate() == std::ios::eofbit, 
					"End-Of-File reached while performing an extracting operation on an input stream." );
				return false;
			}
			else if ( filestr.rdstate() == std::ios::failbit )
			{
				ASSERT ( filestr.rdstate() == std::ios::failbit, 
					"The last input operation failed because of an error related to the internal logic of the operation itself." );
				return false;
			}
			else if ( filestr.rdstate() == std::ios::badbit )
			{
				ASSERT ( filestr.rdstate() == std::ios::badbit, 
					"Error due to the failure of an input/output operation on the stream buffer." );
				return false;
			}


			//validate if the data in the file is valid
			if( ( this->m_tgaHeader.m_width <= 0 ) || ( this->m_tgaHeader.m_height <= 0 ) 
				|| ( ( this->m_tgaHeader.m_bpp != 24 ) && ( this->m_tgaHeader.m_bpp != 32 ) ) )
			{
				return false;
			} 


			// if the file header matches the uncompressed header
			if ( this->m_tgaHeader.m_imageTypeCode == 2 )
			{
				// load uncompressed TGA

				// read pixel data
				// 1 byte = 8 bits
				// Calculate image size ( width * height * bytes per pixel )
				int imageSize = this->m_tgaHeader.m_width * this->m_tgaHeader.m_height * ( this->m_tgaHeader.m_bpp / 8 );		

				// Reserve space in the memory to store our image data
				//this->m_imageDataPtr = (char*) malloc( imageSize );	
				this->m_imageDataPtr = new char[ imageSize ];
				// Read image data from file, into the reserved memory place
				filestr.read( (char*) this->m_imageDataPtr, imageSize );	

				/*
				Since TGA file is stored in little endian data:
				TGA is stored in BGR (Blue-Green-Red) format, we need to convert this to Red-Green-Blue (RGB).
				The following section does BGR to RGB conversion
				*/
				//this->FlipColorBytes();
			}
			// if the file header matches the compressed header
			else if ( this->m_tgaHeader.m_imageTypeCode == 10 )
			{                                          
				// load compressed TGA
			}
			else
			{
				return false;
			} 

			filestr.close();
		}
		else
		{
			ASSERT ( filestr == NULL, "Error in opening file" );
			return false;
		}

		return true;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Flip the color byte values
	\param
	\return
	*/
	/******************************************************************************/
	void TGALoader::FlipColorBytes( void )
	{
		// read pixel data
		// 1 byte = 8 bits
		// Calculate image size ( width * height * bytes per pixel )
		int imageSize = this->m_tgaHeader.m_width * this->m_tgaHeader.m_height * ( this->m_tgaHeader.m_bpp / 8 );	

		/*
		Since TGA file is stored in little endian data:
		TGA is stored in BGR (Blue-Green-Red) format, we need to convert this to Red-Green-Blue (RGB).
		The following section does BGR to RGB conversion
		*/
		//if the bits per pixel is 24
		if ( this->m_tgaHeader.m_bpp == 24 )
		{
			//loop through the image by BGR
			for ( int i = 0; i < imageSize; i+=3 )
			{	
				// 24 bits per pixel = 3 byte per pixel
				//swap first and the last byte of BGR to make it RGB
				char c = this->m_imageDataPtr[i];
				this->m_imageDataPtr[i] = this->m_imageDataPtr[i+2];
				this->m_imageDataPtr[i+2] = c;
			}
		}
		//if the bits per pixel is 32
		else if ( this->m_tgaHeader.m_bpp == 32 )
		{
			for ( int i = 0; i < imageSize; i+=4 )
			{	
				// 32 bits per pixel = 4 byte per pixel	
				//swap first and the last byte of BGR to make it RGB
				char c = this->m_imageDataPtr[i];
				this->m_imageDataPtr[i] = this->m_imageDataPtr[i+2];
				this->m_imageDataPtr[i+2] = c;
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the image data
	\param
	\return char *
	the pointer to the image data
	*/
	/******************************************************************************/
	char * TGALoader::GetImageData( void ) const
	{
		return this->m_imageDataPtr;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the image type code
	\param
	\return unsigned char
	the image type code
	*/
	/******************************************************************************/
	const unsigned char TGALoader::GetImageTypeCode( void ) const
	{
		return this->m_tgaHeader.m_imageTypeCode;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the image bits per pixel
	\param
	\return unsigned char
	the image bits per pixel
	*/
	/******************************************************************************/
	const unsigned char TGALoader::GetImageBpp( void ) const
	{
		return this->m_tgaHeader.m_bpp;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the image width
	\param
	\return unsigned short
	the image width
	*/
	/******************************************************************************/
	const unsigned short TGALoader::GetImageWidth( void ) const
	{
		return this->m_tgaHeader.m_width;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the image height
	\param
	\return unsigned short
	the image height
	*/
	/******************************************************************************/
	const unsigned short TGALoader::GetImageHeight( void ) const
	{
		return this->m_tgaHeader.m_height;
	}


}//end namespace File
