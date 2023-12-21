#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class Button {
public:
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor, float offset = 1)
    : offset(offset) 
        {
        text.setString(t);
        text.setFillColor(textColor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgColor);
    }
    void setFont(sf::Font& font)
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

        float xPos = pos.x + (button.getLocalBounds().width - text.getLocalBounds().width) / 2;
        float yPos = pos.y + (button.getLocalBounds().height - text.getLocalBounds().height) / 2;

        // Adjusts the vertical position by subtracting a specific offset (e.g., 5.0f)
        yPos -= offset; // You can adjust this offset as needed

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
    void drawTo(sf::RenderWindow& window) 
    {
        window.draw(button);
        window.draw(text);
    }
    bool buttonClicked(sf::RenderWindow& window) 
    {

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
    float offset;
};

int main()
{
    VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
    RenderWindow window(screenSize, "SFML");            // Create a window using the screen dimensions
    window.setFramerateLimit(60);                       // Setting the frame rate to 60 fps

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor
    Button backbutton("BACK", Vector2f(205, 50), 24, Color(114, 156, 155), Color::White); // Creating an object of the Button class named "button" and specifying its properties
    Button nextbutton("NEXT", Vector2f(205, 50), 24, Color(114, 156, 155), Color::White);
    Button grid4button("4 x 4", Vector2f(175, 50), 24, Color(25, 105, 174), Color::White);
    Button grid6button("6 x 6", Vector2f(175, 50), 24, Color(18, 121, 18), Color::White);
    Button grid8button("8 x 8", Vector2f(175, 50), 24, Color(205, 52, 6), Color::White);
    Button gdisplaybutton("GRID SIZE", Vector2f(400, 80), 30, Color(3, 85, 97), Color::White);
    Button multiple2button("2", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button multiple3button("3", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button multiple6button("6", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button multiple7button("7", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button lbbutton("lb", Vector2f(40, 40), 25, Color(114, 156, 155), Color::White);

    Text inputText;

    RectangleShape textBoxBackground;

    Font font;                          // Making an object of the Font class called "font"
    font.loadFromFile("LEMONMILK.otf"); // Loading the font for the button
    backbutton.setFont(font);           // Setting the font to the button
    nextbutton.setFont(font);
    grid4button.setFont(font);
    grid6button.setFont(font);
    grid8button.setFont(font);
    gdisplaybutton.setFont(font);
    multiple2button.setFont(font);
    multiple3button.setFont(font);
    multiple6button.setFont(font);
    multiple7button.setFont(font);
    lbbutton.setFont(font);

    inputText.setFont(font);

    backbutton.setPosition(Vector2f(20, 520)); // Setting button position
    nextbutton.setPosition(Vector2f(1040, 520));
    grid4button.setPosition(Vector2f(350, 420));
    grid6button.setPosition(Vector2f(560, 420));
    grid8button.setPosition(Vector2f(769, 420));
    gdisplaybutton.setPosition(Vector2f(450, 318));
    multiple2button.setPosition(Vector2f(370, 250));
    multiple3button.setPosition(Vector2f(510, 250));
    multiple6button.setPosition(Vector2f(650, 250));
    multiple7button.setPosition(Vector2f(790, 250));
    lbbutton.setPosition(Vector2f(1200, 10));

    textBoxBackground.setPosition(350.f, 182.f);
    inputText.setPosition(356.f, 196.f);

    string input;

    inputText.setCharacterSize(25);
    inputText.setFillColor(Color::Black);

    textBoxBackground.setSize(Vector2f(590.f, 50.f));
    textBoxBackground.setFillColor(Color::Transparent);

    while (window.isOpen())
    {
        Event event; // Making an object "event" of the Event class

        while (window.pollEvent(event)) // Loop to manage when something changes in the console
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            else if (event.type == Event ::MouseButtonPressed) // Checking if mouse was clicked
            {

                if (event.mouseButton.button == Mouse ::Left) // Checking if the left mouse button was clicked
                {

                    Vector2f mousePos = window.mapPixelToCoords(Mouse ::getPosition(window));

                    if (backbutton.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {

                        window.close(); // Closes the window
                    }
                
                    else if (lbbutton.buttonClicked(window)) 
                    {

                        window.close();
                    }

                    else if (nextbutton.buttonClicked(window)) 
                    {

                        window.close(); 
                    }
                    else if (grid4button.buttonClicked(window)) 
                    {

                        backbutton.setBackColor(Color(77, 143, 186));
                        nextbutton.setBackColor(Color(77, 143, 186));
                        lbbutton.setBackColor(Color(77, 143, 186));
                        multiple2button.setBackColor(Color(77, 143, 186));
                        multiple3button.setBackColor(Color(77, 143, 186));
                        multiple6button.setBackColor(Color(77, 143, 186));
                        multiple7button.setBackColor(Color(77, 143, 186));
                        gdisplaybutton.setBackColor(Color(6, 46, 81));
                        
                    }
                    else if (grid6button.buttonClicked(window)) 
                    {

                        backbutton.setBackColor(Color(59, 205, 59));
                        nextbutton.setBackColor(Color(59, 205, 59));
                        lbbutton.setBackColor(Color(59, 205, 59));
                        multiple2button.setBackColor(Color(59, 205, 59));
                        multiple3button.setBackColor(Color(59, 205, 59));
                        multiple6button.setBackColor(Color(59, 205, 59));
                        multiple7button.setBackColor(Color(59, 205, 59));
                        gdisplaybutton.setBackColor(Color(28, 88, 28));
                    }
                    else if (grid8button.buttonClicked(window)) 
                    {

                        backbutton.setBackColor(Color(236, 46, 27));
                        nextbutton.setBackColor(Color(236, 46, 27));
                        lbbutton.setBackColor(Color(236, 46, 27));
                        multiple2button.setBackColor(Color(236, 46, 27));
                        multiple3button.setBackColor(Color(236, 46, 27));
                        multiple6button.setBackColor(Color(236, 46, 27));
                        multiple7button.setBackColor(Color(236, 46, 27));
                        gdisplaybutton.setBackColor(Color(125, 13, 13));
                    }
                    else if (multiple2button.buttonClicked(window)) 
                    {

                        window.close(); 
                    }
                    else if (multiple3button.buttonClicked(window)) 
                    {

                        window.close(); 
                    }
                    else if (multiple6button.buttonClicked(window)) 
                    {

                        window.close(); 
                    }
                    else if (multiple7button.buttonClicked(window)) 
                    {

                        window.close(); 
                    }
                }
                }
            

            else if (event.type == Event::TextEntered)
            {
                if (((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||(event.text.unicode >= 'a' && event.text.unicode <= 'z')) || event.text.unicode == ' ')
                {
                    if (inputText.getLocalBounds().width + 10 < textBoxBackground.getSize().x) // Adjust the padding (10) as needed
                    {
                        input += static_cast<char>(event.text.unicode);
                    }
                }

                else if (event.text.unicode == 8 && !input.empty())
                {
                    input.pop_back();
                }
                inputText.setString(input);
            }

        window.clear(Color::White);
        
        //Buttons:
        backbutton.drawTo(window);
        nextbutton.drawTo(window);
        grid4button.drawTo(window);
        grid6button.drawTo(window);
        grid8button.drawTo(window);
        gdisplaybutton.drawTo(window);
        multiple2button.drawTo(window);
        multiple3button.drawTo(window);
        multiple6button.drawTo(window);
        multiple7button.drawTo(window);
        lbbutton.drawTo(window);

        //Textbox:
        window.draw(textBoxBackground);
        window.draw(inputText);

        window.display();
    }
}
}