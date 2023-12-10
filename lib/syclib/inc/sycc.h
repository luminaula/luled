#pragma once

#include <stdint.h>

#include <tuple>

void sycc();


void mandelBrotSycl(uint32_t* fb, int w, int h, float zoom, std::pair<float, float> center);