#ifndef ASSIGN2_SCRABBLE_BOARD_H
#define ASSIGN2_SCRABBLE_BOARD_H 

#include <istream>
#include <string>
#include <vector>

#include "Tile.h"

#define SCRABBLE_BOARD_LENGTH 15 

class ScrabbleBoard {
public:
   ScrabbleBoard();
   ScrabbleBoard(ScrabbleBoard& other);
   ~ScrabbleBoard();

   void newScrabbleBoard();

   Tile* get(int row, char col);

   void add(Tile* tile, int row, char col);

   void displayBoard();

private:

   // Card* deck[MAXIMUM_DECK_SIZE];
   // // Card** deck;
   // int length;

   std::vector<std::vector<Tile*> > scrabbleBoard;
};

#endif // ASSIGN2_SCRABBLE_BOARD_H