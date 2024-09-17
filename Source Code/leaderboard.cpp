
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

int main() {
  RenderWindow window(VideoMode::getDesktopMode(), "4096", Style::Close | Style::Titlebar);
  string fileName;

  string l1, l2, l3, l4, l5;
  ifstream leaderboardFile(fileName);
  if (leaderboardFile.is_open()) {
    getline(leaderboardFile, l1);
    l1 = "1.\t" + l1;
    getline(leaderboardFile, l2);
    l2 = "2.\t" + l2;
    getline(leaderboardFile, l3);
    l3 = "3.\t" + l3;
    getline(leaderboardFile, l4);
    l4 = "4.\t" + l4;
    getline(leaderboardFile, l5);
    l5 = "5.\t" + l5;

    leaderboardFile.close();
  }
  else {
    cerr << "Unable To Open The File!" << endl;
  }

  // "Text displayed on the button", Vector2f(buttonSizeX, buttonSizeY), Font Size, Color::buttonColor, Color::textColor

  // Creating an object of the Button class named "button" and specifying its properties
  Button rankButt(window, "RANK", Vector2f(8, 7), 24, Color(6, 46, 81, 190), Color::White);
  Button nameButton(window, "NAME", Vector2f(19, 7), 24, Color(6, 46, 81, 190), Color::White);
  Button scoreButton(window, "SCORE", Vector2f(8, 7), 24, Color(6, 46, 81, 190), Color::White);
  Button back(window, "BACK", Vector2f(12, 7), 24, Color(6, 46, 81, 190), Color::White);
  //Rank buttons: (takes up the complete width of each transparent button placeholder)
  Button rank1(window, l1, Vector2f(36, 7), 24, Color(154, 197, 219), Color::White);
  Button rank2(window, l2, Vector2f(36, 7), 24, Color(238, 201, 0), Color::White);
  Button rank3(window, l3, Vector2f(36, 7), 24, Color(202, 202, 202), Color::White);
  Button rank4(window, l4, Vector2f(36, 7), 24, Color(185, 97, 30), Color::White);
  Button rank5(window, l5, Vector2f(36, 7), 24, Color(205, 127, 50), Color::White);
  //Rank No.(to remain definite)
  Button r1(window, "1.", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button r2(window, "2.", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button r3(window, "3.", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button r4(window, "4.", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button r5(window, "5.", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  //Name place holders (shd updated with the name of the user that has the highest score)
  Button name1(window, "TEST", Vector2f(18, 7), 25, Color::Transparent, Color::White);
  Button name2(window, "TEST", Vector2f(18, 7), 25, Color::Transparent, Color::White);
  Button name3(window, "TEST", Vector2f(18, 7), 25, Color::Transparent, Color::White);
  Button name4(window, "TEST", Vector2f(18, 7), 25, Color::Transparent, Color::White);
  Button name5(window, "TEST", Vector2f(18, 7), 25, Color::Transparent, Color::White);
  //Score (shd updated with the score of the user that has the highest score)
  Button s1(window, "SIKE", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button s2(window, "SIKE", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button s3(window, "SIKE", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button s4(window, "SIKE", Vector2f(7, 7), 25, Color::Transparent, Color::White);
  Button s5(window, "SIKE", Vector2f(7, 7), 25, Color::Transparent, Color::White);

  // To display bg image
  Picture background("4096 bg(light).png");

  background.SetTexture("4096 bg(light).png");
  background.setScale(window, Vector2f(51, 50));
  background.setPosition(window, Vector2f(0, 0));

  // Making an object of the Font class called "font"
  Font font;

  // Loading the font for the button
  font.loadFromFile("Baloo.ttf");

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
  r1.setFont(font);
  r2.setFont(font);
  r3.setFont(font);
  r4.setFont(font);
  r5.setFont(font);
  name1.setFont(font);
  name2.setFont(font);
  name3.setFont(font);
  name4.setFont(font);
  name5.setFont(font);
  s1.setFont(font);
  s2.setFont(font);
  s3.setFont(font);
  s4.setFont(font);
  s5.setFont(font);

  // Setting button position
  rankButt.setPosition(window, Vector2f(36, 25));
  nameButton.setPosition(window, Vector2f(50, 25));
  scoreButton.setPosition(window, Vector2f(64, 25));
  rank1.setPosition(window, Vector2f(50, 33.0f));
  rank2.setPosition(window, Vector2f(50, 41.0f));
  rank3.setPosition(window, Vector2f(50, 49.0f));
  rank4.setPosition(window, Vector2f(50, 57.0f));
  rank5.setPosition(window, Vector2f(50, 65.0f));
  back.setPosition(window, Vector2f(50, 73));
  r1.setPosition(window, Vector2f(36, 33.0f));
  r2.setPosition(window, Vector2f(36, 41.0f));
  r3.setPosition(window, Vector2f(36, 49.0f));
  r4.setPosition(window, Vector2f(36, 57.0f));
  r5.setPosition(window, Vector2f(36, 65.0f));
  name1.setPosition(window, Vector2f(50, 33.0f));
  name2.setPosition(window, Vector2f(50, 41.0f));
  name3.setPosition(window, Vector2f(50, 49.0f));
  name4.setPosition(window, Vector2f(50, 57.0f));
  name5.setPosition(window, Vector2f(50, 65.0f));
  s1.setPosition(window, Vector2f(64, 33.0f));
  s2.setPosition(window, Vector2f(64, 41.0f));
  s3.setPosition(window, Vector2f(64, 49.0f));
  s4.setPosition(window, Vector2f(64, 57.0f));
  s5.setPosition(window, Vector2f(64, 65.0f));

  window.setFramerateLimit(60); // Setting the frame rate to 60 fps

  while (window.isOpen()) {
    Event event; // Making an object "event" of the Event class

    while (window.pollEvent(event)) // Loop to manage when something changes in the console
    {
      if (event.type == Event::Closed) {
        window.close();
      }

      else if (event.type == Event::MouseButtonPressed) // Checking if mouse was clicked
      {

        if (event.mouseButton.button == Mouse::Left) // Checking if the left mouse button was clicked
        {

          if (back.cursorInbound(window)) // Using self defined function to check if the button was clicked
          {
            return 0; // Closes the window
          }
        }
      }
    }

    background.drawTo(window);

    rankButt.drawTo(window);
    nameButton.drawTo(window);
    scoreButton.drawTo(window);
    rank1.drawTo(window);
    rank2.drawTo(window);
    rank3.drawTo(window);
    rank4.drawTo(window);
    rank5.drawTo(window);
    r1.drawTo(window);
    r2.drawTo(window);
    r3.drawTo(window);
    r4.drawTo(window);
    r5.drawTo(window);
    name1.drawTo(window);
    name2.drawTo(window);
    name3.drawTo(window);
    name4.drawTo(window);
    name5.drawTo(window);
    s1.drawTo(window);
    s2.drawTo(window);
    s3.drawTo(window);
    s4.drawTo(window);
    s5.drawTo(window);
    back.drawTo(window);


    window.display();
  }

}