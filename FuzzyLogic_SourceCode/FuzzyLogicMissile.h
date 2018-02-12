/******************************************************************************/
/*!
\file FuzzyLogicMissile.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #04
\date 29/03/2012
\brief
This is the class that contains the Fuzzy Logic algorithm

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#ifndef _FUZZYLOGICTEST_H_
#define _FUZZYLOGICTEST_H_

#include "../MotionPlanning_Project/MathUtility.h"


namespace
{
	const float PLANE_RADIUS = 8.0F;
	const float WORLD_SCALE = 0.02F;
	const unsigned ATTACK_OFFSET = 10;
	const unsigned LOW_ATTACK_STARTING_VAL = 10;
	const unsigned MEDIUM_ATTACK_STARTING_VAL = 50;
	const unsigned HIGH_ATTACK_STARTING_VAL = 80;
	const unsigned LOW_ATTACK_MEMBERS = 4;
	const unsigned MEDIUM_ATTACK_MEMBERS = 3;
	const unsigned HIGH_ATTACK_MEMBERS = 3;
	const unsigned TOTAL_ATTACK_MEMBERS = LOW_ATTACK_MEMBERS + MEDIUM_ATTACK_MEMBERS + HIGH_ATTACK_MEMBERS;	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the Plane struct

\param 

\return
*/
/******************************************************************************/
struct Plane
{
	Plane();

	Vector2D m_direction;
	float m_speed;
	Point2D m_position;
	float m_radius;

	Vector2D m_vecBetwnPlaneAndMissile;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the Missile struct

\param 

\return
*/
/******************************************************************************/
struct Missile
{
	Missile();

	Vector2D m_direction;
	float m_speed;
	Point2D m_position;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the FuzzyLogic_Missile class

\param 

\return
*/
/******************************************************************************/
class FuzzyLogic_Missile
{
public:
	FuzzyLogic_Missile( float fuel );
	~FuzzyLogic_Missile();

	float GetDeltaAngle( float angle );
	void UpdateCorrection( Missile * missile, Plane * plane );

	void CalculateAttackRate();

	//get values
	float GetFuelValue();
	float GetDamageValue();
	float GetAttackValue();

	void SetCorrectedDamageValue( float dm );
	void SetFuelValue( float fuel );

	//added by Oliver Chong - April 1, 2012
	void SetDamageValue( float damageVal );
	void SetAttackValue( float attackVal );

private:
	//added by Oliver Chong - April 1, 2012
	enum MISSILE_ROTATION
	{
		EXTREME_LEFT = 15,
		FAR_LEFT = 8,
		LEFT = 2,
		CENTER = 1,
		RIGHT = -2,
		FAR_RIGHT = -8,
		EXTREME_RIGHT = -15
	};
	//end - added by Oliver Chong - April 1, 2012


	float m_fuel;
	float m_damage;
	float m_attack;

	float ExtremeLeft( float angle );
	float FarLeft( float angle );
	float Left( float angle );
	float Center( float angle );
	float Right( float angle );
	float FarRight( float angle );
	float ExtremeRight( float angle );

	float Fuel_Low( float fl );
	float Fuel_Medium( float fl );
	float Fuel_High( float fl );
	float Damage_Low( float dm );
	float Damage_High( float dm );
	float Attack_Low( float at );
	float Attack_Medium( float at );
	float Attack_High( float at );

	//added by Oliver Chong - April 1, 2012
	//helper functions
	float EvaluateTriangle( const float value, const float leftLowerBoundVal, const float upperBoundVal, const float rightLowerBoundVal ) const;
	float EvaluateTrapezoid( const float value, const float leftLowerBoundVal, const float leftUpperBoundVal, 
		const float rightUpperBoundVal, const float rightLowerBoundVal ) const;
	float EvaluateLeftShoulderTrapezoid( const float value, const float upperBoundVal, const float lowerBoundVal ) const;
	float EvaluateRightShoulderTrapezoid( const float value, const float lowerBoundVal, const float upperBoundVal ) const;	
};

#endif