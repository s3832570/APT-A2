
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
   this->head = nullptr;
   this->tail = nullptr;
   listSize = 0;
}

LinkedList::~LinkedList()
{
}

int LinkedList::getListSize()
{
   return listSize;
}

void LinkedList::addFront(Tile *tile)
{
   Node *node = new Node();
   node->tile = tile;
   node->next = head;
   head = node;
   ++listSize;
}

Node *LinkedList::getFront()
{
   // Node* head = head;
   // Tile* tile = head->tile;
   return head;
}

void LinkedList::addBack(Tile *tile)
{
   Node *node = new Node();

   // tail->next = node;
   node->next = nullptr;
   node->tile = tile;

   if (head == nullptr)
   {
      head = node;
   }
   else
   {
      tail->next = node;
      tail = node;
      tail->next = nullptr;
   }

   tail = node;
   ++listSize;
}

void LinkedList::removeFront()
{
   if (head == tail)
   {
      head = nullptr;
      tail = nullptr;
   }
   else if (head != tail)
   {
      head = head->next;
   }
   --listSize;
}

Node *LinkedList::get(int index)
{
   Node *node = nullptr;
   if (index >= 0 && index < listSize)
   {
      int count = 0;
      Node *current = head;
      while (count != index)
      {
         ++count;
         current = current->next;
      }
      node = current;
   }
   return node;
}

void LinkedList::remove(int index)
{
   if (index >= 0 && index < listSize)
   {
      int count = 0;
      Node *nodeToBeRemoved = head;
      Node *prevNode = nullptr;
      while (count != index)
      {
         // if(count == index - 1) {
         //    prevNode = nodeToBeRemoved;
         // }
         ++count;
         prevNode = nodeToBeRemoved;
         nodeToBeRemoved = nodeToBeRemoved->next;
      }
      if (prevNode == nullptr)
      {
         head = nodeToBeRemoved->next;
      }
      else
      {
         prevNode->next = nodeToBeRemoved->next;
      }
      // prevNode->next = nodeToBeRemoved->next;
      --listSize;
   }
}

void LinkedList::shuffle()
{
   srand(100);
   for (int i = 0; i < listSize; i++)
   {
      int randNum = std::rand() % listSize;
      this->addBack(get(randNum)->tile);
      this->remove(randNum);
   }
}