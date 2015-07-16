#include <GL/gl3w.h>
#include <opengl/context.h>
#include <SDL2/SDL.h>
#include <UI/window.h>
#include <utilities/assetcache.h>
#include <utilities/ioutils.h>
#include <iostream>
#include <string>
#include <vector>

#include <glm/gtx/string_cast.hpp>
#include <framework/sprite/basicsprite.h>
#include <framework/sprite/spriteinstancedata.h>
#include <opengl/texturecache.h>
#include <memory>
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
    //Note: needs to be modified to only use 4 points to work properly with SpriteTextureData struct
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

    //DEBUG
    // OpenGL::TextureCache cache;
    // std::shared_ptr<OpenGL::Texture> texture = cache.loadTexture(
    //     "demotexture.png",
    //     GL_REPEAT,
    //     GL_REPEAT,
    //     GL_LINEAR,
    //     GL_LINEAR,
    //     false
    // );
    // Framework::Sprite::SpriteInstanceData instanceData;
    // instanceData.colorModifier.r = 0.75f;
    // Framework::Sprite::BasicSprite testSprite(texture, instanceData, 5);
    // std::cout << testSprite.getInstanceID() << std::endl;
    // std::cout << glm::to_string(testSprite.getInstanceData().colorModifier) << std::endl;
    // instanceData.colorModifier.b = 0.44;
    // std::cout << glm::to_string(testSprite.getInstanceData().colorModifier) << std::endl;
    // std::cout << glm::to_string(testSprite.getInstanceData().MVPMatrix) << std::endl;
    // testSprite.scale(glm::vec3(.5, .75, .9895));
    // std::cout << glm::to_string(instanceData.MVPMatrix) << std::endl;
    //END DEBUG

    //Event loop
    SDL_Event e;
    bool userRequestedExit = false;

    while (userRequestedExit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) {
                userRequestedExit = true;
            }
        }
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // renderer.render(spriteModelMatrices);
        SDL_GL_SwapWindow(window.getWindow());
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
