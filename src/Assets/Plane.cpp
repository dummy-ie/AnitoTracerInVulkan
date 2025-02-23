#include "Plane.hpp"
#include "Model.hpp"

using namespace glm;

void Assets::Plane::Create(const glm::vec3& p0, const glm::vec3& p1, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    vec3 center = (p0 + p1) * 0.5f;

    vertices =
    {
        Vertex{vec3(p0.x, p0.y, p0.z) - center, vec3(0, -1, 0), vec2(0), 0},
        Vertex{vec3(p1.x, p0.y, p0.z) - center, vec3(0, -1, 0), vec2(0), 0},
        Vertex{vec3(p1.x, p0.y, p1.z) - center, vec3(0, -1, 0), vec2(0), 0},
        Vertex{vec3(p0.x, p0.y, p1.z) - center, vec3(0, -1, 0), vec2(0), 0},

        Vertex{vec3(p1.x, p0.y + 0.0001f, p0.z) - center, vec3(0, 1, 0), vec2(0), 0},
        Vertex{vec3(p0.x, p0.y + 0.0001f, p0.z) - center, vec3(0, 1, 0), vec2(0), 0},
        Vertex{vec3(p0.x, p0.y + 0.0001f, p1.z) - center, vec3(0, 1, 0), vec2(0), 0},
        Vertex{vec3(p1.x, p0.y + 0.0001f, p1.z) - center, vec3(0, 1, 0), vec2(0), 0},
    };

    indices =
    {
        0, 1, 2, 0, 2, 3,
        4, 5, 6, 6, 7, 4
    };
}
