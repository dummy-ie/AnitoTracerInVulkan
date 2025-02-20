#pragma once
#include "AUIScreen.h"
#include "GameObject.h"

class Texture;
class InspectorScreen :    public AUIScreen
{

public:
	InspectorScreen();
	~InspectorScreen();
	void SendResult(String materialPath);
	
private:

	void onTransformUpdate() const;
	virtual void drawUI() override;
	void updateTransformDisplays();
	void FormatMatImage();
	void drawMaterialsTab();
	friend class UIManager;

	float positionDisplay[3] = {0.0f, 0.0f, 0.0f};
	float rotationDisplay[3] = {0.0f, 0.0f, 0.0f};
	float scaleDisplay[3] = { 1.0f, 1.0f, 1.0f };
	bool popupOpen = false;

	std::shared_ptr<GameObject> selectedObject = nullptr;
	const String DEFAULT_MATERIAL = "None";
	String materialPath = DEFAULT_MATERIAL;
	String materialName = DEFAULT_MATERIAL;
	Texture* materialDisplay;
	
	
};

