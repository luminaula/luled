#include "lelu_decode.h"

#include <iostream>

// include vulkan
#include <vulkan/vulkan.hpp>


extern "C"
{

#include <libavcodec/avcodec.h>
#include <libavutil/hwcontext_vulkan.h>

}

namespace luled
{



struct LeLuDecoder::Impl
{
	int a;

	void init()
	{
	}
};

LeLuDecoder::LeLuDecoder() :
	impl(std::make_shared<Impl>())
{}

LeLuDecoder::~LeLuDecoder()
{}

void foo_decode()
{
	std::cout << "Foo" << std::endl;
}


} // namespace luled

