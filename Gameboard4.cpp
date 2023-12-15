#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
using namespace sf;
VideoMode screenSize = VideoMode::getDesktopMode();
RenderWindow window(screenSize, "Game Board");

int arr[4][4] = {0};
int prevArr[4][4] = {0}; // Temporary copy of the board

class Button
{
public:
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor, float offset = 1)
        : offset(offset)
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

        float xPos = pos.x + (button.getLocalBounds().width - text.getLocalBounds().width) / 2;
        float yPos = pos.y + (button.getLocalBounds().height - text.getLocalBounds().height) / 2;

        // Adjusts the vertical position by subtracting a specific offset (e.g., 5.0f)
        yPos -= offset; // You can adjust this offset as needed

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
    float offset;
};
void isGameOver()
{
    bool boardFilled = true;

    // Check if the board is entirely filled
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (arr[i][j] == 0)
            {
                boardFilled = false;
                break;
            }
        }
        if (!boardFilled)
        {
            break;
        }
    }

    if (boardFilled)
    {
        // Check if any adjacent elements in the same row/column are the same
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                // Check row-wise
                if (arr[i][j] == arr[i][j + 1])
                {
                    return;
                }
                // Check column-wise
                if (arr[j][i] == arr[j + 1][i])
                {
                    return;
                }
            }
        }

        // Display "GAME OVER" if no adjacent elements found in the same row/column
        while (window.isOpen())
        {
            Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
            gameOver.setPosition(Vector2f(200, 200));
            Font font;
            font.loadFromFile("LEMONMILK.otf");
            gameOver.setFont(font);
            gameOver.drawTo(window);
            window.display();
        }
    }
}

// Function to copy the current board to prevArr
void copyBoard()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            prevArr[i][j] = arr[i][j];
        }
    }
}

// Function to check if the board has changed after movement
bool boardChanged()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (prevArr[i][j] != arr[i][j])
            {
                return true; // Board has changed
            }
        }
    }
    return false; // Board remains the same
}
void random1()
{
    while (true)
    {
        int r = rand() % 4;
        int c = rand() % 4;

        if (arr[r][c] == 0)
        {
            arr[r][c] = 2;
            break;
        }
    }
}

void mergeTilesud()
{
    for (int c = 0; c < 4; ++c)
    {
        for (int r = 0; r < 4 - 1; ++r)
        {
            if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c])
            {
                arr[r][c] *= 2;
                arr[r + 1][c] = 0;
            }
        }
    }
}

void mergeTilesrl()
{
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4 - 1; ++c)
        {
            if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1])
            {
                arr[r][c] *= 2;
                arr[r][c + 1] = 0;
            }
        }
    }
}

void moveTilesRight()
{
    for (int r = 0; r < 4; r++)
    {
        int column = 3;
        for (int c = 3; c >= 0; c--)
        {
            if (arr[r][c] != 0)
            {
                arr[r][column] = arr[r][c];
                if (column != c)
                {
                    arr[r][c] = 0;
                }
                column--;
            }
        }
    }
}

void moveTilesLeft()
{

    for (int r = 0; r < 4; ++r)
    {
        int column = 0;
        for (int c = 0; c < 4; c++)
        {
            if (arr[r][c] != 0)
            {
                arr[r][column] = arr[r][c];
                if (column != c)
                {
                    arr[r][c] = 0;
                }
                column++;
            }
        }
    }
}
void moveTilesUp()
{

    for (int c = 0; c < 4; c++)
    {
        int row = 0;
        for (int r = 0; r < 4; r++)
        {
            if (arr[r][c] != 0)
            {
                arr[row][c] = arr[r][c];
                if (row != r)
                {
                    arr[r][c] = 0;
                };
                row++;
            }
        }
    }
}
void moveTilesDown()
{

    for (int c = 0; c < 4; c++)
    {
        int row = 3;
        for (int r = 3; r >= 0; r--)
        {
            if (arr[r][c] != 0)
            {
                arr[row][c] = arr[r][c];
                if (row != r)
                {
                    arr[r][c] = 0;
                }
                row--;
            }
        }
    }
}

void upArrow()
{
    copyBoard();
    moveTilesUp();
    mergeTilesud();
    moveTilesUp();

    if (boardChanged())
    {
        random1();
    }
    isGameOver();
}

void leftArrow()
{
    copyBoard();
    moveTilesLeft();
    mergeTilesrl();
    moveTilesLeft();
    if (boardChanged())
    {
        random1();
    }
    isGameOver();
}

void rightArrow()
{
    copyBoard();
    moveTilesRight();
    mergeTilesrl();
    moveTilesRight();
    if (boardChanged())
    {
        random1();
    }
    isGameOver();
}

void downArrow()
{
    copyBoard();
    moveTilesDown();
    mergeTilesud();
    moveTilesDown();
    if (boardChanged())
    {
        random1();
    }
    isGameOver();
}
Color tileColor(int r, int c, int n)
{

    if (arr[r][c] == n * pow(2, 0))
        return Color(158, 174, 190);

    else if (arr[r][c] == n * pow(2, 1))
        return Color(136, 160, 176);

    else if (arr[r][c] == n * pow(2, 2))
        return Color(100, 124, 148);

    else if (arr[r][c] == n * pow(2, 3))
        return Color(84, 108, 132);

    else if (arr[r][c] == n * pow(2, 4))
        return Color(68, 100, 124);

    else if (arr[r][c] == n * pow(2, 5))
        return Color(60, 84, 108);

    else if (arr[r][c] == n * pow(2, 6))
        return Color(36, 68, 100);

    else if (arr[r][c] == n * pow(2, 7))
        return Color(28, 60, 84);

    else if (arr[r][c] == n * pow(2, 8))
        return Color(20, 44, 68);

    else if (arr[r][c] == n * pow(2, 9))
        return Color(4, 36, 68);

    else if (arr[r][c] == n * pow(2, 10))
        return Color(16, 20, 52);
    else
        return Color(212, 220, 220);
}
int calculateFontSize(int value)
{
    // Define a base font size
    int baseFontSize = 50;

    // Calculate a dynamic font size based on the value
    int fontSize = baseFontSize - log2(value + 1) * 2; // Adjust the multiplication factor for your preference

    // Ensure the font size doesn't become too small
    if (fontSize < 15)
    {
        fontSize = 15; // Set a minimum font size to maintain readability
    }

    return fontSize;
}

int main()
{
    srand(time(0));

    int r = rand() % 4;
    int c = rand() % 4;

    arr[r][c] = 2;
    window.setFramerateLimit(60);

    // Assigning Variables.

    // Applying fonts...

    while (window.isOpen())
    {
        Event event; // Making an object "event" of the Event class
        window.clear();

        while (window.pollEvent(event)) // Loop to manage when something changes in the console
        {

            Button name("2048", Vector2f(150, 100), 50, Color::Transparent, Color::Black, 6);
            Button boardbackground(" ", Vector2f(395, 440), 90, Color(8, 24, 56), Color::Black);
            Button b1(to_string(arr[0][0]), Vector2f(90, 100), calculateFontSize(arr[0][0]), tileColor(0, 0, 2), Color::Black, 16.0f);
            Button b2(to_string(arr[0][1]), Vector2f(90, 100), calculateFontSize(arr[0][1]), tileColor(0, 1, 2), Color::Black, 16.0f);
            Button b3(to_string(arr[0][2]), Vector2f(90, 100), calculateFontSize(arr[0][2]), tileColor(0, 2, 2), Color::Black, 16.0f);
            Button b4(to_string(arr[0][3]), Vector2f(90, 100), calculateFontSize(arr[0][3]), tileColor(0, 3, 2), Color::Black, 16.0f);
            Button b5(to_string(arr[1][0]), Vector2f(90, 100), calculateFontSize(arr[1][0]), tileColor(1, 0, 2), Color::Black, 16.0f);
            Button b6(to_string(arr[1][1]), Vector2f(90, 100), calculateFontSize(arr[1][1]), tileColor(1, 1, 2), Color::Black, 16.0f);
            Button b7(to_string(arr[1][2]), Vector2f(90, 100), calculateFontSize(arr[1][2]), tileColor(1, 2, 2), Color::Black, 16.0f);
            Button b8(to_string(arr[1][3]), Vector2f(90, 100), calculateFontSize(arr[1][3]), tileColor(1, 3, 2), Color::Black, 16.0f);
            Button b9(to_string(arr[2][0]), Vector2f(90, 100), calculateFontSize(arr[2][0]), tileColor(2, 0, 2), Color::Black, 16.0f);
            Button b10(to_string(arr[2][1]), Vector2f(90, 100), calculateFontSize(arr[2][1]), tileColor(2, 1, 2), Color::Black, 16.0f);
            Button b11(to_string(arr[2][2]), Vector2f(90, 100), calculateFontSize(arr[2][2]), tileColor(2, 2, 2), Color::Black, 16.0f);
            Button b12(to_string(arr[2][3]), Vector2f(90, 100), calculateFontSize(arr[2][3]), tileColor(2, 3, 2), Color::Black, 16.0f);
            Button b13(to_string(arr[3][0]), Vector2f(90, 100), calculateFontSize(arr[3][0]), tileColor(3, 0, 2), Color::Black, 16.0f);
            Button b14(to_string(arr[3][1]), Vector2f(90, 100), calculateFontSize(arr[3][1]), tileColor(3, 1, 2), Color::Black, 16.0f);
            Button b15(to_string(arr[3][2]), Vector2f(90, 100), calculateFontSize(arr[3][2]), tileColor(3, 2, 2), Color::Black, 16.0f);
            Button b16(to_string(arr[3][3]), Vector2f(90, 100), calculateFontSize(arr[3][3]), tileColor(3, 3, 2), Color::Black, 16.0f);
            Button newgame("New Game", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
            Button score("Score\n2334", Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
            Button best("Best\n 2356", Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);

            Font font;
            font.loadFromFile("LEMONMILK.otf");
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

            // Assigning the positions...
            boardbackground.setPosition(Vector2f(370, 200));
            name.setPosition(Vector2f(370, 70));
            b1.setPosition(Vector2f(378, 210));
            b2.setPosition(Vector2f(474, 210));
            b3.setPosition(Vector2f(570, 210));
            b4.setPosition(Vector2f(666, 210));
            b5.setPosition(Vector2f(378, 316));
            b6.setPosition(Vector2f(474, 316));
            b7.setPosition(Vector2f(570, 316));
            b8.setPosition(Vector2f(666, 316));
            b9.setPosition(Vector2f(378, 422));
            b10.setPosition(Vector2f(474, 422));
            b11.setPosition(Vector2f(570, 422));
            b12.setPosition(Vector2f(666, 422));
            b13.setPosition(Vector2f(378, 528));
            b14.setPosition(Vector2f(474, 528));
            b15.setPosition(Vector2f(570, 528));
            b16.setPosition(Vector2f(666, 528));
            newgame.setPosition(Vector2f(666, 150));
            score.setPosition(Vector2f(566, 50));
            best.setPosition(Vector2f(672, 50));
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
            } // if (event.type == sf::Event::KeyPressed) {
            //     handleMovement(event.key.code);
            // }

            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    upArrow();
                }
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    downArrow();
                }
                else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    leftArrow();
                }
                else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    rightArrow();
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
    }
    return 0;
}
