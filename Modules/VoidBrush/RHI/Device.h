// RHI/Device.h
#pragma once
#include "Backend.h"

// 前向声明模板
namespace RHI
{
template <typename BackendTag> class Device;
}

// 包含各后端实现（按需包含，也可由用户手动包含）
#ifdef RHI_IMPLEMENTATION_DX11
#include "impl/DeviceDX11.h"
#endif

#ifdef RHI_IMPLEMENTATION_DX12
#include "impl/DeviceDX12.h"
#endif

#ifdef RHI_IMPLEMENTATION_VULKAN
#include "impl/DeviceVulkan.h"
#endif

// 类型别名（方便使用）
namespace RHI
{
using DX11Device = Device<DX11Backend>;
using DX12Device = Device<DX12Backend>;
using VulkanDevice = Device<VulkanBackend>;
} // namespace RHI