#include "Game/Scene.h"
#include "Input/InputHandler.h"
#include "Rendering/Renderer.h"
#include "Rendering/Window.h"

int main(int argc, char* argv[])
{
    Window window(800, 600, "Test");
    Renderer renderer { };
    InputHandler inputHandler { };
    Scene scene;

    while (window.IsOpen())
    {
        // PRE FRAME
        window.pollEvents();
        window.clear();

        scene.update(0.01);
        scene.render(&window, &renderer);

        
        // POST FRAME
        window.swapBuffers();
        inputHandler.update();
    }

    return 0;
}
