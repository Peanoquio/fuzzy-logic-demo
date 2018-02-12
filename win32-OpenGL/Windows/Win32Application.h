/******************************************************************************/
/*!
\file Win32Application.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 21/12/2011
\brief
This is the interface for a Win32 Application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32_APPLICATION_H
#define WIN32_APPLICATION_H
////////////////////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "../FrameRate/FrameRateController.h"
#include "Console.h"


//#include "../MyGeometryGM.h"


namespace GameFramework
{
	//Forward declare GameState
	class GameState;

	template<typename ApplicationType>
	class Win32Application: public ApplicationType
	//class Win32Application
	{
	public:
		Win32Application( void );
		~Win32Application( void );

		//void Init( void );
		void Init( HINSTANCE hInstance, int nShowCmd );
		void Update( void );
		void Shutdown( void );

		static LRESULT CALLBACK WinProc( HWND win, UINT msg, WPARAM wp, LPARAM lp );

	private:
		void InitWindow( HINSTANCE hInstance, int nShowCmd, unsigned width, unsigned height, const LPCTSTR windowTitle );
		void ShutdownWindow( void );
		void CheckWindowsMessages( void );

		unsigned							m_width;
		unsigned							m_height;
		WNDCLASS							m_windowClass;
		HWND								m_hWnd;
		SIZE								m_winSize;
		GameState*							m_gameState;		
		FrameRate::FrameRateController		m_timer;
		Console::Console					m_console;

		//MyGeometryGame::MyGeometryGM		m_gameManager;
	};
}

#include "Win32Application.cpp"

#endif
////////////////////////////////////////////////////////////////////////////////