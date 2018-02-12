/******************************************************************************/
/*!
\file CollisionResponse.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H
////////////////////////////////////////////////////////////////////////////////

#include "../Math/Vector4.h"
#include "../Game/GameObj.h"

namespace PhysicsFramework
{
	class CollisionResponse
	{
	public:
		void SetReflectionCircleFromWall( const float collisionDt, const Math::Vector4 & wallNormal, GameFramework::GameObject & circle,
			const Math::Vector4 & circleEndPosition, const Math::Vector4 & circleIntersectPosition  ) const;

		void SetReflectionCircleFromCirclePillar( const float collisionDt, GameFramework::GameObject & circle,
			const Math::Vector4 & circleStartPosition, const Math::Vector4 & circleIntersectPosition, const Math::Vector4 & circlePillarStartPosition ) const;

		void SetReflectionCircleFromCircle( const float collisionDt, GameFramework::GameObject & circleFrom, const Math::Vector4 & circleFromIntersectPosition, 
			GameFramework::GameObject & circleTo, const Math::Vector4 & circleToIntersectPosition ) const;
	};

}//end namespace PhysicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////