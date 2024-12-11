#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

class Card
{
private:
    char suit;
    char rank;

public:
    Card(char s, char r)
    {
        suit = s;
        rank = r;
    }

    void print()
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

    int compare(Card secondCard)
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
};

class Deck
{
private:
    vector<Card> cards;
    int topCardIndex;

public:
    Deck()
    {
        vector<Card> tempDeck = {
            Card('D', '2'),
            Card('D', '3'),
            Card('D', '4'),
            Card('D', '5'),
            Card('D', '6'),
            Card('D', '7'),
            Card('D', '8'),
            Card('D', '9'),
            Card('D', '0'),
            Card('D', 'J'),
            Card('D', 'Q'),
            Card('D', 'K'),
            Card('D', 'A'),
            Card('C', '2'),
            Card('C', '3'),
            Card('C', '4'),
            Card('C', '5'),
            Card('C', '6'),
            Card('C', '7'),
            Card('C', '8'),
            Card('C', '9'),
            Card('C', '0'),
            Card('C', 'J'),
            Card('C', 'Q'),
            Card('C', 'K'),
            Card('C', 'A'),
            Card('H', '2'),
            Card('H', '3'),
            Card('H', '4'),
            Card('H', '5'),
            Card('H', '6'),
            Card('H', '7'),
            Card('H', '8'),
            Card('H', '9'),
            Card('H', '0'),
            Card('H', 'J'),
            Card('H', 'Q'),
            Card('H', 'K'),
            Card('H', 'A'),
            Card('S', '2'),
            Card('S', '3'),
            Card('S', '4'),
            Card('S', '5'),
            Card('S', '6'),
            Card('S', '7'),
            Card('S', '8'),
            Card('S', '9'),
            Card('S', '0'),
            Card('S', 'J'),
            Card('S', 'Q'),
            Card('S', 'K'),
            Card('S', 'A'),
        };
        cards = tempDeck;
        topCardIndex = 0;
    }
    Card deal()
    {
        if (isEmpty())
        {
            throw -1;
        }
        Card dealtCard = cards[topCardIndex];
        topCardIndex++;
        return dealtCard;
    }
    void print()
    {
        for (int i = 0; i < 52; i++)
        {
            cards[i].print();
        }
    }
    void shuffle()
    {
        random_shuffle(cards.begin(), cards.end());
    }
    bool isEmpty()
    {
        return topCardIndex >= 52;
    }
};
int main()
{
    srand(time(0));
    string player1 = "";
    string player2 = "";
    cout << "Enter the name of the first player: ";
    cin >> player1;
    cout << "Enter the name of the second player: ";
    cin >> player2;
    int gameAmount;
    cout << "How many games will they play? ";
    cin >> gameAmount;
    Deck mainDeck;
    cout << endl;
    cout << "Original Deck" << endl;
    mainDeck.print();
    cout << "\n"
         << endl;
    mainDeck.shuffle();
    cout << "Shuffled Deck" << endl;
    mainDeck.print();
    cout << endl;
    int player1score = 0, player2score = 0;
    int ties = 0, player1losses = 0, player2losses = 0;
    for (int i = 0; i < gameAmount; ++i)
    {
        try
        {
            Card player1card = mainDeck.deal();
            Card player2card = mainDeck.deal();
            cout << "Game " << i + 1 << endl;
            cout << "--------" << endl;
            cout << "\t" << player1 << "=>";
            player1card.print();
            cout << endl;
            cout << "\t" << player2 << "=>";
            player2card.print();
            cout << endl;
            int result = player1card.compare(player2card);
            if (result == 1)
            {
                player1score++;
                player2losses++;
                cout << player1 << "=> Winner\n"
                     << endl;
            }
            if (result == 0)
            {
                ties++;
                cout << "Tie Game\n"
                     << endl;
            }
            if (result == -1)
            {
                player2score++;
                player1losses++;
                cout << player2 << "=> Winner\n"
                     << endl;
            }
        }
        catch (int)
        {
            cout << "Error - Deck is empty" << endl;
            break;
        }
    }
    cout << "------Final Stats-------" << endl;
    cout << "\t" << player1 << " vs. " << player2 << endl;
    cout << "Wins\t" << player1score << "\t " << player2score << endl;
    cout << "Losses\t" << player1losses << "\t " << player2losses << endl;
    cout << "Ties\t" << ties << "\t " << ties << endl;
    return 0;
}