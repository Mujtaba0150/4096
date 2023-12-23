#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
using namespace sf;

class Button {
public:
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor, float offset = 1)
        : offset(offset) {
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);
        button.setSize(size);
        button.setFillColor(bgColor);
    }
    void setFont(sf::Font& font) {
        text.setFont(font);
    }
    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }
    void setTextColor(sf::Color color) {
        text.setFillColor(color);
    }
    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos);
        float xPos = pos.x + (button.getLocalBounds().width - text.getLocalBounds().width) / 2;
        float yPos = pos.y + (button.getLocalBounds().height - text.getLocalBounds().height) / 2;
        // Adjusts the vertical position by subtracting a specific offset (e.g., 5.0f)
        yPos -= offset; // You can adjust this offset as needed
        text.setPosition(xPos, yPos);
    }
    Vector2f getPosition() const {
        return button.getPosition();
    }
    Vector2f getSize() const {
        return button.getSize();
    }
    void drawTo(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(text);
    }
    bool buttonClicked(sf::RenderWindow& window) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (button.getPosition().x <= mousePos.x && mousePos.x <= button.getPosition().x + button.getSize().x && button.getPosition().y <= mousePos.y && mousePos.y <= button.getPosition().y + button.getSize().y) {
            return 1;
        }
        else
            return 0;
    }
    void leftalign(sf::Vector2f pos, float textOffset) {
        button.setPosition(pos);

        float xPos = pos.x + textOffset; // Set the x-position with the offset
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);

    }
private:
    sf::RectangleShape button;
    sf::Text text;
    float offset;
};

int main() {

    VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
    RenderWindow window(screenSize, "SFML");            // Create a window using the screen dimensions
    window.setFramerateLimit(60);                       // Setting the frame rate to 60 fps
    window.setFramerateLimit(60);

    //Open the next window
    while (window.isOpen()) {

        // Handle events for the next window (if needed)
        Event Event;

        Button playbutton("PLAY", Vector2f(300, 80), 24, Color(6, 46, 81), Color::White);
        Button lbbutton("LEADER BOARD", Vector2f(300, 60), 24, Color(6, 46, 81), Color::White);


        Font font;
        font.loadFromFile("LEMONMILK.otf");
        playbutton.setFont(font);
        lbbutton.setFont(font);


        playbutton.setPosition(Vector2f(500, 218));
        lbbutton.setPosition(Vector2f(500, 308));


        while (window.pollEvent(Event)) {
            // Handle events for the next window
            if (Event.type == Event::Closed) {
                window.close();
            }

            // (e.g., window closing event, user interactions, etc.)
            if (Event.type == Event::MouseButtonPressed) {
                if (Event.mouseButton.button == Mouse::Left) {
                    if (playbutton.buttonClicked(window)) {
                        system("./mainMenu");
                        window.close();
                        exit(0);
                        return 0;
                    }
                    else if (lbbutton.buttonClicked(window)) {
                        system("./leaderboard");
                        window.close();
                        exit(0);
                        return 0;
                    }

                }
            }
        }



        window.clear(Color(250, 247, 238));

        playbutton.drawTo(window);
        lbbutton.drawTo(window);


        window.display();
    }
}