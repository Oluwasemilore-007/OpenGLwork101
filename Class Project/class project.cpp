#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>

float angle = 0.0f;

int width = 1920;
int height = 1080;

void drawCube()
{
    glBegin(GL_QUADS);

    // Front
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    // Back
    glColor3f(0, 1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);

    // Top
    glColor3f(0, 0, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    // Bottom
    glColor3f(1, 1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);

    // Right
    glColor3f(0, 1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);

    // Left
    glColor3f(1, 0, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);

    glEnd();
}

void updateProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow(
        "Rotating Cube",
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window)
        return 1;

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
        return 1;

    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    updateProjection();

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;

            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                width = event.window.data1;
                height = event.window.data2;

                glViewport(0, 0, width, height);
                updateProjection();
            }
        }

        angle += 0.5f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        // camera (kept further back for big cube)
        glTranslatef(0.0f, 0.0f, -8.0f);

        // BIGGER cube
        glScalef(1.5f, 1.5f, 1.5f);

        glRotatef(angle, 1.0f, 1.0f, 0.0f);

        drawCube();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}