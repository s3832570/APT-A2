
#include "LinkedList.h"
#include <iostream>

// Create Linked List
LinkedList::LinkedList()
{
   this->head = nullptr;
   this->tail = nullptr;
   listSize = 0;
}

// Copy Linked List
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

// Clear Linked List
LinkedList::~LinkedList()
{
   clear();
}

// Return Linked List Size
int LinkedList::getListSize()
{
   return listSize;
}

// Add Tile to Front of Linked List
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

// Get Tile from Front of Linked List
Node *LinkedList::getTileFront()
{
   return head;
}

// Add tile to the back of Linked List
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

// Remove Tile from Front of Linked List
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

// Get Index in Linked List
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

// Remove Tile at Index in Linked List
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

// Add Tile at Index in Linked List
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

// Clear Linked List
void LinkedList::clear()
{
   while (head != nullptr)
   {
      removeTileFront();
   }
}
