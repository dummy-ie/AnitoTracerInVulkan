#include "InspectorScreen.h"

#include <glm/gtx/string_cast.hpp>

#include "imgui.h"
#include "From-GDGRAP2/ModelManager.h"
#include "UIManager.h"
#include "From-GDGRAP2/GameObject.h"

InspectorScreen::InspectorScreen() : AUIScreen("InspectorScreen")
{
}

InspectorScreen::~InspectorScreen()
{

}

void InspectorScreen::drawUI()
{

	ImGui::Begin("Inspector Window", 0, ImGuiWindowFlags_NoResize);
	this->selectedObject = ModelManager::getInstance()->getSelectedObject();
	if (this->selectedObject != nullptr)
	{
		String name = this->selectedObject->getName();
		ImGui::Text("Selected Object: %s", name.c_str());
		this->updateTransformDisplays();
		bool enabled = this->selectedObject->isEnabled();
		if (ImGui::Checkbox("Enabled", &enabled)) { this->selectedObject->setEnabled(enabled); }
		ImGui::SameLine();
		if (ImGui::Button("Delete")) {
			ModelManager::getInstance()->deleteObject(this->selectedObject);
			ModelManager::getInstance()->setSelectedObject(static_cast<std::shared_ptr<GameObject>>(nullptr));
		}
		if (ImGui::InputFloat3("Position", this->positionDisplay, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) { this->onTransformUpdate(); }
		if (ImGui::InputFloat3("Rotation", this->rotationDisplay, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) { this->onTransformUpdate(); }

		if (this->selectedObject->getType() == GameObject::PrimitiveType::SPHERE)
		{
			if (ImGui::InputFloat("Resize", this->scaleDisplay, 0, 0, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) { this->onTransformUpdate(); }
		}
		else {
			if (ImGui::InputFloat3("Scale", this->scaleDisplay, "%.3f", ImGuiInputTextFlags_EnterReturnsTrue)) { this->onTransformUpdate(); }
		}

		this->drawMaterialsTab();
	}
	else {
		ImGui::Text("No object selected. Select an object first.");
	}

	ImGui::End();
}

void InspectorScreen::updateTransformDisplays()
{
	typedef glm::vec3 vec3;
	vec3 pos = this->selectedObject->getLocalPosition();
	this->positionDisplay[0] = pos.x;
	this->positionDisplay[1] = pos.y;
	this->positionDisplay[2] = pos.z;

	vec3 rot = this->selectedObject->getLocalRotation();
	this->rotationDisplay[0] = rot.x;
	this->rotationDisplay[1] = rot.y;
	this->rotationDisplay[2] = rot.z;

	vec3 scale = this->selectedObject->getLocalScale();
	this->scaleDisplay[0] = scale.x;
	this->scaleDisplay[1] = scale.y;
	this->scaleDisplay[2] = scale.z;
}

void InspectorScreen::SendResult(String materialPath)
{
	// TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObject);
	// texturedObj->getRenderer()->setMaterialPath(materialPath);
	// this->popupOpen = false;
}

void InspectorScreen::FormatMatImage()
{
	//convert to wchar format
	// String textureString = this->materialPath;
	// std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	// const wchar_t* texturePath = widestr.c_str();
	//
	// this->materialDisplay = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}

void InspectorScreen::drawMaterialsTab()
{
	int BUTTON_WIDTH = 225;
	int BUTTON_HEIGHT = 20;

	// if(this->selectedObject->getType() != AHittable::TEXTURED_CUBE)
	// {
	// 	return;
	// }

	// TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObject);
	// this->materialPath = texturedObj->getRenderer()->getMaterialPath();
	// this->FormatMatImage();
	// ImGui::SetCursorPosX(50);
	// ImGui::Image(static_cast<void*>(this->materialDisplay->getShaderResource()), ImVec2(150, 150));
	//
	// std::vector<String> paths = StringUtils::split(this->materialPath, '\\');
	// this->materialName = paths[paths.size() - 1];
	// String displayText = "Material: " + this->materialName;
	// ImGui::Text(displayText.c_str());
	// if (ImGui::Button("Add Material", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
	// 	this->popupOpen = !this->popupOpen;
	// 	UINames uiNames;
	// 	MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
	// 	materialScreen->linkInspectorScreen(this, this->materialPath);
	// 	UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, this->popupOpen);
	// }
}

void InspectorScreen::onTransformUpdate() const
{
	if (this->selectedObject != nullptr)
	{
		// ActionHistory::getInstance()->recordAction(this->selectedObject);

		this->selectedObject->setLocalPosition(this->positionDisplay[0], this->positionDisplay[1], this->positionDisplay[2]);
		this->selectedObject->setLocalRotation(this->rotationDisplay[0], this->rotationDisplay[1], this->rotationDisplay[2]);

		if (this->selectedObject->getType() == GameObject::PrimitiveType::SPHERE)
		{
			this->selectedObject->setLocalScale(this->scaleDisplay[0], this->scaleDisplay[0], this->scaleDisplay[0]);
		}
		else
		{
			this->selectedObject->setLocalScale(this->scaleDisplay[0], this->scaleDisplay[1], this->scaleDisplay[2]);
		}

	}
}
