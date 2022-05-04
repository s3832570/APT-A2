
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   int getListSize();
   void addTileFront(Tile* tile);
   void addTileBack(Tile* tile);
   void removeTileFront();
   void removeTileBack();
   Tile* get(int index);
   Node* getTileFront();
   void remove(int index);
   void shuffle();
   void printList();

private:
   Node* head;
   Node* tail;
   int listSize;
};

#endif // ASSIGN2_LINKEDLIST_H
