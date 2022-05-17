
#include "Node.h"

// Create Node
Node::Node()
{
}

// Create Node with Tile and next Pointer
Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

// Copy Node
Node::Node(Node& other)
{
   this->tile = other.tile;
   this->next = other.next;
}

// Node Delete
Node::~Node()
{
   delete tile;
}