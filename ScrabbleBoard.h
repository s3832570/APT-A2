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

   bool placeTile(Tile* tile, int row, int col);

   void displayBoard();

   bool checkPlacement(Tile* prevTile, Tile* currTile, Direction direction);

private:

   // Card* deck[MAXIMUM_DECK_SIZE];
   // // Card** deck;
   // int length;

   std::vector<std::vector<Tile*> > scrabbleBoard;
};

#endif // ASSIGN2_SCRABBLE_BOARD_H