
#include "LinkedList.h"

#include <iostream>

#define EXIT_SUCCESS    0

/**
 * TODO:
 * - 🟡 main menu
 *    > 1. new game 
 *       • display "Starting a new game" 
 *    > 2. load game
 *       • display "Enter the filename from which load a game"
 *       • user enters relative path and then presses enter
 *       • check file exists
 *       • check file format is correct (maybs try catch exception)
 *       • display "Scrabble game successfully loaded"
 *    > 3. show credits
 *       • all student information
 *    > 4. quit program
 *    > user will enter number to select
 *       • check number is in bounds
 * 
 * - 🟠 player
 *    > score
 *    > hand
 *    > name
 *    > update players score
 * 
 * - 🟠 player hand
 *    > linked list
 * 
 * - 🟢 tile bag
 *    linked list
 *    > jumbles tile bag and pulls from front (put in "random" order)
 *    > replace players tiles with new tiles from tile bag
 *       • tile must be removed from tile bag
 * 
 * - 🟢 linked list
 *    > add back
 *    > add front
 * 
 * - 🟡 node
 *    constructor
 *    copy constuctor
 *    data (tile)
 *    Node* pointer
 * 
 * - 🔴 tile
 * 
 * - 🔴 board
 *    > A vector of vectors of tiles
 *    > rows
 *    > columns
 *    > create empty board
 *    > check placement of tile is legal
 * 
 * - the game 
 *    > ask for player names (must only contain letters)
 *       • "Enter a name for player 1 (uppercase characters only)"
 *         display "Let's Play!"
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
 * - user input
 *    > display "Invalid Input" when input is invalid
 * 
 * put ✅ at start of every task completed
 * and possibly a coloured circle for who implemented? (🔴 - Alex, 🟠 - Chloe, 🟡 - Hien, 🟢 - Lachlan)
 * Just so we know who has to write about that feature
 * in the report.
 */

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "TODO: Implement Scrabble!" << std::endl;

   return EXIT_SUCCESS;
}
