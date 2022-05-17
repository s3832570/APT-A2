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

#define INT_OF_LETTER 6

#define EXIT_SUCCESS 0

// DEFINE FUNCTIONS
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

// Run Main
int main(void)
{
   mainMenu();

   return EXIT_SUCCESS;
}

// Main Menu Print Out
void mainMenu()
{
   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   // User Selection
   int userMenuInput = 0;
   while (userMenuInput != 1 && userMenuInput != 4)
   {
      // Print Menu Selections
      std::cout << "Menu" << std::endl;
      std::cout << "----" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Credits (Show student information)" << std::endl;
      std::cout << "4. Quit" << std::endl;
      std::cout << std::endl;
      std::cout << "> ";

      // If invalid input clear and get input
      while ((!(std::cin >> userMenuInput) || !(userMenuInput >= 1 && userMenuInput <= 4)) && !std::cin.eof())
      {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
         std::cin.clear();
         std::cin.ignore(100, '\n');
      }

      // Create new game
      if (userMenuInput == 1)
      {
         newGame();
      }

      // Load Game
      if (userMenuInput == 2)
      {
         loadGame();
      }

      // View Credits
      if (userMenuInput == 3)
      {
         viewCredits();
      }
   }

   // Good Bye
   std::cout << std::endl;
   std::cout << "Goodbye!" << std::endl;
}

// Create New Game of Scrabble
void newGame()
{
   // Create Blank TileBag
   TileBag *tileBag = new TileBag();

   // Reading in new tile bag from text file and shuffle
   std::fstream infile("ScrabbleTiles.txt");
   char letter;
   int value;
   while (infile >> letter >> value)
   {
      tileBag->addNewTile(new Tile(letter, value));
   }
   tileBag->shuffleBag();

   // Create input for players names
   std::string player1Name;
   std::string player2Name;

   // Start Game
   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   // Enter Names for Both Players
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

   // Start Game
   startGame(tileBag, player1, player2);

   // Memory Clean Up
   delete player1;
   delete player2;
   delete tileBag;
}

void loadGame()
{
   // Get File Name
   std::cout << "Enter the filenane for which to load a game! " << std::endl;
   std::cout << "> ";

   // Get File Name to Be Loaded
   std::string fileName;
   std::string test;
   std::cin >> fileName;

   // Load File
   std::ifstream file(fileName);

   // Check if file exists
   if (file.good())
   {
      // Check File Contents and Load in players, board and tileBag
      Player *playerOne = loadPlayer(file);
      Player *playerTwo = loadPlayer(file);

      // Make Current Player
      Player *currentPlayer;

      // Get board and TileBag
      ScrabbleBoard *board = loadBoard(file);
      TileBag *bag = loadTileBag(file);

      // Get Current Player Name
      std::string currentPlayerName;
      getline(file, currentPlayerName);

      // Determine who is starting player
      if (currentPlayerName == playerOne->getName())
      {
         currentPlayer = playerOne;
      }
      else
      {
         currentPlayer = playerTwo;
      }

      // Print Game Loading has been successful
      std::cout << "" << std::endl;
      std::cout << "Scrabble game successfully loaded" << std::endl;

      // Play Game not that it has been loaded
      playGame(bag, playerOne, playerTwo, currentPlayer, board);

      // Memory Management
      delete playerOne;
      delete playerTwo;
      delete currentPlayer;
      delete board;
      delete bag;
   }
   else
   {
      std::cout << "" << std::endl;
      std::cout << "Invalid Input" << std::endl;
      std::cout << "" << std::endl;
      loadGame();
   }
}

// Load Player in - Format of Save Game must be exact
Player *loadPlayer(std::ifstream &infile)
{
   // Create Attributes
   std::string playerName;
   std::string playerScore;
   std::string playerTiles;

   // Get Lines with Data and set it to attributes
   getline(infile, playerName);
   getline(infile, playerScore);
   getline(infile, playerTiles);
   int score = stoi(playerScore);

   // Set Player Details
   Player *player = new Player(playerName);
   PlayerHand *hand = new PlayerHand();
   player->setScore(score);

   // Set each player hand tile
   int counter = 0;
   for (char c : playerTiles)
   {
      // If char is a alphabetic characters
      if (isalpha(c))
      {
         // Then get Value
         char charValue = playerTiles[counter + 2];
         int num = (int)charValue - 48;

         // Create Tile and Add it to Players Hand
         Tile *tile = new Tile(c, num);
         hand->addTile(tile);
      }
      // Increment
      counter = counter + 1;
   }
   // Set Player Hand full of tiles
   player->setPlayerHand(hand);

   // Return Player to Load Function
   return player;
}

// Load ScrabbleBoard - Format of Save Game must be exact
ScrabbleBoard *loadBoard(std::ifstream &infile)
{
   // Create Blank Board
   ScrabbleBoard *board = new ScrabbleBoard();

   // Get Blank Lines in file
   std::string lineContent;
   getline(infile, lineContent);
   getline(infile, lineContent);

   // For each row, find characters and add to board in position
   for (int row = 0; row < 15; ++row)
   {
      int col = -1;
      // Get that lines content
      getline(infile, lineContent);

      // For each Char in that Line
      for (char c : lineContent)
      {
         // If Character is Alphabetic and Col is within range
         if (isalpha(c) && col >= 0)
         {
            int value = getValue(c);

            // Create Tile with letter and value
            Tile *tile = new Tile(c, value);

            // Place Tile on board
            board->placeTile(tile, row, col);
         }

         // Increase Col based on '|'
         if (c == '|')
         {
            ++col;
         }
      }
   }

   // Return Board with loaded in tiles
   return board;
}

// Load TileBag - Format of Save Game must be exact
TileBag *loadTileBag(std::ifstream &infile)
{
   // Create Tilebag
   TileBag *bag = new TileBag();
   std::string tilebag;

   // Get TileBag content
   getline(infile, tilebag);

   // For each char, create tile with letter and value
   int counter = 0;
   for (char c : tilebag)
   {
      if (isalpha(c))
      {
         // Create tile and Add it to Bag
         char charValue = tilebag[counter + 2];
         int num = (int)charValue - 48;
         Tile *tile = new Tile(c, num);
         bag->addNewTile(tile);
      }
      counter = counter + 1;
   }

   // Return TileBag with loaded in tiles
   return bag;
}

// Start Game with Tilebag, Players, only for not loading in scrabbleboard or tilebag
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

   // Proceed to Play Game
   playGame(tileBag, player1, player2, currentPlayer, scrabbleBoard);
}

// Play Game with Tilebag, Players, only for not loading in scrabbleboard or tilebag and Players
void playGame(TileBag *tileBag, Player *player1, Player *player2, Player *currentPlayer, ScrabbleBoard *scrabbleBoard)
{
   // Create Player Inputs for Placements and Replacement, see those functions for more details
   std::vector<std::string> placements;
   std::vector<std::string> replacements;

   // While not end of file and game is not endable
   while (!(std::cin.eof()) && (!gameIsEndable(tileBag, player1, player2)))
   {
      // Clear Player Placements for Boards
      placements.clear();

      // Display Board
      displayInfo(currentPlayer, player1, player2, scrabbleBoard);

      // Create turn is done variable
      bool turnIsDone = false;

      // Initalise inputs commands
      std::string command;
      std::string next;
      std::string at;
      std::string coord;
      std::string saveName;

      // PLAYERS TURN - While their turn is not done or End of File
      while (!(std::cin.eof()) && turnIsDone != true)
      {
         // Initalise Command
         command = "";

         // Provide > for input for user
         std::cout << "> ";

         // Get Input
         std::cin >> command;

         // HELP MENU
         if ((command == "Help") || (command == "HELP") || (command == "help"))
         {
            // Print out options for help
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
            // This stops Players Turn and Passes
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
            // Print Goodbye and Quit
            std::cout << "" << std::endl;
            std::cout << "Goodbye!!" << std::endl;
            std::cout << "" << std::endl;
            exit(EXIT_SUCCESS);
         }

         // REPLACE TILE
         else if (command == "replace")
         {
            // CLear Placements and get letter to be replaced
            char letter;
            replacements.clear();

            // Get Letter to be Removed from Player Hand
            std::cin >> letter;
            std::string sendCommand = "place " + std::string(1, letter);
            replacements.push_back(sendCommand);
            if (checkPlayerHasTiles(replacements, currentPlayer->getPlayerHand()) && tileBag->getSize() > 0)
            {
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
            // Handle Inputs and Tile Errors
            else
            {
               // If tilebag is empty
               if (tileBag->getSize() == 0)
               {
                  std::cout << "No more tiles are left in the bag!" << std::endl;
               }
               else
               {
                  // Print Invalid Input
                  std::cout << "" << std::endl;
                  std::cout << "Invalid Input" << std::endl;
                  std::cout << "" << std::endl;
               }
            }
         }
         // PLACE TILE
         else if (command == "place")
         {
            // Get Placement Input
            std::cin >> next;

            // End turn and do placements
            if (next == "Done")
            {
               turnIsDone = true;
            }
            else
            {
               // Get Co-ordiantes to Place
               std::cin >> at >> coord;
               std::string row;

               // Concat command string
               command = command + " " + next + " " + at + " " + coord;

               // Get Row and Col from Command
               row = getRowLetter(command);
               int col = getCol(command);
               // Check that command is entered correclty - && std::stoi(coord) < 15 std::isdigit(coord.at(1)
               if (containsOnlyLetters(next) && containsOnlyLetters(row) && col >= 0 && col <= 14 && coord.size() < 4)
               {
                  // Get Row and Col from Command
                  row = getRowLetter(command);
                  int col = getCol(command);

                  // Check that command is entered correclty - && std::stoi(coord) < 15 std::isdigit(coord.at(1)
                  if (containsOnlyLetters(next) && containsOnlyLetters(row) && col >= 0 && col <= 14 && coord.size() < 4)
                  {
                     // Push Placements to string Vector
                     placements.push_back(command);
                  }
                  // Handle Invalid Inpit
                  else
                  {
                     std::cout << "Invalid Input" << std::endl;
                  }
               }
               else
               {
                  std::cout << "Invalid Input" << std::endl;
               }
            }
         }
         // SAVE GAME
         else if (!(std::cin.eof()) && command == "save")
         {
            // Get Save File Name
            std::cin >> saveName;
            std::ofstream output(saveName += ".save", std::ofstream::trunc);

            // Call Save File Functions for Players, Board and TileBag
            savePlayerData(output, player1);
            savePlayerData(output, player2);
            saveGameState(output, tileBag, currentPlayer, scrabbleBoard);

            // Output if game is successfully saved
            std::cout << std::endl;
            std::cout << "Game successfully saved" << std::endl;
            std::cout << std::endl;
         }
         // Handle Invalid Input if file Name is not present
         else if (command != "")
         {
            std::cout << "Invalid Input" << std::endl;
         }

         // Clear the cin, start input again
         std::cin.clear();
         std::cin.ignore(100, '\n');
      }

      // If there are any placement commands
      if (placements.size() != 0 && command == "place")
      {
         // Place Tiles and
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

   // Once Game has Ended, Display Results
   displayGameResults(player1, player2);

   // Delete Board
   delete scrabbleBoard;
}

// Place Tiles on the Board
bool placeTiles(PlayerHand *playerHand, std::vector<std::string> commands,
                ScrabbleBoard *board, Player *player)
{
   // Inialised Placed Value
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

               // Update date Return Value
               retVal = true;
            }
         }
         // Handle Invalid input
         else
         {
            std::cout << "\n";
            std::cout << "Invalid Input" << std::endl;
         }
      }
      else
      {
         // Handle Invalid input
         std::cout << "\n";
         std::cout << "Invalid Input" << std::endl;
      }
   }
   else
   {
      // Handle Invalid input
      std::cout << "\n";
      std::cout << "Invalid Input" << std::endl;
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

// Check player has Tiles in their hand
bool checkPlayerHasTiles(std::vector<std::string> commands, PlayerHand *playerHand)
{
   // Return Value
   bool retVal = false;
   int dontHave = 0;

   // Create Copy of player Hand
   PlayerHand *phCopy = new PlayerHand(*playerHand);

   // For each Command in commands
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

   // If player has tiles
   if (dontHave == 0)
   {
      retVal = true;
   }

   // Delete Copy
   delete phCopy;

   // Return Value
   return retVal;
}

// If game can end, return whether game is over
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

   // Return whether game should end
   return endGame;
}