#include "common.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_NOPARACHUTE) && SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialze SDL");
    }
    else
    {
        SDL_Log("SDL Initilze");
    }

    SDL_Window *window =
        SDL_CreateWindow("Hello window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL

        );

    SDL_GLContext glContest = SDL_GL_CreateContext(window);
    glutInit(&argc, argv);
    // glutCreateWindow("This is title of the window");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


    // Ready buffer
    bool isRunning = true;

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);




    while (isRunning)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(window);
    }




    SDL_GL_DeleteContext(window);

    SDL_Quit();

    return 0;
}