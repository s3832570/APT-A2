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

   // std::cout << "getting here" << std::endl;
}

ScrabbleBoard::ScrabbleBoard(ScrabbleBoard &other)
{
}

ScrabbleBoard::~ScrabbleBoard()
{
}

// vector of vectors for scrabble board.
// needs implementation of passing in tiles.
void ScrabbleBoard::newScrabbleBoard()
{

   // Scrabble board is 15x15, so 15 vectors 15 tiles long

   // Fill the inner vector with char for first element, then insert it into the outer vector
   // for (char i = 'A'; i < 'P'; i++)
   // {
   //    std::vector<Tile*> temp;
   //    char a = ' ';
   //    for (int j = 0; j < 16; j++)
   //    {

   //       if (j == 0)
   //       {
   //          temp.push_back(i);
   //       }

   //       temp.push_back(a);
   //    }
   //    scrabbleBoard.push_back(temp);
   // }
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

// display empty scrabble board.
// can only display empty board and requires changes to pass in tiles.
void ScrabbleBoard::displayBoard()
{
   // Displays the empty board
   std::cout << "     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14" << std::endl;
   std::cout << "----------------------------------------------------------------" << std::endl;
   // for (int i = 0; i < scrabbleBoard.size(); i++)
   // {
   //    for (int j = 0; j < scrabbleBoard[i].size(); j++)
   //    {
   //       std::cout << scrabbleBoard[i][j] << " | ";
   //    }
   //    std::cout << std::endl;
   // }

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