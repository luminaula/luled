#pragma once

#include <array>
#include "color_matrix.h"
#include "color_vec.h"
#include "color_transfer.h"

namespace luled::color
{

constexpr Vec3F bt709Constants(0.2126f, 0.7152f, 0.0722f);
constexpr Vec3F bt2020Constants(0.2627f, 0.6780f, 0.0593f);

struct YcbcrToRgbConversionInfo
{
	Vec3F constants;
	Mat3F ycbrToRgbMat;
	Mat3F rgbToYcbcrMat;
    float black; 		// 16.0f;
    float white; 		// 235.0f;
    float achroma; 		// 128.0f;
    float chromaLo;		// 16.0f;
    float chromaHi;		// 240.0f;
    int bits; 			// 8;
    bool fullRange; 	// Narrow

	YcbcrToRgbConversionInfo(int bits = 8, bool fullRange = false);
	
};

Vec3F rgbToHsl(const Vec3F& rgb);
Vec3F hslToRgb(const Vec3F& hsl);


} // namespace luled::color