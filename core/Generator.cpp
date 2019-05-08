#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include <random>
#include "MazeGenerator.hpp"
#include "Generator.hpp"
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, Generator, "HM's Algorithm(Required)");

Generator :: ~Generator(){};

void Generator :: generateMaze(Maze& maze)
{
    
    maze.addAllWalls(); // in case that the passed in maze is not perfect
    get_dimension(maze);
    createmultidimensionalarray(maze_width, maze_height);
    dig(maze,0,0);
} 

void Generator :: print(std :: ostream & out)
{
    // for debug use
    for (int i = 0; i < maze_width; i++)
      {
        for (int j = 0; j < maze_height; j++)
          {
            std :: cout << multi_array[i][j] << std::endl;
          }
      }
}

void Generator :: get_dimension(Maze&maze)
{
    maze_width = maze.getWidth();
    maze_height = maze.getHeight();
}

void Generator ::  createmultidimensionalarray
(unsigned int first, unsigned int second)

{
  for (int i = 0; i < first; i++)
    {
      std :: vector <Cell> temp_v;
      for (int j = 0; j < second; ++j)
        {
          temp_v.push_back( Cell{j,i});
        }
      multi_array.push_back(temp_v);
    }

}

int Generator :: generate_random(int lower, int upper)
{
	std::random_device device; // this is a limited source of entropy
	std::default_random_engine engine{device()};
	std::uniform_int_distribution<int> distribution{lower,upper};
        return distribution(engine);

}

bool Generator :: all_visited()
{
  for (int i = 0; i < maze_width; i++)
      {
        for (int j = 0; j < maze_height; j++)
          {
          if (multi_array[i][j].is_visited() == false)
            return multi_array[i][j].is_visited();
          }

      }
    return true;
}

void Generator :: dig(Maze&maze, int start_x, int start_y)
{
    Cell start_point;
    if (all_visited())
      return;
    multi_array[start_x][start_y].visit();
    start_point = multi_array[start_x][start_y];
     
    std :: vector<Direction> aval_move = avaliable_move(start_x,start_y);
    if (aval_move.size() !=  0)
      {

        int random = generate_random(0, aval_move.size()-1);
        maze.removeWall(start_x, start_y, aval_move[random]);

        int x = start_x;
        int y = start_y;
        if (aval_move[random] == Direction :: right)
          x = start_x+1;
        if (aval_move[random] == Direction :: left)
          x = start_x-1;
        if (aval_move[random] == Direction :: up)
          y = start_y-1;
        if (aval_move[random] == Direction :: down)
          y = start_y+1;
        turning_point.push_back(Cell{start_x,start_y});
        dig(maze,x,y);
      }
    else
      {
      int co_x = turning_point[turning_point.size()-1].coor_x();
      int co_y = turning_point[turning_point.size()-1].coor_y();
      turning_point.erase(turning_point.end()-1);
      return dig(maze,co_x,co_y);
      }
    
}

std :: vector <Direction> Generator :: avaliable_move(int x, int y)
{
  std :: vector <Direction> temp;
  if (0 <= x+1 && x+1 < maze_width && 0 <= y && y < maze_height)
  {
    if (!multi_array[x+1][y].is_visited())
      {
        temp.push_back(Direction::right);
      }
  }
  
  if (0 <= x && x < maze_width && 0 <= y-1 && y-1 < maze_height)
  {
    if (!multi_array[x][y-1].is_visited())
      {
        temp.push_back(Direction::up);

      }
  }
  
  if (0 <= x && x < maze_width && 0 <= y+1 && y+1 < maze_height)
  {
    if (!multi_array[x][y+1].is_visited())
      {
        temp.push_back(Direction::down);

      }
  }
  
  if (0 <= x-1 && x-1 < maze_width && 0 <= y && y < maze_height)
  {

    if (!multi_array[x-1][y].is_visited())
      {
        temp.push_back(Direction::left);

      }
  }
  

  return temp;
}


void Generator :: generate_cell()
{
    // generate the corrosponding cell array into buf
    createmultidimensionalarray(maze_width, maze_height); 
}



Cell :: Cell(int coordinate_x, int coordinate_y)
    : x(coordinate_x), y(coordinate_y), visited(false)
{
}

Cell :: ~Cell(){}



void Cell :: print(std :: ostream & out)
  {
    // for debug use
    std :: cout << "x: " << x << " y: " << y << std :: endl;
  }

Cell :: Cell(const Cell& cell)
{
  x = cell.x;
  y = cell.y;
  visited = cell.visited;

}

Cell :: Cell(){}

void Cell :: operator =(const Cell & cell)
{
  x = cell.x;
  y = cell.y;
  visited = cell.visited;

}

int Cell :: coor_x()
{
  return x;
}

int Cell :: coor_y()
{
  return y;
}

void Cell :: visit()
{
  visited = true;
}

bool Cell :: is_visited()
{
  return visited;
}

std :: ostream &  operator << (std :: ostream & out, Cell cell)
{
        cell.print(out);
	return out;
}

std :: ostream &  operator << (std :: ostream & out, Generator gen)
{
        gen.print(out);
	return out;
}



