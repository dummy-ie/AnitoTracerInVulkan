#include "Camera.h"

#include <iostream>
#include <glm/fwd.hpp>

#include "From-GDGRAP2/Debug.h"
#include "From-GDGRAP2/ModelManager.h"
#include "OBB/Ray.hpp"
#include "Vulkan/Vulkan.hpp"

Camera::Camera(std::string name, ProjectionMode proj) : GameObject(name, PrimitiveType::CAMERA)
{
	this->name = name;
	this->projMode = proj;
}

Camera::~Camera() {}

void Camera::Reset(const glm::mat4& modelView)
{
	const auto inverse = glm::inverse(modelView);

	position_ = inverse * glm::vec4(0, 0, 0, 1);
	orientation_ = glm::mat4(glm::mat3(modelView));

	cameraRotX_ = 0;
	cameraRotY_ = 0;
	modelRotX_ = 0;
	modelRotY_ = 0;

	mouseLeftPressed_ = false;
	mouseRightPressed_ = false;

	UpdateVectors();
}

glm::mat4 Camera::ModelView() const
{
	const auto cameraRotX = static_cast<float>(modelRotY_ / 300.0);
	const auto cameraRotY = static_cast<float>(modelRotX_ / 300.0);

	const auto model =
		glm::rotate(glm::mat4(1.0f), cameraRotY * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), cameraRotX * glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	const auto view = orientation_ * glm::translate(glm::mat4(1), -glm::vec3(position_));

	return view * model;
}

bool Camera::OnKey(const int key, const int scancode, const int action, const int mods)
{
	switch (key)
	{
	case GLFW_KEY_S: cameraMovingBackward_ = action != GLFW_RELEASE; return true;
	case GLFW_KEY_W: cameraMovingForward_ = action != GLFW_RELEASE; return true;
	case GLFW_KEY_A: cameraMovingLeft_ = action != GLFW_RELEASE; return true;
	case GLFW_KEY_D: cameraMovingRight_ = action != GLFW_RELEASE; return true;
	case GLFW_KEY_LEFT_CONTROL: cameraMovingDown_ = action != GLFW_RELEASE; return true;
	case GLFW_KEY_LEFT_SHIFT: cameraMovingUp_ = action != GLFW_RELEASE; return true;
	default: return false;
	}
}

bool Camera::OnCursorPosition(const double xpos, const double ypos)
{
	const auto deltaX = static_cast<float>(xpos - mousePosX_);
	const auto deltaY = static_cast<float>(ypos - mousePosY_);

	const auto limit = 360*2;
	if (mouseLeftPressed_)
	{
		cameraRotX_ += deltaX;
		this->localRotation.x += deltaX;
		if (localRotation.x > limit) {cameraRotX_ = 0; this->localRotation.x -= deltaX;}
		if (localRotation.x < -limit) {cameraRotX_ = 0; this->localRotation.x -= deltaX;}

		cameraRotY_ += deltaY;
		this->localRotation.y += deltaY;
		if (localRotation.y > limit) { cameraRotY_ = 0; this->localRotation.y -= deltaY; }
		if (localRotation.y < -limit) { cameraRotY_ = 0; this->localRotation.y -= deltaY; }

		Debug::Log("Camera rotation: " + std::to_string(localRotation.x) + ", " + std::to_string(localRotation.y) + "\n");
	}

	if (mouseRightPressed_)
	{
		modelRotX_ += deltaX;
		modelRotY_ += deltaY;
	}

	mousePosX_ = xpos;
	mousePosY_ = ypos;

	return mouseLeftPressed_ || mouseRightPressed_;
}

bool Camera::OnMouseButton(const int button, const int action, const int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		float ndcX = (2.0f * static_cast<float>(mousePosX_)) / windowWidth_ - 1.0f;
		float ndcY = 1.0f - (2.0f * static_cast<float>(mousePosY_)) / windowHeight_;
		glm::vec2 mouseNDC(ndcX, ndcY);

		glm::mat4 view = orientation_;
		glm::mat4 proj = projection_;
		glm::mat4 invVP = glm::inverse(proj * view);

		glm::vec4 rayStartNDC(mouseNDC, -1.0f, 1.0f);
		glm::vec4 rayEndNDC(mouseNDC, 1.0f, 1.0f);

		glm::vec4 rayStartWorld = invVP * rayStartNDC;
		glm::vec4 rayEndWorld = invVP * rayEndNDC;
		rayStartWorld /= rayStartWorld.w;
		rayEndWorld /= rayEndWorld.w;

		glm::vec3 rayOrigin = glm::vec3(rayStartWorld);
		glm::vec3 rayDirection = glm::normalize(glm::vec3(rayEndWorld - rayStartWorld));

		// Construct the picking ray.
		Ray pickingRay(rayOrigin, rayDirection);

		// Iterate over objects from ModelManager.
		auto objects = ModelManager::getInstance()->getAllObjects();
		for (auto& obj : objects)
		{
			if (!obj->isEnabled())
				continue;

			auto obb = obj->getOBB();
			if (obb)
			{
				
				float tHit = 0.0f;
				if (pickingRay.intersects(*obb, tHit))
				{
					glm::vec3 hitPoint = rayOrigin + rayDirection * tHit;
					std::cout << "Picked object: " << obj->getName() << "\n";
					std::cout << "Intersection at (" << hitPoint.x << ", "
						<< hitPoint.y << ", " << hitPoint.z << ")\n";

					ModelManager::getInstance()->setSelectedObject(obj);
					break;
				}
			}
		}	
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		mouseLeftPressed_ = action == GLFW_PRESS;
	}
		

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		mouseRightPressed_ = action == GLFW_PRESS;
	}

	return true;
}

bool Camera::UpdateCamera(const double speed, const double timeDelta)
{
	const auto d = static_cast<float>(speed * timeDelta);

	if (cameraMovingLeft_) MoveRight(-d);
	if (cameraMovingRight_) MoveRight(d);
	if (cameraMovingBackward_) MoveForward(-d);
	if (cameraMovingForward_) MoveForward(d);
	if (cameraMovingDown_) MoveUp(-d);
	if (cameraMovingUp_) MoveUp(d);

	const float rotationDiv = 300;
	Rotate(cameraRotX_ / rotationDiv, cameraRotY_ / rotationDiv);

	const bool updated =
		cameraMovingLeft_ ||
		cameraMovingRight_ ||
		cameraMovingBackward_ ||
		cameraMovingForward_ ||
		cameraMovingDown_ ||
		cameraMovingUp_ ||
		cameraRotY_ != 0 ||
		cameraRotX_ != 0;

	cameraRotY_ = 0;
	cameraRotX_ = 0;

	return updated;
}

glm::mat4 Camera::GetProjection(UserSettings settings, const VkExtent2D extent)
{
	switch (projMode)
	{
	case ProjectionMode::orthographic:
		projection_ = glm::ortho(-1000.0f, 1000.0f, 1000.0f, -1000.0f, 0.1f, 1000.0f);
		break;

	case ProjectionMode::perspective:
		projection_ = glm::perspective(glm::radians(settings.FieldOfView), extent.width / static_cast<float>(extent.height), 0.1f, 10000.0f);
		break;
	}

	windowWidth_ = extent.width;
	windowHeight_ = extent.height;

	return projection_;
}

void Camera::SetProjectionType(ProjectionMode type)
{
	this->projMode = type;
}

void Camera::MoveForward(const float d)
{
	position_ += d * forward_;
}

void Camera::MoveRight(const float d)
{
	position_ += d * right_;
}

void Camera::MoveUp(const float d)
{
	position_ += d * up_;
}

void Camera::Rotate(const float y, const float x)
{
	orientation_ =
		glm::rotate(glm::mat4(1), x, glm::vec3(1, 0, 0)) *
		orientation_ *
		glm::rotate(glm::mat4(1), y, glm::vec3(0, 1, 0));

	UpdateVectors();
}

void Camera::UpdateVectors()
{
	// Given the ortientation matrix, find out the x,y,z vector orientation.
	const auto inverse = glm::inverse(orientation_);

	right_ = inverse * glm::vec4(1, 0, 0, 0);
	up_ = inverse * glm::vec4(0, 1, 0, 0);
	forward_ = inverse * glm::vec4(0, 0, -1, 0);
}
