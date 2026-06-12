#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public: 
    Camera(float pos, float speed);
    ~Camera();

    void Move(glm::vec3 moveVector);
private:
    float speed;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
};