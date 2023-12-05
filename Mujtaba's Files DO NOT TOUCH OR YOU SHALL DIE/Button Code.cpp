#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Button
{
public:
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor)
    {
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
    }
    void setFont(sf::Font &font)
    {
        text.setFont(font);
    }
    void setBackColor(sf::Color color)
    {
        button.setFillColor(color);
    }
    void setTextColor(sf::Color color)
    {
        text.setFillColor(color);
    }
    void setPosition(sf::Vector2f pos)
    {
        button.setPosition(pos);

        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }
    Vector2f getPosition() const
    {
        return button.getPosition();
    }

    Vector2f getSize() const
    {
        return button.getSize();
    }
    void drawTo(sf::RenderWindow &window)
    {
        window.draw(button);
        window.draw(text);
    }
    bool buttonClicked(sf::RenderWindow &window)
    {

        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (button.getPosition().x <= mousePos.x && mousePos.x <= button.getPosition().x + button.getSize().x && button.getPosition().y <= mousePos.y && mousePos.y <= button.getPosition().y + button.getSize().y)
        {
            return 1;
        }
        else
        return 0;
    }

private:
    sf::RectangleShape button;
    sf::Text text;
};

int main()
{

    Button button("Don't Click Me!", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Font font;

    font.loadFromFile("/usr/share/fonts/truetype/tlwg/Laksaman.ttf");
    button.setFont(font);

    button.setPosition(Vector2f(100, 100));

    VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
    RenderWindow window(screenSize, "SFML");            // Create a window using the screen dimensions

    window.setFramerateLimit(60);
    // CircleShape shape(100.f);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            else if (event.type == Event ::MouseButtonPressed)
            {

                if (event.mouseButton.button == Mouse ::Left)
                {

                    Vector2f mousePos = window.mapPixelToCoords(Mouse ::getPosition(window));

                    if (button.buttonClicked(window))
                    {

                        window.close();
                    }
                }
            }
        }

        window.clear();

        // Draw your button here
        button.drawTo(window);

        window.display();
    }
}
