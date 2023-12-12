#include "sycc.h"


#include "syclivat.h"


Syccliva::Syccliva()
{
	d = initSyccs();
}

void sycc()
{
	sycli();
}

void mandelBrotSycl(Syccliva& syccliva, uint32_t* fb, int w, int h, float zoom, std::pair<float, float> center)
{
	mandelbro(syccliva.data(), fb, w, h, zoom, center);
}
