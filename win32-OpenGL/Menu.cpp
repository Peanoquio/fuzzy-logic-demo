/******************************************************************************/
/*!
\file Menu.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 25/12/2011
\brief
This is the menu state

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "Menu.h"
#include "MyGeometryOM.h"
#include <sstream>

namespace MyGeometryGame
{
	/////////////////////////////////////////////////////////////////////////////
	/*!
	\brief
	This is the default constructor

	\param stateName
	the name of the game state
	\param parentGM
	the parent game manager of this state
	
	\exception None
	\return void
	*/
	/////////////////////////////////////////////////////////////////////////////
	MenuState::MenuState( const std::string& stateName, MyGeometryGM& parentGM )
		:GameState( stateName ), 
		m_parentGM( parentGM ), 
		m_currentMenuItem( 0 )
	{
		this->m_menuOptions.push_back("2 X 2");
		this->m_menuOptions.push_back("3 x 3");
		this->m_menuOptions.push_back("4 x 4");
		this->m_menuOptions.push_back("Quit");
	}


	/////////////////////////////////////////////////////////////////////////////
	/*!
	\brief
	MenuState::~MenuState(void)
	This is the destructor

	\param void
	
	\exception None
	\return void
	*/
	/////////////////////////////////////////////////////////////////////////////
	MenuState::~MenuState( void )
	{
		this->m_menuOptions.clear();
	}


	/////////////////////////////////////////////////////////////////////////////
	/*!
	\brief
	This is to initialize the state

	\param void
	
	\exception None
	\return void
	*/
	/////////////////////////////////////////////////////////////////////////////
	void MenuState::Init( void )
	{		
		//TILES
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_2_GAMEOBJ, BLOCK_2_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_3_GAMEOBJ, BLOCK_3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_4_GAMEOBJ, BLOCK_4_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_0_GAMEOBJ, CUBE_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 1.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.0F, 1.0F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_P_GAMEOBJ, BLOCK_P_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -2.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.65F, 0.65F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_U_GAMEOBJ, BLOCK_U_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -1.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.65F, 0.65F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_Z_GAMEOBJ, BLOCK_Z_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -0.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.65F, 0.65F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_Z_GAMEOBJ, BLOCK_Z_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.65F, 0.65F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_L_GAMEOBJ, BLOCK_L_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 1.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.65F, 0.65F, 1.0F, 0.0F ), 0.0F );

		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( BLOCK_E_GAMEOBJ, BLOCK_E_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.5F, 0.0F, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 0.65F, 0.65F, 1.0F, 0.0F ), 0.0F );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//GANTRY
		//TOP BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, 2.0F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 4.0F, 0.10F, 2.0F, 0.0F ), 0.0F );
		//BOTTOM BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 0.0F, -2.0F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 4.0F, 0.10F, 2.0F, 0.0F ), 180.0F );
		//LEFT BORDER		
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -3.0F, 0.0F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.10F, 2.0F, 0.0F ), 90.0F );
		//RIGHT BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 3.0F, 0.0F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 3.0F, 0.10F, 2.0F, 0.0F ), -90.0F );

		//RIGHT TOP CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.50F, 1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), -28.0F );
		//RIGHT BOTTOM CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( 2.50F, -1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), 208.0F );
		//LEFT TOP CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -2.50F, 1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), 28.0F );
		//LEFT BOTTOM CORNER BORDER
		this->m_parentGM.m_gameObjMgrPtr->GeneratePendingGameObject( WALL_GAMEOBJ, CUBE3_OBJTYPE, this->m_parentGM.m_graphicsInterfacePtr, 
			Math::Vector4( -2.50F, -1.73F, -1.10F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), Math::Vector4( 1.18F, 0.10F, 2.0F, 0.0F ), -208.0F );
			

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Update the state
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MenuState::Update( float /*startTime*/, float dt )
	{
		//add the game objects from the game object manager to the current object list of the state
		this->m_parentGM.m_gameObjMgrPtr->AddGameObjects( this->m_currGameObjList );

		//updates the scene
		this->UpdateBehavior( dt );
		//draw/render the objects
		this->DrawMain( dt );
	}


	/////////////////////////////////////////////////////////////////////////////
	/*!
	\brief
	This is to update the state behaviour based on the input

	\param float
	
	\exception None
	\return void
	*/
	/////////////////////////////////////////////////////////////////////////////
	void MenuState::UpdateBehavior( float /*dt*/ )
	{
		if ( this->m_parentGM.m_input.IsTriggered( InputMap::RETURN ) )
		{
			switch( this->m_currentMenuItem )
			{
				case MT_PUZZLE2X2:
					{
						this->m_parentGM.m_noOfTilesPerSide = 2;
						this->m_parentGM.SetNextState( "GeometryState" );
						break;
					}		
				case MT_PUZZLE3X3:
					{
						this->m_parentGM.m_noOfTilesPerSide = 3;
						this->m_parentGM.SetNextState( "GeometryState" );
						break;
					}
				case MT_PUZZLE4X4:
					{
						this->m_parentGM.m_noOfTilesPerSide = 4;
						this->m_parentGM.SetNextState( "GeometryState" );
						break;
					}
				case MT_QUIT:
					{
						this->m_parentGM.SetQuit(true);
						break;
					}
				default:
					break;
			}

			return;
		}		
		else if ( this->m_parentGM.m_input.IsTriggered( InputMap::ESCAPE ) )
		{
			this->m_parentGM.SetQuit(true);
			return;
		}
		else if ( this->m_parentGM.m_input.IsTriggered( InputMap::ARROW_DOWN ) )
		{
			//only increment if value is less than the allowable size
			if ( this->m_currentMenuItem != MT_QUIT )
			{
				++this->m_currentMenuItem;
			}	
		}
		else if (this->m_parentGM.m_input.IsTriggered( InputMap::ARROW_UP ) )
		{
			//only decrement if value is greater than zero
			if ( this->m_currentMenuItem != MT_PUZZLE2X2 )
			{
				--this->m_currentMenuItem;
			}		
		}


		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//toggle display of puzzle mode tile
			if ( this->m_currentMenuItem == MT_PUZZLE2X2 )
			{
				if ( gameObj.GetIdentifier() == BLOCK_2_OBJTYPE )
				{
					gameObj.SetActive( true );
				}
				else if ( gameObj.GetIdentifier() == BLOCK_3_OBJTYPE || gameObj.GetIdentifier() == BLOCK_4_OBJTYPE || gameObj.GetIdentifier() == BLOCK_0_OBJTYPE )
				{
					gameObj.SetActive( false );
				}
			}
			else if ( this->m_currentMenuItem == MT_PUZZLE3X3 )
			{
				if ( gameObj.GetIdentifier() == BLOCK_3_OBJTYPE )
				{
					gameObj.SetActive( true );
				}
				else if ( gameObj.GetIdentifier() == BLOCK_2_OBJTYPE || gameObj.GetIdentifier() == BLOCK_4_OBJTYPE || gameObj.GetIdentifier() == BLOCK_0_OBJTYPE )
				{
					gameObj.SetActive( false );
				}
			}
			else if ( this->m_currentMenuItem == MT_PUZZLE4X4 )
			{
				if ( gameObj.GetIdentifier() == BLOCK_4_OBJTYPE )
				{
					gameObj.SetActive( true );
				}
				else if ( gameObj.GetIdentifier() == BLOCK_2_OBJTYPE || gameObj.GetIdentifier() == BLOCK_3_OBJTYPE || gameObj.GetIdentifier() == BLOCK_0_OBJTYPE )
				{
					gameObj.SetActive( false );
				}
			}
			else if ( this->m_currentMenuItem == MT_QUIT )
			{
				if ( gameObj.GetIdentifier() == BLOCK_0_OBJTYPE )
				{
					gameObj.SetActive( true );
				}
				else if ( gameObj.GetIdentifier() == BLOCK_2_OBJTYPE || gameObj.GetIdentifier() == BLOCK_3_OBJTYPE || gameObj.GetIdentifier() == BLOCK_4_OBJTYPE )
				{
					gameObj.SetActive( false );
				}
			}

		}//end for loop

	}


	/////////////////////////////////////////////////////////////////////////////
	/*!
	\brief
	This is to shutdown the state

	\param void
	
	\exception None
	\return void
	*/
	/////////////////////////////////////////////////////////////////////////////
	void MenuState::Shutdown(void)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The main draw function
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MenuState::DrawMain( float dt )
	{
		//start the graphics interface for drawing
		this->m_parentGM.m_graphicsInterfacePtr->StartDrawing();

		//get pointer to the matrix stack
		Utility::MatrixStack * matrixStack = &( this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack );			

		//set the model view matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::MODELVIEW ) );	
		matrixStack->MatrixMode( Utility::MODELVIEW );

		matrixStack->Push();

			//pass the view transformation matrix
			matrixStack->MultMatrix ( this->m_parentGM.m_graphicsInterfacePtr->m_camera.GenerateViewTransformMtx() );	

			//render/draw the objects
			this->DrawObjects( dt );

			//draw the text
			this->DrawTextToScreen();

		matrixStack->Pop();

		//end the graphics interface for drawing
		this->m_parentGM.m_graphicsInterfacePtr->EndDrawing();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render/draw the text
	\param
	\return
	*/
	/******************************************************************************/
	void MenuState::DrawTextToScreen( void )
	{
		Math::Mtx44 mvp;
		Math::Mtx44 projMtx;
		Math::Mtx44 tranformMtx;

		GraphicsFramework::GraphicsInterface * gfx = this->m_parentGM.m_graphicsInterfacePtr;

		//get pointer to the matrix stack
		Utility::MatrixStack * matrixStack = &( this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//set the projection matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::PROJECTION ) );
		matrixStack->MatrixMode( Utility::PROJECTION );
		//store the projection matrix
		projMtx = matrixStack->Top();
		this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( projMtx );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set the model view matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::MODELVIEW ) );
		matrixStack->MatrixMode( Utility::MODELVIEW );

		matrixStack->Push();

			//tranformMtx.SetToTranslation( 0.0F, 0.0F, 1.0F );
			//pass the object transformation matrix					
			//matrixStack->MultMatrix ( tranformMtx );

			//concatenate to form the model-view-projection matrix
			mvp = projMtx * matrixStack->Top();					

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//explicitly call the graphics API to load the matrix transformation
			this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( mvp );

			//this->InvokeVertexShader( "vtxShader", "modelViewProjMatrix", mvp.GetMatrixArr() );
			//this->InvokeFragmentShader( "fragShader", "texId", textureId );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			std::stringstream ss;

			ss.str("");
			ss << "Use arrow keys to select the puzzle mode:";
			gfx->PrintText(ss.str().c_str(), 
					(static_cast<float>( gfx->GetScreenWidth() ) / 4 ), 
					(static_cast<float>( gfx->GetScreenHeight() ) / 2 + 110 ), 
					GraphicsFramework::TS_SCREEN, 0, 0, 255, 255 );

			size_t size = this->m_menuOptions.size();
		
			//create the menu items
			for ( size_t i = 0; i < size; ++i )
			{
				ss.str("");
				ss << this->m_menuOptions[i];

				//check if the current menu item is selected
				if ( this->m_currentMenuItem == i )
				{
					gfx->PrintText( ss.str().c_str(), 
						( static_cast<float>( gfx->GetScreenWidth() ) / 3 + 150 ), 
						( static_cast<float>( gfx->GetScreenHeight() ) / 2 ) + 150 + ( i * 30 ), 
						GraphicsFramework::TS_SCREEN, 100, 100, 100, 255 );					
				}
				else
				{
					gfx->PrintText( ss.str().c_str(), 
						( static_cast<float>( gfx->GetScreenWidth()) / 3 + 120 ), 
						( static_cast<float>( gfx->GetScreenHeight() / 2 ) ) + 150 + ( i * 30 ), 
						GraphicsFramework::TS_SCREEN );
				}
			}

		matrixStack->Pop();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render/draw the object
	\param dt
	the frame time
	\return
	*/
	/******************************************************************************/
	void MenuState::DrawObjects( float /*dt*/ )
	{
		//render/draw the object
		//loop through the game objects of the state
		for ( size_t index = 0; index < this->m_currGameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = this->m_currGameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == false)
			{
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
			//render the game object
			this->RenderObject( gameObj );			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
		}//end for loop
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Render of the game object
	\param gameObj
	the game object
	\return
	*/
	/******************************************************************************/
	void MenuState::RenderObject( GameFramework::GameObject & gameObj ) const
	{
		const GraphicsFramework::BaseGeometryBuilder* baseGeometryBuilderPtr = 0;
		GLuint VAO = 0;
		GLuint textureId = 0;

		Math::Mtx44 mvp;
		Math::Mtx44 projMtx;		

		//get pointer to the matrix stack
		Utility::MatrixStack * matrixStack = &( this->m_parentGM.m_graphicsInterfacePtr->m_matrixStack );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//set the projection matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::PROJECTION ) );
		matrixStack->MatrixMode( Utility::PROJECTION );
		//store the projection matrix
		projMtx = matrixStack->Top();
		this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( projMtx );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//set the model view matrix
		this->m_parentGM.m_graphicsInterfacePtr->SetMatrixMode( static_cast<unsigned>( Utility::MODELVIEW ) );
		matrixStack->MatrixMode( Utility::MODELVIEW );

		matrixStack->Push();

			//pass the object transformation matrix					
			matrixStack->MultMatrix ( this->GetObjectTransformation( gameObj ) );

			//concatenate to form the model-view-projection matrix
			mvp = projMtx * matrixStack->Top();					

			//get the VAO of the current game object
			VAO = gameObj.GetGraphicsObj().GetNameOfVAO();
			//get the pointer to the base geometry builder based on the object type to be rendered
			baseGeometryBuilderPtr = this->m_parentGM.m_gameObjMgrPtr->RetrieveBaseGeometryBuilder( gameObj.GetType() );	
			//get the texture name of the current game object
			textureId = gameObj.GetGraphicsObj().GetTextureId( 0 );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//explicitly call the graphics API to load the matrix transformation
			this->m_parentGM.m_graphicsInterfacePtr->LoadMatrixToGraphicsInterface( mvp );

			//this->InvokeVertexShader( "vtxShader", "modelViewProjMatrix", mvp.GetMatrixArr() );
			//this->InvokeFragmentShader( "fragShader", "texId", textureId );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//validate if there is a texture provided
			if ( textureId != 0 )
			{
				//render the game object
				this->m_parentGM.m_graphicsInterfacePtr->Draw( VAO, baseGeometryBuilderPtr, textureId );
			}
			else
			{
				//render the game object
				this->m_parentGM.m_graphicsInterfacePtr->Draw( VAO, baseGeometryBuilderPtr );	
			}

		matrixStack->Pop();

		//ASSERT ( glGetError() != GL_NO_ERROR, "Cannot render the object." );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Apply the transformation of the game object
	\param gameObj
	the game object
	\return Mtx44
	the object transformation matrix
	*/
	/******************************************************************************/
	const Math::Mtx44 MenuState::GetObjectTransformation( GameFramework::GameObject & gameObj ) const
	{
		Math::Mtx44 rotateMtx;
		Math::Mtx44 scaleMtx;
		Math::Mtx44 translateMtx;

		//set scale
		scaleMtx.SetToScale( 
			gameObj.GetPhysicsObj().GetScale().GetFloatX(), 
			gameObj.GetPhysicsObj().GetScale().GetFloatY(), 
			gameObj.GetPhysicsObj().GetScale().GetFloatZ() );
		//set rotation
		rotateMtx.SetToRotationDegreesZ( gameObj.GetPhysicsObj().GetAngleDegrees() );				
		//set translation
		translateMtx.SetToTranslation( 
			gameObj.GetPhysicsObj().GetPosition().GetFloatX(), 
			gameObj.GetPhysicsObj().GetPosition().GetFloatY(), 
			gameObj.GetPhysicsObj().GetPosition().GetFloatZ() );

		//return the concatenated transformation matrices
		return ( translateMtx * rotateMtx * scaleMtx );
	}

}