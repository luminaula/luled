#pragma once

#include "shape.h"

namespace luled
{

class Wave : public Shape
{
public:
	Wave(
		float x1,
		float y1,
		float length,
		float angle,
		float amplitude,
		float frequency,
		float phase,
		uint32_t color,
		float distanceAmplitudeFactor = .0f,
		float distanceFrequencyFactor = .0f
	);
	~Wave() = default;

	void draw(FrameBuffer& fb) const override;
	void shift(float phase);
	void rot(float angle);

private:
	float x1, y1, length, angle;
	float amplitude, frequency, phase;
	float distanceAmplitudeFactor, distanceFrequencyFactor;
	uint32_t color;
};


} // namespace luled
