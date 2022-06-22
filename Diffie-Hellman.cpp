#include <iostream>

using namespace std;
int g = 5;
int p = 17;
int a = 7;
int b = 13;

unsigned int potenzaZn( int b, int e, int zn){

    long long int part = b;
    long long int molt_parziale = 0;

    for(int i = 0 ; i < e-1; i++){
            molt_parziale = b * part;
            part = (b * part) % zn;
    }
    //cout << "Potenze Calcolate:"  << part << endl;
    return part;
}

int mittente( int g, int p ,int a){
    int A = potenzaZn(g, a , p);
    return A;
}

int destinatario(int g, int p, int b){
    int B = potenzaZn(g, b , p);
    return B;
}


int main()
{
    int A = mittente(g, p ,a);
    int B = destinatario(g, p, b);
    int kA = potenzaZn(B, a, p);
    int kB = potenzaZn(A, b, p);

    if( kA == kB )
       cout << "Chiave Simmetrica: " << kA << endl;

    return 0;
}
