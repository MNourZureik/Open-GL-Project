#include "Camera.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
Camera::Camera()  {}


// Constructor initializes camera attributes
Camera::Camera(float posX, float posY, float posZ, float yaw, float pitch) {
    Position[0] = posX;
    Position[1] = posY;
    Position[2] = posZ;

    Yaw = yaw;
    Pitch = pitch;

    MovementSpeed = 5.0f;
    MouseSensitivity = 0.1f;

    WorldUp[0] = 0.0f;
    WorldUp[1] = 1.0f;
    WorldUp[2] = 0.0f;

    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(char direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;

    if (direction == 'W') {
        for (int i = 0; i < 3; ++i)
            Position[i] += Front[i] * velocity;
    }
    if (direction == 'S') {
        for (int i = 0; i < 3; ++i)
            Position[i] -= Front[i] * velocity;
    }
    if (direction == 'A') {
        for (int i = 0; i < 3; ++i)
            Position[i] -= Right[i] * velocity;
    }
    if (direction == 'D') {
        for (int i = 0; i < 3; ++i)
            Position[i] += Right[i] * velocity;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
    MovementSpeed += yOffset;
    if (MovementSpeed < 1.0f) MovementSpeed = 1.0f;
    if (MovementSpeed > 10.0f) MovementSpeed = 10.0f;
}

void Camera::UpdateCameraVectors() {
    float front[3];
    front[0] = cosf(Yaw * M_PI / 180.0f) * cosf(Pitch * M_PI / 180.0f);
    front[1] = sinf(Pitch * M_PI / 180.0f);
    front[2] = sinf(Yaw * M_PI / 180.0f) * cosf(Pitch * M_PI / 180.0f);

    Normalize(front);

    for (int i = 0; i < 3; ++i)
        Front[i] = front[i];

    CrossProduct(Front, WorldUp, Right);
    Normalize(Right);

    CrossProduct(Right, Front, Up);
    Normalize(Up);
}

void Camera::ApplyView() {
    float center[3];
    for (int i = 0; i < 3; ++i)
        center[i] = Position[i] + Front[i];

    gluLookAt(
        Position[0], Position[1], Position[2],
        center[0], center[1], center[2],
        Up[0], Up[1], Up[2]
    );
}

// Helper method: Normalizes a vector
void Camera::Normalize(float vector[3]) {
    float length = sqrtf(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    if (length != 0.0f) {
        for (int i = 0; i < 3; ++i)
            vector[i] /= length;
    }
}

// Helper method: Calculates the cross product of two vectors
void Camera::CrossProduct(const float v1[3], const float v2[3], float result[3]) {
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
