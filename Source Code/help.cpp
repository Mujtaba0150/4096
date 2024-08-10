#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "classes.cpp"

using namespace std;
using namespace sf;



int main() {
  RenderWindow window(VideoMode::getDesktopMode(), "4096", Style::Close | Style::Titlebar);


  Button htp(window, "HOW TO PLAY: ", Vector2f(21, 15), 40, Color(6, 46, 81, 190), Color::White, 10, 5);
  Button instructions(window, "Use your keyboard arrow \nkeys to move the tiles.\nWhen two tiles of the same \nnumbers touch, they merge into \nONE!\nJOIN THE NUMBERS AND GET \nTO THE HIGHEST TILE!", Vector2f(21, 28), 25, Color(6, 46, 81, 190), Color::White, 5, 10);

  Font font;
  font.loadFromFile("Baloo.ttf");
  htp.setFont(font);
  instructions.setFont(font);

  htp.setPosition(window, Vector2f(35, 33));
  instructions.setPosition(window, Vector2f(35, 56));

  Picture background("4096 bg(light).png");

  background.SetTexture("4096 bg(light).png");
  background.setScale(Vector2f(window.getSize().x, window.getSize().y));
  background.setPosition(window, Vector2f(0, 0));

  Picture disp("grid4_preview.png");

  disp.SetTexture("grid4_preview.png");
  disp.setScale(Vector2f(500, 500));
  disp.setPosition(window, Vector2f(50, 25));


  // Main loop that continues until the window is closed
  while (window.isOpen()) {
    // Create an event object to hold events
    Event event;

    // Process all events
    while (window.pollEvent(event)) {
      // Check for specific event types
      if (event.type == Event::Closed) { // If the close button is pressed
        window.close(); // Close the window
      }
      else if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
          // if (sound.coursorInbound(window)) {}

        }

      }

    }

    //Picture:
    background.drawTo(window);
    disp.drawTo(window);

    // Buttons:
    htp.drawTo(window);
    instructions.drawTo(window);


    // Display the contents of the window
    window.display();
  }

  return 0;
}
