#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <cmath>

class Camera {
public:
    // Position of the camera
    float Position[3];
    // Orientation of the camera (yaw, pitch)
    float Yaw, Pitch;
    // Movement speed and sensitivity
    float MovementSpeed, MouseSensitivity;
	Camera();
    Camera(float posX, float posY, float posZ, float yaw = -90.0f, float pitch = 0.0f);

    // Methods to handle movement and orientation
    void ProcessKeyboard(char direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yOffset);
    void UpdateCameraVectors();

    void ApplyView();

private:
    // Vectors to define the camera orientation
    float Front[3];
    float Right[3];
    float Up[3];
    float WorldUp[3];

    // Helper methods for vector math
    void Normalize(float vector[3]);
    void CrossProduct(const float v1[3], const float v2[3], float result[3]);
};

#endif
