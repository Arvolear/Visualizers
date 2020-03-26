#pragma once

#include "../global/globaluse.hpp"

#include "../shader/shader.hpp"

#include "../framebuffer/framebuffer.hpp"
#include "../framebuffer/colorbuffer.hpp"

#include "../window/renderquad.hpp"

//opengl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template < typename T >
class GaussianBlur
{
    private:
       Shader* blurShader; 
       Shader* scaleShader; 

       vector < T* > colorBuffers;
       T* upscaleBuffer;
       T* downscaleBuffer;
       RenderQuad* quad;

       GLuint bluredTexture;

    public:
        GaussianBlur();

        void genBuffer(int width, int height, FrameBufferData data, float scaleFactor = 1.0);
        void genBuffer(vec2 size, FrameBufferData data, float scaleFactor = 1.0);

        GLuint blur(GLuint textureID, int intensity, float radius = 1.0);

        GLuint getTexture() const;
        pair < GLuint, GLuint > getBuffers() const;

        ~GaussianBlur();

};
