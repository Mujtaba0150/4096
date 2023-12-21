#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

private:
    sf::RectangleShape button;
    sf::Text text;
    float offset;
};

int main() {
    VideoMode screenSize = VideoMode::getDesktopMode(); // Get screen dimensions
    RenderWindow window(screenSize, "SFML");            // Create a window using the screen dimensions
    window.setFramerateLimit(60);                       // Setting the frame rate to 60 fps

    string gSize = " ";

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor
    Button backbutton("BACK", Vector2f(205, 50), 24, Color(114, 156, 155), Color::White); // Creating an object of the Button class named "button" and specifying its properties
    Button nextbutton("NEXT", Vector2f(205, 50), 24, Color(114, 156, 155), Color::White);
    Button grid4button("4 x 4", Vector2f(175, 50), 24, Color(25, 105, 174), Color::White);
    Button grid6button("6 x 6", Vector2f(175, 50), 24, Color(113, 85, 156), Color::White);
    Button grid8button("8 x 8", Vector2f(175, 50), 24, Color(205, 52, 6), Color::White);
    Button multiple2button("2", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button multiple3button("3", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button multiple6button("6", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button multiple7button("7", Vector2f(120, 50), 24, Color(114, 156, 155), Color::White);
    Button lbbutton("lb", Vector2f(40, 40), 25, Color(114, 156, 155), Color::White);
    Button volbutton("VOL", Vector2f(40, 40), 20, Color(114, 156, 155), Color::White);

    Text inputText;

    RectangleShape textBoxBackground;

    Font font;                          // Making an object of the Font class called "font"
    font.loadFromFile("LEMONMILK.otf"); // Loading the font for the button
    backbutton.setFont(font);           // Setting the font to the button
    nextbutton.setFont(font);
    grid4button.setFont(font);
    grid6button.setFont(font);
    grid8button.setFont(font);
    multiple2button.setFont(font);
    multiple3button.setFont(font);
    multiple6button.setFont(font);
    multiple7button.setFont(font);
    lbbutton.setFont(font);
    volbutton.setFont(font);

    inputText.setFont(font);

    backbutton.setPosition(Vector2f(20, 520)); // Setting button position
    nextbutton.setPosition(Vector2f(1040, 520));
    grid4button.setPosition(Vector2f(350, 420));
    grid6button.setPosition(Vector2f(560, 420));
    grid8button.setPosition(Vector2f(769, 420));
    multiple2button.setPosition(Vector2f(370, 250));
    multiple3button.setPosition(Vector2f(510, 250));
    multiple6button.setPosition(Vector2f(650, 250));
    multiple7button.setPosition(Vector2f(790, 250));
    lbbutton.setPosition(Vector2f(1200, 10));
    volbutton.setPosition(Vector2f(1200, 55));

    textBoxBackground.setPosition(350.f, 182.f);
    inputText.setPosition(356.f, 196.f);

    //To make a label above the text box
    Text Name("Name:", font, 17);
    Name.setFillColor(Color(0, 0, 0));
    Name.setPosition(350.f, 155.f);

    string input;
    int multi = 0;
    int grid = 0;
    Color gdc = Color(3,85,97);

    inputText.setCharacterSize(25);
    inputText.setFillColor(Color::Black);

    textBoxBackground.setSize(Vector2f(590.f, 50.f));
    textBoxBackground.setFillColor(Color(0, 0, 0, 20));

    bool toCheckSelections = false;

    while (window.isOpen()) {
        Button gdisplaybutton(gSize, Vector2f(400, 80), 30, gdc, Color::White);
        gdisplaybutton.setFont(font);
        gdisplaybutton.setPosition(Vector2f(450, 318));

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

                    if (backbutton.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {
                        //Shd go to main screen
                        window.close(); // Closes the window
                    }

                    else if (lbbutton.buttonClicked(window)) {
                        //Leaderboard function/window
                        window.close();
                    }

                    else if (volbutton.buttonClicked(window)) {
                        //Volume control
                        window.close();
                    }

                    else if (nextbutton.buttonClicked(window)) {
                        //Shd call a functions with all the variables.

                        // Check if the required conditions are met
                        if (multi > 0 && grid > 0 && !input.empty() && !gSize.empty()) {
                                toCheckSelections=true;
                        
                            RenderWindow nextWindow(screenSize, "2048 Game");  // Create a nextWindow using the screen dimensions
                            sf::Texture texture;
                            texture.loadFromFile("heheboi.jpg");

                            // Load the image file (replace "image.jpg" with the path to your JPG file)
                            if (!texture.loadFromFile("heheboi.jpg")) {
                                cerr << "Failed to load texture!" << endl;
                                return EXIT_FAILURE;
                            }
                            sf::Sprite sprite(texture);

                            nextWindow.setFramerateLimit(60);

                            //Open the next window
                            while (nextWindow.isOpen()) {
                                // Handle events for the next window (if needed)
                                Event nextEvent;

                                Button closebutton("CLOSE", Vector2f(300, 80), 24, Color(6, 46, 81), Color::White);
                                closebutton.setFont(font);
                                closebutton.setPosition(Vector2f(550, 318));

                                while (nextWindow.pollEvent(nextEvent)) {
                                    //grid4button.setPreviewTexture(grid4Preview);
                                    // Handle events for the next window
                                    if (nextEvent.type == Event::Closed) {
                                        nextWindow.close();
                                    }

                                    // (e.g., window closing event, user interactions, etc.)
                                    if (nextEvent.type == Event::MouseButtonPressed) {
                                        if (nextEvent.mouseButton.button == Mouse::Left) {
                                            if (closebutton.buttonClicked(nextWindow)) {
                                                nextWindow.close(); // Closes the window
                                            }
                                        }
                                    }

                                }



                                // Clear, draw, and display content for the next window
                                nextWindow.clear();
                                nextWindow.draw(sprite);
                                closebutton.drawTo(nextWindow);
                                // Add your drawing code here
                                nextWindow.display();
                            }
                            // toCheckSelections=false;
                            }

                        }
                    

                    else if (grid4button.buttonClicked(window)) {

                        backbutton.setBackColor(Color(77, 143, 186));
                        nextbutton.setBackColor(Color(77, 143, 186));
                        lbbutton.setBackColor(Color(77, 143, 186));
                        volbutton.setBackColor(Color(77, 143, 186));
                        multiple2button.setBackColor(Color(77, 143, 186));
                        multiple3button.setBackColor(Color(77, 143, 186));
                        multiple6button.setBackColor(Color(77, 143, 186));
                        multiple7button.setBackColor(Color(77, 143, 186));
                        gdisplaybutton.setBackColor(gdc = Color(6, 46, 81));
                        gSize = "4x4";
                        grid = 4;

                    }
                    else if (grid6button.buttonClicked(window)) {

                        backbutton.setBackColor(Color(132, 108, 188));
                        nextbutton.setBackColor(Color(132, 108, 188));
                        lbbutton.setBackColor(Color(132, 108, 188));
                        volbutton.setBackColor(Color(132, 108, 188));
                        multiple2button.setBackColor(Color(132, 108, 188));
                        multiple3button.setBackColor(Color(132, 108, 188));
                        multiple6button.setBackColor(Color(132, 108, 188));
                        multiple7button.setBackColor(Color(132, 108, 188));
                        gdisplaybutton.setBackColor(gdc = Color(60, 52, 124));
                        gSize = "6x6";
                        grid = 6;

                    }
                    else if (grid8button.buttonClicked(window)) {

                        backbutton.setBackColor(Color(236, 46, 27));
                        nextbutton.setBackColor(Color(236, 46, 27));
                        lbbutton.setBackColor(Color(236, 46, 27));
                        volbutton.setBackColor(Color(228, 52, 19));
                        multiple2button.setBackColor(Color(236, 46, 27));
                        multiple3button.setBackColor(Color(236, 46, 27));
                        multiple6button.setBackColor(Color(236, 46, 27));
                        multiple7button.setBackColor(Color(236, 46, 27));
                        gdisplaybutton.setBackColor(gdc = Color(125, 13, 13));
                        gSize = "8x8";
                        grid = 8;
                    }
                    else if (multiple2button.buttonClicked(window)) {

                        multi = 2;
                    }
                    else if (multiple3button.buttonClicked(window)) {

                        multi = 3;
                    }
                    else if (multiple6button.buttonClicked(window)) {

                        multi = 6;
                    }
                    else if (multiple7button.buttonClicked(window)) {

                        multi = 7;
                    }
                }
            }


            else if (event.type == Event::TextEntered) {
                if (((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')) || event.text.unicode == ' ') {
                    if (inputText.getLocalBounds().width + 10 < textBoxBackground.getSize().x) // Adjust the padding (10) as needed
                    {
                        input += static_cast<char>(event.text.unicode);
                    }
                }

                else if (event.text.unicode == 8 && !input.empty()) {
                    input.pop_back();
                }
                inputText.setString(input);
            }

            window.clear(Color::White);

            //Textbox:
            window.draw(textBoxBackground);
            window.draw(inputText);
            window.draw(Name);
        }
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
        volbutton.drawTo(window);

        window.display();
    }
}
