g++ firstScreen.cpp -o firstScreen -lsfml-graphics -lsfml-window -lsfml-system && g++ -c firstScreen.cpp &&
g++ mainMenu.cpp -o mainMenu -lsfml-graphics -lsfml-window -lsfml-system && g++ -c mainMenu.cpp &&
g++ board4x4.cpp -o board4x4 -lsfml-graphics -lsfml-window -lsfml-system && g++ -c board4x4.cpp &&
g++ board6x6.cpp -o board6x6 -lsfml-graphics -lsfml-window -lsfml-system && g++ -c board6x6.cpp &&
g++ board8x8.cpp -o board8x8 -lsfml-graphics -lsfml-window -lsfml-system && g++ -c board8x8.cpp &&
g++ leaderboard.cpp -o leaderboard -lsfml-graphics -lsfml-window -lsfml-system && g++ -c leaderboard.cpp &&
g++ leaderboard4x4.cpp -o leaderboard4x4 -lsfml-graphics -lsfml-window -lsfml-system && g++ -c leaderboard4x4.cpp &&
g++ leaderboard6x6.cpp -o leaderboard6x6 -lsfml-graphics -lsfml-window -lsfml-system && g++ -c leaderboard6x6.cpp &&
g++ leaderboard8x8.cpp -o leaderboard8x8 -lsfml-graphics -lsfml-window -lsfml-system && g++ -c leaderboard8x8.cpp &&
./firstScreen