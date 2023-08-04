#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "framebuffer.h"
#include "shape.h"

namespace luled
{


class Display
{
public:
	Display(int width, int height);
	~Display();

	void init(int width, int height);
	void update();
	void update(FrameBuffer& frameBuffer);
	void clear(float r, float g, float b, float a);
	void clear(uint32_t color);
	void pollEvents();
	bool isClosed();

	void drawSquare(const int x,
					const int y,
					const int size,
					const float r,
					const float g,
					const float b,
					const float a = 1.0f);

	void drawSquare(const int x,
					const int y,
					const int size,
					const uint8_t r,
					const uint8_t g,
					const uint8_t b,
					const uint8_t a = 255);

	void drawSquare(
					const int x,
					const int y,
					const int size,
					const uint32_t color);

	void fill(uint32_t color);

	void drawShape(const Shape& shape);
	void drawShapes(const std::vector<Shape&>& shapes);

	int width() const { return fb.width; }
	int height() const { return fb.height; }

private:
	SDL_Texture* texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	FrameBuffer fb;
};


}