/******************************************************************************/
/*!
\file Character.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 01/03/2012
\brief
This is the character class that will be used to manage the movement along the generated path

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "Character.h"
#include "../ErrorHandling/MessageBox.h"

#include <sstream> // std::wstringstream
#if defined(UNICODE)
typedef std::wstringstream StringStream_t;
#else
typedef std::stringstream SringStream_t;
#endif // UNICODE



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The constructor of the Character class

\param

\return
*/
/******************************************************************************/
Character::Character()
	: m_isStartPtSet( false ),
	m_isEndPtSet( false ),
	m_startPt(),
	m_endPt(),
	m_pathLineSeg(),
	m_startTrap( 0 ),
	m_endTrap( 0 ),
	m_startIndex( -1 ),
	m_endIndex( -1 ),
	m_showErrMessage( false ),
	m_xTargetReached( true ),
	m_yTargetReached( true )
{
	speed = 0.0f;
	motionPlanning_PointRobot = NULL;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The destructor of the Character class

\param

\return
*/
/******************************************************************************/
Character::~Character()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Set the motion planning point robot
\param mp
the motion planning point robot
\return
*/
/******************************************************************************/
void Character::Set_MotionPlanning_PointRobot( MotionPlanning_PointRobot * mp )
{
	this->motionPlanning_PointRobot = mp;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Get the pointer to the motion planning robot

\param

\return MotionPlanning_PointRobot *
the pointer to the motion planning robot
*/
/******************************************************************************/
const MotionPlanning_PointRobot * Character::Get_MotionPlanning_PointRobot( void ) const
{
	return this->motionPlanning_PointRobot;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Set the speed of the character
\param sp
the speed value
\return
*/
/******************************************************************************/
void Character::SetSpeed( float sp )
{
	//set the speed value
	this->speed = sp;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Get the speed
\param 
\return float
the speed value
*/
/******************************************************************************/
float Character::GetSpeed( void ) const
{
	return this->speed;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Set the state radius
\param stateRadius
the state radius
\return
*/
/******************************************************************************/
void Character::SetStateRadius( const float stateRadius )
{
	this->stateRadius = stateRadius;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Get the state radius
\param 
\return float
the state radius
*/
/******************************************************************************/
float Character::GetStateRadius( void ) const
{
	return this->stateRadius;
}	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the nearest trapezoid middle/edge state relative to the starting position of the selected path

\param trapezoid
the pointer to the starting trapezoid

\return int
the index of the trapezoid state nearest to the starting position of the selected path
*/
/******************************************************************************/
int Character::GetNearestTrapezoidState( Trapezoid * trapezoid )
{
	int nearestStateIndex = trapezoid->stateIndex;

	//get the trapezoid middle state in the path 
	State & currState = this->motionPlanning_PointRobot->path->states.at( trapezoid->stateIndex );
	State nearestState = currState;

	//compute the distance
	float xDiff = currState.worldPositionX - this->m_startPt.x;
	float yDiff = currState.worldPositionY - this->m_startPt.y;
	float shortestDistanceSquared = ( xDiff * xDiff ) + ( yDiff * yDiff );

	//validate the edge states if they are nearer to the starting position compared to the trapezoid middle state
	for ( unsigned index = 0; index < currState.edges.size(); ++index )
	{
		//get the shared between/edge state
		Edge & currEdge = currState.edges.at( index );
		State & edgeToState = this->motionPlanning_PointRobot->path->states.at( currEdge.to );		

		//compute the distance
		float xDiffEdge = edgeToState.worldPositionX - this->m_startPt.x;
		float yDiffEdge = edgeToState.worldPositionY - this->m_startPt.y;
		float distanceSquaredEdge = ( xDiffEdge * xDiffEdge ) + ( yDiffEdge * yDiffEdge );

		//if the distance is shorter
		if ( distanceSquaredEdge < shortestDistanceSquared )
		{
			//update the nearest state index
			nearestStateIndex = currEdge.to;
			//update the nearest state
			nearestState = edgeToState;
			//update the shortest distance
			shortestDistanceSquared = distanceSquaredEdge;
		}		
		else
		{
		}

	}//end for loop

	return nearestStateIndex;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the middle trapezoid state

\param trapezoid
the pointer to the trapezoid

\return int
the index of the middle trapezoid state
*/
/******************************************************************************/
int Character::GetMiddleTrapezoidState( const Trapezoid * trapezoid )
{
	return trapezoid->stateIndex;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the trapezoid based on the start and end points of the line segment

\param startTrap
the pointer to the starting trapezoid
\param startPt
the start point
\param endPt
the end point

\return
*/
/******************************************************************************/
bool Character::GetTrapezoid( Trapezoid* & currentTrap, const Point2D startPt, const Point2D endPt )
{
	bool isTrapezoidValid = false;

	//we start by finding the first trapezoid from the left. 
	//This is done by finding in which trapezoid the start point of the current line segment resides.
	currentTrap = this->motionPlanning_PointRobot->TrapezoidSearch( 
		& this->motionPlanning_PointRobot->searchStructure, 
		startPt, 
		endPt );	

	if ( currentTrap == 0 )
	{
		//reset the position flags
		this->m_isStartPtSet = false;
		this->m_isEndPtSet = false;
	}
	else
	{
		//validate the starting trapezoid
		if ( this->ValidateTrapezoid( currentTrap ) == true )
		{
			isTrapezoidValid = true;
		}
		else
		{
			//reset the position flags
			this->m_isStartPtSet = false;
			this->m_isEndPtSet = false;
		}
	}

	return isTrapezoidValid;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the ending trapezoid based on the current starting trapezoid

\param currentTrap
the pointer to the starting trapezoid
\param endTrap
the pointer to the ending trapezoid

\return
*/
/******************************************************************************/
/*
bool Character::GetEndTrapezoid( Trapezoid * currentTrap, Trapezoid* & endTrap )
{
	bool isTrapezoidValid = false;

	this->m_pathLineSeg.start = this->m_startPt;
	this->m_pathLineSeg.end = this->m_endPt;

	//traverse and find the other intersected trapezoids starting from the left-most intersected trapezoid
	this->motionPlanning_PointRobot->TraverseIntersectedTrapezoids( currentTrap, this->m_pathLineSeg );

	//store the ending trapezoid
	endTrap = currentTrap;
	this->m_endTrap = currentTrap;

	//validate the ending trapezoid
	if ( this->ValidateTrapezoid( endTrap ) == true )
	{
		isTrapezoidValid = true;
	}
	else
	{
		//reset the position flags
		this->m_isStartPtSet = false;
		this->m_isEndPtSet = false;
	}
	
	return isTrapezoidValid;	
}
*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Validates if the trapezoid is in the solid area

\param trap
the pointer to the trapezoid

\return bool
if true, the trapezoid is not in the solid area, otherwise false
*/
/******************************************************************************/
bool Character::ValidateTrapezoid( const Trapezoid * trap ) const
{
	bool isValidTrapezoid = true;

	std::list< Trapezoid > unusedTrapList = this->motionPlanning_PointRobot->GetUnusedTrapezoidList();
	std::list< Trapezoid >::const_iterator itor = unusedTrapList.begin();
	std::list< Trapezoid >::const_iterator end = unusedTrapList.end();

	//loop through the unused trapezoid list
	while ( itor != end )
	{
		//if the trapezoid is found in the unused list
		//if they point to the same node in the search tree
		if ( itor->nodePtr == trap->nodePtr )
		{
			isValidTrapezoid = false;
			break;
		}

		++itor;
	}//end while loop

	return isValidTrapezoid;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Set the position based on where the mouse is pointing at

\param mouseX
the mouse x coordinate
\param mouseY
the mouse y coordinate

\return
*/
/******************************************************************************/
void Character::SetPosition( const float mouseX, const float mouseY )
{
	Trapezoid * startTrap = 0;
	Trapezoid * endTrap = 0;

	//initialize the shortest path container
	this->motionPlanning_PointRobot->path->shortestPathStates.clear();
	this->motionPlanning_PointRobot->path->shortestPathIndices.clear();


	if ( this->m_isStartPtSet == false )
	{
		this->m_startPt.x = mouseX;
		this->m_startPt.y = mouseY;
		this->m_pathLineSeg.start = this->m_startPt;	

		//get the start trapezoid based on the starting position
		this->m_isStartPtSet = this->GetTrapezoid( startTrap, this->m_startPt, this->m_startPt );
		this->m_startTrap = startTrap;

		//get the state index based on the trapezoid
		if ( this->m_isStartPtSet == true )
		{
			this->m_startIndex = this->GetNearestTrapezoidState( startTrap );
			this->m_showErrMessage = false;
		}
		else
		{
			this->m_showErrMessage = true;
		}	
	}
	else if ( this->m_isEndPtSet == false )
	{
		this->m_endPt.x = mouseX;
		this->m_endPt.y = mouseY;
		this->m_pathLineSeg.end = this->m_endPt;

		//get the end trapezoid based on the ending position
		//this->m_isEndPtSet = this->GetEndTrapezoid( this->m_startTrap, endTrap );
		this->m_isEndPtSet = this->GetTrapezoid( endTrap, this->m_endPt, this->m_endPt );
		this->m_endTrap = endTrap;

		//get the state index based on the trapezoid
		if ( this->m_isEndPtSet == true )
		{
			this->m_endIndex = this->GetMiddleTrapezoidState( endTrap );
			this->m_showErrMessage = false;
		}
		else
		{
			this->m_showErrMessage = true;
		}
	}

	//if the start and end points are set
	if ( this->m_isStartPtSet == true && this->m_isEndPtSet == true )
	{
		//compute for the shortest path
		this->motionPlanning_PointRobot->path->ComputeShortestPath( this->m_startIndex, this->m_endIndex );

		//reset the flags
		//this->m_isStartPtSet = false;
		//this->m_isEndPtSet = false;

		this->m_showErrMessage = false;
	}	
}