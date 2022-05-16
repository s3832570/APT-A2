#ifndef ASSIGN2_SCRABBLE_BOARD_H
#define ASSIGN2_SCRABBLE_BOARD_H 

#include <istream>
#include <string>
#include <vector>

#include "Tile.h"

#define SCRABBLE_BOARD_LENGTH 15 

enum Direction {
   RIGHT,
   LEFT,
   UP,
   DOWN
};

class ScrabbleBoard {
public:
   ScrabbleBoard();
   ScrabbleBoard(ScrabbleBoard& other);
   ~ScrabbleBoard();

   Tile* get(int row, char col);

   int getSize();

   bool placeTile(Tile* tile, int row, int col);

   void displayBoard();

   std::string saveState();

   bool checkPlacement(std::vector<std::string> coords, int* points);

   int findRow(char c);

   void remove(int row, int col);

   std::vector<std::vector<Tile*> > getBoard();

private:

   std::vector<std::vector<Tile*> > scrabbleBoard;

   bool                             boardEmpty;
};

#endif // ASSIGN2_SCRABBLE_BOARD_H