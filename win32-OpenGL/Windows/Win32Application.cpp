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

#include "Win32Application.h"
#include "../Game/GameState.h"
#include "../Math/Mtx44.h"
#include <cstring> //memset

//#include "../MyGeometryGM.h"


//unnamed namespace create functions which can only be accessed in this file
//similar to static functions
namespace //unnamed
{
	// Constants
	const LPCTSTR LP_WINDOW_NAME = TEXT( "Window to the World" );
	const LPCTSTR LP_CLASS_NAME = TEXT( "Window_ClassName" );
	const LPCTSTR LP_CREATE_WINDOW_ERROR = TEXT( "Cannot create window" );
	const DWORD STYLE = WS_POPUP | WS_SYSMENU | WS_CAPTION;	//WS_OVERLAPPEDWINDOW;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Adjust and centers the window
	\param style
	The window style of the window whose required size is to be calculated. Note that you cannot specify the WS_OVERLAPPED style.
	\param size
	A RECT structure that contains the coordinates of the top-left and bottom-right corners of the desired client area. 
	When the function returns, the structure contains the coordinates of the top-left and bottom-right corners of the window to accommodate the desired client area.
	\param startX
	the starting x value of the window
	\param startY
	the starting y value of the window
	\return
	*/
	/******************************************************************************/
	void AdjustAndCenterWindow( DWORD style, RECT & size, int & startX, int & startY )
	{
		//Adjust the client window
		//Calculates the required size of the window rectangle, based on the desired client-rectangle size. 
		//The window rectangle can then be passed to the CreateWindow function to create a window whose client area is the desired size.
		AdjustWindowRect( &size, style, 0 );

		//The DEVMODE data structure contains information about the initialization and environment of a printer or a display device.
		DEVMODE dm = { 0 };
		dm.dmSize = sizeof( dm );
		//The EnumDisplaySettings function retrieves information about one of the graphics modes for a display device.
		//ENUM_CURRENT_SETTINGS - Retrieve the current settings for the display device.
		EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &dm );

		//compute for the window width and height
		int winWidth = size.right - size.left;
		int winHeight = size.bottom - size.top;

		//compute for the starting x and y values of the window
		startX = ( dm.dmPelsWidth / 2 ) - ( winWidth / 2 );
		startY = ( dm.dmPelsHeight / 2 ) - ( winHeight / 2 );
	}
}


namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the Win32Application
	\param
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	Win32Application<ApplicationType>::Win32Application( void )
	//Win32Application::Win32Application( void )
		: m_width( 0 ), 
		m_height( 0 ), 
		m_hWnd( 0 ),
		m_winSize(),
		m_gameState( 0 ),
		m_timer(),
		m_console()
	{
		//writes 0 to the memory location of the window class based on its size
		memset( &this->m_windowClass, 0, sizeof( this->m_windowClass ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the Win32Application
	\param
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	Win32Application<ApplicationType>::~Win32Application( void )
	//Win32Application::~Win32Application( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Initialize the application
	\param hInstance
	is something called a "handle to an instance" or "handle to a module." 
	The operating system uses this value to identify the executable (EXE) when it is loaded in memory. 
	The instance handle is needed for certain Windows functions — for example, to load icons or bitmaps.
	\param nShowCmd
	is a flag that says whether the main application window will be minimized, maximized, or shown normally.
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	void Win32Application<ApplicationType>::Init( HINSTANCE hInstance, int nShowCmd )
	//void Win32Application::Init( HINSTANCE hInstance, int nShowCmd )
	{
		this->m_gameManager.Init();
		//this->InitWindow( hInstance, nShowCmd, 1024u, 768u, LP_WINDOW_NAME );
		this->InitWindow( hInstance, nShowCmd, 640u, 480u, LP_WINDOW_NAME );
		this->m_timer.SetMaxFrameRate( 120.0 );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the application through the custom game loop.
	There is also a separate window loop to handle windows messages.
	\param
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	void Win32Application<ApplicationType>::Update( void )
	//void Win32Application::Update( void )
	{
		//get initial game state
		this->m_gameState = this->m_gameManager.GetInitialState();

		//this->m_timer.StartFrame();
		float frameTime = 0.0F; 
		float startFrameTime = 0.0F; 

		//loop until the game is quit
		while( !this->m_gameManager.QuitRequested() )
		{
			//initilize state
			this->m_gameState->Init();

			//update state until there is a change
			while( !this->m_gameManager.ChangeStateRequested() )
			{
				//get start of frame
				this->m_timer.StartFrame();

				//update the frame, based on current state
				this->m_gameState->Update( startFrameTime, frameTime );
				//this->m_gameState->Update( 0.0F, 0.25F );

				//reset input for the next frame
				this->m_gameManager.m_input.Reset();

				//send OS message to windows
				this->CheckWindowsMessages();

				//get end of frame
				this->m_timer.EndFrame();

				frameTime = this->m_timer.GetFrameTime();
				startFrameTime = this->m_timer.GetFrameTimeStart();

			}//end while loop

			//shutdown current state before starting new one
			this->m_gameState->Shutdown();

			//switch to new state then continue
			this->m_gameState = this->m_gameManager.ChangeState();

		}//end while loop

		// Window's main loop
		if ( IsWindow( this->m_hWnd ) )
		{
			SendMessage( this->m_hWnd, WM_CLOSE, 0, 0);
			this->CheckWindowsMessages();
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Shuts down the application.
	\param
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	void Win32Application<ApplicationType>::Shutdown( void )
	//void Win32Application::Shutdown( void )
	{
		ShutdownWindow();
		this->m_gameManager.Shutdown();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Initializes the window
	\param hInstance
	is something called a "handle to an instance" or "handle to a module." 
	The operating system uses this value to identify the executable (EXE) when it is loaded in memory. 
	The instance handle is needed for certain Windows functions — for example, to load icons or bitmaps.
	\param nShowCmd
	is a flag that says whether the main application window will be minimized, maximized, or shown normally.
	\param width
	the width of the window
	\param height
	the height of the window
	\param windowTitle
	the window title
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	void Win32Application<ApplicationType>::InitWindow( HINSTANCE hInstance, int nShowCmd, unsigned width, unsigned height, const LPCTSTR windowTitle )
	//void Win32Application::InitWindow( HINSTANCE hInstance, int nShowCmd, unsigned width, unsigned height, const LPCTSTR windowTitle )
	{
		//store the window dimensions
		this->m_width = width;
		this->m_height = height;

		// Initialise window class
		//Contains the window class attributes that are registered by the RegisterClass function. 
		this->m_windowClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;		
		this->m_windowClass.cbClsExtra		= 0;
		this->m_windowClass.cbWndExtra		= 0;
		this->m_windowClass.hInstance		= hInstance;
		this->m_windowClass.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
		this->m_windowClass.hCursor			= LoadCursor( NULL, IDC_ARROW );		
		this->m_windowClass.lpszMenuName	= NULL;
		this->m_windowClass.lpszClassName	= LP_CLASS_NAME;
		this->m_windowClass.hbrBackground	= static_cast<HBRUSH>( GetStockObject( WHITE_BRUSH ) );
		//this->m_windowClass.hbrBackground	= NULL;
		this->m_windowClass.lpfnWndProc		= &Win32Application<ApplicationType>::WinProc;
		//this->m_windowClass.lpfnWndProc	= &Win32Application::WinProc;
		//this->m_windowClass.lpfnWndProc	= WndProc;

		// Register class name
		//Registers a window class for subsequent use in calls to the CreateWindow 
		RegisterClass( &this->m_windowClass );

		//setting up the window size
		RECT rect = { 0, 0, this->m_width, this->m_height };
		//get the client rectangle
		GetClientRect( this->m_hWnd, &rect );
		//compute the size of the window
		this->m_winSize.cx = rect.right - rect.left;
		this->m_winSize.cy = rect.bottom - rect.top;

		//initial starting x and y positions
		int startX = 0, startY = 0;

		//invoke the function to adjust and center the window
		AdjustAndCenterWindow( STYLE, rect, startX, startY );

		// Create window
		//Creates an overlapped, pop-up, or child window. It specifies the window class, 
		//window title, window style, and (optionally) the initial position and size of the window. 
		//The function also specifies the window's parent or owner, if any, and the window's menu.
		/*
		Type: HWND
		If the function succeeds, the return value is a handle to the new window.
		If the function fails, the return value is NULL. To get extended error information, call GetLastError. 
		This function typically fails for one of the following reasons: 
		-an invalid parameter value
		-the system class was registered by a different module
		-The WH_CBT hook is installed and returns a failure code
		-if one of the controls in the dialog template is not registered, or its window window procedure fails WM_CREATE or WM_NCCREATE 
		*/
		this->m_hWnd = CreateWindow(
			LP_CLASS_NAME,				//class name
			windowTitle,				//window title
			STYLE,						//window style WS_OVERLAPPEDWINDOW
			startX,						//starting X CW_USEDEFAULT
			startY,						//starting Y CW_USEDEFAULT
			this->m_winSize.cx,			//width of window CW_USEDEFAULT
			this->m_winSize.cy,			//height of window CW_USEDEFAULT
			NULL,						//parent window
			NULL,						//menu
			hInstance,					//hInstance
			this						//lparam for create window message
			);


		// If window cannot be created, display an error and exit
		if ( this->m_hWnd == NULL )
		{
			MessageBox ( NULL, LP_CREATE_WINDOW_ERROR, windowTitle, MB_OK );
			//return FALSE;
		}

		// Display window
		// Sets the specified window's show state
		ShowWindow( this->m_hWnd, nShowCmd );
		//ShowWindow( this->m_hWnd, SW_SHOWNORMAL );

		//This function updates the client area of the specified window by sending a WM_PAINT message to the window if the windows update region is not empty. 
		//UpdateWindow sends a WM_PAINT message directly to the window procedure of the specified window, bypassing the application queue. 
		//If the update region is empty, no message is sent.
		UpdateWindow( this->m_hWnd );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Shuts down the window
	\param
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	void Win32Application<ApplicationType>::ShutdownWindow( void )
	//void Win32Application::ShutdownWindow( void )
	{
		//unregister the window
		UnregisterClass( LP_CLASS_NAME, 0 );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Check for windows messages
	\param
	\return
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	void Win32Application<ApplicationType>::CheckWindowsMessages( void )
	//void Win32Application::CheckWindowsMessages( void )
	{
		MSG msg = { 0 };

		//Dispatches incoming sent messages, checks the thread message queue for a posted message, and retrieves the message (if any exist).
		/*
		Return value
		Type: BOOL
		If a message is available, the return value is nonzero.
		If no messages are available, the return value is zero. 
		*/
		while ( PeekMessage( &msg, this->m_hWnd, 0, 0, PM_REMOVE ) )
		{
			//Translates virtual-key messages into character messages. 
			//The character messages are posted to the calling thread's message queue, 
			//to be read the next time the thread calls the GetMessage or PeekMessage function.
			/*
			Return value
			Type: BOOL
			If the message is translated (that is, a character message is posted to the thread's message queue), the return value is nonzero.
			*/
			TranslateMessage( &msg );
			//Dispatches a message to a window procedure. It is typically used to dispatch a message retrieved by the GetMessage function
			/*
			Return value
			Type: LRESULT
			The return value specifies the value returned by the window procedure. 
			Although its meaning depends on the message being dispatched, the return value generally is ignored.
			*/
			DispatchMessage( &msg );
		}

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	\brief 
	An application-defined function that processes messages sent to a window. 
	The WNDPROC type defines a pointer to this callback function.
	WindowProc is a placeholder for the application-defined function name.

	\param [in] hWnd
		handle to this window
	\param [in] msg
		the system provided message
	\param [in] wParam
		Additional message information. The contents of this parameter depend on the value of the msg parameter.
	\param [in] lParam
		Additional message information. The contents of this parameter depend on the value of the msg parameter.

	\return
	LRESULT - The return value is the result of the message processing and depends on the message sent.
	*/
	/******************************************************************************/
	template<typename ApplicationType>
	LRESULT CALLBACK Win32Application<ApplicationType>::WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	//LRESULT CALLBACK Win32Application::WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		static Win32Application< ApplicationType >* app = 0;
		//static Win32Application* app = 0;

		RECT rect;
		float FOV = 70.0F;
		float aspectRatio = 0.0F;

		Math::Mtx44 projMatrix;
		projMatrix.SetToIdentity();

		Math::Mtx44 rotateMatrixAlongSideVec;
		Math::Mtx44 rotateMatrixAlongUpVec;
		Math::Vector4 revisedCameraViewDirectionVector;

		Math::Vector4 cameraPosition ( 0.0F, 0.0F, 4.0F, 1.0f );
		Math::Vector4 target ( 0.0F, 0.0F, 0.0F, 1.0f );
		Math::Vector4 upVector  ( 0.0F, 1.0F, 0.0F, 0.0f );

		static float vertical = 0.0F;
		static float horizontal = 0.0F;
		//const float speed = 0.05F;

		static float spin = 0.0F;
		static float spin2 = 0.0F;
		static float swing = 0.0F;

		if (spin > Math::REVOLUTION_DEGREES)
		{
			spin -= Math::REVOLUTION_DEGREES;
		}

		if (spin2 > Math::REVOLUTION_DEGREES)
		{
			spin2 -= Math::REVOLUTION_DEGREES;
		}

		if (swing > 30.0F)
		{
			swing = 30.0F;
		} 
		else if (swing < -40.0F)
		{
			swing = -40.0F;
		}


		switch( msg )
		{
		case WM_NCCREATE:
			{
				//CREATESTRUCT
				/*
				Defines the initialization parameters passed to the window procedure of an application. 
				These members are identical to the parameters of the CreateWindowEx function.
				*/
				//lpCreateParams
				//Type: LPVOID
				/*
				Contains additional data which may be used to create the window. 
				If the window is being created as a result of a call to the CreateWindow or CreateWindowEx function, this member contains the value of the lpParam parameter specified in the function call.
				If the window being created is a MDI client window, this member contains a pointer to a CLIENTCREATESTRUCT structure. 
				If the window being created is a MDI child window, this member contains a pointer to an MDICREATESTRUCT structure.
				If the window is being created from a dialog template, this member is the address of a SHORT value that specifies the size, in bytes, of the window creation data. 
				The value is immediately followed by the creation data. For more information, see the following Remarks section.
				*/
				CREATESTRUCT* createStruct = reinterpret_cast< CREATESTRUCT* >( lParam );
				app = reinterpret_cast< Win32Application< ApplicationType >* >( createStruct->lpCreateParams );
				//app = reinterpret_cast< Win32Application* >( createStruct->lpCreateParams );
				return TRUE;

				break;
			}
		case WM_CREATE:
			{
				//get the client rectangle
				GetClientRect( hWnd, &rect );

				//initialize the device and render context for the window
				app->m_gameManager.m_graphicsInterfacePtr->Init( hWnd, static_cast<float>( rect.right ), static_cast<float>( rect.bottom ) );				

				//set up the camera				
				app->m_gameManager.m_graphicsInterfacePtr->m_camera.SetCameraPosition ( cameraPosition );
				app->m_gameManager.m_graphicsInterfacePtr->m_camera.SetCameraTarget ( target );
				app->m_gameManager.m_graphicsInterfacePtr->m_camera.SetWorldUpVector ( upVector );

				//load the mesh objects
				app->m_gameManager.m_gameObjMgrPtr->LoadMeshObjects( app->m_gameManager.m_graphicsInterfacePtr );

				break;
			}
		case WM_SIZE:
			{
				if( wParam == SIZE_MINIMIZED)
					break;

				//update viewport
				//glViewport( 0, 0, app->m_winSize.cx, app->m_winSize.cy );	
				app->m_gameManager.m_graphicsInterfacePtr->SetViewPort( 0, 0, app->m_winSize.cx, app->m_winSize.cy );

				if ( app->m_winSize.cy == 0 )
					break;
				
				aspectRatio = static_cast<float>( app->m_winSize.cx ) / app->m_winSize.cy;

				//store the FOV and aspect ratio
				app->m_gameManager.m_graphicsInterfacePtr->SetAspectRatio( aspectRatio );
				app->m_gameManager.m_graphicsInterfacePtr->SetFieldOfView( FOV );

				//compute for the world dimension
				app->m_gameManager.m_graphicsInterfacePtr->ComputeWorldDimension( FOV, aspectRatio, cameraPosition.GetFloatZ() );
				//store the screen dimension
				app->m_gameManager.m_graphicsInterfacePtr->SetScreenWidth( static_cast<float>( app->m_winSize.cx ) );
				app->m_gameManager.m_graphicsInterfacePtr->SetScreenHeight( static_cast<float>( app->m_winSize.cy ) );

				//set the projection matrix
				app->m_gameManager.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::PROJECTION ) );
				//projMatrix.Ortho ( -2.75F * aspectRatio, 2.75F * aspectRatio, -2.75F, 3.0F, -100.0F, 100.0F );
				projMatrix.Perspective ( FOV, aspectRatio, 0.1F, 200.0F );
				//load the matrix to the matrix stack
				app->m_gameManager.m_graphicsInterfacePtr->m_matrixStack.LoadMatrix( projMatrix );

				break;
			}
		case WM_DESTROY:
			{
				//Indicates to the system that a thread has made a request to terminate (quit). 
				//It is typically used in response to a WM_DESTROY message.
				PostQuitMessage( EXIT_SUCCESS );

				//quit the game manager
				app->m_gameManager.SetQuit( true );

				break;
			}
		case WM_CLOSE:
			{
				//shut down the graphics interface
				app->m_gameManager.m_graphicsInterfacePtr->Shutdown();

				//destroy the window
				DestroyWindow( hWnd );
				break;
			}

		case WM_CHAR:
			{
				switch( toupper( wParam ) )
				{
				case 0x1b: //ESC
					{
						//Places (posts) a (close) message in the message queue associated with the thread that created the specified window 
						//and returns without waiting for the thread to process the message.
						PostMessage( hWnd, WM_CLOSE, 0, 0 );
						break;
					}	
				case '1': //toggle object to move
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'L': //toggle lighting effect
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'K': //toggle render effect
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'J': //toggle vertex/fragment effect
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'U': //toggle lighting attenuation
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'O': //toggle projective texture
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
					/*
				case 'E': //toggle tile animation
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
					*/
				case 'T': //toggle anisotropic filtering
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'F': //toggle the minification texture filter mode
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'G': //toggle the magnification texture filter mode
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'P': //toggle the projection mode
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'N': //toggle the display of the wall normal
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}	
				case 'V': //set the polygon mode
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}				
				case 'C': //set culling
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
								
				case 'W': //move light forward
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
				case 'S': //move light backward
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
				case 'A': //move light to the left
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
				case 'D': //move light to the right
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'Q': //move light upwards
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'E': //move light downwards
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case 'Z': //reset light position
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}

				case 'R': //reset camera position
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}	
				case VK_UP: //move camera forward
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
				case VK_DOWN: //move camera backward
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
				case VK_LEFT: //move camera left
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}					
				case VK_RIGHT: //move camera right
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case VK_PRIOR: //move camera up
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				case VK_NEXT: //move camera down
					{
						app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
						break;
					}
				}//end switch
			}
			break;

		case VK_RETURN:
			{
				app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
				break;
			}
		case VK_SPACE:
			{
				app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
				break;
			}
		case WM_KEYDOWN:
			{
				app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), true );
				break;
			}
		case WM_KEYUP:
			{
				app->m_gameManager.m_input.SetPressed( GameFramework::GetKey( wParam ), false );
				break;
			}
		case WM_LBUTTONDOWN:
			{
				app->m_gameManager.m_input.SetPressed( InputMap::MOUSE_LEFT, true );
				break;
			}
		case WM_LBUTTONUP:
			{
				app->m_gameManager.m_input.SetPressed( InputMap::MOUSE_LEFT, false );
				break;
			}
		case WM_RBUTTONDOWN:
			{
				app->m_gameManager.m_input.SetPressed( InputMap::MOUSE_RIGHT, true );
				break;
			}
		case WM_RBUTTONUP:
			{
				app->m_gameManager.m_input.SetPressed( InputMap::MOUSE_RIGHT, false );
				break;
			}
		case WM_MOUSEMOVE:
			{
				app->m_gameManager.m_input.SetMouseX( LOWORD( lParam ) );
				app->m_gameManager.m_input.SetMouseY( HIWORD( lParam) );
				break;
			}
		default:
			{
				//Calls the default window procedure to provide default processing for any window messages that an application does not process. 
				//This function ensures that every message is processed. DefWindowProc is called with the same parameters received by the window procedure.
				return DefWindowProc( hWnd, msg, wParam, lParam );
				break;
			}
		}

		return 0;
	}

}// namespace Windows