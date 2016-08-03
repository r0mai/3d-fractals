#include "Model.hpp"

namespace fractals {

void Model::addPyramid(
    const glm::vec3& p1,
    const glm::vec3& p2,
    const glm::vec3& p3,
    const glm::vec3& p4,
    const Color& c1,
    const Color& c2,
    const Color& c3,
    const Color& c4)
{
    auto si  = points.size(); // start_index

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);

    triangles.push_back(std::make_tuple(si + 0, si + 1, si + 2));
    triangles.push_back(std::make_tuple(si + 0, si + 1, si + 3));
    triangles.push_back(std::make_tuple(si + 0, si + 2, si + 3));
    triangles.push_back(std::make_tuple(si + 1, si + 2, si + 3));

    colors.push_back(c1);
    colors.push_back(c2);
    colors.push_back(c3);
    colors.push_back(c4);
}

std::vector<GLfloat> Model::getVertexBuffer() const {
    std::vector<GLfloat> result;
    result.reserve(triangles.size() * 3 * 3);

    for (const Triangle& triangle : triangles) {
        result.push_back(points[std::get<0>(triangle)].x);
        result.push_back(points[std::get<0>(triangle)].y);
        result.push_back(points[std::get<0>(triangle)].z);
        result.push_back(points[std::get<1>(triangle)].x);
        result.push_back(points[std::get<1>(triangle)].y);
        result.push_back(points[std::get<1>(triangle)].z);
        result.push_back(points[std::get<2>(triangle)].x);
        result.push_back(points[std::get<2>(triangle)].y);
        result.push_back(points[std::get<2>(triangle)].z);
    }

    return result;
}

std::size_t Model::getTriangleCount() const {
    return triangles.size();
}

std::vector<GLfloat> Model::getColorBuffer() const {
    std::vector<GLfloat> result;
    result.reserve(triangles.size() * 3 * 3);

    for (const Triangle& triangle : triangles) {
        result.push_back(colors[std::get<0>(triangle)].r);
        result.push_back(colors[std::get<0>(triangle)].g);
        result.push_back(colors[std::get<0>(triangle)].b);
        result.push_back(colors[std::get<1>(triangle)].r);
        result.push_back(colors[std::get<1>(triangle)].g);
        result.push_back(colors[std::get<1>(triangle)].b);
        result.push_back(colors[std::get<2>(triangle)].r);
        result.push_back(colors[std::get<2>(triangle)].g);
        result.push_back(colors[std::get<2>(triangle)].b);
    }

    return result;
}

const glm::mat4& Model::getTransform() const {
    return transform;
}

void Model::setTransform(const glm::mat4& transform) {
    this->transform = transform;
}

} // namespace fractals
