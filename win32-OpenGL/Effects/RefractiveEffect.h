/******************************************************************************/
/*!
\file RefractiveEffect.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 18/02/2012
\brief
This is the refractive effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef REFRACTIVE_EFFECT_H
#define REFRACTIVE_EFFECT_H
////////////////////////////////////////////////////////////////////////////////

#include "Effects.h"

namespace GraphicsFramework
{
	class RefractiveEffect : public Effects
	{
	public:
		virtual void Init( const CGcontext cgContext );
		void Init( const CGcontext cgContext, const bool vtxComputationFlag );

	private:

	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////