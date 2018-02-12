/******************************************************************************/
/*!
\file MyGeometryGM.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 24/12/2011
\brief
This is the geometry game manager

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "MyGeometryGM.h"
#include "MyGeometryOM.h"
#include "MyGeometryState.h"
//#include "Menu.h"

namespace MyGeometryGame
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the MyGeometryGM class
	\param
	\return
	*/
	/******************************************************************************/
	MyGeometryGM::MyGeometryGM( void )
		: m_graphicsInterfacePtr( 0 ),
		m_gameStatePtr( 0 ),
		m_gameObjMgrPtr( 0 ),
		m_input(),
		m_renderMgr(),
		m_showOrthoProj( false ),
		m_showWallNormal( false ),
		m_isBackFaceEnabled( true ),
		m_enableAnisotropicFiltering( true ),
		m_polygonMode( GL_FILL ),
		m_texMinFilterMode( GL_LINEAR ),
		m_texMagFilterMode( GL_LINEAR ),
		m_noOfTilesPerSide( 3 ),
		m_lighting( Light::POINT ),
		m_lightingEffect( GraphicsFramework::LIGHT_FRAG ),
		m_renderEffect( GraphicsFramework::FRESNEL_FRAG ),
		m_objectToMove( 0 ),
		m_showProjTex( false ),
		m_enableAttenuation( true )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the MyGeometryGM class
	\param
	\return
	*/
	/******************************************************************************/
	MyGeometryGM::~MyGeometryGM( void )
	{
		this->Shutdown();

		//the game state pointers will be managed by the destructor of the GameManager base class
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Initializes the game manager by setting up the graphics interface as well as the different states
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryGM::Init( void )
	{
		//instantiate as an OpenGL graphics interface
		this->m_graphicsInterfacePtr = new GraphicsFramework::GraphicsOpenGL();

		//instantiate as a geometry game object manager
		this->m_gameObjMgrPtr = new MyGeometryOM();

		//initialize the render manager
		this->m_renderMgr.Init( m_graphicsInterfacePtr, m_gameObjMgrPtr );

		//instantiate the state ( pass the state name and its parent game manager )
		/*
		this->m_gameStatePtr = new MenuState( "Menu", *this );
		//add the state to the game state map
		this->AddState( this->m_gameStatePtr );
		*/

		//instantiate the state ( pass the state name and its parent game manager )
		this->m_gameStatePtr = new MyGeometryState( "GeometryState", *this );
		//add the state to the game state map
		this->AddState( this->m_gameStatePtr );

		//set the initial game state
		this->SetInitialState( "GeometryState" );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Shuts down the game manager by deleting resources from the heap
	\param
	\return
	*/
	/******************************************************************************/
	void MyGeometryGM::Shutdown( void )
	{
		//delete the graphics interface pointer from the heap memory
		delete this->m_graphicsInterfacePtr;
		this->m_graphicsInterfacePtr = 0;

		//delete the game object manager pointer from the heap memory
		delete this->m_gameObjMgrPtr;
		this->m_gameObjMgrPtr = 0;

		//the game state pointers will be managed by the destructor of the GameManager base class
	}
	

} //end namespace MyGeometryGame