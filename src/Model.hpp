#pragma once

#include <tuple>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace fractals {

class Model {
public:
    static Model createPyramid(
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& p3,
        const glm::vec3& p4);

    std::vector<GLfloat> toVertexBuffer() const;
    std::size_t getTriangleCount() const;

    const glm::mat4& getTransform() const;
    void setTransform(const glm::mat4& transform);
private:
    using Triangle = std::tuple<std::size_t, std::size_t, std::size_t>;
    std::vector<glm::vec3> points;
    std::vector<Triangle> triangles;

    glm::mat4 transform;
};

} // namespace fractals
