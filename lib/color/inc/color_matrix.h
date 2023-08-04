#pragma once

#include <array>
#include <functional>

namespace luled::color
{

template<typename T>
class Mat3
{
public:
	Mat3() = default;

	constexpr Mat3(T a0, T a1, T a2,
		 T b0, T b1, T b2,
		 T c0, T c1, T c2) :
		data({a0, a1, a2, b0, b1, b2, c0, c1, c2}){}

	constexpr Mat3(std::array<T, 9> data) : 
		data(data){}

	constexpr Mat3(const Mat3& rhs) : 
		data(rhs.data){}

	constexpr Mat3(Mat3&& rhs) noexcept : 
		data(std::move(rhs.data)){}

	constexpr Mat3 operator=(const Mat3& rhs)
	{
		data = rhs.data;
		return *this;
	}

	constexpr Mat3 inverse()
	{
		auto determinant = [](T a00, T a01, T a10, T a11)
		{
			return a00 * a01 - a11 * a10;
		};

		T det = data[0] * determinant(data[4], data[8], data[7], data[5]) -
					data[1] * determinant(data[3], data[8], data[5], data[6]) +
					data[2] * determinant(data[3], data[7], data[4], data[6]);

		T invdet = 1 / det;			

		return Mat3(determinant(data[4], data[8], data[7], data[5]) * invdet,
				determinant(data[2], data[7], data[1], data[8]) * invdet,
				determinant(data[1], data[5], data[2], data[4]) * invdet,
				determinant(data[5], data[6], data[3], data[8]) * invdet,
				determinant(data[0], data[8], data[2], data[6]) * invdet,
				determinant(data[3], data[2], data[0], data[5]) * invdet,
				determinant(data[3], data[7], data[6], data[4]) * invdet,
				determinant(data[6], data[1], data[0], data[7]) * invdet,
				determinant(data[0], data[4], data[3], data[1]) * invdet);
	}

	constexpr Mat3 operator*(const Mat3& rhs)
	{
		return Mat3(
			data[0] * rhs.data[0] + data[1] * rhs.data[3] + data[2] * rhs.data[6],
			data[0] * rhs.data[1] + data[1] * rhs.data[4] + data[2] * rhs.data[7],
			data[0] * rhs.data[2] + data[1] * rhs.data[5] + data[2] * rhs.data[8],
			data[3] * rhs.data[0] + data[4] * rhs.data[3] + data[5] * rhs.data[6],
			data[3] * rhs.data[1] + data[4] * rhs.data[4] + data[5] * rhs.data[7],
			data[3] * rhs.data[2] + data[4] * rhs.data[5] + data[5] * rhs.data[8],
			data[6] * rhs.data[0] + data[7] * rhs.data[3] + data[8] * rhs.data[6],
			data[6] * rhs.data[1] + data[7] * rhs.data[4] + data[8] * rhs.data[7],
			data[6] * rhs.data[2] + data[7] * rhs.data[5] + data[8] * rhs.data[8]
		);
	}

	constexpr Mat3& operator*= (const Mat3& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	T operator[](int i) const
	{
		return data[i];
	}
	T& operator[](int i)
	{
		return data[i];
	}
private:
	std::array<T, 9> data;
};

using Mat3F = Mat3<float>;
using Mat3D = Mat3<double>; 


} // namespace luled::color