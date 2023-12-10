#include "wave.h"

#include <cmath>

namespace luled
{

Wave::Wave(
	float x1,
	float y1,
	float length,
	float angle,
	float amplitude,
	float frequency,
	float phase,
	uint32_t color,
	float distanceAmplitudeFactor,
	float distanceFrequencyFactor
)	:
	x1(x1),
	y1(y1),
	length(length),
	angle(angle),
	amplitude(amplitude),
	frequency(frequency),
	phase(phase),
	color(color),
	distanceAmplitudeFactor(distanceAmplitudeFactor),
	distanceFrequencyFactor(distanceFrequencyFactor)
{}


void Wave::shift(float phase)
{
	this->phase += phase;
	if(this->phase < 0)
		this->phase += 2 * M_PI;
	this->phase = std::fmod(this->phase, 2 * M_PI);
}

void Wave::rot(float angle)
{
	this->angle += angle;
	if(this->angle < 0)
		this->angle += 2 * M_PI;
	this->angle = std::fmod(this->angle, 2 * M_PI);
}

void Wave::draw(FrameBuffer& fb) const
{
	const float epsilon = 0.1;
	float iPlus = 0.1f;
	float x1 = 0.0f, y1 = 0.0f;
	for(float i = 0; i < length; i += iPlus)
	{
		const auto [x, y] = sample(i);
		fb.drawPixel(x, y, color);
		if (i != 0)
		{
			if (std::abs(x - x1) < epsilon
				|| std::abs(y - y1) < epsilon)
			{
				iPlus += 0.1f;
			}
			else
			{
				iPlus -= 0.1f;
			}
		}
		x1 = x;
		y1 = y;
	}
}

std::pair<float, float> Wave::sample(const float pos) const
{
	const float tmpAmplitude = amplitude + amplitude * pos * distanceAmplitudeFactor;
	const float tmpFrequency = frequency * pos + frequency * pos * distanceFrequencyFactor;
	std::pair<float, float> normal = {std::cos(angle + M_PI / 2), std::sin(angle + M_PI / 2)};
	float x = x1 + pos * std::cos(angle) + std::sin(phase + tmpFrequency / amplitude) * normal.first * tmpAmplitude;
	float y = y1 + pos * std::sin(angle) + std::sin(phase + tmpFrequency / amplitude) * normal.second * tmpAmplitude;
	return {x, y};
}

std::tuple<float, float, float> Wave::sampleAndAngle(const float pos) const
{
	const auto [x1, y1] = sample(pos);
	const auto [x2, y2] = sample(pos + 0.1f);
	const float angle = std::atan2(y2 - y1, x2 - x1);
	return {x1, y1, angle + M_PI / 2};
}


} // namespace luled
