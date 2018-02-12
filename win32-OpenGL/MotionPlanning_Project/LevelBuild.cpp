/******************************************************************************/
/*!
\file LevelBuild.cpp
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

#include "LevelBuild.h"

#include <sstream>


#define LINESEGMENT_NUMBER1	26



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Specifies the line segments to be drawn
\param mp
the MotionPlanning_PointRobot
\return
*/
/******************************************************************************/
void InitStaticScene(MotionPlanning_PointRobot & mp)
{
	LineSegment2D segmentList[LINESEGMENT_NUMBER1];
		
	//Set of non-crossing line segments
	//set1
	segmentList[0].start.x = 70;
	segmentList[0].start.y = 210;
	segmentList[0].end.x = 120;
	segmentList[0].end.y = 80;
	
	segmentList[1].start.x = 120;
	segmentList[1].start.y = 80;
	segmentList[1].end.x = 180;
	segmentList[1].end.y = 80;
	
	segmentList[2].start.x = 180;
	segmentList[2].start.y = 80;
	segmentList[2].end.x = 380;
	segmentList[2].end.y = 130;
	
	segmentList[3].start.x = 380;
	segmentList[3].start.y = 130;
	segmentList[3].end.x = 360;
	segmentList[3].end.y = 175;
	
	segmentList[4].start.x = 360;
	segmentList[4].start.y = 175;
	segmentList[4].end.x = 160;
	segmentList[4].end.y = 175;
	
	segmentList[5].start.x = 160;
	segmentList[5].start.y = 175;
	segmentList[5].end.x = 70;
	segmentList[5].end.y = 210;
	
	//set2
	segmentList[6].start.x = 335;
	segmentList[6].start.y = 275;
	segmentList[6].end.x = 345;
	segmentList[6].end.y = 601;

	segmentList[7].start.x = 345;
	segmentList[7].start.y = 601;
	segmentList[7].end.x = 455;
	segmentList[7].end.y = 425;
	
	segmentList[8].start.x = 455;
	segmentList[8].start.y = 425;
	segmentList[8].end.x = 475;
	segmentList[8].end.y = 605;
	
	segmentList[9].start.x = 475;
	segmentList[9].start.y = 605;
	segmentList[9].end.x = 395;
	segmentList[9].end.y = 705;
	
	segmentList[10].start.x = 395;
	segmentList[10].start.y = 705;
	segmentList[10].end.x = 315;
	segmentList[10].end.y = 595;
	
	segmentList[11].start.x = 315;
	segmentList[11].start.y = 595;
	segmentList[11].end.x = 95;
	segmentList[11].end.y = 700;
	
	segmentList[12].start.x = 95;
	segmentList[12].start.y = 700;
	segmentList[12].end.x = 255;
	segmentList[12].end.y = 525;
	
	segmentList[13].start.x = 255;
	segmentList[13].start.y = 525;
	segmentList[13].end.x = 335;
	segmentList[13].end.y = 275;
	
	//set3
	segmentList[14].start.x = 785;
	segmentList[14].start.y = 75;
	segmentList[14].end.x = 865;
	segmentList[14].end.y = 45;
	
	segmentList[15].start.x = 865;
	segmentList[15].start.y = 45;
	segmentList[15].end.x = 930;
	segmentList[15].end.y = 100;
	
	segmentList[16].start.x = 930;
	segmentList[16].start.y = 100;
	segmentList[16].end.x = 860;
	segmentList[16].end.y = 100;
	
	segmentList[17].start.x = 860;
	segmentList[17].start.y = 100;
	segmentList[17].end.x = 920;
	segmentList[17].end.y = 120;
	
	segmentList[18].start.x = 920;
	segmentList[18].start.y = 120;
	segmentList[18].end.x = 841;
	segmentList[18].end.y = 190;
	
	segmentList[19].start.x = 841;
	segmentList[19].start.y = 190;
	segmentList[19].end.x = 960;
	segmentList[19].end.y = 250;
	
	segmentList[20].start.x = 960;
	segmentList[20].start.y = 250;
	segmentList[20].end.x = 820;
	segmentList[20].end.y = 250;
	
	segmentList[21].start.x = 820;
	segmentList[21].start.y = 250;
	segmentList[21].end.x = 885;
	segmentList[21].end.y = 650;
	
	segmentList[22].start.x = 885;
	segmentList[22].start.y = 650;
	segmentList[22].end.x = 620;
	segmentList[22].end.y = 660;
	
	segmentList[23].start.x = 620;
	segmentList[23].start.y = 660;
	segmentList[23].end.x = 740;
	segmentList[23].end.y = 250;
	
	segmentList[24].start.x = 740;
	segmentList[24].start.y = 250;
	segmentList[24].end.x = 870;
	segmentList[24].end.y = 130;
	
	segmentList[25].start.x = 870;
	segmentList[25].start.y = 130;
	segmentList[25].end.x = 785;
	segmentList[25].end.y = 75;
	
	for(int i = 0; i < LINESEGMENT_NUMBER1; i++)
		mp.segmentList.push_back(segmentList[i]);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Creates the entire level path
\param mp
the MotionPlanning_PointRobot
\return
*/
/******************************************************************************/
void CreateLevelPath_MotionPlanning(MotionPlanning_PointRobot & mp)
{
	InitStaticScene(mp);

	//Compute and Save the normals of the segments in a normal-segment data for later use
	mp.Calculate_LineSegments_Normals();

	//Adjust start and end points of all initial segments so that the start is always on the left.
	mp.Adjust_StartEnd_PointsSegment();

	//Compute Free Space
	//Divide the space to trapezoids linked together
	mp.TrapezoidalMap();

	//Line-01
	//Adjust top - bottom line segments
	mp.AdjustRemainingTrapezoids();

	//Line-02
	//Notes Line-02 must be before Line-01. It is after only so we can display correctly the unused trapezoids
	//Remove the unused (solid location) trapezoids
	mp.RemoveUnusedTrapezoids();

	//Compute Path
	//state generation and edge generation
	mp.PathBuilding();	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The main function to draw the scene

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawStaticScene( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	glDisable( GL_TEXTURE_2D );

	//draw static scene options	

	if ( mp.m_showBoundingRect == true )
	{
		//key1
		//draw bounding rectangle
		DrawBoundingRectangle( mp, gfx );
	}

	if ( mp.m_showMainSegments == true )
	{
		//key2
		//draw the main line segment list
		DrawMainSegments( mp, gfx );
	}

	if ( mp.m_showValidTrapezoids == true )
	{
		//key3
		//draw the valid trapezoids for the free space with their left/right points
		DrawValidTrapezoids( mp, gfx );
	}

	if ( mp.m_showUnusedTrapezoids == true )
	{
		//key4
		//draw the trapezoid of the solid area with their left/right points
		DrawUnusedSolidAreaTrapezoids( mp, gfx );
	}

	if ( mp.m_showGraphStates == true )
	{
		//key5
		//draw the states of the graph generated
		DrawGraphStates( mp, gfx );
	}

	if ( mp.m_showGraphPath == true )
	{
		//key6
		//draw the path of the graph generated
		DrawGraphPath( mp, gfx );
	}

	if ( mp.m_showGraphStateIndices == true )
	{
		//key7
		//draw the indices of the states of the graph generated
		DrawGraphStateIndices( mp, gfx );
	}

	glEnable( GL_TEXTURE_2D );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the line

\param xStartPt
the starting x point
\param yStartPt
the starting y point
\param xEndPt
the ending x point
\param yEndPt
the ending y point
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawLine( const float xStartPt, const float yStartPt, const float xEndPt, const float yEndPt, 
	GraphicsFramework::GraphicsInterface * gfx )
{
	float xWorldPt1 = 0.0F;
	float yWorldPt1 = 0.0F;
	float xWorldPt2 = 0.0F;
	float yWorldPt2 = 0.0F;

	gfx->ConvertScreenToWorld( xStartPt, yStartPt, xWorldPt1, yWorldPt1 );
	gfx->ConvertScreenToWorld( xEndPt, yEndPt, xWorldPt2, yWorldPt2 );

	glBegin( GL_LINES );
		glVertex3f( xWorldPt1, -yWorldPt1, 0.0F ); // origin of the FIRST line
		glVertex3f( xWorldPt2, -yWorldPt2, 0.0F ); // ending point of the FIRST line
		//glVertex3f( xStartPt, yStartPt, 0.0F ); // origin of the FIRST line
		//glVertex3f( xEndPt, yEndPt, 0.0F ); // ending point of the FIRST line
	glEnd( );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the point

\param xPt
the x coordinate of the point
\param yPt
the y coordinate of the point
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawPoint( const float xPt, const float yPt, GraphicsFramework::GraphicsInterface * gfx )
{
	float xWorldPt = 0.0F;
	float yWorldPt = 0.0F;

	gfx->ConvertScreenToWorld( xPt, yPt, xWorldPt, yWorldPt );

	glBegin( GL_POINTS );
		glVertex3f( xWorldPt, -yWorldPt, 0.0F );
	glEnd( );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the bounding rectangle

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawBoundingRectangle( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	glColor4f( 1.0F, 0.0F, 0.0F, 1.0F );	

	//TOP
	DrawLine( mp.boundingRect.top.start.x, mp.boundingRect.top.start.y, mp.boundingRect.top.end.x, mp.boundingRect.top.end.y, gfx );

	//BOTTOM
	DrawLine( mp.boundingRect.bottom.start.x, mp.boundingRect.bottom.start.y, mp.boundingRect.bottom.end.x, mp.boundingRect.bottom.end.y, gfx );

	//LEFT
	DrawLine( mp.boundingRect.leftPoint.x, mp.boundingRect.leftPoint.y, mp.boundingRect.top.start.x, mp.boundingRect.top.start.y, gfx );

	//RIGHT
	DrawLine( mp.boundingRect.rightPoint.x, mp.boundingRect.rightPoint.y, mp.boundingRect.bottom.end.x, mp.boundingRect.bottom.end.y, gfx );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the main line segment list

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawMainSegments( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	//std::stringstream ss;

	glColor4f( 0.0F, 1.0F, 0.0F, 1.0F );

	LineSegment2D currLineSeg;
	Point2D startingPt;
	Point2D endingPt;

	for ( unsigned index = 0; index < mp.segmentList.size(); ++index )
	{
		currLineSeg = mp.segmentList.at( index );
		startingPt = currLineSeg.start;
		endingPt = currLineSeg.end;

		DrawLine( startingPt.x, startingPt.y, endingPt.x, endingPt.y, gfx );
		
		/*
		ss.str("");
		ss << startingPt.x << "," << startingPt.y;
		gfx->PrintText( ss.str().c_str(), 
			startingPt.x, startingPt.y,
			GraphicsFramework::TS_SCREEN );

		ss.str("");
		ss << endingPt.x << "," << endingPt.y;
		gfx->PrintText( ss.str().c_str(), 
			endingPt.x, endingPt.y,
			GraphicsFramework::TS_SCREEN );	
		*/

	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the valid trapezoids for the free space with their left/right points

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawValidTrapezoids( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	//std::stringstream ss;
	
	const std::list<Trapezoid> trapList = mp.GetTrapezoidList();

	std::list<Trapezoid>::const_iterator itor = trapList.begin();
	std::list<Trapezoid>::const_iterator end = trapList.end();
	
	while ( itor != end )
	{
		glColor4f( 0.0F, 0.0F, 1.0F, 1.0F );
		DrawLine( itor->top.start.x, itor->top.start.y, itor->bottom.start.x, itor->bottom.start.y, gfx );
		DrawLine( itor->top.end.x, itor->top.end.y, itor->bottom.end.x, itor->bottom.end.y, gfx );

		glColor4f( 0.0F, 1.0F, 1.0F, 1.0F );
		DrawPoint( itor->leftPoint.x, itor->leftPoint.y, gfx );
		DrawPoint( itor->rightPoint.x, itor->rightPoint.y, gfx );

		/*
		ss.str("");
		ss << itor->top.start.x << "," << itor->top.start.y;
		gfx->PrintText( ss.str().c_str(), 
			itor->top.start.x, itor->top.start.y,
			GraphicsFramework::TS_SCREEN );

		ss.str("");
		ss << itor->bottom.start.x << "," << itor->bottom.start.y;
		gfx->PrintText( ss.str().c_str(), 
			itor->bottom.start.x, itor->bottom.start.y,
			GraphicsFramework::TS_SCREEN );

		ss.str("");
		ss << itor->top.end.x << "," << itor->top.end.y;
		gfx->PrintText( ss.str().c_str(), 
			itor->top.end.x, itor->top.end.y,
			GraphicsFramework::TS_SCREEN );

		ss.str("");
		ss << itor->bottom.end.x << "," << itor->bottom.end.y;
		gfx->PrintText( ss.str().c_str(), 
			itor->bottom.end.x, itor->bottom.end.y,
			GraphicsFramework::TS_SCREEN );
		*/

		/*
		ss.str("");
		ss << itor->leftPoint.x << "," << itor->leftPoint.y;
		gfx->PrintText( ss.str().c_str(), 
			itor->leftPoint.x, itor->leftPoint.y,
			GraphicsFramework::TS_SCREEN );

		ss.str("");
		ss << itor->rightPoint.x << "," << itor->rightPoint.y;
		gfx->PrintText( ss.str().c_str(), 
			itor->rightPoint.x, itor->rightPoint.y,
			GraphicsFramework::TS_SCREEN );	
		*/

		++itor;
	}//end while loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the trapezoid of the solid area with their left/right points

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawUnusedSolidAreaTrapezoids( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	const std::list<Trapezoid> trapList = mp.GetUnusedTrapezoidList();

	std::list<Trapezoid>::const_iterator itor = trapList.begin();
	std::list<Trapezoid>::const_iterator end = trapList.end();
	
	while ( itor != end )
	{
		glColor4f( 1.0F, 0.0F, 1.0F, 1.0F );
		DrawLine( itor->top.start.x, itor->top.start.y, itor->bottom.start.x, itor->bottom.start.y, gfx );
		DrawLine( itor->top.end.x, itor->top.end.y, itor->bottom.end.x, itor->bottom.end.y, gfx );

		glColor4f( 0.0F, 1.0F, 1.0F, 1.0F );
		DrawPoint( itor->leftPoint.x, itor->leftPoint.y, gfx );
		DrawPoint( itor->rightPoint.x, itor->rightPoint.y, gfx );

		++itor;
	}//end while loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the states of the graph

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawGraphStates( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	glColor4f( 1.0F, 1.0F, 0.0F, 1.0F );

	State currState;

	for ( unsigned index = 0; index < mp.path->states.size(); ++index )
	{
		currState = mp.path->states.at( index );
		DrawPoint( currState.worldPositionX, currState.worldPositionY, gfx );
	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the path of the graph

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawGraphPath( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	glColor4f( 1.0F, 1.0F, 0.0F, 1.0F );

	State currState;
	State fromState;
	State toState;
	Edge currEdge;

	for ( unsigned index = 0; index < mp.path->states.size(); ++index )
	{
		currState = mp.path->states.at( index );
		
		//loop through the edges of the state
		for ( unsigned i = 0; i < currState.edges.size(); ++i )
		{
			currEdge = currState.edges.at( i );
			fromState = mp.path->states.at( currEdge.from );
			toState = mp.path->states.at( currEdge.to );

			DrawLine( fromState.worldPositionX, fromState.worldPositionY, toState.worldPositionX, toState.worldPositionY, gfx );

		}//end for loop

	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the indices of each state in the path of the graph

\param mp
the motion planning class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawGraphStateIndices( MotionPlanning_PointRobot & mp, GraphicsFramework::GraphicsInterface * gfx )
{
	std::stringstream ss;

	glColor4f( 1.0F, 1.0F, 0.0F, 1.0F );

	State currState;

	for ( unsigned index = 0; index < mp.path->states.size(); ++index )
	{
		currState = mp.path->states.at( index );

		ss.str("");
		ss << index;
		//ss << " (" << currState.worldPositionX << "," << currState.worldPositionY << ")";
		gfx->PrintText( ss.str().c_str(), 
			currState.worldPositionX, currState.worldPositionY,
			GraphicsFramework::TS_SCREEN );
	}//end for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Draw the path of the character position

\param character
the character class
\param gfx
the pointer to the graphics interface

\return
*/
/******************************************************************************/
void DrawCharacterPos( Character & character, GraphicsFramework::GraphicsInterface * gfx )
{
	glDisable( GL_TEXTURE_2D );
	glPointSize( 15.0F );	

	if ( character.m_isStartPtSet == true )
	{
		glColor4f( 0.0F, 1.0F, 0.0F, 1.0F );
		DrawPoint( character.m_startPt.x, character.m_startPt.y, gfx );
	}

	if ( character.m_isEndPtSet == true )
	{
		glColor4f( 1.0F, 0.0F, 0.0F, 1.0F );
		DrawPoint( character.m_endPt.x, character.m_endPt.y, gfx );
	}

	glPointSize( 5.0F );
	glEnable( GL_TEXTURE_2D );
}