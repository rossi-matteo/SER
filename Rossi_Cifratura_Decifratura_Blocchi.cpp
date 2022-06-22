#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <string>


using namespace std;
int alph_base = 27;


int cifratura(string str){
    char arr[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::vector <char> alfabeto( arr, arr + sizeof(arr) / sizeof(arr[0]));
    int numValue;
    int M = 0;

    for( int i = 0; i < str.size(); i++){
        std::vector<char>::iterator it = std::find(  alfabeto.begin(),  alfabeto.end(),  str.at(i)  );
        numValue = std::distance( alfabeto.begin(), it);
        //cout << numValue << str.at(i) << endl;
        M += numValue * pow( alfabeto.size(), (str.size()-i-1) ); // Spazi " " a inizio stringa non aggiungono valore al num pecrché 0*k, quindi non possono essere trovati in decodifica
    }
    return M;
}

string decifratura (int msgCifrato ){
    char arr[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string strChiaro;

    while(msgCifrato != 0){
        strChiaro += arr[msgCifrato % (alph_base) ];
        msgCifrato /= (alph_base);

        //cout << strChiaro << ',' ;
    }
    cout << endl << "Creato Questo:|" << strChiaro << "|" <<endl;
    return string(strChiaro.rbegin(), strChiaro.rend());
}

int main()
{

    string str;

    cout << "Inserisci una stringa:" << endl;
    std::getline(std::cin, str);

    std::vector <string> msgBlock;

    int i = 0;

    const int STEP = 5;
    do{
        msgBlock.push_back( str.substr( i, STEP));
        i+= STEP;
    }while( i < str.length() );

    i = 0;
    std::vector <int> cypherData;
    for( std::vector <string>::iterator it = msgBlock.begin(); it != msgBlock.end(); ++i, ++it){
        cout << msgBlock.at(i) << ",";
        cypherData.push_back(cifratura( *it )) ;
        cout << cypherData.at(i) << ".";
     }
     cout << endl;

    for( std::vector <int>::iterator it = cypherData.begin() ; it != cypherData.end(); ++it){
        cout << decifratura( *it ) ;
     }
     cout << endl;

    return 0;
}




