#include <iostream>
#include <ctime>
#include <cstdlib>
#include "card.h"
#include "deck.h"
using namespace std;

int main()
{
    srand(time(0));
    string player1 = "";
    string player2 = "";

    cout << "Enter the name of the first player: ";
    cin >> player1;

    cout << "Enter the name of the second player: ";
    cin >> player2;

    Deck mainDeck;
    cout << endl;
    cout << "Original Deck" << endl;
    mainDeck.print();
    cout << "\n" << endl;
    mainDeck.shuffle();
    cout << "Shuffled Deck" << endl;
    mainDeck.print();
    cout << endl;
    int player1score = 0, player2score = 0;
    int ties = 0, player1losses = 0, player2losses = 0;
    for (int i = 0; i < 26; ++i)
    {
        cout << "Game " << i + 1 << endl;
        cout << "--------" << endl;
        Card player1card = mainDeck.deal();
        Card player2card = mainDeck.deal();
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
    cout << "------Final Stats-------" << endl;
    cout << "\t" << player1 << " vs. " << player2 << endl;
    cout << "Wins\t" << player1score << "\t " << player2score << endl;
    cout << "Losses\t" << player1losses << "\t " << player2losses << endl;
    cout << "Ties\t" << ties << "\t " << ties << endl;
    return 0;
}