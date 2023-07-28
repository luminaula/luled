#include <stdlib.h> // EXIT_SUCCESS

#include "display.h"
#include "ledarray.h"

using namespace luled;

int main(int, char**)
{
	Display display(2560, 1440);
	LedArray ledArray(256);
	for(auto i = 0; i < ledArray.size(); i++)
	{
		ledArray.setLed(i, i, i, i);
	}
	auto counter = 0;
	while(!display.isClosed())
	{
		display.pollEvents();
		display.clear(0x00000000);
		for(auto j = 0; j < 5; j++)
		{
			for(auto i = 0; i < ledArray.size(); i++)
			{
				auto& led = ledArray[i];

				display.drawSquare(i*10, j * 20 + 500, 10, led.r, led.g, led.b);
			}
		}
		counter++;
		ledArray.rot(1);
		display.update();
	}
	return EXIT_SUCCESS;
}