/******************************************************************************/
/*!
\file Win32Input.cpp
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

#include "Win32Input.h"

namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Resets all the values
	\param
	\return
	*/
	/******************************************************************************/
	void Input::Reset( void )
	{
		//reset the mouse difference values
		this->m_mouseDX = this->m_mouseDY = 0;

		//resets all the bits in the bitset to 0
		this->m_triggered.reset();
		this->m_repeating.reset();

		//loop through the stack that contains the unpressed keys (on key up)
		while ( !this->m_unpress.empty() )
		{
			//reset the key pressed values as if they have never been pressed
			this->m_pressed[ this->m_unpress.top() ] = false;
			//pop that element from the stack
			this->m_unpress.pop();
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks if the key was pressed
	\param key
	the key that was pressed
	\return bool
	if true, the key was pressed, otherwise false
	*/
	/******************************************************************************/
	bool Input::IsPressed( InputMap::ID key ) const
	{
		//validate if the key entered is valid
		if ( ( key > InputMap::INVALID ) && ( key < InputMap::LAST ) )
		{
			return this->m_pressed[ key ];
		}

		return false;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks if the key was triggered
	\param key
	the key that was triggered
	\return bool
	if true, the key was triggered, otherwise false
	*/
	/******************************************************************************/
	bool Input::IsTriggered( InputMap::ID key ) const
	{
		//validate if the key entered is valid
		if ( ( key > InputMap::INVALID ) && ( key < InputMap::LAST ) )
		{
			return this->m_triggered[ key ];
		}

		return false;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks if the key is repeating
	\param key
	the key that is repeating
	\return bool
	if true, the key is repeating, otherwise false
	*/
	/******************************************************************************/
	bool Input::IsRepeating( InputMap::ID key ) const
	{
		//validate if the key entered is valid
		if( ( key > InputMap::INVALID ) && ( key < InputMap::LAST ) )
		{
			return this->m_repeating[ key ];
		}

		return false;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks if any of the key is pressed
	\param
	\return bool
	true if any of the key is pressed, and false otherwise
	*/
	/******************************************************************************/
	bool Input::IsAnyPressed( void ) const
	{
		//true if any of the bits in the bitset is set, and false otherwise
		return this->m_pressed.any();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Checks if any of the key is triggered
	\param
	\return bool
	true if any of the key is triggered, and false otherwise
	*/
	/******************************************************************************/
	bool Input::IsAnyTriggered( void ) const
	{
		//true if any of the bits in the bitset is set, and false otherwise
		return this->m_triggered.any();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the key that was entered
	\param key
	the key that was entered (order position of the bit)
	\param status
	the boolean value to determine if the key is pressed down or released
	\return
	*/
	/******************************************************************************/
	void Input::SetPressed( InputMap::ID key, bool status )
	{
		//check that the key pressed is valid
		if ( ( key > InputMap::INVALID ) && ( key < InputMap::LAST ) )
		{
			//check if key press down
			if ( status == true )
			{
				//check if the key is pressed the first time
				if ( this->m_pressed[key] == false )
				{
					this->m_pressed[key] = true;
					this->m_triggered[key] = true;
				}
				else
				{
					this->m_repeating[key] = true;
				}
			}
			else
			{
				this->m_unpress.push( key );
			}
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the mouse x position
	\param
	\return int
	the mouse x position
	*/
	/******************************************************************************/
	int Input::GetMouseX( void ) const
	{
		return this->m_mouseX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the mouse y position
	\param
	\return int
	the mouse y position
	*/
	/******************************************************************************/
	int Input::GetMouseY( void ) const
	{
		return this->m_mouseY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the difference in the mouse x position
	\param
	\return int
	difference in the mouse x position
	*/
	/******************************************************************************/
	int Input::GetMouseDX( void ) const
	{
		return this->m_mouseDX;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the difference in the mouse y position
	\param
	\return int
	difference in the mouse y position
	*/
	/******************************************************************************/
	int Input::GetMouseDY( void ) const
	{
		return this->m_mouseDY;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the mouse x position
	\param x
	the mouse x position
	\return
	*/
	/******************************************************************************/
	void Input::SetMouseX( int x )
	{
		this->m_mouseDX = x - this->m_mouseX;
		this->m_mouseX = x;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the mouse y position
	\param y
	the mouse y position
	\return
	*/
	/******************************************************************************/
	void Input::SetMouseY( int y )
	{
		this->m_mouseDY = y - this->m_mouseY;
		this->m_mouseY = y;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Catches the windows characer input and returns the corresponding key ID from the input map
	\param wp
	the windows WPARAM ( in this case, the windows characer input )
	\return InputMap::ID
	the key ID from the input map
	*/
	/******************************************************************************/
	InputMap::ID GetKey( WPARAM wp )
	{
		switch( wp )
		{
		case VK_RETURN:  return InputMap::RETURN;
		case VK_SPACE:   return InputMap::SPACE;
		case VK_UP:      return InputMap::ARROW_UP;
		case VK_DOWN:    return InputMap::ARROW_DOWN;
		case VK_LEFT:    return InputMap::ARROW_LEFT;
		case VK_RIGHT:   return InputMap::ARROW_RIGHT;
		case VK_TAB:     return InputMap::TAB;
		case VK_SHIFT:   return InputMap::SHIFT;
		case VK_CONTROL: return InputMap::CONTROL;
		case VK_ESCAPE:  return InputMap::ESCAPE;
		case VK_BACK:    return InputMap::BACKSPACE;
		case VK_PRIOR:	 return InputMap::PAGE_UP;
		case VK_NEXT:	 return InputMap::PAGE_DOWN;
		case 'A':        return InputMap::A;
		case 'B':        return InputMap::B;
		case 'C':        return InputMap::C;
		case 'D':        return InputMap::D;
		case 'E':        return InputMap::E;
		case 'F':        return InputMap::F;
		case 'G':        return InputMap::G;
		case 'H':        return InputMap::H;
		case 'I':        return InputMap::I;
		case 'J':        return InputMap::J;
		case 'K':        return InputMap::K;
		case 'L':        return InputMap::L;
		case 'M':        return InputMap::M;
		case 'N':        return InputMap::N;
		case 'O':        return InputMap::O;
		case 'P':        return InputMap::P;
		case 'Q':        return InputMap::Q;
		case 'R':        return InputMap::R;
		case 'S':        return InputMap::S;
		case 'T':        return InputMap::T;
		case 'U':        return InputMap::U;
		case 'V':        return InputMap::V;
		case 'W':        return InputMap::W;
		case 'X':        return InputMap::X;
		case 'Y':        return InputMap::Y;
		case 'Z':        return InputMap::Z;
		case '0':        return InputMap::N_0;
		case '1':        return InputMap::N_1;
		case '2':        return InputMap::N_2;
		case '3':        return InputMap::N_3;
		case '4':        return InputMap::N_4;
		case '5':        return InputMap::N_5;
		case '6':        return InputMap::N_6;
		case '7':        return InputMap::N_7;
		case '8':        return InputMap::N_8;
		case '9':        return InputMap::N_9;

		default:        return InputMap::INVALID;
		}//end switch
	}

}//end namespace GameFramework