
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
   this->head = nullptr;
   this->tail = nullptr;
   listSize = 0;
}

LinkedList::LinkedList(LinkedList &other)
{
   head = nullptr;
   tail = nullptr;
   listSize = 0;
   for (int i = 0; i < other.getListSize(); ++i)
   {
      Tile *tile = new Tile(other.get(i)->tile->getLetter(), other.get(i)->tile->getValue());
      addTileBack(tile);
   }
}

LinkedList::~LinkedList()
{
   clear();
}

int LinkedList::getListSize()
{
   return listSize;
}

void LinkedList::addTileFront(Tile *tile)
{
   Node *node = new Node(tile, head);
   if (listSize == 0)
   {
      head = node;
      tail = node;
   }
   else
   {
      head = node;
   }
   ++listSize;
}

Node *LinkedList::getTileFront()
{
   return head;
}

void LinkedList::addTileBack(Tile *tile)
{
   Node *node = new Node();
   node->tile = tile;
   node->next = nullptr;

   if (head == nullptr)
   {
      head = node;
   }
   else
   {
      Node *current = head;
      while (current->next != nullptr)
      {
         current = current->next;
      }
      current->next = node;
   }

   ++listSize;
}

void LinkedList::removeTileFront()
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
   if (index >= 0 && index <= listSize)
   {
      int count = 0;
      Node *current = head;
      while (count != index)
      {
         current = current->next;
         count++;
      }
      node = current;
   }

   return node;
}

void LinkedList::remove(int index)
{
   if (head == nullptr)
   {
      return;
   }
   Node *node = head;
   if (index == 0)
   {
      head = head->next;
      --listSize;
      return;
   }
   for (int i = 0; node != NULL && i < index - 1; i++)
      node = node->next;

   Node *next = node->next->next;

   node->next = next;
   --listSize;
}

void LinkedList::add(Tile *tile, int index)
{
   Node *node = head;

   if (index == 0)
   {
      Node *node = new Node(tile, head);
      head = node;
   }

   if (index > 0)
   {
      int count = 0;
      while (count != index - 1)
      {
         node = node->next;
         ++count;
      }
      Node *newNode = new Node(tile, node->next);
      node->next = newNode;
   }
   ++listSize;
}

void LinkedList::clear()
{
   while (head != nullptr)
   {
      removeTileFront();
   }
}

void LinkedList::shuffle()
{
   srand(100);
   for (int i = 0; i < listSize; i++)
   {
      int randNum = std::rand() % listSize;
      this->addTileBack(get(randNum)->tile);
      this->remove(randNum);
   }
}
