#include "functions.cpp"

int main() {

    VideoMode screenSize = VideoMode::getDesktopMode();
    RenderWindow window(screenSize, "4096");
    firstScreen(window);
}