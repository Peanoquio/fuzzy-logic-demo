/******************************************************************************/
/*!
\file MessageBox.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This is the custom error message for error handling

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
////////////////////////////////////////////////////////////////////////////////


namespace Error
{

	bool Assert ( bool expression, const char * outputMessage, const char * functionName, const char * fileName, unsigned lineNumber );

} //end namespace Error


#if defined(WIN32) & defined(_DEBUG)
#include <windows.h>
#define ASSERT(expression, outputMessage) if(Error::Assert(expression, outputMessage, __FUNCTION__, __FILE__, __LINE__)) {DebugBreak();}
#else
#define ASSERT(expression, outputMessage)
#endif


#endif
////////////////////////////////////////////////////////////////////////////////