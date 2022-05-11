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

   void addNewTile(Tile* tile);

   Tile* getNewTile();

   void removeTile();

   void shuffleBag();

   int getSize();

   Tile* get(int index);

private:

    LinkedList* tileBag;
};

#endif // ASSIGN2_TILE_H