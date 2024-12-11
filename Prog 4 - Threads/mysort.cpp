#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <array>
#include <mutex>
using namespace std;

long long swaps = 0;
mutex m;

void bubble(int A[], int size, int process) 
{
    long long swapCount = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
                swapCount++;
            }
        }
    }
    m.lock();
    swaps += swapCount;
    cout << "Process " << process << " swap count: " << swapCount << endl;
    m.unlock();
}


void merge(int* left, int* right, int segmentSize) 
{
    int* temp = new int[segmentSize * 2];
    int* leftEnd = left + segmentSize;
    int* rightEnd = right + segmentSize;
    int i = 0;

    while (left < leftEnd && right < rightEnd) {
        if (*left < *right) {
            temp[i++] = *left++;
        } else {
            temp[i++] = *right++;
        }
    }

    while (left < leftEnd) temp[i++] = *left++;
    while (right < rightEnd) temp[i++] = *right++;

    for (int n = 0; n < segmentSize * 2; n++) {
        *(leftEnd - segmentSize + n) = temp[n];
    }

    delete[] temp;
}

int main(int argc, char *argv[]) 
{
    if (argc != 3 && argc != 4) {
        cout<<"Please enter 2 parameters: \n";
        cout<<"Arg 1: The input file name\n";
        cout<<"Arg 2: The output file name\n";
        cout<<"Example: $ mysort numbers.dat mysort.out\n";
        exit(EXIT_SUCCESS);
    }

    string filename = argv[1];
    string output = argv[2];
    string testmode;

    if (argc == 4) {
        testmode = argv[3];
    }

    int count = 0;
    ifstream file(filename);
    string line;


    if (testmode == "-test") {
        count = 10000;
    } else {
        count = 1000000;
    }

    int* numbers = new int[count];

    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int num;
        ss >> num;
        numbers[i++] = num;
    }
    file.close();

    constexpr int threadCount = 16;
    int segmentSize = count / threadCount;
    array<thread, threadCount> threads;

    for (int i = 0; i < threadCount; i++) {
        int* start = numbers + (i * segmentSize);
        threads[i] = thread(bubble, start, segmentSize, i);
    }

    for (thread& t : threads) {
        t.join();
    }

    for (int step = 2; step <= threadCount; step *= 2) {
        for (int i = 0; i < threadCount; i += step) {
            merge(numbers + (i * segmentSize), numbers + ((i + step / 2) * segmentSize), segmentSize * (step / 2));
        }
    }
    
    ofstream fout(output);
    for (int i = 0; i < count; i++) {
        fout << numbers[i] << endl;
    }

    // i closed the ofstream! o7
    fout.close();
    delete[] numbers;

    cout << "Total Swaps: " << swaps << endl;
}