#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

class Arco{
    public:
        int sorgente;
        int destinazione;
        int peso;
};

void MST_Kruskal(Arco*, int, int);
void input_dati(Arco*, int);




int main(){
    FILE *in;
    int n, a;
    in = freopen("inputA.txt", "r" , stdin);
    scanf("%d", &n); //N Nodi
    scanf("%d", &a); //N Archi

    Arco *input = new Arco[a];

    input_dati(input, a);
    fclose(in);
    freopen("output.txt","w", stdout);

    MST_Kruskal(input, n, a);

    return 0;
}

void input_dati(Arco *input, int a){
    for(int i = 0; i < a; i++){
        int s, d, p;
        scanf("%d %d %d", &s, &d, &p);
        input[i].sorgente  = s-1;
        input[i].destinazione = d-1;
        input[i].peso = p;
    }

}

bool compare(Arco a1, Arco a2){
    return (a1.peso < a2.peso); //Se vero ritorna True, altrimenti False
}

int trovaAlbero(int valore, int *albero){
    if(valore == albero[valore])  //Se l'inizio o la fine dell'albero è l'arco in analisi, ritorno il suo valore
        return valore;
    else
        return trovaAlbero(albero[valore], albero); //Altrimenti cerco se il lato collegato coincide con l'inizio o la fine (Risalgo l'albero fino a uno degli inizi
}

void stampa_MST(Arco* output, int n){
    printf("MST\nDa\tA\tPeso\n");
    for(int i = 0 ; i < n-1; i++){
        if(output[i].sorgente < output[i].destinazione)
            printf("%d\t%d\t%d\n", output[i].sorgente, output[i].destinazione, output[i].peso);
        else
            printf("%d\t%d\t%d\n", output[i].destinazione, output[i].sorgente, output[i].peso);
    }

}

void MST_Kruskal(Arco* input, int n, int a){
    int costoTotale = 0;
    //Ordinare in modo crescente gli archi in base al peso
    sort(input, input+a, compare); //Funzione Offerta dal C++

    int* albero = new int[n]; //Inizializzo un vettore di alberi disgiunti costituiti da un solo nodo, se stesso
    for(int i = 0; i < n; i++)
        albero[i] = i;

    Arco* output = new Arco[n-1];
    int counter = 0;
    int i = 0;

    while(counter < n-1){           //L'albero è MST se ha N-1 archi
        Arco arcoCorrente = input[i];
    //Verifico se posso includere l'arco al MST
        int alberoSorgente = trovaAlbero(arcoCorrente.sorgente, albero);
        int alberoDestinazione = trovaAlbero(arcoCorrente.destinazione, albero);
        if(alberoSorgente != alberoDestinazione){       //Se l'albero intermedio non è ciclico, lo includo al MST
            output[counter] = arcoCorrente;
            output[counter].sorgente+=1;
            output[counter].destinazione+=1;
            albero[alberoSorgente] = alberoDestinazione;
            costoTotale += output[counter++].peso;
        }
        i++;   //Proseguo al prossimo arco
    }
    printf("%d\n", costoTotale);
    stampa_MST(output, n);
}
