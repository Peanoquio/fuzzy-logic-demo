/******************************************************************************/
/*!
\file CustomFileHandler.cpp
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

#include "CustomFileHandler.h"
#include "../ErrorHandling/MessageBox.h"
#include <fstream>

namespace File
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Writes to file

	\param fileHeader that contains:
		the image width
		the image height
		the internal format of the file
		the file data size
	\param fileData
	the file data
	\param fileName
	the file name
	*/
	/******************************************************************************/
	void CustomFileHandler::WriteFile( file_header & fileHeader, unsigned char * fileData, const char * fileName ) const
	{
		std::ofstream outfile;

		//allow output operations on the stream
		//consider stream as binary rather than text
		outfile.open( fileName, std::ofstream::out | std::ofstream::binary );

		if ( outfile.is_open() )
		{
			// write to outfile
			outfile.write( reinterpret_cast< char* >( & fileHeader ), sizeof( file_header ) ); //file header
			outfile.write( reinterpret_cast< char* >( fileData ), fileHeader.m_fileDataSize ); //the image data	

			outfile.close();
		}

		/*
		std::FILE *stream;

		// open the file
		if ( ( stream = std::fopen( fileName, "w+t" ) ) != NULL )
		{
			int numwritten = 0;
			long offset = 0;

			int headerSize = sizeof( file_header );
			//write the file header
			numwritten = std::fwrite( &fileHeader, headerSize, 1, stream );
			offset = std::ftell( stream ); 
			//write the data
			numwritten = std::fwrite( fileData, fileHeader.m_fileDataSize, 1, stream );
			offset = std::ftell( stream );

			std::fclose( stream );
		}
		*/
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Opens a file for reading

	\param fileName
	the name of the file to open
	\return bool
	true if successful, otherwise false
	*/
	/******************************************************************************/
	bool CustomFileHandler::ReadFile( const char * fileName )
	{
		bool readFlag = false;

		//Open the file
		std::ifstream infile;
		//allow input operations on the stream
		//consider stream as binary rather than text
		infile.open( fileName, std::ios::in | std::ios::binary );	

		//check if the file is open
		if ( !infile.is_open() )
		{
			//ASSERT ( !infile.is_open(), "The file cannot be opened." );
			return readFlag;
		}
		else
		{
			// read file header
			infile.read( ( char* ) &this->m_fileHeader , sizeof( struct file_header ) );	

			//validate for error in reading the file
			if ( infile.rdstate() == std::ios::eofbit )
			{
				ASSERT ( infile.rdstate() == std::ios::eofbit, 
					"End-Of-File reached while performing an extracting operation on an input stream." );
				return readFlag;
			}
			else if ( infile.rdstate() == std::ios::failbit )
			{
				ASSERT ( infile.rdstate() == std::ios::failbit, 
					"The last input operation failed because of an error related to the internal logic of the operation itself." );
				return readFlag;
			}
			else if ( infile.rdstate() == std::ios::badbit )
			{
				ASSERT ( infile.rdstate() == std::ios::badbit, 
					"Error due to the failure of an input/output operation on the stream buffer." );
				return readFlag;
			}
			
			//validate if the data in the file is valid
			if( ( this->m_fileHeader.m_width > 0 ) && ( this->m_fileHeader.m_height > 0 ) )
			{
				// Reserve space in the memory to store our image data
				//this->m_fileDataPtr = ( char* )malloc( this->m_fileHeader.m_fileDataSize );	
				this->m_fileDataPtr = new char[ this->m_fileHeader.m_fileDataSize ];
				// Read image data from file, into the reserved memory place
				infile.read( (char*) this->m_fileDataPtr, this->m_fileHeader.m_fileDataSize );
				infile.close();

				readFlag = true;
			}
			
		}

		return readFlag;
	}


	/******************************************************************************/
	/*!
	Release the pointer to the file data
	\param
	\return
	*/
	/******************************************************************************/
	void CustomFileHandler::Release()
	{
		// Free file data from memory
		free( this->m_fileDataPtr );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the image width

	\return unsigned short
	the image width
	*/
	/******************************************************************************/
	const unsigned short CustomFileHandler::GetImageWidth( void ) const
	{
		return this->m_fileHeader.m_width;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the image height

	\return unsigned short
	the image height
	*/
	/******************************************************************************/
	const unsigned short CustomFileHandler::GetImageHeight( void ) const
	{
		return this->m_fileHeader.m_height;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the file internal format

	\return int
	the file internal format
	*/
	/******************************************************************************/
	const int CustomFileHandler::GetInternalFormat( void ) const
	{
		return this->m_fileHeader.m_internalFormat;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the file data size

	\return int
	the file size
	*/
	/******************************************************************************/
	const int CustomFileHandler::GetFileDataSize( void ) const
	{
		return this->m_fileHeader.m_fileDataSize;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Get the file data

	\return char*
	the pointer to the file data
	*/
	/******************************************************************************/
	char * CustomFileHandler::GetFileData( void ) const
	{
		return this->m_fileDataPtr;
	}

}//using namespace file