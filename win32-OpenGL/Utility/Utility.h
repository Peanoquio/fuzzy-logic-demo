/******************************************************************************/
/*!
\file Utility.h
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


////////////////////////////////////////////////////////////////////////////////
#ifndef UTILITYOPENGL_H
#define UTILITYOPENGL_H
////////////////////////////////////////////////////////////////////////////////

#include <sstream> // std::wstringstream
#include <GL/glew.h>

namespace Utility
{
	template <typename T>
	void CopyArrayBasedOnOffset (const T * sourceArray, const unsigned srcArrSize, 
		T * destinationArray, const unsigned destArrSize, const unsigned offsetVal);

	int isExtensionSupported(const char *extension);

	unsigned GenerateRandomNumber( const unsigned upperLimitValue );

} //end namespace Utility

#include "Utility.inl"

#endif
////////////////////////////////////////////////////////////////////////////////