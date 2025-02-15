#pragma once
#include <unordered_set>

#include "AUIScreen.h"
#include "GameObject.h"

class HierarchyScreen :    public AUIScreen
{
public:
	HierarchyScreen();
	~HierarchyScreen();
private:
	virtual void drawUI() override;
	void updateObjectList() const;
	void drawObjectNode(GameObject* obj) const;

	mutable std::unordered_set<std::string> openNodes;  

	friend class UIManager;
};

