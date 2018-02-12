/******************************************************************************/
/*!
\file FresnelEffect.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1050
\par Project #03
\date 19/02/2012
\brief
This is the Fresnel effect

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef FRESNEL_EFFECT_H
#define FRESNEL_EFFECT_H
////////////////////////////////////////////////////////////////////////////////

#include "Effects.h"

namespace GraphicsFramework
{
	class FresnelEffect : public Effects
	{
	public:
		virtual void Init( const CGcontext cgContext );
		void Init( const CGcontext cgContext, const bool vtxComputationFlag );

	private:

	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////