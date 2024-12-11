#ifndef CARD_H
#define CARD_H
using namespace std;

class Card {
    private:
        char suit;
        char rank;
    public:
        Card(char, char);
        Card();
        void print();
        int compare(Card);
};

#endif