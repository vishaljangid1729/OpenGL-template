#include "common.h"

static unsigned int CompileShader( unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);

    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght*sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex":"fragment") << "Shader" << endl;
        cout << message << endl;

        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const string& vertexShader, string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

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
                         SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE

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


    string vertexShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0 ) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    string fragmentShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0 ) out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    unsigned int shader = CreateShader(vertexShader, fragmentShader);

    glUseProgram(shader);


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