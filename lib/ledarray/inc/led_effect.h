#pragma once

#include <functional>

#include "ledarray.h"

namespace luled
{

class LedEffect
{
public:
	LedEffect(std::function<void(LedArray&, uint8_t, uint8_t, uint8_t, int)> updateFunc, uint8_t r, uint8_t g, uint8_t b, int index = 0);
	~LedEffect();

	void operator()(LedArray& leds) { updateFunc(leds, r, g, b, index); }

	LedEffect& operator++() { ++index; return *this; }
	LedEffect& operator--() { --index; return *this; }

	LedEffect& operator+=(int n) { index += n; return *this; }
	LedEffect& operator-=(int n) { index -= n; return *this; }

	LedEffect& operator=(int n) { index = n; return *this; }

	LedEffect operator++(int) { auto tmp = *this; ++index; return tmp; }
	LedEffect operator--(int) { auto tmp = *this; --index; return tmp; }

private:
	std::function<void(LedArray&, uint8_t, uint8_t, uint8_t, int)> updateFunc;
	int index;
	uint8_t r, g, b;
};

} // namespace luled