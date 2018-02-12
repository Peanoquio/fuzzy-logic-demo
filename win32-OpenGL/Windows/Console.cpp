/******************************************************************************/
/*!
\file Console.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 05/03/2012
\brief
This is the console application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "Console.h"
#include <Windows.h>

namespace Console
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is the constructor of the Console class
	\param
	\return
	*/
	/******************************************************************************/
	Console::Console( void )
		: m_isConsoleAllocated( 0 ),
		m_cout( 0 ),
		m_cerr( 0 )
	{
		//allocate the console
		this->m_isConsoleAllocated = AllocConsole();		

		if ( this->m_isConsoleAllocated != 0 )
		{
			//attach the console
			AttachConsole( GetCurrentProcessId() ) ;

			freopen_s( &this->m_cout, "CONOUT$", "w", stdout );
			freopen_s( &this->m_cerr, "CONOUT$", "w", stderr );
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is the destructor of the Console class
	\param
	\return
	*/
	/******************************************************************************/
	Console::~Console( void )
	{
		if ( this->m_isConsoleAllocated != 0 )
		{
			this->m_isConsoleAllocated = 0;

			//close the handles
			fclose( this->m_cout );
			fclose( this->m_cerr );

			//free the console
			FreeConsole();
		}
	}

};