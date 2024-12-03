#include "Game/Game.h"
#include "Rendering/Window.h"

int main(int argc, char* argv[])
{
    Window* window = new Window(800, 600, "Test");
    Game game = Game(window);
    game.Run();
    return 0;
}
