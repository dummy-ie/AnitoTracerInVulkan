#version 460
#extension GL_EXT_nonuniform_qualifier : require
#extension GL_GOOGLE_include_directive : require
#extension GL_EXT_ray_tracing : require
#include "Material.glsl"

layout(binding = 4) readonly buffer VertexArray { float Vertices[]; };
layout(binding = 5) readonly buffer IndexArray { uint Indices[]; };
layout(binding = 6) readonly buffer MaterialArray { Material[] Materials; };
layout(binding = 7) readonly buffer LightsArray { LightProperties[] Lights; }; 
layout(binding = 8) readonly buffer OffsetArray { uvec2[] Offsets; };
layout(binding = 9) uniform sampler2D[] TextureSamplers;

#include "Scatter.glsl"
#include "Vertex.glsl"

hitAttributeEXT vec2 HitAttributes;
rayPayloadInEXT RayPayload Ray;

vec2 Mix(vec2 a, vec2 b, vec2 c, vec3 barycentrics)
{
	return a * barycentrics.x + b * barycentrics.y + c * barycentrics.z;
}

vec3 Mix(vec3 a, vec3 b, vec3 c, vec3 barycentrics) 
{
    return a * barycentrics.x + b * barycentrics.y + c * barycentrics.z;
}

vec3 calculatePointLight(LightProperties pl, vec3 worldPos, vec3 normal) 
{
	// Computing the coordinates of the hit position
	const vec3 worldNrm = normalize(transpose(inverse(mat3(gl_ObjectToWorldEXT))) * normal);

	// Compute the diffuse light.
	vec3 lightDir = pl.LightPos.xyz - worldPos;
	float attenuation = 1.0 / dot(lightDir, lightDir);

	// Compute the light colors and intensity.
	vec3 lightCol = pl.LightColor.xyz * pl.LightColor.w * attenuation;
	vec3 ambientLight = pl.AmbientColor.xyz * pl.AmbientColor.w;
	vec3 diffuseLight = lightCol * max(dot(worldNrm, normalize(lightDir)), 0);
	
	vec3 lighting = diffuseLight + ambientLight;

	return lighting;
}

vec3 calculateDirectionalLight(LightProperties dl, vec3 worldPos, vec3 normal) 
{
	// Computing the coordinates of the hit position
	const vec3 worldNrm = normalize(transpose(inverse(mat3(gl_ObjectToWorldEXT))) * normal);

	// Compute the diffuse light.
	vec3 lightDir = dl.LightPos.xyz - worldPos;
	vec3 lighting = dl.LightColor.rgb * max(dot(worldNrm, normalize(lightDir)), 0);

	return lighting;
}

void NVidiaTutLightingComp(LightProperties pl, vec3 normal) // Unused 
{
	//const vec3 worldNrm = normalize(vec3(normal * gl_WorldToObjectEXT));  // Transforming the normal to world space

	// Vector toward the light
	//vec3  L;
	//float lightIntensity = pl.lightColor.w;
	//float lightDistance  = 100000.0;
	// Point light
	//if(lightType == 0)
	//{
		//vec3 lDir      = pl.lightPos - worldPos;
		//lightDistance  = length(lDir);
		//lightIntensity = lightIntensity / (lightDistance * lightDistance);
		//L              = pl.lightColor.rgb * max(dot(worldNrm, normalize(lDir)), 0);
	//}
	//else  // Directional light
	//{
		//vec3 lDir      = pl.lightPos - worldPos; 
		//L = pl.lightColor.rgb * max(dot(worldNrm, normalize(lDir)), 0);
	//}
}

void main()
{
	// Get the material.
	const uvec2 offsets = Offsets[gl_InstanceCustomIndexEXT];
	const uint indexOffset = offsets.x;
	const uint vertexOffset = offsets.y;
	const Vertex v0 = UnpackVertex(vertexOffset + Indices[indexOffset + gl_PrimitiveID * 3 + 0]);
	const Vertex v1 = UnpackVertex(vertexOffset + Indices[indexOffset + gl_PrimitiveID * 3 + 1]);
	const Vertex v2 = UnpackVertex(vertexOffset + Indices[indexOffset + gl_PrimitiveID * 3 + 2]);
	const Material material = Materials[v0.MaterialIndex];
	 
	// Compute the ray hit point properties.
	const vec3 barycentrics = vec3(1.0 - HitAttributes.x - HitAttributes.y, HitAttributes.x, HitAttributes.y);
	const vec3 normal = normalize(Mix(v0.Normal, v1.Normal, v2.Normal, barycentrics));
	const vec2 texCoord = Mix(v0.TexCoord, v1.TexCoord, v2.TexCoord, barycentrics);

	// For lighting computations.
	const vec3 pos = Mix(v0.Position, v1.Position, v2.Position, barycentrics);
	const vec3 worldPos = vec3(gl_ObjectToWorldEXT * vec4(pos, 1.0));  // Transforming the position to world space
	
	vec3 lighting = vec3(0);
	for (int i = 0; i < Lights.length(); i++) {
		if (Lights[i].LightType == PointLight) { // Point Light
			lighting += calculatePointLight(Lights[i], worldPos, normal);
		} else if (Lights[i].LightType == DirectionalLight) { // Directional Light
			lighting += calculateDirectionalLight(Lights[i], worldPos, normal);
		} else if (Lights[i].LightType == SpotLight) { // Spot Light
			//lighting += calculateDirectionalLight(Lights[i], worldPos, normal);
		}
	}
	if (Lights.length() == 0) { // Pink light if buffer is empty
		LightProperties pl = InitializeTestPLProperties(); // Adding point light.
		lighting += calculatePointLight(pl, worldPos, normal);
	}
	//LightProperties dl = InitializeTestDLProperties(); // Adding directional light.
	//lighting += calculateDirectionalLight(dl, worldPos, normal);

	Ray = Scatter(material, gl_WorldRayDirectionEXT, normal, texCoord, gl_HitTEXT, Ray.RandomSeed, lighting);
}
	