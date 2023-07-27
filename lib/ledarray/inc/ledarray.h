#pragma once

#include <vector>
#include <cstdint>

namespace luled
{

template<typename T>
struct Led
{
	T r, g, b;
};

class LedArray
{
public:
	LedArray(size_t count);
	~LedArray();

	void setLed(size_t index, uint8_t r, uint8_t g, uint8_t b);
	const Led<uint8_t>& getLed(size_t index) const { return leds[index]; }
	size_t size() const { return leds.size(); }

private:
	std::vector<Led<uint8_t>> leds;
};

} // namespace luled