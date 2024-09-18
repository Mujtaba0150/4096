#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <unistd.h>
#include "classes.cpp"

using namespace std;
using namespace sf;

struct gameboard {
    gameboard(int i, string file) {
        size = i;
        fileName = file;
    }

    std::vector<std::vector<int>> arr;
    std::vector<std::vector<int>> prevArr;

    bool replaceLine(const std::string& filename, int lineNumber, const std::string& newLine) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening input file: " << filename << std::endl;
            return false;
        }

        std::vector<std::string> lines;
        std::string line;
        int currentLineNumber = 0;

        // Read all lines from the file into a vector
        while (std::getline(inFile, line)) {
            ++currentLineNumber;
            if (currentLineNumber == lineNumber) {
                lines.push_back(newLine); // Replace the line at lineNumber with newLine
            }
            else {
                lines.push_back(line); // Keep the original line
            }
        }

        inFile.close();

        // Write the modified content back to the file
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error opening output file: " << filename << std::endl;
            return false;
        }

        for (const auto& l : lines) {
            outFile << l << std::endl;
        }

        outFile.close();

        return true;
    }

    void highScore(const std::string& fileName, const std::string& name, int score) {
        string highscore;
        int lineNumber = 0;
        ifstream file(fileName);
        if (file.good()) {
            file.seekg(0, ios::beg);
            if (file.is_open()) {
                for (int i = 1; i <= 5; i++) {
                    getline(file, highscore);

                    if (stoi(highscore) <= score) {
                        lineNumber = i;
                        break;
                    }
                }
                if (lineNumber) {
                    replaceLine(fileName, lineNumber, to_string(score));
                    replaceLine(fileName, lineNumber + 6, to_string(score));
                }
            }
            else
                std::cerr << "Unable to open file for writing: " << fileName << std::endl;
        }
        else {
            file.close();
            std::ofstream outfile(fileName);
            if (outfile.is_open()) {
                outfile << score << endl;
                outfile << "0" << endl << "0" << endl << "0" << endl << "0" << endl << endl;
                outfile << name;
                outfile.close();
            }
        }
    }

    int scorefunc(int base, int merged) {
        int power = 0;

        while (base * (pow(2, power)) <= merged) {
            if (base * (pow(2, power)) == merged)
                return 2 * (pow(2, power));
            power++;
        }

        return 0;
    }

    bool isGameOver(int n) {
        // Check if the board is entirely filled
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (arr[i][j] == 0) {
                    return false; // If any empty cell found, the game is not over
                }
            }
        }

        // Check if any adjacent elements in the same row/column are the same
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                // Check row-wise
                if (arr[i][j] == arr[i][j + 1]) {
                    return false; // If any adjacent elements are the same, the game is not over
                }
                // Check column-wise
                if (arr[j][i] == arr[j + 1][i])

                {
                    return false; // If any adjacent elements are the same, the game is not over
                }
            }
        }

        // If no empty cells and no adjacent elements found, the game is over
        return true;
    }

    // Function to copy the current board to prevArr
    void copyBoard(int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                prevArr[i][j] = arr[i][j];
            }
        }
    }
    // Function to check if the board has changed after movement
    bool boardChanged(int n) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (prevArr[i][j] != arr[i][j]) {
                    return true; // Board has changed
                }
            }
        }
        return false; // Board remains the same
    }
    void generateRandom(int n, int multi) {
        while (true) {
            int r = rand() % n;
            int c = rand() % n;
            int num = rand() % 2 ? multi : multi * 2;
            if (arr[r][c] == 0) {
                arr[r][c] = num;
                break;
            }
        }
    }
    void mergeTilesUp(int n, int multi, int& scoreValue) {
        for (int c = 0; c < n; ++c) {
            for (int r = 0; r < n - 1; ++r) {
                if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c]) {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r + 1][c] = 0;
                }
            }
        }
    }
    void mergeTilesDown(int n, int multi, int& scoreValue) {
        for (int c = n - 1; c >= 0; --c) {
            for (int r = n - 1; r >= 1; --r) {
                if (arr[r][c] != 0 && arr[r][c] == arr[r - 1][c]) {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r - 1][c] = 0;
                }
            }
        }
    }
    void mergeTilesLeft(int n, int multi, int& scoreValue) {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n - 1; ++c) {
                if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1]) {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r][c + 1] = 0;
                }
            }
        }
    }
    void mergeTilesRight(int n, int multi, int& scoreValue) {
        for (int r = n - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 1; --c) {
                if (arr[r][c] != 0 && arr[r][c] == arr[r][c - 1]) {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r][c - 1] = 0;
                }
            }
        }
    }
    void moveTilesRight(int n) {
        for (int r = 0; r < n; r++) {
            int column = n - 1;
            for (int c = n - 1; c >= 0; c--) {
                if (arr[r][c] != 0) {
                    arr[r][column] = arr[r][c];
                    if (column != c) {
                        arr[r][c] = 0;
                    }
                    column--;
                }
            }
        }
    }
    void moveTilesLeft(int n) {
        for (int r = 0; r < n; ++r) {
            int column = 0;
            for (int c = 0; c < n; c++) {
                if (arr[r][c] != 0) {
                    arr[r][column] = arr[r][c];
                    if (column != c) {
                        arr[r][c] = 0;
                    }
                    column++;
                }
            }
        }
    }
    void moveTilesUp(int n) {
        for (int c = 0; c < n; c++) {
            int row = 0;
            for (int r = 0; r < n; r++) {
                if (arr[r][c] != 0) {
                    arr[row][c] = arr[r][c];
                    if (row != r) {
                        arr[r][c] = 0;
                    };
                    row++;
                }
            }
        }
    }
    void moveTilesDown(int n) {
        for (int c = 0; c < n; c++) {
            int row = n - 1;
            for (int r = n - 1; r >= 0; r--) {
                if (arr[r][c] != 0) {
                    arr[row][c] = arr[r][c];
                    if (row != r) {
                        arr[r][c] = 0;
                    }
                    row--;
                }
            }
        }
    }
    void upArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesUp(n);
        mergeTilesUp(n, multi, scoreValue);
        moveTilesUp(n);
        if (boardChanged(n)) {
            generateRandom(n, multi);
        }
    }
    void leftArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesLeft(n);
        mergeTilesLeft(n, multi, scoreValue);
        moveTilesLeft(n);
        if (boardChanged(n)) {
            generateRandom(n, multi);
        }
    }
    void rightArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesRight(n);
        mergeTilesRight(n, multi, scoreValue);
        moveTilesRight(n);
        if (boardChanged(n)) {
            generateRandom(n, multi);
        }
    }
    void downArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesDown(n);
        mergeTilesDown(n, multi, scoreValue);
        moveTilesDown(n);
        if (boardChanged(n)) {
            generateRandom(n, multi);
        }
    }
    Color tileColor(int size, int r, int c, int multi) {
        if (size == 4) {
            if (arr[r][c] == multi * pow(2, 0))
                return Color(158, 174, 190);
            else if (arr[r][c] == multi * pow(2, 1))
                return Color(136, 160, 176);
            else if (arr[r][c] == multi * pow(2, 2))
                return Color(100, 124, 148);
            else if (arr[r][c] == multi * pow(2, 3))
                return Color(84, 108, 132);
            else if (arr[r][c] == multi * pow(2, 4))
                return Color(68, 100, 124);
            else if (arr[r][c] == multi * pow(2, 5))
                return Color(60, 84, 108);
            else if (arr[r][c] == multi * pow(2, 6))
                return Color(36, 68, 100);
            else if (arr[r][c] == multi * pow(2, 7))
                return Color(28, 60, 84);
            else if (arr[r][c] == multi * pow(2, 8))
                return Color(20, 44, 68);
            else if (arr[r][c] == multi * pow(2, 9))
                return Color(size, 36, 68);
            else if (arr[r][c] == multi * pow(2, 10))
                return Color(16, 20, 52);
            else
                return Color(212, 220, 220);
        }
        else if (size == 6) {
            if (arr[r][c] == multi * pow(2, 0))
                return Color(156, 132, 212);

            else if (arr[r][c] == multi * pow(2, 1))
                return Color(132, 108, 188);

            else if (arr[r][c] == multi * pow(2, 2))
                return Color(124, 100, 172);

            else if (arr[r][c] == multi * pow(2, 3))
                return Color(116, 92, 156);

            else if (arr[r][c] == multi * pow(2, 4))
                return Color(92, 76, 164);

            else if (arr[r][c] == multi * pow(2, 5))
                return Color(84, 68, 148);

            else if (arr[r][c] == multi * pow(2, 6))
                return Color(76, 60, 116);

            else if (arr[r][c] == multi * pow(2, 7))
                return Color(60, 52, 124);

            else if (arr[r][c] == multi * pow(2, 8))
                return Color(52, 44, 108);

            else if (arr[r][c] == multi * pow(2, 9))
                return Color(36, 28, 100);

            else if (arr[r][c] == multi * pow(2, 10))
                return Color(36, 20, 84);
            else
                return Color(204, 196, 228);
        }
        else if (size == 8) {
            if (arr[r][c] == multi * pow(2, 0))
                return Color(208, 112, 104);

            else if (arr[r][c] == multi * pow(2, 1))
                return Color(164, 84, 76);

            else if (arr[r][c] == multi * pow(2, 2))
                return Color(164, 68, 60);

            else if (arr[r][c] == multi * pow(2, 3))
                return Color(124, 68, 68);

            else if (arr[r][c] == multi * pow(2, 4))
                return Color(155, 36, 36);

            else if (arr[r][c] == multi * pow(2, 5))
                return Color(164, 4, 20);

            else if (arr[r][c] == multi * pow(2, 6))
                return Color(135, 44, 36);

            else if (arr[r][c] == multi * pow(2, 7))
                return Color(132, 20, 28);

            else if (arr[r][c] == multi * pow(2, 8))
                return Color(108, 28, 28);

            else if (arr[r][c] == multi * pow(2, 9))
                return Color(116, 4, 4);

            else if (arr[r][c] == multi * pow(2, 10))
                return Color(84, 28, 28);
            else
                return Color(228, 196, 196);
        }
    }

    string boardValues(int gridValue) {

        if (gridValue != 0)
            return to_string(gridValue);
        else
            return "";
    }

    Vector2f tileSize(int size) {
        if (size == 4)
            return Vector2f(8.5, 13.2);

        else if (size == 6)
            return Vector2f(5.5, 8.7);

        else if (size == 8)
            return Vector2f(4, 6.5);
    }

    Vector2f backgroundSize(int size) {
        if (size == 4)
            return Vector2f(37, 58);

        else if (size == 6)
            return Vector2f(37, 58);

        else if (size == 8)
            return Vector2f(36.4, 59);
    }

    // Vector2f backgroundPosition(int size) {
    //     if (size == 4)
    //         return Vector2f(50, 55);

    //     else if (size == 6)
    //         return Vector2f(50, 58);

    //     else if (size == 8)
    //         return Vector2f(50, 59);
    // }

    int gameOver(RenderWindow& window, const std::string& username, int scoreValue, int size, int multi) {
        // Save high score
        highScore(fileName, username, scoreValue);

        // Determine color based on grid size
        Color buttonColor;
        Color bg;
        switch (size) {
            case 4:
                bg = Color(36, 68, 100, 10);
                buttonColor = Color(16, 20, 52, 200);
                break;
            case 6:
                bg = Color(76, 60, 116, 10);
                buttonColor = Color(36, 20, 84, 200);
                break;
            case 8:
                bg = Color(135, 44, 36, 10);
                buttonColor = Color(84, 28, 28, 200);
                break;
            default:
                buttonColor = Color::White; // Default color if size is not matched
                break;
        }
        // Create and setup the buttons
        RectangleShape gameOverBackground(Vector2f(window.getSize().x, window.getSize().y));

        gameOverBackground.setFillColor(bg);

        gameOverBackground.setPosition(0, 0);

        Button gameOver(window, "GAME OVER", Vector2f(21, 15), 40, buttonColor, Color::White, 10, 5);
        Button playAgain(window, "Play Again", Vector2f(12, 7), 24, buttonColor, Color::White);
        Button mainMenu(window, "Main Menu", Vector2f(12, 7), 24, buttonColor, Color::White);


        Font font;
        font.loadFromFile("Baloo.ttf");
        gameOver.setFont(font);
        playAgain.setFont(font);
        mainMenu.setFont(font);

        gameOver.setPosition(window, Vector2f(50, 40));
        playAgain.setPosition(window, Vector2f(43, 55));
        mainMenu.setPosition(window, Vector2f(57, 55));

        // Display the game over screen
        while (true) {

            window.draw(gameOverBackground);
            gameOver.drawTo(window);
            playAgain.drawTo(window);
            mainMenu.drawTo(window);
            window.display();

            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    return 0;
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        if (gameOver.coursorInbound(window)) {
                            return 0;
                        }
                        else if (playAgain.coursorInbound(window)) {
                            return 1;
                        }
                        else if (mainMenu.coursorInbound(window)) {
                            return false;
                        }

                    }
                }
            }
        }
    }

    bool board(RenderWindow& window, string username, int multi, int lightTheme, int sfx) {

        ifstream file(fileName);
        string highscore;
        getline(file, highscore);

        file.close();

        arr.resize(size, std::vector<int>(size, 0));
        prevArr.resize(size, std::vector<int>(size, 0));

        srand(time(0));

        int r = rand() % size;
        int c = rand() % size;
        bool firstValue = true;
        bool isGameover = false;
        int scoreValue = 0;

        arr[r][c] = multi;
        window.setFramerateLimit(60);


        //Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
        Button name(window, "4096", Vector2f(15, 14), 50, Color::Transparent, Color::Black, 6);
        Button boardbackground(window, " ", backgroundSize(size), 90, Color(8, 24, 56), Color::Black);
        Button back(window, "Main Menu", Vector2f(9, 5), 24, Color(160, 82, 45), Color::White);
        Button newgame(window, "New Game", Vector2f(9, 5), 24, Color(160, 82, 45), Color::White);
        Button score(window, to_string(scoreValue), Vector2f(9, 7), 24, Color(160, 82, 45), Color::White);
        Button best(window, highscore, Vector2f(9, 7), 24, Color(160, 82, 45), Color::White);

        Picture background("4096 bg(light).png");
        if (!lightTheme) {
            background.SetTexture("4096 bg(dark).png");
        }

        background.setScale(window, Vector2f(51, 50));
        background.setPosition(window, Vector2f(0, 0));

        std::vector<std::vector<Button>> buttons;
        buttons.resize(size, std::vector<Button>(size, Button(window, "", Vector2f(0, 0), 0, Color::Transparent, Color::Transparent)));

        // Initialize each button in the vector
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                buttons[i][j] = Button(
                    window,
                    boardValues(arr[i][j]),
                    tileSize(size),
                    30,
                    tileColor(size, i, j, multi),
                    Color::White
                );
            }
        }

        Font font;
        font.loadFromFile("Baloo.ttf");
        //gameOver.setFont(font);
        name.setFont(font);
        boardbackground.setFont(font);
        back.setFont(font);
        newgame.setFont(font);
        score.setFont(font);
        best.setFont(font);

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                buttons[i][j].setFont(font);
            }
        }

        // Assigning the positions...
        //gameOver.setPosition(Vector2f(200, 200));
        boardbackground.setPosition(window, Vector2f(50, 58));
        back.setPosition(window, Vector2f(52, 25));
        name.setPosition(window, Vector2f(39, 20));
        newgame.setPosition(window, Vector2f(62, 25));
        score.setPosition(window, Vector2f(52, 15));
        best.setPosition(window, Vector2f(62, 15));

        float x = 0, y = 0;
        //! Need to make a function
        for (float i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                switch (size) {

                    case 4:
                        if (firstValue) {
                            x = 36.5, y = 37;
                            firstValue = false;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        else if (j == 3) {
                            x += 9;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                            x = 36.5, y += 14;
                        }
                        else if (j != 0) {
                            x += 9;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        else {
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        break;

                    case 6:
                        if (firstValue) {
                            x = 35, y = 34.4;
                            firstValue = false;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        else if (j == 5) {
                            x += 6;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                            x = 35, y += 9.5;
                        }
                        else if (j != 0) {
                            x += 6;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        else {
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        break;

                    case 8:
                        if (firstValue) {
                            x = 34.40, y = 32.50;
                            firstValue = false;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        else if (j == 7) {
                            x += 4.45;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                            x = 34.40, y += 7.30;
                        }
                        else if (j != 0) {
                            x += 4.45;
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        else {
                            buttons[i][j].setPosition(window, Vector2f(x, y));
                        }
                        break;

                    default:
                        break;
                }
            }
        }        while (window.isOpen()) {
            Event event; // Making an object "event" of the Event class

            while (window.pollEvent(event)) // Loop to manage when something changes in the console
            {
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        buttons[i][j].setText(boardValues(arr[i][j]));
                        buttons[i][j].setBackColor(tileColor(size, i, j, multi));
                    }
                }
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
                {
                    if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                    {
                        if (back.coursorInbound(window)) // Using self defined function to check if the button was clicked
                        {
                            return false;
                        }
                        else if (newgame.coursorInbound(window)) // Using self defined function to check if the button was clicked
                        {
                            return true;
                        }
                    }
                }

                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                        upArrow(size, multi, scoreValue);
                        score.setText(to_string(scoreValue));
                        if (isGameOver(size)) {
                            newGame = gameOver(window, username, scoreValue, size, multi); // Call gameOver function
                            return newGame; // End the game
                        }
                    }
                    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                        downArrow(size, multi, scoreValue);
                        score.setText(to_string(scoreValue));
                        if (isGameOver(size)) {
                            newGame = gameOver(window, username, scoreValue, size, multi); // Call gameOver function
                            return newGame; // End the game
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                        leftArrow(size, multi, scoreValue);
                        score.setText(to_string(scoreValue));
                        if (isGameOver(size)) {
                            newGame = gameOver(window, username, scoreValue, size, multi); // Call gameOver function
                            return newGame; // End the game
                        }
                    }
                    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                        rightArrow(size, multi, scoreValue);
                        score.setText(to_string(scoreValue));
                        if (isGameOver(size)) {
                            newGame = gameOver(window, username, scoreValue, size, multi); // Call gameOver function
                            return newGame; // End the game
                        }
                    }
                }
                window.clear();
                background.drawTo(window);

                name.drawTo(window);
                boardbackground.drawTo(window);
                back.drawTo(window);
                for (int i = 0; i < size; ++i) {
                    for (int j = 0; j < size; ++j) {
                        buttons[i][j].drawTo(window);
                    }
                }

                //window.clear();
                newgame.drawTo(window);
                score.drawTo(window);
                best.drawTo(window);

                window.display();

            }
        }
        return false;
    }

    private:
    string fileName;
    int size;
    bool newGame = false;
};