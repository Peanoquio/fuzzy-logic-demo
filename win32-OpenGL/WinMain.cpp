/******************************************************************************/
/*!
\file WinMain.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This is the main function of the game application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//CHECK FOR MEMORY LEAKS
//Place this at the very top of the cpp file that contains main
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "Windows\Win32Application.h"
#include "MyGeometryApp.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nShowCmd)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//CHECK FOR MEMORY LEAKS
	//Place this at the very top of the main function
	#ifdef _DEBUG 
		//This sets the program to call _CrtDumpMemoryLeaks on program exit
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		//Set where to report the leaks
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);

		//if we have memory leaks, we can put the number from the curly
		//braces inside this function to break on alloc.  Otherwise use -1.
		_CrtSetBreakAlloc(-1);
	#endif
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	GameFramework::Win32Application< MyGeometryGame::MyGeometryApp > game;
	//GameFramework::Win32Application game;

	game.Init( hInstance, nShowCmd );
	game.Update();
	game.Shutdown();

	return 0;
}