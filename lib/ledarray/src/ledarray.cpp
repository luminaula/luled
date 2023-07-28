#include "ledarray.h"

namespace luled
{

LedArray::LedArray(size_t count) :
	base(0)
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

void LedArray::rotr(int n)
{
	base -= n;
}

void LedArray::rotl(int n)
{
	rotr(-n);
}

void LedArray::rot(int n)
{
	rotr(n);
}

} // namespace luled