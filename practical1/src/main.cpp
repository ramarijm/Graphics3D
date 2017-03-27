#include "../include/Viewer.hpp"
#include "../include/log.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/FrameRenderable.hpp"
#include "../include/CubeRenderable.hpp"
#include <iostream>

static void initialize_scene(Viewer& viewer)
    {
    //Path to the vertex shader glsl code
    std::string vShader = "../shaders/flatVertex.glsl";
    //Path to the fragment shader glsl code
    std::string fShader = "../shaders/flatFragment.glsl";
    //Compile and link the shaders into a program
    ShaderProgramPtr flatShader = std::make_shared<ShaderProgram>(vShader, fShader);
    //Add the shader program to the Viewer
    viewer.addShaderProgram(flatShader);
    
    //Renderable instanciation
    CubeRenderablePtr cube = std::make_shared<CubeRenderable>(flatShader);
    //when instanciating a renderable
    //you must specify the shader program used to draw it.
    FrameRenderablePtr frame = std::make_shared<FrameRenderable>(flatShader);
    viewer.addRenderable(frame);
    
    //add the renderable to the Viewer
    viewer.addRenderable(cube);
    }

int main()
{
   
    //std::cout << "Hello World!" << std::endl;
    int width = 1280;
    int height = 720;
    Viewer viewer(width, height);
    initialize_scene(viewer);
    viewer.display();
    while (viewer.isRunning()) {
        viewer.handleEvent();
        viewer.draw();
        viewer.display();
    }
    return EXIT_SUCCESS;
}
