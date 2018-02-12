/******************************************************************************/
/*!
\file ImageObj.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 12/02/2012
\brief
This is the image object that will contain the image related data

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef IMGOBJ_H
#define IMGOBJ_H
////////////////////////////////////////////////////////////////////////////////


namespace GraphicsFramework
{
	class ImageObj
	{
	public:
		ImageObj( void );
		~ImageObj( void );

		char * GetImageData( void ) const;
		void SetImageData( char * imageDataPtr );
		void InstantiateImageData( const unsigned int imageSize );
		void DeleteImageData( void );

		const unsigned char GetImageTypeCode( void ) const;
		const unsigned char GetImageBpp( void ) const;
		const unsigned short GetImageWidth( void ) const;
		const unsigned short GetImageHeight( void ) const;
		const unsigned int GetImageSize( void ) const;
		const int GetInternalFormat( void ) const;

		void SetImageTypeCode( const unsigned char imageTypeCode );
		void SetImageBpp( const unsigned char imageBpp );
		void SetImageWidth( const unsigned short imageWidth );
		void SetImageHeight( const unsigned short imageHeight );
		void SetImageSize( const unsigned int imageSize );
		void SetInternalFormat( const int internalFormat );

	private:
		//texture image data members
		char *			m_imageDataPtr;
		unsigned char	m_imageTypeCode;
		unsigned char	m_imageBpp;
		unsigned short	m_imageWidth;
		unsigned short	m_imageHeight;		
		unsigned int	m_imageSize;
		int				m_internalFormat;	
	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////