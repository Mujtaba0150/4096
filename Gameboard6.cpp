#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include<iomanip>

using namespace std;
using namespace sf;
VideoMode screenSize = VideoMode::getDesktopMode();
RenderWindow window(screenSize, "Game Board");


int arr[6][6] = {0};
int prevArr[6][6] = { }; // Temporary copy of the board



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
bool isGameOver() {
    // Check if the board is entirely filled
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (arr[i][j] == 0) {
                return false; // If any empty cell found, the game is not over
            }
        }
    }

    // Check if any adjacent elements in the same row/column are the same
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
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
void copyBoard() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            prevArr[i][j] = arr[i][j];
        }
    }
}

// Function to check if the board has changed after movement
bool boardChanged() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (prevArr[i][j] != arr[i][j]) {
                return true; // Board has changed
            }
        }
    }
    return false; // Board remains the same
}
void random1() {
    while (true) {
        int r = rand() % 4;
        int c = rand() % 4;

        if (arr[r][c] == 0) {
            arr[r][c] = 2;
            break;
        }
    }
}

void mergeTilesud() {
    for (int c = 0; c < 6; ++c) {
        for (int r = 0; r < 6 - 1; ++r) {
            if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c]) {
                arr[r][c] *= 2;
                arr[r + 1][c] = 0;
            }
        }
    }
}


void mergeTilesrl() {
    for (int r = 0; r < 6; ++r) {
        for (int c = 0; c < 6 - 1; ++c) {
            if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1]) {
                arr[r][c] *= 2;
                arr[r][c + 1] = 0;
            }
        }
    }
}



void moveTilesRight() {
    for (int r = 0; r < 6; r++) {
        int column = 5;
        for (int c = 5; c >= 0; c--) {
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

void moveTilesLeft() {

    for (int r = 0; r < 6; ++r) {
        int column = 0;
        for (int c = 0; c < 6; c++) {
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
void moveTilesUp() {

    for (int c = 0; c < 6; c++) {
        int row = 0;
        for (int r = 0; r < 6; r++) {
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
void moveTilesDown() {

    for (int c = 0; c < 6; c++) {
        int row = 5;
        for (int r = 5; r >= 0; r--) {
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


void upArrow() {
    copyBoard();
    moveTilesUp();
    mergeTilesud();
    moveTilesUp();

    if (boardChanged()) {
        random1();
    }
    isGameOver();
}

void leftArrow() {
    copyBoard();
    moveTilesLeft();
    mergeTilesrl();
    moveTilesLeft();
    if (boardChanged()) {
        random1();
    }
    isGameOver();
}

void rightArrow() {
    copyBoard();
    moveTilesRight();
    mergeTilesrl();
    moveTilesRight();
    if (boardChanged()) {
        random1();
    }
    isGameOver();
}

void downArrow() {
    copyBoard();
    moveTilesDown();
    mergeTilesud();
    moveTilesDown();
    if (boardChanged()) {
        random1();
    }
    isGameOver();
}

Color tileColor(int r, int c, int n) {

    if (arr[r][c] == n * pow(2, 0))
        return Color(156, 132, 212);

    else if (arr[r][c] == n * pow(2, 1))
        return Color(132, 108, 188);

    else if (arr[r][c] == n * pow(2, 2))
        return Color(124, 100, 172);

    else if (arr[r][c] == n * pow(2, 3))
        return Color(116, 92, 156);

    else if (arr[r][c] == n * pow(2, 4))
        return Color(92, 76, 164);

    else if (arr[r][c] == n * pow(2, 5))
        return Color(84, 68, 148);

    else if (arr[r][c] == n * pow(2, 6))
        return Color(76, 60, 116);

    else if (arr[r][c] == n * pow(2, 7))
        return Color(60, 52, 124);

    else if (arr[r][c] == n * pow(2, 8))
        return Color(52, 44, 108);

    else if (arr[r][c] == n * pow(2, 9))
        return Color(36, 28, 100);

    else if (arr[r][c] == n * pow(2, 10))
        return Color(36, 20, 84);
    else
        return Color(204, 196, 228);


}
int calculateFontSize(int value) {
    // Define a base font size
    int baseFontSize = 50;

    // Calculate a dynamic font size based on the value
    int fontSize = baseFontSize - log2(value + 1) * 3; // Adjust the multiplication factor for your preference

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

int main() {
    srand(time(0));
    
    bool gameover = false;
    int r = rand() % 4;
    int c = rand() % 4;

    arr[r][c] = 2;
    window.setFramerateLimit(60);


    while (window.isOpen()) {
        Event event; // Making an object "event" of the Event class
        window.clear();

        while (window.pollEvent(event)) // Loop to manage when something changes in the console
        {


            Button name("2048", Vector2f(150, 100), 50, Color::Transparent, Color::Black, 6);
            Button boardbackground(" ", Vector2f(395, 465), 90, Color(16, 8, 56), Color::Black);
            Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
            Button b1(boardValues(arr[0][0]), Vector2f(60, 70), calculateFontSize(arr[0][0]), tileColor(0, 0, 2), Color::Black, 16.0f);
            Button b2(boardValues(arr[0][1]), Vector2f(60, 70), calculateFontSize(arr[0][1]), tileColor(0, 1, 2), Color::Black, 16.0f);
            Button b3(boardValues(arr[0][2]), Vector2f(60, 70), calculateFontSize(arr[0][2]), tileColor(0, 2, 2), Color::Black, 16.0f);
            Button b4(boardValues(arr[0][3]), Vector2f(60, 70), calculateFontSize(arr[0][3]), tileColor(0, 3, 2), Color::Black, 16.0f);
            Button b5(boardValues(arr[0][4]), Vector2f(60, 70), calculateFontSize(arr[0][4]), tileColor(0, 4, 2), Color::Black, 16.0f);
            Button b6(boardValues(arr[0][5]), Vector2f(60, 70), calculateFontSize(arr[0][5]), tileColor(0, 5, 2), Color::Black, 16.0f);
            //Row 2
            Button b7(boardValues(arr[1][0]), Vector2f(60, 70), calculateFontSize(arr[1][0]), tileColor(1, 0, 2), Color::Black, 16.0f);
            Button b8(boardValues(arr[1][1]), Vector2f(60, 70), calculateFontSize(arr[1][1]), tileColor(1, 1, 2), Color::Black, 16.0f);
            Button b9(boardValues(arr[1][2]), Vector2f(60, 70), calculateFontSize(arr[1][2]), tileColor(1, 2, 2), Color::Black, 16.0f);
            Button b10(boardValues(arr[1][3]), Vector2f(60, 70), calculateFontSize(arr[1][3]), tileColor(1, 3, 2), Color::Black, 16.0f);
            Button b11(boardValues(arr[1][4]), Vector2f(60, 70), calculateFontSize(arr[1][4]), tileColor(1, 4, 2), Color::Black, 16.0f);
            Button b12(boardValues(arr[1][5]), Vector2f(60, 70), calculateFontSize(arr[1][5]), tileColor(1, 5, 2), Color::Black, 16.0f);
            //Row 3
            Button b13(boardValues(arr[2][0]), Vector2f(60, 70), calculateFontSize(arr[2][0]), tileColor(2, 0, 2), Color::Black, 16.0f);
            Button b14(boardValues(arr[2][1]), Vector2f(60, 70), calculateFontSize(arr[2][1]), tileColor(2, 1, 2), Color::Black, 16.0f);
            Button b15(boardValues(arr[2][2]), Vector2f(60, 70), calculateFontSize(arr[2][2]), tileColor(2, 2, 2), Color::Black, 16.0f);
            Button b16(boardValues(arr[2][3]), Vector2f(60, 70), calculateFontSize(arr[2][3]), tileColor(2, 3, 2), Color::Black, 16.0f);
            Button b17(boardValues(arr[2][4]), Vector2f(60, 70), calculateFontSize(arr[2][4]), tileColor(2, 4, 2), Color::Black, 16.0f);
            Button b18(boardValues(arr[2][5]), Vector2f(60, 70), calculateFontSize(arr[2][5]), tileColor(2, 5, 2), Color::Black, 16.0f);
            //Row 4
            Button b19(boardValues(arr[3][0]), Vector2f(60, 70), calculateFontSize(arr[3][0]), tileColor(3, 0, 2), Color::Black, 16.0f);
            Button b20(boardValues(arr[3][1]), Vector2f(60, 70), calculateFontSize(arr[3][1]), tileColor(3, 1, 2), Color::Black, 16.0f);
            Button b21(boardValues(arr[3][2]), Vector2f(60, 70), calculateFontSize(arr[3][2]), tileColor(3, 2, 2), Color::Black, 16.0f);
            Button b22(boardValues(arr[3][3]), Vector2f(60, 70), calculateFontSize(arr[3][3]), tileColor(3, 3, 2), Color::Black, 16.0f);
            Button b23(boardValues(arr[3][4]), Vector2f(60, 70), calculateFontSize(arr[3][4]), tileColor(3, 4, 2), Color::Black, 16.0f);
            Button b24(boardValues(arr[3][5]), Vector2f(60, 70), calculateFontSize(arr[3][5]), tileColor(3, 5, 2), Color::Black, 16.0f);
            //Row 5
            Button b25(boardValues(arr[4][0]), Vector2f(60, 70), calculateFontSize(arr[4][0]), tileColor(4, 0, 2), Color::Black, 16.0f);
            Button b26(boardValues(arr[4][1]), Vector2f(60, 70), calculateFontSize(arr[4][1]), tileColor(4, 1, 2), Color::Black, 16.0f);
            Button b27(boardValues(arr[4][2]), Vector2f(60, 70), calculateFontSize(arr[4][2]), tileColor(4, 2, 2), Color::Black, 16.0f);
            Button b28(boardValues(arr[4][3]), Vector2f(60, 70), calculateFontSize(arr[4][3]), tileColor(4, 3, 2), Color::Black, 16.0f);
            Button b29(boardValues(arr[4][4]), Vector2f(60, 70), calculateFontSize(arr[4][4]), tileColor(4, 4, 2), Color::Black, 16.0f);
            Button b30(boardValues(arr[4][5]), Vector2f(60, 70), calculateFontSize(arr[4][5]), tileColor(4, 5, 2), Color::Black, 16.0f);
            //Row 6
            Button b31(boardValues(arr[5][0]), Vector2f(60, 70), calculateFontSize(arr[5][0]), tileColor(5, 0, 2), Color::Black, 16.0f);
            Button b32(boardValues(arr[5][1]), Vector2f(60, 70), calculateFontSize(arr[5][1]), tileColor(5, 1, 2), Color::Black, 16.0f);
            Button b33(boardValues(arr[5][2]), Vector2f(60, 70), calculateFontSize(arr[5][2]), tileColor(5, 2, 2), Color::Black, 16.0f);
            Button b34(boardValues(arr[5][3]), Vector2f(60, 70), calculateFontSize(arr[5][3]), tileColor(5, 3, 2), Color::Black, 16.0f);
            Button b35(boardValues(arr[5][4]), Vector2f(60, 70), calculateFontSize(arr[5][4]), tileColor(5, 4, 2), Color::Black, 16.0f);
            Button b36(boardValues(arr[5][5]), Vector2f(60, 70), calculateFontSize(arr[5][5]), tileColor(5, 5, 2), Color::Black, 16.0f);


            Button newgame("New Game", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
            Button score("Score\n2334", Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
            Button best("Best\n 2356", Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);

            Font font;
            font.loadFromFile("LEMONMILK.otf");
            name.setFont(font);
            gameOver.setFont(font);
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
            b17.setFont(font);
            b18.setFont(font);
            b19.setFont(font);
            b20.setFont(font);
            b21.setFont(font);
            b22.setFont(font);
            b23.setFont(font);
            b24.setFont(font);
            b25.setFont(font);
            b26.setFont(font);
            b27.setFont(font);
            b28.setFont(font);
            b29.setFont(font);
            b30.setFont(font);
            b31.setFont(font);
            b32.setFont(font);
            b33.setFont(font);
            b34.setFont(font);
            b35.setFont(font);
            b36.setFont(font);


            newgame.setFont(font);
            score.setFont(font);
            best.setFont(font);
            gameOver.setPosition(Vector2f(200, 200));

            // Assigning the positions...
            boardbackground.setPosition(Vector2f(370, 200));
            name.setPosition(Vector2f(370, 70));
            //Row 1
            b1.setPosition(Vector2f(378, 210));
            b2.setPosition(Vector2f(442, 210));
            b3.setPosition(Vector2f(506, 210));
            b4.setPosition(Vector2f(570, 210));
            b5.setPosition(Vector2f(634, 210));
            b6.setPosition(Vector2f(698, 210));
            //Row 2
            b7.setPosition(Vector2f(378, 285));
            b8.setPosition(Vector2f(442, 285));
            b9.setPosition(Vector2f(506, 285));
            b10.setPosition(Vector2f(570, 285));
            b11.setPosition(Vector2f(634, 285));
            b12.setPosition(Vector2f(698, 285));
            //Row 3
            b13.setPosition(Vector2f(378, 360));
            b14.setPosition(Vector2f(442, 360));
            b15.setPosition(Vector2f(506, 360));
            b16.setPosition(Vector2f(570, 360));
            b17.setPosition(Vector2f(634, 360));
            b18.setPosition(Vector2f(698, 360));
            //Row 4
            b19.setPosition(Vector2f(378, 435));
            b20.setPosition(Vector2f(442, 435));
            b21.setPosition(Vector2f(506, 435));
            b22.setPosition(Vector2f(570, 435));
            b23.setPosition(Vector2f(634, 435));
            b24.setPosition(Vector2f(698, 435));
            //Row 5
            b25.setPosition(Vector2f(378, 510));
            b26.setPosition(Vector2f(442, 510));
            b27.setPosition(Vector2f(506, 510));
            b28.setPosition(Vector2f(570, 510));
            b29.setPosition(Vector2f(634, 510));
            b30.setPosition(Vector2f(698, 510));
            //Row 6
            b31.setPosition(Vector2f(378, 585));
            b32.setPosition(Vector2f(442, 585));
            b33.setPosition(Vector2f(506, 585));
            b34.setPosition(Vector2f(570, 585));
            b35.setPosition(Vector2f(634, 585));
            b36.setPosition(Vector2f(698, 585));

            newgame.setPosition(Vector2f(666, 150));
            score.setPosition(Vector2f(566, 50));
            best.setPosition(Vector2f(672, 50));
            if (event.type == Event::Closed) {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
            {

                if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                {

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                    if (name.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {

                        window.close(); // Closes the window
                    }
                }
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                    upArrow();
                    if (isGameOver()) {
                        gameover = true;
                    }
                }
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                    downArrow();
                    Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                    if (isGameOver()) {
                        gameover = true;
                    }
                }
                else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                    leftArrow();
                    if (isGameOver()) {
                        gameover = true;
                    }
                }
                else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                    rightArrow();
                    if (isGameOver()) {
                        gameover = true;
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
            b17.drawTo(window);
            b18.drawTo(window);
            b19.drawTo(window);
            b20.drawTo(window);
            b21.drawTo(window);
            b22.drawTo(window);
            b23.drawTo(window);
            b24.drawTo(window);
            b25.drawTo(window);
            b26.drawTo(window);
            b27.drawTo(window);
            b28.drawTo(window);
            b29.drawTo(window);
            b30.drawTo(window);
            b31.drawTo(window);
            b32.drawTo(window);
            b33.drawTo(window);
            b34.drawTo(window);
            b35.drawTo(window);
            b36.drawTo(window);
            newgame.drawTo(window);
            score.drawTo(window);
            best.drawTo(window);
            if (gameover) {
                gameOver.drawTo(window);
            }
            window.display();
        }
    }
    return 0;
}
