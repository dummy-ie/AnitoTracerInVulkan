#include "GameObject.h"

#include <iostream>

#include "EventBroadcaster.h"

GameObject::GameObject()
{
	this->name = "No-name";
	this->type = NONE;
	this->modelRef = nullptr;
}

GameObject::GameObject(String name, PrimitiveType type)
{
	this->name = name;
	this->type = type;
	this->modelRef = nullptr;
}

GameObject::GameObject(String name, PrimitiveType type, std::shared_ptr<Assets::Model> modelRef)
{
	this->name = name;
	this->type = type;
	this->modelRef = modelRef;
}

GameObject::String GameObject::getName() const
{
	return this->name;
}

GameObject::PrimitiveType GameObject::getType() const
{
	return this->type;
}

bool GameObject::isEnabled()
{
	return this->enabled;
}

void GameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

GameObject::vec3 GameObject::getTransform() const
{
	return this->transform;
}

GameObject::vec3 GameObject::getScale() const
{
	return this->scale;
}

GameObject::vec3 GameObject::getRotAngles() const
{
	return this->rotAngles;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->transform = vec3(x, y, z);
	this->performModelTransform();
}

void GameObject::setPosition(vec3 newPos)
{
	this->transform = newPos;
	this->performModelTransform();
}

void GameObject::setRotAngles(float x, float y, float z)
{
	this->rotAngles = vec3(x, y, z);
	this->performModelRotate();
}

void GameObject::setRotAngles(vec3 newRot)
{
	this->rotAngles = newRot;
	this->performModelRotate();
}

void GameObject::setScale(float x, float y, float z)
{
	this->scale = vec3(x, y, z);
	this->performModelScale();
}

void GameObject::setScale(vec3 newScale)
{
	this->scale = newScale;
	this->performModelScale();
}

std::shared_ptr<Assets::Model> GameObject::getModel()
{
	return this->modelRef;
}

void GameObject::addChild(GameObject* child)
{
	if (!child || child == this || child->parent == this) 
		return;

	if (child->parent) 
	{
		child->parent->removeChild(child);
	}

	child->parent = this;
	children.push_back(child);
}

void GameObject::removeChild(GameObject* child)
{
	if (!child) return;

	auto it = std::find(children.begin(), children.end(), child);
	if (it != children.end())
	{
		children.erase(it);
		child->parent = nullptr;
	}
}

std::vector<GameObject*> GameObject::getChildren() const
{
	return this->children;
}

GameObject* GameObject::getParent() const
{
	return this->parent;
}

void GameObject::setParent(GameObject* newParent)
{
	if (newParent == this || (newParent && isDescendantOf(newParent))) 
		return;

	if (parent)
		parent->removeChild(this);

	parent = newParent;

	if (parent)
		parent->addChild(this);
}

bool GameObject::isDescendantOf(const GameObject* potentialParent) const
{
	const GameObject* current = this;
	while (current)
	{
		if (current == potentialParent)
		{
			return true;
		}
		current = current->parent;
	}
	return false;
}

/**
 * \brief Performs the model transform via model-view-projection matrix form
 */
void GameObject::performModelTransform()
{
	// lucy0.Transform(
	// 	rotate(
	// 		scale(
	// 			translate(i, vec3(0, -0.08f, 0)),
	// 			vec3(scaleFactor)),
	// 		radians(90.0f), vec3(0, 1, 0)));

	mat4 translateOp = glm::translate(mat4(1), this->transform - this->origin);
	this->origin = this->transform;
	if (modelRef)
		this->modelRef->Transform(translateOp);
	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}

void GameObject::performModelRotate()
{
	//vertex.Position = transform * vec4(vertex.Position, 1);

	vec3 rotOffset = this->rotAngles - this->originRot;
	mat4 rotateXOp = glm::rotate(mat4(1), glm::radians(rotOffset.x), vec3(1, 0, 0));
	mat4 rotateYOp = glm::rotate(mat4(1), glm::radians(rotOffset.y), vec3(0, 1, 0));
	mat4 rotateZOp = glm::rotate(mat4(1), glm::radians(rotOffset.z), vec3(0, 0, 1));

	if (modelRef)
	{
		this->modelRef->Transform(rotateXOp);
		this->modelRef->Transform(rotateYOp);
		this->modelRef->Transform(rotateZOp);
	}

	this->originRot = this->rotAngles;
	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}

void GameObject::performModelScale()
{
	mat4 scaleOp = glm::scale(mat4(1), this->scale);
	this->scale = VectorUtils::ones(); //TODO: Workaround. Reset to identity

	if (modelRef)
		this->modelRef->Transform(scaleOp);
	EventBroadcaster::getInstance()->broadcastEvent(EventNames::ON_MARK_SCENE_DIRTY);
}
