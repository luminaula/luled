#include "color_transform.h"


namespace luled::color
{


namespace
{

inline uint32_t YUYV(uint32_t y1, uint32_t u, uint32_t y2, uint32_t v)
{
    return v  << 24 |
           y2 << 16 |
           u  <<  8 |
           y1;
}

inline uint64_t YUYV_U16(uint64_t y1, uint64_t u, uint64_t y2, uint64_t v)
{
    return v  << 48 |
           y2 << 32 |
           u  << 16 |
           y1;
}

}

std::pair<Vec3F, Vec3F> yuyvToRgb(uint32_t yuyv, const YcbcrToRgbConversionInfo& info)
{
	#define nthLsByte(val, n) ((val >> (n * 8)) & 0xff)
    const float y  = (nthLsByte(yuyv, 0) - info.black);
    const float y1 = (nthLsByte(yuyv, 2) - info.black);
    const float cb = (nthLsByte(yuyv, 1) - info.achroma);
    const float cr = (nthLsByte(yuyv, 3) - info.achroma);
    #undef nthLsByte

    const Vec3F col(y, cb, cr);
    const Vec3F col2(y1, cb, cr);

    return {col *  info.ycbrToRgbMat, col2 * info.ycbrToRgbMat};
}

std::pair<Vec3F, Vec3F> yuyvU16ToRgb(uint64_t yuyv, const YcbcrToRgbConversionInfo& info)
{
	#define nthLsShort(val, n) ((val >> (n * 16)) & 0xffff)
    const float y  = (nthLsShort(yuyv, 0) - info.black);
    const float y1 = (nthLsShort(yuyv, 2) - info.black);
    const float cb = (nthLsShort(yuyv, 1) - info.achroma);
    const float cr = (nthLsShort(yuyv, 3) - info.achroma);
    #undef nthLsByte

    const Vec3F col = {y, cb, cr};
    const Vec3F col2 = {y1, cb, cr};

    return {col *  info.ycbrToRgbMat, col2 * info.ycbrToRgbMat};
}

uint32_t rgbToYuyv(const Vec3F& rgb1, const Vec3F& rgb2, const YcbcrToRgbConversionInfo& info)
{
	Vec3F ycbcr1  = rgb1 * info.rgbToYcbcrMat;
    Vec3F ycbcr2  = rgb2 * info.rgbToYcbcrMat;

    ycbcr1[0] += info.black;
    ycbcr1[1] += info.achroma;
    ycbcr1[2] += info.achroma;

    ycbcr2[0] += info.black;
    ycbcr2[1] += info.achroma;
    ycbcr2[2] += info.achroma;

    Vec3F ycbcr3 = (ycbcr1 + ycbcr2) * 0.5f;
    return YUYV(std::clamp(ycbcr1[0], info.black,    info.white),
                std::clamp(ycbcr3[1], info.chromaLo, info.chromaHi),
                std::clamp(ycbcr2[0], info.black,    info.white),
                std::clamp(ycbcr3[2], info.chromaLo, info.chromaHi));
}

uint64_t rgbToYuyvU16(const Vec3F& rgb1, const Vec3F& rgb2, const YcbcrToRgbConversionInfo& info)
{
	Vec3F ycbcr1 = rgb1 * info.rgbToYcbcrMat;
    Vec3F ycbcr2 = rgb2 * info.rgbToYcbcrMat;

    ycbcr1[0] += info.black;
    ycbcr1[1] += info.achroma;
    ycbcr1[2] += info.achroma;

    ycbcr2[0] += info.black;
    ycbcr2[1] += info.achroma;
    ycbcr2[2] += info.achroma;
    
    Vec3F ycbcr3 = (ycbcr1 + ycbcr2) * 0.5f;

    return YUYV_U16(std::clamp(ycbcr1[0],  info.black,    info.white),
                    std::clamp(ycbcr3[1], info.chromaLo, info.chromaHi),
                    std::clamp(ycbcr2[0], info.black,    info.white),
                    std::clamp(ycbcr3[2], info.chromaLo, info.chromaHi));
}



}