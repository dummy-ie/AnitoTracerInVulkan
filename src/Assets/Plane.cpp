#include "Plane.hpp"

#include "Model.hpp"

using namespace glm;

void Assets::Plane::Create(const glm::vec3& p0, const glm::vec3& p1, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	vertices =
	{
		Vertex{vec3(p0.x, p0.y, p0.z), vec3(0, -1, 0), vec2(0), 0},
		Vertex{vec3(p1.x, p0.y, p0.z), vec3(0, -1, 0), vec2(0), 0},
		Vertex{vec3(p1.x, p0.y, p1.z), vec3(0, -1, 0), vec2(0), 0},
		Vertex{vec3(p0.x, p0.y, p1.z), vec3(0, -1, 0), vec2(0), 0},

		Vertex{vec3(p1.x, p1.y, p0.z), vec3(0, 1, 0), vec2(0), 0},
		Vertex{vec3(p0.x, p1.y, p0.z), vec3(0, 1, 0), vec2(0), 0},
		Vertex{vec3(p0.x, p1.y, p1.z), vec3(0, 1, 0), vec2(0), 0},
		Vertex{vec3(p1.x, p1.y, p1.z), vec3(0, 1, 0), vec2(0), 0},
	};

	indices =
	{
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 6, 7, 4
	};
}
