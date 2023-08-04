#pragma once

#include <cstdint>

namespace luled
{

struct FrameBuffer
{
	FrameBuffer(int width, int height) : data(new uint32_t[width*height]), width(width), height(height) {}
	~FrameBuffer() { if(data) delete[] data; }


	void drawPixel(int x, int y, uint32_t color);

	void drawSquare(int x, int y, int size, uint32_t color);

	void fill(uint32_t color);

	uint32_t* data;
	int width;
	int height;
};

}