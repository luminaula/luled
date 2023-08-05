#pragma once

#include "shape.h"

namespace luled
{

class Wave : public Shape
{
public:
	Wave(float x1, float y1, float amplitude, float length, float angle, float phase, uint32_t color);
	~Wave() = default;

	void draw(FrameBuffer& fb) const override;
	void shift(float phase);
	void rot(float angle);

private:
	float x1, y1, length, angle, amplitude;
	float phase;
	uint32_t color;
};


} // namespace luled
