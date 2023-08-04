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

void Wave::draw(FrameBuffer& fb) const
{
	for(auto i = 0; i < length; i++)
	{
		fb.drawPixel(x1 + i, y1 + std::sin(i * 0.1 + phase) * 10, color);
	}

}

} // namespace luled