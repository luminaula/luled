#include "lelu_loader.h"

#include <iostream>

#include "vulkan/vulkan.h"
#include "vulkan/vulkan.hpp"

namespace luled
{

struct LeLuLoader::Impl
{
	vk::Instance instance;
	vk::PhysicalDevice physicalDevice;
	vk::Device device;
	vk::Queue queue;
	vk::CommandPool commandPool;
	vk::CommandBuffer commandBuffer;
	vk::Fence fence;
	vk::Semaphore semaphore;
	vk::Image image;

	Impl()
	{
		instance = vk::createInstance({});

		std::vector<vk::PhysicalDevice> physicalDevices = instance.enumeratePhysicalDevices();

		// Print device names
		for (const auto& physicalDevice : physicalDevices)
		{
			vk::PhysicalDeviceProperties properties = physicalDevice.getProperties();
			std::cout << properties.deviceName << std::endl;
		}

		physicalDevice = physicalDevices[0]; // Select the first physical device for simplicity

		device = physicalDevice.createDevice({});

		queue = device.getQueue(0, 0); // Get the first queue family and the first queue in that family

		vk::CommandPoolCreateInfo commandPoolCreateInfo;
		commandPoolCreateInfo.queueFamilyIndex = 0; // Use the first queue family
		commandPool = device.createCommandPool(commandPoolCreateInfo);

		vk::CommandBufferAllocateInfo commandBufferAllocateInfo;
		commandBufferAllocateInfo.commandPool = commandPool;
		commandBufferAllocateInfo.level = vk::CommandBufferLevel::ePrimary;
		commandBufferAllocateInfo.commandBufferCount = 1;
		commandBuffer = device.allocateCommandBuffers(commandBufferAllocateInfo)[0];

	}

	int a;
};


LeLuLoader::LeLuLoader()
	: impl(std::make_shared<Impl>())
{
}
	
} // namespace luled