#include <stdlib.h> // EXIT_SUCCESS

#include "display.h"

using namespace luled;

int main(int, char**)
{
	Display display(2560, 1440);
	auto counter = 0;
	while(!display.isClosed())
	{
		display.pollEvents();
		display.clear(0x00000000);
		for(auto j = 0; j < 72; j++)
		{
			for(auto i = 0; i < 256; i++)
			{
				uint8_t r = i,
						g = j * 3,
						b = counter;

				display.drawSquare(i*10, j * 20, 10, r, g, b);
			}
		}
		counter++;
		display.update();
	}
	return EXIT_SUCCESS;
}