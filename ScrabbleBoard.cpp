#include <iostream>

#include "ScrabbleBoard.h"
#include "utils.h"

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
   for (int i = 0; i < SCRABBLE_BOARD_LENGTH; i++)
   {
      for (int j = 0; j < SCRABBLE_BOARD_LENGTH; j++)
      {
         delete scrabbleBoard[i][j];
      }
   }
}

Tile *ScrabbleBoard::get(int row, char col)
{
   return nullptr;
}

int ScrabbleBoard::getSize() {
   return scrabbleBoard.size();
}

bool ScrabbleBoard::placeTile(Tile *tile, int row, int col)
{
   bool placedTile = false;

   if (scrabbleBoard[row][col]->getLetter() == ' ')
   {
      scrabbleBoard[row][col] = tile;
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

   for (int i = 0; i < int(scrabbleBoard.size()); i++)
   {
      std::cout <<" "<<coord <<" | ";
      for (int j = 0; j < int(scrabbleBoard[i].size()); j++)
      {
         std::cout << scrabbleBoard[i][j]->getLetter() << " | ";
      }
      std::cout << ""<< std::endl;
      coord++;
   }
}

std::string ScrabbleBoard::saveState() {
   std::string save;
   
   // Displays the board
   save = save + "     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14";
   save = save + "\n" + "----------------------------------------------------------------" + "\n";

   char coord = 'A';

   for (int i = 0; i < int(scrabbleBoard.size()); i++)
   {
      save = save + " " +  coord + " | ";
      for (int j = 0; j < int(scrabbleBoard[i].size()); j++)
      {
         save = save + scrabbleBoard[i][j]->getLetter() + " | ";
      }
      save = save + "\n";

      coord++;
   }

   return save;
}

bool ScrabbleBoard::checkPlacement(std::vector<std::string> coords, int* points)
{
   int p = *points;
   /**
    * TODO:
    * Get points from surrounding tiles
    * 
    */
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
         col = getCol(c);
         sameRow++;
         sameCol++;
      }
   }
   // if all of the coordinates are in a line either horizontally or verticlly
   // return true, otherwise placement is illegal
   if (sameRow == int(coords.size()) || sameCol == int(coords.size()))
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
         col = getCol(c);
         // checking the surroundings of each tile placed
         // to make sure the word connects with an
         // existing word

         if (col < 14 && scrabbleBoard[row][col + 1]->getLetter() != ' ')
            {
            p = p + getValue(scrabbleBoard[row][col + 1]->getLetter());
            retVal = true;
            }

         else if (col > 0 && scrabbleBoard[row][col - 1]->getLetter() != ' ') {
            p = p + getValue(scrabbleBoard[row][col - 1]->getLetter());
            retVal = true;
            }
      
         else if (row < 14 && scrabbleBoard[row + 1][col]->getLetter() != ' ')
         {
            p = p + getValue(scrabbleBoard[row + 1][col]->getLetter());
            retVal = true;
         }
         else if (row > 0 && scrabbleBoard[row-1][col]->getLetter() != ' ') {
            p = p + getValue(scrabbleBoard[row-1][col]->getLetter());
            retVal = true;
            }

      }
   }
   *points = p;
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

std::vector<std::vector<Tile*> > ScrabbleBoard::getBoard() {
   return scrabbleBoard;
}