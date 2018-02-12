/******************************************************************************/
/*!
\file LevelBuild.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 01/03/2012
\brief
This is the level build class that creates and draws the entire level path

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#ifndef _LEVELBUILD_H_
#define _LEVELBUILD_H_

#include "Character.h"
#include "MotionPlanning.h"
#include "../Graphics/GraphicsInterface.h"

void InitStaticScene(MotionPlanning_PointRobot & mp);
void CreateLevelPath_MotionPlanning(MotionPlanning_PointRobot & mp);
//void DrawStaticScene(MotionPlanning_PointRobot & mp);
void DrawStaticScene( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );

//drawing functions
void DrawLine( const float xStartPt, const float yStartPt, const float xEndPt, const float yEndPt, GraphicsFramework::GraphicsInterface * gfx );
void DrawPoint( const float xPt, const float yPt, GraphicsFramework::GraphicsInterface * gfx );

void DrawBoundingRectangle( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );
void DrawMainSegments( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );
void DrawValidTrapezoids( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );
void DrawUnusedSolidAreaTrapezoids( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );

void DrawGraphStates( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );
void DrawGraphPath( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );

void DrawGraphStateIndices( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx );

void DrawCharacterPos( Character & character, GraphicsFramework::GraphicsInterface * gfx );

#endif