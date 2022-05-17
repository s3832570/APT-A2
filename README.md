# APT-A2
By Chloe, Hien and Lachlan

## Test Cases
*All test cases test the load function so that the tiles are in the same order for the .out and .gameout files.*

**edge** <br>
The edge test tests whether you can place tiles along the edge of the board without errors. <br> It also shows that the save file saves the correct points & tiles.

**outside** <br>
The outside test shows that a player is unable to place a tile outside the bounds of the <br> board, and will not get the points for unplaced tile.

**parallel** <br>
The parallel test shows that you can place a word parallel to another word, and you will get the points from <br> the letters that are directly connected to the letters that you placed.

**wrong input** <br>
The wrong input test shows that the "place <letter> at <coordinate>" input must be entered correctly for the game <br> to continue.
