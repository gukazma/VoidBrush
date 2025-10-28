// RHI/impl/DeviceVulkan.h
#pragma once
#include "../Device.h"
#include <cassert>
#include <vector>
#include <vulkan/vulkan.h>

namespace RHI
{

template <> class Device<VulkanBackend>
{
  public:
    using NativeDevice = VkDevice;
    using NativeInstance = VkInstance;
    using NativePhysicalDevice = VkPhysicalDevice;

    Device(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device,
           const std::vector<VkQueueFamilyProperties> &queueFamilies)
        : m_instance(instance), m_physicalDevice(physicalDevice), m_device(device), m_queueFamilies(queueFamilies)
    {
        for (uint32_t i = 0; i < m_queueFamilies.size(); ++i)
        {
            if (m_queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                m_graphicsQueueFamilyIndex = i;
                vkGetDeviceQueue(m_device, i, 0, &m_graphicsQueue);
                break;
            }
        }
        assert(m_graphicsQueue != VK_NULL_HANDLE && "No graphics queue found!");
    }

    // ½ûÖ¹¿½±´
    Device(const Device &) = delete;
    Device &operator=(const Device &) = delete;

    NativeDevice GetDevice() const
    {
        return m_device;
    }
    VkQueue GetGraphicsQueue() const
    {
        return m_graphicsQueue;
    }
    uint32_t GetGraphicsQueueFamilyIndex() const
    {
        return m_graphicsQueueFamilyIndex;
    }

    void Submit(VkCommandBuffer cmdBuffer, VkFence fence = VK_NULL_HANDLE)
    {
        VkSubmitInfo submit = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .commandBufferCount = 1, .pCommandBuffers = &cmdBuffer};
        vkQueueSubmit(m_graphicsQueue, 1, &submit, fence);
    }

  private:
    VkInstance m_instance = VK_NULL_HANDLE;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device = VK_NULL_HANDLE;
    VkQueue m_graphicsQueue = VK_NULL_HANDLE;
    uint32_t m_graphicsQueueFamilyIndex = 0;
    std::vector<VkQueueFamilyProperties> m_queueFamilies;
};

} // namespace RHI