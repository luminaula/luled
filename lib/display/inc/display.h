#pragma once

#include <SDL2/SDL.h>

namespace luled
{

struct FrameBuffer
{
	FrameBuffer(int width, int height) : data(new uint32_t[width*height]), width(width), height(height) {}
	~FrameBuffer() { if(data) delete[] data; }


	void drawSquare(int x, int y, int size, uint32_t color);

	void fill(uint32_t color);

	uint32_t* data;
	int width;
	int height;
};

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

private:
	SDL_Texture* texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
	FrameBuffer fb;
};


}