#include <stdlib.h> // EXIT_SUCCESS

#include "display.h"
#include "ledarray.h"
#include "led_effect.h"

using namespace luled;

int main(int, char**)
{
	Display display(2560, 1440);
	LedArray ledArray(256);

	int range = 10;
	std::function<void(LedArray&, uint8_t, uint8_t, uint8_t, int)> glow = [range](LedArray& leds, uint8_t r, uint8_t g, uint8_t b, int index)
	{
		index = index % leds.size();
		for(auto i = index - range; i < index + range; i++)
		{
			auto& led = leds[i];
			float intensity = 1.0f - (float)abs(i - index) / range;
			led.r = intensity * r;
			led.g = intensity * g;
			led.b = intensity * b;
		}
	};
	LedEffect glowEffectWhite(glow, 255, 255, 255, 20);
	LedEffect glowEffectRed(glow, 255, 0, 0, 40);
	auto counter = 0;
	while(!display.isClosed())
	{
		display.pollEvents();
		display.clear(0x00000000);
		for(auto i = 0; i < ledArray.size(); i++)
		{
			ledArray.setLed(i, 0, 0, 0);
		}
		glowEffectWhite(ledArray);
		glowEffectWhite++;

		glowEffectRed(ledArray);
		glowEffectRed++;
		for(auto j = 0; j < 5; j++)
		{
			for(auto i = 0; i < ledArray.size(); i++)
			{
				auto& led = ledArray[i];

				display.drawSquare(i*10, j * 20 + 500, 10, led.r, led.g, led.b);
			}
		}
		counter++;
		// ledArray.rot(2);

		display.update();
	}

	return EXIT_SUCCESS;
}