#pragma once


#include <memory>

namespace luled
{


class LeLuLoader
{
public:
	LeLuLoader();
private:
	struct Impl;
	std::shared_ptr<Impl> impl;
};

} // namespace luled