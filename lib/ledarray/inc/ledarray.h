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
	const Led<uint8_t>& getLed(size_t index) const { return leds[(index + base) % leds.size()]; }
	size_t size() const { return leds.size(); }

	void rotr(int n = 1);
	void rotl(int n = 1);
	void rot(int n = 1);

	const Led<uint8_t>& operator[](size_t index) const { return getLed(index); }

private:
	std::vector<Led<uint8_t>> leds;
	int base;
};

} // namespace luled