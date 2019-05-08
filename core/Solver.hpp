#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
// do other includes here


class Solver : public MazeSolver 
{
public:
  ~Solver();
  void solveMaze(const Maze&maze, MazeSolution & mazeSolution);
  void get_dimension(const Maze&maze);

private:
  int maze_width;
  int maze_height;
  bool check_visited(const std :: vector<std::pair<int,int>> & v, const std::pair<int,int>& p);
  void move(const Maze&maze, MazeSolution &mazesolution, int start_x,int start_y);
  std :: vector <Direction> get_valid_move(const Maze&maze,int x,int y);
  std :: pair<int, int> start_point;
  std :: pair<int, int> end_point;
  std :: vector< std :: pair <int,int>> turning_point;
  std :: vector< std :: pair<int,int>> visited;
};




#endif
