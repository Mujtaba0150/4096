#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>

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
        string l1,l2,l3,l4,l5;
    ifstream leaderboard("leaderboard.txt");
    if(leaderboard.is_open()){
        getline(leaderboard,l1);
        cout<<l1<<endl;
        getline(leaderboard,l2);
        cout<<l2<<endl;
        getline(leaderboard,l3);
        cout<<l3<<endl;
        getline(leaderboard,l4);
        cout<<l4<<endl;
        getline(leaderboard,l5);
        cout<<l5<<endl;

        leaderboard.close();
    }else{
        cerr<<"Unable To Open The File!"<<endl;
    }

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor
   
    // Creating an object of the Button class named "button" and specifying its properties
    Button rankButt("RANK", Vector2f(100, 50), 24, Color::Blue, Color::White); 
    Button nameButton("NAMES", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Button scoreButton("SCORES", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Button rank1(l1, Vector2f(505.7, 50), 24, Color::Blue, Color::White);
    Button rank2(l2, Vector2f(505.7, 50), 24, Color::Blue, Color::White);
    Button rank3(l3, Vector2f(505.7, 50), 24, Color::Blue, Color::White);
    Button rank4(l4, Vector2f(505.7, 50), 24, Color::Blue, Color::White);
    Button rank5(l5, Vector2f(505.7, 50), 24, Color::Blue, Color::White);
    
    // Making an object of the Font class called "font"
    Font font; 
    
    // Loading the font for the button
    font.loadFromFile("LEMONMILK-Regular.otf"); 
    
    // Setting the font to the button
    rankButt.setFont(font); 
    nameButton.setFont(font);
    scoreButton.setFont(font);
    rank1.setFont(font);
    rank2.setFont(font);
    rank3.setFont(font);
    rank4.setFont(font);
    rank5.setFont(font);
    
    // Setting button position
    rankButt.setPosition(Vector2f(355, 100)); 
    nameButton.setPosition(Vector2f(458, 100));
    scoreButton.setPosition(Vector2f(661, 100));
    rank1.setPosition(Vector2f(355, 153));
    rank2.setPosition(Vector2f(355,206));
    rank3.setPosition(Vector2f(355,259));
    rank4.setPosition(Vector2f(355,312));
    rank5.setPosition(Vector2f(355,365));
    VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
    RenderWindow window(screenSize, "SFML");            // Create a window using the screen dimensions

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps

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

                    if (rankButt.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {

                        window.close(); // Closes the window
                    }
                }
            }
        }

        window.clear(Color::White);

        rankButt.drawTo(window);
        nameButton.drawTo(window);
        scoreButton.drawTo(window);
        rank1.drawTo(window);
        rank2.drawTo(window);
        rank3.drawTo(window);
        rank4.drawTo(window);
        rank5.drawTo(window);

          window.display();
    }
}
