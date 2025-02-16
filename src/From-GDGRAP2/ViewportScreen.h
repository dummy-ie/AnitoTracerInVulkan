#pragma once

#include <memory>
#include <imgui.h>

#include "From-GDGRAP2/AUIScreen.h"
#include "Vulkan/DescriptorSetLayout.hpp"

#include "Vulkan/RenderPass.hpp"
#include "Vulkan/FrameBuffer.hpp"

namespace Vulkan {
	class Image;
	class DeviceMemory;
	class ImageView;
	class FrameBuffer;
	class RenderPass;
	class SwapChain;
	class DepthBuffer;
	class GraphicsPipeline;
}

class ViewportScreen final :
    public AUIScreen
{
	enum EFillMode
	{
		SOLID,
		WIREFRAME,
		SOLID_WIREFRAME
	};

private:
	int index;
	int camIndex;

	// SceneCameraPtr currentCamera;
	// SceneCameraPtr ownCamera;

	EFillMode currentFillMode = SOLID;

	//RenderTexturePtr renderTexture;

	bool isRightMouseDown = false;

	int selectedProj = 0;
	int selectedState = 0;
	int selectedCameraIndex = 0;
	//std::vector<VkDescriptorSet> m_Dset;

	std::vector<std::unique_ptr<Vulkan::Image>> images_;
	std::vector<std::unique_ptr<Vulkan::DeviceMemory>> imagesMemory_;
	std::vector<std::unique_ptr<Vulkan::ImageView>> imageViews_;
	std::vector<std::unique_ptr<Vulkan::FrameBuffer>> framebuffers_;

	//std::unique_ptr<class Vulkan::GraphicsPipeline> graphicsPipeline_;

	const Vulkan::SwapChain& swapChain_;
	const Vulkan::RenderPass& renderPass_;

	friend class UIManager;

public:
	ViewportScreen(const Vulkan::SwapChain& swapChain, const Vulkan::DepthBuffer& depthBuffer, const Vulkan::RenderPass& renderPass);
	virtual ~ViewportScreen() = default;

	const Vulkan::SwapChain& SwapChain() const { return swapChain_; }
	const Vulkan::FrameBuffer& ViewportFrameBuffer(const size_t i) const { return *framebuffers_[i]; }
	const Vulkan::RenderPass& RenderPass() const { return renderPass_; }

protected:
	void drawUI() override;
	void drawViewportUI(ImVec2 position);

};

