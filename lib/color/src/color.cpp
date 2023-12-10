#include "color.h"

#include <functional>

namespace luled::color
{

namespace
{

Mat3F genYcbcrToRgbColorMat(const YcbcrToRgbConversionInfo& info)
{
	auto& constants = info.constants;
	float scaleY  = 1.0f / (info.white - info.black);
	float scaleUv = 1.0f / (info.chromaHi - info.chromaLo);
	float yCoeff = (constants[0] + constants[1] + constants[2]) * scaleY;
	float dCoeff = ((1.0f - constants[2]) * 2.0f) * scaleUv;
	float eCoeff = ((1.0f - constants[0]) * 2.0f) * scaleUv;
	Mat3F mat =
	{
		yCoeff, 0.0f, eCoeff,
		yCoeff, -1.0f * constants[2] * dCoeff / constants[1], -1.0f * constants[0] * eCoeff / constants[1],
		yCoeff, dCoeff, 0.0f
	};
	return mat;
}


}

YcbcrToRgbConversionInfo::YcbcrToRgbConversionInfo(int bits, bool fullRange) :
		bits(bits), fullRange(fullRange)
{
		auto scaler = 1 << (bits - 8);
		
		black = fullRange ? 0.0f : 16.0f * scaler; 
		white = fullRange ? (1 << bits) - 1.0f : 219.0f * scaler + black;

		achroma   = 1 << (bits - 1);
		chromaLo  = fullRange ? 1.0f : 16.0f * scaler;
		chromaHi  = fullRange ? (1 << bits) - 1.0f : 224.0f * scaler + chromaLo;
		constants = bt709Constants;

		ycbrToRgbMat  = genYcbcrToRgbColorMat(*this);
		rgbToYcbcrMat = ycbrToRgbMat.inverse();
}

Vec3F rgbToHsl(const Vec3F& rgb)
{
	Vec3F hsl;
    float valueMax, valueMin;
    float r = rgb[0] / 255.0f;
    float g = rgb[1] / 255.0f;
    float b = rgb[2] / 255.0f;
    valueMax = std::max(std::max(r, g), b);
    valueMin = std::min(std::min(r, g), b);

    hsl[2] = (valueMax + valueMin) / 2.0;
    if (valueMax == valueMin) 
	{
        hsl[0] = 0.0f;
        hsl[1] = 0.0f;
    }
	else
	{
        float range = valueMax - valueMin;
        if (hsl[2] > 0.5)
		{
            hsl[1] = range / (2 - valueMax - valueMin);
        }
		else 
		{
            hsl[1] = range / (valueMax + valueMin);
        }
        if (r > g && r > b)
		{
            hsl[0] = (g - b) / range + (g < b ? 6.0f : 0.0f);
		}
        else if (g > b)
		{
            hsl[0] = (b - r) / range + 2.0f;
		}
        else
		{
            hsl[0] = (r - g) / range + 4.0f;
		}
        hsl[0] /= 6;
    }

	return hsl;
}

Vec3F hslToRgb(const Vec3F& hsl)
{
	Vec3F rgb;
	if (hsl[1] <= 0.0001f)
	{
        rgb[0] = hsl[2] * 255.0;
        rgb[1] = hsl[2] * 255.0;
        rgb[2] = hsl[2] * 255.0;
    }
	else
	{
        float chroma = (1 - std::abs(2 * hsl[2] - 1)) * hsl[1];
        float hue = hsl[0] * 6.0f;
        float x = chroma * (1 - std::abs(std::fmod(hue, 2.0f) - 1));
        float magnitude = hsl[2] - chroma / 2;

        auto hueToRgb = [](float chroma, float x, float hue) -> auto 
		{
            if (hue <= 0.001f)
			{
                return std::make_tuple(0.0f, 0.0f, 0.0f);
			}
            int hue_floor = static_cast<int>(std::floor(hue));
            switch (hue_floor)
			{
				case 0:
					return std::make_tuple(chroma, x, 0.0f);
				case 1:
					return std::make_tuple(x, chroma, 0.0f);
				case 2:
					return std::make_tuple(0.0f, chroma, x);
				case 3:
					return std::make_tuple(0.0f, x, chroma);
				case 4:
					return std::make_tuple(x, 0.0f, chroma);
				case 5:
					return std::make_tuple(chroma, 0.0f, x);
				default:
					return std::make_tuple(0.0f, 0.0f, 0.0f);
            }
        };
        std::tie(rgb[0], rgb[1], rgb[2]) = hueToRgb(chroma, x, hue);
        rgb[0] = (rgb[0] + magnitude) * 255.0f;
        rgb[1] = (rgb[1] + magnitude) * 255.0f;
        rgb[2] = (rgb[2] + magnitude) * 255.0f;
    }
	return rgb;
}

} // namespace luled::color