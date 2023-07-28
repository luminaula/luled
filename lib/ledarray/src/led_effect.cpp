#include "led_effect.h"

namespace luled
{

LedEffect::LedEffect(std::function<void(LedArray&, uint8_t, uint8_t, uint8_t, int)> updateFunc, uint8_t r, uint8_t g, uint8_t b, int index) :
	updateFunc(updateFunc),
	r(r),
	g(g),
	b(b),
	index(index)
{}

LedEffect::~LedEffect()
{}

} // namespace luled
