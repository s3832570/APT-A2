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

   boardEmpty = true;
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

   if (scrabbleBoard[row][col + 1]->getLetter() == ' ')
   {
      scrabbleBoard[row][col + 1] = tile;
      placedTile = true;
   }
   else
   {
      placedTile = false;
   }

   boardEmpty = false;

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

bool ScrabbleBoard::checkPlacement(std::vector<std::string> coords)
{
   bool retVal = false;

   int sameRow = 0;
   int sameCol = 0;

   std::string firstCoord = " ";
   int row = 0;
   int col = 0;

   // Adds up how many of the coordinates are in a line
   for (std::string &c : coords)
   {
      std::string coord = c.substr(11, 12);
      if (firstCoord != " ")
      {
         if (firstCoord.at(0) == coord.at(0))
         {
            sameRow++;
         }

         if (firstCoord.at(1) == coord.at(1))
         {
            sameCol++;
         }
      }
      else
      {
         firstCoord = coord;
         row = findRow(coord.at(0));
         col = coord.at(1) - '0';
         sameRow++;
         sameCol++;
      }
   }

   // if all of the coordinates are in a line either horizontally or verticlly
   // return true, otherwise placement is illegal
   if (sameRow == coords.size() || sameCol == coords.size())
   {
      retVal = true;
   }

   // if the board isn't empty, make sure new word connects with existing word
   if (!boardEmpty && retVal)
   {
      retVal = false;
      for (std::string &c : coords)
      {
         std::string coord = c.substr(11, 12);
         row = findRow(coord.at(0));
         col = coord.at(1) - '0';

         // checking the surroundings of each tile placed
         // to make sure the word connects with an
         // existing word
         if (scrabbleBoard[row][col + 1]->getLetter() != ' ')
         {
            retVal = true;
         }
         else if (scrabbleBoard[row][col - 1]->getLetter() != ' ')
         {
            retVal = true;
         }
         else if (scrabbleBoard[row + 1][col]->getLetter() != ' ')
         {
            retVal = true;
         }
         else if (scrabbleBoard[row - 1][col]->getLetter() != ' ')
         {
            retVal = true;
         }
      }
   }

   return retVal;
}

int ScrabbleBoard::findRow(char c)
{
   char c2 = 'A';
   int row = 0;
   while (c2 != c)
   {
      row++;
      c2++;
   }

   return row;
}