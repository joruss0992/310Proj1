#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "defns.h"

using namespace::std;


int main(){
    struct symbol Symbols[NSYMBOLS];    //Symbols array for structure

    ifstream file;
    file.open("pre-file.txt");

    if(file.fail()){
        cerr << "Error openning file" << endl;
        exit(1);
    }

    for(int ii = 0; ii<NSYMBOLS; ii++){ //Initializing every symbol structure inside array
        Symbols[ii].freq = 0;   //Frequency set to 0
        Symbols[ii].symbol = ii;    //Symbol set simply to current iteration's number
        Symbols[ii].parent = NULL;  //All pointers set to NULL
        Symbols[ii].left = NULL;
        Symbols[ii].right = NULL;
        Symbols[ii].encoding[0] = '\0'; //Encoding array set to Null
    }
    
    string s;
    int counter = 0;
    int curIn = 0;

    int a;
    while (file >> a){
        if(counter % 2 == 0){
            curIn = a;
            cout << a << " Counter: " << counter << endl;
            counter++;
        }
        else{
            cout << a << " Counter: " << counter << endl;
            counter++;
            Symbols[curIn].freq = a;
            cout << "Frequency of " << curIn << ", Increased to " << a << endl;
        }
    }

    return 0;
}
