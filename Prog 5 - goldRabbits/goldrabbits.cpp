#include <iostream>
#include <time.h>
#include <iomanip>
#include <map>
using namespace std;

int fiboCount = 0;

int goldRabbits(int n) {
    static map<int, int> map;
    fiboCount++;

    if (map.find(n) != map.end()) {
        return map[n];
    }

    if (n == -1) {
        cout << "Fibo Map" << endl;
        cout << "--------" << endl;
        for (auto& [key, value] : map) {
            cout << setw(3) << key << ": " << setw(11) << value << endl;
        }
        exit(0);
    }

    if (n == 0 || n == 1) {
        map[n] = 1;
        return 1;
    }

    int step = goldRabbits(n - 1) + goldRabbits(n - 2);
    if (goldRabbits(n - 1) + goldRabbits(n - 2) < 0) {
        throw overflow_error("Overflow at fibo(" + to_string(n) + ")");
    }

    map[n] = step;
    return step;
}

int main() {
    int const months = 12 * 10;
    int start = time(0);
    try {
        for (int i = 0; i < months; i++) {
            int current = time(0);
            cout << setw(5) << current - start << ":";
            cout << " GoldRabbits(" << setw(2) << i << ") = ";
            cout << setw(11) << goldRabbits(i);
            cout << setw(14) << "fiboCount: " << setw(4) << fiboCount << endl;
        }   
    } catch (overflow_error& e) {
        cout << "\n" << e.what() << endl;
        goldRabbits(-1);
    }
}