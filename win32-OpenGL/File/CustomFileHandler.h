/******************************************************************************/
/*!
\file CustomFileHandler.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #02
\date 31/01/2012
\brief
Opens, read and writes the contents of the file

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef CUSTOM_FILE_HANDLER_H
#define CUSTOM_FILE_HANDLER_H
////////////////////////////////////////////////////////////////////////////////


namespace File
{
	struct file_header
	{
		unsigned short	m_width;			// image width in pixels
		unsigned short	m_height;			// image height in pixels
		int m_internalFormat;				// internal file format
		int m_fileDataSize;					// file data size
	};

	class CustomFileHandler
	{

	public:
		void WriteFile( file_header & fileHeader, unsigned char * fileData, const char * fileName ) const;
		bool ReadFile( const char * fileName );
		void Release();

		const unsigned short GetImageWidth( void ) const;
		const unsigned short GetImageHeight( void ) const;		
		const int GetInternalFormat( void ) const;
		const int GetFileDataSize( void ) const;
		char * GetFileData( void ) const;

	private:
		char * m_fileDataPtr; 			
		file_header m_fileHeader;	
	};

}//using namespace file

#endif
////////////////////////////////////////////////////////////////////////////////