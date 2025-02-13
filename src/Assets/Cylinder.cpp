#include "Cylinder.hpp"

using namespace glm;

void Assets::Cylinder::Create(const glm::vec3& center, float radius, float height, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    const int slices = 32;  // Number of radial subdivisions
    const float pi = 3.14159265358979f;
    const float halfHeight = height * 0.5f;

    // Generate side vertices (smooth shading)
    for (int i = 0; i <= slices; ++i)
    {
        float theta = 2 * pi * i / slices;
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);

        vec3 normal(std::cos(theta), 0, std::sin(theta));  // Outward normal

        // Bottom vertex
        vertices.push_back(Vertex{ vec3(center.x + x, center.y - halfHeight, center.z + z), normal, vec2(i / (float)slices, 0.0f), 0 });

        // Top vertex
        vertices.push_back(Vertex{ vec3(center.x + x, center.y + halfHeight, center.z + z), normal, vec2(i / (float)slices, 1.0f), 0 });
    }

    // Generate indices for side quads
    for (int i = 0; i < slices; ++i)
    {
        int bottomLeft = i * 2;
        int topLeft = bottomLeft + 1;
        int bottomRight = bottomLeft + 2;
        int topRight = bottomLeft + 3;

        indices.push_back(bottomLeft);
        indices.push_back(topLeft);
        indices.push_back(bottomRight);

        indices.push_back(topLeft);
        indices.push_back(topRight);
        indices.push_back(bottomRight);
    }

    // Generate bottom cap (flat shading)
    int bottomCenterIndex = vertices.size();
    vertices.push_back(Vertex{ vec3(center.x, center.y - halfHeight, center.z), vec3(0, -1, 0), vec2(0.5f, 0.5f), 0 });

    int baseIndex = vertices.size();
    for (int i = 0; i <= slices; ++i)
    {
        float theta = 2 * pi * i / slices;
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);

        vertices.push_back(Vertex{ vec3(center.x + x, center.y - halfHeight, center.z + z), vec3(0, -1, 0), vec2((x / radius + 1) * 0.5f, (z / radius + 1) * 0.5f), 0 });
    }

    for (int i = 0; i < slices; ++i)
    {
        indices.push_back(bottomCenterIndex);
        indices.push_back(baseIndex + i + 1);
        indices.push_back(baseIndex + i);
    }

    // Generate top cap (flat shading)
    int topCenterIndex = vertices.size();
    vertices.push_back(Vertex{ vec3(center.x, center.y + halfHeight, center.z), vec3(0, 1, 0), vec2(0.5f, 0.5f), 0 });

    baseIndex = vertices.size();
    for (int i = 0; i <= slices; ++i)
    {
        float theta = 2 * pi * i / slices;
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);

        vertices.push_back(Vertex{ vec3(center.x + x, center.y + halfHeight, center.z + z), vec3(0, 1, 0), vec2((x / radius + 1) * 0.5f, (z / radius + 1) * 0.5f), 0 });
    }

    for (int i = 0; i < slices; ++i)
    {
        indices.push_back(topCenterIndex);
        indices.push_back(baseIndex + i);
        indices.push_back(baseIndex + i + 1);
    }
}
