#include "functions.cpp"

int main()
{

    VideoMode screenSize = VideoMode::getDesktopMode();
    RenderWindow window(screenSize, "Game Board");
    firstScreen(window);
}
