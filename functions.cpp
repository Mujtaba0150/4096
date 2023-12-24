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

        float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
        float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }
    void leftalign(sf::Vector2f pos, float textOffset)
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

class Picture
{

public:
    Picture(std::string filePath)
    {
        texture.loadFromFile(filePath);
        sprite.setTexture(texture);
    }

    void setScale(sf::Vector2f scale)
    {

        sf::Vector2f Aspectratio(scale.x / texture.getSize().x, scale.y / texture.getSize().y);
        sprite.setScale(Aspectratio);
    }
    void setPosition(sf::Vector2f position)
    {

        sprite.setPosition(position);
    }
    void drawTo(sf::RenderWindow &window)
    {

        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};
void Leaderboard(RenderWindow &window, string file)
{
    string l1, l2, l3, l4, l5;
    ifstream leaderboard(file);
    if (leaderboard.is_open())
    {
        getline(leaderboard, l1);
        getline(leaderboard, l2);
        getline(leaderboard, l3);
        getline(leaderboard, l4);
        getline(leaderboard, l5);

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
    Button rank1(l1, Vector2f(505.8, 50), 24, Color(154, 197, 219), Color::White);
    Button rank2(l2, Vector2f(505.8, 50), 24, Color(238, 201, 0), Color::White);
    Button rank3(l3, Vector2f(505.8, 50), 24, Color(202, 202, 202), Color::White);
    Button rank4(l4, Vector2f(505.8, 50), 24, Color(185, 97, 30), Color::White);
    Button rank5(l5, Vector2f(505.8, 50), 24, Color(205, 127, 50), Color::White);
    Button back("BACK", Vector2f(100, 50), 24, Color::Blue, Color::White);

    // Making an object of the Font class called "font"
    Font font;

    // Loading the font for the button
    font.loadFromFile("LEMONMILK.otf");

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

                        return; // Closes the window
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

        window.display();
    }
}
// Gameboard 4x4
struct _4
{
    int arr[4][4] = {0};
    int prevArr[4][4] = {0};

    void highScore(const std::string &filename, const std::string &namedscoretxt, const std::string &name, int highscore)
    {
        std::fstream highscoreFile(filename, std::ios::in | std::ios::out);

        if (!highscoreFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        std::string line[5];
        int lineNumber = 1;

        while (lineNumber <= 5 && std::getline(highscoreFile, line[0]))
        {
            if (std::stoi(line[0]) == highscore)
                return;

            if (std::stoi(line[0]) < highscore)
                break;

            lineNumber++;
        }

        highscoreFile.seekg(0);

        for (int i = 0; i < 5; i++)
        {
            std::getline(highscoreFile, line[i]);
        }

        lineNumber--;

        if (lineNumber >= 1 && lineNumber <= 5)
            line[lineNumber] = std::to_string(highscore);

        highscoreFile.close();

        highscoreFile.open(filename, std::ios::out | std::ios::trunc);

        for (int i = 0; i < 5; i++)
        {
            highscoreFile << line[i] << std::endl;
        }
        highscoreFile.close();

        std::fstream namedHighscoreFile(namedscoretxt, std::ios::in); // Use std:: before ios

        if (!namedHighscoreFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        namedHighscoreFile.seekp(0);
        for (int i = 0; i < 5; i++)
        {
            line[i].clear(); // Clear the contents of the string
        }

        for (int i = 0; i < 5; i++)
        {
            getline(namedHighscoreFile, line[i]);
        }

        namedHighscoreFile.close();

        namedHighscoreFile.open(namedscoretxt, std::ios::out | std::ios::trunc);

        namedHighscoreFile.seekp(0);
        namedHighscoreFile << std::fixed << std::setprecision(2); // Set formatting for floating-point numbers

        for (int i = 0; i < 5; i++)
        {
            if (lineNumber != i)
                namedHighscoreFile << std::setw(20) << line[i] << std::endl;
            else
                namedHighscoreFile << std::setw(20) << std::left << std::setw(20) << name << std::right << std::setw(10) << highscore << std::endl;
        }

        namedHighscoreFile.close();
    }

    int scorefunc(int base, int merged)
    {
        int power = 0;

        while (base * (pow(2, power)) <= merged)
        {
            if (base * (pow(2, power)) == merged)
                return 2 * (pow(2, power));
            power++;
        }

        // Assuming the condition is always true
        return 0;
    }

    bool isGameOver(int n)
    {
        // Check if the board is entirely filled
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (arr[i][j] == 0)
                {
                    return false; // If any empty cell found, the game is not over
                }
            }
        }

        // Check if any adjacent elements in the same row/column are the same
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n - 1; ++j)
            {
                // Check row-wise
                if (arr[i][j] == arr[i][j + 1])
                {
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
    void copyBoard(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                prevArr[i][j] = arr[i][j];
            }
        }
    }
    // Function to check if the board has changed after movement
    bool boardChanged(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (prevArr[i][j] != arr[i][j])
                {
                    return true; // Board has changed
                }
            }
        }
        return false; // Board remains the same
    }
    void random1(int n, int multi)
    {
        while (true)
        {
            int r = rand() % n;
            int c = rand() % n;
            if (arr[r][c] == 0)
            {
                arr[r][c] = multi;
                break;
            }
        }
    }
    void mergeTilesud(int n, int multi, int &scoreValue)
    {
        for (int c = 0; c < n; ++c)
        {
            for (int r = 0; r < n - 1; ++r)
            {
                if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c])
                {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r + 1][c] = 0;
                }
            }
        }
    }
    void mergeTilesrl(int n, int multi, int &scoreValue)
    {
        for (int r = 0; r < n; ++r)
        {
            for (int c = 0; c < n - 1; ++c)
            {
                if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1])
                {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r][c + 1] = 0;
                }
            }
        }
    }
    void moveTilesRight(int n)
    {
        for (int r = 0; r < n; r++)
        {
            int column = n - 1;
            for (int c = n - 1; c >= 0; c--)
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
    void moveTilesLeft(int n)
    {
        for (int r = 0; r < n; ++r)
        {
            int column = 0;
            for (int c = 0; c < n; c++)
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
    void moveTilesUp(int n)
    {
        for (int c = 0; c < n; c++)
        {
            int row = 0;
            for (int r = 0; r < n; r++)
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
    void moveTilesDown(int n)
    {
        for (int c = 0; c < n; c++)
        {
            int row = n - 1;
            for (int r = n - 1; r >= 0; r--)
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
    void upArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesUp(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesUp(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void leftArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesLeft(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesLeft(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void rightArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesRight(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesRight(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void downArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesDown(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesDown(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    Color tileColor4x4(int r, int c, int multi)
    {
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

    string boardValues(int gridValue)
    {

        if (gridValue != 0)
            return to_string(gridValue);
        else
            return "";
    }

    bool board(RenderWindow &window, string username, int multi)
    {

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

        while (window.isOpen())
        {
            Event event; // Making an object "event" of the Event class
            window.clear();
            while (window.pollEvent(event)) // Loop to manage when something changes in the console
            {

                Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                Button name("4096", Vector2f(150, 100), 50, Color::Transparent, Color::Black, 6);
                Button boardbackground(" ", Vector2f(395, 440), 90, Color(8, 24, 56), Color::Black);
                Button b1(boardValues(arr[0][0]), Vector2f(90, 100), calculateFontSize(arr[0][0]), tileColor4x4(0, 0, multi), Color::Black, 16.0f);
                Button b2(boardValues(arr[0][1]), Vector2f(90, 100), calculateFontSize(arr[0][1]), tileColor4x4(0, 1, multi), Color::Black, 16.0f);
                Button b3(boardValues(arr[0][2]), Vector2f(90, 100), calculateFontSize(arr[0][2]), tileColor4x4(0, 2, multi), Color::Black, 16.0f);
                Button b4(boardValues(arr[0][3]), Vector2f(90, 100), calculateFontSize(arr[0][3]), tileColor4x4(0, 3, multi), Color::Black, 16.0f);
                Button b5(boardValues(arr[1][0]), Vector2f(90, 100), calculateFontSize(arr[1][0]), tileColor4x4(1, 0, multi), Color::Black, 16.0f);
                Button b6(boardValues(arr[1][1]), Vector2f(90, 100), calculateFontSize(arr[1][1]), tileColor4x4(1, 1, multi), Color::Black, 16.0f);
                Button b7(boardValues(arr[1][2]), Vector2f(90, 100), calculateFontSize(arr[1][2]), tileColor4x4(1, 2, multi), Color::Black, 16.0f);
                Button b8(boardValues(arr[1][3]), Vector2f(90, 100), calculateFontSize(arr[1][3]), tileColor4x4(1, 3, multi), Color::Black, 16.0f);
                Button b9(boardValues(arr[2][0]), Vector2f(90, 100), calculateFontSize(arr[2][0]), tileColor4x4(2, 0, multi), Color::Black, 16.0f);
                Button b10(boardValues(arr[2][1]), Vector2f(90, 100), calculateFontSize(arr[2][1]), tileColor4x4(2, 1, multi), Color::Black, 16.0f);
                Button b11(boardValues(arr[2][2]), Vector2f(90, 100), calculateFontSize(arr[2][2]), tileColor4x4(2, 2, multi), Color::Black, 16.0f);
                Button b12(boardValues(arr[2][3]), Vector2f(90, 100), calculateFontSize(arr[2][3]), tileColor4x4(2, 3, multi), Color::Black, 16.0f);
                Button b13(boardValues(arr[3][0]), Vector2f(90, 100), calculateFontSize(arr[3][0]), tileColor4x4(3, 0, multi), Color::Black, 16.0f);
                Button b14(boardValues(arr[3][1]), Vector2f(90, 100), calculateFontSize(arr[3][1]), tileColor4x4(3, 1, multi), Color::Black, 16.0f);
                Button b15(boardValues(arr[3][2]), Vector2f(90, 100), calculateFontSize(arr[3][2]), tileColor4x4(3, 2, multi), Color::Black, 16.0f);
                Button b16(boardValues(arr[3][3]), Vector2f(90, 100), calculateFontSize(arr[3][3]), tileColor4x4(3, 3, multi), Color::Black, 16.0f);
                Button newgame("New Game", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
                Button score(to_string(scoreValue), Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
                Button best(highscore, Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);

                Font font;
                font.loadFromFile("LEMONMILK.otf");
                gameOver.setFont(font);
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
                gameOver.setPosition(Vector2f(200, 200));
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
                else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
                {
                    if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                    {
                        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                        if (name.buttonClicked(window)) // Using self defined function to check if the button was clicked
                        {
                            window.close(); // Closes the window
                        }
                        else if (newgame.buttonClicked(window)) // Using self defined function to check if the button was clicked
                        {
                            return true;
                        }
                    }
                }

                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                    {
                        upArrow(4, multi, scoreValue);
                        if (isGameOver(4))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                    {
                        downArrow(4, multi, scoreValue);
                        Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                        if (isGameOver(4))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                    {
                        leftArrow(4, multi, scoreValue);
                        if (isGameOver(4))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                    {
                        rightArrow(4, multi, scoreValue);
                        if (isGameOver(4))
                        {
                            isGameover = true;
                            runHighscore = true;
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
                newgame.drawTo(window);
                score.drawTo(window);
                best.drawTo(window);

                if (isGameover)
                {
                    gameOver.drawTo(window);
                }
                if (runHighscore)
                {
                    highScore("leaderboards/leaderboard4x4.txt", "leaderboards/namedLeaderboard4x4.txt", username, scoreValue);
                    runHighscore = false;
                }
                window.display();
            }
        }
        return false;
    }
}

// Gameboard 6x6
struct _6
{
    int arr[6][6] = {0};
    int prevArr[6][6] = {0};

    void highScore(const std::string &filename, const std::string &namedscoretxt, const std::string &name, int highscore)
    {
        std::fstream highscoreFile(filename, std::ios::in | std::ios::out);

        if (!highscoreFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        std::string line[5];
        int lineNumber = 1;

        while (lineNumber <= 5 && std::getline(highscoreFile, line[0]))
        {
            if (std::stoi(line[0]) == highscore)
                return;

            if (std::stoi(line[0]) < highscore)
                break;

            lineNumber++;
        }

        highscoreFile.seekg(0);

        for (int i = 0; i < 5; i++)
        {
            std::getline(highscoreFile, line[i]);
        }

        lineNumber--;

        if (lineNumber >= 1 && lineNumber <= 5)
            line[lineNumber] = std::to_string(highscore);

        highscoreFile.close();

        highscoreFile.open(filename, std::ios::out | std::ios::trunc);

        for (int i = 0; i < 5; i++)
        {
            highscoreFile << line[i] << std::endl;
        }
        highscoreFile.close();

        std::fstream namedHighscoreFile(namedscoretxt, std::ios::in); // Use std:: before ios

        if (!namedHighscoreFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        namedHighscoreFile.seekp(0);
        for (int i = 0; i < 5; i++)
        {
            line[i].clear(); // Clear the contents of the string
        }

        for (int i = 0; i < 5; i++)
        {
            getline(namedHighscoreFile, line[i]);
        }

        namedHighscoreFile.close();

        namedHighscoreFile.open(namedscoretxt, std::ios::out | std::ios::trunc);

        namedHighscoreFile.seekp(0);
        namedHighscoreFile << std::fixed << std::setprecision(2); // Set formatting for floating-point numbers

        for (int i = 0; i < 5; i++)
        {
            if (lineNumber != i)
                namedHighscoreFile << std::setw(20) << line[i] << std::endl;
            else
                namedHighscoreFile << std::setw(20) << std::left << std::setw(20) << name << std::right << std::setw(10) << highscore << std::endl;
        }

        namedHighscoreFile.close();
    }

    int scorefunc(int base, int merged)
    {
        int power = 0;

        while (base * (pow(2, power)) <= merged)
        {
            if (base * (pow(2, power)) == merged)
                return 2 * (pow(2, power));
            power++;
        }

        // Assuming the condition is always true
        return 0;
    }

    bool isGameOver(int n)
    {
        // Check if the board is entirely filled
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (arr[i][j] == 0)
                {
                    return false; // If any empty cell found, the game is not over
                }
            }
        }

        // Check if any adjacent elements in the same row/column are the same
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n - 1; ++j)
            {
                // Check row-wise
                if (arr[i][j] == arr[i][j + 1])
                {
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
    void copyBoard(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                prevArr[i][j] = arr[i][j];
            }
        }
    }
    // Function to check if the board has changed after movement
    bool boardChanged(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (prevArr[i][j] != arr[i][j])
                {
                    return true; // Board has changed
                }
            }
        }
        return false; // Board remains the same
    }
    void random1(int n, int multi)
    {
        while (true)
        {
            int r = rand() % n;
            int c = rand() % n;
            if (arr[r][c] == 0)
            {
                arr[r][c] = multi;
                break;
            }
        }
    }
    void mergeTilesud(int n, int multi, int &scoreValue)
    {
        for (int c = 0; c < n; ++c)
        {
            for (int r = 0; r < n - 1; ++r)
            {
                if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c])
                {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r + 1][c] = 0;
                }
            }
        }
    }
    void mergeTilesrl(int n, int multi, int &scoreValue)
    {
        for (int r = 0; r < n; ++r)
        {
            for (int c = 0; c < n - 1; ++c)
            {
                if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1])
                {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r][c + 1] = 0;
                }
            }
        }
    }
    void moveTilesRight(int n)
    {
        for (int r = 0; r < n; r++)
        {
            int column = n - 1;
            for (int c = n - 1; c >= 0; c--)
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
    void moveTilesLeft(int n)
    {
        for (int r = 0; r < n; ++r)
        {
            int column = 0;
            for (int c = 0; c < n; c++)
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
    void moveTilesUp(int n)
    {
        for (int c = 0; c < n; c++)
        {
            int row = 0;
            for (int r = 0; r < n; r++)
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
    void moveTilesDown(int n)
    {
        for (int c = 0; c < n; c++)
        {
            int row = n - 1;
            for (int r = n - 1; r >= 0; r--)
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
    void upArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesUp(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesUp(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void leftArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesLeft(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesLeft(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void rightArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesRight(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesRight(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void downArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesDown(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesDown(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
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

    string boardValues(int gridValue)
    {

        if (gridValue != 0)
            return to_string(gridValue);
        else
            return "";
    }
    Color tileColor6x6(int r, int c, int multi)
    {

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
    bool board(RenderWindow &window, string username, int multi)
    {

        srand(time(0));

        ifstream file("leaderboards/leaderboard6x6.txt");
        string highscore;
        getline(file, highscore);
        file.close();

        bool isGameover = false;
        bool runHighscore = false;
        int scoreValue = 0;

        int r = rand() % 6;
        int c = rand() % 6;

        arr[r][c] = multi;

        window.setFramerateLimit(60);

        while (window.isOpen())
        {
            Event event; // Making an object "event" of the Event class
            window.clear();

            while (window.pollEvent(event)) // Loop to manage when something changes in the console
            {

                Button name("4096", Vector2f(150, 100), 50, Color::Transparent, Color::Black, 6);
                Button boardbackground(" ", Vector2f(395, 465), 90, Color(16, 8, 56), Color::Black);
                Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                Button b1(boardValues(arr[0][0]), Vector2f(60, 70), calculateFontSize(arr[0][0]), tileColor6x6(0, 0, multi), Color::Black, 16.0f);
                Button b2(boardValues(arr[0][1]), Vector2f(60, 70), calculateFontSize(arr[0][1]), tileColor6x6(0, 1, multi), Color::Black, 16.0f);
                Button b3(boardValues(arr[0][2]), Vector2f(60, 70), calculateFontSize(arr[0][2]), tileColor6x6(0, 2, multi), Color::Black, 16.0f);
                Button b4(boardValues(arr[0][3]), Vector2f(60, 70), calculateFontSize(arr[0][3]), tileColor6x6(0, 3, multi), Color::Black, 16.0f);
                Button b5(boardValues(arr[0][4]), Vector2f(60, 70), calculateFontSize(arr[0][4]), tileColor6x6(0, 4, multi), Color::Black, 16.0f);
                Button b6(boardValues(arr[0][5]), Vector2f(60, 70), calculateFontSize(arr[0][5]), tileColor6x6(0, 5, multi), Color::Black, 16.0f);
                // Row 2
                Button b7(boardValues(arr[1][0]), Vector2f(60, 70), calculateFontSize(arr[1][0]), tileColor6x6(1, 0, multi), Color::Black, 16.0f);
                Button b8(boardValues(arr[1][1]), Vector2f(60, 70), calculateFontSize(arr[1][1]), tileColor6x6(1, 1, multi), Color::Black, 16.0f);
                Button b9(boardValues(arr[1][2]), Vector2f(60, 70), calculateFontSize(arr[1][2]), tileColor6x6(1, 2, multi), Color::Black, 16.0f);
                Button b10(boardValues(arr[1][3]), Vector2f(60, 70), calculateFontSize(arr[1][3]), tileColor6x6(1, 3, multi), Color::Black, 16.0f);
                Button b11(boardValues(arr[1][4]), Vector2f(60, 70), calculateFontSize(arr[1][4]), tileColor6x6(1, 4, multi), Color::Black, 16.0f);
                Button b12(boardValues(arr[1][5]), Vector2f(60, 70), calculateFontSize(arr[1][5]), tileColor6x6(1, 5, multi), Color::Black, 16.0f);
                // Row 3
                Button b13(boardValues(arr[2][0]), Vector2f(60, 70), calculateFontSize(arr[2][0]), tileColor6x6(2, 0, multi), Color::Black, 16.0f);
                Button b14(boardValues(arr[2][1]), Vector2f(60, 70), calculateFontSize(arr[2][1]), tileColor6x6(2, 1, multi), Color::Black, 16.0f);
                Button b15(boardValues(arr[2][2]), Vector2f(60, 70), calculateFontSize(arr[2][2]), tileColor6x6(2, 2, multi), Color::Black, 16.0f);
                Button b16(boardValues(arr[2][3]), Vector2f(60, 70), calculateFontSize(arr[2][3]), tileColor6x6(2, 3, multi), Color::Black, 16.0f);
                Button b17(boardValues(arr[2][4]), Vector2f(60, 70), calculateFontSize(arr[2][4]), tileColor6x6(2, 4, multi), Color::Black, 16.0f);
                Button b18(boardValues(arr[2][5]), Vector2f(60, 70), calculateFontSize(arr[2][5]), tileColor6x6(2, 5, multi), Color::Black, 16.0f);
                // Row 4
                Button b19(boardValues(arr[3][0]), Vector2f(60, 70), calculateFontSize(arr[3][0]), tileColor6x6(3, 0, multi), Color::Black, 16.0f);
                Button b20(boardValues(arr[3][1]), Vector2f(60, 70), calculateFontSize(arr[3][1]), tileColor6x6(3, 1, multi), Color::Black, 16.0f);
                Button b21(boardValues(arr[3][2]), Vector2f(60, 70), calculateFontSize(arr[3][2]), tileColor6x6(3, 2, multi), Color::Black, 16.0f);
                Button b22(boardValues(arr[3][3]), Vector2f(60, 70), calculateFontSize(arr[3][3]), tileColor6x6(3, 3, multi), Color::Black, 16.0f);
                Button b23(boardValues(arr[3][4]), Vector2f(60, 70), calculateFontSize(arr[3][4]), tileColor6x6(3, 4, multi), Color::Black, 16.0f);
                Button b24(boardValues(arr[3][5]), Vector2f(60, 70), calculateFontSize(arr[3][5]), tileColor6x6(3, 5, multi), Color::Black, 16.0f);
                // Row 5
                Button b25(boardValues(arr[4][0]), Vector2f(60, 70), calculateFontSize(arr[4][0]), tileColor6x6(4, 0, multi), Color::Black, 16.0f);
                Button b26(boardValues(arr[4][1]), Vector2f(60, 70), calculateFontSize(arr[4][1]), tileColor6x6(4, 1, multi), Color::Black, 16.0f);
                Button b27(boardValues(arr[4][2]), Vector2f(60, 70), calculateFontSize(arr[4][2]), tileColor6x6(4, 2, multi), Color::Black, 16.0f);
                Button b28(boardValues(arr[4][3]), Vector2f(60, 70), calculateFontSize(arr[4][3]), tileColor6x6(4, 3, multi), Color::Black, 16.0f);
                Button b29(boardValues(arr[4][4]), Vector2f(60, 70), calculateFontSize(arr[4][4]), tileColor6x6(4, 4, multi), Color::Black, 16.0f);
                Button b30(boardValues(arr[4][5]), Vector2f(60, 70), calculateFontSize(arr[4][5]), tileColor6x6(4, 5, multi), Color::Black, 16.0f);
                // Row 6
                Button b31(boardValues(arr[5][0]), Vector2f(60, 70), calculateFontSize(arr[5][0]), tileColor6x6(5, 0, multi), Color::Black, 16.0f);
                Button b32(boardValues(arr[5][1]), Vector2f(60, 70), calculateFontSize(arr[5][1]), tileColor6x6(5, 1, multi), Color::Black, 16.0f);
                Button b33(boardValues(arr[5][2]), Vector2f(60, 70), calculateFontSize(arr[5][2]), tileColor6x6(5, 2, multi), Color::Black, 16.0f);
                Button b34(boardValues(arr[5][3]), Vector2f(60, 70), calculateFontSize(arr[5][3]), tileColor6x6(5, 3, multi), Color::Black, 16.0f);
                Button b35(boardValues(arr[5][4]), Vector2f(60, 70), calculateFontSize(arr[5][4]), tileColor6x6(5, 4, multi), Color::Black, 16.0f);
                Button b36(boardValues(arr[5][5]), Vector2f(60, 70), calculateFontSize(arr[5][5]), tileColor6x6(5, 5, multi), Color::Black, 16.0f);
                Button newgame("New Game", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
                Button score(to_string(scoreValue), Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
                Button best(highscore, Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);

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
                // Row 1
                b1.setPosition(Vector2f(378, 210));
                b2.setPosition(Vector2f(442, 210));
                b3.setPosition(Vector2f(506, 210));
                b4.setPosition(Vector2f(570, 210));
                b5.setPosition(Vector2f(634, 210));
                b6.setPosition(Vector2f(698, 210));
                // Row 2
                b7.setPosition(Vector2f(378, 285));
                b8.setPosition(Vector2f(442, 285));
                b9.setPosition(Vector2f(506, 285));
                b10.setPosition(Vector2f(570, 285));
                b11.setPosition(Vector2f(634, 285));
                b12.setPosition(Vector2f(698, 285));
                // Row 3
                b13.setPosition(Vector2f(378, 360));
                b14.setPosition(Vector2f(442, 360));
                b15.setPosition(Vector2f(506, 360));
                b16.setPosition(Vector2f(570, 360));
                b17.setPosition(Vector2f(634, 360));
                b18.setPosition(Vector2f(698, 360));
                // Row 4
                b19.setPosition(Vector2f(378, 435));
                b20.setPosition(Vector2f(442, 435));
                b21.setPosition(Vector2f(506, 435));
                b22.setPosition(Vector2f(570, 435));
                b23.setPosition(Vector2f(634, 435));
                b24.setPosition(Vector2f(698, 435));
                // Row 5
                b25.setPosition(Vector2f(378, 510));
                b26.setPosition(Vector2f(442, 510));
                b27.setPosition(Vector2f(506, 510));
                b28.setPosition(Vector2f(570, 510));
                b29.setPosition(Vector2f(634, 510));
                b30.setPosition(Vector2f(698, 510));
                // Row 6
                b31.setPosition(Vector2f(378, 585));
                b32.setPosition(Vector2f(442, 585));
                b33.setPosition(Vector2f(506, 585));
                b34.setPosition(Vector2f(570, 585));
                b35.setPosition(Vector2f(634, 585));
                b36.setPosition(Vector2f(698, 585));

                newgame.setPosition(Vector2f(666, 150));
                score.setPosition(Vector2f(566, 50));
                best.setPosition(Vector2f(672, 50));
                if (event.type == Event::Closed)
                {
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
                        else if (newgame.buttonClicked(window)) // Using self defined function to check if the button was clicked
                        {
                            return true;
                        }
                    }
                }

                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                    {
                        upArrow(6, multi, scoreValue);
                        if (isGameOver(6))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                    {
                        downArrow(6, multi, scoreValue);
                        Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                        if (isGameOver(6))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                    {
                        leftArrow(6, multi, scoreValue);
                        if (isGameOver(6))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                    {
                        rightArrow(6, multi, scoreValue);
                        if (isGameOver(6))
                        {
                            isGameover = true;
                            runHighscore = true;
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
                if (isGameover)
                {
                    gameOver.drawTo(window);
                }
                if (runHighscore)
                {
                    highScore("leaderboards/leaderboard6x6.txt", "leaderboards/namedLeaderboard6x6.txt", username, scoreValue);
                    runHighscore = false;
                }
                window.display();
            }
        }
        return false;
    }
}

// Gameboard 8x8:
struct _8
{

    int arr[8][8];
    int prevArr[8][8];

    void highScore(const std::string &filename, const std::string &namedscoretxt, const std::string &name, int highscore)
    {
        std::fstream highscoreFile(filename, std::ios::in | std::ios::out);

        if (!highscoreFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        std::string line[5];
        int lineNumber = 1;

        while (lineNumber <= 5 && std::getline(highscoreFile, line[0]))
        {
            if (std::stoi(line[0]) == highscore)
                return;

            if (std::stoi(line[0]) < highscore)
                break;

            lineNumber++;
        }

        highscoreFile.seekg(0);

        for (int i = 0; i < 5; i++)
        {
            std::getline(highscoreFile, line[i]);
        }

        lineNumber--;

        if (lineNumber >= 1 && lineNumber <= 5)
            line[lineNumber] = std::to_string(highscore);

        highscoreFile.close();

        highscoreFile.open(filename, std::ios::out | std::ios::trunc);

        for (int i = 0; i < 5; i++)
        {
            highscoreFile << line[i] << std::endl;
        }
        highscoreFile.close();

        std::fstream namedHighscoreFile(namedscoretxt, std::ios::in); // Use std:: before ios

        if (!namedHighscoreFile.is_open())
        {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        namedHighscoreFile.seekp(0);
        for (int i = 0; i < 5; i++)
        {
            line[i].clear(); // Clear the contents of the string
        }

        for (int i = 0; i < 5; i++)
        {
            getline(namedHighscoreFile, line[i]);
        }

        namedHighscoreFile.close();

        namedHighscoreFile.open(namedscoretxt, std::ios::out | std::ios::trunc);

        namedHighscoreFile.seekp(0);
        namedHighscoreFile << std::fixed << std::setprecision(2); // Set formatting for floating-point numbers

        for (int i = 0; i < 5; i++)
        {
            if (lineNumber != i)
                namedHighscoreFile << std::setw(20) << line[i] << std::endl;
            else
                namedHighscoreFile << std::setw(20) << std::left << std::setw(20) << name << std::right << std::setw(10) << highscore << std::endl;
        }

        namedHighscoreFile.close();
    }

    int scorefunc(int base, int merged)
    {
        int power = 0;

        while (base * (pow(2, power)) <= merged)
        {
            if (base * (pow(2, power)) == merged)
                return 2 * (pow(2, power));
            power++;
        }

        // Assuming the condition is always true
        return 0;
    }

    bool isGameOver(int n)
    {
        // Check if the board is entirely filled
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (arr[i][j] == 0)
                {
                    return false; // If any empty cell found, the game is not over
                }
            }
        }

        // Check if any adjacent elements in the same row/column are the same
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n - 1; ++j)
            {
                // Check row-wise
                if (arr[i][j] == arr[i][j + 1])
                {
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
    void copyBoard(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                prevArr[i][j] = arr[i][j];
            }
        }
    }
    // Function to check if the board has changed after movement
    bool boardChanged(int n)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (prevArr[i][j] != arr[i][j])
                {
                    return true; // Board has changed
                }
            }
        }
        return false; // Board remains the same
    }
    void random1(int n, int multi)
    {
        while (true)
        {
            int r = rand() % n;
            int c = rand() % n;
            if (arr[r][c] == 0)
            {
                arr[r][c] = multi;
                break;
            }
        }
    }
    void mergeTilesud(int n, int multi, int &scoreValue)
    {
        for (int c = 0; c < n; ++c)
        {
            for (int r = 0; r < n - 1; ++r)
            {
                if (arr[r][c] != 0 && arr[r][c] == arr[r + 1][c])
                {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r + 1][c] = 0;
                }
            }
        }
    }
    void mergeTilesrl(int n, int multi, int &scoreValue)
    {
        for (int r = 0; r < n; ++r)
        {
            for (int c = 0; c < n - 1; ++c)
            {
                if (arr[r][c] != 0 && arr[r][c] == arr[r][c + 1])
                {
                    arr[r][c] *= 2;
                    scoreValue += scorefunc(multi, arr[r][c]);
                    arr[r][c + 1] = 0;
                }
            }
        }
    }
    void moveTilesRight(int n)
    {
        for (int r = 0; r < n; r++)
        {
            int column = n - 1;
            for (int c = n - 1; c >= 0; c--)
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
    void moveTilesLeft(int n)
    {
        for (int r = 0; r < n; ++r)
        {
            int column = 0;
            for (int c = 0; c < n; c++)
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
    void moveTilesUp(int n)
    {
        for (int c = 0; c < n; c++)
        {
            int row = 0;
            for (int r = 0; r < n; r++)
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
    void moveTilesDown(int n)
    {
        for (int c = 0; c < n; c++)
        {
            int row = n - 1;
            for (int r = n - 1; r >= 0; r--)
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
    void upArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesUp(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesUp(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void leftArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesLeft(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesLeft(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void rightArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesRight(n);
        mergeTilesrl(n, multi, scoreValue);
        moveTilesRight(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
    }
    void downArrow(int n, int multi, int &scoreValue)
    {
        copyBoard(n);
        moveTilesDown(n);
        mergeTilesud(n, multi, scoreValue);
        moveTilesDown(n);
        if (boardChanged(n))
        {
            random1(n, multi);
        }
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

    string boardValues(int gridValue)
    {

        if (gridValue != 0)
            return to_string(gridValue);
        else
            return "";
    }
    Color tileColor8x8(int r, int c, int multi)
    {

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

    bool board(RenderWindow &window, string username, int multi)
    {

        ifstream file("highscore.txt");
        string highscore;
        getline(file, highscore);
        file.close();

        srand(time(0));

        bool isGameover = false;
        bool runHighscore = false;
        int r = rand() % 8;
        int c = rand() % 8;
        int scoreValue = 0;

        arr[r][c] = multi;
        window.setFramerateLimit(60);

        while (window.isOpen())
        {
            Event event; // Making an object "event" of the Event class
            window.clear();

            while (window.pollEvent(event)) // Loop to manage when something changes in the console
            {

                Button name("2048", Vector2f(150, 100), 50, Color::Transparent, Color::Black, 6);
                Button boardbackground(" ", Vector2f(405, 512), 90, Color(80, 0, 8), Color::Black);
                Button newgame("New Game", Vector2f(100, 45), 15, Color(160, 82, 45), Color::White);
                Button score(to_string(scoreValue), Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
                Button best(highscore, Vector2f(100, 55), 14, Color(160, 82, 45), Color::White);
                Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                // Row 1
                Button b1(boardValues(arr[0][0]), Vector2f(45, 55), calculateFontSize(arr[0][0]), tileColor8x8(0, 0, multi), Color::Black, 16.0f);
                Button b2(boardValues(arr[0][1]), Vector2f(45, 55), calculateFontSize(arr[0][1]), tileColor8x8(0, 1, multi), Color::Black, 16.0f);
                Button b3(boardValues(arr[0][2]), Vector2f(45, 55), calculateFontSize(arr[0][2]), tileColor8x8(0, 2, multi), Color::Black, 16.0f);
                Button b4(boardValues(arr[0][3]), Vector2f(45, 55), calculateFontSize(arr[0][3]), tileColor8x8(0, 3, multi), Color::Black, 16.0f);
                Button b5(boardValues(arr[0][4]), Vector2f(45, 55), calculateFontSize(arr[0][4]), tileColor8x8(0, 4, multi), Color::Black, 16.0f);
                Button b6(boardValues(arr[0][5]), Vector2f(45, 55), calculateFontSize(arr[0][5]), tileColor8x8(0, 5, multi), Color::Black, 16.0f);
                Button b7(boardValues(arr[0][6]), Vector2f(45, 55), calculateFontSize(arr[0][6]), tileColor8x8(0, 6, multi), Color::Black, 16.0f);
                Button b8(boardValues(arr[0][7]), Vector2f(45, 55), calculateFontSize(arr[0][7]), tileColor8x8(0, 7, multi), Color::Black, 16.0f);
                // Row 2
                Button b9(boardValues(arr[1][0]), Vector2f(45, 55), calculateFontSize(arr[1][0]), tileColor8x8(1, 0, multi), Color::Black, 16.0f);
                Button b10(boardValues(arr[1][1]), Vector2f(45, 55), calculateFontSize(arr[1][1]), tileColor8x8(1, 1, multi), Color::Black, 16.0f);
                Button b11(boardValues(arr[1][2]), Vector2f(45, 55), calculateFontSize(arr[1][2]), tileColor8x8(1, 2, multi), Color::Black, 16.0f);
                Button b12(boardValues(arr[1][3]), Vector2f(45, 55), calculateFontSize(arr[1][3]), tileColor8x8(1, 3, multi), Color::Black, 16.0f);
                Button b13(boardValues(arr[1][4]), Vector2f(45, 55), calculateFontSize(arr[1][4]), tileColor8x8(1, 4, multi), Color::Black, 16.0f);
                Button b14(boardValues(arr[1][5]), Vector2f(45, 55), calculateFontSize(arr[1][5]), tileColor8x8(1, 5, multi), Color::Black, 16.0f);
                Button b15(boardValues(arr[1][6]), Vector2f(45, 55), calculateFontSize(arr[1][6]), tileColor8x8(1, 6, multi), Color::Black, 16.0f);
                Button b16(boardValues(arr[1][7]), Vector2f(45, 55), calculateFontSize(arr[1][7]), tileColor8x8(1, 7, multi), Color::Black, 16.0f);
                // Row 3
                Button b17(boardValues(arr[2][0]), Vector2f(45, 55), calculateFontSize(arr[2][0]), tileColor8x8(2, 0, multi), Color::Black, 16.0f);
                Button b18(boardValues(arr[2][1]), Vector2f(45, 55), calculateFontSize(arr[2][1]), tileColor8x8(2, 1, multi), Color::Black, 16.0f);
                Button b19(boardValues(arr[2][2]), Vector2f(45, 55), calculateFontSize(arr[2][2]), tileColor8x8(2, 2, multi), Color::Black, 16.0f);
                Button b20(boardValues(arr[2][3]), Vector2f(45, 55), calculateFontSize(arr[2][3]), tileColor8x8(2, 3, multi), Color::Black, 16.0f);
                Button b21(boardValues(arr[2][4]), Vector2f(45, 55), calculateFontSize(arr[2][4]), tileColor8x8(2, 4, multi), Color::Black, 16.0f);
                Button b22(boardValues(arr[2][5]), Vector2f(45, 55), calculateFontSize(arr[2][5]), tileColor8x8(2, 5, multi), Color::Black, 16.0f);
                Button b23(boardValues(arr[2][6]), Vector2f(45, 55), calculateFontSize(arr[2][6]), tileColor8x8(2, 6, multi), Color::Black, 16.0f);
                Button b24(boardValues(arr[2][7]), Vector2f(45, 55), calculateFontSize(arr[2][7]), tileColor8x8(2, 7, multi), Color::Black, 16.0f);
                // Row 4
                Button b25(boardValues(arr[3][0]), Vector2f(45, 55), calculateFontSize(arr[3][0]), tileColor8x8(3, 0, multi), Color::Black, 16.0f);
                Button b26(boardValues(arr[3][1]), Vector2f(45, 55), calculateFontSize(arr[3][1]), tileColor8x8(3, 1, multi), Color::Black, 16.0f);
                Button b27(boardValues(arr[3][2]), Vector2f(45, 55), calculateFontSize(arr[3][2]), tileColor8x8(3, 2, multi), Color::Black, 16.0f);
                Button b28(boardValues(arr[3][3]), Vector2f(45, 55), calculateFontSize(arr[3][3]), tileColor8x8(3, 3, multi), Color::Black, 16.0f);
                Button b29(boardValues(arr[3][4]), Vector2f(45, 55), calculateFontSize(arr[3][4]), tileColor8x8(3, 4, multi), Color::Black, 16.0f);
                Button b30(boardValues(arr[3][5]), Vector2f(45, 55), calculateFontSize(arr[3][5]), tileColor8x8(3, 5, multi), Color::Black, 16.0f);
                Button b31(boardValues(arr[3][6]), Vector2f(45, 55), calculateFontSize(arr[3][6]), tileColor8x8(3, 6, multi), Color::Black, 16.0f);
                Button b32(boardValues(arr[3][7]), Vector2f(45, 55), calculateFontSize(arr[3][7]), tileColor8x8(3, 7, multi), Color::Black, 16.0f);
                // Row 5
                Button b33(boardValues(arr[4][0]), Vector2f(45, 55), calculateFontSize(arr[4][0]), tileColor8x8(4, 0, multi), Color::Black, 16.0f);
                Button b34(boardValues(arr[4][1]), Vector2f(45, 55), calculateFontSize(arr[4][1]), tileColor8x8(4, 1, multi), Color::Black, 16.0f);
                Button b35(boardValues(arr[4][2]), Vector2f(45, 55), calculateFontSize(arr[4][2]), tileColor8x8(4, 2, multi), Color::Black, 16.0f);
                Button b36(boardValues(arr[4][3]), Vector2f(45, 55), calculateFontSize(arr[4][3]), tileColor8x8(4, 3, multi), Color::Black, 16.0f);
                Button b37(boardValues(arr[4][4]), Vector2f(45, 55), calculateFontSize(arr[4][4]), tileColor8x8(4, 4, multi), Color::Black, 16.0f);
                Button b38(boardValues(arr[4][5]), Vector2f(45, 55), calculateFontSize(arr[4][5]), tileColor8x8(4, 5, multi), Color::Black, 16.0f);
                Button b39(boardValues(arr[4][6]), Vector2f(45, 55), calculateFontSize(arr[4][6]), tileColor8x8(4, 6, multi), Color::Black, 16.0f);
                Button b40(boardValues(arr[4][7]), Vector2f(45, 55), calculateFontSize(arr[4][7]), tileColor8x8(4, 7, multi), Color::Black, 16.0f);
                // Row 6
                Button b41(boardValues(arr[5][0]), Vector2f(45, 55), calculateFontSize(arr[5][0]), tileColor8x8(5, 0, multi), Color::Black, 16.0f);
                Button b42(boardValues(arr[5][1]), Vector2f(45, 55), calculateFontSize(arr[5][1]), tileColor8x8(5, 1, multi), Color::Black, 16.0f);
                Button b43(boardValues(arr[5][2]), Vector2f(45, 55), calculateFontSize(arr[5][2]), tileColor8x8(5, 2, multi), Color::Black, 16.0f);
                Button b44(boardValues(arr[5][3]), Vector2f(45, 55), calculateFontSize(arr[5][3]), tileColor8x8(5, 3, multi), Color::Black, 16.0f);
                Button b45(boardValues(arr[5][4]), Vector2f(45, 55), calculateFontSize(arr[5][4]), tileColor8x8(5, 4, multi), Color::Black, 16.0f);
                Button b46(boardValues(arr[5][5]), Vector2f(45, 55), calculateFontSize(arr[5][5]), tileColor8x8(5, 5, multi), Color::Black, 16.0f);
                Button b47(boardValues(arr[5][6]), Vector2f(45, 55), calculateFontSize(arr[5][6]), tileColor8x8(5, 6, multi), Color::Black, 16.0f);
                Button b48(boardValues(arr[5][7]), Vector2f(45, 55), calculateFontSize(arr[5][7]), tileColor8x8(5, 7, multi), Color::Black, 16.0f);
                // Row 7
                Button b49(boardValues(arr[6][0]), Vector2f(45, 55), calculateFontSize(arr[6][0]), tileColor8x8(6, 0, multi), Color::Black, 16.0f);
                Button b50(boardValues(arr[6][1]), Vector2f(45, 55), calculateFontSize(arr[6][1]), tileColor8x8(6, 1, multi), Color::Black, 16.0f);
                Button b51(boardValues(arr[6][2]), Vector2f(45, 55), calculateFontSize(arr[6][2]), tileColor8x8(6, 2, multi), Color::Black, 16.0f);
                Button b52(boardValues(arr[6][3]), Vector2f(45, 55), calculateFontSize(arr[6][3]), tileColor8x8(6, 3, multi), Color::Black, 16.0f);
                Button b53(boardValues(arr[6][4]), Vector2f(45, 55), calculateFontSize(arr[6][4]), tileColor8x8(6, 4, multi), Color::Black, 16.0f);
                Button b54(boardValues(arr[6][5]), Vector2f(45, 55), calculateFontSize(arr[6][5]), tileColor8x8(6, 5, multi), Color::Black, 16.0f);
                Button b55(boardValues(arr[6][6]), Vector2f(45, 55), calculateFontSize(arr[6][6]), tileColor8x8(6, 6, multi), Color::Black, 16.0f);
                Button b56(boardValues(arr[6][7]), Vector2f(45, 55), calculateFontSize(arr[6][7]), tileColor8x8(6, 7, multi), Color::Black, 16.0f);
                // Row 8
                Button b57(boardValues(arr[7][0]), Vector2f(45, 55), calculateFontSize(arr[7][0]), tileColor8x8(7, 0, multi), Color::Black, 16.0f);
                Button b58(boardValues(arr[7][1]), Vector2f(45, 55), calculateFontSize(arr[7][1]), tileColor8x8(7, 1, multi), Color::Black, 16.0f);
                Button b59(boardValues(arr[7][2]), Vector2f(45, 55), calculateFontSize(arr[7][2]), tileColor8x8(7, 2, multi), Color::Black, 16.0f);
                Button b60(boardValues(arr[7][3]), Vector2f(45, 55), calculateFontSize(arr[7][3]), tileColor8x8(7, 3, multi), Color::Black, 16.0f);
                Button b61(boardValues(arr[7][4]), Vector2f(45, 55), calculateFontSize(arr[7][4]), tileColor8x8(7, 4, multi), Color::Black, 16.0f);
                Button b62(boardValues(arr[7][5]), Vector2f(45, 55), calculateFontSize(arr[7][5]), tileColor8x8(7, 5, multi), Color::Black, 16.0f);
                Button b63(boardValues(arr[7][6]), Vector2f(45, 55), calculateFontSize(arr[7][6]), tileColor8x8(7, 6, multi), Color::Black, 16.0f);
                Button b64(boardValues(arr[7][7]), Vector2f(45, 55), calculateFontSize(arr[7][7]), tileColor8x8(7, 7, multi), Color::Black, 16.0f);

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
                b37.setFont(font);
                b38.setFont(font);
                b39.setFont(font);
                b40.setFont(font);
                b41.setFont(font);
                b42.setFont(font);
                b43.setFont(font);
                b44.setFont(font);
                b45.setFont(font);
                b46.setFont(font);
                b47.setFont(font);
                b48.setFont(font);
                b49.setFont(font);
                b50.setFont(font);
                b51.setFont(font);
                b52.setFont(font);
                b53.setFont(font);
                b54.setFont(font);
                b55.setFont(font);
                b56.setFont(font);
                b57.setFont(font);
                b58.setFont(font);
                b59.setFont(font);
                b60.setFont(font);
                b61.setFont(font);
                b62.setFont(font);
                b63.setFont(font);
                b64.setFont(font);

                newgame.setFont(font);
                score.setFont(font);
                best.setFont(font);

                // Assigning the positions...
                boardbackground.setPosition(Vector2f(370, 200));
                name.setPosition(Vector2f(370, 70));
                gameOver.setPosition(Vector2f(200, 200));
                // Row 1
                b1.setPosition(Vector2f(378, 210));
                b2.setPosition(Vector2f(427, 210));
                b3.setPosition(Vector2f(476, 210));
                b4.setPosition(Vector2f(525, 210));
                b5.setPosition(Vector2f(575, 210));
                b6.setPosition(Vector2f(624, 210));
                b7.setPosition(Vector2f(673, 210));
                b8.setPosition(Vector2f(722, 210));
                // Row 2

                b9.setPosition(Vector2f(378, 272));
                b10.setPosition(Vector2f(427, 272));
                b11.setPosition(Vector2f(476, 272));
                b12.setPosition(Vector2f(525, 272));
                b13.setPosition(Vector2f(575, 272));
                b14.setPosition(Vector2f(624, 272));
                b15.setPosition(Vector2f(673, 272));
                b16.setPosition(Vector2f(722, 272));
                // Row 3

                b17.setPosition(Vector2f(378, 334));
                b18.setPosition(Vector2f(427, 334));
                b19.setPosition(Vector2f(476, 334));
                b20.setPosition(Vector2f(525, 334));
                b21.setPosition(Vector2f(575, 334));
                b22.setPosition(Vector2f(624, 334));
                b23.setPosition(Vector2f(673, 334));
                b24.setPosition(Vector2f(722, 334));
                // Row 4
                b25.setPosition(Vector2f(378, 396));
                b26.setPosition(Vector2f(427, 396));
                b27.setPosition(Vector2f(476, 396));
                b28.setPosition(Vector2f(525, 396));
                b29.setPosition(Vector2f(575, 396));
                b30.setPosition(Vector2f(624, 396));
                b31.setPosition(Vector2f(673, 396));
                b32.setPosition(Vector2f(722, 396));
                // Row 5
                b33.setPosition(Vector2f(378, 458));
                b34.setPosition(Vector2f(427, 458));
                b35.setPosition(Vector2f(476, 458));
                b36.setPosition(Vector2f(525, 458));
                b37.setPosition(Vector2f(575, 458));
                b38.setPosition(Vector2f(624, 458));
                b39.setPosition(Vector2f(673, 458));
                b40.setPosition(Vector2f(722, 458));
                // Row 6
                b41.setPosition(Vector2f(378, 520));
                b42.setPosition(Vector2f(427, 520));
                b43.setPosition(Vector2f(476, 520));
                b44.setPosition(Vector2f(525, 520));
                b45.setPosition(Vector2f(575, 520));
                b46.setPosition(Vector2f(624, 520));
                b47.setPosition(Vector2f(673, 520));
                b48.setPosition(Vector2f(722, 520));
                // Row 7
                b49.setPosition(Vector2f(378, 585));
                b50.setPosition(Vector2f(427, 585));
                b51.setPosition(Vector2f(476, 585));
                b52.setPosition(Vector2f(525, 585));
                b53.setPosition(Vector2f(575, 585));
                b54.setPosition(Vector2f(624, 585));
                b55.setPosition(Vector2f(673, 585));
                b56.setPosition(Vector2f(722, 585));
                // Row 8
                b57.setPosition(Vector2f(378, 647));
                b58.setPosition(Vector2f(427, 647));
                b59.setPosition(Vector2f(476, 647));
                b60.setPosition(Vector2f(525, 647));
                b61.setPosition(Vector2f(575, 647));
                b62.setPosition(Vector2f(624, 647));
                b63.setPosition(Vector2f(673, 647));
                b64.setPosition(Vector2f(722, 647));

                newgame.setPosition(Vector2f(666, 150));
                score.setPosition(Vector2f(566, 50));
                best.setPosition(Vector2f(672, 50));
                if (event.type == Event::Closed)
                {
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
                        else if (newgame.buttonClicked(window)) // Using self defined function to check if the button was clicked
                        {
                            return true;
                        }
                    }
                }

                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                    {
                        upArrow(8, multi, scoreValue);
                        if (isGameOver(8))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                    {
                        downArrow(8, multi, scoreValue);
                        Button gameOver("GAME OVER", Vector2f(200, 200), 24, Color::Black, Color::White);
                        if (isGameOver(8))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                    {
                        leftArrow(8, multi, scoreValue);
                        if (isGameOver(8))
                        {
                            isGameover = true;
                            runHighscore = true;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                    {
                        rightArrow(8, multi, scoreValue);
                        if (isGameOver(8))
                        {
                            isGameover = true;
                            runHighscore = true;
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
                b37.drawTo(window);
                b38.drawTo(window);
                b39.drawTo(window);
                b40.drawTo(window);
                b41.drawTo(window);
                b42.drawTo(window);
                b43.drawTo(window);
                b44.drawTo(window);
                b45.drawTo(window);
                b46.drawTo(window);
                b47.drawTo(window);
                b48.drawTo(window);
                b49.drawTo(window);
                b50.drawTo(window);
                b51.drawTo(window);
                b52.drawTo(window);
                b53.drawTo(window);
                b54.drawTo(window);
                b55.drawTo(window);
                b56.drawTo(window);
                b57.drawTo(window);
                b58.drawTo(window);
                b59.drawTo(window);
                b60.drawTo(window);
                b61.drawTo(window);
                b62.drawTo(window);
                b63.drawTo(window);
                b64.drawTo(window);

                newgame.drawTo(window);
                score.drawTo(window);
                best.drawTo(window);
                if (runHighscore)
                {
                    highScore("highscores/unnamedhighscore8x8.txt", "highscores/highscore8x8.txt", username, scoreValue);
                    runHighscore = false;
                }
                if (isGameover)
                {
                    gameOver.drawTo(window);
                }

                window.display();
            }
        }
        return false;
    }
} int beforeLeaderboard(RenderWindow &window)
{

    Picture preview4x4("grid4_preview.png");
    Picture preview6x6("grid6_preview.png");
    Picture preview8x8("grid8_preview.png");
    // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

    // Creating an object of the Button class named "button" and specifying its properties
    Button four("4 X 4", Vector2f(150, 50), 24, Color(6, 46, 81), Color::White);
    Button six("6 X 6", Vector2f(150, 50), 24, Color(60, 52, 124), Color::White);
    Button eight("8 X 8", Vector2f(150, 50), 24, Color(125, 13, 13), Color::White);
    Button back("Back", Vector2f(100, 45), 24, Color(3, 85, 97), Color::White);

    // Making an object of the Font class called "font"
    Font font;

    // Loading the font for the button
    font.loadFromFile("LEMONMILK.otf");

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

            else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
            {

                if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                {

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                    if (four.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {
                        Leaderboard("leaderboards/namedLeaderboard4x4.txt");
                    }
                    if (six.buttonClicked(window))
                    {
                        Leaderboard("leaderboards/namedLeaderboard6x6.txt");
                    }
                    if (eight.buttonClicked(window))
                    {
                        Leaderboard("leaderboards/namedLeaderboard8x8.txt");
                    }
                    if (back.buttonClicked(window))
                    {
                        return;
                    }
                }
            }
        }

        window.clear(Color::White);

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

void mainMenu(RenderWindow &window)
{

    window.setFramerateLimit(60); // Setting the frame rate to 60 fps

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

    string input;
    int multi = 0;
    int grid = 0;
    Color gdc = Color(3, 85, 97);

    inputText.setCharacterSize(25);
    inputText.setFillColor(Color::Black);

    textBoxBackground.setSize(Vector2f(590.f, 50.f));
    textBoxBackground.setFillColor(Color(0, 0, 0, 20));

    bool toCheckSelections = false;

    while (window.isOpen())
    {
        Button gdisplaybutton(gSize, Vector2f(400, 80), 30, gdc, Color::White);
        gdisplaybutton.setFont(font);
        gdisplaybutton.setPosition(Vector2f(450, 318));

        Event event; // Making an object "event" of the Event class

        while (window.pollEvent(event)) // Loop to manage when something changes in the console
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }

            else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
            {

                if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
                {

                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                    if (backbutton.buttonClicked(window)) // Using self defined function to check if the button was clicked
                    {
                        return;
                    }

                    else if (nextbutton.buttonClicked(window))
                    {
                        // Shd call a functions with all the variables.

                        // Check if the required conditions are met
                        if (multi > 0 && grid > 0 && !input.empty() && !gSize.empty())
                        {
                            bool newGame = true;
                            toCheckSelections = true;

                            if (grid == 4)
                            {
                                _4 game;
                                while (newGame == true)
                                {
                                    newGame = game.board(window, input, multi);
                                }
                            }

                            else if (grid == 6)
                            {
                                _6 game;
                                while (newGame == true)
                                {
                                    newGame = game.board(window, input, multi);
                                }
                            }

                        else if (grid == 8)
                        {
                            _8 game;
                            while (newGame == true)
                            {
                                newGame = game.board(window, input, multi);
                            }
                        }
                        }
                    }
            

            else if (grid4button.buttonClicked(window))
            {

                backbutton.setBackColor(Color(77, 143, 186));
                nextbutton.setBackColor(Color(77, 143, 186));
                multiple2button.setBackColor(Color(77, 143, 186));
                multiple3button.setBackColor(Color(77, 143, 186));
                multiple6button.setBackColor(Color(77, 143, 186));
                multiple7button.setBackColor(Color(77, 143, 186));
                gdisplaybutton.setBackColor(gdc = Color(6, 46, 81));
                gSize = "4x4";
                grid = 4;
            }
            else if (grid6button.buttonClicked(window))
            {

                backbutton.setBackColor(Color(132, 108, 188));
                nextbutton.setBackColor(Color(132, 108, 188));
                multiple2button.setBackColor(Color(132, 108, 188));
                multiple3button.setBackColor(Color(132, 108, 188));
                multiple6button.setBackColor(Color(132, 108, 188));
                multiple7button.setBackColor(Color(132, 108, 188));
                gdisplaybutton.setBackColor(gdc = Color(60, 52, 124));
                gSize = "6x6";
                grid = 6;
            }
            else if (grid8button.buttonClicked(window))
            {

                backbutton.setBackColor(Color(236, 46, 27));
                nextbutton.setBackColor(Color(236, 46, 27));
                multiple2button.setBackColor(Color(236, 46, 27));
                multiple3button.setBackColor(Color(236, 46, 27));
                multiple6button.setBackColor(Color(236, 46, 27));
                multiple7button.setBackColor(Color(236, 46, 27));
                gdisplaybutton.setBackColor(gdc = Color(125, 13, 13));
                gSize = "8x8";
                grid = 8;
            }
            else if (multiple2button.buttonClicked(window))
            {

                multi = 2;
            }
            else if (multiple3button.buttonClicked(window))
            {

                multi = 3;
            }
            else if (multiple6button.buttonClicked(window))
            {

                multi = 6;
            }
            else if (multiple7button.buttonClicked(window))
            {

                multi = 7;
            }
        }
        }
        else if (event.type == Event::TextEntered)
        {
            if (((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')) || event.text.unicode == ' ')
            {
                if (inputText.getLocalBounds().width + 10 < textBoxBackground.getSize().x) // Adjust the padding (10) as needed
                {
                    input += static_cast<char>(event.text.unicode);
                }
            }

            else if (event.text.unicode == 8 && !input.empty())
            {
                input.pop_back();
            }
            inputText.setString(input);
        }
        }

        window.clear(Color::White);

        // Textbox:
        window.draw(textBoxBackground);
        window.draw(inputText);
        window.draw(Name);
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
void firstScreen(RenderWindow &window)
{

    window.setFramerateLimit(60);

    // Open the next window
    while (window.isOpen())
    {

        // Handle events for the next window (if needed)
        Event Event;

        Button playbutton("PLAY", Vector2f(300, 80), 24, Color(6, 46, 81), Color::White);
        Button lbbutton("LEADER BOARD", Vector2f(300, 60), 24, Color(6, 46, 81), Color::White);

        Font font;
        font.loadFromFile("LEMONMILK.otf");
        playbutton.setFont(font);
        lbbutton.setFont(font);

        playbutton.setPosition(Vector2f(500, 218));
        lbbutton.setPosition(Vector2f(500, 308));

        while (window.pollEvent(Event))
        {
            // Handle events for the next window
            if (Event.type == Event::Closed)
            {
                window.close();
            }

            // (e.g., window closing event, user interactions, etc.)
            if (Event.type == Event::MouseButtonPressed)
            {
                if (Event.mouseButton.button == Mouse::Left)
                {
                    if (playbutton.buttonClicked(window))
                    {

                        mainMenu(window);
                    }
                    else if (lbbutton.buttonClicked(window))
                    {
                        beforeLeaderboard(window);
                    }
                }
            }
        }

        window.clear(Color(250, 247, 238));

        playbutton.drawTo(window);
        lbbutton.drawTo(window);

        window.display();
    }
}