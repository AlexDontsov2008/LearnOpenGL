#include <iostream>

#include "Camera.hpp"

static constexpr GLfloat SPEED { 3.0f };
static constexpr GLfloat SENSITIVITY { 0.1f };
static constexpr GLfloat ZOOM { 45.0f };




// Construct from Constructor by default
Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
: mPosition{ position }
, mFront { glm::vec3(0.f, 0.f, -1.0f) }
, mUp { up }
, mRight {}
, mWorldUp { mUp }
, mYaw { yaw }
, mPitch { pitch }
, mMovementSpeed { SPEED }
, mMouseSensitivity { SENSITIVITY }
, mZoom { ZOOM }
{
    updateCameraVectors();
}

// Construct from position, up values and Euler angles
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
: mPosition{ glm::vec3(posX, posY, posZ) }
, mFront { glm::vec3(0.f, 0.f, -1.0f) }
, mUp { glm::vec3(upX, upY, upZ) }
, mRight {}
, mWorldUp { mUp }
, mYaw { yaw }
, mPitch { pitch }
, mMovementSpeed { SPEED }
, mMouseSensitivity { SENSITIVITY }
, mZoom { ZOOM }
{
    updateCameraVectors();
}


glm::mat4 Camera::getMyLookAtMatrix() const
{
    glm::vec3 cameraDirection = glm::normalize(mPosition - mFront);
    glm::mat4 matrix = glm::mat4(glm::vec4(mRight.x, mUp.x, cameraDirection.x, 0.f),
                                 glm::vec4(mRight.y, mUp.y, cameraDirection.y, 0.f),
                                 glm::vec4(mRight.z, mUp.z, cameraDirection.z, 0.f),
                                 glm::vec4(0.f, 0.f, 0.f, 1.f));



    glm::mat4 translate = glm::mat4(glm::vec4(1.f, 0.f, 0.f, 0.f),
                                    glm::vec4(0.f, 1.f, 0.f, 0.f),
                                    glm::vec4(0.f, 0.f, 1.f, 0.f),
                                    glm::vec4(-mPosition, 1.f));

    return matrix * translate;
}

// Get View matrix
glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

// Set new Camera position from the keyboard input
void Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime)
{
    GLfloat velocity { SPEED * deltaTime };

    switch (direction)
    {
        case CameraMovement::FORWARD:
            mPosition += mFront * velocity;
            break;

        case CameraMovement::BACKWARD:
            mPosition -= mFront * velocity;
            break;

        case CameraMovement::LEFT:
            mPosition -= mRight * velocity;
            break;

        case CameraMovement::RIGHT:
            mPosition += mRight * velocity;
            break;
    }
}

// Set Camera orientation from the mouse input
void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
    xOffset *= mMouseSensitivity;
    yOffset *= mMouseSensitivity;

    mYaw += xOffset;
    mPitch += yOffset;

    if (constrainPitch)
    {
        if (mPitch > 89.0f)
            mPitch = 89.0f;

        if (mPitch < -89.0f)
            mPitch = -89.0f;
    }

    updateCameraVectors();
}

// Set Camera zoom from the mouse scroll input
void Camera::ProcessMouseScroll(GLfloat yOffset)
{
    if (mZoom >= 1.0f && mZoom <= 45.0f)
        mZoom -= yOffset;

    if (mZoom <= 1.0f)
        mZoom = 1.0f;

    if (mZoom >= 45.0f)
        mZoom = 45.0f;
}

// Recalculate front vector from the Euler angles
void Camera::updateCameraVectors()
{
    glm::vec3 newFront;

    newFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    newFront.y = sin(glm::radians(mPitch));
    newFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mFront = glm::normalize(newFront);
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));
}


















