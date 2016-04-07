#include <Model.hpp>

#include <SOIL.h>



namespace Modeling
{
    GLint TextureFromFile(const char* path, string directory)
    {
         //Generate texture ID and load texture data
        string filename = string(path);
        filename = directory + '/' + filename;

        GLuint textureID;
        glGenTextures(1, &textureID);


        int width,height;
        unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

        if (image == NULL)
            throw std::logic_error("TextureFromFile()::INVALID_TEXTURE_PATH");

        // Assign texture to ID
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        SOIL_free_image_data(image);

        return textureID;
    }

    Model::Model(const GLchar* path)
    {
        loadModel(path);
    }


    // Load model from path
    void Model::loadModel(const string& path)
    {
        Assimp::Importer import;
        // Set path and post-processing options
        const aiScene* scene = import.ReadFile(path, aiProcess_FindInstances                  |
                                                     aiProcess_ValidateDataStructure          |
                                                     aiProcess_OptimizeMeshes                 |
                                                     aiProcess_Debone                         |
                                                     aiProcess_Triangulate                    |
                                                     aiProcess_FlipUVs                        |
                                                     aiProcess_GenNormals);


        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
            return;
        }
        // Get directory for loading textures
        directory = path.substr(0, path.find_last_of('/'));
        processNode(scene->mRootNode, scene);
    }

    // Draw all meshes
    void Model::Draw(Shader shader)
    {
        for (auto& mesh : meshes)
        {
            mesh.Draw(shader);
        }
    }

    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        // Get all meshes from node
        for (GLuint i = 0; i < node->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

            meshes.push_back(processMesh(mesh, scene));
        }

        // Process the all child nodes for current node
        for(GLuint i = 0; i < node->mNumChildren; ++i)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex>  vertices;
        vector<GLuint>  indices;
        vector<Texture> textures;

        for (GLuint i = 0; i < mesh->mNumVertices; ++i)
        {
            Vertex vertex;

            glm::vec3 vectorStore;

            vectorStore.x = mesh->mVertices[i].x;
            vectorStore.y = mesh->mVertices[i].y;
            vectorStore.z = mesh->mVertices[i].z;

            vertex.Position = vectorStore;

            vectorStore.x = mesh->mNormals[i].x;
            vectorStore.y = mesh->mNormals[i].y;
            vectorStore.z = mesh->mNormals[i].z;

            vertex.Normal = vectorStore;

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 textureStore;

                textureStore.x = mesh->mTextureCoords[0][i].x;
                textureStore.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = textureStore;
            }
            else
                vertex.TexCoords = glm::vec2(0.f, 0.f);

            vertices.push_back(vertex);
        }

        for (GLuint i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (GLuint j = 0; j < face.mNumIndices; ++j)
            {
                indices.push_back(face.mIndices[j]);
            }
        }


        if (mesh->mMaterialIndex >= 0)
        {
            // Retrieve material object from scene->mMaterials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            vector<Texture> diffuseMap = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());

            vector<Texture> specularMap = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMap.begin(), specularMap.end());
        }


        return Mesh(vertices, indices, textures);

    }

    vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName)
    {
        vector<Texture> textures;


        for(GLuint i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            GLboolean skip = false;


            for(GLuint j = 0; j < textures_loaded.size(); ++j)
            {
                if(textures_loaded[j].path == str)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }

            }

            if(!skip)
            {
                // If texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), directory);
                texture.type = typeName;
                texture.path = str;
                textures.push_back(texture);

                // Add to loaded textures
                textures_loaded.push_back(texture);
            }
        }

        return textures;
    }
}
