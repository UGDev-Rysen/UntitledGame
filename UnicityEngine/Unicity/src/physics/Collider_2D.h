#pragma once

#include <physics/PhysicsObject.h>
#include <u_engine_includes.h>
#include <maths/maths.h>

namespace u_engine { namespace physics {

	struct AABB {		//Axis Aligned Bounding Boxes

		maths::vec2 min;
		maths::vec2 max;

	};

	struct CircleC {

		UE_float radius;
		maths::vec2 position;
	};

	class Collider2D {

	private:

		UE_bool m_Colliding;
		UE_bool m_Collidable;


	public:

		Collider2D(UE_bool collidable);
		Collider2D();
		~Collider2D();

		UE_bool CheckAABBCollision(AABB a, AABB b);
		UE_bool CeckCircleCollision(CircleC a, CircleC b);

//		UE_void ResolveCollision(PhysicsObject A, PhysicsObject B);

		UE_bool SimpleCollisionDet(PhysicsObject obj, maths::vec2 pos);

		UE_void CheckCollisions(Collider2D collider);


	};


} }