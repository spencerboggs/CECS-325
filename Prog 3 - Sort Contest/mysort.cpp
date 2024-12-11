#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void bubble(int A[], int size) 
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 3){
        cout<<"Please enter 2 parameters: \n";
        cout<<"Arg 1: The input file name\n";
        cout<<"Arg 2: The output file name\n";
        cout<<"Example: $ mysort numbers.dat mysort.out\n";
        exit(EXIT_SUCCESS);
    }

    string filename = argv[1];
    string output = argv[2];

    int count = 0;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        count++;
    }
     
    file.clear();
    file.seekg(0, ios::beg);

    int numbers[1000000];
    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int num;
        ss >> num;
        numbers[i++] = num;
    }
    file.close();

    bubble(numbers, count);
    
    ofstream fout(output);
    for (int i = 0; i < count; i++) {
        fout << numbers[i] << endl;
    }
}