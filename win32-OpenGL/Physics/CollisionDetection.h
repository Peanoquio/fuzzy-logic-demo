/******************************************************************************/
/*!
\file CollisionDetection.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H
////////////////////////////////////////////////////////////////////////////////

#include "../Math/Vector4.h"
#include "../Game/GameObj.h"

namespace PhysicsFramework
{
	class CollisionDetection
	{
	public:
		const bool CheckCollisionCircleToWall( const float startTime, const float dt, float & collisionDt,
			GameFramework::GameObject & circle, GameFramework::GameObject & wall, const bool checkInwardOutwardDirection, const bool checkOverlap ) const;
		const bool CheckCollisionCircleToCirclePillar( const float startTime, const float dt, float & collisionDt,
			GameFramework::GameObject & circle, GameFramework::GameObject & circlePillar ) const;
		const bool CheckCollisionCircleToCircle( const float startTime, const float dt, float & collisionDt,
			GameFramework::GameObject & circle, GameFramework::GameObject & circlePillar ) const;

	private:
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		const bool IsCircleCollidingWithCirclePillar( float & intersectionTime, const float frameStartTime, const float frameEndTime, 
			const float radiusSum, const Math::Vector4 & circleComputedVelocity, 
			const Math::Vector4 & circleStartPosition, const Math::Vector4 & circlePillarStartPosition ) const;

		const bool IsCircleCollidingWithCirclePillarQuadraticeEq( float & intersectionTime, const float frameStartTime, const float frameEndTime, 
			const float radiusSum, const Math::Vector4 & circleComputedVelocity, 
			const Math::Vector4 & circleStartPosition, const Math::Vector4 & circlePillarStartPosition ) const;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		const bool IsCircleStartPositionInsideWall( const Math::Vector4 & wallNormal, const Math::Vector4 & wallStart, 
			const Math::Vector4 & circleStartPosition, const float radius ) const;

		const bool IsCircleInsideWall( const Math::Vector4 & wallNormal, const Math::Vector4 & wallStart, 
			const Math::Vector4 & circleStartPosition, const Math::Vector4 & circleEndPosition, const float radius ) const;
		const bool IsCircleOutsideWall( const Math::Vector4 & wallNormal, const Math::Vector4 & wallStart, 
			const Math::Vector4 & circleStartPosition, const Math::Vector4 & circleEndPosition, const float radius ) const;

		const bool IsCircleOnInfiniteWallStart( const Math::Vector4 & circleIntersectPosition, const Math::Vector4 & wallStart, const Math::Vector4 & wallEnd ) const;
		const bool IsCircleOnInfiniteWallEnd( const Math::Vector4 & circleIntersectPosition, const Math::Vector4 & wallStart, const Math::Vector4 & wallEnd ) const;
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	};

}//end namespace PhysicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////