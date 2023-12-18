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

void mandelBrotSycl(Syccliva& syccliva, uint32_t* fb, int w, int h, MandelReal zoom, std::pair<MandelReal, MandelReal> center)
{
	mandelbro(syccliva.data(), fb, w, h, zoom, center);
}
