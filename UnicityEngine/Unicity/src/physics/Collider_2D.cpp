#include <physics/Collider_2D.h>

namespace u_engine { namespace physics {

	Collider2D::Collider2D(UE_bool collidable)
		: m_Collidable(collidable) { 
		
		m_Colliding = false;
	}

	Collider2D::Collider2D()
		: m_Collidable(true) {
	
		m_Colliding = false;
	}

	UE_bool Collider2D::CheckAABBCollision(AABB a, AABB b) {

		//If no intersection, there is no collision -> return false
		if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
		if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

		//If no seperating axis has been found, there is at least one overlapping axis -> Collision
		return true;
	}

	UE_bool Collider2D::CeckCircleCollision(CircleC a, CircleC b) {

		UE_float r = a.radius + b.radius;
		r *= r;
		return r < (a.position.x + b.position.x) * (a.position.x + b.position.x) + (a.position.y + b.position.y) * (a.position.y + b.position.y);

	}

	UE_bool Collider2D::SimpleCollisionDet(PhysicsObject obj, maths::vec2 pos) {

		if (obj.getPosition().x < pos.x || obj.getPosition().x > pos.x)
			return true;
		if (obj.getPosition().y < pos.y || obj.getPosition().y > pos.x)
			return true;

		return false;

	}

	UE_void Collider2D::CheckCollisions(Collider2D collider) {

		


	}



} }