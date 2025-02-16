#pragma once
#include "From-GDGRAP2/GameObject.h"
#include "Utilities/Glm.hpp"

namespace Assets
{

	struct alignas(16) LightProperties final
	{
		enum class Enum : uint32_t
		{
			PointLight = 0,
			DirectionalLight = 1,
			SpotLight = 2
		};

		glm::vec3 LightPos;
		glm::vec4 AmbientColor;
		glm::vec4 LightColor;
		Enum LightType;
	};
}

class Light : public GameObject
{
protected:
	Assets::LightProperties props_;

public:
	enum LightType { PointLight = 0, DirectionalLight = 1, SpotLight = 2 };

	Light(String name, LightType type) : GameObject(name, LIGHT)
	{
		// Default Properties
		props_.LightPos = glm::vec3(2600, 20.0, 0);
		props_.AmbientColor = glm::vec4(1.0, 1.0, 1.0, 0.02);
		props_.LightColor = glm::vec4(1.0, 0.4, 0.5, 1000000.0f);
		props_.LightType = convertLightTypeEnum(type);

		GameObject::setLocalPosition(props_.LightPos);
	}

	const Assets::LightProperties Properties() const { return this->props_; }

	// setposition sets lightpos also
	void setLocalPosition(float x, float y, float z) override
	{
		props_.LightPos = glm::vec3(x, y, z);
		GameObject::setLocalPosition(x, y, z);
	}
	void setLocalPosition(vec3 newPos) override
	{
		props_.LightPos = newPos;
		GameObject::setLocalPosition(newPos);
	}

private:
	Assets::LightProperties::Enum convertLightTypeEnum(LightType type)
	{
		switch (type)
		{
		case PointLight:
			return Assets::LightProperties::Enum::PointLight;
			break;
		case DirectionalLight:
			return Assets::LightProperties::Enum::DirectionalLight;
			break;
		case SpotLight:
			return Assets::LightProperties::Enum::SpotLight;
			break;
		}
	}
};