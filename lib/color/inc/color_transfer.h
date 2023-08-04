#pragma once

#include <cmath>
#include "color_vec.h"
#include "color_constants.h"

namespace luled::color
{



template<typename T>
constexpr T srgbEotfInverse(const T& x)
{
	return x <= 0.0031308 ? x * 12.92 : 1.055 * std::pow(x, 1.0 / 2.4) - 0.055;
}

template<typename T>
constexpr T srgbEotf(const T& x)
{
	return x <= 0.04045 ? x / 12.92 : std::pow((x + 0.055) / 1.055, 2.4);
}

template<typename T>
constexpr T bt709Oetf(const T& x)
{
    return x < 0.018 ? x * 4.5 : 1.099 * std::pow(x, 0.45) - 0.099;
}

template<typename T>
constexpr Vec3<T> bt709Oetf(const Vec3<T>& x)
{
    return Vec3<T>(bt709Oetf(x[0]), bt709Oetf(x[1]), bt709Oetf(x[2]));
}

template<typename T>
constexpr T bt709OetfInverse(const T& x)
{
    return x < 0.081 ? x / 4.5 : std::pow((x + 0.099) / 1.099, 1.0 / 0.45);
}

template<typename T>
constexpr Vec3<T> bt709OetfInverse(const Vec3<T>& x)
{
    return Vec3<T>(bt709OetfInverse(x[0]), bt709OetfInverse(x[1]), bt709OetfInverse(x[2]));
}


template<typename T>
constexpr T bt1886Eotf(const T& x, const T lightBlack = 0.0, const T lightPeak = 1.0)
{
    T gam = 2.40;
    T gamd = 1.0 / gam;

    T n = std::pow(lightPeak, gamd) - std::pow(lightBlack, gamd);
    T a = std::pow(n, gam);
    T b = std::pow(lightBlack, gamd / n);
    return a * std::pow(std::max(x + b, 0.0), gam);
}

template<typename T>
constexpr Vec3<T> bt1886Eotf(const Vec3<T>& x, const T lightBlack = 0.0, const T lightPeak = 1.0)
{
    return Vec3<T>(bt1886Eotf(x[0], lightBlack, lightPeak), bt1886Eotf(x[1], lightBlack, lightPeak), bt1886Eotf(x[2], lightBlack, lightPeak));
}

template<typename T>
constexpr T bt1886EotfInverse(const T& x, const T& lightBlack = 0.0f, const T& lightPeak = 1.0f)
{
    T g = 2.4f;
    T gd = 1.0f / g;

    T n = std::pow(lightPeak, gd) - std::pow(lightBlack, gd);
    T a = std::pow(n, g);
    T b = std::pow(lightBlack, gd) / n;

    T v = std::pow(x / a, gd) - b;
    return v;
}

template<typename T>
constexpr Vec3<T> bt1886EotfInverse(const Vec3<T>& x, const float lightBlack = 0.0f, const float lightPeak = 1.0f)
{
    return Vec3<T>(bt1886EotfInverse(x[0], lightBlack, lightPeak), bt1886EotfInverse(x[1], lightBlack, lightPeak), bt1886EotfInverse(x[2], lightBlack, lightPeak));
}

template<typename T>
constexpr T hlgGamma(const T lightPeak = 1000.0)
{
    if(lightPeak < 0.001)
    {
        return 1.2;
    }
    return 1.2 + 0.42 * std::log10(lightPeak / 1000.0);
}

template<typename T>
T hlgOetf(const T& x)
{
    return (x <= 1.0f / 12.0f) ? (std::sqrt(3.0f * x)) : (hlgConstants[0] * std::log(12.0f * x - hlgConstants[1]) + hlgConstants[2]);
}

template<typename T>
Vec3<T> hlgOetf(const Vec3<T>& x)
{
    return Vec3<T>(hlgOetf(x[0]), hlgOetf(x[1]), hlgOetf(x[2]));
}

template<typename T>
Vec3<T> hlgOotf(const Vec3<T>& x, const T lightBlack = 0.0f, const T lightPeak = 1000.0f)
{
    T alpha = lightPeak - lightBlack;
    T beta = lightBlack;
    T lumi = x[0] * bt2100Constants[0] + x[1] * bt2100Constants[1] + x[2] * bt2100Constants[2];
    T gam = hlgGamma(lightPeak);

    T rd = alpha * x[0] * std::pow(std::abs(lumi), gam - 1.0f) + beta;
    T rg = alpha * x[1] * std::pow(std::abs(lumi), gam - 1.0f) + beta;
    T rb = alpha * x[2] * std::pow(std::abs(lumi), gam - 1.0f) + beta;

    return Vec3<T>(rd, rg, rb);
}

template<typename T>
Vec3<T> hlgOotfInverse(const Vec3<T>& x, T lightBlack = 0.0f, T lightPeak = 1000.0f)
{
    T alpha = lightPeak - lightBlack;
    T lumi = x[0] * bt2100Constants[0] + x[1] * bt2100Constants[1] + x[2] * bt2100Constants[2];
    T gam = hlgGamma(lightPeak);
    T beta = std::abs(std::pow((lumi - lightBlack) / alpha, ((1.0f - gam) / gam)));

    return Vec3<T>(beta * (x[0] - lightBlack) / lightPeak,
                   beta * (x[1] - lightBlack) / lightPeak,
                   beta * (x[2] - lightBlack) / lightPeak);
}

template<typename T>
Vec3<T> hlgEotfInverse(const Vec3<T>& x, const T lightBlack = 0.0f, const T lightPeak = 1000.0)
{
    return hlgOetf(hlgOotfInverse(x, lightBlack, lightPeak));
}

template<typename T>
T hlgOetfInverse(const T& x)
{
    return (x <= 0.5f) ? (x * x / 3.0f) : ((std::exp((x - hlgConstants[2]) / hlgConstants[0]) + hlgConstants[1]) / 12.0f);
}

template<typename T>
Vec3<T> hlgOetfInverse(const Vec3<T>& x)
{    
    return Vec3<T>(hlgOetfInverse(x[0]), hlgOetfInverse(x[1]), hlgOetfInverse(x[2]));   
}

template<typename T>
Vec3<T> hlgEotf(const Vec3<T>& x, const T lightBlack = 0.0f, const T lightPeak = 1000.0f)
{ 
    return hlgOotf(hlgOetfInverse(x), lightBlack, lightPeak);
}



}