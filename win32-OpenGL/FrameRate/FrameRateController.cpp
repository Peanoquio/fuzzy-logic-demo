/******************************************************************************/
/*!
\file FrameRateController.cpp
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

#include "FrameRateController.h"

namespace FrameRate
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The constructor of the FrameRateController class

	\param
	\return
	*/
	/******************************************************************************/
	FrameRateController::FrameRateController( void )
	{
		//Retrieves the frequency of the high-resolution performance counter, if one exists. The frequency cannot change while the system is running.
		/*
		Parameters:
		Type: LARGE_INTEGER*
		A pointer to a variable that receives the current performance-counter frequency, in counts per second. 
		If the installed hardware does not support a high-resolution performance counter, this parameter can be zero.
		Return Value:
		Type: BOOL
		If the installed hardware supports a high-resolution performance counter, the return value is nonzero.
		If the function fails, the return value is zero. To get extended error information, call GetLastError. 
		For example, if the installed hardware does not support a high-resolution performance counter, the function fails.
		*/
		QueryPerformanceFrequency( (LARGE_INTEGER*) &this->m_freq );

		//reset the frame time and frame rate values
		this->Reset();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	The destructor of the FrameRateController class

	\param
	\return
	*/
	/******************************************************************************/
	FrameRateController::~FrameRateController( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Compute for the time based on the counter from the CPU cycle

	\param
	\return
	*/
	/******************************************************************************/
	double FrameRateController::ComputeTime( void ) const
	{
		double counter = 0.0;

		//Retrieves the current value of the high-resolution performance counter.
		/*
		Parameters:
		Type: LARGE_INTEGER*
		A pointer to a variable that receives the current performance-counter value, in counts.
		Return Value:
		Type: BOOL
		If the function succeeds, the return value is nonzero.
		If the function fails, the return value is zero. To get extended error information, call GetLastError.
		*/
		QueryPerformanceCounter( (LARGE_INTEGER*) &counter );

		//return the time based on the counter and frequency
		return ( counter / ( this->m_freq ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Start the frame

	\param
	\return
	*/
	/******************************************************************************/
	void FrameRateController::StartFrame( void )
	{		
		//get the time
		this->m_frameTimeStart = this->ComputeTime();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	End the frame
	This also computes the elapsed frame time based on the starting and ending frame times

	\param
	\return
	*/
	/******************************************************************************/
	void FrameRateController::EndFrame( void )
	{
		//get the time
		this->m_frameTimeEnd = this->ComputeTime();
		//get the time difference between the start and end of the frame
		double diff = this->m_frameTimeEnd - this->m_frameTimeStart;

		//lock the frame rate
		while ( diff < this->m_frameTimeMin )
		{
			//get the time
			this->m_frameTimeEnd = this->ComputeTime();
			//get the time difference between the start and end of the frame
			diff = this->m_frameTimeEnd - this->m_frameTimeStart;
		}

		//set the elapsed frame time
		this->m_frameTime = diff;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Reset the frame time and frame rate values

	\param
	\return
	*/
	/******************************************************************************/
	void FrameRateController::Reset(void)
	{
		this->m_frameTime = 0;
		this->m_frameRateMax = 0;
		this->m_frameTimeMin = 0;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Sets the maximum frame rate

	\param
	\return
	*/
	/******************************************************************************/
	void FrameRateController::SetMaxFrameRate( double maxRate )
	{
		this->m_frameRateMax = maxRate;
		this->m_frameTimeMin = 1.0 / this->m_frameRateMax;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the frame time

	\param
	\return float
	the frame time
	*/
	/******************************************************************************/
	float FrameRateController::GetFrameTime( void ) const
	{
		return static_cast<float>( this->m_frameTime );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the starting frame time

	\param
	\return float
	the starting frame time
	*/
	/******************************************************************************/
	float FrameRateController::GetFrameTimeStart( void ) const
	{
		return static_cast<float>( this->m_frameTimeStart );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Gets the ending frame time

	\param
	\return float
	the ending frame time
	*/
	/******************************************************************************/
	float FrameRateController::GetFrameTimeEnd( void ) const
	{
		return static_cast<float>( this->m_frameTimeEnd );
	}

}//end namespace FrameRate

