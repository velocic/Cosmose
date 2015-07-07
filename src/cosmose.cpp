#include <GL/gl3w.h>
#include <framework/sprite.h>
#include <opengl/context.h>
#include <opengl/programlinker.h>
#include <opengl/shader.h>
#include <opengl/texturecache.h>
#include <opengl/texture.h>
#include <SDL2/SDL.h>
#include <UI/window.h>
#include <utilities/assetcache.h>
#include <utilities/ioutils.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    UI::Window window(
        "Cosmose",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );
    OpenGL::Context glContext(window);

    if (gl3wInit()) {
        std::cout << "gl3w failed to initialize OpenGL" << std::endl;
        return EXIT_FAILURE;
    }
    
    //testing sprite drawing
    Shader basicSpriteVertexShader(GL_VERTEX_SHADER, "src/shaders/basicsprite.vert");
    Shader basicSpriteFragmentShader(GL_FRAGMENT_SHADER, "src/shaders/basicsprite.frag");
    std::vector<Shader> shaders = {basicSpriteVertexShader, basicSpriteFragmentShader};
    ProgramLinker basicSpriteShaderProgram(shaders);
    basicSpriteShaderProgram.link();
    basicSpriteShaderProgram.use();

    //load a texture
    OpenGL::TextureCache textureCache;
    textureCache.loadTexture(
        "demotexture.png",
        GL_CLAMP_TO_BORDER,
        GL_CLAMP_TO_BORDER,
        GL_LINEAR,
        GL_LINEAR,
        false
    );
    std::shared_ptr<OpenGL::Texture> texturePointer = textureCache.getTexture("demotexture.png");

    float modelCoordinatesAndUVData[] = {
        //x,y,u,v
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    //VBO, VAO, Vertex Coordinates, UV Coordinates, Texture, Uniform matrix, shader program
    GLuint modelBuffer;
    glGenBuffers(1, &modelBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelCoordinatesAndUVData), modelCoordinatesAndUVData, GL_STATIC_DRAW);

    GLuint basicShaderVertexArray;
    glGenVertexArrays(1, &basicShaderVertexArray);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (GLvoid *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (GLvoid *)(2*sizeof(float)));
    GLuint modelMatrixUniformLocation = basicSpriteShaderProgram.getUniformLocation("modelMatrix");
    //end setup for testing sprite drawing

    //Event loop
    SDL_Event e;
    bool userRequestedExit = false;

    while (userRequestedExit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) {
                userRequestedExit = true;
            }
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
