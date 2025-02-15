
struct Vertex
{
  vec3 Position;
  vec3 Normal;
  vec2 TexCoord;
  int MaterialIndex;
};

Vertex UnpackVertex(uint index)
{
	const uint vertexSize = 9;
	const uint offset = index * vertexSize;
	
	Vertex v;
	
	v.Position = vec3(Vertices[offset + 0], Vertices[offset + 1], Vertices[offset + 2]);
	v.Normal = vec3(Vertices[offset + 3], Vertices[offset + 4], Vertices[offset + 5]);
	v.TexCoord = vec2(Vertices[offset + 6], Vertices[offset + 7]);
	v.MaterialIndex = floatBitsToInt(Vertices[offset + 8]);

	return v;
}

struct LightProperties 
{
	vec3 lightPos;
	vec4 ambientColor;
	vec4 lightColor;
};

LightProperties InitializeTestPLProperties() 
{
	LightProperties pl;
	pl.lightPos = vec3(2600, 20.0, 0);
	pl.ambientColor = vec4(1.0, 1.0, 1.0, 0.02);
	pl.lightColor = vec4(1.0, 0.4, 0.5, 1000000.0f);

	return pl;
}

LightProperties InitializeTestDLProperties() 
{
	LightProperties dl;
	dl.lightPos = vec3(1600, 200.0, 0);
	dl.ambientColor = vec4(1.0, 1.0, 1.0, 0.02);
	dl.lightColor = vec4(0.2, 0.4, 1.0, 10.0f);

	return dl;
}