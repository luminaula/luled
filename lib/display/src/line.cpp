#include "line.h"

#include <cmath>

namespace luled
{

Line::Line(float x1, float y1, float x2, float y2, uint32_t color) :
	x1(x1), y1(y1), x2(x2), y2(y2), color(color)
{}

void Line::draw(FrameBuffer& fb) const
{
	// Bresenham's line algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

	int x1 = this->x1;
	int y1 = this->y1;
	int y2 = this->y2;
	int x2 = this->x2;

	int dx = std::abs(x2 - x1);
	int dy = std::abs(y2 - y1);
	int sx, sy;
	if (x1 < x2) sx = 1; else sx = -1;
	if (y1 < y2) sy = 1; else sy = -1;
	int err = dx - dy;
	while (true)
	{
		fb.drawPixel(x1, y1, color);
		if (x1 == x2 && y1 == y2) break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

Line2::Line2(float x1, float y1, float length, float angle, uint32_t color) :
	x1(x1), y1(y1), length(length), angle(angle), color(color)
{}

void Line2::rot(float angle)
{
	this->angle += angle;
	if(this->angle < 0)
		this->angle += 2 * M_PI;
	this->angle = std::fmod(this->angle, 2 * M_PI);
}

void Line2::draw(FrameBuffer& fb) const
{
	float x2 = x1 + length * std::cos(angle);
	float y2 = y1 + length * std::sin(angle);
	Line(x1, y1, x2, y2, color).draw(fb);
}

}