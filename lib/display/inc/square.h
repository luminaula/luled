#pragma once

#include "shape.h"

namespace luled
{

class Square : public Shape
{
public:
	Square(int x, int y, uint32_t color, int size);
	~Square() = default;
	void draw(FrameBuffer& fb) const override;
private:
	int x, y, size;
	uint32_t color;
};


} // namespace luled