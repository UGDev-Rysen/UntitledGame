#include <maths/vec2.h>


namespace u_engine { namespace maths {

	vec2::vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	vec2::vec2(const UE_float& x, const UE_float& y)
	{
		this->x = x;
		this->y = y;
	}

	vec2::vec2(const vec3& vector)
	{
		this->x = vector.x;
		this->y = vector.y;
	}

	vec2& vec2::add(const vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	vec2 operator+(vec2 left, const vec2& right)
	{
		return left.add(right);
	}

	vec2 operator-(vec2 left, const vec2& right)
	{
		return left.subtract(right);
	}

	vec2 operator*(vec2 left, const vec2& right)
	{
		return left.multiply(right);
	}

	vec2 operator/(vec2 left, const vec2& right)
	{
		return left.divide(right);
	}

	vec2 operator+(vec2 left, UE_float value)
	{
		return vec2(left.x + value, left.y + value);
	}

	vec2 operator*(vec2 left, UE_float value)
	{
		return vec2(left.x * value, left.y * value);
	}

	vec2& vec2::operator+=(const vec2& other)
	{
		return add(other);
	}

	vec2& vec2::operator-=(const vec2& other)
	{
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other)
	{
		return multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other)
	{
		return divide(other);
	}

	UE_bool vec2::operator==(const vec2& other)
	{
		return x == other.x && y == other.y;
	}

	UE_bool vec2::operator!=(const vec2& other)
	{
		return !(*this == other);
	}

	UE_float vec2::distance(const vec2& other) const
	{
		UE_float a = x - other.x;
		UE_float b = y - other.y;
		return sqrt(a * a + b * b);
	}

	UE_float vec2::dot(const vec2& other) const
	{
		return x * other.x + y * other.y;
	}

	UE_float vec2::magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	vec2 vec2::normalise() const
	{
		UE_float length = magnitude();
		return vec2(x / length, y / length);
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}


} }