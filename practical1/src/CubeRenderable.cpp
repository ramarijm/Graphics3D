#include "./../include/CubeRenderable.hpp"
#include "./../include/gl_helper.hpp"
#include "./../include/log.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

CubeRenderable::CubeRenderable(ShaderProgramPtr shaderProgram) :
    Renderable(shaderProgram),
    m_pBuffer(0), 
    m_cBuffer(0)
{
    //Build the geometry: just a simple triangle for now
    m_positions.push_back(glm::vec3(0, 0, 0));
    m_positions.push_back(glm::vec3(1, 0, 0));
    m_positions.push_back(glm::vec3(0, 1, 0));
    
    //m_positions.push_back(glm::vec3(1, 0, 0));
    //m_positions.push_back(glm::vec3(1, 1, 0));
    //m_positions.push_back(glm::vec3(0, 1, 0));
    
    m_colors.push_back(glm::vec4(1, 0.8, 1, 1));
    m_colors.push_back(glm::vec4(1, 0.8, 1, 1));
    m_colors.push_back(glm::vec4(1, 0.8, 1, 1));
    //m_colors.push_back(glm::vec4(0.8, 0.8, 1, 1));
    //m_colors.push_back(glm::vec4(0.8, 0.8, 1, 1));
    //m_colors.push_back(glm::vec4(0.8, 0.8, 1, 1));
    
    //set the model matric to Id
    m_model = glm::mat4(1.0);
    
    //Create a new buffer identifier
    //this is the name of a pointer variable on the GPU
    glGenBuffers(1, &m_pBuffer);
    //Bind the buffer to the GL_ARRAY_BUFFER binding point
    //this is a place to perform vertex attributes operations
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    //Transfer data to our new buffer thanks to this binding point
    //this function resizes the buffer to the requested size
    glBufferData(GL_ARRAY_BUFFER, m_positions.size()*sizeof(glm::vec3), m_positions.data(), GL_STATIC_DRAW);
    
    //we do the same with the colors
    glGenBuffers(1, &m_cBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(glm::vec4), m_colors.data(), GL_STATIC_DRAW);
}

CubeRenderable::~CubeRenderable()
{
    glDeleteBuffers(1, &m_pBuffer);
    glDeleteBuffers(1, &m_cBuffer);
}
void CubeRenderable::do_draw()
{
    //get the identifier (location) of the uniform modelMat in te Shader Program
    int modelLocation = m_shaderProgram->getUniformLocation("modelMat");
    //send the data corresponding to this identifier on the GPU
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(m_model));
    //get the identifier of the attribute vPosition in the shader program
    int positionLocation = m_shaderProgram->getAttributeLocation("vPosition");
    //Activate the attribute array at this location
    glEnableVertexAttribArray(positionLocation);
    //Bind the position buffer on the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, m_pBuffer);
    //specify the location and the format of the vertex position attribute
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //draw the triangles
    glDrawArrays(GL_TRIANGLES, 0, m_positions.size());
    //Release the vertex attribute array
    glDisableVertexAttribArray(positionLocation);
    //we do the same for the colors
    int colorsLocation = m_shaderProgram->getAttributeLocation("cPosition");
    glEnableVertexAttribArray(colorsLocation);
    glBindBuffer(GL_ARRAY_BUFFER, m_cBuffer);
    glVertexAttribPointer(colorsLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, m_colors.size());
    glDisableVertexAttribArray(colorsLocation);
}

void CubeRenderable::do_animate(float time)
{
}

