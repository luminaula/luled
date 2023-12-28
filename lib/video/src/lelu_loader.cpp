#include "lelu_loader.h"

#include <iostream>

#include "vulkan/vulkan.h"
#include "vulkan/vulkan.hpp"

#include "VkBootstrap.h"

namespace luled
{

struct LeLuLoader::Impl
{

	vkb::InstanceBuilder builder;

	Impl()
	{
		vkb::InstanceBuilder builder;
		auto inst_ret = builder.set_app_name("lelu")
			.request_validation_layers()
			.require_api_version(1, 3, 0)
			.use_default_debug_messenger()
			.build();

		vkb::PhysicalDeviceSelector selector{ inst_ret.value() };

		auto phys_ret = selector.set_minimum_version(1, 1)
			.set_minimum_version(1, 2)
			.require_dedicated_transfer_queue ()
			.select();

		// vkb::DeviceBuilder deviceBuilder{ inst_ret.value() };
		// vkb::Device vkbDevice = deviceBuilder.build().value();

	}

	int a;
};


LeLuLoader::LeLuLoader()
	: impl(std::make_shared<Impl>())
{
}
	
} // namespace luled