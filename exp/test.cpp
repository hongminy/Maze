#include <memory>
#include "MazeFactory.hpp"
#include "Generator.hpp"
#include <iostream>


int main()
{
	std::unique_ptr<Maze> maze = MazeFactory{}.createMaze(10, 10);

        Generator generator;
        generator.generateMaze(*maze);
        return 0;
}
