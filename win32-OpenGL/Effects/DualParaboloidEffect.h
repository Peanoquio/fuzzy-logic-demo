/******************************************************************************/
/*!
\file DualParaboloidEffect.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 22/02/2012
\brief
This is the dual paraboloid effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef DUAL_PARABOLOID_EFFECT_H
#define DUAL_PARABOLOID_EFFECT_H
////////////////////////////////////////////////////////////////////////////////

#include "Effects.h"

namespace GraphicsFramework
{
	class DualParaboloidEffect : public Effects
	{
	public:
		virtual void Init( const CGcontext cgContext );

	private:

	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////