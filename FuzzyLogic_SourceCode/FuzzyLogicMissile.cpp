/******************************************************************************/
/*!
\file FuzzyLogicMissile.cpp
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


#include "FuzzyLogicMissile.h"

#include <iostream>
#include <iomanip>



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the Plane struct

\param 

\return
*/
/******************************************************************************/
Plane::Plane()
{
	this->m_direction = Vector2D();
	this->m_speed = 0;
	this->m_position.x=0;
	this->m_position.y=0;
	this->m_radius = PLANE_RADIUS;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the Missile struct

\param 

\return
*/
/******************************************************************************/
Missile::Missile()
{
	this->m_direction = Vector2D();
	this->m_speed = 0;
	this->m_position.x=0;
	this->m_position.y=0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor of the FuzzyLogic_Missile class

\param fuel
the amount of fuel for the missle

\return
*/
/******************************************************************************/
FuzzyLogic_Missile::FuzzyLogic_Missile( float fuel )
{
	this->m_fuel = fuel;
	this->m_damage = 0.0f;
	this->m_attack = 0.0f;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the destructor of the FuzzyLogic_Missile class

\param

\return
*/
/******************************************************************************/
FuzzyLogic_Missile::~FuzzyLogic_Missile()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This computes the delta angle based on fuzzy logic with the current angle as input

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the delta angle
*/
/******************************************************************************/
float FuzzyLogic_Missile::GetDeltaAngle( float angle )
{
	float deltaAngle = 0.0F;

	float degOfMship1 = 0.0F;
	float degOfMship2 = 0.0F;
	MISSILE_ROTATION missileRot1 = CENTER;
	MISSILE_ROTATION missileRot2 = CENTER;

	//EXTREME_LEFT
	float degOfMshipExtremeLeft = this->ExtremeLeft( angle );
	if ( FloatValueSame( degOfMshipExtremeLeft, 0.0F ) == false )
	{
		degOfMship1 = degOfMshipExtremeLeft;
		missileRot1 = EXTREME_LEFT;
	}

	//FAR_LEFT
	float degOfMshipFarLeft = this->FarLeft( angle );
	if ( FloatValueSame( degOfMshipFarLeft, 0.0F ) == false )
	{
		if ( FloatValueSame( degOfMship1, 0.0F ) )
		{
			degOfMship1 = degOfMshipFarLeft;
			missileRot1 = FAR_LEFT;
		}
		else
		{
			degOfMship2 = degOfMshipFarLeft;
			missileRot2 = FAR_LEFT;
		}
	}

	//LEFT
	float degOfMshipLeft = this->Left( angle );
	if ( FloatValueSame( degOfMshipLeft, 0.0F ) == false )
	{
		if ( FloatValueSame( degOfMship1, 0.0F ) )
		{
			degOfMship1 = degOfMshipLeft;
			missileRot1 = LEFT;
		}
		else
		{
			degOfMship2 = degOfMshipLeft;
			missileRot2 = LEFT;
		}
	}

	//CENTER
	float degOfMshipCenter = this->Center( angle );
	if ( FloatValueSame( degOfMshipCenter, 0.0F ) == false )
	{
		if ( FloatValueSame( degOfMship1, 0.0F ) )
		{
			degOfMship1 = degOfMshipCenter;
			missileRot1 = CENTER;
		}
		else
		{
			degOfMship2 = degOfMshipCenter;
			missileRot2 = CENTER;
		}
	}

	//RIGHT
	float degOfMshipRight = this->Right( angle );
	if ( FloatValueSame( degOfMshipRight, 0.0F ) == false )
	{
		if ( FloatValueSame( degOfMship1, 0.0F ) )
		{
			degOfMship1 = degOfMshipRight;
			missileRot1 = RIGHT;
		}
		else
		{
			degOfMship2 = degOfMshipRight;
			missileRot2 = RIGHT;
		}
	}

	//FAR_RIGHT
	float degOfMshipFarRight = this->FarRight( angle );
	if ( FloatValueSame( degOfMshipFarRight, 0.0F ) == false )
	{
		if ( FloatValueSame( degOfMship1, 0.0F ) )
		{
			degOfMship1 = degOfMshipFarRight;
			missileRot1 = FAR_RIGHT;
		}
		else
		{
			degOfMship2 = degOfMshipFarRight;
			missileRot2 = FAR_RIGHT;
		}
	}

	//EXTREME_RIGHT
	float degOfMshipExtremeRight = this->ExtremeRight( angle );
	if ( FloatValueSame( degOfMshipExtremeRight, 0.0F ) == false )
	{
		if ( FloatValueSame( degOfMship1, 0.0F ) )
		{
			degOfMship1 = degOfMshipExtremeRight;
			missileRot1 = EXTREME_RIGHT;
		}
		else
		{
			degOfMship2 = degOfMshipExtremeRight;
			missileRot2 = EXTREME_RIGHT;
		}
	}

	//validate if it belongs to two fuzzy sets
	if ( FloatValueSame( degOfMship1, 0.0F ) == false && FloatValueSame( degOfMship2, 0.0F ) == false )
	{
		//use the one that belongs to two fuzzy sets by getting the minimum
		if ( degOfMship1 < degOfMship2 )
		{
			deltaAngle = degOfMship1 * missileRot1;
		}
		else
		{
			deltaAngle = degOfMship2 * missileRot2;
		}

		//debug
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "///////////////////////////////////////////////////" << std::endl;
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "angle : " << angle << std::endl;
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "degOfMship1 : " << degOfMship1 << " missileRot1 : " << missileRot1 << std::endl;
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "degOfMship2 : " << degOfMship2 << " missileRot2 : " << missileRot2 << std::endl;
	}
	else
	{
		deltaAngle = degOfMship1 * missileRot1;
		//debug
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "///////////////////////////////////////////////////" << std::endl;
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "angle : " << angle << std::endl;
		//std::cout << std::setfill (' ') << std::setw( 0 ) << "degOfMship1 : " << degOfMship1 << " missileRot1 : " << missileRot1 << std::endl;
	}


	return deltaAngle;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function takes as input the missile and plane objects.
Calculates the current angle from their vector directions.
Calls GetDeltaAngle() function to get deltaAngle value.
Updates the missile’s direction based on the new angle.

\param missile
the pointer to the missile
\param

the pointer to the plane

\return
*/
/******************************************************************************/
void FuzzyLogic_Missile::UpdateCorrection( Missile * missile, Plane * plane )
{
	//debug
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "=============================================================================" << std::endl;
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "plane x : " << plane->m_position.x << " y: " << plane->m_position.y << std::endl;
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "missile x : " << missile->m_position.x << " y: " << missile->m_position.y << std::endl;

	//get the vector between the plane and the missile
	Vector2D vecBetwnPlaneAndMissile = ComputeVector( plane->m_position, missile->m_position );
	vecBetwnPlaneAndMissile = NormalizeVector( vecBetwnPlaneAndMissile );
	plane->m_vecBetwnPlaneAndMissile = vecBetwnPlaneAndMissile;

	//debug
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "missile direction x : " << missile->m_direction.x << " y: " << missile->m_direction.y << std::endl;
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "vecBetwnPlaneAndMissile x : " << vecBetwnPlaneAndMissile.x << " y : " << vecBetwnPlaneAndMissile.y << std::endl;

	//compute the current angle between the vector of the missile and the vector between the object and the missile
	float angleDegrees = ComputeAngleDegreesBetweenTwoVectors( missile->m_direction, vecBetwnPlaneAndMissile );

	//perform a cross product so we can tell if the missile is to the left or to the right
	Vector3D vecOrtho = CrossProduct( missile->m_direction, vecBetwnPlaneAndMissile );
	//if the z-component of the resulting vector from the cross product is negative
	if ( FloatValueSame( vecOrtho.z, 0.0F ) == false && vecOrtho.z < 0.0F ) 
	{
		//negate the angle
		angleDegrees = -angleDegrees;
	}

	//compute the delta angle
	float deltaAngle = 0.0F;
	deltaAngle = this->GetDeltaAngle( angleDegrees );
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "deltaAngle : " << deltaAngle << std::endl;

	//update the missile direction based on the delta angle and the attack rate
	float computedDeltaAngle = deltaAngle * ( this->m_attack / 100.0F );
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "computedDeltaAngle : " << computedDeltaAngle << std::endl;
	angleDegrees += computedDeltaAngle;

	const float cosVal = std::cosf( DegreeToRadian( -computedDeltaAngle ) );
	const float sinVal = std::sinf( DegreeToRadian( -computedDeltaAngle ) );
	//the rotation matrix approach is used so the rotation will be with respect to the direction of the missile
	missile->m_direction.x = ( cosVal * missile->m_direction.x ) + ( -sinVal * missile->m_direction.y );
	missile->m_direction.y = ( sinVal * missile->m_direction.x ) + ( cosVal * missile->m_direction.y );
	//normalize the direction
	missile->m_direction = NormalizeVector( missile->m_direction );	

	/*
	//update the missile direction based on the delta angle
	angleDegrees += deltaAngle;// * this->m_attack;
	missile->m_direction.x = std::cosf( DegreeToRadian( angleDegrees ) );
	missile->m_direction.y = std::sinf( DegreeToRadian( angleDegrees ) );	
	*/

	//debug
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "angleDegrees : " << angleDegrees << std::endl;	
}


//Fuzzy MemberShip functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the extreme left area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::ExtremeLeft( float angle )
{
	float degOfMship = this->EvaluateLeftShoulderTrapezoid( angle, -100.0F, -90.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the far left area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::FarLeft( float angle )
{
	float degOfMship = this->EvaluateTrapezoid( angle, -100.0F, -90.0F, -25.0F, -15.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the left area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Left( float angle )
{
	float degOfMship = this->EvaluateTrapezoid( angle, -25.0F, -15.0F, -10.0F, 0.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the center area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Center( float angle )
{
	float degOfMship = this->EvaluateTriangle( angle, -10.0F, 0.0F, 10.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the right area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Right( float angle )
{
	float degOfMship = this->EvaluateTrapezoid( angle, 0.0F, 10.0F, 15.0F, 25.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the far right area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::FarRight( float angle )
{
	float degOfMship = this->EvaluateTrapezoid( angle, 15.0F, 25.0F, 90.0F, 100.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of the missile in the extreme right area

\param angle
the current angle between the vector of the missile and the vector between the object and the missile

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::ExtremeRight( float angle )
{
	float degOfMship = this->EvaluateRightShoulderTrapezoid( angle, 90.0F, 100.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of low fuel level

\param fl
the current fuel level

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Fuel_Low( float fl )
{
	float degOfMship = this->EvaluateLeftShoulderTrapezoid( fl, 30.0F, 40.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of medium fuel level

\param fl
the current fuel level

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Fuel_Medium( float fl )
{
	float degOfMship = this->EvaluateTrapezoid( fl, 30.0F, 40.0F, 70.0F, 80.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of high fuel level

\param fl
the current fuel level

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Fuel_High( float fl )
{
	float degOfMship = this->EvaluateRightShoulderTrapezoid( fl, 70.0F, 80.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of low damage level

\param dm
the current damage level

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Damage_Low( float dm )
{
	float degOfMship = this->EvaluateLeftShoulderTrapezoid( dm, 35.0F, 50.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the degree of membership of high damage level

\param dm
the current damage level

\return float
the degree of membership
*/
/******************************************************************************/
float FuzzyLogic_Missile::Damage_High( float dm )
{
	float degOfMship = this->EvaluateRightShoulderTrapezoid( dm, 40.0F, 60.0F );
	return degOfMship;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the sum of the low attack level based on the maximum mask value for the attack level degree of membership

\param at
the maximum mask value for the attack level degree of membership

\return float
the sum for this fuzzy set area
*/
/******************************************************************************/
float FuzzyLogic_Missile::Attack_Low( float at )
{
	//float degOfMship = this->EvaluateLeftShoulderTrapezoid( at, 30.0F, 50.0F );

	float sumOfFuzzyAreaSet = 0.0F;

	for ( unsigned index = 0; index < LOW_ATTACK_MEMBERS; ++index )
	{
		sumOfFuzzyAreaSet += at * ( LOW_ATTACK_STARTING_VAL + ( index * ATTACK_OFFSET ) );
	}//end for loop

	return sumOfFuzzyAreaSet;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the sum of the medium attack level based on the maximum mask value for the attack level degree of membership

\param at
the maximum mask value for the attack level degree of membership

\return float
the sum for this fuzzy set area
*/
/******************************************************************************/
float FuzzyLogic_Missile::Attack_Medium( float at )
{
	//float degOfMship = this->EvaluateTrapezoid( at, 40.0F, 60.0F, 70.0F, 80.0F );

	float sumOfFuzzyAreaSet = 0.0F;

	for ( unsigned index = 0; index < MEDIUM_ATTACK_MEMBERS; ++index )
	{
		sumOfFuzzyAreaSet += at * ( MEDIUM_ATTACK_STARTING_VAL + ( index * ATTACK_OFFSET ) );
	}//end for loop

	return sumOfFuzzyAreaSet;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the sum of the high attack level based on the maximum mask value for the attack level degree of membership

\param at
the maximum mask value for the attack level degree of membership

\return float
the sum for this fuzzy set area
*/
/******************************************************************************/
float FuzzyLogic_Missile::Attack_High( float at )
{
	//float degOfMship = this->EvaluateRightShoulderTrapezoid( at, 70.0F, 85.0F );

	float sumOfFuzzyAreaSet = 0.0F;

	for ( unsigned index = 0; index < HIGH_ATTACK_MEMBERS; ++index )
	{
		sumOfFuzzyAreaSet += at * ( HIGH_ATTACK_STARTING_VAL + ( index * ATTACK_OFFSET ) );
	}//end for loop

	return sumOfFuzzyAreaSet;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
It gradually changes the damage value when entering/leaving a city’s area.

\param dm
the damage value

\return
*/
/******************************************************************************/
void FuzzyLogic_Missile::SetCorrectedDamageValue( float dm )
{
	this->m_damage = this->m_damage + (dm - this->m_damage) / 20.0f;//delta = 20.0f -> gradually changing the value
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function calculates the final “m_attack” fuzzy value that should be used as described earlier.
Based on “m_damage” and “m_fuel” current values, this function apply the inference system to calculate “m_attack” value.
It uses the rules of the problem to do the Fuzzification, Evaluation, Clipping, Aggregation and DeFuzzification steps.
“m_attack” calculated will be a percentage value (a value between 0 and 1).

\param

\return
*/
/******************************************************************************/
void FuzzyLogic_Missile::CalculateAttackRate()
{
	float highAttackSum = 0.0F;
	float mediumAttackSum = 0.0F;
	float lowAttackSum = 0.0F;

	float highAttackMaskVal = 0.0F;
	float mediumAttackMaskVal = 0.0F;
	float lowAttackMaskVal = 0.0F;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//If Fuel Low OR Damage Low then Attack High
	float fuelDegOfMship = this->Fuel_Low( this->m_fuel );
	float damageDegOfMship = this->Damage_Low( this->m_damage );
	highAttackMaskVal = std::max( fuelDegOfMship, damageDegOfMship );
	if ( FloatValueSame( highAttackMaskVal, 0.0F ) == false )
	{
		highAttackSum = this->Attack_High( highAttackMaskVal );
	}

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "///////////////////////////////////////////////////" << std::endl;
	//std::cout << std::setfill (' ') << std::setw( 0 ) << "highAttackMaskVal : " << highAttackMaskVal << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//If Fuel Medium AND Damage High then Attack Medium
	fuelDegOfMship = this->Fuel_Medium( this->m_fuel );
	damageDegOfMship = this->Damage_High( this->m_damage );
	mediumAttackMaskVal = std::min( fuelDegOfMship, damageDegOfMship );
	if ( FloatValueSame( mediumAttackMaskVal, 0.0F ) == false )
	{
		mediumAttackSum = this->Attack_Medium( mediumAttackMaskVal );
	}

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "mediumAttackMaskVal : " << mediumAttackMaskVal << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//If Fuel High AND Damage High then Attack Low
	fuelDegOfMship = this->Fuel_High( this->m_fuel );
	damageDegOfMship = this->Damage_High( this->m_damage );
	lowAttackMaskVal = std::min( fuelDegOfMship, damageDegOfMship );
	if ( FloatValueSame( lowAttackMaskVal, 0.0F ) == false )
	{
		lowAttackSum = this->Attack_Low( lowAttackMaskVal );
	}

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "lowAttackSum : " << lowAttackSum << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//compute the weighted average through the Mamdani method
	float denominator = ( HIGH_ATTACK_MEMBERS * highAttackMaskVal ) + ( MEDIUM_ATTACK_MEMBERS * mediumAttackMaskVal ) + ( LOW_ATTACK_MEMBERS * lowAttackMaskVal );
	float weightedAve = ( highAttackSum + mediumAttackSum + lowAttackSum ) / denominator;
	//normalize the weighted average so it can be used as the attack fuzzy value
	//this->m_attack = weightedAve / 100.0F;
	this->m_attack = weightedAve;

	//std::cout << std::setfill (' ') << std::setw( 0 ) << "weightedAve : " << weightedAve << std::endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Get the fuel value

\param

\return float
the fuel value
*/
/******************************************************************************/
float FuzzyLogic_Missile::GetFuelValue()
{
	return this->m_fuel;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Get the damage value

\param

\return float
the damage value
*/
/******************************************************************************/
float FuzzyLogic_Missile::GetDamageValue()
{
	return this->m_damage;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Get the attack value

\param

\return float
the attack value
*/
/******************************************************************************/
float FuzzyLogic_Missile::GetAttackValue()
{
	return this->m_attack;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Sets the fuel value

\param fuel
the fuel of the missile

\return
*/
/******************************************************************************/
void FuzzyLogic_Missile::SetFuelValue( float fuel )
{
	this->m_fuel = fuel;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Sets the current damage value

\param damageVal
the current damage value

\return
*/
/******************************************************************************/
void FuzzyLogic_Missile::SetDamageValue( float damageVal )
{
	this->m_damage = damageVal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Sets the current attack value

\param attackVal
the current attack value

\return
*/
/******************************************************************************/
void FuzzyLogic_Missile::SetAttackValue( float attackVal )
{
	this->m_attack = attackVal;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Evaluates the value in the triangle fuzzy set area

\param value
the value to be evaluated
\param leftLowerBoundVal
the left lower bound value
\param upperBoundVal
the upper bound value
\param rightLowerBoundVal
the right lower bound value

\return float
the evaluated value
*/
/******************************************************************************/
float FuzzyLogic_Missile::EvaluateTriangle( const float value, const float leftLowerBoundVal, const float upperBoundVal, const float rightLowerBoundVal ) const
{
	float evaluatedValue = 0.0F;

	//out of bounds
	if ( value <= leftLowerBoundVal )
	{
		evaluatedValue = 0.0F;
	}
	//ascend
	else if ( ( value > leftLowerBoundVal ) && ( value <= upperBoundVal ) )
	{
		evaluatedValue = ( value - leftLowerBoundVal ) / ( upperBoundVal - leftLowerBoundVal );
	}
	//descend
	else if ( ( value > upperBoundVal ) && ( value <= rightLowerBoundVal ) )
	{
		evaluatedValue = ( value - rightLowerBoundVal ) / ( upperBoundVal - rightLowerBoundVal );
	}
	//out of bounds
	else if ( value > rightLowerBoundVal )
	{
		evaluatedValue = 0.0F;
	}

	return evaluatedValue;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Evaluates the value in the trapezoid fuzzy set area

\param value
the value to be evaluated
\param leftLowerBoundVal
the left lower bound value
\param leftUpperBoundVal
the left upper bound value
\param rightLowerBoundVal
the right lower bound value
\param rightUpperBoundVal
the right upper bound value

\return float
the evaluated value
*/
/******************************************************************************/
float FuzzyLogic_Missile::EvaluateTrapezoid( const float value, const float leftLowerBoundVal, const float leftUpperBoundVal, 
	const float rightUpperBoundVal, const float rightLowerBoundVal ) const
{
	float evaluatedValue = 0.0F;
	
	//out of bounds
	if ( value <= leftLowerBoundVal )
	{
		evaluatedValue = 0.0F;
	}
	//ascend
	else if ( ( value > leftLowerBoundVal ) && ( value <= leftUpperBoundVal ) )
	{
		evaluatedValue = ( value - leftLowerBoundVal ) / ( leftUpperBoundVal - leftLowerBoundVal );
	}
	//flat
	else if ( ( value > leftUpperBoundVal ) && ( value <= rightUpperBoundVal ) )
	{
		evaluatedValue = 1.0F;
	}
	//descend
	else if ( ( value > rightUpperBoundVal ) && ( value <= rightLowerBoundVal ) )
	{
		evaluatedValue = ( value - rightLowerBoundVal ) / ( rightUpperBoundVal - rightLowerBoundVal );
	}
	//out of bounds
	else if ( value > rightLowerBoundVal )
	{
		evaluatedValue = 0.0F;
	}

	return evaluatedValue;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Evaluates the value in the left shoulder trapezoid fuzzy set area

\param value
the value to be evaluated
\param lowerBoundVal
the lower bound value
\param upperBoundVal
the upper bound value

\return float
the evaluated value
*/
/******************************************************************************/
float FuzzyLogic_Missile::EvaluateLeftShoulderTrapezoid( const float value, const float upperBoundVal, const float lowerBoundVal ) const
{
	float evaluatedValue = 0.0F;

	//infinite flat
	if ( value <= upperBoundVal )
	{
		evaluatedValue = 1.0F;
	}	
	//descend
	else if ( ( value > upperBoundVal ) && ( value <= lowerBoundVal ) )
	{
		evaluatedValue = ( value - lowerBoundVal ) / ( upperBoundVal - lowerBoundVal );
	}
	//out of bounds
	else if ( value > lowerBoundVal )
	{
		evaluatedValue = 0.0F;
	}

	return evaluatedValue;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Evaluates the value in the right shoulder trapezoid fuzzy set area

\param value
the value to be evaluated
\param lowerBoundVal
the lower bound value
\param upperBoundVal
the upper bound value

\return float
the evaluated value
*/
/******************************************************************************/
float FuzzyLogic_Missile::EvaluateRightShoulderTrapezoid( const float value, const float lowerBoundVal, const float upperBoundVal ) const
{
	float evaluatedValue = 0.0F;
	
	//out of bounds
	if ( value <= lowerBoundVal )
	{
		evaluatedValue = 0.0F;
	}	
	//ascend
	else if ( ( value > lowerBoundVal ) && ( value <= upperBoundVal ) )
	{
		evaluatedValue = ( value - lowerBoundVal ) / ( upperBoundVal - lowerBoundVal );
	}
	//infinite flat
	else if ( value > upperBoundVal )
	{
		evaluatedValue = 1.0F;
	}

	return evaluatedValue;
}