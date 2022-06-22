#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int MCD_esteso(int a, int b, int* s_prev, int* t_prev){
        int r, q, temp;
        *s_prev = 1;
        *t_prev = 0;
        int s = 0, t = 1;

        while(b != 0){
            q = a / b;
            r = a % b;

            temp = s;
            s = *s_prev - q * s;
            *s_prev = temp;

            temp = t;
            t = *t_prev - q * t;
            *t_prev = temp;

            a = b;
            b = r;
        }
        return a;
}

int main()
{
    int a, b, N;
    int s, t;
    fstream inputFile;
    fstream outputFile;
    inputFile.open("input.txt", ios::in);
    outputFile.open("output.txt", ios::out);

    inputFile >> N;
    for( int i = 0; i < N; i++){
        inputFile >> a >> b;
        //if(a < b) std::swap(a, b);
        outputFile << s << " " << t  << " " << MCD_esteso(a, b, &s, &t) << '\n'; //Output Line Format: s t a( MCD(a,b));
    }
    inputFile.close();
    outputFile.close();
    return 0;
}
