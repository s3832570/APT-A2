#include "TileBag.h"

TileBag::TileBag() {
    tileBag = new  LinkedList();
}

TileBag::TileBag(TileBag& other) {
    tileBag = new LinkedList(*other.tileBag);
}

TileBag::~TileBag() {
    delete tileBag;
}

Tile TileBag::getNewTile() {
    return *tileBag->getFront();
}

void TileBag::removeTile() {
    tileBag->removeFront();
}

void TileBag::shuffleBag() {
    tileBag->shuffle();
}