#pragma once

#include <string>

#include "From-GDGRAP2/GameObject.h"
#include "Utilities/Glm.hpp"

class Camera : public GameObject
{
public:
	Camera(std::string name);
	~Camera();

	void Reset(const glm::mat4& modelView);

	glm::mat4 ModelView() const;

	bool OnKey(int key, int scancode, int action, int mods);
	bool OnCursorPosition(double xpos, double ypos);
	bool OnMouseButton(int button, int action, int mods);
	bool UpdateCamera(double speed, double timeDelta);

protected:

	virtual void MoveForward(float d);
	virtual void MoveRight(float d);
	virtual void MoveUp(float d);
	virtual void Rotate(float y, float x);
	void UpdateVectors();

	std::string name;

	// Matrices and vectors.
	glm::mat4 orientation_{};

	glm::vec4 position_{};
	glm::vec4 right_{ 1, 0, 0, 0 };
	glm::vec4 up_{ 0, 1, 0, 0 };
	glm::vec4 forward_{ 0, 0, -1, 0 };

	// Control states.
	bool cameraMovingLeft_{};
	bool cameraMovingRight_{};
	bool cameraMovingBackward_{};
	bool cameraMovingForward_{};
	bool cameraMovingDown_{};
	bool cameraMovingUp_{};

	float cameraRotX_{};
	float cameraRotY_{};
	float modelRotX_{};
	float modelRotY_{};

	double mousePosX_{};
	double mousePosY_{};

	bool mouseLeftPressed_{};
	bool mouseRightPressed_{};
};
