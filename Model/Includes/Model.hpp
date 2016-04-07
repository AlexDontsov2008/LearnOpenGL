#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

#include <Mesh.hpp>

using namespace std;

namespace Modeling
{
    GLint TextureFromFile(const char* path, string directory);

    class Model
    {
        public:
                    Model(const GLchar* path);

            // Draw all meshes
            void    Draw(Shader shader);

        private:
            // Load model from path
            void    loadModel(const string& path);


            void    processNode(aiNode* node, const aiScene* scene);
            Mesh    processMesh(aiMesh* mesh, const aiScene* scene);


            vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName);


        private:
            vector<Texture> textures_loaded;
            vector<Mesh>    meshes;
            string          directory;
    };

}

#endif // _MODEL_HPP_
