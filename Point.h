#ifndef POINT_H
#define POINT_H

#include "matrix_transform.hpp"
#include <glm/gtx/rotate_vector.hpp>

#define X_MAX 1280
#define Y_MAX 720

class Point {
public:
    Point(float x, float y, float s, float theta);
    glm::vec3 get_pos() const;
    void collide();
    glm::vec3 move(float deltaTime);

private:
    glm::vec3 pos;
    glm::vec3 velo;
};

#endif // POINT_H
