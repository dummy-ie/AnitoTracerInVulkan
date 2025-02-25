#version 460
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_nonuniform_qualifier : require
#extension GL_GOOGLE_include_directive : require
#include "Material.glsl"

layout(binding = 1) readonly buffer MaterialArray { Material[] Materials; };
layout(binding = 2) uniform sampler2D[] TextureSamplers;

layout(location = 0) in vec3 FragColor;
layout(location = 1) in vec3 FragNormal;
layout(location = 2) in vec2 FragTexCoord;
layout(location = 3) in flat int FragMaterialIndex;

layout(location = 0) out vec4 OutColor;

const vec4 dirLightColor = vec4(1.0);
const vec3 dirLightDir = normalize(vec3(5.0, 4.0, 3.0));

void main() 
{
	const int textureId = Materials[FragMaterialIndex].DiffuseTextureId;
	const int normalTextureId = Materials[FragMaterialIndex].NormalTextureId;
	const float normalStrength = Materials[FragMaterialIndex].Normal;
	//const float d = max(dot(dirLightDir, normalize(FragNormal)), 0.2);

	float d;
	if (normalTextureId >= 0)
	{
		vec3 normal = texture(TextureSamplers[normalTextureId], FragTexCoord).rgb;
		normal = normalize(normal * 2.0 - 1.0);
		normal = normalize(FragNormal * normal);
		d = max(dot(dirLightDir, normal), 0.2);
	}
	else {
		d = max(dot(dirLightDir, normalize(FragNormal)), 0.2);
	}

	vec3 c = FragColor * d;
	if (textureId >= 0)
	{
		c *= texture(TextureSamplers[textureId], FragTexCoord).rgb;
	}
	
    OutColor = dirLightColor * vec4(c, 1);
}