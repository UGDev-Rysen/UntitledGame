#include <physics/PhysicsObject.h>

namespace u_engine { namespace physics {

	PhysicsObject::PhysicsObject(UE_float mass)
		: m_Mass(mass), m_Acceleration(0, 0, 0), m_Velocity(0, 0, 0), m_Static(false), m_Force(0, 0, 0), m_BounceF(0), m_Density(0) {

	}

	PhysicsObject::PhysicsObject()
		: m_Mass(0), m_Acceleration(0, 0, 0), m_Velocity(0, 0, 0), m_Static(false), m_Force(0, 0, 0), m_BounceF(0), m_Density(0) {

	}

	UE_void PhysicsObject::setWeightForce() {

		m_Force.y = m_Mass * GRAV_CONST;

	}

	UE_void PhysicsObject::updateAcc() {

		if (!m_Static) {
			m_Acceleration.x = m_Force.x * m_Mass;
			m_Acceleration.y = m_Force.y * m_Mass;
			m_Acceleration.z = m_Force.z * m_Mass;
		}
	}

	UE_void PhysicsObject::updateVel() {

		if (!m_Static) {
			m_Velocity.x = m_Acceleration.x * m_TimeStep;
			m_Velocity.x = m_Acceleration.x * m_TimeStep;
			m_Velocity.x = m_Acceleration.x * m_TimeStep;
		}
	}

	UE_void PhysicsObject::updatePosition() {
		
		if (!m_Static) {

			m_Position.x = m_Velocity.x * m_TimeStep;
			m_Position.y = m_Velocity.y * m_TimeStep;
			m_Position.z = m_Velocity.z * m_TimeStep;

		}
	}

	UE_void PhysicsObject::setMass(UE_float mass) {

		m_Mass = mass;		
	}

	UE_void PhysicsObject::setAcceleration(maths::vec3 acc) {

		m_Acceleration.x = acc.x;
		m_Acceleration.y = acc.y;
		m_Acceleration.z = acc.z;

	}

	UE_void PhysicsObject::setForce(maths::vec3 frc) {
		
		m_Force = frc;

	}

	UE_void PhysicsObject::setPosition(maths::vec3 pos) {
		
		m_Position = pos;

	}

	UE_void PhysicsObject::setTimeStep(UE_float tp) {

		m_TimeStep = tp;

	}

	UE_void PhysicsObject::updatePhysics() {

		PhysicsObject::updateAcc();
		PhysicsObject::updateVel();
		PhysicsObject::updatePosition();

	}



} }