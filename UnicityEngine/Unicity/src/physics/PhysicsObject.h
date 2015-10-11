#pragma once

#include <maths/maths.h>
#include <u_engine_includes.h>
#include <physics/PhysicsObject.h>

namespace u_engine { namespace physics {

	class PhysicsObject {

	private:

		const UE_float GRAV_CONST = 9.80665f;

		UE_float m_Mass;				//in kg
		maths::vec3 m_Force;			//in N(ewton)
		maths::vec3 m_Acceleration;		//in m/s^2
		maths::vec3 m_Velocity;			//in m/s
		UE_float m_TimeStep;			//in s

		UE_bool m_Static;

		maths::vec3 m_Position;

		UE_float m_BounceF;
		UE_float m_Density;

		UE_float m_gravPull;

		maths::vec3 m_WeightForce;

	public:

		PhysicsObject(UE_float mass);
		PhysicsObject();


		~PhysicsObject();

		inline const UE_float getMass() const { return m_Mass; }
		inline const maths::vec3 getAcceleration() const { return m_Acceleration; }
		inline const maths::vec3 getForce() const { return m_Force; }
		inline const maths::vec3 getPosition() const { return m_Position; }

		UE_void setMass(UE_float mass);
		UE_void setAcceleration(maths::vec3 acc);
		UE_void setForce(maths::vec3 frc);
		UE_void setPosition(maths::vec3 pos);
		UE_void setTimeStep(UE_float tp);

		UE_void setWeightForce();

		UE_void updateAcc();
		UE_void updateVel();
		UE_void updatePosition();

		UE_void updatePhysics();



	};

} }