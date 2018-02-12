/******************************************************************************/
/*!
\file MessageBox.cpp
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

#include "MessageBox.h"

#if defined(WIN32) & defined(_DEBUG)
#include <windows.h>
#include <string>
#include <sstream>

namespace Error
{

	/******************************************************************************/
	/*! 
	\brief 
	This shows a custom error message window

	\param expression
	the expression to be evaluated
	false is the expression is not satisfied, otherwise true
	\param outputMessage
	the error message
	\param functionName
	the function name
	\param fileName
	the file name
	\param lineNumber
	the line number
	\return
	*/
	/******************************************************************************/
	bool Assert ( bool expression, const char * outputMessage, const char * functionName, const char * fileName, unsigned lineNumber )
	{
		//the expression for error handling
		if ( expression )
		{
			size_t i;
			const size_t BUFFER_SIZE = 500;				
			wchar_t * pwcoutputMessage = (wchar_t *) malloc ( sizeof( wchar_t ) );
			
			//set the custom message
			std::ostringstream message;
			message << "ASSERTION FAILURE: " << std::endl;
			message << "File: " << fileName << std::endl;
			message << "Line: " << lineNumber << std::endl;
			message << "Function: " << functionName << std::endl;
			message << std::endl << std::endl;

			message << "Description: " << outputMessage << std::endl << std::endl;
			message << "Do you want to Debug?" << std::endl;

			//convert from multi-byte string to wide character string
			mbstowcs_s( &i, pwcoutputMessage, (size_t)BUFFER_SIZE, message.str().c_str(), (size_t)BUFFER_SIZE );

			//show the message box
			int returnVal = MessageBox ( 
				NULL, 
				//(LPCWSTR)message.str().c_str(), 
				(LPCWSTR)pwcoutputMessage,
				(LPCWSTR)L"ASSERT!", 
				MB_TASKMODAL | MB_SETFOREGROUND | MB_YESNO | MB_ICONERROR
				);

			// Free wide character buffer
			/*
			if (pwcoutputMessage)
			{
				free(pwcoutputMessage);
			}
			*/

			//perform the action based on what the user selected
			switch ( returnVal )
			{
			case IDYES:
				return true;
				break;
			case IDNO:
				ExitProcess(static_cast<unsigned>(-1));
				break;
			default:
				ExitProcess(static_cast<unsigned>(-1));
				break;
			}

		}

		return false;
	}

} //end namespace Error

#endif