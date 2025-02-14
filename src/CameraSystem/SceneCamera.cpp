#include "SceneCamera.h"

SceneCamera::SceneCamera(std::string name) : Camera(name)
{
}

SceneCamera::~SceneCamera()
{
}

void SceneCamera::MoveForward(const float d)
{
	position_ += d * forward_;
}

void SceneCamera::MoveRight(const float d)
{
	position_ += d * right_;
}

void SceneCamera::MoveUp(const float d)
{
	position_ += d * up_;
}

void SceneCamera::Rotate(const float y, const float x)
{
	orientation_ =
		glm::rotate(glm::mat4(1), x, glm::vec3(1, 0, 0)) *
		orientation_ *
		glm::rotate(glm::mat4(1), y, glm::vec3(0, 1, 0));

	UpdateVectors();
}
