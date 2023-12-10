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
	Line2 line2(display.width() / 2, display.height() / 2, 2560, 0, 0xFF0000FF);
	Line2 line3(display.width() / 2, display.height() / 2, 2560, -M_PI, 0xFF0000FF);

	Wave wave(
		display.width() / 2,
		display.height() / 2,
		2560,
		0,
		0.01f,
		0.1f,
		0,
		0xFFFF0000,
		500.f,
		0.1f
	);
	Wave wave2(
		display.width() / 2,
		display.height() / 2,
		2560,
		M_PI,
		0.01f,
		0.1f,
		0,
		0xFF00FF00,
		500.f,
		0.1f
	);

	Wave wave3(0, 0, 1500, 0, 0.001, 0.0001, 0, 0xFFFF0000, -500.f, .001f);
	Wave wave4(0, 0, 1500, 0, 0.001, 0.0001, 0, 0xFF00FF00, 500.f, .001f);

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

				//display.drawShape(sq);
				// display.drawSquare(i*10, j * 20 + 500, 10, led.r, led.g, led.b);
			}
		}
		// display.drawShape(line);
		display.drawShape(line2);
		display.drawShape(line3);
		display.drawShape(wave);
		display.drawShape(wave2);

		enum { posMin = -10, posMax = 10, posPerLoop = 100 };
		static bool posDir = 1;

		static int pos = 0;
		if (posDir > 0)
		{
			pos+=posPerLoop;
		}
		else
		{
			pos-=posPerLoop;
		}
		if (pos > posMax)
		{
			posDir = 0;
		}
		else if (pos < posMin)
		{
			posDir = 1;
		}
		float x, y, angle;
		if (pos < 0)
		{
			std::tie(x, y, angle) = wave2.sampleAndAngle(-pos);
			angle = angle + M_PI;
		}
		else
		{
			std::tie(x, y, angle) = wave.sampleAndAngle(pos);
		}

		wave3.setStartingPoint(x, y);
		wave3.setAngle(angle);
		wave4.setStartingPoint(x, y);
		wave4.setAngle(angle + M_PI);


		display.drawShape(wave3);
		display.drawShape(wave4);

		auto [x1, y1] = wave3.sample(std::abs(pos));
		auto [x2, y2] = wave4.sample(std::abs(pos));
		auto [x3, y3] = wave3.sample(std::abs(pos/2));
		auto [x4, y4] = wave4.sample(std::abs(pos/2));

		display.drawShape(Line(x1, y1, x3, y3, 0xFF00FF00));
		display.drawShape(Line(x3, y3, x2, y2, 0xFF00FF00));
		display.drawShape(Line(x2, y2, x4, y4, 0xFFFF0000));
		display.drawShape(Line(x4, y4, x1, y1, 0xFFFF0000));


		line2.rot(0.001f);
		line3.rot(0.001f);
		wave.shift(0.1f);
		wave2.shift(-0.1f);
		wave3.shift(0.05f);
		wave4.shift(-0.05f);

		wave.rot(0.005f);
		wave2.rot(0.005f);
		//wave3.rot(0.01f);

		counter++;
		//  ledArray.rot(2);

		display.update();
	}

	return EXIT_SUCCESS;
}
