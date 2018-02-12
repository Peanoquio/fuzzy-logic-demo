/******************************************************************************/
/*!
\file Board.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #03
\date 13/03/2012
\brief
This is the board class that manages tile related functions

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "Board.h"
#include "../MyGeometryOM.h"



namespace GameFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Initializes the tile board

	\param numOfTilesPerSide
	the number of tiles per side
	\param boardSideLength
	the length of the side of the board

	\return
	*/
	/******************************************************************************/
	void Board::InitializeTileBoard( const unsigned numOfTilesPerSide, const float boardSideLength )
	{
		//initialize the board values
		this->m_boardSideLength = boardSideLength;
		this->m_numOfTilesPerSide = numOfTilesPerSide;
		this->m_tileSize = this->m_boardSideLength / this->m_numOfTilesPerSide;
		this->m_tileSizeOffset = 0.0F;

		this->m_maxRow = static_cast<unsigned>( this->m_numOfTilesPerSide );
		this->m_maxCol = static_cast<unsigned>( this->m_numOfTilesPerSide );
		this->m_tilesNumber = this->m_maxRow * this->m_maxCol;

		this->m_xLimit = this->m_boardSideLength / 2.0F;
		this->m_yLimit = this->m_boardSideLength / 2.0F;
		this->m_xOffset = 0.0F;
		this->m_yOffset = 0.0F;

		this->m_holeReachedTarget = true;
		this->m_tileReachedTarget = true;

		this->m_tileSpeed = SLOW;

		this->m_lockButtons = true;
		this->m_lockTiles = true;
		this->m_stopAnimation = false;

		this->m_endGameState = NA;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the x and y offset values

	\param xOffsetValue
	the x offset value
	\param yOffsetValue
	the y offset value

	\return
	*/
	/******************************************************************************/
	void Board::SetTilePosOffset( const float xOffsetValue, const float yOffsetValue )
	{
		this->m_xOffset = xOffsetValue;
		this->m_yOffset = yOffsetValue;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the tile size offset values

	\param tileOffsetValue
	the tile size offset value

	\return
	*/
	/******************************************************************************/
	void Board::SetTileSizeOffset( const float tileOffsetValue )
	{
		this->m_tileSizeOffset = tileOffsetValue;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the tic tac toe grids

	\param gameMgrPtr
	the pointer to the game manager

	\return
	*/
	/******************************************************************************/
	void Board::CreateTicTacToeGrid( const MyGeometryGame::MyGeometryGM * gameMgrPtr )
	{
		//float xPos = -this->m_xLimit + ( this->m_tileSize / 2.0F );
		//float yPos = this->m_yLimit - ( this->m_tileSize / 2.0F );

		float xPos = -this->m_xLimit;
		float yPos = this->m_yLimit;

		//float tileSize = this->m_tileSize - this->m_tileSizeOffset;

		//allocate in the heap memory
		//add one to the buffer size to include the last index containing the hole position
		//this->m_currTileArrangement = new unsigned int[ this->m_tilesNumber + 1 ];

		unsigned index = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				index = ( j * this->m_maxCol ) + i;

				//set the index positions of the blocks
				//this->m_currTileArrangement[index] = index;			

				if ( i != 0 )
				{
					//VERTICAL LINE
					gameMgrPtr->m_gameObjMgrPtr->GeneratePendingGameObject( MyGeometryGame::WALL_GAMEOBJ, MyGeometryGame::CUBE3_OBJTYPE, 
						gameMgrPtr->m_graphicsInterfacePtr, 
						Math::Vector4( xPos, 0.0F, -0.5F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), 
						Math::Vector4( this->m_boardSideLength, 0.20F, 1.0F, 0.0F ), 90.0F );
				}

				//increment the x position
				xPos += this->m_tileSize;

			} //end for loop	
				
			if ( j != 0 )
			{
				//HORIZONTAL LINE
				gameMgrPtr->m_gameObjMgrPtr->GeneratePendingGameObject( MyGeometryGame::WALL_GAMEOBJ, MyGeometryGame::CUBE3_OBJTYPE, 
					gameMgrPtr->m_graphicsInterfacePtr, 
					Math::Vector4( 0.0F, yPos, -0.5F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), 
					Math::Vector4( this->m_boardSideLength, 0.20F, 1.0F, 0.0F ), 180.0F );
			}

			//decrement the y position
			yPos -= this->m_tileSize;
			
			//reset the x position
			//xPos = -this->m_xLimit + ( this->m_tileSize / 2.0F );
			xPos = -this->m_xLimit;

		}//end for loop

		//set the initial hole position
		//this->m_currTileArrangement[ this->m_tilesNumber ] = 0;		
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the tic tac toe tiles

	\param gameMgrPtr
	the pointer to the game manager

	\return
	*/
	/******************************************************************************/
	void Board::CreateTicTacToeTiles( const MyGeometryGame::MyGeometryGM * gameMgrPtr )
	{
		float xPos = -this->m_xLimit + ( this->m_tileSize / 2.0F );
		float yPos = this->m_yLimit - ( this->m_tileSize / 2.0F );

		float tileSize = this->m_tileSize - this->m_tileSizeOffset;

		//allocate in the heap memory
		//add one to the buffer size to include the last index containing the hole position
		//this->m_currTileArrangement = new unsigned int[ this->m_tilesNumber + 1 ];

		unsigned index = 0;
		//loop through the one-dimensional 3D matrix
		for ( unsigned j = 0; j < this->m_maxRow; ++j )		
		{
			for ( unsigned i = 0; i < this->m_maxCol; ++i )
			{
				//index to simulate a two-dimensional matrix
				index = ( j * this->m_maxCol ) + i;

				//set the index positions of the blocks
				//this->m_currTileArrangement[index] = index;				

				//X TILE BLOCK
				gameMgrPtr->m_gameObjMgrPtr->GeneratePendingGameObject( MyGeometryGame::BLOCK_X_GAMEOBJ, MyGeometryGame::BLOCK_X_OBJTYPE, 
					gameMgrPtr->m_graphicsInterfacePtr, 
					Math::Vector4( xPos, yPos, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), 
					Math::Vector4( tileSize, tileSize, tileSize, 0.0F ), 0.0F,
					static_cast<float>( this->m_tileSpeed ), 0.0F, 0.0F, 1.0F, false, j, i, index );

				//O TILE BLOCK
				gameMgrPtr->m_gameObjMgrPtr->GeneratePendingGameObject( MyGeometryGame::BLOCK_O_GAMEOBJ, MyGeometryGame::BLOCK_O_OBJTYPE, 
					gameMgrPtr->m_graphicsInterfacePtr, 
					Math::Vector4( xPos, yPos, 0.0F, 1.0F ), Math::Vector4( 0.0F, 0.0F, 0.0F, 0.0F ), 
					Math::Vector4( tileSize, tileSize, tileSize, 0.0F ), 0.0F,
					static_cast<float>( this->m_tileSpeed ), 0.0F, 0.0F, 1.0F, false, j, i, index );
				
				//increment the x position
				xPos += this->m_tileSize;

			} //end for loop	

			//decrement the y position
			yPos -= this->m_tileSize;
			
			//reset the x position
			xPos = -this->m_xLimit + ( this->m_tileSize / 2.0F );

		}//end for loop

		//set the initial hole position
		//this->m_currTileArrangement[ this->m_tilesNumber ] = 0;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Inactivates the tic tac toe tiles

	\param gameObjList
	the reference to the game object list

	\return
	*/
	/******************************************************************************/
	void Board::InactivateTicTacToeTiles( GameFramework::GameObjectVector & gameObjList ) const
	{
		for ( unsigned index = 0; index < gameObjList.size(); ++index )
		{
			GameFramework::GameObject & currGameObj = gameObjList.at( index );
			//set the tic tac toe tile initially to inactive
			if ( currGameObj.GetIdentifier() == MyGeometryGame::BLOCK_O_GAMEOBJ || currGameObj.GetIdentifier() == MyGeometryGame::BLOCK_X_GAMEOBJ )
			{
				currGameObj.SetActive( false );
			}
		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Inactivates the tic tac toe tiles

	\param gameObjList
	the reference to the game object list
	\param worldX
	the world x coordinate
	\param worldY
	the world y coordinate

	\return
	*/
	/******************************************************************************/
	void Board::SelectAndActivateTicTacToeTilesEvent( GameFramework::GameObjectVector & gameObjList, const float worldX, const float worldY )
	{
		//loop through the game objects of the state
		for ( size_t index = 0; index < gameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = gameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == true )
			{
				continue;
			}

			float posOffset = this->m_tileSize / 2.0F;
			float xPosGameObj = gameObj.GetPhysicsObj().GetPosition().GetFloatX();
			float yPosGameObj = gameObj.GetPhysicsObj().GetPosition().GetFloatY();

			//validate tile blocks only if there is no animation for the block tiles
			if ( gameObj.GetIdentifier() == MyGeometryGame::BLOCK_O_GAMEOBJ && this->m_lockTiles == false )
			{
				//validate if the mouse world position is within the world coordinates of the tile
				//if ( ( worldX >= ( xPosGameObj - posOffset ) ) && ( worldX <= ( xPosGameObj + posOffset ) ) 
					//&& ( worldY >= ( yPosGameObj - ( posOffset * 0.5F ) ) ) && ( worldY <= ( yPosGameObj + ( posOffset * 1.75F ) ) ) )
				if ( ( worldX >= ( xPosGameObj - posOffset ) ) && ( worldX <= ( xPosGameObj + posOffset ) ) 
					&& ( worldY >= ( yPosGameObj - (posOffset) ) ) && ( worldY <= ( yPosGameObj + (posOffset) ) ) )
				{
					//validate if the selected cell is already occupied
					bool isCellOccupied = this->m_ticTacToe.IsBoardCellOccupied( gameObj.GetRow(), gameObj.GetColumn() );

					if ( isCellOccupied == false )
					{
						gameObj.SetActive( true );	

						//set the board state
						this->SetBoardState( gameObj, TicTacToe::PLAYER );	

						//check the game state
						if ( this->ValidateEndState() == false )
						{
							//invoke the MiniMax algorithm
							this->m_ticTacToe.MiniMax( this->m_searchDepth );

							//invoke the next move of the computer
							this->ComputerTicTacToeMove( gameObjList );

							//check the game state again after the computer move
							this->ValidateEndState();
						}
					}

					break;
				}
			}

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Updates the state of the board based on the selected tile

	\param gameObj
	the reference to the game object
	\param TURN
	the flag to indicate whether it is the computer's or player's turn

	\return
	*/
	/******************************************************************************/
	void Board::SetBoardState( const GameFramework::GameObject & gameObj, const TicTacToe::TURN turn )
	{
		unsigned row = gameObj.GetRow();
		unsigned col = gameObj.GetColumn();

		//update the state of the board based on the selected tile
		this->m_ticTacToe.SetBoardCell( row, col, turn );	
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Updates the board based on the computer's move

	\param gameObjList
	the reference to the game object list

	\return
	*/
	/******************************************************************************/
	void Board::ComputerTicTacToeMove( GameFramework::GameObjectVector & gameObjList )
	{
		//loop through the game objects of the state
		for ( size_t index = 0; index < gameObjList.size(); ++index)
		{
			//the current game object
			GameFramework::GameObject& gameObj = gameObjList.at( index );

			//validate if the game object is active
			if ( gameObj.IsActive() == true )
			{
				continue;
			}

			//validate tile blocks only if there is no animation for the block tiles
			if ( gameObj.GetIdentifier() == MyGeometryGame::BLOCK_X_GAMEOBJ
				&& this->m_lockTiles == false )
			{
				//get the computed next move of the computer
				unsigned row = 0;
				unsigned col = 0;
				this->m_ticTacToe.GetNextMove( row, col );

				//find the corresponding tile to display based on the next move of the computer
				if ( row == gameObj.GetRow() && col == gameObj.GetColumn() )
				{
					gameObj.SetActive( true );	

					//set the board state
					this->SetBoardState( gameObj, TicTacToe::COMPUTER );		

					break;
				}
			}

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validates if the end state of the game has been reached

	\param

	\return bool
	if true, the end state of the game has been reached, otherwise false
	*/
	/******************************************************************************/
	bool Board::ValidateEndState( void )
	{
		bool endStateReached = false;

		//check the game state
		if ( this->m_ticTacToe.WinTest() == true )
		{
			endStateReached = true;
			this->m_endGameState = WIN;

			//if computer wins hand the turn to the player
			this->m_ticTacToe.m_currentTurn = TicTacToe::PLAYER;
		}
		else if ( this->m_ticTacToe.LooseTest() == true )
		{
			endStateReached = true;
			this->m_endGameState = LOSE;

			//if computer loses, hand the turn to the computer
			this->m_ticTacToe.m_currentTurn = TicTacToe::COMPUTER;
		}
		else if ( this->m_ticTacToe.DrawTest() == true )
		{
			endStateReached = true;
			this->m_endGameState = DRAW;

			//alternate the turns
			if ( this->m_ticTacToe.m_currentTurn == TicTacToe::COMPUTER )
			{
				this->m_ticTacToe.m_currentTurn = TicTacToe::PLAYER;
			}
			else if ( this->m_ticTacToe.m_currentTurn == TicTacToe::PLAYER )
			{
				this->m_ticTacToe.m_currentTurn = TicTacToe::COMPUTER;
			}
		}

		if ( endStateReached == true )
		{
			this->m_lockTiles = true;
			this->m_lockButtons = false;
		}

		return endStateReached;
	}

}//end namespace Board