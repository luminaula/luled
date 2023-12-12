#pragma once

#include <stdint.h>

#include <memory>
#include <tuple>

#include "sycc.h"


void* initSyccs();

void sgemmSycl(float* A, float* B, float* C, int N, int M, int K);

void sycli();

void mandelbro(void* syccliva, uint32_t* fb, int width, int height, float zoom, std::pair<float, float> center);