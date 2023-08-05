#include "wave.h"

#include <cmath>

namespace luled
{

Wave::Wave(float x1, float y1, float length, float angle, float phase, uint32_t color) :
	x1(x1), y1(y1), length(length), angle(angle), phase(phase), color(color)
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
	for(auto i = 0; i < length; i++)
	{
		std::pair<float, float> normal = {std::cos(angle + M_PI / 2), std::sin(angle + M_PI / 2)};
		float x = x1 + i * std::cos(angle) + std::cos(phase + i) * 100 * normal.first;
		float y = y1 + i * std::sin(angle) + std::sin(phase + i) * 100 * normal.second;
		fb.drawPixel(x, y, color);
	}
}

} // namespace luled