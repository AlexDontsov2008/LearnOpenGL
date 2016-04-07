#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <iostream>
#include <array>
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Camera.hpp>
#include <Shader.hpp>
#include <Uncopyable.hpp>
#include <Light/Light.hpp>
#include <Model.hpp>

namespace InitialParameters
{
    static constexpr GLfloat WINDOW_WIDTH { 1200.f }, WINDOW_HEIGHT { 675.f };
    static const std::string WINDOW_NAME { "Model" };
    static constexpr size_t KEYS_COUNT { 1024 };
}

using namespace InitialParameters;
using namespace Lighting;
using namespace Modeling;

class Application : private Uncopyable
{
    public:
        using BoolKeys = std::array<bool, KEYS_COUNT>;


    public:
        explicit        Application(size_t width = WINDOW_WIDTH, size_t height = WINDOW_HEIGHT, const std::string& windowName = WINDOW_NAME);
                        ~Application();


        // Start Application
        void            Run();


    private:
        /************* Initialize Block *************/
        void            Initialize_window(size_t width, size_t height, const std::string& windowName);

        // Initialize all input data
        void            Initialize_scene();
        void            Initialize_shaders();
        void            Initialize_textures();
        void            Initialize_lights();
        void            Initialize_models();

        // Draw of the point lights abstactions
        void            Draw_point_lights();


        /************* Logic Block *************/
        void            Game_loop();
        void            Generate_texture(const char texturePath[]);
        void            Do_movement(GLfloat deltaTime);
        void            Render();

        /************* User Input Block *************/

        // Keyboard callback function
        static void     Key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
        // Mouse callback function
        static void     Mouse_callback(GLFWwindow* window, double xpos, double ypos);
        // Scroll callback function
        static void     Scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


    private:
        std::vector<GLuint>                 mTextures;
        std::vector<Shader>                 mShaderPrograms;
        std::vector<std::unique_ptr<Light>> mLights;
        std::vector<std::unique_ptr<Model>> mModels;
        GLFWwindow*                         mWindow;

        static Camera                       mCamera;
        static BoolKeys                     mKeys;
};

#endif // _APPLICATION_HPP_
