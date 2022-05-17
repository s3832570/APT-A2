# APT-A2
<h3>By Chloe S3832570, Hien S3783447 and Lachlan S3888736</h3>

## Test Cases
*All test cases test the load function so that the tiles are in the same order for the .out and .gameout files.* 
-> To run the test files: ./scrabble < ./test/*testname*.input > ./test/*testname*.gameout

**edge** <br>
The edge test tests whether you can place tiles along the edge of the board without errors.  It also shows that the save file saves the correct points & tiles.

**outside** <br>
The outside test shows that a player is unable to place a tile outside the bounds of the > board, and will not get the points for unplaced tile.

**parallel** <br>
The parallel test shows that you can place a word parallel to another word, and you will get the points from the letters that are directly connected to the letters that you placed.

**wrong input** <br>
The wrong input test shows that the "place (letter) at (coordinate)" input must be entered correctly for the game  to continue.

**replace** <br>
The tests the in-place replace function four seperate times showing that players hands are updated, without changing the order. 
