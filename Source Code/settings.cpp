#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "classes.cpp"

using namespace std;
using namespace sf;


int replaceLine(const std::string& filename, int lineNumber, const std::string& newLine) {
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
        return 1;
    }

    for (const auto& l : lines) {
        outFile << l << std::endl;
    }

    outFile.close();

    return 0;
}

int main() {
    RenderWindow window(VideoMode::getDesktopMode(), "4096", Style::Close | Style::Titlebar);

    ifstream file("settings.dat");
    // Load textures for icons
    Picture soundIcon("s.png");
    Picture themeTexture("moon.png");


    Button settings("Settings", Vector2f(400, 150), 40, Color(6, 46, 81, 190), Color::White, 10, 5);
    Button sound("", Vector2f(50, 50), 30, Color::Transparent, Color::White);
    Button themeButton("", Vector2f(50, 50), 30, Color::Transparent, Color::White);
    Button purge("Purge All Highscores", Vector2f(300, 50), 30, Color(212, 0, 0), Color::White);
    Button sfxbutton("Sound Effects", Vector2f(300, 50), 30, Color(6, 46, 81), Color::White);
    Button backbutton("Back", Vector2f(365, 50), 30, Color(6, 46, 81), Color::White);

    Font font;
    font.loadFromFile("Baloo.ttf");
    settings.setFont(font);
    sound.setFont(font);
    themeButton.setFont(font);
    purge.setFont(font);
    sfxbutton.setFont(font);
    backbutton.setFont(font);

    settings.setPosition(Vector2f(755, 300));
    sound.setPosition(Vector2f(1085, 500));
    themeButton.setPosition(Vector2f(770, 570));
    purge.setPosition(Vector2f(835, 570));
    sfxbutton.setPosition(Vector2f(770, 500));
    backbutton.setPosition(Vector2f(770, 640));

    Picture background("4096 bg(dark).png");

    background.setScale(Vector2f(window.getSize().x, window.getSize().y));
    background.setPosition(Vector2f(0, 0));

    soundIcon.setPosition(Vector2f(sound.getPosition().x + 5.f, sound.getPosition().y + 5.f));
    soundIcon.setScale(Vector2f(sound.getSize().x - 10.f, sound.getSize().y - 10.f));

    themeTexture.setPosition(Vector2f(themeButton.getPosition().x + 5.f, themeButton.getPosition().y + 5.f));
    themeTexture.setScale(Vector2f(themeButton.getSize().x - 10.f, themeButton.getSize().y - 10.f));

    Music bgmusic;

    if (!bgmusic.openFromFile("bg.ogg")) {
        cout << "Error loading music file" << endl;
        return 1;
    }

    RectangleShape soundbg;
    soundbg.setSize(Vector2f(50, 50));
    soundbg.setFillColor(Color(6, 46, 81));
    soundbg.setPosition(sound.getPosition());

    RectangleShape modebg;
    modebg.setSize(Vector2f(50, 50));
    modebg.setFillColor(Color(6, 46, 81));
    modebg.setPosition(themeButton.getPosition());

    bool isMusicPlaying;
    bool lightTheme;
    bool sfx;

    string temp;

    if (file.is_open()) {
        file >> isMusicPlaying >> lightTheme >> sfx;
    }
    else {
        cout << "Error opening file" << endl;
        return 1;
    }
    file.close();

    if (!isMusicPlaying)
        soundIcon.SetTexture("mute.png");

    if (lightTheme) {
        themeTexture.SetTexture("sun.png");
        themeTexture.setScale(Vector2f(themeButton.getSize().x - 10.f, themeButton.getSize().y - 10.f));
        background.SetTexture("4096 bg.png");
    }
    // Main loop that continues until the window is closed
    while (window.isOpen()) {
        // Create an event object to hold events
        sf::Event event;

        // Process all events
        while (window.pollEvent(event)) {
            // Check for specific event types
            if (event.type == Event::Closed) { // If the close button is pressed
                window.close(); // Close the window
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (sound.coursorInbound(window)) {
                        if (isMusicPlaying) {
                            bgmusic.pause(); // Pause the music
                            soundIcon.SetTexture("mute.png");
                            soundIcon.setScale(Vector2f(sound.getSize().x - 10.f, sound.getSize().y - 10.f));
                            replaceLine("settings.dat", 1, "0");
                        }
                        else {
                            bgmusic.play(); // Resume the music
                            soundIcon.SetTexture("s.png");
                            soundIcon.setScale(Vector2f(sound.getSize().x - 10.f, sound.getSize().y - 10.f));
                            replaceLine("settings.dat", 1, "1");
                        }
                        isMusicPlaying = !isMusicPlaying; // Toggle the music status
                    }
                    else if (themeButton.coursorInbound(window)) {
                        if (lightTheme) {
                            themeTexture.SetTexture("moon.png");
                            themeTexture.setScale(Vector2f(themeButton.getSize().x - 10.f, themeButton.getSize().y - 10.f));
                            replaceLine("settings.dat", 2, "1");
                            background.SetTexture("4096 bg(dark).png");
                        }
                        else {

                            themeTexture.SetTexture("sun.png");
                            themeTexture.setScale(Vector2f(themeButton.getSize().x - 10.f, themeButton.getSize().y - 10.f));
                            replaceLine("settings.dat", 2, "0");
                            background.SetTexture("4096 bg.png");
                        }
                        lightTheme = !lightTheme;
                    }
                    else if (purge.coursorInbound(window)) {
                        ofstream outfile("leaderboard4x4.dat");
                        if (outfile.is_open()) {
                            outfile << "0" << endl << "0" << endl << "0" << endl << "0" << endl << "0" << endl;
                        }
                        else
                            cout << "Error opening file" << endl;
                        outfile.close();

                        outfile.open("leaderboard6x6.dat");
                        if (outfile.is_open()) {
                            outfile << "0" << endl << "0" << endl << "0" << endl << "0" << endl << "0" << endl;
                        }
                        else
                            cout << "Error opening file" << endl;
                        outfile.close();

                        outfile.open("leaderboard8x8.dat");
                        if (outfile.is_open())
                            outfile << "0" << endl << "0" << endl << "0" << endl << "0" << endl << "0" << endl;
                        else
                            cout << "Error opening file" << endl;
                        outfile.close();
                    }
                    else if (sfxbutton.coursorInbound(window)) {
                        if (sfx) {
                            replaceLine("settings.dat", 3, "0");
                            sfxbutton.setText("Sound Effects: Off");
                        }
                        else {
                            replaceLine("settings.dat", 3, "1");
                            sfxbutton.setText("Sound Effects: On");
                        }
                        sfx = !sfx;
                    }
                    else if (backbutton.coursorInbound(window)) {
                        return 0;
                    }
                }
            }

        }


        background.drawTo(window);
        window.draw(soundbg);
        soundIcon.drawTo(window);
        window.draw(modebg);
        themeTexture.drawTo(window);

        // Buttons:
        settings.drawTo(window);
        sound.drawTo(window);
        themeButton.drawTo(window);
        purge.drawTo(window);
        sfxbutton.drawTo(window);
        backbutton.drawTo(window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
