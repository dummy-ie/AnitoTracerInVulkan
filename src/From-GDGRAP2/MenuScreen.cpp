#include "MenuScreen.h"
#include "imgui.h"
#include <iostream>

#include "EventBroadcaster.h"
#include "ModelManager.h"

// #include "GameObjectManager.h"

MenuScreen::MenuScreen(): AUIScreen("MenuScreen")
{
	// this->openSceneDialog = new ImGui::FileBrowser();
	// this->openSceneDialog->SetTitle("Open Scene");
	// this->openSceneDialog->SetTypeFilters({ ".iet"});
	//
	// this->saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	// this->saveSceneDialog->SetTitle("Save Scene");
	// this->saveSceneDialog->SetTypeFilters({ ".iet" });
}

MenuScreen::~MenuScreen()
{
	// delete this->openSceneDialog;
	// delete this->saveSceneDialog;
}

void MenuScreen::drawUI()
{

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) {
				//this->openSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				//this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
				//this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W"))
			{
				// Walnut::Application::Get().Close();
				exit(0); // temp exit lol 
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("Load Sphere World")) { this->OnLoadSphereWorld(); }
			if (ImGui::MenuItem("Load Box World")) { this->OnLoadBoxWorld(); }
			if (ImGui::MenuItem("Load Cornell Box")) {this->OnLoadCornellBox();}
			if (ImGui::MenuItem("Load AnitoTracer Demo")) {this->OnLoadAnitoTracerDemo();}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Sphere")) { this->OnCreateSphereClicked(); }
			if (ImGui::MenuItem("Create Cube")) { this->OnCreateCubeClicked(); }
			if (ImGui::MenuItem("Create Textured Cube")) { this->OnCreateTexturedCubeClicked(); }
			if (ImGui::MenuItem("Create Plane")) { this->OnCreatePlaneClicked(); }
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) { /* Do stuff */ }
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Components")) {
			if (ImGui::MenuItem("Material")) { this->OnMaterialComponentClicked(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// this->openSceneDialog->Display();
	// this->saveSceneDialog->Display();
	//
	// if (this->saveSceneDialog->HasSelected())
	// {
	// 	SceneWriter writer = SceneWriter(this->saveSceneDialog->GetSelected().string());
	// 	writer.writeToFile();
	//
	// 	this->saveSceneDialog->ClearSelected();
	// 	this->saveSceneDialog->Close();
	// }
	//
	// else if (this->openSceneDialog->HasSelected()) {
	// 	SceneReader reader = SceneReader(this->openSceneDialog->GetSelected().string());
	// 	reader.readFromFile();
	//
	// 	this->openSceneDialog->ClearSelected();
	// 	this->openSceneDialog->Close();
	// }
}

void MenuScreen::OnCreateCubeClicked()
{
	//initialize vertex for object
	// GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::CUBE);
}

void MenuScreen::OnCreateTexturedCubeClicked()
{
	// GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::TEXTURED_CUBE);
}

void MenuScreen::OnCreateSphereClicked()
{
	std::cout << "Creating sphere placeholder. \n";
}

void MenuScreen::OnCreatePlaneClicked()
{
	//initialize vertex for object
	// GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::QUAD);
}

void MenuScreen::OnMaterialComponentClicked()
{
	// Debug::Log("Creating material placeholder.");
}

void MenuScreen::OnLoadSphereWorld()
{
	// GameObjectManager::getInstance()->clearAll();
	// RayTracingProper::getInstance()->generateSphereWorld();
	// RayTracingProper::getInstance()->renderSceneFromHierarchy();

	ModelManager::getInstance()->clearAllObjects();
	std::shared_ptr<Parameters> parameters = std::make_shared<Parameters>(EventNames::ON_SCENE_LOADED);
	parameters->encodeInt("SCENE_INDEX", 6);
	EventBroadcaster::getInstance()->broadcastEventWithParams(EventNames::ON_SCENE_LOADED, parameters);
}

void MenuScreen::OnLoadBoxWorld()
{
	ModelManager::getInstance()->clearAllObjects();
	std::shared_ptr<Parameters> parameters = std::make_shared<Parameters>(EventNames::ON_SCENE_LOADED);
	parameters->encodeInt("SCENE_INDEX", 8);
	EventBroadcaster::getInstance()->broadcastEventWithParams(EventNames::ON_SCENE_LOADED, parameters);
}

void MenuScreen::OnLoadCornellBox()
{
	// GameObjectManager::getInstance()->clearAll();
	// RayTracingProper::getInstance()->generateCornellBox();
	//
	// RayTracingProper::getInstance()->renderSceneFromHierarchy();

	ModelManager::getInstance()->clearAllObjects();
	std::shared_ptr<Parameters> parameters = std::make_shared<Parameters>(EventNames::ON_SCENE_LOADED);
	parameters->encodeInt("SCENE_INDEX", 7);
	EventBroadcaster::getInstance()->broadcastEventWithParams(EventNames::ON_SCENE_LOADED, parameters);
}

void MenuScreen::OnLoadAnitoTracerDemo()
{
	ModelManager::getInstance()->clearAllObjects();
	std::shared_ptr<Parameters> parameters = std::make_shared<Parameters>(EventNames::ON_SCENE_LOADED);
	parameters->encodeInt("SCENE_INDEX", 9);
	EventBroadcaster::getInstance()->broadcastEventWithParams(EventNames::ON_SCENE_LOADED, parameters);
}
