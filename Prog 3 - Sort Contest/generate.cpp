#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
    srand(0);

    if (argc != 4){
        cout<<"Please enter 3 parameters: \n";
        cout<<"Arg 1: Total count of numbers\n";
        cout<<"Arg 2: Min value. \n";
        cout<<"Arg 3: Max value. \n";
        cout<<"Example: $ generate 1000000 -100000 100000\n";
        exit(EXIT_SUCCESS);
    }

    cout << "argv[0]:" << argv[0] << endl;
    cout << "argv[1]:" << argv[1] << endl;
    cout << "argv[2]:" << argv[2] << endl;
    cout << "argv[3]:" << argv[3] << endl;
    
    int count = atoi(argv[1]);
    int low = atoi(argv[2]);
    int high = atoi(argv[3]);
    
    ofstream fout ("numbers.dat");
    
    for (int i = 0; i < count; i++) {
        int number = rand() % (high - low + 1) + low;
        fout << number << endl;
    }

    fout.close();
    return 0;
}