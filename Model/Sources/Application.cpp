#include <iostream>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h>

#include <Application.hpp>
#include <Light/DirectionLight.hpp>
#include <Light/PointLight.hpp>
#include <Light/SpotLight.hpp>

Application::BoolKeys Application::mKeys{};
Camera Application::mCamera{ glm::vec3(0.f , 0.f, 3.0f) };


Application::Application(size_t width, size_t height, const std::string& windowName)
: mTextures{}
, mShaderPrograms{}
, mLights{}
, mModels{}
{
    Initialize_window(width, height, windowName);
    Initialize_scene();
}

Application::~Application()
{}

// Start Application
void Application::Run()
{
    Game_loop();
}

// Game loop
void Application::Game_loop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();

        // Calculate the deltaTime of current frame
        static GLfloat lastFrame {};
        GLfloat currentFrame = glfwGetTime();
        GLfloat deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Update Application logic
        Do_movement(deltaTime);

        // Render all objects
        Render();

        glfwSwapBuffers(mWindow);
    }

    glfwTerminate();
}

// Initialize window from width, height, windowName
void Application::Initialize_window(size_t width, size_t height, const std::string& windowName)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    mWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(mWindow);

    // Registering callback functions
    glfwSetKeyCallback(mWindow, Key_callback);
    glfwSetCursorPosCallback(mWindow, Mouse_callback);
    glfwSetScrollCallback(mWindow, Scroll_callback);

    // Initial glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    // Hide cursor and capture it
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


// Initialize input data
void Application::Initialize_scene()
{

    Initialize_shaders();
    Initialize_lights();
    Initialize_models();
}

// Initialize shaders
void Application::Initialize_shaders()
{
    mShaderPrograms.push_back(Shader("Shaders/lighting.vert", "Shaders/lighting.frag"));
    mShaderPrograms.push_back(Shader("Shaders/lamp.vert", "Shaders/lamp.frag"));
    return;
}

// Initialize lights
void Application::Initialize_lights()
{
    using namespace Lighting;

    // Positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 2.3f, -1.6f, -3.0f),
        glm::vec3(-1.7f,  0.9f,  1.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    // Colors of the point lights
    glm::vec3 pointLightColors[] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.9f, 0.9f, 0.9f),
        glm::vec3(0.9f, 0.9f, 0.9f)
    };


    // Initialize DirectLights
    std::unique_ptr<Light>  dirLight {
                        new DirectionLight(Ambient(glm::vec3(0.05f, 0.05f, 0.05f)),     AmbientLocation("dirLight.ambient"),
                                           Diffuse(glm::vec3(0.2f, 0.2f, 0.2f)),        DiffuseLocation("dirLight.diffuse"),
                                           Specular(glm::vec3(0.7f, 0.7f, 0.7f)),       SpecularLocation("dirLight.specular"),
                                           Direction(glm::vec3(-0.2f, -1.0f, -0.3f)),   DirectionLocation("dirLight.direction")) };
    mLights.push_back(std::move(dirLight));


    /************************* Initialize Geometric Lights *************************/

    std::string location {};

    constexpr size_t POINT_LIGHTS_COUNT { 2 };

    // Initialize PointLights
    for (size_t i { 0 }; i < POINT_LIGHTS_COUNT; ++i)
    {
        char num = i + '0';
        std::string position{};
        position += num;

        location = std::string("pointLights[" ) + position + std::string("]");

        std::unique_ptr<Light> pointLight {
                        new PointLight(Ambient(pointLightColors[i] * 0.1f),     AmbientLocation(location   + ".ambient"),
                                       Diffuse(pointLightColors[i]),            DiffuseLocation(location   + ".diffuse"),
                                       Specular(pointLightColors[i]),           SpecularLocation(location  + ".specular"),
                                       Position(pointLightPositions[i]),        PositionLocation(location  + ".position"),
                                       Constant(1.0f),                          ConstantLocation(location  + ".constant"),
                                       Linear(0.009),                           LinearLocation(location    + ".linear"),
                                       Quadratic(0.0032),                       QuadraticLocation(location + ".quadratic"))
        };

        mLights.push_back(std::move(pointLight));

        location.clear();
    }

/*
    // Initialize SpotLight
    location = "spotLight";
    glm::vec3 cameraPosition { mCamera.GetPosition() };
    glm::vec3 cameraDirection { mCamera.GetFrontPosition() };

    std::unique_ptr<Light> spotLight {
        new SpotLight(
          Ambient(glm::vec3(0.0f, 0.0f, 0.0f)),        AmbientLocation(location   + ".ambient"),
          Diffuse(glm::vec3(1.0f, 1.0f, 1.0f)),        DiffuseLocation(location   + ".diffuse"),
          Specular(glm::vec3(1.0f, 1.0f, 1.0f)),       SpecularLocation(location  + ".specular"),
          Position(cameraPosition),                    PositionLocation(location  + ".position"),
          Constant(1.0f),                              ConstantLocation(location  + ".constant"),
          Linear(0.009),                               LinearLocation(location    + ".linear"),
          Quadratic(0.0032),                           QuadraticLocation(location + ".quadratic"),
          Direction(cameraDirection),                  DirectionLocation(location  + ".direction"),
          CutOff(glm::cos(glm::radians(15.0f))),       CutOffLocation(location + ".cutOff"),
          OuterCutOff(glm::cos(glm::radians(20.5f))),  OuterCutOffLocation(location + ".outerCutOff"))
    };
    mLights.push_back(std::move(spotLight));
*/
}

// Initialize models
void Application::Initialize_models()
{
    std::unique_ptr<Modeling::Model> nanosuit { new Modeling::Model { "Resources/Nanosuit/nanosuit.obj" } };
    std::unique_ptr<Modeling::Model> bulb { new Modeling::Model { "Resources/light/bulb.obj" } };

    mModels.push_back(std::move(nanosuit));
    mModels.push_back(std::move(bulb));
}


void Application::Do_movement(GLfloat deltaTime)
{
    // Camera controls
    if(mKeys[GLFW_KEY_W])
        mCamera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);

    if(mKeys[GLFW_KEY_S])
        mCamera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);

    if(mKeys[GLFW_KEY_A])
        mCamera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);

    if(mKeys[GLFW_KEY_D])
        mCamera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

// Generate a texture
void Application::Generate_texture(const char texturePath[])
{
    // Load Textures
    int width, height;
    unsigned char* image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);

    if (image == NULL)
        throw std::logic_error("generate_texture()::INVALID_TEXTURE_PATH");

    // Create texture
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 6);

    // Work with texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image memory and unbind texture object.
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    mTextures.push_back(texture);
}

// Main render function
void Application::Render()
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    constexpr size_t MODEL_COUNT { 6 };
    glm::vec3 model_positions[MODEL_COUNT]
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f)
    };

    /* =================== Shader Use =================== */
    mShaderPrograms[0].Use();

    // Create camera transformations
    glm::mat4 view = mCamera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(mCamera.GetZoom(),
                                            InitialParameters::WINDOW_WIDTH / InitialParameters::WINDOW_HEIGHT,
                                            0.1f, 100.0f);
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(mShaderPrograms[0].getProgram(),  "model");
    GLint viewLoc  = glGetUniformLocation(mShaderPrograms[0].getProgram(),  "view");
    GLint projLoc  = glGetUniformLocation(mShaderPrograms[0].getProgram(),  "projection");


    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Use Lightings
    for (const auto& light : mLights)
        light->UseLight(&mShaderPrograms[0]);

    // Draw models
    for (size_t i = 0; i < MODEL_COUNT; ++i)
    {
        glm::mat4 model;
        model = glm::translate(model, model_positions[i]); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        mModels[0]->Draw(mShaderPrograms[0]);
    }

    // Draw point lights
    Draw_point_lights();

}


// Draw of the point lights abstactions
void Application::Draw_point_lights()
{
    mShaderPrograms[1].Use();
    glm::mat4 view = mCamera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(mCamera.GetZoom(),
                                            InitialParameters::WINDOW_WIDTH / InitialParameters::WINDOW_HEIGHT,
                                            0.1f, 100.0f);

    // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
    GLint modelLoc = glGetUniformLocation(mShaderPrograms[1].getProgram(), "model");
    GLint viewLoc  = glGetUniformLocation(mShaderPrograms[1].getProgram(), "view");
    GLint projLoc  = glGetUniformLocation(mShaderPrograms[1].getProgram(), "projection");

    // Set matrices
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    for (const auto& light : mLights)
    {
        if (light->GetLightType() == Lighting::Light::PointType)
        {
            Lighting::PointLight* pointLight = static_cast<PointLight*>(light.get());

            glm::vec3 position = pointLight->GetPosition().position;

            glm::mat4 model = glm::mat4();
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(-45.f), glm::vec3(1.0f, 0.f, 0.f));
            model = glm::scale(model, glm::vec3(0.1f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            mModels[1]->Draw(mShaderPrograms[1]);
        }
    }
}



void Application::Key_callback(GLFWwindow* window, int key, int scancde, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        mKeys[key] = true;

    if (action == GLFW_RELEASE)
        mKeys[key] = false;
}

// Mouse callback function
void Application::Mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse { true };
    static GLfloat lastX {}, lastY {};

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;

        firstMouse = false;
    }

    glm::vec2 offset = glm::vec2(xpos, ypos) - glm::vec2(lastX, lastY);

    lastX = xpos;
    lastY = ypos;

    mCamera.ProcessMouseMovement(offset.x, -offset.y, true);
}

// Scroll callback function
void  Application::Scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    mCamera.ProcessMouseScroll(yoffset);
}
