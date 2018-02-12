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

////////////////////////////////////////////////////////////////////////////////
#ifndef MYGEOMETRY_GM_H
#define MYGEOMETRY_GM_H
////////////////////////////////////////////////////////////////////////////////

#include "Graphics\GraphicsOpenGL.h"
#include "Game\GameManager.h"
#include "Game\GameObjectManager.h"
#include "Input\Win32Input.h"
#include "Render\RenderManager.h"

namespace MyGeometryGame
{
	class MyGeometryGM : public GameFramework::GameManager
	{
	public:
		MyGeometryGM( void );
		~MyGeometryGM( void );

		void Init( void );
		void Shutdown( void );

		GraphicsFramework::GraphicsInterface*		m_graphicsInterfacePtr;		
		GameFramework::GameState*					m_gameStatePtr;
		GameFramework::GameObjectManager*			m_gameObjMgrPtr;
		GameFramework::Input						m_input;
		GraphicsFramework::RenderManager			m_renderMgr;

		bool										m_showOrthoProj;
		bool										m_showWallNormal;
		bool										m_isBackFaceEnabled;	
		bool										m_enableAnisotropicFiltering;
		unsigned									m_polygonMode;
		unsigned									m_texMinFilterMode;
		unsigned									m_texMagFilterMode;

		unsigned									m_noOfTilesPerSide;

		Light::LIGHT_EFFECT							m_lighting;
		GraphicsFramework::RENDER_EFFECT			m_lightingEffect;
		GraphicsFramework::RENDER_EFFECT			m_renderEffect;
		unsigned									m_objectToMove;
		bool										m_showProjTex;
		bool										m_enableAttenuation;

	private:
		//make the copy constructor private
		MyGeometryGM( const MyGeometryGM & myGeometryGM );
		//make the assignment operator private
		MyGeometryGM & operator=( const MyGeometryGM & myGeometryGM );
	};

} //end namespace MyGeometryGame


#endif
////////////////////////////////////////////////////////////////////////////////