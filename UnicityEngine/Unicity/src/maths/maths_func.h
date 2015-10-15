#pragma once

#define _USE_MATH_DEFINES
#define UE_PI 3.14159265358979323846f

#include <math.h>

#include <utils/unicitydef.h>


namespace u_engine { namespace maths {

		inline UE_float toRadians(UE_float degrees) {
			return degrees * (UE_PI / 180.0f);
		}

		inline UE_float toDeegrees(UE_float radians) {

			return radians * (180.0f / UE_PI);
		}

		inline UE_float sign(UE_float value) {

			return (value > 0.0f) - (value < 0.0f);
		}


} }