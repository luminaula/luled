#include "ledarray.h"

namespace luled
{

LedArray::LedArray(size_t count)
{
	leds.resize(count);
}

LedArray::~LedArray()
{}

void LedArray::setLed(size_t index, uint8_t r, uint8_t g, uint8_t b)
{
	auto& l = leds[index];
	l.r = r;
	l.g = g;
	l.b = b;
}

} // namespace luled