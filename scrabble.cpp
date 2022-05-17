#include "LinkedList.h"
#include "Player.h"
#include "ScrabbleBoard.h"
#include "TileBag.h"
#include "utils.h"

#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <sstream>

#define COMMAND_STRING_LENGTH 12
#define INT_OF_LETTER 6

#define EXIT_SUCCESS 0

/**
 * TODO:
 * - make it so can't do coords past board
 * - user input checking for place tile
 * - replace letter thats not in hand
 * - tests
 */

void mainMenu();
void newGame();
void loadGame();
Player *loadPlayer(std::ifstream &infile);
ScrabbleBoard *loadBoard(std::ifstream &infile);
TileBag *loadTileBag(std::ifstream &infile);
void startGame(TileBag *tileBag, Player *player1, Player *player2);
int getValue(char c);
void playGame(TileBag *tileBag, Player *player1, Player *player2, Player *currentPlayer, ScrabbleBoard *scrabbleBoard);
bool placeTiles(PlayerHand *playerHand, std::vector<std::string> commands, ScrabbleBoard *board, Player *player);
bool checkPlayerHasTiles(std::vector<std::string> commands, PlayerHand *playerHand);
bool gameIsEndable(TileBag *tileBag, Player *player1, Player *player2);

int main(void)
{
   mainMenu();

   return EXIT_SUCCESS;
}

void mainMenu()
{
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   int userMenuInput = 0;
   while (userMenuInput != 1 && userMenuInput != 4)
   {
      std::cout << "Menu" << std::endl;
      std::cout << "----" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Credits (Show student information)" << std::endl;
      std::cout << "4. Quit" << std::endl;

      std::cout << std::endl;
      std::cout << "> ";

      while ((!(std::cin >> userMenuInput) || !(userMenuInput >= 1 && userMenuInput <= 4)) && !std::cin.eof())
      {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
         std::cin.clear();
         std::cin.ignore(100, '\n');
      }

      if (userMenuInput == 1)
      {
         newGame();
      }

      if (userMenuInput == 2)
      {
         loadGame();
      }

      if (userMenuInput == 3)
      {
         viewCredits();
      }

      // TESTING FUNCTION ONLY
      if (userMenuInput == 4)
      {
         // quit
      }
   }
   std::cout << std::endl;
   std::cout << "Goodbye!" << std::endl;
}

void newGame()
{
   TileBag *tileBag = new TileBag();

   // Reading in new tile bag
   std::fstream infile("ScrabbleTiles.txt");
   char letter;
   int value;
   while (infile >> letter >> value)
   {
      tileBag->addNewTile(new Tile(letter, value));
   }
   tileBag->shuffleBag();

   std::string player1Name;
   std::string player2Name;

   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   inputName(&player1Name);
   Player *player1 = new Player(player1Name);
   std::cout << std::endl;

   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   inputName(&player2Name);
   Player *player2 = new Player(player2Name);
   std::cout << std::endl;

   std::cout << "Let's Play!" << std::endl;
   std::cout << std::endl;

   startGame(tileBag, player1, player2);
}

void loadGame()
{
    std::cout << "Enter the filenane for which to load a game! " << std::endl;
   std::cout << "> ";
   std::string fileName;
   std::string test;
   std::cin >> fileName;

   std::ifstream file(fileName);

   if(file.good()) {
      Player *playerOne = loadPlayer(file);
      Player *playerTwo = loadPlayer(file);
      Player *currentPlayer;
      ScrabbleBoard *board = loadBoard(file);
      TileBag *bag = loadTileBag(file);
      std::string currentPlayerName;
      getline(file, currentPlayerName);
      if (currentPlayerName == playerOne->getName())
      {
         currentPlayer = playerOne;
      }
      else
      {
         currentPlayer = playerTwo;
      }
      std::cout << ""<< std::endl;
      std::cout << "Scrabble game successfully loaded"<< std::endl;
      playGame(bag, playerOne, playerTwo, currentPlayer, board);
   }
   else {
      std::cout << ""<< std::endl;
      std::cout << "Invalid File - Please Try Again"<< std::endl;
      std::cout << ""<< std::endl;
      loadGame();
   }
}

// Load Player in - Format of Save Game must be exact
Player *loadPlayer(std::ifstream &infile)
{
   std::string playerName;
   std::string playerScore;
   std::string playerTiles;
   getline(infile, playerName);
   getline(infile, playerScore);
   getline(infile, playerTiles);
   int score = stoi(playerScore);
   Player *player = new Player(playerName);
   PlayerHand *hand = new PlayerHand();
   player->setScore(score);
   int counter = 0;
   for (char c : playerTiles)
   {
      if (isalpha(c))
      {
         char charValue = playerTiles[counter + 2];
         int num = (int)charValue - 48;
         Tile *tile = new Tile(c, num);
         hand->addTile(tile);
      }
      counter = counter + 1;
   }
   player->setPlayerHand(hand);
   return player;
}

// Load ScrabbleBoard - Format of Save Game must be exact
ScrabbleBoard *loadBoard(std::ifstream &infile)
{
   ScrabbleBoard *board = new ScrabbleBoard();
   std::string lineContent;
   getline(infile, lineContent);
   getline(infile, lineContent);

   for (int row = 0; row < 15; ++row)
   {
      int col = -1;
      getline(infile, lineContent);
      for (char c : lineContent)
      {
         if (isalpha(c) && col >= 0)
         {
            int value = getValue(c);
            Tile *tile = new Tile(c, value);
            board->placeTile(tile, row, col);
         }
          if (c == '|')
         {
            ++col;
         }
      }
   }
   return board;
}

// Load TileBag - Format of Save Game must be exact
TileBag *loadTileBag(std::ifstream &infile)
{
   TileBag *bag = new TileBag();
   std::string tilebag;
   getline(infile, tilebag);

   int counter = 0;
   for (char c : tilebag)
   {
      if (isalpha(c))
      {
         char charValue = tilebag[counter + 2];
         int num = (int)charValue - 48;
         Tile *tile = new Tile(c, num);
         bag->addNewTile(tile);
      }
      counter = counter + 1;
   }
   return bag;
}

void startGame(TileBag *tileBag, Player *player1, Player *player2)
{
   // Initalise Board
   ScrabbleBoard *scrabbleBoard = new ScrabbleBoard();

   // Initalise Current Player to Player 1
   Player *currentPlayer = player1;

   // Deal players initial 7 tiles
   PlayerHand *p1Hand = new PlayerHand();
   PlayerHand *p2Hand = new PlayerHand();
   dealPlayer(tileBag, player1, MAX_TILES, p1Hand);
   dealPlayer(tileBag, player2, MAX_TILES, p2Hand);

   playGame(tileBag, player1, player2, currentPlayer, scrabbleBoard);
}

void playGame(TileBag *tileBag, Player *player1, Player *player2, Player *currentPlayer, ScrabbleBoard *scrabbleBoard)
{
   // bool pass = false;

   std::vector<std::string> placements;

   // While not end of file and game is not endable
   while (!(std::cin.eof()) && (!gameIsEndable(tileBag, player1, player2)))
   {
      placements.clear();

      // Output current player name and both players scores
      std::cout << "" << std::endl;
      std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
      std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
      std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;

      // Output Board
      scrabbleBoard->displayBoard();

      // Displaying players hand
      std::cout << "" << std::endl;
      std::cout << "Your hand is: " << std::endl;
      for (int i = 0; i < currentPlayer->getPlayerHand()->getSize(); i++)
      {
         Tile *currTile = currentPlayer->getPlayerHand()->get(i);
         std::cout << currTile->getLetter() << "-" << currTile->getValue() << ", ";
      }
      std::cout << "After tiles" << std::endl;
      std::cout << "\n"
                << std::endl;

      std::cout << "Play your Turn! or type 'HELP' for options " << std::endl;

      bool turnIsDone = false;
      std::string command;
      std::string next;
      std::string at;
      std::string coord;
      std::string saveName;

      // PLAYERS TURN
      while (!(std::cin.eof()) && turnIsDone != true)
      {
         command = "";
         std::cout << "> ";
         std::cin >> command;

         // HELP MENU
         if ((command == "Help") || (command == "HELP") || (command == "help"))
         {
            std::cout << "You can play the following actions:" << std::endl;
            std::cout << "  1. Place a tile: type 'place <LETTER> at <CO-ORDINATES>'" << std::endl;
            std::cout << "  2. Replace a tile: type 'replace <LETTER>'" << std::endl;
            std::cout << "  3. Pass your turn: type 'pass'" << std::endl;
            std::cout << "  4. Save Game: type 'save <FILENAME>'" << std::endl;
            std::cout << "  5. Quit Game: type 'quit'" << std::endl;
         }

         // PASS TURN

         else if (command == "pass")
         {
            turnIsDone = true;

            // Increment passTotal by 1 for currentPlayer if they pass while tileBag is empty
            if (tileBag->getSize() == 0)
            {
               currentPlayer->setPassTotal(currentPlayer->getPassTotal() + 1);
            }
            // Consecutive passes stay at 1 for players if tileBag is not empty
            else
            {
               currentPlayer->setPassTotal(1);
            }
         }

         // QUIT DURING TURN
         else if (command == "quit")
         {
            std::cout << "" << std::endl;
            std::cout << "Goodbye!!" << std::endl;
            std::cout << "" << std::endl;
            exit(0);
         }

         // REPLACE TILE
         else if (command == "replace")
         {
            char letter;
            // Get Letter to be Removed from Player Hand
            std::cin >> letter;

            // Get Tile from Front of Tile Bag
            Tile *frontTile = tileBag->getNewTile();

            // Remove Tile from Tile Bag
            tileBag->removeTile();

            // Get tile to be replaced
            Tile *replaceTile = currentPlayer->getPlayerHand()->findTile(letter);

            int index = currentPlayer->getPlayerHand()->getTileIndex(replaceTile);

            // Remove Tile from Player Hand
            currentPlayer->getPlayerHand()->removeTile(replaceTile);

            // Add front tile from tile bag to player hand
            currentPlayer->getPlayerHand()->addAtIndex(frontTile, index);

            // Place replaced tile in back of tilebag
            tileBag->addNewTile(frontTile);

            // Next players turn
            turnIsDone = true;
         }

         // PLACE TILE
         else if (command == "place")
         {
            std::cin >> next;

            if (next == "Done")
            {
               turnIsDone = true;
            }
            else
            {
               std::cin >> at >> coord;
               std::string row;

               // concat command string
               command = command + " " + next + " " + at + " " + coord;
               row = getRowLetter(command);
               int col = getCol(command);
                std::cout << col<< std::endl;
               // Check that command is entered correclty - && std::stoi(coord) < 15 std::isdigit(coord.at(1)
               if (containsOnlyLetters(next) && containsOnlyLetters(row) && col >= 0 && col <= 14 && coord.size() < 4) 
               {
                  std::cout << command << std::endl;
                  placements.push_back(command);
               }
               else
               {
                  std::cout << "The command you entered is incorrect. Try again." << std::endl;
               }
            }
         }

         // SAVE GAME
         else if (!(std::cin.eof()) && command == "save")
         {
            std::cin >> saveName;
            std::ofstream output(saveName += ".txt", std::ofstream::trunc);
            savePlayerData(output, player1);
            savePlayerData(output, player2);
            saveGameState(output, tileBag, currentPlayer, scrabbleBoard);

            std::cout << std::endl;
            std::cout << "Game successfully saved" << std::endl;
            std::cout << std::endl;
         }

         else if (command != "")
         {
            std::cout << "The command you have given is incorrect, try again." << std::endl;
         }

         // Clear the cin, start input again
         std::cin.clear();
         std::cin.ignore(100, '\n');
      }
      // If there are any placement commands
      if (placements.size() != 0 && command == "place")
      {
         if (placeTiles(currentPlayer->getPlayerHand(), placements, scrabbleBoard, currentPlayer))
         {
            // If tileBag is not empty, deal tile(s) to player
            if (tileBag->getSize() != 0)
            {
       
               dealPlayer(tileBag, currentPlayer, placements.size(), currentPlayer->getPlayerHand());

            }
      
            // Reset consecutive passes back to 0 for both players if passTotal of current player that makes a placement is 1
            if (currentPlayer->getPassTotal() == 1)
            {
               player1->setPassTotal(0);
               player2->setPassTotal(0);
            }

            // Swap Current Player After Turn has Ended
            if ((currentPlayer->getName() == player1->getName()) && (turnIsDone == true))
            {
               currentPlayer = player2;
            }
            else if ((currentPlayer->getName() == player2->getName()) && (turnIsDone == true))
            {
               currentPlayer = player1;
            }
         }
      }
      else
      {
         // Swap Current Player After Turn has Ended
         if ((currentPlayer->getName() == player1->getName()) && (turnIsDone == true))
         {
            currentPlayer = player2;
         }
         else if ((currentPlayer->getName() == player2->getName()) && (turnIsDone == true))
         {
            currentPlayer = player1;
         }
      }
   }
   displayGameResults(player1, player2);

   delete scrabbleBoard;
}

bool placeTiles(PlayerHand *playerHand, std::vector<std::string> commands,
                ScrabbleBoard *board, Player *player)
{
   bool retVal = false;
   // Points from letters that are already on board
   int extraPoints = 0;
   int *ptr = &extraPoints;

   // If the placements of the tiles is legal, place tiles on board
   if (board->checkPlacement(commands, ptr))
   {
      // Check that the player has the tiles they are trying to place
      if (checkPlayerHasTiles(commands, playerHand))
      {
         // Check that there aren't already tiles where player would like to place
         if (checkPlaceTiles(board, commands, playerHand))
         {
            for (std::string &command : commands)
            {

               char letter = command.at(INT_OF_LETTER);
               // Finding nominated tile in players hand
               Tile *tileToPlace = playerHand->findTile(letter);
               // getting row
               int row = board->findRow(getRowLetter(command));
               // getting column
               int col;
               col = getCol(command);
    
                  board->placeTile(tileToPlace, row, col);
                  // Set player score and remove tile that was placed from player hand
                  player->setScore(player->getScore() + tileToPlace->getValue());
                  playerHand->removeTile(tileToPlace);
   
                  retVal = true;
            }
         }
         else
         {
            std::cout << "\n";
            std::cout << "Invalid tile placement. Try again." << std::endl;
         }
      }
      else
      {
         std::cout << "\n";
         std::cout << "A tile you tried to place is not in your hand. Try again." << std::endl;
      }
   }
   else
   {
      std::cout << "\n";
      std::cout << "The placement of your tiles is not legal. Try again." << std::endl;
      std::cout << "\n";
      retVal = false;
   }

   // Give the player points for words that are already on the board
   player->setScore(player->getScore() + extraPoints);

   // Print "BINGO!!!" if player places all 7 tiles and add 50 points to score
   if (retVal && commands.size() == 7)
   {
      std::cout << "BINGO!!!" << std::endl;
      player->setScore(player->getScore() + 50);
   }

   return retVal;
}

bool checkPlayerHasTiles(std::vector<std::string> commands, PlayerHand *playerHand)
{
   bool retVal = false;
   int dontHave = 0;
   PlayerHand *phCopy = new PlayerHand(*playerHand);

   for (std::string &command : commands)
   {
      char letter = command.at(INT_OF_LETTER);

      // Finding nominated tile in players hand
      Tile *tileToPlace = phCopy->findTile(letter);

      if (tileToPlace == nullptr)
      {
         dontHave++;
      }
      else
      {
         // Removing tile so that if there are two of the same letters, but
         // the player only has one, program won't accept the letter twice
         // adding dummy tile so that findTile function still works
         phCopy->removeTile(tileToPlace);
         phCopy->addTileBack(new Tile(' ', 0));
      }
   }

   if (dontHave == 0)
   {
      retVal = true;
   }

   return retVal;
}

bool gameIsEndable(TileBag *tileBag, Player *player1, Player *player2)
{
   bool endGame = false;

   // If tileBag is empty and...
   if (tileBag->getSize() == 0)
   {
      // ...if either player hand's are empty, then return endGame is true
      if (player1->getPlayerHand()->getSize() == 0 || player2->getPlayerHand()->getSize() == 0)
      {
         endGame = true;
      }
      // else if both players passed once one after the other, then return endGame is true
      else if (player1->getPassTotal() == 1 && player2->getPassTotal() == 1)
      {
         endGame = true;
      }
      // else if either players passed twice in a row, then return endGame is true
      else if (player1->getPassTotal() == 2 || player2->getPassTotal() == 2)
      {
         endGame = true;
      }
   }
   return endGame;
}