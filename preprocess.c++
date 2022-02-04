// Jacob Russ

#include <iostream>
#include <string>
#include <cstdlib>
#include "defns.h"

using namespace::std;

int main(){
    struct symbol Symbols[NSYMBOLS];    //Symbols array for structure

    for(int ii = 0; ii<NSYMBOLS; ii++){ //Initializing every symbol structure inside array
        Symbols[ii].freq = 0;   //Frequency set to 0
        Symbols[ii].symbol = ii;    //Symbol set simply to current iteration's number
        Symbols[ii].parent = NULL;  //All pointers set to NULL
        Symbols[ii].left = NULL;
        Symbols[ii].right = NULL;
        Symbols[ii].encoding[0] = '\0'; //Encoding array set to Null
    }
    
    string s;   // string s will be assigned contents of input
                            
    // Begin the preprocessing algorithm
    while(getline(cin, s)){ //While there is input
        Symbols[10].freq++; //Begin by counting newline character
        for(int ii=0; ii<(s.size()); ii++){   //Iterate through the line char by char
                Symbols[s[ii]].freq++;  //Where there's a char, the corresponding freq is incremented
        }
    }

    for(int i=0; i<NSYMBOLS; i++){  //Loops through all ASCII characters
        if(Symbols[i].freq != 0){   //Stops when letters contained in s are found due to incremented freq
            cout << i << "\t" << Symbols[i].freq++ << "\n"; //Prints formatted output to txt file
        }
    }
    return 0;
}