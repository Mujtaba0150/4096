#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>


using namespace std;
using namespace sf;
class Picture {

public:
    Picture(std::string filePath) {
        texture.loadFromFile(filePath);
        sprite.setTexture(texture);
    }

    void setScale(sf::Vector2f scale) {

        sf::Vector2f Aspectratio(scale.x / texture.getSize().x, scale.y / texture.getSize().y);
        sprite.setScale(Aspectratio);
    }
    void setPosition(sf::Vector2f position) {

        sprite.setPosition(position);

    }
    void drawTo(sf::RenderWindow& window) {

        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

};

class Button {
public:
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
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

        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }
    void leftalign(sf::Vector2f pos, float textOffset) {
        button.setPosition(pos);

        float xPos = pos.x + textOffset; // Set the x-position with the offset
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
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

private:
    sf::RectangleShape button;
    sf::Text text;
};

int main() {

    Picture preview4x4("grid4_preview.png");
    Picture preview6x6("grid6_preview.png");
    Picture preview8x8("grid8_preview.png");
    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

    // Creating an object of the Button class named "button" and specifying its properties
    Button four("4 X 4", Vector2f(150, 50), 24, Color::Blue, Color::White);
    Button six("6 X 6", Vector2f(150, 50), 24, Color::Blue, Color::White);
    Button eight("8 X 8", Vector2f(150, 50), 24, Color::Blue, Color::White);
    Button back("Back", Vector2f(100,45), 24, Color::Blue, Color::White);

    
    // Making an object of the Font class called "font"
    Font font;

    // Loading the font for the button
    font.loadFromFile("LEMONMILK.otf");

    // Setting the font to the button
    four.setFont(font);
    eight.setFont(font);
    six.setFont(font);
    back.setFont(font);

    // Setting button position
    four.setPosition(Vector2f(243, 450));
    six.setPosition(Vector2f(573, 450));
    eight.setPosition(Vector2f(900, 450));
    preview4x4.setPosition(Vector2f(190, 150));
    preview6x6.setPosition(Vector2f(520, 150));
    preview8x8.setPosition(Vector2f(847, 150));
    back.setPosition(Vector2f(600,530));
    //setting scale.......
    preview4x4.setScale(Vector2f(250, 250));
    preview6x6.setScale(Vector2f(250, 250));
    preview8x8.setScale(Vector2f(250, 250));
   

    VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
    RenderWindow window(screenSize, "SFML");            // Create a window using the screen dimensions

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps

    while (window.isOpen()) {
        Event event; // Making an object "event" of the Event class

        while (window.pollEvent(event)) // Loop to manage when something changes in the console
        {
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
            {

                if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                {

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                    if (four.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {
                        //gameboard4
                        window.close(); // Closes the window
                    }
                    if (six.buttonClicked(window)) {
                        //gameboard6
                        window.close();
                    }
                    if(eight.buttonClicked(window)){
                        //gameboard8
                        window.close();
                    }
                    if(back.buttonClicked(window)){
                        //screen before main menu
                        window.close();

                    }
                    
                }
            }
        }

        window.clear(Color::White);

        four.drawTo(window);
        six.drawTo(window);
        eight.drawTo(window);
        preview4x4.drawTo(window); 
        preview6x6.drawTo(window);
        preview8x8.drawTo(window);
        back.drawTo(window);

        window.display();
    }
}
