#pragma once

#include <memory>

namespace luled
{


class LeLuDecoder
{
public:
	LeLuDecoder();
	~LeLuDecoder();
	

	void decode();

private:
	struct Impl;
	std::shared_ptr<Impl> impl;
};

void foo_decode();

}