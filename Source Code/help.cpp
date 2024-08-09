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


  Button help(window, "Settings", Vector2f(21, 15), 40, Color(6, 46, 81, 190), Color::White, 10, 5);

  Font font;
  font.loadFromFile("Baloo.ttf");
  help.setFont(font);

  help.setPosition(window, Vector2f(50, 35));


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
          // if (sound.coursorInbound(window)) {}

        }


      }

    }


    background.drawTo(window);

    // Buttons:
    help.drawTo(window);


    // Display the contents of the window
    window.display();
  }

  return 0;
}
