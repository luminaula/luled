#pragma once

#include <tuple>
#include <cstdint>

#include "color.h"
#include "color_vec.h"

namespace luled::color
{

std::pair<Vec3F, Vec3F> yuyvToRgb(uint32_t yuyv, const YcbcrToRgbConversionInfo& info);
std::pair<Vec3F, Vec3F> yuyvU16ToRgb(uint64_t yuyv, const YcbcrToRgbConversionInfo& info);

uint32_t rgbToYuyv(const Vec3F& rgb1, const Vec3F& rgb2, const YcbcrToRgbConversionInfo& info);
uint64_t rgbToYuyvU16(const Vec3F& rgb1, const Vec3F& rgb2, const YcbcrToRgbConversionInfo& info);


} // namespace lelud::color