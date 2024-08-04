#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "classes.cpp"

using namespace std;
using namespace sf;

int main()
{
    
    RenderWindow window(VideoMode::getDesktopMode(), "4096", Style::Close | Style::Titlebar);

    // Load textures for icons
    Picture soundIcon("s.png");
    Picture dark("moon.png");
    

    Button settings("Settings", Vector2f(400, 150), 40, Color(6, 46, 81, 190), Color::White, 10, 5);
    Button sound("", Vector2f(50,50), 30, Color::Transparent, Color::White);
    Button darkMode("", Vector2f(50,50), 30, Color::Transparent, Color::White);
    Button purge("Purge All Highscores", Vector2f(300,50),30,Color(212, 0, 0), Color::White);
    Button sfxbutton("Sound Effects", Vector2f(300, 50), 30, Color(6, 46, 81), Color::White);
    Button backbutton("Back", Vector2f(365, 50), 30, Color(6, 46, 81), Color::White);

    Font font;
    font.loadFromFile("Baloo.ttf");
    settings.setFont(font);
    sound.setFont(font);
    darkMode.setFont(font);
    purge.setFont(font);
    sfxbutton.setFont(font);
    backbutton.setFont(font);

    settings.setPosition(Vector2f(755, 300));
    sound.setPosition(Vector2f(1085,500));
    darkMode.setPosition(Vector2f(770,570));
    purge.setPosition(Vector2f(835, 570));
    sfxbutton.setPosition(Vector2f(770, 500));
    backbutton.setPosition(Vector2f(770, 640));

    Picture background("4096 bg.png");

    background.SetTexture("4096 bg.png");

    background.setScale(Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(Vector2f(0, 0));
    
    soundIcon.setPosition(Vector2f(sound.getPosition().x + 5.f, sound.getPosition().y + 5.f));
    soundIcon.setScale(Vector2f(sound.getSize().x - 10.f , sound.getSize().y - 10.f));

    dark.setPosition(Vector2f(darkMode.getPosition().x + 5.f, darkMode.getPosition().y + 5.f));
    dark.setScale(Vector2f(darkMode.getSize().x - 10.f , darkMode.getSize().y - 10.f));
    
    RectangleShape soundbg;
    soundbg.setSize(Vector2f(50,50));
    soundbg.setFillColor(Color(6, 46, 81));
    soundbg.setPosition(sound.getPosition());

    RectangleShape modebg;
    modebg.setSize(Vector2f(50,50));
    modebg.setFillColor(Color(6, 46, 81));
    modebg.setPosition(darkMode.getPosition());

    bool isMusicPlaying = true; // Flag to track music status

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
                        if (sound.coursorInbound(window)) {
                        //     if (isMusicPlaying) {
                        //     bgmusic.pause(); // Pause the music
                        // } else {
                        //     bgmusic.play(); // Resume the music
                        // }
                        // isMusicPlaying = !isMusicPlaying; // Toggle the music status
                        }
                        else if (darkMode.coursorInbound(window)) {
                            window.close();
                        }
                        else if (purge.coursorInbound(window)) {
                            window.close();
                        }
                        else if (sfxbutton.coursorInbound(window)) {
                            window.close();
                        }
                        else if (backbutton.coursorInbound(window)) {
                            window.close();
                        }
                    }
                }

        }

        
        background.drawTo(window);
        window.draw(soundbg);
        soundIcon.drawTo(window);
        window.draw(modebg);
        dark.drawTo(window);
        
        // Buttons:
        settings.drawTo(window);
        sound.drawTo(window);
        darkMode.drawTo(window);
        purge.drawTo(window);
        sfxbutton.drawTo(window);
        backbutton.drawTo(window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
