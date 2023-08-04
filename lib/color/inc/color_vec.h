#pragma once

#include <ostream>

#include "color_matrix.h"

namespace luled::color
{

template<typename T>
class Vec3
{
public:
	Vec3() = default;
	constexpr Vec3(T x, T y, T z) : data({x, y, z}){}
	constexpr Vec3(const Vec3<T>& rhs) : data(rhs.data) {}
	constexpr Vec3(Vec3<T>&& rhs) noexcept : data(std::move(rhs.data)) {}
	constexpr Vec3 operator=(const Vec3<T>& rhs)
	{
		data = rhs.data;
		return *this;
	}
	~Vec3() = default;

	Vec3<T> operator*(const Mat3<T>& rhs ) const
	{
		return Vec3<T>(
			data[0] * rhs[0] + data[1] * rhs[3] + data[2] * rhs[6],
			data[0] * rhs[1] + data[1] * rhs[4] + data[2] * rhs[7],
			data[0] * rhs[2] + data[1] * rhs[5] + data[2] * rhs[8]);
	}

	Vec3<T> operator*(const float& rhs) const
	{
		return Vec3<T>(data[0] * rhs, data[1] * rhs, data[2] * rhs);
	}

	Vec3<T> operator+(const Vec3<T>& rhs) const
	{
		return Vec3<T>(data[0] + rhs[0], data[1] + rhs[1], data[2] + rhs[2]);
	}

	T operator[](int i) const { return data[i]; }
	T& operator[](int i) { return data[i]; }

private:
	std::array<T, 3> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& rhs)
{
	os << rhs[0] << " " << rhs[1] << " " << rhs[2];
		return os;
}

using Vec3F = Vec3<float>;
using Vec3D = Vec3<double>;

}