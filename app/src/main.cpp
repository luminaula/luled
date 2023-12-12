#include <stdlib.h> // EXIT_SUCCESS

#include <iostream>
#include <thread>
#include <tuple>

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

int counter = 0;
int counter2 = 0;


void worker(std::stop_token st, std::reference_wrapper<FrameBuffer> fb, float zoom, std::pair<float, float> center)
{
	Syccliva syccl;
	while(!st.stop_requested())
	{
		mandelBrotSycl(syccl, fb.get().data, fb.get().width, fb.get().height, zoom, center);
		zoom = zoom * 1.001f + 0.001f;
		counter++;

	}
}

int main(int, char**)
{
	Display display(2560, 1440);

	float zoom = 0.25f;
	std::pair<float, float> center = {-0.1528f, 1.0397};

	std::jthread workerThread(worker, std::reference_wrapper<FrameBuffer>(display.frameBuffer()), zoom, center);

	while(!display.isClosed())
	{
		counter2++;

		display.pollEvents();

		display.update();

		std::cout << counter - counter2 << std::endl;
	}

	return EXIT_SUCCESS;
}
