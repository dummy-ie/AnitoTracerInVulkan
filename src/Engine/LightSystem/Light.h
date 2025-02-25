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

		glm::vec3 LightPos;   // 12 bytes
		float padding1;       // 4 bytes padding (to align to 16 bytes)

		glm::vec4 AmbientColor;  // 16 bytes
		glm::vec4 LightColor;    // 16 bytes

		Enum LightType;        // 4 bytes
		uint32_t padding2[3];  // 12 bytes padding (to align struct to 16 bytes)
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
		props_.LightPos = glm::vec3(1600, 20.0, 0);
		props_.AmbientColor = glm::vec4(1.0, 1.0, 1.0, 0.02);
		props_.LightColor = glm::vec4(0.0, 1.0, 0.0, 1000000.0f); // Purple
		props_.LightType = convertLightTypeEnum(type);

		GameObject::setLocalPosition(props_.LightPos);
	}

	Light(String name, LightType type, glm::vec3 pos, glm::vec4 ambientCol, glm::vec4 lightCol)
		: GameObject(name, LIGHT)
	{
		// Default Properties
		props_.LightPos = pos;
		props_.AmbientColor = ambientCol;
		props_.LightColor = lightCol;
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