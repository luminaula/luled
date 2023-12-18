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

void worker(
	std::stop_token st,
	std::reference_wrapper<FrameBuffer> fb,
	std::reference_wrapper<MandelReal> zoom,
	std::reference_wrapper<MandelReal> zoomPerFrame,
	std::reference_wrapper<std::pair<MandelReal, MandelReal>> center,
	std::reference_wrapper<MandelReal> xPerFrame,
	std::reference_wrapper<MandelReal> yPerFrame,
	std::reference_wrapper<MandelReal> multiplier
)
{
	Syccliva syccl;
	while(!st.stop_requested())
	{
		mandelBrotSycl(syccl, fb.get().data, fb.get().width, fb.get().height, zoom, center);
		counter++;

		//input handling
		//zoom.get() *= std::pow(zoomPerFrame, multiplier);
		//center.get().first += xPerFrame / zoom * multiplier;
		//center.get().second += yPerFrame / zoom * multiplier;

		//calculate and cout ups
		static auto lastTime = std::chrono::steady_clock::now();
		static int frames = 0;
		auto currentTime = std::chrono::steady_clock::now();
		frames++;
		if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() > 1000)
		{
			std::cout << "UPS: " << frames << std::endl;
			frames = 0;
			lastTime = currentTime;
		}
	}
}

int main(int, char**)
{
	Display display(2560, 1440);

	MandelReal zoom = 46.450;//0.25f;
	MandelReal zoomPerFrame = 1.00f;
	MandelReal xPerFrame = 0.0f;
	MandelReal yPerFrame = 0.0f;

	MandelReal multiplier = 1.0f;

	display.input->addKeyCb_multiply(SDLK_q, std::ref(zoomPerFrame), 1.001);
	display.input->addKeyCb_multiply(SDLK_a, std::ref(zoomPerFrame), 0.999);
	display.input->addKeyCb_add(SDLK_UP, std::ref(yPerFrame), -0.001);
	display.input->addKeyCb_add(SDLK_DOWN, std::ref(yPerFrame), 0.001);
	display.input->addKeyCb_add(SDLK_RIGHT, std::ref(xPerFrame), 0.001);
	display.input->addKeyCb_add(SDLK_LEFT, std::ref(xPerFrame), -0.001);

	display.input->addKeyCb_multiply(SDLK_1, std::ref(multiplier), 2.);
	display.input->addKeyCb_multiply(SDLK_2, std::ref(multiplier), 3.);
	display.input->addKeyCb_multiply(SDLK_3, std::ref(multiplier), 4.);
	display.input->addKeyCb_multiply(SDLK_4, std::ref(multiplier), 5.);

	display.input->addKeyCb_ignoreRelease(SDLK_w);

	std::pair<MandelReal, MandelReal> center = {-0.732613, 0.212312};//{-0.1528f, 1.0397};

	std::jthread workerThread(
		worker,
		std::reference_wrapper<FrameBuffer>(display.frameBuffer()),
		std::ref(zoom),
		std::ref(zoomPerFrame),
		std::ref(center),
		std::ref(xPerFrame),
		std::ref(yPerFrame),
		std::ref(multiplier)
	);

	while(!display.pollEvents_isClosed())
	{
		//const uint32_t frameStart = SDL_GetTicks();
		counter2++;

		//display.pollEvents();

		display.update();

		//std::cout << counter - counter2 << std::endl;

		zoom *= std::pow(zoomPerFrame, multiplier);;
		center.first += xPerFrame / zoom * multiplier;
		center.second += yPerFrame / zoom * multiplier;

		//calculate and cout fps
		static auto lastTime = std::chrono::steady_clock::now();
		static int frames = 0;
		auto currentTime = std::chrono::steady_clock::now();
		frames++;
		if(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() > 1000)
		{
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			lastTime = currentTime;

			//std::cout << "Zoom: " << zoom << std::endl;
			//std::cout << "Center: " << center.first << ", " << center.second << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
