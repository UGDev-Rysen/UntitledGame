#include <maths/vec3.h>
#include <maths/vec2.h>

namespace u_engine { namespace maths {

	vec3::vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	vec3::vec3(UE_float x, UE_float y, UE_float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3::vec3(const vec2& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = 0.0f;
	}

	vec3& vec3::add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3& vec3::subtract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3& vec3::multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	vec3& vec3::divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	vec3 operator+(vec3 left, const vec3& right)
	{
		return left.add(right);
	}

	vec3 operator-(vec3 left, const vec3& right)
	{
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, const vec3& right)
	{
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, const vec3& right)
	{
		return left.divide(right);
	}

	vec3& vec3::operator+=(const vec3& other)
	{
		return add(other);
	}

	vec3& vec3::operator-=(const vec3& other)
	{
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other)
	{
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other)
	{
		return divide(other);
	}

	UE_bool vec3::operator==(const vec3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	UE_bool vec3::operator!=(const vec3& other)
	{
		return !(*this == other);
	}

	UE_float vec3::distance(const vec3& other) const
	{
		UE_float a = x - other.x;
		UE_float b = y - other.y;
		UE_float c = z - other.z;
		return sqrt(a * a + b * b + c * c);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector)
	{
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}


} }