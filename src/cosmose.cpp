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

    /*
     * DEBUG DEBUG DEBUG
     */
    //Test tutorial snippet to see if texture loading works
    Shader vertexShader(GL_VERTEX_SHADER, "src/shaders/test.vert");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "src/shaders/test.frag");
    std::vector<Shader> shaders = {vertexShader, fragmentShader};
    ProgramLinker program(shaders);
    program.link();
    program.use();

    OpenGL::TextureCache textureCache;

    std::shared_ptr<OpenGL::Texture> texture = textureCache.loadTexture(
        "hazard-rotated.png",
        GL_REPEAT,
        GL_REPEAT,
        GL_LINEAR,
        GL_LINEAR,
        false
    );

    // Framework::Sprite testSprite(texture);
    // testSprite.rotate();

    glActiveTexture(GL_TEXTURE0);
    texture->bind();
    //need to set the texture into the uniform2d of fragment shader

    GLfloat vertexData[] = {
        //  X     Y     Z       U     V
         0.0f, 0.8f, 0.0f,   0.5f, 1.0f,
        -0.8f,-0.8f, 0.0f,   0.0f, 0.0f,
         0.8f,-0.8f, 0.0f,   1.0f, 0.0f,
    };
    GLuint vbo = 0;
    GLuint vao = 0;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5*sizeof(GLfloat), (const GLvoid *)(3 * sizeof(GLfloat)));

    /*
     * END DEBUG DEBUG DEBUG
     */


    //Event loop
    SDL_Event e;
    bool userRequestedExit = false;

    while (userRequestedExit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) {
                userRequestedExit = true;
            }
        }

        /*
         * DEBUG DRAW STUFF
         */
        glClearColor(0, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window.getWindow());
        /*
         * END DEBUG DRAW STUFF
         */
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
