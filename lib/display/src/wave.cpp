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
	for(float i = 0; i < length; i++)
	{
		const float tmpAmplitude = amplitude + amplitude * i * distanceAmplitudeFactor;
		const float tmpFrequency = frequency * i + frequency * i * distanceFrequencyFactor;
		std::pair<float, float> normal = {std::cos(angle + M_PI / 2), std::sin(angle + M_PI / 2)};
		float x = x1 + i * std::cos(angle) + std::sin(phase + tmpFrequency / amplitude) * normal.first * tmpAmplitude;
		float y = y1 + i * std::sin(angle) + std::sin(phase + tmpFrequency / amplitude) * normal.second * tmpAmplitude;
		fb.drawPixel(x, y, color);
	}
}
/* void Wave::draw(FrameBuffer& fb) const
{
    for(float i = 0; i < length; i++)
    {
        const float tmpAmplitude = amplitude + amplitude * (1.0f - distanceAmplitudeFactor) * i;
		const float tmpFrequency = frequency * i;
        std::pair<float, float> normal = {std::cos(angle + M_PI / 2), std::sin(angle + M_PI / 2)};
        float x = x1 + i * std::cos(angle) + std::sin(phase + tmpFrequency * i / amplitude) * normal.first * tmpAmplitude;
        float y = y1 + i * std::sin(angle) + std::sin(phase + tmpFrequency * i / amplitude) * normal.second * tmpAmplitude;
        fb.drawPixel(x, y, color);
    }
} */


} // namespace luled
