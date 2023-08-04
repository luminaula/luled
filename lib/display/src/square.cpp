#include "square.h"

namespace luled
{

Square::Square(int x, int y, uint32_t color, int size) :
	x(x), y(y), color(color), size(size)
{}

void Square::draw(FrameBuffer& fb) const
{
	fb.drawSquare(x, y, size, color | 0xFF000000);
}

}