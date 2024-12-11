#include <iostream>
#include "card.h"
using namespace std;

Card::Card(char s, char r)
{
    suit = s;
    rank = r;
}

Card::Card()
{
    suit;
    rank;
}

void Card::print()
{
    if (rank == '0')
    {
        cout << "10" << suit << " ";
    }
    else
    {
        cout << rank << suit << " ";
    }
}

int Card::compare(Card secondCard)
{
    int firstCardRank = 0;
    if (rank == '0')
    {
        firstCardRank = 10;
    }
    else if (rank == 'J')
    {
        firstCardRank = 11;
    }
    else if (rank == 'Q')
    {
        firstCardRank = 12;
    }
    else if (rank == 'K')
    {
        firstCardRank = 13;
    }
    else if (rank == 'A')
    {
        firstCardRank = 1;
    }
    else
    {
        firstCardRank = (int)rank - '0';
    }

    int secondCardRank = (int)secondCard.rank;
    if (secondCard.rank == '0')
    {
        secondCardRank = 10;
    }
    else if (secondCard.rank == 'J')
    {
        secondCardRank = 11;
    }
    else if (secondCard.rank == 'Q')
    {
        secondCardRank = 12;
    }
    else if (secondCard.rank == 'K')
    {
        secondCardRank = 13;
    }
    else if (secondCard.rank == 'A')
    {
        secondCardRank = 1;
    }
    else
    {
        secondCardRank = (int)secondCard.rank - '0';
    }
    if (firstCardRank > secondCardRank)
    {
        return 1;
    }
    else if (firstCardRank < secondCardRank)
    {
        return -1;
    }
    
    return 0;
}