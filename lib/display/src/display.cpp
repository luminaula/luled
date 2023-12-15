#include "display.h"

namespace luled
{



Display::Display(int width, int height) : fb(width, height)
{
	init(width, height);

	input = std::make_unique<Input>();
}

Display::~Display()
{
}

void Display::init(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("LULED", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

void Display::update()
{
	update(fb);
}

void Display::update(FrameBuffer& frameBuffer)
{
	SDL_UpdateTexture(texture, NULL, (void*)frameBuffer.data, frameBuffer.width * sizeof(uint32_t));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Display::clear(float r, float g, float b, float a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

void Display::clear(uint32_t color)
{
	fill(color);
	SDL_SetRenderDrawColor(renderer, color >> 24, color >> 16, color >> 8, color);
	SDL_RenderClear(renderer);
}

bool Display::isClosed()
{
	return !window;
}

void Display::pollEvents()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			SDL_DestroyTexture(texture);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			window = nullptr;
		}
		else
		{
			input->queueEvent(e);
		}
	}
}

bool Display::pollEvents_isClosed()
{
	pollEvents();
	return isClosed();
}

void Display::drawSquare(const int x,
						 const int y,
						 const int size,
						 const float r,
						 const float g,
						 const float b,
						 const float a)
{
	drawSquare(x, y, size, (uint8_t)(r * 255), (uint8_t)(g * 255), (uint8_t)(b * 255), (uint8_t)(a * 255));
}
void Display::drawSquare(const int x,
						 const int y,
						 const int size,
						 const uint8_t r,
						 const uint8_t g,
						 const uint8_t b,
						 const uint8_t a)
{
	drawSquare(x, y, size, (uint32_t)(a << 24) | (r << 16) | (g << 8) | (b));
}

void Display::drawSquare(
						const int x,
						const int y,
						const int size,
						const uint32_t color)
{
	fb.drawSquare(x, y, size, color);
}

void Display::fill(uint32_t color)
{
	fb.fill(color);
}

void Display::drawShape(const Shape& shape)
{
	shape.draw(fb);
}

} // namespace luled
