#include "Point.h"

glm::vec3 Point::get_pos() const {
    return this->pos;
}

Point::Point(float x, float y, float s, float theta) {
    this->pos = glm::vec3(x, y, 0);
    this->velo = glm::vec3(1, 0, 0);
    this->velo = glm::rotateZ(this->velo, glm::radians(theta));
    this->velo *= s;
}

void Point::collide() {
    if (this->pos.x <= 0 || this->pos.x >= X_MAX) {
        this->velo.x = -this->velo.x;
        this->pos.x = glm::clamp(this->pos.x, 0.0f, (float)X_MAX);
    }
    if (this->pos.y <= 0 || this->pos.y >= Y_MAX) {
        this->velo.y = -this->velo.y;
        this->pos.y = glm::clamp(this->pos.y, 0.0f, (float)Y_MAX);
    }
}

glm::vec3 Point::move(float deltaTime) {
    this->pos += this->velo * deltaTime;
    this->collide();
    return this->pos;
}
