#include "HierarchyScreen.h"

#include <imgui_internal.h>

#include "imgui.h"
#include "From-GDGRAP2/ModelManager.h"
#include "UIManager.h"
#include "RTConfig.h"

HierarchyScreen::HierarchyScreen(): AUIScreen("HierarchyScreen")
{
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::drawUI()
{
	ImGui::Begin("Scene Outline");
	this->updateObjectList();
	ImGui::End();
}

void HierarchyScreen::updateObjectList() const
{
     const ModelManager::List objectList = ModelManager::getInstance()->getAllObjects();

    for (const auto& obj : objectList) 
    {
        if (!obj->getParent())  // Only draw root objects
        {
            drawObjectNode(obj.get());
        }
    }
}

void HierarchyScreen::drawObjectNode(GameObject* obj) const
{
    if (!obj) return;

    String objectName = obj->getName();
    bool hasChildren = !obj->getChildren().empty();

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    if (!hasChildren) flags |= ImGuiTreeNodeFlags_Leaf;

    // Keep parent node open if previously opened
    bool isNodeOpen = openNodes.count(objectName) > 0;
    if (isNodeOpen) flags |= ImGuiTreeNodeFlags_DefaultOpen;

    bool open = ImGui::TreeNodeEx(objectName.c_str(), flags);

    // Selection logic
    if (ImGui::IsItemClicked())
    {
        ModelManager::getInstance()->setSelectedObject(objectName);
    }

    // --- DRAG-AND-DROP IMPLEMENTATION ---

    // Drag Source 
    if (ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("DND_GAMEOBJECT", &obj, sizeof(GameObject*));
        ImGui::Text("Dragging %s", objectName.c_str());
        ImGui::EndDragDropSource();
    }

    // Drop Target 
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_GAMEOBJECT"))
        {
            GameObject* draggedObj = *(GameObject**)payload->Data;

            if (draggedObj != obj && draggedObj->getParent() != obj)
            {
                if (draggedObj->getParent())
                {
                    draggedObj->getParent()->removeChild(draggedObj);
                }
                obj->addChild(draggedObj);

                openNodes.insert(objectName);
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (open)
    {
        for (const auto& child : obj->getChildren())
        {
            drawObjectNode(child);
        }
        ImGui::TreePop();
    }
    else
    {
        openNodes.erase(objectName);
    }
}
