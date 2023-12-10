#pragma once

#include <stdint.h>
#include <memory>

#include <tuple>

class Syccliva
{
public:
	Syccliva();
private:
	struct Data;
	std::shared_ptr<Data> d;
};


void sgemmSycl(float* A, float* B, float* C, int N, int M, int K);

void sycli();

void mandelbro(uint32_t* fb, int width, int height, float zoom, std::pair<float, float> center);