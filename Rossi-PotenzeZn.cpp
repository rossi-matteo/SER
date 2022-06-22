#include <iostream>
#include <fstream>

using namespace std;


int potenzaZn(int b, int e, int zn){

    int part = b;

    for(int i = 0 ; i < e-1; i++){
            part = (unsigned long int)(b * part) % zn;
    }
    return part;

}

int main()
{
    int b, e, N, zn;
    fstream inputFile;
    fstream outputFile;
    inputFile.open("input.txt", ios::in);
    outputFile.open("output.txt", ios::out);

    inputFile >> N;

    for( int i = 0; i < N; i++){
        inputFile >> b >> e >> zn;
        outputFile << potenzaZn(b, e, zn) << '\n';
    }

    inputFile.close();
    outputFile.close();
    return 0;
}
