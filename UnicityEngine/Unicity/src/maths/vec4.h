#pragma once
#include <iostream>
#include <utils/unicitydef.h>
namespace u_engine { namespace maths {

		struct vec4 {
			UE_float x, y, z, w;

			vec4() = default;
			vec4(const UE_float& x, const UE_float& y, const UE_float& z, const UE_float& w);

			vec4& add(const vec4& other);
			vec4& substract(const vec4& other);
			vec4& multiply(const vec4& other);
			vec4& divide(const vec4& other);


			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);

			UE_bool operator==(const vec4& other);
			UE_bool operator!=(const vec4& other);

			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);


			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);

		};


	}
}