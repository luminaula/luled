#pragma once

#include "shape.h"

namespace luled
{

class Line : public Shape
{
public:
	Line(float x1, float y1, float x2, float y2, uint32_t color);
	~Line() = default;

	void draw(FrameBuffer& fb) const override;
private:
	float x1, y1, x2, y2;
	uint32_t color;
};

class Line2 : public Shape
{
public:
	Line2(float x1, float y1, float length, float angle, uint32_t color);
	~Line2() = default;

	void rot(float angle);

	void draw(FrameBuffer& fb) const override;
private:
	float x1, y1, length, angle;
	uint32_t color;
};

} // namespace luled