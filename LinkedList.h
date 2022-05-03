
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int getListSize();

   void addFront(Tile* tile);

   void addBack(Tile* tile);

   void removeFront();

   void removeBack();

   Node* get(int index);

   Node* getFront();

   void remove(int index);

   void shuffle();

private:
   Node* head;
   Node* tail;
   int listSize;
};

#endif // ASSIGN2_LINKEDLIST_H
