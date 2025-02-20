#include "BoundingBox.hpp"

#include <glm/ext/quaternion_geometric.hpp>

BoundingBox::BoundingBox(const std::vector<glm::vec3>& vertices, const std::array<glm::vec3, 3>& inAxes)
    : axes(inAxes)
{
    // 1. Compute the center as the average of all vertices.
    glm::vec3 sum(0.0f);
    for (const auto& v : vertices) {
        sum += v;
    }
    center = sum / static_cast<float>(vertices.size());

    // 2. For each axis, compute the min and max projections.
    float minProj[3] = { std::numeric_limits<float>::max(),
                         std::numeric_limits<float>::max(),
                         std::numeric_limits<float>::max() };
    float maxProj[3] = { -std::numeric_limits<float>::max(),
                         -std::numeric_limits<float>::max(),
                         -std::numeric_limits<float>::max() };

    for (const auto& v : vertices) {
        glm::vec3 diff = v - center;
        for (int i = 0; i < 3; ++i) {
            // Project diff onto the i-th axis.
            float proj = glm::dot(diff, axes[i]);
            minProj[i] = std::min(minProj[i], proj);
            maxProj[i] = std::max(maxProj[i], proj);
        }
    }

    // 3. The half-extents are half the distance along each axis.
    halfExtents = glm::vec3(
        (maxProj[0] - minProj[0]) * 0.5f,
        (maxProj[1] - minProj[1]) * 0.5f,
        (maxProj[2] - minProj[2]) * 0.5f
    );

    // Optional: Re-center the box if you want the OBB to tightly enclose the vertices.
    // Here we could shift the center along each axis by the average of the min and max projections.
    for (int i = 0; i < 3; ++i) {
        center += axes[i] * ((minProj[i] + maxProj[i]) * 0.5f);
    }
}
