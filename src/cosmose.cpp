#include <GL/gl3w.h>
#include <opengl/context.h>
#include <SDL2/SDL.h>
#include <UI/window.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <opengl/texturecache.h>
#include <opengl/texture.h>
#include <framework/sprite/spritecollection.h>
#include <framework/sprite/basicsprite.h>
#include <framework/sprite/spriteinstancedata.h>
#include <framework/sprite/spritetexturecoordinates.h>
#include <framework/renderer/instancerenderer.h>
#include <opengl/programlinker.h>
#include <opengl/shader.h>
#include <vector>
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
    Shader basicVertexShader(GL_VERTEX_SHADER, "src/shaders/instancedsprite.vert");
    Shader basicFragmentShader(GL_FRAGMENT_SHADER, "src/shaders/instancedsprite.frag");
    std::vector<Shader> shaders = {basicVertexShader, basicFragmentShader};
    ProgramLinker shaderProgram(shaders);
    shaderProgram.link();

    OpenGL::TextureCache textureCache;
    std::shared_ptr<OpenGL::Texture> debugTexture = textureCache.loadTexture(
        "demotexture.png",
        GL_REPEAT,
        GL_REPEAT,
        GL_LINEAR,
        GL_LINEAR,
        false
    );
    debugTexture->bind();

    Framework::Sprite::SpriteCollection spriteCollection(
        textureCache,
        "demotexture.png"
    );
    std::vector<std::unique_ptr<Framework::Sprite::BasicSprite>> sprites;
    sprites.push_back(spriteCollection.getSprite<Framework::Sprite::BasicSprite>());
    Framework::Renderer::InstanceRenderer renderer(
        shaderProgram,
        modelBuffer
    );
    //Setup vertex attrib pointer for sprite MVP matrix (must be done 1 row at a time)
    renderer.enableVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Framework::Sprite::SpriteInstanceData),
        (GLvoid *)0,
        1
    );
    renderer.enableVertexAttribPointer(
        2,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Framework::Sprite::SpriteInstanceData),
        (GLvoid *)(sizeof(glm::vec4)),
        1
    );
    renderer.enableVertexAttribPointer(
        3,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Framework::Sprite::SpriteInstanceData),
        (GLvoid *)(2 * sizeof(glm::vec4)),
        1
    );
    renderer.enableVertexAttribPointer(
        4,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Framework::Sprite::SpriteInstanceData),
        (GLvoid *)(3 * sizeof(glm::vec4)),
        1
    );
    //Setup vertex attrib pointer for UV coordinates (non-instanced)
    renderer.enableVertexAttribPointer(
        5,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(glm::vec2),
        (GLvoid *)(sizeof(Framework::Sprite::SpriteInstanceData::MVPMatrix)),
        0
    );
    //Setup vertex attrib pointer for colorModifier vec4 (instanced)
    renderer.enableVertexAttribPointer(
        6,
        4,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Framework::Sprite::SpriteInstanceData),
        (GLvoid *)(sizeof(Framework::Sprite::SpriteInstanceData::MVPMatrix) + sizeof(Framework::Sprite::SpriteTextureCoordinates)),
        1
    );
    sprites[0]->translate(glm::vec3(-1, -1, 0));
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
        renderer.render(spriteCollection.getInstanceData());
        SDL_GL_SwapWindow(window.getWindow());
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
