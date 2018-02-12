/******************************************************************************/
/*!
\file CollisionDetection.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 10/01/2012
\brief
This will contain functions for collision detection

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "CollisionDetection.h"
#include "CollisionResponse.h"


namespace PhysicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate if the circle collides with another circle
	\param startTime
	the start time of the frame
	\param dt
	the elapsed time of the frame
	\param collisionDt
	the elapsed time between the time of collision and the end time of the frame
	\param circleFrom
	the circle game object
	\param circleTo
	the circle game object
	\return bool
	if true, there is collision, otherwise false
	*/
	/******************************************************************************/
	const bool CollisionDetection::CheckCollisionCircleToCircle( const float startTime, const float dt, float & collisionDt,
		GameFramework::GameObject & circleFrom, GameFramework::GameObject & circleTo ) const
	{
		bool collideFlag = false;

		//time values
		const float endTime = startTime + dt;
		float timeIntersect = 0.0F;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//values of the circle
		//Math::Vector4 circleFromComputedVelocity = circleFrom.GetPhysicsObj().GetVelocity() * circleFrom.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleFromComputedVelocity = circleFrom.GetPhysicsObj().GetDirection() * circleFrom.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleFromStartPosition = circleFrom.GetPhysicsObj().GetPosition();
		Math::Vector4 circleFromEndPosition = circleFromStartPosition + circleFromComputedVelocity * dt;
		float circleFromRadius = circleFrom.GetPhysicsObj().GetScale().GetFloatX() / 2.0F;

		//valus of the other circle
		Math::Vector4 circleToComputedVelocity = circleTo.GetPhysicsObj().GetVelocity() * circleTo.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleToStartPosition = circleTo.GetPhysicsObj().GetPosition();
		Math::Vector4 circleToEndPosition = circleToStartPosition + circleToComputedVelocity * dt;
		float circleToRadius = circleTo.GetPhysicsObj().GetScale().GetFloatX() / 2.0F;

		//computed values of the two circles		
		float radiusSum = circleFromRadius + circleToRadius;

		//subtract the velocity of the other circle from both the circles
		//this is to simplify the problem by making the circleFrom animated while circleTo stationary
		Math::Vector4 circleFromComputedVelocityRevised = circleFromComputedVelocity - circleToComputedVelocity;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//test for circle to circular pillar collision and compute for the intersection time
		if ( this->IsCircleCollidingWithCirclePillar( timeIntersect, startTime, endTime,
			radiusSum, circleFromComputedVelocityRevised, circleFromStartPosition, circleToStartPosition ) == true )
		{
			collideFlag = true;

			//compute for the collision frame time
			collisionDt = endTime - ( startTime + timeIntersect );

			//compute for the point of intersection of the two circles
			Math::Vector4 circleFromIntersectPosition = circleFromStartPosition + ( circleFromComputedVelocity * timeIntersect );
			Math::Vector4 circleToIntersectPosition = circleToStartPosition + ( circleToComputedVelocity * timeIntersect );

			//set the collision response
			CollisionResponse collisionResponse;
			collisionResponse.SetReflectionCircleFromCircle( collisionDt, circleFrom, circleFromIntersectPosition, circleTo, circleToIntersectPosition );
		}

		return collideFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate if the circle collides with a circular pillar
	\param startTime
	the start time of the frame
	\param dt
	the elapsed time of the frame
	\param collisionDt
	the elapsed time between the time of collision and the end time of the frame
	\param circle
	the circle game object
	\param circlePillar
	the circle pillar game object
	\return bool
	if true, there is collision, otherwise false
	*/
	/******************************************************************************/
	const bool CollisionDetection::CheckCollisionCircleToCirclePillar( const float startTime, const float dt, float & collisionDt,
		GameFramework::GameObject & circle, GameFramework::GameObject & circlePillar ) const
	{
		bool collideFlag = false;

		//time values
		const float endTime = startTime + dt;
		float timeIntersect = 0.0F;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//values of the first circle
		//Math::Vector4 circleComputedVelocity = circle.GetPhysicsObj().GetVelocity() * circle.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleComputedVelocity = circle.GetPhysicsObj().GetDirection() * circle.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleStartPosition = circle.GetPhysicsObj().GetPosition();
		//Math::Vector4 circleEndPosition = circleStartPosition + circleComputedVelocity * dt;
		float radius = circle.GetPhysicsObj().GetScale().GetFloatX() / 2.0F;

		//value of the circle pillar
		Math::Vector4 circlePillarStartPosition = circlePillar.GetPhysicsObj().GetPosition();
		float circlePillarRadius = circlePillar.GetPhysicsObj().GetScale().GetFloatX() / 2.0F;

		//computed values of the two circles		
		float radiusSum = radius + circlePillarRadius;	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//test for circle to circular pillar collision and compute for the intersection time
		if ( this->IsCircleCollidingWithCirclePillar( timeIntersect, startTime, endTime,
			radiusSum, circleComputedVelocity, circleStartPosition, circlePillarStartPosition ) == true )
		{
			collideFlag = true;

			//compute for the collision frame time
			collisionDt = endTime - ( startTime + timeIntersect );

			//compute for the position where the circle intersects with the circle pillar
			Math::Vector4 circleIntersectPosition = circleStartPosition + ( circleComputedVelocity * timeIntersect );
			
			//set the collision response
			CollisionResponse collisionResponse;
			collisionResponse.SetReflectionCircleFromCirclePillar( collisionDt, circle, circleStartPosition, circleIntersectPosition, circlePillarStartPosition );
		}

		return collideFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is to detect the collision between a circle and a circular pillar as well as to compute for the time of intersection
	\param intersectionTime
	the time of intersection
	\param frameStartTime
	the starting time of the frame
	\param frameEndTime
	the ending time of the frame	
	\param radiusSum
	the sum of the radius of the two circles
	\param circleComputedVelocity
	the velocity of the moving circle
	\param circleStartPosition
	the start position of the circle
	\param circlePillarStartPosition
	the start position of the circle pillar
	\return
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleCollidingWithCirclePillar( float & intersectionTime, const float frameStartTime, const float frameEndTime, 
		const float radiusSum, const Math::Vector4 & circleComputedVelocity, 
		const Math::Vector4 & circleStartPosition, const Math::Vector4 & circlePillarStartPosition ) const
	{
		bool collideFlag = false;
		float intersectionTimeCompareVal = 0.0F;

		//get the vector between the two circles
		float radiusSumSquared = radiusSum * radiusSum;
		float circleDistanceSquared = circlePillarStartPosition.DistanceSquared( circleStartPosition );
		Math::Vector4 circleDistanceVector = circlePillarStartPosition - circleStartPosition;
		Math::Vector4 circleComputedVelocityNormalized = circleComputedVelocity.GetNormalized();

		//compute for the projection of the vector between the two circles on to the normalized circle velocity
		//vector projection formula : ( u . v ) / (v . v ) * v
		/*
		Math::Vector4 projectionVec = ( circleDistanceVector.Dot( circleComputedVelocity ) 
			/ circleComputedVelocity.Dot( circleComputedVelocity ) ) 
			* circleComputedVelocity;
		*/
		//Math::Vector4 projectionVec = circleDistanceVector.Dot( circleComputedVelocityNormalized ) * circleComputedVelocityNormalized;		
		Math::Vector4 projectionVec = circleDistanceVector.Project( circleComputedVelocityNormalized );

		float projectionVecMagnitudeSquared = projectionVec.LengthSquared();
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//test for non-collision
		//if circle direction is away from the other circle
		//is circle behind ray origin and if circle start position is outside the other circle		 
		if ( circleDistanceVector.Dot( circleComputedVelocityNormalized ) < 0.0F && ( circleDistanceSquared > radiusSumSquared ) )
		{
			collideFlag = false;
		}

		//test for non-collision
		//if circle direction is towards the other circle
		//if the distance between the direction of the moving circle and the position of the other circle is greater than their combined radius
		if ( circleDistanceVector.Dot( circleComputedVelocityNormalized ) > 0.0F 
			&& ( circleDistanceSquared - projectionVecMagnitudeSquared ) > radiusSumSquared )
		{
			collideFlag = false;
		}

		//test for collision
		//if circle direction is towards the other circle
		//if the distance between the direction of the moving circle and the position of the other circle is less than their combined radius
		if ( circleDistanceVector.Dot( circleComputedVelocityNormalized ) > 0.0F 
			&& ( circleDistanceSquared - projectionVecMagnitudeSquared ) < radiusSumSquared )
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
			//METHOD 2 : to get the time of intersection
			// s^2 = r^2 - n^2
			//formula to get the distance from the center of the circle to its edge
			float distanceFromCtrToCircleEdge = std::sqrtf( radiusSumSquared - ( circleDistanceSquared - projectionVecMagnitudeSquared ) );
			float projectionVecMagnitude = std::sqrtf( projectionVecMagnitudeSquared );
			float circleComputedVelocityMagnitude = circleComputedVelocity.Length();

			//compute for the intersection time at the entry point of the circle
			float intersectEntryTime = ( projectionVecMagnitude - distanceFromCtrToCircleEdge ) / circleComputedVelocityMagnitude;
			//compute for the intersection time at the exit point of the circle
			float intersectExitTime = ( projectionVecMagnitude + distanceFromCtrToCircleEdge ) / circleComputedVelocityMagnitude;
			//get the earlier intersection time
			intersectionTime = ( intersectEntryTime < intersectExitTime ) ? intersectEntryTime : intersectExitTime;			

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			intersectionTimeCompareVal = frameStartTime + intersectionTime;
			//compute for the intersection point if the intersection time is within the frame
			//or if intersection time is negative, the ball are overlapping each other
			if ( ( intersectionTimeCompareVal >= frameStartTime && intersectionTimeCompareVal <= frameEndTime )
				/*|| intersectionTime < 0.0F*/ )
			{
				collideFlag = true;
			}
			else
			{
				collideFlag = false;
			}
		}		

		return collideFlag;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This is to detect the collision between a circle and a circular pillar as well as to compute for the time of intersection
	\param intersectionTime
	the time of intersection
	\param frameStartTime
	the starting time of the frame
	\param frameEndTime
	the ending time of the frame	
	\param radiusSum
	the sum of the radius of the two circles
	\param circleComputedVelocity
	the velocity of the moving circle
	\param circleStartPosition
	the start position of the circle
	\param circlePillarStartPosition
	the start position of the circle pillar
	\return
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleCollidingWithCirclePillarQuadraticeEq( float & intersectionTime, const float frameStartTime, const float frameEndTime, 
		const float radiusSum, const Math::Vector4 & circleComputedVelocity, 
		const Math::Vector4 & circleStartPosition, const Math::Vector4 & circlePillarStartPosition ) const
	{
		bool collideFlag = false;
		float intersectionTimeCompareVal = 0.0F;

		Math::Vector4 circlePositionDiff = circlePillarStartPosition - circleStartPosition;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// quadratic formula: ( -B +- sqrt( B^2 - 4AC ) ) / 2A
		// A = circleVelocity . circleVelocity
		float A = circleComputedVelocity.Dot( circleComputedVelocity );
		// B = -2 ( circle2Position - circleStartPosition ) . circleVelocity
		float B = ( -2.0F * circlePositionDiff ).Dot( circleComputedVelocity );
		// C = ( circle2Position - circleStartPosition ) . ( circle2Position - circleStartPosition ) - radius^2
		float C = circlePositionDiff.Dot( circlePositionDiff ) - ( radiusSum * radiusSum );

		//collision test equation B^2 - 4AC
		float collisionTestVal = ( B * B ) - ( 4 * A * C );
		float collisionTestValSqrt = std::sqrtf( collisionTestVal );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// if B^2 - 4AC < 0, ray misses circle
		if ( collisionTestVal < 0.0F )
		{
			collideFlag = false;
		}
		else
		{
			// if B^2 - 4AC = 0, ray grazes circle
			if ( collisionTestVal >= 0.0F && collisionTestVal <= Math::EPSILON )
			{		
				//get the intersection time
				intersectionTime = ( - B / ( 2.0F * A ) );
			}
			// if B^2 - 4AC > 0, ray intersects circle
			else if ( collisionTestVal > 0.0F )
			{
				//METHOD #1 : to get the time of intersection
				//compute for the intersection time at the entry point of the circle
				float intersectEntryTime = ( - B - collisionTestValSqrt ) / ( 2.0F * A );
				//compute for the intersection time at the exit point of the circle
				float intersectExitTime = ( - B + collisionTestValSqrt ) / ( 2.0F * A );
				//get the earlier intersection time
				intersectionTime = ( intersectEntryTime < intersectExitTime ) ? intersectEntryTime : intersectExitTime;
			}

			intersectionTimeCompareVal = frameStartTime + intersectionTime;
			//compute for the intersection point if the intersection time is within the frame
			if ( intersectionTimeCompareVal >= frameStartTime && intersectionTimeCompareVal <= frameEndTime )
			{
				collideFlag = true;
			}
			else
			{
				collideFlag = false;
			}
		}

		return collideFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate if the circle collides with the wall
	\param startTime
	the start time of the frame
	\param dt
	the elapsed time of the frame
	\param collisionDt
	the elapsed time between the time of collision and the end time of the frame
	\param circle
	the circle game object
	\param wall
	the wall game object
	\param checkInwardOutwardDirection
	indicator to check both the inward or outward direction of the ball against the wall
	\param checkOverlap
	indicator whether to check if the ball overlaps the wall
	\return bool
	if true, there is collision, otherwise false
	*/
	/******************************************************************************/
	const bool CollisionDetection::CheckCollisionCircleToWall( const float startTime, const float dt, float & collisionDt,
		GameFramework::GameObject & circle, GameFramework::GameObject & wall, 
		const bool checkInwardOutwardDirection, const bool checkOverlap) const
	{
		bool collideFlag = false;
		const float endTime = startTime + dt;

		Math::Vector4 wallNormal = wall.GetPhysicsObj().GetNormal();
		Math::Vector4 wallStart = wall.GetPhysicsObj().GetTail();
		Math::Vector4 wallEnd = wall.GetPhysicsObj().GetHead();

		//////////////////////////////////////////////////////////////////////
		//FOR TESTING ONLY
		/*
		Math::Vector4 wallVec = wallEnd - wallStart;
		float val = wallVec.Dot( wallNormal );
		wallVec.Normalize();
		*/
		//////////////////////////////////////////////////////////////////////

		//Math::Vector4 circleComputedVelocity = circle.GetPhysicsObj().GetVelocity() * circle.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleComputedVelocity = circle.GetPhysicsObj().GetDirection() * circle.GetPhysicsObj().GetMovementSpeed();
		Math::Vector4 circleStartPosition = circle.GetPhysicsObj().GetPosition();
		Math::Vector4 circleEndPosition = circleStartPosition + circleComputedVelocity * dt;
		float radius = circle.GetPhysicsObj().GetScale().GetFloatX() / 2.0F;
		

		//test for non-collision
		//is the circle start and end positions inside or outside the wall
		if ( this->IsCircleInsideWall( wallNormal, wallStart, circleStartPosition, circleEndPosition, radius ) == false
			&& this->IsCircleOutsideWall( wallNormal, wallStart, circleStartPosition, circleEndPosition, radius ) == false )
		{		
			//validate if the starting position of the circle is inside the wall
			float computedRadius = radius;
			if ( checkInwardOutwardDirection == true &&
				this->IsCircleStartPositionInsideWall( wallNormal, wallStart, circleStartPosition, radius ) == true )
			{
				computedRadius *= -1.0F;
			}

			//compute for the intersection values
			float intersectionVal = ( wallNormal.Dot( wallStart ) - wallNormal.Dot( circleStartPosition ) + computedRadius ) 
				/ ( wallNormal.Dot( circleComputedVelocity ) );	

			//compute for the time of intersection
			float timeIntersect = startTime + intersectionVal;

			//check if the time of intersection is within the frame time
			// or if the time intersect value is negative meaning that the ball is already in the wall
			if ( ( timeIntersect >= startTime && timeIntersect <= endTime )
				|| ( checkOverlap == true && intersectionVal < 0.0F ) )
			{
				//compute for the position where the circle intersects with the wall
				Math::Vector4 circleIntersectPosition = circleStartPosition + ( circleComputedVelocity * intersectionVal );

				//test for non-collision
				if ( this->IsCircleOnInfiniteWallStart( circleIntersectPosition, wallStart, wallEnd ) == false
					&& this->IsCircleOnInfiniteWallEnd( circleIntersectPosition, wallStart, wallEnd ) == false )
				{
					//set the collision flag
					collideFlag = true;

					//compute for the collision frame time
					collisionDt = endTime - timeIntersect;

					//set the collision response
					CollisionResponse collisionResponse;
					collisionResponse.SetReflectionCircleFromWall( collisionDt, wallNormal, circle, circleEndPosition, circleIntersectPosition );
				}
			}
		}		

		return collideFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate if the starting position of the circle is inside the wall
	\param wallNormal
	the outside normal of the wall
	\param wallStart
	the starting point of the wall
	\param circleStartPosition
	the starting position of the circle
	\param circleEndPosition
	the end position of the circle
	\param radius
	the radius of the circle
	\return bool
	if true, the starting position of the circle is inside the wall, otherwise false
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleStartPositionInsideWall( const Math::Vector4 & wallNormal, const Math::Vector4 & wallStart, 
		const Math::Vector4 & circleStartPosition, const float radius ) const
	{
		if ( ( wallNormal.Dot( circleStartPosition ) - wallNormal.Dot( wallStart ) ) < -radius )
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate for non-collision if the circle is inside the wall
	\param wallNormal
	the outside normal of the wall
	\param wallStart
	the starting point of the wall
	\param circleStartPosition
	the starting position of the circle
	\param circleEndPosition
	the end position of the circle
	\param radius
	the radius of the circle
	\return bool
	if true, there is no collision, otherwise false 
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleInsideWall( const Math::Vector4 & wallNormal, const Math::Vector4 & wallStart, 
		const Math::Vector4 & circleStartPosition, const Math::Vector4 & circleEndPosition, const float radius ) const
	{
		bool isCircleInsideWallFlag = false;

		//test for non-collision
		if ( ( wallNormal.Dot( circleStartPosition ) - wallNormal.Dot( wallStart ) ) < -radius 
			&& ( wallNormal.Dot( circleEndPosition ) - wallNormal.Dot( wallStart ) ) < -radius )
		{
			isCircleInsideWallFlag = true;
		}

		return isCircleInsideWallFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate for non-collision if the circle is outside the wall
	\param wallNormal
	the outside normal of the wall
	\param wallStart
	the starting point of the wall
	\param circleStartPosition
	the starting position of the circle
	\param circleEndPosition
	the end position of the circle
	\param radius
	the radius of the circle
	\return bool
	if true, there is no collision, otherwise false 
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleOutsideWall( const Math::Vector4 & wallNormal, const Math::Vector4 & wallStart, 
		const Math::Vector4 & circleStartPosition, const Math::Vector4 & circleEndPosition, const float radius ) const
	{
		bool isCircleOutsideWallFlag = false;

		//test for non-collision
		if ( ( wallNormal.Dot( circleStartPosition ) - wallNormal.Dot( wallStart ) ) > radius 
			&& ( wallNormal.Dot( circleEndPosition ) - wallNormal.Dot( wallStart ) ) > radius )
		{
			isCircleOutsideWallFlag = true;
		}

		return isCircleOutsideWallFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate for non-collision if the circle is on the infinite start of the wall
	\param circleIntersectPosition
	the position where the circle intersects the wall
	\param wallStart
	the starting point of the wall
	\param wallEnd
	the end point of the wall
	\return bool
	if true, there is no collision, otherwise false 
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleOnInfiniteWallStart( const Math::Vector4 & circleIntersectPosition, 
		const Math::Vector4 & wallStart, const Math::Vector4 & wallEnd ) const
	{
		bool isCircleOnInfiniteWallStartFlag = false;

		//test for non-collision
		if ( ( circleIntersectPosition - wallStart ).Dot( wallEnd - wallStart ) < 0.0F )
		{
			isCircleOnInfiniteWallStartFlag = true;
		}

		return isCircleOnInfiniteWallStartFlag;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Validate for non-collision if the circle is on the infinite end of the wall
	\param circleIntersectPosition
	the position where the circle intersects the wall
	\param wallStart
	the starting point of the wall
	\param wallEnd
	the end point of the wall
	\return bool
	if true, there is no collision, otherwise false 
	*/
	/******************************************************************************/
	const bool CollisionDetection::IsCircleOnInfiniteWallEnd( const Math::Vector4 & circleIntersectPosition, 
		const Math::Vector4 & wallStart, const Math::Vector4 & wallEnd ) const
	{
		bool isCircleOnInfiniteWallEndFlag = false;

		Math::Vector4 wallVector = wallEnd - wallStart;

		//test for non-collision
		if ( ( circleIntersectPosition - wallStart ).Dot( wallVector ) > wallVector.Dot( wallVector ) )
		{
			isCircleOnInfiniteWallEndFlag = true;
		}

		return isCircleOnInfiniteWallEndFlag;
	}


} //end PhysicsFramework