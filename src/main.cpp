#include "Constants.h"
#include "Components/Player.h"
#include "Components/SpriteComponent.h"
#include "Game/Scene.h"
#include "Game/Time.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "Rendering/Texture.h"
#include "Rendering/Window.h"

int main(int argc, char* argv[])
{
    Window window(800, 600, "Test");
    Scene scene;

    Renderer::initialize();
    Input::initialize();
    Renderer::setClearColor(PRIMARY_COLOR);

    auto camera = Entity();
    auto cameraComponent = camera.AddComponent<Camera>(true);
    
    auto player = Entity().WithComponent<SpriteComponent>(new Texture("res/Player.png")).WithComponent<Player>();

    scene.AddEntity(camera, 0);
    scene.AddEntity(player, 1);
    
    while (window.IsOpen())
    {
        // PRE FRAME
        Time::startFrame();
        window.pollEvents();
        window.clear();

        scene.update();
        scene.render(&window, cameraComponent);
        
        // POST FRAME
        window.swapBuffers();
        Input::update();
        Time::endFrame();
    }

    return 0;
}
