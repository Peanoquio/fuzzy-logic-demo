/******************************************************************************/
/*!
\file Console.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef CONSOLE_H
#define CONSOLE_H
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>


namespace Console
{
	class Console
	{
	public:
		Console( void );
		~Console( void );

	private:
		int 	m_isConsoleAllocated;
		FILE *	m_cout;
		FILE *	m_cerr;
	};

}//end namespace Console


#endif
////////////////////////////////////////////////////////////////////////////////