#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

void input_dati(int* ,int );
void printMatrix(int*, int);
int minValue(int[], bool[], int);
void printMST(int[], int*, int);
void MST_Prim(int*, int n);

int main(){
    FILE *in;
    int nVertici;
    in = freopen("input.txt", "r" , stdin);
    scanf("%d", &nVertici); //N Vertici

    int* matriceDati = (int*) malloc(nVertici * nVertici * sizeof(int));
    input_dati(matriceDati, nVertici);
    fclose(in);

    MST_Prim(matriceDati, nVertici);

    free(matriceDati);
    return 0;
}

void input_dati(int* matrice, int n){
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++){
            scanf("%d", &matrice[i*n+j]);
        }
    }
    printMatrix(matrice, n);
}

void printMatrix(int* matrice, int n){
        printf("- ");
    for(int i = 0; i < n; i++)
        printf("%d ", i);

    printf("\n");

    for(int i = 0 ; i < n; i++){
        printf("%d ", i);
        for(int j = 0 ; j < n; j++){
            printf("%d ", matrice[i*n+j]);
        }
        printf("\n");
    }
}

void printMST(int parent[], int* matrice, int n){
    printf("\n");
    printf("Arco \tPeso\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d\t %d \n", parent[i], i, matrice[i*n+parent[i]]);

}

int minValue(int value[], bool MST_Status[], int n){
    int min = INT_MAX, min_index = 0;

    for (int i = 0; i < n; i++)
        if (MST_Status[i] == false && value[i] < min){
            min = value[i];
            min_index = i;
        }

    return min_index;
}

void MST_Prim(int* matrice, int n){

    int parent[n];
    int key[n];
    bool MST_Status[n]; //Matrice che rappreenta lo stato attutale di archi inclusi nel MST

    for (int i = 0; i < n; i++)
        key[i] = INT_MAX, MST_Status[i] = false;

    key[0] = 0;  //Nodo di partenza escluso
    parent[0] = -1;

    for (int c = 0; c < n - 1; c++)
    {
        int u = minValue(key, MST_Status, n);

        MST_Status[u] = true; //Modifico lo stato del nodo individuato
        for (int i = 0; i < n; i++){
            if (matrice[u*n+i] && MST_Status[i] == false && matrice[u*n+i] < key[i]) //Analizzo la matrice, escludo i valori di colonne già incluse
                parent[i] = u;
                key[i] = matrice[u*n+i];
        }
    }

    printMST(parent, matrice, n);
}




