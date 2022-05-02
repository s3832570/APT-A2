
#include "LinkedList.h"
#include <iostream>

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
   if (head == tail) {
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

void LinkedList::remove(int index) {
   if (index >= 0 && index < listSize) {
      int count = 0;
      Node* nodeToBeRemoved = head;
      Node* prevNode = nullptr;
      while (count != index) {
         if(count == index - 1) {
            prevNode = nodeToBeRemoved;
         }
         ++count;
         nodeToBeRemoved = nodeToBeRemoved->next;
      }
      prevNode->next = nodeToBeRemoved->next;
      --listSize;
   }
}

void LinkedList::shuffle() {
   srand(100);
   for (int i = 0; i < listSize; i++)
   {
      int randNum = std::rand() % listSize;
      this->addTileBack(new Tile(*this->get(randNum)));
      this->remove(randNum);
   }
}