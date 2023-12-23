#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

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
    void leftalign(sf::Vector2f pos, float textOffset) {
        button.setPosition(pos);

        float xPos = pos.x + textOffset; // Set the x-position with the offset
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);

    }
private:
    sf::RectangleShape button;
    sf::Text text;
    float offset;
};

int arr[][];
int prevArr[][];

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
        line[i].clear();  // Clear the contents of the string
    }

    for (int i = 0; i < 5; i++) {
        getline(namedHighscoreFile, line[i]);
    }

    namedHighscoreFile.close();

    namedHighscoreFile.open(namedscoretxt, std::ios::out | std::ios::trunc);

    namedHighscoreFile.seekp(0);
    namedHighscoreFile << std::fixed << std::setprecision(2);  // Set formatting for floating-point numbers

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
            if (arr[j][i] == arr[j + 1][i]) {
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
int calculateFontSize(int value) {
    // Define a base font size
    int baseFontSize = 50;
    // Calculate a dynamic font size based on the value
    int fontSize = baseFontSize - log2(value + 1) * 2; // Adjust the multiplication factor for your preference
    // Ensure the font size doesn't become too small
    if (fontSize < 15) {
        fontSize = 15; // Set a minimum font size to maintain readability
    }
    return fontSize;
}

string boardValues(int gridValue) {

    if (gridValue != 0)
        return to_string(gridValue);
    else
        return "";
}
Color tileColor8x8(int(*arr[]), int r, int c, int multi) {

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