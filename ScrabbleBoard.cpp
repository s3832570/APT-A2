#include <iostream>

#include "ScrabbleBoard.h"

ScrabbleBoard::ScrabbleBoard()
{
   for (int i = 0; i < SCRABBLE_BOARD_LENGTH; i++)
   {
      std::vector<Tile *> newRow;

      for (int j = 0; j < SCRABBLE_BOARD_LENGTH; j++)
      {
         newRow.push_back(new Tile(' ', 0));
      }

      scrabbleBoard.push_back(newRow);
   }

}

ScrabbleBoard::ScrabbleBoard(ScrabbleBoard &other)
{
}

ScrabbleBoard::~ScrabbleBoard()
{
}

Tile *ScrabbleBoard::get(int row, char col)
{
   return nullptr;
}

bool ScrabbleBoard::placeTile(Tile *tile, int row, int col)
{
   bool placedTile = false;

   if (scrabbleBoard[row][col+1]->getLetter() == ' ') {
      scrabbleBoard[row][col+1] = tile;
      placedTile = true;
   } else {
      placedTile = false;
   }

   return placedTile;
}

// display scrabble board
void ScrabbleBoard::displayBoard()
{
   // Displays the board
   std::cout << "     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14" << std::endl;
   std::cout << "----------------------------------------------------------------" << std::endl;

   char coord = 'A';

   for (int i = 0; i < scrabbleBoard.size(); i++)
   {
      std::cout << coord;
      for (int j = 0; j < scrabbleBoard[i].size(); j++)
      {
         std::cout << scrabbleBoard[i][j]->getLetter() << " | ";
      }
      std::cout << "  |" << std::endl;
      coord++;
   }
}

bool checkPlacement(Tile* prevTile, Tile* currTile, Direction direction) {
   return false;
}