#pragma once
#include <memory>
#include <string>

#include "Assets/Model.hpp"
#include "From-GDGRAP2/VectorUtils.h"

class GameObject
{
public:
	~GameObject() = default;

	// TODO ADD NEW PRIMITIVES
	enum PrimitiveType {
		CAMERA,
		CUBE,
		OBJECT_GROUP,
		QUAD,
		PLANE,
		CYLINDER,
		CAPSULE,
		SPHERE,
		NONE,
	};

	typedef glm::vec3 vec3;
	typedef std::string String;

	GameObject();
	GameObject(String name, PrimitiveType type);
	GameObject(String name, PrimitiveType type, std::shared_ptr<Assets::Model> modelRef);

	String getName();
	PrimitiveType getType();

	bool isEnabled();
	void setEnabled(bool flag);

	vec3 getTransform() const;
	vec3 getScale() const;
	vec3 getRotAngles() const;

	void setPosition(float x, float y, float z);
	void setPosition(vec3 newPos);

	void setRotAngles(float x, float y, float z);
	void setRotAngles(vec3 newRot);

	void setScale(float x, float y, float z);
	void setScale(vec3 newScale);

	std::shared_ptr<Assets::Model> getModel();

protected:
	String name;
	PrimitiveType type;
	bool enabled;

	typedef glm::mat4 mat4;
	vec3 origin = VectorUtils::zeros();
	vec3 originRot = VectorUtils::zeros();

	vec3 transform = VectorUtils::zeros();
	vec3 rotAngles = VectorUtils::zeros();
	vec3 scale = VectorUtils::ones();

	std::shared_ptr<Assets::Model> modelRef;

	virtual void performModelTransform();
	virtual void performModelRotate();
	virtual void performModelScale();

	friend class ModelManager;
 };

