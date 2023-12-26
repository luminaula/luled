#pragma once

#include <stdint.h>

#include <tuple>

using MandelReal = float;

#ifdef WITH_SYCL
#include "syclivat.h"
#endif

class Syccliva
{
public:
	Syccliva();

	void* data() { return d; }
private:
	void* d;
};


void sycc();


void mandelBrotSycl(Syccliva& syccliva, uint32_t* fb, int w, int h, MandelReal zoom, std::pair<MandelReal, MandelReal> center);
