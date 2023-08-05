#include <stdlib.h> // EXIT_SUCCESS

#include "display.h"
#include "square.h"
#include "line.h"
#include "wave.h"
#include "ledarray.h"
#include "led_effect.h"
#include "color.h"
#include "color_vec.h"
#include "color_transfer.h"

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
	Line line(display.width() / 2, display.height() / 2, display.width() / 2 + 100, display.height() / 2 + 100, 0xFF00FFFF);
	Line2 line2(display.width() / 2, display.height() / 2, 100.0f, 0, 0xFF00FFFF);
	Line2 line3(display.width() / 2, display.height() / 2, 100.0f, -M_PI, 0xFF00FFFF);

	Wave wave(500, 500, 2560, 0, 0, 0xFFFF0000);

	color::Vec3F v1(1, 0, 0);

	auto counter = 0;
	while(!display.isClosed())
	{
		display.pollEvents();
		display.clear(0x00000000);
		for(auto i = 0; i < ledArray.size(); i++)
		{
			ledArray.setLed(i, 0, 0, 0);
		}

		++glowEffectWhite(ledArray);
		

		for(auto j = 0; j < 5; j++)
		{
			for(auto i = 0; i < ledArray.size(); i++)
			{
				auto& led = ledArray[i];
				
				Square sq(i*10, j * 20 + 500, led.r << 16 | led.g << 8 | led.b, 10);

				display.drawShape(sq);
				// display.drawSquare(i*10, j * 20 + 500, 10, led.r, led.g, led.b);
			}
		}
		// display.drawShape(line);
		display.drawShape(line2);
		display.drawShape(line3);
		display.drawShape(wave);
		line2.rot(0.01f);
		line3.rot(0.01f);
		wave.shift(0.1f);
		wave.rot(0.01f);
		
		counter++;
		//  ledArray.rot(2);

		display.update();
	}

	return EXIT_SUCCESS;
}