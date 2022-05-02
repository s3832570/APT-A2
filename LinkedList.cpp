
#include "LinkedList.h"

LinkedList::LinkedList() {
   this->head = nullptr;
   this->tail = nullptr;
   listSize = 0;
}

LinkedList::~LinkedList() {
}

int LinkedList::getListSize() {
   return listSize;
}

void LinkedList::addTileFront(Tile* tile) {
   Node* node = new Node(tile, head);
   head = node;
   ++listSize;
}

Tile* LinkedList::getTileFront(){
   Node* head = head;
   Tile* tile = head->tile;
   return tile;
}

void LinkedList::addTileBack(Tile* tile) {
   Node* node = new Node(tile, tail);
   tail->next = node;
   tail = node;
    ++listSize;
}

void LinkedList::removeTileFront() {
   if (head == tail) { //one element in list
      head = nullptr;
      tail = nullptr;
   }
   else if (head != tail) {
      head = head->next;
   }
   --listSize;
}

Tile* LinkedList::get(int index){
   Tile* tile = nullptr;
   if (index >= 0 && index < listSize) {
      int count = 0;
      Node* current = head;
      while (count < index) {
         ++count;
         current = current->next;
      }
      tile = current->tile;
   }
   return tile;
}