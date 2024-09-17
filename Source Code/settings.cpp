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
    Picture themeTexture("sun.png");

    Button soundbg(window, "", Vector2f(3, 5), 30, Color(6, 46, 81), Color::White);
    Button modebg(window, "", Vector2f(3, 5), 30, Color(6, 46, 81), Color::White);
    Button settings(window, "Settings", Vector2f(21, 15), 40, Color(6, 46, 81, 190), Color::White, 10, 5);
    Button sound(window, "", Vector2f(3, 5), 30, Color::Transparent, Color::White);
    Button themeButton(window, "", Vector2f(3, 5), 30, Color::Transparent, Color::White);
    Button purge(window, "Purge All Highscores", Vector2f(16, 5), 30, Color(212, 0, 0), Color::White);
    Button sfxbutton(window, "Sound Effects", Vector2f(16, 5), 30, Color(6, 46, 81), Color::White);
    Button backbutton(window, "Back", Vector2f(20, 5), 30, Color(6, 46, 81), Color::White);

    Font font;
    font.loadFromFile("Baloo.ttf");
    settings.setFont(font);
    soundbg.setFont(font);
    sound.setFont(font);
    themeButton.setFont(font);
    purge.setFont(font);
    sfxbutton.setFont(font);
    backbutton.setFont(font);

    settings.setPosition(window, Vector2f(50, 35));
    sound.setPosition(window, Vector2f(58.5, 48.5));
    soundbg.setPosition(window, Vector2f(58.5, 48.5));
    themeButton.setPosition(window, Vector2f(41.5, 54.8));
    modebg.setPosition(window, Vector2f(41.5, 54.8));
    purge.setPosition(window, Vector2f(52, 54.8));
    sfxbutton.setPosition(window, Vector2f(48, 48.5));
    backbutton.setPosition(window, Vector2f(50, 61.1));

    Picture background("4096 bg(light).png");

    background.setScale(window, Vector2f(51, 50));
    background.setPosition(window, Vector2f(0, 0));

    soundIcon.setPosition(window, Vector2f(57.5, 46.5));
    soundIcon.setScale(window, Vector2f(1, 2));

    themeTexture.setPosition(window, Vector2f(40.5, 52.8));
    themeTexture.setScale(window, Vector2f(1, 2));

    Music bgmusic;

    if (!bgmusic.openFromFile("bg.ogg")) {
        cout << "Error loading music file" << endl;
        return 1;
    }

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

    if (!lightTheme)
        themeTexture.SetTexture("moon.png");

    // Main loop that continues until the window is closed
    while (window.isOpen()) {
        // Create an event object to hold events
        Event event;

        // Process all events
        while (window.pollEvent(event)) {
            // Check for specific event types
            if (event.type == Event::Closed) { // If the close button is pressed
                window.close(); // Close the window
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    if (sound.cursorInbound(window)) {
                        if (isMusicPlaying) {
                            bgmusic.pause(); // Pause the music
                            soundIcon.SetTexture("mute.png");
                            replaceLine("settings.dat", 1, "0");
                        }
                        else {
                            bgmusic.play(); // Resume the music
                            soundIcon.SetTexture("s.png");
                            replaceLine("settings.dat", 1, "1");
                        }
                        isMusicPlaying = !isMusicPlaying; // Toggle the music status
                    }
                    else if (themeButton.cursorInbound(window)) {
                        if (lightTheme) {
                            themeTexture.SetTexture("sun.png");
                            themeTexture.setScale(window, Vector2f(1, 2));
                            replaceLine("settings.dat", 2, "0");
                            background.SetTexture("4096 bg(light).png");
                        }
                        else {
                            themeTexture.SetTexture("moon.png");
                            themeTexture.setScale(window, Vector2f(1, 2));
                            replaceLine("settings.dat", 2, "1");
                            background.SetTexture("4096 bg(dark).png");
                        }
                        lightTheme = !lightTheme;
                    }
                    else if (purge.cursorInbound(window)) {
                        window.close();
                    }
                    else if (sfxbutton.cursorInbound(window)) {
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
                    else if (backbutton.cursorInbound(window)) {
                        return 0;
                    }
                }
            }

        }


        background.drawTo(window);
        soundbg.drawTo(window);
        modebg.drawTo(window);

        // Buttons:
        settings.drawTo(window);
        sound.drawTo(window);
        themeButton.drawTo(window);
        purge.drawTo(window);
        sfxbutton.drawTo(window);
        backbutton.drawTo(window);

        themeTexture.drawTo(window);
        soundIcon.drawTo(window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
