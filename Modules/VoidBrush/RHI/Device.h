// RHI/Device.h
#pragma once
#include "Backend.h"

// ǰ������ģ��
namespace RHI
{
template <typename BackendTag> class Device;
}

// ���������ʵ�֣����������Ҳ�����û��ֶ�������
#ifdef RHI_IMPLEMENTATION_DX11
#include "impl/DeviceDX11.h"
#endif

#ifdef RHI_IMPLEMENTATION_DX12
#include "impl/DeviceDX12.h"
#endif

#ifdef RHI_IMPLEMENTATION_VULKAN
#include "impl/DeviceVulkan.h"
#endif

// ���ͱ���������ʹ�ã�
namespace RHI
{
using DX11Device = Device<DX11Backend>;
using DX12Device = Device<DX12Backend>;
using VulkanDevice = Device<VulkanBackend>;
} // namespace RHI