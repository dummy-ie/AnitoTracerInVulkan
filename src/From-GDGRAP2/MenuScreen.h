#pragma once
#include "AUIScreen.h"

class MenuScreen :    public AUIScreen
{
public:
	MenuScreen();
	~MenuScreen();

private:
	virtual void drawUI() override;
	void OnCreateCubeClicked();
	void OnCreateTexturedCubeClicked();
	void OnCreateSphereClicked();
	void OnCreatePlaneClicked();
	void OnMaterialComponentClicked();

	void OnLoadSphereWorld();
	void OnLoadBoxWorld();
	void OnLoadCornellBox();
	void OnLoadAnitoTracerDemo();

	friend class UIManager;

	bool isOpen = false;

	bool openSceneSelected = false;

	// ImGui::FileBrowser* saveSceneDialog;
	// ImGui::FileBrowser* openSceneDialog;
};

