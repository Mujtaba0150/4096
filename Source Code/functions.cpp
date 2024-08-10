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

void beforeLeaderboard(RenderWindow& window) {

    Picture preview4x4("grid4_preview.png");
    Picture preview6x6("grid6_preview.png");
    Picture preview8x8("grid8_preview.png");
    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

    // Creating an object of the Button class named "button" and specifying its properties
    Button four(window, "4 X 4", Vector2f(12, 7), 24, Color(6, 46, 81), Color(255, 255, 255));
    Button six(window, "6 X 6", Vector2f(12, 7), 24, Color(60, 52, 124), Color(255, 255, 255));
    Button eight(window, "8 X 8", Vector2f(12, 7), 24, Color(125, 13, 13), Color(255, 255, 255));
    Button back(window, "Back", Vector2f(12, 7), 24, Color(3, 85, 97), Color(255, 255, 255));

    //To display bg image
    Picture background("4096 bg(light).png");

    // background.SetTexture("4096 bg(light).png");
    background.setScale(window, Vector2f(51, 50));
    background.setPosition(window, Vector2f(0, 0));

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
    four.setPosition(window, Vector2f(34.5, 55));
    six.setPosition(window, Vector2f(50, 55));
    eight.setPosition(window, Vector2f(65.5, 55));
    back.setPosition(window, Vector2f(50, 67));

    //Picture previews....
    preview4x4.setPosition(window, Vector2f(27.5, 20));
    preview6x6.setPosition(window, Vector2f(43, 20));
    preview8x8.setPosition(window, Vector2f(58.5, 20));
    // Setting scale.......
    preview4x4.setScale(window, Vector2f(7, 13));
    preview6x6.setScale(window, Vector2f(7, 13));
    preview8x8.setScale(window, Vector2f(7, 13));

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed) {

                if (event.mouseButton.button == Mouse::Left) {

                    if (four.coursorInbound(window)) {
                        // leaderboard(window, "leaderboard4x4.dat");
                    }
                    if (six.coursorInbound(window)) {
                        // leaderboard(window, "leaderboard6x6.dat");
                    }
                    if (eight.coursorInbound(window)) {
                        // leaderboard(window, "leaderboard8x8.dat");
                    }
                    if (back.coursorInbound(window)) {
                        return;
                    }
                }
            }
        }

        window.clear();
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

void multiplierButtonColor(Button* button, int multiplier, string gridButtonText) {
    Color defaultButtonColor(114, 156, 155);
    Color selectedButtonColor(58, 79, 78);

    if (gridButtonText == "4x4") {
        defaultButtonColor = Color(77, 143, 186);
        selectedButtonColor = Color(45, 84, 109);
    }
    else if (gridButtonText == "6x6") {
        defaultButtonColor = Color(132, 108, 188);
        selectedButtonColor = Color(78, 64, 111);
    }
    else if (gridButtonText == "8x8") {
        defaultButtonColor = Color(236, 46, 27);
        selectedButtonColor = Color(159, 31, 18);
    }

    if (multiplier == 2) {
        button[0].setBackColor(selectedButtonColor);
        button[1].setBackColor(defaultButtonColor);
        button[2].setBackColor(defaultButtonColor);
        button[3].setBackColor(defaultButtonColor);
    }
    else if (multiplier == 3) {
        button[1].setBackColor(selectedButtonColor);
        button[0].setBackColor(defaultButtonColor);
        button[2].setBackColor(defaultButtonColor);
        button[3].setBackColor(defaultButtonColor);
    }
    else if (multiplier == 6) {
        button[2].setBackColor(selectedButtonColor);
        button[0].setBackColor(defaultButtonColor);
        button[1].setBackColor(defaultButtonColor);
        button[3].setBackColor(defaultButtonColor);
    }
    else if (multiplier == 7) {
        button[3].setBackColor(selectedButtonColor);
        button[0].setBackColor(defaultButtonColor);
        button[1].setBackColor(defaultButtonColor);
        button[2].setBackColor(defaultButtonColor);
    }
    else if (multiplier == 0) {
        for (int i = 0; i < 4; i++) {
            button[i].setBackColor(defaultButtonColor);
        }
    }
}
void mainMenu(RenderWindow& window) {

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps
    bool newGame = true;
    string highscoreFile;

    // Button colors
    Color defaultButtonColor(114, 156, 155);
    Color selectedButtonColor(58, 79, 78);

    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor
    Button backbutton(window, "BACK", Vector2f(12, 7), 30, defaultButtonColor, Color::White); // Creating an object of the Button class named "button" and specifying its properties
    Button nextbutton(window, "NEXT", Vector2f(12, 7), 30, defaultButtonColor, Color::White);
    Button grid4button(window, "4 x 4", Vector2f(12, 7), 30, Color(25, 105, 174), Color::White);
    Button grid6button(window, "6 x 6", Vector2f(12, 7), 30, Color(113, 85, 156), Color::White);
    Button grid8button(window, "8 x 8", Vector2f(12, 7), 30, Color(205, 52, 6), Color::White);
    Button gdisplaybutton(window, "", Vector2f(25, 16), 45, Color(3, 85, 97), Color::White);

    Button multiples[4] = { Button(window,"2", Vector2f(9, 7), 30, defaultButtonColor, Color::White),
                            Button(window,"3", Vector2f(9, 7), 30, defaultButtonColor, Color::White),
                            Button(window,"6", Vector2f(9, 7), 30, defaultButtonColor, Color::White),
                            Button(window,"7", Vector2f(9, 7), 30, defaultButtonColor, Color::White) };

    // To display bg image
    Picture background("4096 bg(light).png");

    background.SetTexture("4096 bg(light).png");
    background.setScale(window, Vector2f(51, 50));
    background.setPosition(window, Vector2f(0, 0));

    Text inputText;

    Button textBoxBackground(window, "", Vector2f(46, 8), 30, Color(0, 0, 0, 50), Color::Black);

    RectangleShape textBoxBackgroundOld;

    Font font;                      // Making an object of the Font class called "font"
    font.loadFromFile("Baloo.ttf"); // Loading the font for the button
    backbutton.setFont(font);       // Setting the font to the button
    nextbutton.setFont(font);
    grid4button.setFont(font);
    grid6button.setFont(font);
    grid8button.setFont(font);
    gdisplaybutton.setFont(font);
    textBoxBackground.setFont(font);

    for (int i = 0; i < 4; i++) {
        multiples[i].setFont(font);
    }

    inputText.setFont(font);

    backbutton.setPosition(window, Vector2f(19, 75)); // Setting button position
    nextbutton.setPosition(window, Vector2f(80, 75));
    grid4button.setPosition(window, Vector2f(37, 65));
    grid6button.setPosition(window, Vector2f(50, 65));
    grid8button.setPosition(window, Vector2f(63, 65));
    gdisplaybutton.setPosition(window, Vector2f(50, 50));
    textBoxBackground.setPosition(window, Vector2f(49.5, 26));

    textBoxBackgroundOld.setPosition(Vector2f(500, 241));

    for (int i = 0; i < 4; i++) {
        multiples[i].setPosition(window, Vector2f(31.5 + 12 * i, 35));
    }


    inputText.setPosition(510.f, 240.f);

    // To make a label above the text box
    Text Name("Name:", font, 35);
    Name.setFillColor(Color(0, 0, 0));
    Name.setPosition(510.f, 190.f);
    string name;
    int multi = 0;
    int grid = 0;

    inputText.setCharacterSize(35);
    inputText.setFillColor(Color::Black);

    textBoxBackgroundOld.setSize(Vector2f(900.f, 80.f));
    textBoxBackgroundOld.setFillColor(Color(0, 0, 0, 50));
    textBoxBackgroundOld.setOutlineThickness(3);              // Initially set outline thickness to make it visible when selected
    textBoxBackgroundOld.setOutlineColor(Color::Transparent); // Set to transparent initially

    // Cursor for the text box
    RectangleShape cursor(Vector2f(2.f, inputText.getCharacterSize()));
    cursor.setFillColor(Color::Black);
    cursor.setPosition(inputText.getPosition().x + 2.f, inputText.getPosition().y + 2.f); // Adjust the position to be inside the textbox
    bool isTextBoxSelected = false;
    Clock cursorTimer;

    // Cursor position index
    int cursorIndex = name.size();

    while (window.isOpen()) {

        Event event; // Making an object "event" of the Event class

        while (window.pollEvent(event)) { // Loop to manage when something changes in the console
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed) { // Checking if mouse was clicked

                if (event.mouseButton.button == Mouse::Left) { // Checking if the left mouse button was clicked

                    if (backbutton.coursorInbound(window)) { // Using self defined function to check if the button was clicked
                        backbutton.setBackColor(backbutton.coursorInbound(window) ? selectedButtonColor : defaultButtonColor);
                        return;
                    }

                    else if (nextbutton.coursorInbound(window)) {

                        nextbutton.setBackColor(nextbutton.coursorInbound(window) ? selectedButtonColor : defaultButtonColor);
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

                    else if (grid4button.coursorInbound(window)) {

                        gdisplaybutton.setBackColor(Color(6, 46, 81));
                        gdisplaybutton.setText("4x4");
                        highscoreFile = "leaderboard4x4.dat";
                        grid = 4;
                        // multi button colors
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                        nextbutton.setBackColor(nextbutton.coursorInbound(window) ? Color(45, 84, 109) : Color(77, 143, 186));
                        backbutton.setBackColor(backbutton.coursorInbound(window) ? Color(45, 84, 109) : Color(77, 143, 186));
                    }
                    else if (grid6button.coursorInbound(window)) {

                        gdisplaybutton.setBackColor(Color(60, 52, 124));
                        gdisplaybutton.setText("6x6");
                        highscoreFile = "leaderboard6x6.dat";
                        grid = 6;
                        // multi button colors
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                        nextbutton.setBackColor(nextbutton.coursorInbound(window) ? Color(78, 64, 111) : Color(132, 108, 188));
                        backbutton.setBackColor(backbutton.coursorInbound(window) ? Color(78, 64, 111) : Color(132, 108, 188));
                    }
                    else if (grid8button.coursorInbound(window)) {

                        gdisplaybutton.setBackColor(Color(125, 13, 13));
                        gdisplaybutton.setText("8x8");
                        highscoreFile = "leaderboard8x8.dat";
                        grid = 8;
                        // multi button colors
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                        nextbutton.setBackColor(nextbutton.coursorInbound(window) ? Color(159, 31, 18) : Color(236, 46, 27));
                        backbutton.setBackColor(backbutton.coursorInbound(window) ? Color(159, 31, 18) : Color(236, 46, 27));
                    }
                    else if (multiples[0].coursorInbound(window)) {

                        multi = 2;
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                    }
                    else if (multiples[1].coursorInbound(window)) {

                        multi = 3;
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                    }
                    else if (multiples[2].coursorInbound(window)) {

                        multi = 6;
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                    }
                    else if (multiples[3].coursorInbound(window)) {

                        multi = 7;
                        multiplierButtonColor(multiples, multi, gdisplaybutton.getText().getString());
                    }
                    // Check if the text box was clicked
                    if (textBoxBackgroundOld.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        isTextBoxSelected = true;
                        textBoxBackgroundOld.setOutlineColor(Color(114, 156, 155)); // Highlight outline color
                    }
                    else {
                        isTextBoxSelected = false;
                        textBoxBackgroundOld.setOutlineColor(Color::Transparent); // Default outline color
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
                Text tempText(textBeforeCursor, font, 35);
                cursor.setPosition(inputText.getPosition().x + tempText.getLocalBounds().width + 2.f, inputText.getPosition().y + 2.f);
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left && cursorIndex > 0) {
                    cursorIndex--;
                }
                else if (event.key.code == Keyboard::Right && cursorIndex < name.size()) {
                    cursorIndex++;
                }

                // Update cursor position based on cursorIndex
                string textBeforeCursor = name.substr(0, cursorIndex);
                Text tempText(textBeforeCursor, font, 35);
                cursor.setPosition(inputText.getPosition().x + tempText.getLocalBounds().width + 2.f, inputText.getPosition().y + 2.f);
            }
        }

        // Blink the cursor
        if (isTextBoxSelected) {
            if (cursorTimer.getElapsedTime().asSeconds() >= 0.5f) {
                cursor.setFillColor(cursor.getFillColor() == Color::Black ? Color::Transparent : Color::Black);
                cursorTimer.restart();
            }
        }
        else {
            cursor.setFillColor(Color::Transparent);
        }

        window.clear();

        // Picture:
        background.drawTo(window);

        // Textbox:
        window.draw(textBoxBackgroundOld);
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
        textBoxBackground.drawTo(window);

        for (int i = 0; i < 4; i++) {
            multiples[i].drawTo(window);
        }

        window.display();
    }
}

void firstScreen(RenderWindow& window) {

    window.setFramerateLimit(60);

    Button playbutton(window, "PLAY", Vector2f(22, 12), 24, Color(6, 46, 81), Color::White);
    Button lbbutton(window, "LEADERBOARD", Vector2f(22, 7), 24, Color(6, 46, 81), Color::White);
    Button settingbutton(window, "SETTINGS", Vector2f(22, 7), 24, Color(6, 46, 81), Color::White);

    //To display bg image
    Picture background("4096 bg(light).png");

    background.setScale(window, Vector2f(51, 50));
    background.setPosition(window, Vector2f(0, 0));

    Font font;
    font.loadFromFile("Baloo.ttf");
    playbutton.setFont(font);
    lbbutton.setFont(font);
    settingbutton.setFont(font);

    playbutton.setPosition(window, Vector2f(50, 42));
    lbbutton.setPosition(window, Vector2f(50, 53));
    settingbutton.setPosition(window, Vector2f(50, 61.5));

    bool isMusicPlaying = true;
    bool lightTheme = true;
    bool sfx = true;

    fstream file("settings.dat", ios::in);

    if (file.is_open()) {
        file >> isMusicPlaying;
        file >> lightTheme;
        file >> sfx;
    }
    else {
        file.close();
        file.open("settings.txt", ios::out);
        file << 1 << endl;
        file << 1 << endl;
        file << 1 << endl;
    }
    file.close();

    // Music
    Music bgmusic;
    if (!bgmusic.openFromFile("bg.ogg"))
        // Handle error if audio fails to load
        return;
    else if (isMusicPlaying)
        bgmusic.play();

    if (!lightTheme)
        background.SetTexture("4096 bg(dark).png");

    // Open the next window
    while (window.isOpen()) {

        // Handle events for the next window (if needed)
        Event Event;

        if (playbutton.coursorInbound(window))
            playbutton.setBackColor(Color(2, 17, 29)); // Change button color to indicate hover
        else
            playbutton.setBackColor(Color(6, 46, 81));

        if (lbbutton.coursorInbound(window))
            lbbutton.setBackColor(Color(2, 17, 29)); // Change button color to indicate hover
        else
            lbbutton.setBackColor(Color(6, 46, 81));

        if (settingbutton.coursorInbound(window))
            settingbutton.setBackColor(Color(2, 17, 29)); // Change button color to indicate hover
        else
            settingbutton.setBackColor(Color(6, 46, 81));

        while (window.pollEvent(Event)) {
            // Handle events for the next window
            if (Event.type == Event::Closed)
                window.close();

            // (e.g., window closing event, user interactions, etc.)
            if (Event.type == Event::MouseButtonPressed) {
                if (Event.mouseButton.button == Mouse::Left) {
                    if (playbutton.coursorInbound(window)) {
                        mainMenu(window);
                    }
                    else if (lbbutton.coursorInbound(window)) {
                        beforeLeaderboard(window);
                    }

                    else if (settingbutton.coursorInbound(window)) {
                        beforeLeaderboard(window);
                    }
                }
            }
        }

        window.clear();

        background.drawTo(window);

        playbutton.drawTo(window);
        lbbutton.drawTo(window);
        settingbutton.drawTo(window);
        window.display();
    }
}


