#pragma once

#include <tuple>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Color.hpp"

namespace fractals {

class Model {
public:
    Model() = default;

    void addPyramid(
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& p3,
        const glm::vec3& p4,
        const Color& c1,
        const Color& c2,
        const Color& c3,
        const Color& c4
    );

    std::vector<GLfloat> getVertexBuffer() const;
    std::size_t getTriangleCount() const;

    std::vector<GLfloat> getColorBuffer() const;

    const glm::mat4& getTransform() const;
    void setTransform(const glm::mat4& transform);
private:
    using Triangle = std::tuple<std::size_t, std::size_t, std::size_t>;

    std::vector<glm::vec3> points;
    std::vector<Triangle> triangles;

    std::vector<Color> colors;

    glm::mat4 transform;
};

} // namespace fractals
