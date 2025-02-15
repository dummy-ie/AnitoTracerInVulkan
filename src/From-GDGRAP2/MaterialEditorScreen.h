#pragma once

#include <imgui.h>
#include <wrl/client.h>
#include <string>
#include <shobjidl.h> 
#include <vector>

#include "AUIScreen.h"
#include "Assets/Material.hpp"

namespace gdeng03
{
	class MenuScreen;

	using Assets::Material;

	class MaterialEditorScreen :
		public AUIScreen
	{
	public:
		MaterialEditorScreen();
		//bool* getMaterialEditorOpen();

		bool canSelectMaterial() const;
		void updateMaterial(Material* mat);
		void setSelectedMaterial(Material* mat);
		void unselectMaterial();

	private:
		void drawUI() override;
		void showColorPickerWindow();
		void updateSelectedMaterial();
		void showMaterialEditorWindow();

		// static std::vector<unsigned char> getPixelData(const TexturePtr& texture);
		// static bool isNormalImage(const TexturePtr& texture);
		//
		// void loadTextureFile(TexturePtr& texture);
		// void loadDefaultTextures();

	private:
		Material* selectedMaterial = nullptr;

		bool isColorPickerOpen = false;
		//bool isMaterialEditorOpen = false;

		ImVec4 color = ImVec4(1, 1, 1, 1);
		float metallic = 0;
		float smoothness = 0;
		float flatness = 0;
		ImVec2 tiling = { 1,1 };
		ImVec2 offset = { 0,0 };

		// TexturePtr albedoTexture;
		// TexturePtr metallicTexture;
		// TexturePtr smoothnessTexture;
		// TexturePtr normalTexture;

		//friend class MenuScreen;
		//friend class InspectorScreen;
	};
}

