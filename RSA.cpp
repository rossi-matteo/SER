#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <string>


using namespace std;

int p = 997; //MIO p = 31 //11
int q = 991; //MIO q = 7; //13
const int first_prime_n = 503; //Ricerca dal primo 13

char arr[] = { 0x0d, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x','y', 'z', ' '};
int alph_base = sizeof(arr) / sizeof(char) ;



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

void generazioneChiavi( int *e_pubblica, int *d_privata, int *n_chiavi ){
    int eul_n = (p-1)*(q-1);
    int t;
    int d_part;


    int e = first_prime_n ; //Partendo dal num primo scelto ;

    while(e < eul_n){
        int verify = MCD_esteso( e, eul_n, &d_part, &t);

        if( verify == 1) break;

        e++;
    }
    // CHIAVE 1: e , eul_N CHIAVE 2: inverso, eul_N

    if(d_part < 0)  //RICERCA DELL'INVERSO POSITIVO
        d_part += eul_n;

    *n_chiavi = p*q;
    *e_pubblica = e;
    *d_privata = d_part;




    return;
}

unsigned int cifratura(string str){
    std::vector <char> alfabeto( arr, arr + sizeof(arr) / sizeof(arr[0]));
    unsigned int numValue;
    unsigned int M = 0;

    for( unsigned int i = 0; i < str.size(); i++){
        std::vector<char>::iterator it = std::find(  alfabeto.begin(),  alfabeto.end(),  str.at(i)  );
        numValue = std::distance( alfabeto.begin(), it);
        //cout << numValue << str.at(i) << endl;
        M += (numValue) * (float) pow( alph_base, (str.size()-i-1) ); // Spazi " " a inizio stringa non aggiungono valore al num pecrché 0*k, quindi non possono essere trovati in decodifica
    }
    return M;
}

string decifratura (unsigned int msgCifrato ){
    string strChiaro;

    while(msgCifrato != 0){
        strChiaro += arr[ msgCifrato % (alph_base) ];
        msgCifrato /= (alph_base);

        //cout << strChiaro << ',' ;
    }
   // cout << endl << "Creato Questo:|" << strChiaro << "|" <<endl;
    return string(strChiaro.rbegin(), strChiaro.rend());
}

unsigned int potenzaZn( int b, int e, int zn){

    long long int part = b;
    long long int molt_parziale = 0; //Le due variabili sono long long int nonostante non conterranno mai un valore del genere per poter realizzare la moltiplicazione
    //Spunto da: https://stackoverflow.com/questions/51888482/multiply-2-large-numbers-in-c-have-wrong-result

    for(int i = 0 ; i < e-1; i++){


            molt_parziale = b * part;
            part = (b * part) % zn;
    }

    cout << "Potenze Calcolate:"  << part << endl;
    return part;

}


void crittografia(){


    string str;

    cout << "Inserisci una stringa:" << endl;
    std::getline(std::cin, str);


    std::vector <string> msgBlock;

    unsigned int i = 0;

    const int STEP = 4;
    do{
        msgBlock.push_back( str.substr( i, STEP));
        i+= STEP;
    }while( i < str.length() );

    i = 0;


    cout << "Conversione da caratteri a numeri:" << endl;

    std::vector <unsigned int> cypherData;
    for( std::vector <string>::iterator it = msgBlock.begin(); it != msgBlock.end(); ++i, ++it){
        cout << msgBlock.at(i) << ",";
        cypherData.push_back(cifratura( *it )) ;
        cout << cypherData.at(i) << ".";
     }
     cout << endl;


    int e_pubblica, d_privata, n_chiavi;
    generazioneChiavi( &e_pubblica, &d_privata, &n_chiavi);



    cout << "Chiave Pubblica(" << e_pubblica << ", " << n_chiavi << ")" << endl;
    cout << "Chiave Privata(" << d_privata << ", " << n_chiavi << ")" << endl;



    std::vector <unsigned int> transmittedData;

     for( std::vector <unsigned int>::iterator it = cypherData.begin(); it != cypherData.end(); ++it ){

         unsigned int numeroCrittografato = 0;

         numeroCrittografato = potenzaZn( *it, d_privata, n_chiavi );

         transmittedData.push_back( potenzaZn( numeroCrittografato, e_pubblica, n_chiavi));
     }

    //cout << "Ricevuto in trasmissione da decifrare:" << endl;
    for( std::vector <unsigned int>::iterator it = transmittedData.begin() ; it != transmittedData.end(); ++it){
        //cout << *it << endl;
        cout << decifratura( *it ) ;
     }
     cout << endl;

    return;
}



int main()
{
    crittografia();

    return 0;
}
