#pragma once

#include <glm/glm.hpp>
#include <ostream>

inline
std::ostream& operator<<(std::ostream& os, const glm::mat4& mat) {
    for (int x = 0; x < 4; ++x) {
        os << std::fixed
            << mat[x][0] << ", "
            << mat[x][1] << ", "
            << mat[x][2] << ", "
            << mat[x][3] << '\n';
    }
    return os;
}
