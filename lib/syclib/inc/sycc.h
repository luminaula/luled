#pragma once

#include <stdint.h>

#include <tuple>

#include "syclivat.h"

class Syccliva
{
public:
	Syccliva();

	void* data() { return d; }
private:
	void* d;
};


void sycc();


void mandelBrotSycl(Syccliva& syccliva, uint32_t* fb, int w, int h, float zoom, std::pair<float, float> center);