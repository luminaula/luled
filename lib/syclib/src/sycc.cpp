#include "sycc.h"


#ifdef WITH_SYCL
#include "syclivat.h"
#endif

Syccliva::Syccliva()
{
#ifdef WITH_SYCL
	d = initSyccs();
#endif
}

void sycc()
{
#ifdef WITH_SYCL
	sycli();
#endif
}

void mandelBrotSycl(Syccliva& syccliva, uint32_t* fb, int w, int h, MandelReal zoom, std::pair<MandelReal, MandelReal> center)
{
#ifdef WITH_SYCL
	mandelbro(syccliva.data(), fb, w, h, zoom, center);
#endif
}
