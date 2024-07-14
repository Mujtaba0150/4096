#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "classes.cpp"

using namespace std;
using namespace sf;

struct _4 {
    int arr[4][4] = { 0 };
    int prevArr[4][4] = { 0 };

    void highScore(const std::string& filename, const std::string& namedscoretxt, const std::string& name, int highscore) {
        std::fstream highscoreFile(filename, std::ios::in | std::ios::out);

        if (!highscoreFile.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        std::string line[5];
        int lineNumber = 1;

        while (lineNumber <= 5 && std::getline(highscoreFile, line[0])) {
            if (std::stoi(line[0]) == highscore)
                return;

            if (std::stoi(line[0]) < highscore)
                break;

            lineNumber++;
        }

        highscoreFile.seekg(0);

        for (int i = 0; i < 5; i++) {
            std::getline(highscoreFile, line[i]);
        }

        lineNumber--;

        if (lineNumber >= 1 && lineNumber <= 5)
            line[lineNumber] = std::to_string(highscore);

        highscoreFile.close();

        highscoreFile.open(filename, std::ios::out | std::ios::trunc);

        for (int i = 0; i < 5; i++) {
            highscoreFile << line[i] << std::endl;
        }
        highscoreFile.close();

        std::fstream namedHighscoreFile(namedscoretxt, std::ios::in); // Use std:: before ios

        if (!namedHighscoreFile.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        namedHighscoreFile.seekp(0);
        for (int i = 0; i < 5; i++) {
            line[i].clear(); // Clear the contents of the string
        }

        for (int i = 0; i < 5; i++) {
            getline(namedHighscoreFile, line[i]);
        }

        namedHighscoreFile.close();

        namedHighscoreFile.open(namedscoretxt, std::ios::out | std::ios::trunc);

        namedHighscoreFile.seekp(0);
        namedHighscoreFile << std::fixed << std::setprecision(2); // Set formatting for floating-point numbers

        for (int i = 0; i < 5; i++) {
            if (lineNumber != i)
                namedHighscoreFile << std::setw(20) << line[i] << std::endl;
            else
                namedHighscoreFile << std::setw(20) << std::left << std::setw(20) << name << std::right << std::setw(10) << highscore << std::endl;
        }

        namedHighscoreFile.close();
    }

    int scorefunc(int base, int merged) {
        int power = 0;

        while (base * (pow(2, power)) <= merged) {
            if (base * (pow(2, power)) == merged)
                return 2 * (pow(2, power));
            power++;
        }

        // Assuming the condition is always true
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
    void random1(int n, int multi) {
        while (true) {
            int r = rand() % n;
            int c = rand() % n;
            if (arr[r][c] == 0) {
                arr[r][c] = multi;
                break;
            }
        }
    }
    void mergeTilesud(int n, int multi, int& scoreValue) {
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
    void mergeTilesrl(int n, int multi, int& scoreValue) {
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
        mergeTilesud(n, multi, scoreValue);
        moveTilesUp(n);
        if (boardChanged(n)) {
            random1(n, multi);
        }
    }
    void leftArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesLeft(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesLeft(n);
        if (boardChanged(n)) {
            random1(n, multi);
        }
    }
    void rightArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesRight(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesRight(n);
        if (boardChanged(n)) {
            random1(n, multi);
        }
    }
    void downArrow(int n, int multi, int& scoreValue) {
        copyBoard(n);
        moveTilesDown(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesDown(n);
        if (boardChanged(n)) {
            random1(n, multi);
        }
    }
    Color tileColor4x4(int r, int c, int multi) {
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
            return Color(4, 36, 68);
        else if (arr[r][c] == multi * pow(2, 10))
            return Color(16, 20, 52);
        else
            return Color(212, 220, 220);
    }

    string boardValues(int gridValue) {

        if (gridValue != 0)
            return to_string(gridValue);
        else
            return "";
    }

    bool board(RenderWindow& window, string username, int multi) {

        ifstream file("leaderboards/leaderboard4x4.txt");
        string highscore;
        getline(file, highscore);

        file.close();

        srand(time(0));

        int r = rand() % 4;
        int c = rand() % 4;

        bool isGameover = false;
        bool runHighscore = false;
        int scoreValue = 0;

        arr[r][c] = multi;
        window.setFramerateLimit(60);

        Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
        Button name("4096", Vector2f(150, 100), 50, Color::Transparent, Color::Black, 6);
        Button boardbackground(" ", Vector2f(395, 440), 90, Color(8, 24, 56), Color::Black);
        Button back("Main Menu", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
        Button newgame("New Game", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
        Button score(to_string(scoreValue), Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
        Button best(highscore, Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);

        std::vector<std::vector<Button>> buttons;
        buttons.resize(4, std::vector<Button>(4, Button("", Vector2f(0, 0), 0, Color::Transparent, Color::Transparent)));

        // Initialize each button in the vector
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                buttons[i][j] = Button(
                    boardValues(arr[i][j]),
                    Vector2f(90, 100),
                    30,
                    tileColor4x4(i, j, multi),
                    Color::White,
                    16.0f
                );
            }
        }

        Font font;
        font.loadFromFile("LEMONMILK.otf");
        gameOver.setFont(font);
        name.setFont(font);
        boardbackground.setFont(font);
        back.setFont(font);
        newgame.setFont(font);
        score.setFont(font);
        best.setFont(font);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                buttons[i][j].setFont(font);
            }
        }

        // Assigning the positions...
        gameOver.setPosition(Vector2f(200, 200));
        boardbackground.setPosition(Vector2f(370, 200));
        back.setPosition(Vector2f(560, 150));
        name.setPosition(Vector2f(370, 70));
        newgame.setPosition(Vector2f(666, 150));
        score.setPosition(Vector2f(566, 50));
        best.setPosition(Vector2f(672, 50));

        for (int i = 0, x = 378, y = 210; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                buttons[i][j].setPosition(Vector2f(x, y));

                if (j == 3) {
                    x = 378, y += 106;
                }
                else
                    x += 96;
            }
        }
        while (window.isOpen()) {
            Event event; // Making an object "event" of the Event class
            window.clear();

            while (window.pollEvent(event)) // Loop to manage when something changes in the console
            {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        buttons[i][j].setText(boardValues(arr[i][j]));
                        buttons[i][j].setBackColor(tileColor4x4(i, j, multi));
                    }
                }
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
                {
                    if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                    {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (back.buttonClicked(window)) // Using self defined function to check if the button was clicked
                        {
                            return false;
                        }
                        else if (newgame.buttonClicked(window)) // Using self defined function to check if the button was clicked
                        {
                            return true;
                        }
                    }
                }

                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                        upArrow(4, multi, scoreValue);
                        if (isGameOver(4)) {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                        downArrow(4, multi, scoreValue);
                        Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                        if (isGameOver(4)) {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                        leftArrow(4, multi, scoreValue);
                        if (isGameOver(4)) {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                        rightArrow(4, multi, scoreValue);
                        if (isGameOver(4)) {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                }

                window.clear(Color::White);
                name.drawTo(window);
                boardbackground.drawTo(window);
                back.drawTo(window);
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        buttons[i][j].drawTo(window);
                    }
                }
                back.drawTo(window);
                newgame.drawTo(window);
                score.drawTo(window);
                best.drawTo(window);

                if (isGameover) {
                    gameOver.drawTo(window);
                }
                if (runHighscore) {
                    highScore("leaderboards/leaderboard4x4.txt", "leaderboards/namedLeaderboard4x4.txt", username, scoreValue);
                    runHighscore = false;
                }
                window.display();
            }
        }
        return false;
    }
};