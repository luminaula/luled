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

} // namespace luled::color