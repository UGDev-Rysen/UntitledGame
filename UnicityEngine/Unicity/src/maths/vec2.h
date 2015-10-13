#pragma once

#include <iostream>
#include <math.h>
#include <maths/vec3.h>

#include <utils/unicitydef.h>
namespace u_engine { namespace maths {

	struct vec2
	{
		UE_float x, y;

		vec2();
		vec2(const UE_float& x, const UE_float& y);
		vec2(const vec3& vector);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		friend vec2 operator+(vec2 left, UE_float value);
		friend vec2 operator*(vec2 left, UE_float value);

		UE_bool operator==(const vec2& other);
		UE_bool operator!=(const vec2& other);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		UE_float magnitude() const;
		vec2 normalise() const;
		UE_float distance(const vec2& other) const;
		UE_float dot(const vec2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
	};

} }