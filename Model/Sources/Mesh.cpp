#include <Mesh.hpp>

namespace Modeling
{

    // Construct
    Mesh::Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vector<Texture>& textures)
    : vertices { vertices }
    , indices { indices }
    , textures { textures }
    {
        setupMesh();
    }

    Mesh::~Mesh()
    {}

    void Mesh::Draw(Shader shader)
    {
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;

        for (GLuint i = 0; i < textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            stringstream ss;
            string number;
            string name = textures[i].type;

            if (name == "texture_diffuse")
                ss << diffuseNr++;
            else if (name == "texture_specular")
                ss << specularNr++;

            number = ss.str();

            glUniform1f(glGetUniformLocation(shader.getProgram(), ("material." + name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // Also set each mesh's shininess property to a default value
        // (if you want you could extend this to another mesh property and possibly change this value)
        glUniform1f(glGetUniformLocation(shader.getProgram(), "material.shininess"), 16.0f);

        // Draw Mesh
        glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Always good practice to set everything back to defaults once configured.
        for (GLuint i = 0; i < this->textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

    }

    // Delete VAO, VBO, EBO
    void Mesh::ClearMesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }


    // Initialize VAO, VBO, EBO and attributes.
    void Mesh::setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

            // Vertex Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

            // Vertex Normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

            // Vertex Texture Coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
        glBindVertexArray(0);
    }
}
