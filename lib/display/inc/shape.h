#pragma once

#include "framebuffer.h"

namespace luled
{

class Shape
{
public:
	Shape() = default;
	virtual ~Shape() = default;
	virtual void draw(FrameBuffer& fb) const = 0;
};

} // namespace luled
