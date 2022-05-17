#include "utils.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>

// View Credits 
void viewCredits()
{
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
    std::cout << "Name: Lachlan Ward" << std::endl;
    std::cout << "Student ID: s3888736" << std::endl;
    std::cout << "Email: s3888736@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << std::endl;
}

// Input Name for Player
void inputName(std::string *name)
{
    std::string inputName;
    while ((!(std::cin >> inputName) || (!containsOnlyLetters(inputName))) && !std::cin.eof())
    {
        std::cout << std::endl;
        std::cout << "Invalid Input" << std::endl;
        std::cout << std::endl;
        std::cout << "> ";
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }
    *name = inputName;
}

// Check if contains
bool containsOnlyLetters(std::string name)
{
    return std::regex_match(name, std::regex("^[A-Z]+$"));
}

/**
 * @brief 
 * Gives the player the amount of nominated tiles from the tile bag. Deletes the tile from the
 * tile bag once it has been given to the player and then updates the players hand.
 * 
 * @param tileBag 
 * @param player 
 * @param numTiles 
 * @param playerHand 
 */
void dealPlayer(TileBag *tileBag, Player *player, int numTiles, PlayerHand *playerHand)
{
    // Iterate through the specified amount of times
    for (int i = 0; i < numTiles; i++)
    {
        // If the tileBag isn't empty, give player tile from tileBag
        if (tileBag->getSize() > 0)
        {
            Tile *newTile = tileBag->getNewTile();
            playerHand->addTile(newTile);
            tileBag->removeTile();
        };
    }

    //
    player->setPlayerHand(playerHand);
}

// Save Player Data
void savePlayerData(std::ofstream &output, Player *player)
{
    output << player->getName() << std::endl;
    output << player->getScore() << std::endl;

    for (int i = 0; i < player->getPlayerHand()->getSize(); i++)
    {
        if (i < player->getPlayerHand()->getSize() - 1)
        {
            Tile *currTile = player->getPlayerHand()->get(i);
            output << currTile->getLetter() << "-" << currTile->getValue() << ", ";
        }
        else
        {
            Tile *currTile = player->getPlayerHand()->get(i);
            output << currTile->getLetter() << "-" << currTile->getValue() << std::endl;
        }
    }
}

void saveGameState(std::ofstream &output, TileBag *tileBag, Player *currentPlayer, ScrabbleBoard *scrabbleBoard)
{
    // Displays the board
    output << scrabbleBoard->saveState() << std::endl;

    if (tileBag->getSize() != 0)
    {
        for (int i = 0; i < tileBag->getSize(); i++)
        {
            if (i < tileBag->getSize() - 1)
            {
                Tile *currTile = tileBag->get(i);
                output << currTile->getLetter() << "-" << currTile->getValue() << ", ";
            }
            else
            {
                Tile *currTile = tileBag->get(i);
                output << currTile->getLetter() << "-" << currTile->getValue() << std::endl;
            }
        }
    }
    else
    {
        output << "" << std::endl;
    }

    output << currentPlayer->getName();
    output.close();
}

void displayGameResults(Player *player1, Player *player2)
{
    std::cout << std::endl;
    std::cout << "---Game over---" << std::endl;
    std::cout << "Score for " << player1->getName() << ": " << player1->getScore() << std::endl;
    std::cout << "Score for " << player2->getName() << ": " << player2->getScore() << std::endl;

    if (player1->getScore() > player2->getScore())
    {
        std::cout << "Player " << player1->getName() << " won!" << std::endl;
    }
    else if (player1->getScore() < player2->getScore())
    {
        std::cout << "Player " << player2->getName() << " won!" << std::endl;
    }
    else if (player1->getScore() == player2->getScore())
    {
        std::cout << "Draw! Both players have the same score." << std::endl;
    }

    std::cout << std::endl;
}

int getValue(char c)
{
    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int values[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int value = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (c == alphabet[i])
        {
            value = values[i];
        }
    }
    // int number = values[counter];
    return value;
}

/**
 * @brief
 * This converts the end of the command string into an int and returns that as the column 
 * number. If there is a character where a number should be, returns -1;
 * 
 * @param command 
 * @return int 
 */
int getCol(std::string command)
{
    std::string coord;
    int col;

      std::cout << command << std::endl;
       std::cout << command.length() << std::endl;
    // Get the column from the command, check if 1 digit or 2 digit
    if (command.length() == COMMAND_STRING_LENGTH + 1)
    {
        coord = command.substr(COMMAND_STRING_LENGTH - 1, COMMAND_STRING_LENGTH + 1);
    }
    else if (command.length() == COMMAND_STRING_LENGTH)
    {
        coord = command.substr(COMMAND_STRING_LENGTH - 1, COMMAND_STRING_LENGTH);
    } else {
        col = -1;
    }

    if (coord.length() == 3)
    {
        std::string c = coord.substr(1, 2);
        int containsChar = 0;

        // Check to see if column contains any characters
        for (char ch : c)
        {
            if (isalpha(ch))
            {
                containsChar++;
            }
        }
        // If doesn't contain characters, convert to int and return
        // If contains characters - error
        if (containsChar == 0)
        {
            std::stringstream colValue(coord.substr(1, 2));
            colValue >> col;
        }
        else
        {
            col = -1;
        }
    }
    else
    {
        col = coord.at(1) - '0';
    }
    return col;
}


/**
 * @brief 
 * Returns the char that represents the row at a certain
 * point in the command string.
 * 
 * @param command 
 * @return char 
 */
char getRowLetter(std::string command)
{
    char c = command.at(INDEX_OF_ROW);

    return c;
}

/**
 * @brief 
 * Check that a tile isn't being placed on top of a tile that
 * is already on the board
 * 
 * @param board 
 * @param commands 
 * @param playerHand 
 * @return true 
 * @return false 
 */
bool checkPlaceTiles(ScrabbleBoard *board, std::vector<std::string> commands, PlayerHand *playerHand)
{
    bool retVal = true;
    int count = 0;

    for (std::string &command : commands)
    {
        int row = board->findRow(getRowLetter(command));
        int col = getCol(command);

        // Check coordinate on board if row and column are within range
        // If there is already a tile at coordinate, count += 1;
        if (row >= 0 && row < SCRABBLE_BOARD_LENGTH &&
            col >= 0 && col < SCRABBLE_BOARD_LENGTH + 1)
        {
            if (board->getBoard()[row][col]->getLetter() != ' ')
            {
                count++;
            }
        }
        else
        {
            retVal = false;
        }
    }

    // If there are any existing tiles in placement command coordinates
    // it is an illegal placement
    if (count > 0)
    {
        retVal = false;
    }

    return retVal;
}

/**
 * @brief 
 * Display player info, board and player tiles before they take their turn
 * 
 * @param currentPlayer 
 * @param player1 
 * @param player2 
 * @param scrabbleBoard 
 */
void displayInfo(Player *currentPlayer, Player *player1, Player *player2, ScrabbleBoard *scrabbleBoard)
{
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
    std::cout << "\n"
              << std::endl;

    std::cout << "Play your Turn! or type 'HELP' for options " << std::endl;
}

/**
 * @brief 
 * Swap current player to the next player
 * 
 * @param currentPlayer 
 * @param player1 
 * @param player2 
 * @param turnIsDone 
 */
void swapPlayer(Player *currentPlayer, Player *player1, Player *player2, bool turnIsDone)
{
    std::cout << currentPlayer->getName() << std::endl;
    std::cout << player1->getName() << std::endl;
    std::cout << player2->getName() << std::endl;
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
