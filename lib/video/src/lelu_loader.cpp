#include "lelu_loader.h"

#include <iostream>

#include "vulkan/vulkan.hpp"
#include "vulkan/vulkan_video.hpp"

#include "VkBootstrap.h"

namespace luled
{

struct LeLuLoader::Impl
{

	vk::Instance instance;
	vk::Device device;
	vk::Queue computeQueue;
	vk::Queue transferQueue;
	vk::Queue graphicsQueue;

	vkb::Instance vkbInstance;
	vkb::InstanceBuilder builder;
	vkb::Device vkbDevice;

	vk::CommandPool commandPool;

	Impl()
	{
		auto system_info_ret = vkb::SystemInfo::get_system_info();

		if(!system_info_ret)
		{
			std::cerr << "Could not get system info: " << system_info_ret.error().message() << std::endl;
		}

		auto system_info = system_info_ret.value();

		auto extensions = {
			"VK_KHR_video_queue",
			"VK_KHR_video_decode_queue",
			"VK_KHR_video_decode_h264",
			"VK_KHR_video_decode_h265",
		};

		builder.set_app_name("lelu")
			.set_engine_name("lelu Engine")
			.set_headless()
			.request_validation_layers()
			.require_api_version(1, 3, 0)
			.use_default_debug_messenger();

		auto inst_ret = builder.build();

		if(!inst_ret)
		{
			std::cerr << "Could not create a Vulkan instance: " << inst_ret.error().message() << std::endl;
		}

		vkbInstance = inst_ret.value();

		vkb::PhysicalDeviceSelector selector{ vkbInstance };

		auto phys_ret = selector.set_minimum_version(1, 3)
			.add_required_extensions(extensions)
			.select();

		if(!phys_ret)
		{
			std::cerr << "Could not find a suitable vulkan device " << phys_ret.error().message() << std::endl;
		}

		vkb::DeviceBuilder deviceBuilder{ phys_ret.value() };

		auto dev_ret = deviceBuilder.build();

		if(!dev_ret)
		{
			std::cerr << "Could not create a Vulkan device: " << dev_ret.error().message() << std::endl;
		}

		vkbDevice = dev_ret.value();

		auto compute_queue_ret = vkbDevice.get_queue(vkb::QueueType::compute);

		if(!compute_queue_ret)
		{
			std::cerr << "Could not get a compute queue: " << compute_queue_ret.error().message() << std::endl;
		}

		auto transfer_queue_ret = vkbDevice.get_queue(vkb::QueueType::transfer);

		if(!transfer_queue_ret)
		{
			std::cerr << "Could not get a transfer queue: " << transfer_queue_ret.error().message() << std::endl;
		}

		auto graphics_queue_ret = vkbDevice.get_queue(vkb::QueueType::graphics);

		if(!graphics_queue_ret)
		{
			std::cerr << "Could not get a graphics queue: " << graphics_queue_ret.error().message() << std::endl;
		}

		instance = vkbInstance.instance;
		device = vkbDevice.device;
		computeQueue = compute_queue_ret.value();
		transferQueue = transfer_queue_ret.value();
		graphicsQueue = graphics_queue_ret.value();

		vk::CommandPoolCreateInfo commandPoolInfo{};
		commandPoolInfo.queueFamilyIndex = vkbDevice.get_queue_index(vkb::QueueType::compute).value();
		commandPoolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;

		commandPool = device.createCommandPool(commandPoolInfo);

	}

	~Impl()
	{
		device.destroyCommandPool(commandPool);
		vkb::destroy_device(vkbDevice);
		vkb::destroy_instance(vkbInstance);

	}

	int a;
};


LeLuLoader::LeLuLoader()
	: impl(std::make_shared<Impl>())
{
}
	
} // namespace luled