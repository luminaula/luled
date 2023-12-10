#include <stdlib.h> // EXIT_SUCCESS

#include <iostream>

#include "display.h"
#include "square.h"
#include "line.h"
#include "wave.h"
#include "ledarray.h"
#include "led_effect.h"
#include "color.h"
#include "color_vec.h"
#include "color_transfer.h"

#include "sycc.h"

using namespace luled;

int main(int, char**)
{
	Display display(2560, 1440);
	size_t counter = 0;

	float zoom = 0.25f;
	std::pair<float, float> center = {-0.1528f, 1.0397};

	while(true)
	{
		counter++;

		display.pollEvents();
		auto& fb = display.frameBuffer();

		mandelBrotSycl(fb.data, fb.width, fb.height, zoom, center);
		

		zoom = zoom * 1.01f + 0.001f;
		std::cout << counter << std::endl;

		display.update(fb);
	}

	return EXIT_SUCCESS;
}
