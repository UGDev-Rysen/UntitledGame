#pragma once

#include <iostream>

#include <utils/unicitydef.h>
namespace u_engine { namespace maths {

	struct vec2;

	struct vec3
	{
		UE_float x, y, z;

		vec3();
		vec3(UE_float x, UE_float y, UE_float z);
		vec3(const vec2& other);

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		UE_bool operator==(const vec3& other);
		UE_bool operator!=(const vec3& other);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		UE_float distance(const vec3& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	};

} }