#include <GL/gl3w.h>
#include <framework/renderer/instancerenderer.h>
#include <framework/sprite/basicsprite.h>
#include <glm/gtc/type_ptr.hpp>
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
    //Buffer a quad that will be used for ALL sprites (scaled, rotated, and transformed as needed)
    float quadVertices[] = {
        //x,y
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };
    GLuint modelBuffer;
    glGenBuffers(1, &modelBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //testing sprite drawing
    Shader basicSpriteVertexShader(GL_VERTEX_SHADER, "src/shaders/instancedsprite.vert");
    Shader basicSpriteFragmentShader(GL_FRAGMENT_SHADER, "src/shaders/instancedsprite.frag");
    std::vector<Shader> shaders = {basicSpriteVertexShader, basicSpriteFragmentShader};
    ProgramLinker basicSpriteShaderProgram(shaders);
    basicSpriteShaderProgram.link();
    basicSpriteShaderProgram.use();

    //load a texture
    OpenGL::TextureCache textureCache;
    Framework::Sprite::BasicSprite demoSprite(
        textureCache.loadTexture(
            "./demotexture.png",
            GL_REPEAT,
            GL_REPEAT,
            GL_NEAREST,
            GL_NEAREST,
            false
        )
    );
    Framework::Sprite::BasicSprite demoSprite2 = demoSprite;
    demoSprite2.translate(glm::vec3(-1, -1, 0));

    std::vector<Framework::Sprite::BasicSprite> spriteCollection = {demoSprite, demoSprite2};

    Framework::Renderer::InstanceRenderer renderer(basicSpriteShaderProgram, modelBuffer);

    // demoSprite.getTexture()->bind();
    //
    //
    // GLuint basicShaderVertexArray;
    // glGenVertexArrays(1, &basicShaderVertexArray);
    // glBindVertexArray(basicShaderVertexArray);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    // GLuint modelMatrixUniformLocation = basicSpriteShaderProgram.getUniformLocation("modelMatrix");
    // glBindVertexArray(0);
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
        // glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(demoSprite.getModelMatrix()));
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        renderer.render(spriteCollection);
        SDL_GL_SwapWindow(window.getWindow());
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
