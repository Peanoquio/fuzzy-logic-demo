/******************************************************************************/
/*!
\file Utility.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This contains utility functions that can be used throughout the application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "Utility.h"
#include <ctime>

namespace Utility
{
	/******************************************************************************/
	/*!
	Generates a random number
	\param upperLimitValue
	the upper limit value to limit the random number value generated
	\return unsigned
	the random number value
	*/
	/******************************************************************************/
	unsigned GenerateRandomNumber( const unsigned upperLimitValue )
	{
		//set the seed value
		std::srand( static_cast<unsigned>( time( NULL ) ) );
		//generate random number based on the upper limit
		unsigned randomVal = std::rand() % upperLimitValue;
		return randomVal;
	}


	/******************************************************************************/
	/*!
	Validates whether the extension being passed is supported by the graphics API.
	This code was taken from http://www.opengl.org/resources/features/OGLextensions/
	\param extension
	the extension to be verified
	\return int
	0 - extension is not supported, 1 - extension is supported
	*/
	/******************************************************************************/
	int isExtensionSupported(const char * extension)
	{
		const GLubyte *extensions = NULL;
		const GLubyte *start;
		GLubyte *where, *terminator;

		/* Extension names should not have spaces. */
		where = (GLubyte *) strchr(extension, ' ');
		if (where || *extension == '\0')
			return 0;

		extensions = glGetString(GL_EXTENSIONS);

		/* It takes a bit of care to be fool-proof about parsing the
		OpenGL extensions string. Don't be fooled by sub-strings,
		etc. */
		start = extensions;

		for (;;) 
		{
			where = (GLubyte *) strstr((const char *) start, extension);

			if (!where)
				break;

			terminator = where + strlen(extension);

			if (where == start || *(where - 1) == ' ')
				if (*terminator == ' ' || *terminator == '\0')
					return 1;

			start = terminator;
		}

		return 0;
	}

} //end namespace Utility