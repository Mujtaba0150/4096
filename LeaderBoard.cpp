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

int main()
{
    string l1, l2, l3, l4, l5;
    ifstream leaderboard("leaderboard.txt");
    if (leaderboard.is_open())
    {
        getline(leaderboard, l1);
        cout << l1 << endl;
        getline(leaderboard, l2);
        cout << l2 << endl;
        getline(leaderboard, l3);
        cout << l3 << endl;
        getline(leaderboard, l4);
        cout << l4 << endl;
        getline(leaderboard, l5);
        cout << l5 << endl;

        leaderboard.close();
    }
    else
    {
        cerr << "Unable To Open The File!" << endl;
    }

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

    // Creating an object of the Button class named "button" and specifying its properties
    Button rankButt("RANK", Vector2f(100, 50), 24, Color::Blue, Color::White);
    Button nameButton("NAMES", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Button scoreButton("SCORES", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Button rank1(l1, Vector2f(639.8, 50), 24, Color(154, 197, 219), Color::White);
    Button rank2(l2, Vector2f(639.8, 50), 24, Color(238, 201, 0), Color::White);
    Button rank3(l3, Vector2f(639.8, 50), 24, Color(202, 202, 202), Color::White);
    Button rank4(l4, Vector2f(639.8, 50), 24, Color(185, 97, 30), Color::White);
    Button rank5(l5, Vector2f(639.8, 50), 24, Color(205, 127, 50), Color::White);
    Button back("BACK", Vector2f(100, 50), 24, Color::Blue, Color::White);
    Button view("Profile", Vector2f(130, 50), 24, Color::Blue, Color::White);
    Button v1("View", Vector2f(50, 50), 12, Color::Transparent, Color::White);
    Button v2("View", Vector2f(50, 50), 12, Color::Transparent, Color::White);
    Button v3("View", Vector2f(50, 50), 12, Color::Transparent, Color::White);
    Button v4("View", Vector2f(50, 50), 12, Color::Transparent, Color::White);
    Button v5("View", Vector2f(50, 50), 12, Color::Transparent, Color::White);

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
    back.setFont(font);
    view.setFont(font);
    v1.setFont(font);
    v2.setFont(font);
    v3.setFont(font);
    v4.setFont(font);
    v5.setFont(font);

    // Setting button position
    rankButt.setPosition(Vector2f(295, 100));
    nameButton.setPosition(Vector2f(398, 100));
    scoreButton.setPosition(Vector2f(601, 100));
    rank1.leftalign(sf::Vector2f(295.0f, 153.0f), 50.0f);
    rank2.leftalign(sf::Vector2f(295.0f, 206.0f), 50.0f);
    rank3.leftalign(sf::Vector2f(295.0f, 259.0f), 50.0f);
    rank4.leftalign(sf::Vector2f(295.0f, 312.0f), 50.0f);
    rank5.leftalign(sf::Vector2f(295.0f, 365.0f), 50.0f);
    back.setPosition(Vector2f(550, 500));
    view.setPosition(Vector2f(805, 100));
    v1.setPosition(Vector2f(845, 153));
    v2.setPosition(Vector2f(845, 206));
    v3.setPosition(Vector2f(845, 259));
    v4.setPosition(Vector2f(845, 312));
    v5.setPosition(Vector2f(845, 365));

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

                    if (back.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {

                        window.close(); // Closes the window
                    }
                    if (view.buttonClicked(window))
                    {
                        window.close();
                    }
                    if (v1.buttonClicked(window))
                    {
                        VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
                        RenderWindow window(screenSize, l1);
                        sf::Texture texture;

                        // Load the image file (replace "image.jpg" with the path to your JPG file)
                        if (!texture.loadFromFile("image.jpeg"))
                        {

                            return EXIT_FAILURE;
                        }
                        sf::Sprite sprite(texture);
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
                            }
                            window.clear();
                            window.draw(sprite);
                            window.display();
                        }
                    }
                    if (v2.buttonClicked(window))
                    {
                        VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
                        RenderWindow window(screenSize, l1);
                        sf::Texture texture;

                        // Load the image file (replace "image.jpg" with the path to your JPG file)
                        if (!texture.loadFromFile("image.jpeg"))
                        {

                            return EXIT_FAILURE;
                        }
                        sf::Sprite sprite(texture);
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
                            }
                            window.clear();
                            window.draw(sprite);
                            window.display();
                        }
                    }
                    if (v3.buttonClicked(window))
                    {
                        VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
                        RenderWindow window(screenSize, l1);
                        sf::Texture texture;

                        // Load the image file (replace "image.jpg" with the path to your JPG file)
                        if (!texture.loadFromFile("image.jpeg"))
                        {

                            return EXIT_FAILURE;
                        }
                        sf::Sprite sprite(texture);
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
                            }
                            window.clear();
                            window.draw(sprite);
                            window.display();
                        }
                    }
                    if (v4.buttonClicked(window))
                    {
                        VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
                        RenderWindow window(screenSize, l1);
                        sf::Texture texture;

                        // Load the image file (replace "image.jpg" with the path to your JPG file)
                        if (!texture.loadFromFile("image.jpeg"))
                        {

                            return EXIT_FAILURE;
                        }
                        sf::Sprite sprite(texture);
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
                            }
                            window.clear();
                            window.draw(sprite);
                            window.display();
                        }
                    }
                    if (v5.buttonClicked(window))
                    {
                        VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
                        RenderWindow window(screenSize, l1);
                        sf::Texture texture;

                        // Load the image file (replace "image.jpg" with the path to your JPG file)
                        if (!texture.loadFromFile("image.jpeg"))
                        {

                            return EXIT_FAILURE;
                        }
                        sf::Sprite sprite(texture);
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
                            }
                            window.clear();
                            window.draw(sprite);
                            window.display();
                        }
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
        back.drawTo(window);
        view.drawTo(window);
        v1.drawTo(window);
        v2.drawTo(window);
        v3.drawTo(window);
        v4.drawTo(window);
        v5.drawTo(window);

        window.display();
    }
}
