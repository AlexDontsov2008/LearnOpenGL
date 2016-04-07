#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static constexpr GLfloat YAW { -90.f };
static constexpr GLfloat PITCH { 0.f };

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    public:
        // Construct from Constructor by default
                    Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 3.f),
                           glm::vec3 up = glm::vec3(0.f, 1.f, 0.f),
                           GLfloat yaw = YAW, GLfloat pitch = PITCH);
        // Construct from position, up values and Euler angles
                    Camera(GLfloat posX, GLfloat posY, GLfloat posZ,
                           GLfloat upX, GLfloat upY, GLfloat upZ,
                           GLfloat yaw, GLfloat pitch);

        // Get View matrix
        glm::mat4   GetViewMatrix() const;

        // Get Zoom
        GLfloat     GetZoom() const;

        // Get Camera position
        glm::vec3   GetPosition() const;

        // Get Front position
        glm::vec3   GetFrontPosition() const;

        // Set new Camera position from the keyboard input
        void        ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);

        // Set Camera orientation from the mouse input
        void        ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

        // Set Camera zoom from the mouse scroll input
        void        ProcessMouseScroll(GLfloat yOffset);

        // My Implementation of LookAt matrix
        glm::mat4   getMyLookAtMatrix() const;

    private:
        // Recalculate front vector from the Euler angles
        void        updateCameraVectors();


    private:
        // LookAt parameters
        glm::vec3   mPosition;
        glm::vec3   mFront;
        glm::vec3   mUp;
        glm::vec3   mRight;
        glm::vec3   mWorldUp;

        // Euler angles
        GLfloat     mYaw;
        GLfloat     mPitch;

        // Camera attributes
        GLfloat     mMovementSpeed;
        GLfloat     mMouseSensitivity;
        GLfloat     mZoom;
};

inline GLfloat Camera::GetZoom() const
{
    return mZoom;
}

inline glm::vec3 Camera::GetPosition() const
{
    return mPosition;
}


inline glm::vec3 Camera::GetFrontPosition() const
{
    return mFront;
}

#endif // _CAMERA_HPP_
