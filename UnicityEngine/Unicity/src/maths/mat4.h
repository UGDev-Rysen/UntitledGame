#pragma once


#include <maths/maths_func.h>
#include <maths/vec3.h>
#include <maths/vec4.h>
#include <utils/unicitydef.h>

namespace u_engine { namespace maths {


	struct mat4 {
		union {

			UE_float elements[4 * 4];
			vec4  columns[4];
		};
		mat4();
		mat4(UE_float diagonal);

		vec4 getColumn(UE_int index) {
			index *= 4;
			return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
		}
		

		static mat4 identity();

		mat4& multiply(const mat4& other);
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);


		vec3 multiply(const vec3& other) const;
		friend vec3 operator*(const mat4& left, const vec3& right);


		vec4 multiply(const vec4& other) const;
		friend vec4 operator*(const mat4& left, const vec4& right);

		mat4& invert();

		static mat4 orthographic(UE_float left, UE_float right, UE_float bottom, UE_float top, UE_float near, UE_float far);
		static mat4 perspective(UE_float fov, UE_float aspectRatio, UE_float near, UE_float far);

		static mat4 translation(const vec3& translation);		
		static mat4 rotation(UE_float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);
		static mat4 invert(const mat4& matrix);

	};


} }