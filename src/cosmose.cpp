#include <GL/gl3w.h>
#include <opengl/context.h>
#include <SDL2/SDL.h>
#include <UI/window.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <opengl/texturecache.h>
#include <opengl/texture.h>
#include <framework/sprite/spritemanager.h>
#include <framework/sprite/animatedsprite.h>
#include <framework/sprite/animationgroupmanager.h>
#include <framework/sprite/basicsprite.h>
#include <framework/sprite/scrollingsprite.h>
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
        1920,
        1080,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN
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
        0.0f, 1.0f,
    };
    GLuint modelBuffer;
    glGenBuffers(1, &modelBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLubyte indices[] = {
        0, 1, 2, //Triangle 1
        0, 2, 3  //Triangle 2
    };

    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //DEBUG
    Shader basicVertexShader(GL_VERTEX_SHADER, "src/shaders/instancedsprite.vert");
    Shader basicFragmentShader(GL_FRAGMENT_SHADER, "src/shaders/instancedsprite.frag");
    std::vector<Shader> shaders = {basicVertexShader, basicFragmentShader};
    ProgramLinker shaderProgram(shaders);
    shaderProgram.link();

    OpenGL::TextureCache textureCache;

    Framework::Sprite::SpriteManager spriteCollection(
        textureCache.loadTexture(
            "test-images/demotexture.png",
            GL_REPEAT,
            GL_REPEAT,
            GL_NEAREST,
            GL_NEAREST,
            false
        ),
        4
    );

    Framework::Sprite::SpriteManager backgroundSpriteCollection(
        textureCache.loadTexture(
            "test-images/lavabackground.png",
            GL_MIRRORED_REPEAT,
            GL_MIRRORED_REPEAT,
            GL_NEAREST,
            GL_NEAREST,
            false
        ),
        1
    );

    //Load the dummy sprite sheet to test out the animate sprite
    Framework::Sprite::SpriteManager animatedSpriteCollection(
        textureCache.loadTexture(
            "test-images/TestBrickSpriteSheet.png",
            GL_REPEAT,
            GL_REPEAT,
            GL_NEAREST,
            GL_NEAREST,
            false
        ),
        1
    );

    Framework::Sprite::AnimationGroupManager animationGroups;
    animationGroups.createAnimationGroupFromXMLFile("test-images/TestBrickSpriteSheet.xml");

    std::vector<std::unique_ptr<Framework::Sprite::BasicSprite>> sprites;
    for (int i = 0; i < 4; ++i) {
        sprites.push_back(spriteCollection.getBasicSprite());
    }

    std::vector<std::unique_ptr<Framework::Sprite::ScrollingSprite>> backgroundSprites;
    for (int i = 0; i < 1; ++i) {
        backgroundSprites.push_back(backgroundSpriteCollection.getScrollingSprite(
            0.01f,
            1,
            .5f
        ));
    }

    std::vector<std::unique_ptr<Framework::Sprite::AnimatedSprite>> animatedSprites;
    animatedSprites.push_back(
        animatedSpriteCollection.getAnimatedSprite(
            animationGroups.getAnimationGroup("test-images/TestBrickSpriteSheet.xml"),
            "ColoredBricks",
            30
        )
    );

    Framework::Renderer::InstanceRenderer renderer(
        shaderProgram,
        modelBuffer,
        indexBuffer
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
    // sprites[0]->translate(glm::vec3(-1, -1, 0));
    sprites[1]->translate(glm::vec3(-1, 0, 0));
    sprites[2]->translate(glm::vec3(0, -1, 0));
    sprites[3]->translate(glm::vec3(-1, -1, 0));
    unsigned int frameCount = 0;
    backgroundSprites[0]->scale(glm::vec3(2, 2, 0));
    backgroundSprites[0]->translate(glm::vec3(-.5, -.5, 0));
    //END DEBUG

    //Event loop
    SDL_Event e;
    bool userRequestedExit = false;

    while (userRequestedExit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                userRequestedExit = true;
            }
        }
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        backgroundSprites[0]->advanceFrameCount();
        renderer.render(backgroundSpriteCollection.getInstanceData(), backgroundSpriteCollection.getSpriteTexture(), backgroundSpriteCollection.getInstanceDataCollectionSize(), backgroundSpriteCollection.getInstanceDataCollectionSizeInBytes());
        renderer.render(spriteCollection.getInstanceData(), spriteCollection.getSpriteTexture(), spriteCollection.getInstanceDataCollectionSize(), spriteCollection.getInstanceDataCollectionSizeInBytes());
        frameCount++;
        if (frameCount % 120 == 0) {
            sprites[0] = nullptr;
        }
        if (frameCount % 240 == 0) {
            sprites[1] = nullptr;
        }
        if (frameCount % 360 == 0) {
            sprites[2] = nullptr;
        }
        if (frameCount % 480 == 0) {
            sprites[3] = nullptr;
        }
        SDL_GL_SwapWindow(window.getWindow());
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
