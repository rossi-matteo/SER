#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

class Pair{
    public:
    int cIndex;
    int rIndex;

};

void input_dati(int* ,int, int ); //Funzione per l'acquisizione degli Archi in Input
void printMatrix(int*, int);      //Funzione di Stampa Matrice
Pair* minValue(int*, int);        //Funzione di ricerca del minimo valore presente nella Matrice
void delColumn(int*, int, int);   //Funzione di Cancellazione della Colonna
void kruskalMST(int*, int);       //Funzione che contiene l'algoritmo di KRuskal




int main(){
    FILE *input;
    int N, n_archi;
    input = freopen("inputA.txt","r", stdin);
    scanf("%d", &N);
    scanf("%d", &n_archi);
    freopen("output.txt","w", stdout);

    int* matrice = (int*) malloc(N*N*sizeof(int));
    input_dati(matrice,N, n_archi);
    fclose(input);


    kruskalMST(matrice,N);

    return 0;
}

void kruskalMST(int* matrice, int N){


    int counter = 0;

    Pair* edge[N-1]; //Struttura che contiene la coppia di indici i,j che individuano l'arco e il valore corrispondente
    int w[N-1];

    while(counter < N-1){

        edge[counter] = minValue(matrice, N);   //Salvo la coppia di indici restituita dalla funzione
        w[counter] = matrice[edge[counter]->rIndex*N+edge[counter]->cIndex]; //Salvo il peso dell'arco appena individuato
        delColumn(matrice, N, edge[counter]->cIndex);   //Elimino la colonna identificata da j
        matrice[(edge[counter]->cIndex*N+edge[counter]->rIndex)] = -1;  //Elimino il valore opposto in Tab, da escludere


        /*printMatrix(matrice,N);
        printf("\n");*/

        printf("%d,%d w: %d\n", edge[counter]->rIndex+1, edge[counter]->cIndex+1, w[counter]);  //Stampo l'arco individuato
        counter++;
    }
}

Pair* minValue(int* matrice, int N){
    Pair* p = new Pair();
    int minValue = INT_MAX;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(matrice[N*i+j] != -1 && matrice[N*i+j] != 0 && matrice[N*i+j] < minValue){  //Scarto i valori di -1(Ass. di connessione),
                minValue = matrice[N*i+j];                                                 // 0(Stesso Nodo), e i valori che non superano il minore
                p->rIndex = i;
                p->cIndex = j;
            }
        }
    }

    return p;
}

void delColumn(int *matrice, int N, int column){
    for(int i = 0; i < N; i++)
        matrice[i*N+column] = -1;
}

void input_dati(int* matrice, int N, int n_archi){

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
                if(i == j)
                    matrice[i*N+j] = 0;
                else
                    matrice[i*N+j] = -1;
        }
    }

    for(int i = 0 ; i < n_archi; i++){
        int src,dest,w;
        scanf("%d %d %d", &src, &dest, &w);
        src-=1;
        dest-=1;
        matrice[src*N+dest]=w;
        matrice[dest*N+src]=w;
    }

    printMatrix(matrice, N);
}

void printMatrix(int* matrice, int n){
        printf("- ");
    for(int i = 0; i < n; i++)
        printf("%3d", i);

    printf("\n");

    for(int i = 0 ; i < n; i++){
        printf("%d ", i);
        for(int j = 0 ; j < n; j++){
            printf("%2d ", matrice[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
}
