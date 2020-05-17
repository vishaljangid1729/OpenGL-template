#include"common.h"

int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_NOPARACHUTE) && SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialze SDL");

    }
    else{
        SDL_Log("SDL Initilze");
    }

    SDL_Window * window = SDL_CreateWindow(
        "Hello window", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        500, 
        500,
        SDL_WINDOW_OPENGL

    );


    SDL_GLContext glContest = SDL_GL_CreateContext(window);

    // Ready buffer
    bool isRunning = true;
    while(isRunning){
        SDL_GL_SwapWindow(window);

    }



    SDL_GL_DeleteContext(window);

    SDL_Quit();

    return 0;
}