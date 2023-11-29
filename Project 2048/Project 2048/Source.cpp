//Main SFML Code :
#include"W:/SFML/Project 2048/cppgraphics-1.0.1/src/cppgraphics.hpp"
#include<array>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp> //To Add Music 
using Grid = std::array<std::array<int, 4>, 4>;

using namespace std;
using namespace sf;
using namespace cg;
void draw(const Grid& grid)
{
	cg::clear();
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			cg::text_centered(std::to_string(grid[x][y]), 175 + x * 150, 175 + y * 150, 50);
		}
	}
}

int main()
{
	cg::create_window("2048", 800, 800);

	Grid grid;
	draw(grid);

	cg::wait_until_closed();
	return 0;
}

