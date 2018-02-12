/******************************************************************************/
/*!
\file Win32Input.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 25/12/2011
\brief
This will manage the user input.
This was reference from the Advanced Certificate class.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32_INPUT_H
#define WIN32_INPUT_H
////////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <bitset>
#include <windows.h>

namespace InputMap
{
	enum ID
	{
		INVALID,
		BACKSPACE,
		TAB,
		RETURN,
		SHIFT,
		CONTROL,
		ESCAPE,
		SPACE,
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		PAGE_UP,
		PAGE_DOWN,
		N_0,
		N_1,
		N_2,
		N_3,
		N_4,
		N_5,
		N_6,
		N_7,
		N_8,
		N_9,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		MOUSE_LEFT,
		MOUSE_RIGHT,
		LAST
	};

}//end namespace InputMap

namespace GameFramework
{
	InputMap::ID GetKey( WPARAM wp );

	class Input
	{
	public:
		void Reset( void );

		//To Check key status
		bool IsPressed( InputMap::ID key ) const;
		bool IsTriggered( InputMap::ID key ) const;
		bool IsRepeating( InputMap::ID key ) const;

		bool IsAnyPressed( void ) const;
		bool IsAnyTriggered( void ) const;

		void SetPressed( InputMap::ID key, bool status );

		//Mouse controls
		int GetMouseX( void ) const;
		int GetMouseY( void ) const;

		int GetMouseDX( void ) const;
		int GetMouseDY( void ) const;

		void SetMouseX( int x );
		void SetMouseY( int y );

	private:
		typedef std::stack< InputMap::ID > IDStack;

		IDStack m_unpress;
		//A bitset is a special container class that is designed to store bits (elements with only two possible values: 0 or 1, true or false, ...)
		std::bitset< InputMap::LAST > m_pressed;
		std::bitset< InputMap::LAST > m_triggered;
		std::bitset< InputMap::LAST > m_repeating;

		int m_mouseX;
		int m_mouseY;
		int m_mouseDX;
		int m_mouseDY;
	};

}//end namespace GameFramework

#endif
////////////////////////////////////////////////////////////////////////////////
