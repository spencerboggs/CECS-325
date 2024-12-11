#ifndef DECK_H
#define DECK_H
using namespace std;

class Deck
{
private:
    Card cards[52];
    int topCardIndex;

public:
    Deck();
    Card deal();
    void print();
    void shuffle();
};

#endif