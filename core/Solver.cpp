#include <ics46/factory/DynamicFactory.hpp>
#include "Solver.hpp"
#include <iostream>
#include <algorithm>


// do other includes here
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, Solver, "HM's algorithm(Required)");

void Solver :: solveMaze(const Maze&maze, MazeSolution& mazeSolution)
{
  mazeSolution.restart(); // restart in case that it is not perfect
  get_dimension(maze);// get the width and height of the maze
  start_point = mazeSolution.getStartingCell();
  end_point = mazeSolution.getEndingCell();
  move(maze,mazeSolution,mazeSolution.getStartingCell().first,
  mazeSolution.getStartingCell().second);
}

void Solver :: get_dimension(const Maze&maze)
{
  maze_width = maze.getWidth();
  maze_height = maze.getHeight();
}

void Solver :: move(const Maze& maze, MazeSolution& mazesolution, int start_x,
                    int start_y)
{
  if (start_x == mazesolution.getEndingCell().first && start_y == mazesolution.getEndingCell().second)
    return;
  std :: vector <Direction> aval_move = get_valid_move(maze, start_x,start_y);
  std :: pair<int,int> current_position = mazesolution.getCurrentCell();
  visited.push_back(current_position);
  std :: cout << "current position: " << "x:"<<current_position.first<< " y:" << current_position.second << std :: endl;
  if (aval_move.size()!=0)
    {
      turning_point.push_back(current_position);

      mazesolution.extend(aval_move[0]);
      int x = start_x;
      int y = start_y;
      if (aval_move[0] == Direction :: right)
        x++;
      if (aval_move[0] == Direction :: left)
        x--;
      if (aval_move[0] == Direction :: up)
        y--;
      if (aval_move[0] == Direction :: down)
        y++;
      move(maze,mazesolution,x,y);
    }
  else
    {
      int co_x = turning_point[turning_point.size()-1].first;
      int co_y = turning_point[turning_point.size()-1].second;
      turning_point.erase(turning_point.end()-1);
      mazesolution.backUp();
      return move(maze,mazesolution,co_x,co_y);
    }
  
}
  
bool Solver :: check_visited(const std :: vector<std::pair<int,int>> & v, const std::pair<int,int>& p)

{
  return find(v.begin(),v.end(),p)!=v.end();
}
std :: vector <Direction> Solver :: get_valid_move(const Maze& maze, int x, int y)
{
  std :: vector <Direction> temp;
  if (0 <= x+1 && x+1 < maze_width && 0 <= y && y < maze_height)
  {
    if (!maze.wallExists(x,y,Direction::right)&&!check_visited(visited,std::pair<int,int>{x+1,y}))
      {
        temp.push_back(Direction::right);
        std :: cout << "right" << std :: endl;
      }
  }
  
  if (0 <= x && x < maze_width && 0 <= y-1 && y-1 < maze_height)
  {
    if (!maze.wallExists(x,y,Direction :: up)&&!check_visited(visited,std::pair<int,int>{x,y-1}))
      {
        temp.push_back(Direction::up);
        std :: cout << "up" << std :: endl;
      }
  }
  
  if (0 <= x && x < maze_width && 0 <= y+1 && y+1 < maze_height)
  {
    if (!maze.wallExists(x,y,Direction :: down) &&!check_visited(visited,std::pair<int,int>{x,y+1}))
      {
        temp.push_back(Direction::down);
        std :: cout << "down" << std :: endl;
      }
  }
  
  if (0 <= x-1 && x-1 < maze_width && 0 <= y && y < maze_height)
  {

    if (!maze.wallExists(x,y,Direction::left) &&!check_visited(visited,std::pair<int,int>{x-1,y}))
      {
        temp.push_back(Direction::left);
        std :: cout << "left" << std :: endl;
      }
  }  

  return temp;
}
 
Solver :: ~Solver()
{

}

