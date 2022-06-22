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
        std::vector<char>::iterator it = std::find(  alfabeto.begin(),  alfabeto.end(),  str.at(i) );
        numValue = std::distance( alfabeto.begin(), it);
        //cout << numValue << str.at(i) << endl;
        M += numValue * pow( alfabeto.size(), (str.size()-i-1) );
    }
    return M;
}

string decifratura (unsigned long long msgCifrato ){
    char arr[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string strChiaro;

    while(msgCifrato != 0){
        strChiaro += arr[msgCifrato % alph_base];
        msgCifrato /= alph_base ;

        cout << strChiaro << " " ;
    }

    return string(strChiaro.rbegin(), strChiaro.rend());
}

int main()
{
    string str;

    cout << "Inserisci una stringa:" << endl;
    std::getline(std::cin, str);

    std::vector <string> msgBlock;
    std::vector <string>::iterator it;

    int i = 0, lastIndex = 0;

    const int STEP = 5;
    do{
        lastIndex += STEP;
        if(STEP > str.size() )
            lastIndex = str.size();


        msgBlock.push_back(str.substr( i, lastIndex - 1));

        i+= STEP;
        if( i > str.length())
            i = str.length();

    }while( i < str.length() );

     for( it = msgBlock.begin() ; it != msgBlock.end(); ++it){
        msgBlock.insert(it, std::to_string(cifratura(*it)));
        cout << *it << " ";
     }
     cout << endl;

    //cout << "Stringa in chiaro:" << decifratura(msgCifrato) << endl;

    return 0;
}




