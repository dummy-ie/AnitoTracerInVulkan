#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Assets/Model.hpp"
#include "From-GDGRAP2/VectorUtils.h"

class GameObject
{
public:
    ~GameObject() = default;

    enum PrimitiveType {
        CAMERA, CUBE, OBJECT_GROUP, QUAD, PLANE, CYLINDER, CAPSULE, SPHERE, NONE
    };

    typedef glm::vec3 vec3;
    typedef std::string String;
    typedef glm::mat4 mat4;

    GameObject();
    GameObject(String name, PrimitiveType type);
    GameObject(String name, PrimitiveType type, std::shared_ptr<Assets::Model> modelRef);

    String getName() const;
    PrimitiveType getType() const;

    bool isEnabled();
    void setEnabled(bool flag);

    vec3 getLocalPosition() const;
    vec3 getWorldPosition() const;

    vec3 getLocalRotation() const;
    vec3 getWorldRotation() const;

    vec3 getLocalScale() const;
    vec3 getWorldScale() const;

    void setLocalPosition(vec3 newPos);
    void setLocalPosition(float x, float y, float z);
    void setLocalRotation(vec3 newRot);
    void setLocalRotation(float x, float y, float z);
    void setLocalScale(vec3 newScale);
    void setLocalScale(float x, float y, float z);

    std::shared_ptr<Assets::Model> getModel();

    void addChild(GameObject* child);
    void removeChild(GameObject* child);
    std::vector<GameObject*> getChildren() const;
    GameObject* getParent() const;

    void setParent(GameObject* newParent);
    bool isDescendantOf(const GameObject* potentialParent) const;

protected:
    String name;
    PrimitiveType type;
    bool enabled = true;

    vec3 origin = VectorUtils::zeros();
    vec3 originRot = VectorUtils::zeros();
    vec3 originScale = VectorUtils::ones();
    vec3 localPosition = VectorUtils::zeros();
    vec3 localRotation = VectorUtils::zeros();
    vec3 localScale = VectorUtils::ones();

    vec3 worldPosition = VectorUtils::zeros();
    vec3 worldRotation = VectorUtils::zeros();
    vec3 worldScale = VectorUtils::ones();

    std::shared_ptr<Assets::Model> modelRef;

    GameObject* parent = nullptr;
    std::vector<GameObject*> children;

    void updateWorldTransform();

    virtual void performModelTransform();
    virtual void performModelRotate();
    virtual void performModelScale();

    friend class ModelManager;
};


