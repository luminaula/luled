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

#include "sycc.h"

using namespace luled;

int main(int, char**)
{
	Display display(2560, 1440);
	size_t counter = 0;

	while(true)
	{
		counter++;

		display.pollEvents();
		sycc();

		display.update();
	}

	return EXIT_SUCCESS;
}
