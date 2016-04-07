#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <memory>

#include <Shader.hpp>
#include <Light/Light.hpp>
#include <Model.hpp>

using namespace Lighting;
using namespace Modeling;


class Scene
{
    public:
                                Scene();
                                ~Scene();


    private:



    private:
        std::vector<Shader>                     mShaderPrograms;
        std::vector<std::unique_ptr<Light>>     mLights;
        std::vector<std::unique_ptr<Model>>     mModels;

};


#endif // _SCENE_HPP_
