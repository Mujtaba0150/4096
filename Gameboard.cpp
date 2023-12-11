#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>


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

        float xPos = (pos.x + button.getLocalBounds().width /2) - (text.getLocalBounds().width/2 );
        float yPos = (pos.y + button.getLocalBounds().height /2) - (text.getLocalBounds().height/2 );
        text.setPosition(xPos, yPos);
    }
     void leftalign(sf::Vector2f pos,float textOffset)
    {
        button.setPosition(pos);

         float xPos = pos.x + textOffset; // Set the x-position with the offset
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
int main(){

    //Assigning Variables.
    Button name("2048",Vector2f(150,100),50,Color::Transparent,Color::Black);
    Button boardbackground(" ",Vector2f(395,440),90,Color(105,105,105),Color::Cyan);
    Button b1(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b2(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b3(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b4(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b5(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b6(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b7(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b8(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b9(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b10(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b11(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b12(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b13(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b14(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b15(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button b16(" ",Vector2f(90,100),90,Color(169,169,169),Color::Cyan);
    Button newgame("New Game",Vector2f(100,45),15,Color(160,82,45),Color(188,143,143));
    Button score("Score\n2334",Vector2f(100,55),14,Color(160,82,45),Color(188,143,143));
    Button best("Best\n 2356",Vector2f(100,55),14,Color(160,82,45),Color(188,143,143));


    

    //Applying fonts...
    Font font;
    font.loadFromFile("LEMONMILK-Regular.otf");
    name.setFont(font);
    boardbackground.setFont(font);
    b1.setFont(font);
    b2.setFont(font);
    b3.setFont(font);
    b4.setFont(font);
    b5.setFont(font);
    b6.setFont(font);
    b7.setFont(font);
    b8.setFont(font);
    b9.setFont(font);
    b10.setFont(font);
    b11.setFont(font);
    b12.setFont(font);
    b13.setFont(font);
    b14.setFont(font);
    b15.setFont(font);
    b16.setFont(font);
    newgame.setFont(font);
    score.setFont(font);
    best.setFont(font);
    
    //Assigning the positions...
    boardbackground.setPosition(Vector2f(370,200));
    name.setPosition(Vector2f(370,70));
    b1.setPosition(Vector2f(378,210));
    b2.setPosition(Vector2f(474,210));
    b3.setPosition(Vector2f(570,210));
    b4.setPosition(Vector2f(666,210));
    b5.setPosition(Vector2f(378,316));
    b6.setPosition(Vector2f(474,316));
    b7.setPosition(Vector2f(570,316));
    b8.setPosition(Vector2f(666,316));
    b9.setPosition(Vector2f(378,422));
    b10.setPosition(Vector2f(474,422));
    b11.setPosition(Vector2f(570,422));
    b12.setPosition(Vector2f(666,422));
    b13.setPosition(Vector2f(378,528));
    b14.setPosition(Vector2f(474,528));
    b15.setPosition(Vector2f(570,528));
    b16.setPosition(Vector2f(666,528));
    newgame.setPosition(Vector2f(666,150));
    score.setPosition(Vector2f(566,50));
    best.setPosition(Vector2f(672,50));
    

    VideoMode screenSize = VideoMode::getDesktopMode();
    RenderWindow window(screenSize, "Game Board");
    window.setFramerateLimit(60);
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

                    if (name.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {

                        window.close(); // Closes the window
                    }
                }
            }
        }
    window.clear(Color::White);
    name.drawTo(window);
    boardbackground.drawTo(window);
    b1.drawTo(window);
    b2.drawTo(window);
    b3.drawTo(window);
    b4.drawTo(window);
    b5.drawTo(window);
    b6.drawTo(window);
    b7.drawTo(window);
    b8.drawTo(window);
    b9.drawTo(window);
    b10.drawTo(window);
    b11.drawTo(window);
    b12.drawTo(window);
    b13.drawTo(window);
    b14.drawTo(window);
    b15.drawTo(window);
    b16.drawTo(window);
    newgame.drawTo(window);
    score.drawTo(window);
    best.drawTo(window);
    
    
    window.display();

    }
    return 0;
    
    
    
}
