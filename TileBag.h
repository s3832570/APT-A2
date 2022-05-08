#ifndef ASSIGN2_TILE_BAG_H
#define ASSIGN2_TILE_BAG_H

#include "Tile.h"
#include "LinkedList.h"

#define TILEBAG_MAX_TILES 98

class TileBag {
public:
   TileBag();
   TileBag(TileBag& other);
   ~TileBag();

   Tile getNewTile();

   void removeTile();

   void shuffleBag();

   int getSize();

private:

    LinkedList* tileBag;
    int         size;

};

#endif // ASSIGN2_TILE_H