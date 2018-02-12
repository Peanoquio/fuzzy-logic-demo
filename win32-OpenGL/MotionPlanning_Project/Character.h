/******************************************************************************/
/*!
\file Character.h
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

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "MotionPlanning.h"


class Character
{
	float speed;	
	float stateRadius;//for collision
	
	MotionPlanning_PointRobot * motionPlanning_PointRobot;

	//locate the nearest trapezoid to where the character is plotted
	int GetNearestTrapezoidState( Trapezoid * trapezoid );
	
	//To add any new private member data and member function here
	int GetMiddleTrapezoidState( const Trapezoid * trapezoid);
	bool ValidateTrapezoid( const Trapezoid * trap ) const;
	bool GetTrapezoid( Trapezoid* & currentTrap, const Point2D startPt, const Point2D endPt );
	//bool GetEndTrapezoid( Trapezoid * currentTrap, Trapezoid* & endTrap );
	
public:

	Character();
	~Character();

	void Set_MotionPlanning_PointRobot(MotionPlanning_PointRobot * mp);
	void SetSpeed(float sp);
	
	//To add any new public member data and member function here
	bool			m_isStartPtSet;
	bool			m_isEndPtSet;
	Point2D			m_startPt;
	Point2D			m_endPt;
	LineSegment2D	m_pathLineSeg;	
	Trapezoid *		m_startTrap;
	Trapezoid *		m_endTrap;
	int				m_startIndex;
	int				m_endIndex;
	bool			m_showErrMessage;
	bool			m_xTargetReached;
	bool			m_yTargetReached;
	
	void SetPosition( const float mouseX, const float mouseY );
	const MotionPlanning_PointRobot * Get_MotionPlanning_PointRobot( void ) const;
	
	void SetStateRadius( const float stateRadius );
	float GetStateRadius( void ) const;
	float GetSpeed( void ) const;
};

#endif