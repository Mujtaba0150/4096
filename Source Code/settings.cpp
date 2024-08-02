#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "classes.cpp"

using namespace std;
using namespace sf;

int main()
{
    // Create a window with a title and a size of 800x600 pixels
    
    RenderWindow window(VideoMode::getDesktopMode(), "4096", Style::Close | Style::Titlebar);
    Button settings("Settings", Vector2f(400, 150), 40, Color:: Red, Color::White, 10, 5);
    Button sound("Sound", Vector2f(175,50),30, Color::Red, Color::White);
    Button darkMode("Dark", Vector2f(175,50),30, Color::Red, Color::White);
    
    Font font;
    font.loadFromFile("LEMONMILK.otf");
    settings.setFont(font);
    sound.setFont(font);
    darkMode.setFont(font);

    settings.setPosition(Vector2f(750, 300));
    sound.setPosition(Vector2f(770,500));
    darkMode.setPosition(Vector2f(960,500));

    Picture background("4096 bg.png");

    background.SetTexture("4096 bg.png");

    background.setScale(Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(Vector2f(0, 0));

    // Main loop that continues until the window is closed
    while (window.isOpen())
    {
        // Create an event object to hold events
        sf::Event event;

        // Process all events
        while (window.pollEvent(event))
        {
            // Check for specific event types
            if (event.type == Event::Closed){ // If the close button is pressed
                window.close(); // Close the window
            }
               else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        if (sound.buttonClicked(window)) {
                            window.close();
                        }
                        else if (darkMode.buttonClicked(window)) {
                            window.close();
                        }
                        
                        
                    }
                }

        }

        
        background.drawTo(window);
        // Buttons:
        settings.drawTo(window);
        sound.drawTo(window);
        darkMode.drawTo(window);
        // Display the contents of the window
        window.display();
    }

    return 0;
}
