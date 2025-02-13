#include "Capsule.hpp"

using namespace glm;

void Assets::Capsule::Create(const glm::vec3& center, float radius, float height, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
    const int slices = 32;  // Horizontal subdivisions
    const int stacks = 16;  // Vertical subdivisions (for hemispheres)
    const float pi = 3.14159265358979f;

    const float halfCylinderHeight = (height * 0.5f) - radius; // Height excluding hemispheres

    // Generate side vertices (cylinder part)
    for (int i = 0; i <= slices; ++i)
    {
        float theta = 2 * pi * i / slices;
        float x = radius * std::cos(theta);
        float z = radius * std::sin(theta);

        vec3 normal(std::cos(theta), 0, std::sin(theta));  // Outward normal

        // Bottom vertex
        vertices.push_back(Vertex{ vec3(center.x + x, center.y - halfCylinderHeight, center.z + z), normal, vec2(i / (float)slices, 0.0f), 0 });

        // Top vertex
        vertices.push_back(Vertex{ vec3(center.x + x, center.y + halfCylinderHeight, center.z + z), normal, vec2(i / (float)slices, 1.0f), 0 });
    }

    // Generate indices for the cylinder
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

    // Generate hemispherical caps
    for (int cap = 0; cap < 2; ++cap)
    {
        float capOffset = (cap == 0) ? -halfCylinderHeight : halfCylinderHeight; // Offset up/down
        vec3 capCenter = vec3(center.x, center.y + capOffset, center.z);

        int baseIndex = vertices.size();
        for (int j = 0; j <= stacks; ++j)
        {
            float phi = (pi * 0.5f) * (j / (float)stacks);
            float v = std::sin(phi);
            float y = std::cos(phi) * radius;

            if (cap == 0) y = -y;  // Flip for bottom cap

            for (int i = 0; i <= slices; ++i)
            {
                float theta = 2 * pi * i / slices;
                float x = radius * v * std::cos(theta);
                float z = radius * v * std::sin(theta);

                vec3 position = vec3(capCenter.x + x, capCenter.y + y, capCenter.z + z);
                vec3 normal = glm::normalize(vec3(x, y, z)); // Properly normalized normal

                vertices.push_back(Vertex{ position, normal, vec2(i / (float)slices, j / (float)stacks), 0 });
            }
        }

        // Generate indices for the hemisphere caps
        int centerIndex = vertices.size();
        vertices.push_back(Vertex{ capCenter, vec3(0, (cap == 0) ? -1 : 1, 0), vec2(0.5f, 0.5f), 0 });

        for (int j = 0; j < stacks; ++j)
        {
            for (int i = 0; i < slices; ++i)
            {
                int j0 = (j + 0) * (slices + 1);
                int j1 = (j + 1) * (slices + 1);
                int i0 = i + 0;
                int i1 = i + 1;

                indices.push_back(baseIndex + j0 + i0);
                indices.push_back(baseIndex + j1 + i0);
                indices.push_back(baseIndex + j1 + i1);

                indices.push_back(baseIndex + j0 + i0);
                indices.push_back(baseIndex + j1 + i1);
                indices.push_back(baseIndex + j0 + i1);
            }
        }
    }
}
