#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/types.h>

#include <Shader.hpp>


using namespace std;

namespace Modeling
{
    // Vertex store a postion, normal, texture coords.
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture
    {
        GLuint id;
        string type;
        aiString path;
    };

    class Mesh
    {
        public:
                                Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vector<Texture>& textures);
                                ~Mesh();

            void                Draw(Shader shader);
            // Delete VAO, VBO, EBO
            void                ClearMesh();


        private:
            // Initialize VAO, VBO, EBO and vertex attributes.
            void                setupMesh();


        private:
            vector<Vertex>      vertices;
            vector<GLuint>      indices;
            vector<Texture>     textures;

            GLuint              VAO;
            GLuint              VBO;
            GLuint              EBO;
    };
}

#endif // _MESH_HPP_
