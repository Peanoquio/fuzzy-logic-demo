/******************************************************************************/
/*!
\file CollisionResponse.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 14/01/2012
\brief
This will contain functions for collision response

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "CollisionResponse.h"


namespace PhysicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is to set the collision response of the circle bouncing off the surface of a wall
	\param wallNormal
	the normal of the wall
	\param circle
	the circle game object
	\param circleEndPosition
	the end position of the circle
	\param circleIntersectPosition
	the position where the circle intersects the wall
	\return
	*/
	/******************************************************************************/
	void CollisionResponse::SetReflectionCircleFromWall( const float /*collisionDt*/, const Math::Vector4 & wallNormal, GameFramework::GameObject & circle,
		const Math::Vector4 & circleEndPosition, const Math::Vector4 & circleIntersectPosition  ) const
	{
		//get the vector from the point of the intersection to the ending position of the circle
		Math::Vector4 circleIntersectionVec = circleEndPosition - circleIntersectPosition;

		//reflection formula: i - 2(i . n) * n
		Math::Vector4 circleReflectionVec = circleIntersectionVec - ( 2.0F * ( circleIntersectionVec.Dot( wallNormal ) * wallNormal ) );

		//set the reflection vector as the new velocity of the circle
		circle.GetPhysicsObj().SetVelocity( circleReflectionVec );
		circle.GetPhysicsObj().SetDirection( circleReflectionVec.GetNormalized() );
		//circle.GetPhysicsObj().SetPosition( circleIntersectPosition + ( circleReflectionVec * collisionDt ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is to set the collision response of the circle bouncing off the surface of a circular pillar
	\param circle
	the circle game object
	\param circleStartPosition
	the starting position of the circle
	\param circleIntersectPosition
	the position where the circle intersects the circular pillar
	\param circlePillarStartPosition
	the starting position of the circle pillar
	\return
	*/
	/******************************************************************************/
	void CollisionResponse::SetReflectionCircleFromCirclePillar( const float /*collisionDt*/, GameFramework::GameObject & circle,
		const Math::Vector4 & circleStartPosition, const Math::Vector4 & circleIntersectPosition, const Math::Vector4 & circlePillarStartPosition ) const
	{
		//n
		//compute for the normal of the circle pillar
		Math::Vector4 circlePillarNormal = circleIntersectPosition - circlePillarStartPosition;
		Math::Vector4 circlePillarNormalNormalized = circlePillarNormal.GetNormalized();
		
		//m
		//compute for the vector from the point of intersection on the pillar to the start position of the circle
		Math::Vector4 circInterToCircStartPosVec = circleStartPosition - circleIntersectPosition;

		//set the collision response
		//reflection formula: 2 * ( m . n ) * n - m
		Math::Vector4 circleReflectionVec = 2.0F * circInterToCircStartPosVec.Dot( circlePillarNormalNormalized ) 
			* circlePillarNormalNormalized - circInterToCircStartPosVec;

		//set the reflection vector as the new velocity of the circle
		circle.GetPhysicsObj().SetVelocity( circleReflectionVec );
		circle.GetPhysicsObj().SetDirection( circleReflectionVec.GetNormalized() );
		//circle.GetPhysicsObj().SetPosition( circleIntersectPosition + ( circleReflectionVec * collisionDt ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is to set the collision response of two circles bouncing off each other
	\param circleFrom
	the circle game object
	\param circleFromIntersectPosition
	the intersection position of the circle
	\param circleTo
	the circle game object
	\param circleToIntersectPosition
	the intersection position of the circle
	\return
	*/
	/******************************************************************************/
	void CollisionResponse::SetReflectionCircleFromCircle( const float /*collisionDt*/, 
		GameFramework::GameObject & circleFrom, const Math::Vector4 & circleFromIntersectPosition,
		GameFramework::GameObject & circleTo, const Math::Vector4 & circleToIntersectPosition ) const
	{
		//get the values of the circles
		Math::Vector4 circleFromComputedVelocity = circleFrom.GetPhysicsObj().GetDirection() * circleFrom.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleToComputedVelocity = circleTo.GetPhysicsObj().GetDirection() * circleTo.GetPhysicsObj().GetMovementSpeed();
		float circleFromMass = circleFrom.GetPhysicsObj().GetMass();
		float circleToMass = circleFrom.GetPhysicsObj().GetMass();

		//get the normalized vector between the start positions of the two circles
		Math::Vector4 circleDistanceVectorNormalized = ( circleFromIntersectPosition - circleToIntersectPosition ).GetNormalized();
		//get the perpendicular to the normalized distance
		Math::Vector4 circleDistancePerpVectorNormalized;
		circleDistancePerpVectorNormalized.SetFloatX( -circleDistanceVectorNormalized.GetFloatY() );
		circleDistancePerpVectorNormalized.SetFloatY( circleDistanceVectorNormalized.GetFloatX() );

		//get the projection magnitude of the circle velocity to the distance vector
		float circleFromVelocityProjMagnitude = circleFromComputedVelocity.Dot( circleDistanceVectorNormalized );
		//float circleFromVelocityProjMagnitudePerp = circleFromComputedVelocity.Dot( circleDistancePerpVectorNormalized );
		float circleToVelocityProjMagnitude = circleToComputedVelocity.Dot( circleDistanceVectorNormalized );
		//float circleToVelocityProjMagnitudePerp = circleToComputedVelocity.Dot( circleDistancePerpVectorNormalized );

		//kinetic energy: E = 1/2 * mass * velocity ^ 2
		//law of conservation of kinetic energy
		float momentumVectorMagnitude = ( 2.0F * circleFromMass * circleToMass * ( circleFromVelocityProjMagnitude - circleToVelocityProjMagnitude ) ) 
			/ ( circleFromMass + circleToMass );

		//compute for the change in velocity due to collision
		Math::Vector4 circleFromChangedVelocity = circleFromComputedVelocity - ( momentumVectorMagnitude / circleFromMass ) * circleDistanceVectorNormalized;
		Math::Vector4 circleFromChangedVelocityNormalized = circleFromChangedVelocity.GetNormalized();
		Math::Vector4 circleToChangedVelocity = circleToComputedVelocity + ( momentumVectorMagnitude / circleToMass ) * circleDistanceVectorNormalized;
		Math::Vector4 circleToChangedVelocityNormalized = circleToChangedVelocity.GetNormalized();

		//compute for the change in speed due to collision
		float circleFromNewSpeed = circleFromChangedVelocity.Length();
		float circleToNewSpeed = circleToChangedVelocity.Length();


		//set the reflection vector as the new velocity of the circle
		circleFrom.GetPhysicsObj().SetVelocity( circleFromChangedVelocity );
		circleFrom.GetPhysicsObj().SetDirection( circleFromChangedVelocityNormalized );
		//circleFrom.GetPhysicsObj().SetPosition( circleFromIntersectPosition + ( circleFromChangedVelocity * collisionDt ) );
		circleFrom.GetPhysicsObj().SetMovementSpeed( circleFromNewSpeed );

		//set the reflection vector as the new velocity of the circle
		circleTo.GetPhysicsObj().SetVelocity( circleToChangedVelocity );
		circleTo.GetPhysicsObj().SetDirection( circleToChangedVelocityNormalized );
		//circleTo.GetPhysicsObj().SetPosition( circleToIntersectPosition + ( circleToChangedVelocity * collisionDt ) );
		circleTo.GetPhysicsObj().SetMovementSpeed( circleToNewSpeed );
	}

}//end namespace PhysicsFramework