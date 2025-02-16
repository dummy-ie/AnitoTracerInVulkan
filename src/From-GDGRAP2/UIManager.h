#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "imgui.h"
#include "AUIScreen.h"
#include "ViewportScreen.h"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

typedef std::string String;

class UINames {
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String PLAYBACK_SCREEN = "PLAYBACK_SCREEN";
	const String ACTION_SCREEN = "ACTION_SCREEN";
	const String CONSOLE_SCREEN = "CONSOLE_SCREEN";
	const String MATERIAL_SCREEN = "MATERIAL_SCREEN";
	const String MATERIAL_EDITOR_SCREEN = "MATERIAL_EDITOR_SCREEN";
};

class Viewport;
class UIManager
{
public: 
	typedef std::string String;
	typedef std::vector<std::shared_ptr<AUIScreen>> UIList;
	typedef std::unordered_map<String, std::shared_ptr<AUIScreen>> UITable;
	typedef std::vector<std::shared_ptr<ViewportScreen>> ViewportList;

	static UIManager* getInstance();
	static void initialize();
	static void destroy();

	void drawAllUI();

	std::vector<std::shared_ptr<ViewportScreen>> getViewportList();
	bool* getEnabled(const std::string& name);
	void setEnabled(String uiName, bool flag);
	std::shared_ptr<AUIScreen> findUIByName(String uiName);

	void createViewport(const Vulkan::SwapChain& swapChain, const Vulkan::DepthBuffer& depthBuffer, const Vulkan::RenderPass& renderPass);
	//std::vector<VkImage>* images = nullptr;
	//const Vulkan::Device& device_;
	//Vulkan::ImageView* imageView = nullptr;
	//VkDescriptorSet m_Dset;
	//Vulkan::Image* image = nullptr;
	std::unique_ptr<Vulkan::Sampler> sampler_;
private:
	UIManager();
	~UIManager();
	UIManager(UIManager const&) {};             // copy constructor is private
	UIManager& operator=(UIManager const&) {};  // assignment operator is private*/
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
	ViewportList viewportList;
};

