#include "Camera.h"

Camera::Camera(float pos, float speed)
    :position(pos), speed(speed)
{
    const glm::vec3 universalUp = glm::vec3(0.0f, 1.0f, 0.0f);

    front = glm::vec3(0.0f, 0.0f, -1.0f);
    direction = glm::normalize(position + front);
    right = glm::normalize(glm::cross(universalUp, direction));
    up = glm::cross(direction, right);
}

Camera::~Camera()
{

}

void Camera::Move(glm::vec3 moveVector)
{
    if(moveVector.z != 0.0f)
    {
        position -= speed * front * moveVector.z;
    }

    if(moveVector.x != 0.0f)
    {
        position -= glm::normalize(glm::cross(front, up)) * speed * moveVector.x;
    }
}
