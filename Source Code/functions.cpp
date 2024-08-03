#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp> 
#include <fstream>
#include <string>
#include <iostream>
#include "classes.cpp"
#include "gameboard.cpp"

using namespace std;
using namespace sf;

void leaderboard(RenderWindow& window, string fileName) {
    string l1, l2, l3, l4, l5;
    ifstream leaderboardFile(fileName);
    if (leaderboardFile.is_open()) {
        getline(leaderboardFile, l1);
        l1 = "1.\t" + l1;
        getline(leaderboardFile, l2);
        l2 = "2.\t" + l2;
        getline(leaderboardFile, l3);
        l3 = "3.\t" + l3;
        getline(leaderboardFile, l4);
        l4 = "4.\t" + l4;
        getline(leaderboardFile, l5);
        l5 = "5.\t" + l5;

        leaderboardFile.close();
    }
    else {
        cerr << "Unable To Open The File!" << endl;
    }

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

    // Creating an object of the Button class named "button" and specifying its properties
    Button rankButt("RANK", Vector2f(100, 50), 24, Color::Blue, Color::White);
    Button nameButton("NAMES", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Button scoreButton("SCORES", Vector2f(200, 50), 24, Color::Blue, Color::White);
    Button rank1(l1, Vector2f(505.8, 50), 24, Color(154, 197, 219), Color::White);
    Button rank2(l2, Vector2f(505.8, 50), 24, Color(238, 201, 0), Color::White);
    Button rank3(l3, Vector2f(505.8, 50), 24, Color(202, 202, 202), Color::White);
    Button rank4(l4, Vector2f(505.8, 50), 24, Color(185, 97, 30), Color::White);
    Button rank5(l5, Vector2f(505.8, 50), 24, Color(205, 127, 50), Color::White);
    Button back("BACK", Vector2f(100, 50), 24, Color::Blue, Color::White);

    //To display bg image
    Picture background("4096 bg.png");

    background.SetTexture("4096 bg.png");
    background.setScale(Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(Vector2f(0, 0));

    // Making an object of the Font class called "font"
    Font font;

    // Loading the font for the button
    font.loadFromFile("Baloo.ttf");

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

    // Setting button position
    rankButt.setPosition(Vector2f(345, 100));
    nameButton.setPosition(Vector2f(448, 100));
    scoreButton.setPosition(Vector2f(651, 100));
    rank1.leftalign(sf::Vector2f(345.0f, 153.0f), 50.0f);
    rank2.leftalign(sf::Vector2f(345.0f, 206.0f), 50.0f);
    rank3.leftalign(sf::Vector2f(345.0f, 259.0f), 50.0f);
    rank4.leftalign(sf::Vector2f(345.0f, 312.0f), 50.0f);
    rank5.leftalign(sf::Vector2f(345.0f, 365.0f), 50.0f);
    back.setPosition(Vector2f(550, 500));

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

                    if (back.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {

                        return; // Closes the window
                    }
                }
            }
        }

        background.drawTo(window);

        rankButt.drawTo(window);
        nameButton.drawTo(window);
        scoreButton.drawTo(window);
        rank1.drawTo(window);
        rank2.drawTo(window);
        rank3.drawTo(window);
        rank4.drawTo(window);
        rank5.drawTo(window);
        back.drawTo(window);

        window.display();
    }
}

void beforeLeaderboard(RenderWindow& window) {

    Picture preview4x4("grid4_preview.PNG");
    Picture preview6x6("grid6_preview.png");
    Picture preview8x8("grid8_preview.PNG");
    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

    // Creating an object of the Button class named "button" and specifying its properties
    Button four("4 X 4", Vector2f(150, 50), 24, Color(6, 46, 81), Color::White);
    Button six("6 X 6", Vector2f(150, 50), 24, Color(60, 52, 124), Color::White);
    Button eight("8 X 8", Vector2f(150, 50), 24, Color(125, 13, 13), Color::White);
    Button back("Back", Vector2f(100, 45), 24, Color(3, 85, 97), Color::White);

    //To display bg image
    Picture background("4096 bg.png");

    background.SetTexture("4096 bg.png");
    background.setScale(Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(Vector2f(0, 0));

    // Making an object of the Font class called "font"
    Font font;

    // Loading the font for the button
    font.loadFromFile("Baloo.ttf");

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
    back.setPosition(Vector2f(600, 530));
    // setting scale.......
    preview4x4.setScale(Vector2f(250, 250));
    preview6x6.setScale(Vector2f(250, 250));
    preview8x8.setScale(Vector2f(250, 250));

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed) {

                if (event.mouseButton.button == Mouse::Left) {

                    if (four.buttonClicked(window)) {
                        leaderboard(window, "leaderboard4x4.dat");
                    }
                    if (six.buttonClicked(window)) {
                        leaderboard(window, "leaderboard6x6.dat");
                    }
                    if (eight.buttonClicked(window)) {
                        leaderboard(window, "leaderboard8x8.dat");
                    }
                    if (back.buttonClicked(window)) {
                        return;
                    }
                }
            }
        }

        background.drawTo(window);

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

void mainMenu(RenderWindow& window) {

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps
    bool newGame = true;
    string gridButtonText = "";
    string highscoreFile;

    // Button colors
    Color defaultButtonColor(114, 156, 155);
    Color selectedButtonColor(58, 79, 78);

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor
    Button backbutton("BACK", Vector2f(205, 50), 24, defaultButtonColor, Color::White); // Creating an object of the Button class named "button" and specifying its properties
    Button nextbutton("NEXT", Vector2f(205, 50), 24, defaultButtonColor, Color::White);
    Button grid4button("4 x 4", Vector2f(175, 50), 24, Color(25, 105, 174), Color::White);
    Button grid6button("6 x 6", Vector2f(175, 50), 24, Color(113, 85, 156), Color::White);
    Button grid8button("8 x 8", Vector2f(175, 50), 24, Color(205, 52, 6), Color::White);
    Button multiple2button("2", Vector2f(120, 50), 24, defaultButtonColor, Color::White);
    Button multiple3button("3", Vector2f(120, 50), 24, defaultButtonColor, Color::White);
    Button multiple6button("6", Vector2f(120, 50), 24, defaultButtonColor, Color::White);
    Button multiple7button("7", Vector2f(120, 50), 24, defaultButtonColor, Color::White);
    

    //To display bg image
    Picture background("4096 bg.png");

    background.SetTexture("4096 bg.png");
    background.setScale(Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(Vector2f(0, 0));

    Text inputText;

    RectangleShape textBoxBackground;

    Font font;                          // Making an object of the Font class called "font"
    font.loadFromFile("Baloo.ttf"); // Loading the font for the button
    backbutton.setFont(font);           // Setting the font to the button
    nextbutton.setFont(font);
    grid4button.setFont(font);
    grid6button.setFont(font);
    grid8button.setFont(font);
    multiple2button.setFont(font);
    multiple3button.setFont(font);
    multiple6button.setFont(font);
    multiple7button.setFont(font);

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
    

    textBoxBackground.setPosition(350.f, 182.f);
    inputText.setPosition(356.f, 196.f);

    // To make a label above the text box
    Text Name("Name:", font, 17);
    Name.setFillColor(Color(0, 0, 0));
    Name.setPosition(350.f, 155.f);

    string name;
    int multi = 0;
    int grid = 0;

    inputText.setCharacterSize(25);
    inputText.setFillColor(Color::Black);

    textBoxBackground.setSize(Vector2f(590.f, 50.f));
    textBoxBackground.setFillColor(Color(0, 0, 0, 20));
    textBoxBackground.setOutlineThickness(2); // Initially set outline thickness to make it visible when selected
    textBoxBackground.setOutlineColor(Color::Transparent); // Set to transparent initially

    // Cursor for the text box
    RectangleShape cursor(Vector2f(2.f, inputText.getCharacterSize()));
    cursor.setFillColor(Color::Black);
    cursor.setPosition(inputText.getPosition().x + 1.f, inputText.getPosition().y + 1.f); // Adjust the position to be inside the textbox
    bool isTextBoxSelected = false;
    Clock cursorTimer;

    // Cursor position index
    size_t cursorIndex = name.size();

    Button gdisplaybutton(gridButtonText, Vector2f(400, 80), 30, Color(3, 85, 97), Color::White);

    while (window.isOpen()) {
        
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

                    if (backbutton.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {   
                        backbutton.setBackColor(backbutton.buttonClicked(window) ? selectedButtonColor : defaultButtonColor);
                        return;
                    }

                    else if (nextbutton.buttonClicked(window)) {

                        nextbutton.setBackColor(nextbutton.buttonClicked(window) ? selectedButtonColor : defaultButtonColor);
                        // Check if the required conditions are met
                        if (multi > 0 && grid > 0 && !name.empty()) {
                            newGame = true;
                            while (newGame) {
                                gameboard* game = new gameboard(grid, highscoreFile);
                                newGame = game->board(window, name, multi);
                                delete game;
                                game = nullptr;
                            }
                        }
                    }


                    else if (grid4button.buttonClicked(window)) {

                        gdisplaybutton.setBackColor(Color(6, 46, 81));
                        //gridButtonText = "4x4";
                        gdisplaybutton.setText("4x4");
                        highscoreFile = "leaderboard4x4.dat";
                        grid = 4;
                        // multi button colors
                        multiple2button.setBackColor(multi == 2 ? Color(45, 84, 109) : Color(77, 143, 186));
                        multiple3button.setBackColor(multi == 3 ? Color(45, 84, 109) : Color(77, 143, 186));
                        multiple6button.setBackColor(multi == 6 ? Color(45, 84, 109) : Color(77, 143, 186));
                        multiple7button.setBackColor(multi == 7 ? Color(45, 84, 109) : Color(77, 143, 186));
                        nextbutton.setBackColor(nextbutton.buttonClicked(window) ? Color(45, 84, 109) : Color(77, 143, 186));
                        backbutton.setBackColor(backbutton.buttonClicked(window) ? Color(45, 84, 109) : Color(77, 143, 186));
                    }
                    else if (grid6button.buttonClicked(window)) {

                        gdisplaybutton.setBackColor(Color(60, 52, 124));
                        gridButtonText = "6x6";
                        gdisplaybutton.setText("6x6");
                        highscoreFile = "leaderboard6x6.dat";
                        grid = 6;
                        // multi button colors
                        multiple2button.setBackColor(multi == 2 ? Color(78, 64, 111) : Color(132, 108, 188));
                        multiple3button.setBackColor(multi == 3 ? Color(78, 64, 111) : Color(132, 108, 188));
                        multiple6button.setBackColor(multi == 6 ? Color(78, 64, 111) : Color(132, 108, 188));
                        multiple7button.setBackColor(multi == 7 ? Color(78, 64, 111) : Color(132, 108, 188));
                        nextbutton.setBackColor(nextbutton.buttonClicked(window) ? Color(78, 64, 111) : Color(132, 108, 188));
                        backbutton.setBackColor(backbutton.buttonClicked(window) ? Color(78, 64, 111) : Color(132, 108, 188));
                    }
                    else if (grid8button.buttonClicked(window)) {

                        gdisplaybutton.setBackColor(Color(125, 13, 13));
                        gridButtonText = "8x8";
                        gdisplaybutton.setText("8x8");
                        highscoreFile = "leaderboard8x8.dat";
                        grid = 8;
                        // multi button colors
                        multiple2button.setBackColor(multi == 2 ? Color(159, 31, 18) : Color(236, 46, 27));
                        multiple3button.setBackColor(multi == 3 ? Color(159, 31, 18) : Color(236, 46, 27));
                        multiple6button.setBackColor(multi == 6 ? Color(159, 31, 18) : Color(236, 46, 27));
                        multiple7button.setBackColor(multi == 7 ? Color(159, 31, 18) : Color(236, 46, 27));
                        nextbutton.setBackColor(nextbutton.buttonClicked(window) ? Color(159, 31, 18) : Color(236, 46, 27));
                        backbutton.setBackColor(backbutton.buttonClicked(window) ? Color(159, 31, 18) : Color(236, 46, 27));
                    }
                    else if (multiple2button.buttonClicked(window)) {

                        multi = 2;
                        multiple2button.setBackColor(selectedButtonColor);
                        multiple3button.setBackColor(defaultButtonColor);
                        multiple6button.setBackColor(defaultButtonColor);
                        multiple7button.setBackColor(defaultButtonColor);
                    }
                    else if (multiple3button.buttonClicked(window)) {

                        multi = 3;
                        multiple3button.setBackColor(selectedButtonColor);
                        multiple2button.setBackColor(defaultButtonColor);
                        multiple6button.setBackColor(defaultButtonColor);
                        multiple7button.setBackColor(defaultButtonColor);
                    }
                    else if (multiple6button.buttonClicked(window)) {

                        multi = 6;
                        multiple6button.setBackColor(selectedButtonColor);
                        multiple2button.setBackColor(defaultButtonColor);
                        multiple3button.setBackColor(defaultButtonColor);
                        multiple7button.setBackColor(defaultButtonColor);
                    }
                    else if (multiple7button.buttonClicked(window)) {

                        multi = 7;
                        multiple7button.setBackColor(selectedButtonColor);
                        multiple2button.setBackColor(defaultButtonColor);
                        multiple3button.setBackColor(defaultButtonColor);
                        multiple6button.setBackColor(defaultButtonColor);
                    }
                    // Check if the text box was clicked
                    if (textBoxBackground.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        isTextBoxSelected = true;
                        textBoxBackground.setOutlineColor(Color(114, 156, 155)); // Highlight outline color
                    }
                    else {
                        isTextBoxSelected = false;
                        textBoxBackground.setOutlineColor(Color::Transparent); // Default outline color
                    }
                }
            }
            else if (event.type == Event::TextEntered) {
                if (((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')) || event.text.unicode == ' ') {
                    if (inputText.getLocalBounds().width + 10 < textBoxBackground.getSize().x) // Adjust the padding 
                    {
                        name.insert(name.begin() + cursorIndex, static_cast<char>(event.text.unicode));
                        cursorIndex++;
                    }
                }

                 else if (event.text.unicode == 8 && cursorIndex > 0) { // Backspace
                    name.erase(name.begin() + cursorIndex - 1);
                    cursorIndex--;
                }
                inputText.setString(name);

                // Update cursor position based on cursorIndex
                string textBeforeCursor = name.substr(0, cursorIndex);
                Text tempText(textBeforeCursor, font, 25);
                cursor.setPosition(inputText.getPosition().x + tempText.getLocalBounds().width + 1.f, inputText.getPosition().y + 1.f);
            } else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left && cursorIndex > 0) {
                    cursorIndex--;
                } else if (event.key.code == Keyboard::Right && cursorIndex < name.size()) {
                    cursorIndex++;
                }

                // Update cursor position based on cursorIndex
                string textBeforeCursor = name.substr(0, cursorIndex);
                Text tempText(textBeforeCursor, font, 25);
                cursor.setPosition(inputText.getPosition().x + tempText.getLocalBounds().width + 1.f, inputText.getPosition().y + 1.f);
            }
        }

        // Blink the cursor
        if (isTextBoxSelected) {
            if (cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
                cursor.setFillColor(cursor.getFillColor() == Color::Black ? Color::Transparent : Color::Black);
                cursorTimer.restart();
            }
        } else {
            cursor.setFillColor(Color::Transparent);
        }

        //Picture:
        background.drawTo(window);

        // Textbox:
        window.draw(textBoxBackground);
        window.draw(inputText);
        window.draw(Name);

        // Cursor:
        if (isTextBoxSelected) {
            window.draw(cursor);
        }

        // Buttons:
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

        window.display();
    }
}
void firstScreen(RenderWindow& window) {

    window.setFramerateLimit(60);

    // Open the next window
    while (window.isOpen()) {

        // Handle events for the next window (if needed)
        Event Event;

        Button playbutton("PLAY", Vector2f(300, 80), 24, Color(6, 46, 81), Color::White);
        Button lbbutton("LEADERBOARD", Vector2f(300, 60), 24, Color(6, 46, 81), Color::White);

        //To display bg image
        Picture background("4096 bg.png");

        background.SetTexture("4096 bg.png");
        background.setScale(Vector2f(window.getSize().x, window.getSize().y));
        background.setPosition(Vector2f(0, 0));

        Font font;
        font.loadFromFile("Baloo.ttf");
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
                        playbutton.setBackColor(Color(2, 17, 29)); // Change button color to indicate click
                        lbbutton.setBackColor(Color(6, 46, 81));

                        // Draw the updated state
                        window.clear(); // Clear the window
                        background.drawTo(window);
                        playbutton.drawTo(window);
                        lbbutton.drawTo(window);
                        window.display(); // Display the updated state

                        // Pause for 2 seconds
                        sleep(seconds(1));

                        // Call mainMenu after the pause
                        mainMenu(window);
                        return; // Exit the current loop to prevent further events from being processed
                    }
                    else if (lbbutton.buttonClicked(window)) {
                        lbbutton.setBackColor(Color(2, 17, 29)); // Change button color to indicate click
                        playbutton.setBackColor(Color(6, 46, 81));

                        // Draw the updated state
                        window.clear(); // Clear the window
                        background.drawTo(window);
                        playbutton.drawTo(window);
                        lbbutton.drawTo(window);
                        window.display(); // Display the updated state

                        // Pause for 2 seconds
                        sleep(seconds(1));

                        // Call beforeLeaderboard after the pause
                        beforeLeaderboard(window);
                        return; // Exit the current loop to prevent further events from being processed
                    }
                }
            }
        }

        background.drawTo(window);

        playbutton.drawTo(window);
        lbbutton.drawTo(window);

        window.display();
    }
}

