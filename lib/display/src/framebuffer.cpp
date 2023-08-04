#include "framebuffer.h"

namespace luled
{

void FrameBuffer::drawPixel(int x, int y, uint32_t color)
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return;
	data[y * width + x] = color;
}

void FrameBuffer::drawSquare(int x, int y, int size, uint32_t color)
{
	if(x < 0 || y < 0 || x + size > width || y + size > height)
		return;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			data[(y + j) * width + (x + i)] = color;
		}
	}
}

void FrameBuffer::fill(uint32_t color)
{
	for(int i = 0; i < width*height; i++)
		data[i] = color;
}

} // namespace luled