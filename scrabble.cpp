
#include "LinkedList.h"
#include "Player.h"

#include <iostream>
#include <regex>

#define EXIT_SUCCESS    0

/**
 * TODO:
 * - 🟡 main menu
 *    > 1. new game ✅
 *       • display "Starting a new game" ✅ 
 *    > 2. load game
 *       • display "Enter the filename from which load a game"
 *       • user enters relative path and then presses enter
 *       • check file exists
 *       • check file format is correct (maybs try catch exception)
 *       • display "Scrabble game successfully loaded"
 *    > 3. show credits ✅
 *       • all student information ✅
 *    > 4. quit program ✅
 *    > user will enter number to select ✅
 *       • check number is in bounds ✅
 * 
 * - 🟠 player
 *    > score ✅
 *    > hand
 *    > name ✅
 *    > update players score ✅
 * 
 * - 🟠 player hand
 *    > linked list ✅
 * 
 * - 🟢 tile bag
 *    linked list ✅
 *    > jumbles tile bag and pulls from front (put in "random" order) ✅ 
 *    > replace players tiles with new tiles from tile bag  ✅
 *       • tile must be removed from tile bag ✅
 * 
 * - 🟢 linked list
 *    > add back ✅
 *    > add front ✅
 * 
 * - 🟢 node
 *    constructor ✅
 *    copy constuctor ✅
 *    data (tile) ✅
 *    Node* pointer ✅
 * 
 * - 🔴 tile
 * 
 * - 🔴 board
 *    > A vector of vectors of tiles ✅
 *    > rows ✅
 *    > columns ✅
 *    > create empty board ✅
 *    > check placement of tile is legal
 * 
 * - 🟡 {the game 
 *    > ask for player names (must only contain letters) ✅
 *       • "Enter a name for player 1 (uppercase characters only)" ✅
 *         display "Let's Play!" ✅
 *    > display players' scores ✅}
 *    > display board
 *    > display player 1's hand
 *    > user prompt showing the commands they can use
 *    game always begins with player 1
 *    player can place up to 7 letters
 *    > must type "place <capital letter> at <coordinate>" (check format)
 *       > if player places 7 tiles must display "BINGO!!!" before   
 *      displaying game results
 *      must type "place Done" to finish turn (check format)
 *    > show results on board 
 *    > move to next players turn
 *    > player can replace ONE tile per turn 
 *       • by typing "replace <letter>" (letter must be caps)
 *       • check format
 *       • check player has that tile  
 *       • if tile exists in hand, place tile back in tile bag and   
 *         draw new tile from tile bag (if player has two of same
 *         letter, take first instance)
 *       • replacing tile counts as their turn, move to next player
 *    > player can type "pass" to pass their turn
 *    > save game
 *       • player types "save <filename>"
 *       • display "Game successfully saved"
 *       • turn continues as normal
 *       • formatting for save file is on pg 10-11 of spec
 *    > quit game (idk if game has to save before quitting?)
 *       • no crashing :)
 *       • also quits if ^D is enterd
 *    > game ends when tile bag is empty, player has no more tiles in hand
 *      or turn passes twice
 *       • display "Game over"
 *       • display score for both players "Score for <player>: 000"
 *       • display "Player <player> won!"
 *       • display "Goodbye" and then quit game 
 * 
 * - 🟢 load game
 *    > resume game with current player when loaded
 * 
 * - user input ✅
 *    > display "Invalid Input" when input is invalid ✅
 * 
 * put ✅ at start of every task completed
 * and possibly a coloured circle for who implemented? (🔴 - Alex, 🟠 - Chloe, 🟡 - Hien, 🟢 - Lachlan)
 * Just so we know who has to write about that feature
 * in the report.
 */

void newGame();
void viewCredits();
void testFunction();
bool containsOnlyLetters(std::string name);
void inputName(std::string* name);

int main(void) {
   //LinkedList* list = new LinkedList();
   //delete list;

   //std::cout << "TODO: Implement Scrabble!" << std::endl;

   std::cout << "Welcome to Scrabble!" << std::endl;
   std::cout << "-------------------" << std::endl;

   int userMenuInput;
   while (!std::cin.eof() && userMenuInput != 1 && userMenuInput != 4) {
      std::cout << "Menu" << std::endl;
      std::cout << "----" << std::endl;
      std::cout << "1. New Game" << std::endl;
      std::cout << "2. Load Game" << std::endl;
      std::cout << "3. Credits (Show student information)" << std::endl;
      std::cout << "4. Quit" << std::endl;

      std::cout << std::endl;
      std::cout << "> ";
         
      while ((!(std::cin >> userMenuInput) || !(userMenuInput >= 1 && userMenuInput <= 4)) && !std::cin.eof()) {
         std::cout << "Invalid Input" << std::endl;
         std::cout << "> ";
         std::cin.clear();
         std::cin.ignore(100, '\n');
      }

      if (userMenuInput == 1) {
         newGame();
      }
      /**
       * TODO:
       * if (userMenuInput == 2) {
       * 
       * }
       * 
       */
      if (userMenuInput == 3) {
         viewCredits();
      }

      // TESTING FUNCTION ONLY
      if (userMenuInput == 4) {
         testFunction();
      }
   }
   std::cout << std::endl;
   std::cout << "Goodbye" << std::endl;

   return EXIT_SUCCESS;
}

void newGame() {
   std::string player1Name;
   std::string player2Name;

   std::cout << std::endl;
   std::cout << "Starting a New Game" << std::endl;
   std::cout << std::endl;

   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   inputName(&player1Name);
   Player* player1 = new Player(player1Name);
   std::cout << std::endl;

   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   std::cout << "> ";
   inputName(&player2Name);
   Player* player2 = new Player(player2Name);
   std::cout << std::endl;

   std::cout << "Let's Play!" << std::endl;
   std::cout << std::endl;

   //Get player name test
   std::cout << player1->getName() << ", it's your turn" << std::endl;
   std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
   std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;
}

void inputName(std::string* name) {
   std::string inputName;
   while ((!(std::cin >> inputName) || (!containsOnlyLetters(inputName))) && !std::cin.eof()) {
      std::cout << std::endl;
      std::cout << "Invalid name. Must use uppercase letters only." << std::endl;
      std::cout << std::endl;
      std::cout << "> ";
      std::cin.clear();
      std::cin.ignore(100, '\n');
   }
   *name = inputName;
}

bool containsOnlyLetters(std::string name) {
   return std::regex_match(name, std::regex("^[A-Z]+$"));
}

void viewCredits() {
   std::cout << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Name: Chloe Harvey" << std::endl;
   std::cout << "Student ID: s3832570" << std::endl;
   std::cout << "Email: s3832570@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Hien Tran" << std::endl;
   std::cout << "Student ID: s3783447" << std::endl;
   std::cout << "Email: s3783447@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Alexander Perera" << std::endl;
   std::cout << "Student ID: s3721805" << std::endl;
   std::cout << "Email: s3721805@student.rmit.edu.au" << std::endl;
   std::cout << std::endl;
   std::cout << "Name: Lachlan Ward" << std::endl;
   std::cout << "Student ID: s3888736" << std::endl;
   std::cout << "Email: s3888736@student.rmit.edu.au" << std::endl;
   std::cout << "----------------------------------" << std::endl;
   std::cout << std::endl;
}

void testFunction() {
   LinkedList *list = new LinkedList();
   
   Tile *tile = new Tile('a', 3);
   list->addTileFront(tile);

   Tile *tiles = new Tile('b', 4);
   list->addTileFront(tiles);

   Tile *tiless = new Tile('c', 5);
   list->addTileFront(tiless);

    Tile *tilesss = new Tile('d', 6);
   list->addTileFront(tilesss);

    Tile *tilessss = new Tile('e', 7);
   list->addTileFront(tilessss);

   list->printList();

   list->shuffle();

   list->printList();
}

//vector of vectors for scrabble board.
//needs implementation of passing in tiles.
vector<vector<char> >scrabbleBoard(){

    vector<vector<char> >scrabbleBoard;

    //Fill the inner vector with char for first element, then insert it into the outer vector 
    for(char i = 'A'; i <'P'; i++){
        vector <char> temp;
        char a = ' ';
        for (int j = 0; j < 16; j++){

            if (j == 0){
                temp.push_back(i);
            }

            temp.push_back(a);
        }
        scrabbleBoard.push_back(temp);
    }
    return scrabbleBoard;
}
//display empty scrabble board.
//can only display empty board and requires changes to pass in tiles.
void displayBoard(std::vector<vector<char> > scrabbleBoard){
    //Displays the empty board 
    cout <<"-------------------------------------------------------------------" << endl;
    cout <<"    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15" << endl;
    cout <<"-------------------------------------------------------------------" << endl;
    for (int i = 0; i<scrabbleBoard.size(); i++){
        for (int j = 0; j<scrabbleBoard[i].size(); j++){
            cout << scrabbleBoard[i][j]<< " | ";
        }
        cout <<endl;
    }

}
