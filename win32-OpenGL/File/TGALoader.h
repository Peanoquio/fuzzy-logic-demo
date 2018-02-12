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

All Targa formats are identified by a Data Type field, which is a one byte binary integer located in byte three of the file. These data types are:

0  -  No image data included.
1  -  Uncompressed, color-mapped images.
2  -  Uncompressed, RGB images.
3  -  Uncompressed, black and white images.
9  -  Runlength encoded color-mapped images.
10  -  Runlength encoded RGB images.
11  -  Compressed, black and white images.
32  -  Compressed color-mapped data, using Huffman, Delta, and
runlength encoding.
33  -  Compressed color-mapped data, using Huffman, Delta, and
runlength encoding.  4-pass quadtree-type process.

DATA TYPE 2: Unmapped RGB
________________________________________________________________________________
| Offset | Length |                     Description                            |
|--------|--------|------------------------------------------------------------|
|    0   |     1  |  Number of Characters in Identification Field.             |
|        |        |                                                            |
|        |        |  This field is a one-byte unsigned integer, specifying     |
|        |        |  the length of the Image Identification Field.  Its value  |
|        |        |  is 0 to 255.  A value of 0 means that no Image            |
|        |        |  Identification Field is included.                         |
|--------|--------|------------------------------------------------------------|
|    1   |     1  |  Color Map Type.                                           |
|        |        |                                                            |
|        |        |  This field contains either 0 or 1.  0 means no color map  |
|        |        |  is included.  1 means a color map is included, but since  |
|        |        |  this is an unmapped image it is usually ignored.  TIPS    |
|        |        |  ( a Targa paint system ) will set the border color        |
|        |        |  the first map color if it is present.                     |
|--------|--------|------------------------------------------------------------|
|    2   |     1  |  Image Type Code.                                          |
|        |        |                                                            |
|        |        |  This field will always contain a binary 2.                |
|        |        |  ( That's what makes it Data Type 2 ).                     |
|--------|--------|------------------------------------------------------------|
|    3   |     5  |  Color Map Specification.                                  |
|        |        |                                                            |
|        |        |  Ignored if Color Map Type is 0; otherwise, interpreted    |
|        |        |  as follows:                                               |
|    3   |     2  |  Color Map Origin.                                         |
|        |        |  Integer ( lo-hi ) index of first color map entry.         |
|    5   |     2  |  Color Map Length.                                         |
|        |        |  Integer ( lo-hi ) count of color map entries.             |
|    7   |     1  |  Color Map Entry Size.                                     |
|        |        |  Number of bits in color map entry.  16 for the Targa 16,  |
|        |        |  24 for the Targa 24, 32 for the Targa 32.                 |
|--------|--------|------------------------------------------------------------|
|    8   |    10  |  Image Specification.                                      |
|        |        |                                                            |
|    8   |     2  |  X Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) X coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|   10   |     2  |  Y Origin of Image.                                        |
|        |        |  Integer ( lo-hi ) Y coordinate of the lower left corner   |
|        |        |  of the image.                                             |
|   12   |     2  |  Width of Image.                                           |
|        |        |  Integer ( lo-hi ) width of the image in pixels.           |
|   14   |     2  |  Height of Image.                                          |
|        |        |  Integer ( lo-hi ) height of the image in pixels.          |
|   16   |     1  |  Image Pixel Size.                                         |
|        |        |  Number of bits in a pixel.  This is 16 for Targa 16,      |
|        |        |  24 for Targa 24, and .... well, you get the idea.         |
|   17   |     1  |  Image Descriptor Byte.                                    |
|        |        |  Bits 3-0 - number of attribute bits associated with each  |
|        |        |             pixel.  For the Targa 16, this would be 0 or   |
|        |        |             1.  For the Targa 24, it should be 0.  For     |
|        |        |             Targa 32, it should be 8.                      |
|        |        |  Bit 4    - reserved.  Must be set to 0.                   |
|        |        |  Bit 5    - screen origin bit.                             |
|        |        |             0 = Origin in lower left-hand corner.          |
|        |        |             1 = Origin in upper left-hand corner.          |
|        |        |             Must be 0 for Truevision images.               |
|        |        |  Bits 7-6 - Data storage interleaving flag.                |
|        |        |             00 = non-interleaved.                          |
|        |        |             01 = two-way (even/odd) interleaving.          |
|        |        |             10 = four way interleaving.                    |
|        |        |             11 = reserved.                                 |
|--------|--------|------------------------------------------------------------|
|   18   | varies |  Image Identification Field.                               |
|        |        |                                                            |
|        |        |  Contains a free-form identification field of the length   |
|        |        |  specified in byte 1 of the image record.  It's usually    |
|        |        |  omitted ( length in byte 1 = 0 ), but can be up to 255    |
|        |        |  characters.  If more identification information is        |
|        |        |  required, it can be stored after the image data.          |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Color map data.                                           |
|        |        |                                                            |
|        |        |  If the Color Map Type is 0, this field doesn't exist.     |
|        |        |  Otherwise, just read past it to get to the image.         |
|        |        |  The Color Map Specification describes the size of each    |
|        |        |  entry, and the number of entries you'll have to skip.     |
|        |        |  Each color map entry is 2, 3, or 4 bytes.                 |
|--------|--------|------------------------------------------------------------|
| varies | varies |  Image Data Field.                                         |
|        |        |                                                            |
|        |        |  This field specifies (width) x (height) pixels.  Each     |
|        |        |  pixel specifies an RGB color value, which is stored as    |
|        |        |  an integral number of bytes.                              |
|        |        |  The 2 byte entry is broken down as follows:               |
|        |        |  ARRRRRGG GGGBBBBB, where each letter represents a bit.    |
|        |        |  But, because of the lo-hi storage order, the first byte   |
|        |        |  coming from the file will actually be GGGBBBBB, and the   |
|        |        |  second will be ARRRRRGG. "A" represents an attribute bit. |
|        |        |  The 3 byte entry contains 1 byte each of blue, green,     |
|        |        |  and red.                                                  |
|        |        |  The 4 byte entry contains 1 byte each of blue, green,     |
|        |        |  red, and attribute.  For faster speed (because of the     |
|        |        |  hardware of the Targa board itself), Targa 24 images are  |
|        |        |  sometimes stored as Targa 32 images.                      |
--------------------------------------------------------------------------------

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef TGA_LOADER_H
#define TGA_LOADER_H
////////////////////////////////////////////////////////////////////////////////


namespace File
{
	class TGALoader
	{
	public:

		bool Load( const char * filename );
		void Release();
		void Draw();

		char * GetImageData( void ) const;
		const unsigned char GetImageTypeCode( void ) const;
		const unsigned char GetImageBpp( void ) const;
		const unsigned short GetImageWidth( void ) const;
		const unsigned short GetImageHeight( void ) const;

	private:

		void FlipColorBytes( void );

		char * m_imageDataPtr; 

		struct tga_header
		{
			unsigned char	m_idLength;			// size of ID field that follows 18 byte header (0 usually)
			unsigned char	m_colorMapType;		// type of colour map 0=none, 1=has palette
			unsigned char	m_imageTypeCode;	// type of image 0=none, 1=indexed, 2=rgb, 3=grey, +8=rle packed

			unsigned char	m_colorMapSpec[5];	
			//unsigned short	m_colorMapOrigin;	//Color Map Origin: Integer ( lo-hi ) index of first color map entry.
			//unsigned short	m_colorMapLength;	//Color Map Length: Integer ( lo-hi ) count of color map entries.  
			//unsigned char	m_colorMapDepth;	//Color Map Entry Size: 16 for the Targa 16, 24 for the Targa 24, 32 for the Targa 32  

			unsigned short	m_xOrigin;			// image x origin
			unsigned short	m_yOrigin;			// image y origin
			unsigned short	m_width;			// image width in pixels
			unsigned short	m_height;			// image height in pixels
			unsigned char	m_bpp;				// image bits per pixel 8,16,24,32
			unsigned char	m_imageDesc;		// image descriptor bits (vh flip bits)
		};

		tga_header m_tgaHeader;
	};

}//using namespace file

#endif
////////////////////////////////////////////////////////////////////////////////