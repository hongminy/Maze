#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include "Generator.hpp"
#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <random>


class Cell
{
 public:
  Cell(int coordinate_x, int coordinate_y);
  Cell (const Cell& cell);
  Cell ();
  void operator = (const Cell & cell);
  ~Cell();
  void print(std :: ostream & out);
  void visit ();
  bool is_visited();
  int coor_x();
  int coor_y();
 private:
  int x;
  int y;
  bool visited;
  
  
};


class Generator : public MazeGenerator
{

public:
  ~Generator();
  void generateMaze(Maze&maze);
  void createmultidimensionalarray(unsigned int first, unsigned int second);
  void print(std :: ostream & out);
private:
  bool all_visited();
  int maze_width;
  int maze_height;
  std::vector<Cell> turning_point;
  std::vector<std::vector<Cell>> multi_array;
  void get_dimension(Maze&maze);
  void generate_cell();
  int generate_random(int lower, int upper);
  void dig(Maze&maze, int start_x, int start_y);
  std :: vector<Direction> avaliable_move(int x, int y);
 
  
};

std :: ostream & operator << (std :: ostream & out, Cell cell);
std :: ostream & operator << (std :: ostream & out, Generator gen);









#endif
