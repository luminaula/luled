#include "sycc.h"



#include "syclivat.h"

void sycc()
{
	sycli();
}

void mandelBrotSycl(uint32_t* fb, int w, int h, float zoom, std::pair<float, float> center)
{
	mandelbro(fb, w, h, zoom, center);
}
