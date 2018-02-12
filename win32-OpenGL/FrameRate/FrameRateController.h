/******************************************************************************/
/*!
\file FrameRateController.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 25/12/2011
\brief
This regulates the frame rate of the game
This was researched through the sites:
http://advancedcppwithexamples.blogspot.com/2009/08/measuring-elapsed-time-in-c-using_21.html
http://gafferongames.com/game-physics/fix-your-timestep/
This was also referenced from the previous Advanced Certificate for Game Programmers class

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef FRAME_RATE_CONTROLLER_H
#define FRAME_RATE_CONTROLLER_H
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

namespace FrameRate
{
	class FrameRateController
	{
	public:
		FrameRateController( void );
		~FrameRateController( void );

		void StartFrame( void );
		void EndFrame( void );
		void Reset( void );
		void SetMaxFrameRate( double maxRate );
		float GetFrameTime( void ) const;
		float GetFrameTimeStart( void ) const;
		float GetFrameTimeEnd( void ) const;

	private:
		double		m_freq;		
		double		m_frameTimeStart;
		double		m_frameTimeEnd;
		double		m_frameTime;
		double		m_frameRateMax;
		double		m_frameTimeMin;

		double ComputeTime( void ) const;
	};

}//end namespace FrameRate

#endif
////////////////////////////////////////////////////////////////////////////////