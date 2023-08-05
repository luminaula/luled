#pragma once

#include "shape.h"
#include <tuple>

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
	std::pair<float, float> sample(const float pos) const;
	void setStartingPoint(float x, float y){ x1 = x; y1 = y;};
	void setAngle(float angle){ this->angle = angle; };
	std::tuple<float, float, float> sampleAndAngle(const float pos) const;

private:
	float x1, y1, length, angle;
	float amplitude, frequency, phase;
	float distanceAmplitudeFactor, distanceFrequencyFactor;
	uint32_t color;
};


} // namespace luled
