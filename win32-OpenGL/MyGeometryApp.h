/******************************************************************************/
/*!
\file MyGeometryApp.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 25/12/2011
\brief
This is the geometry game application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef MYGEOMETRY_APP_H
#define MYGEOMETRY_APP_H
////////////////////////////////////////////////////////////////////////////////

#include "MyGeometryGM.h"

namespace MyGeometryGame
{
	class MyGeometryApp
	{
	public:
		MyGeometryApp( void );
		~MyGeometryApp( void );

	protected:
		MyGeometryGM m_gameManager;
	};

}//end namespace MyGeometryGame

#endif
////////////////////////////////////////////////////////////////////////////////