// Jacob Russ
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "defns.h"

using namespace::std;

int *inSort(struct tree arr[], int size) {
    for(int i = 1; i < size; i++){
        int key = arr[i].freq;
        int ii = i - 1;
        while(ii >= 0 && arr[ii].freq > key){
            arr[ii + 1] = arr[ii];
            ii = ii - 1;
        }
        arr[ii + 1].freq = key;
    }
    return 0;
}


int main(int argc,char* argv[]){
    struct symbol Symbols[NSYMBOLS];    // Symbols array for structure

    ifstream file;  
    file.open("pre-file.txt");  // Opens pre-file.txt

    if(file.fail()){    // Makes sure the file is acutally open
        cerr << "Error openning file" << endl;
        exit(1);
    }

    for(int ii = 0; ii<NSYMBOLS; ii++){ // Initializing every symbol structure inside array
        Symbols[ii].freq = 0;   // Frequency set to 0
        Symbols[ii].symbol = ii;    // Symbol set simply to current iteration's number
        Symbols[ii].parent = NULL;  // All pointers set to NULL
        Symbols[ii].left = NULL;
        Symbols[ii].right = NULL;
        Symbols[ii].encoding[0] = '\0'; // Encoding array set to Null
    }
    
    string s;   // String pre-file contents are stored in
    int counter = 0;    // General counter
    int curIn = 0;  // Keeps track of current character
    int AC = 0;     // Alpha Counter
    int NAC = 0;    // Non Alpha Counter
    int a;  // a is the number currenntly being extracted from pre-file
    
    while (file >> a){      // While there is input, 
        if(counter % 2 == 0){   // If the input is Even
            curIn = a;  // It is the current Char value 
            counter++;  // Increment the counter because, 
        }
        else{   // else it is the frequncy for the current Char
            counter++;  // Increment the counter
            Symbols[curIn].freq = a;    // set the current Char's frequency to a
            if((curIn >= 65 && curIn <= 90) || (curIn >= 97 && curIn <= 122)){  // This checks if Char is Alphabetic
                AC++;   // If so keep track of total number of Alphabetic Char's

            }
            else{
                NAC++;  // Else, it is a NonAlphabetic Char

            }

        }
    }
    int Ai = 0; // index for Alpha
    int NAi = 0;    // idex for NonAlpha

    struct tree Alpha[AC];  // initializing Alpha and NonAlpha Tree structures
    struct tree NonAlpha[NAC];

    for(int i=0; i<NSYMBOLS; i++){  //Loops through all ASCII characters
        if(Symbols[i].freq != 0){   //Stops when a structure with non-zero freq found
            if((i >= 65 && i <= 90) || (i >= 97 && i <= 122)){  // If the current value is Alphabetic
                Alpha[Ai].index = i;    // Initialize the Alpha array values for given index
                Alpha[Ai].freq = Symbols[i].freq;
                Alpha[Ai].symbol = Symbols[i].symbol;
                Alpha[Ai].root = &Symbols[i];
                Ai++;
            }
            else{   // Initialize the NonAlpha array values for given index
                NonAlpha[NAi].index = i;
                NonAlpha[NAi].freq = Symbols[i].freq;
                NonAlpha[NAi].symbol = Symbols[i].symbol;
                NonAlpha[NAi].root = &Symbols[i];
                NAi++;
            }
        }
    }  

    string sort = argv[2];
    if(sort == "insertion") {
        int *b = inSort(Alpha, Ai);
        int *c = inSort(NonAlpha , NAi);
    }
    else {
        int *b = inSort(Alpha, Ai);
        int *c = inSort(NonAlpha , NAi);
    }

    // Ai is the number of nodes in Alpha
    struct symbol *t = new symbol;
    t->parent = NULL;
    int stop;
    while(Ai > 2){
        for(int i = 0; i < 1; i++){
            t->left = Alpha[i].root;
            t->right = Alpha[i+1].root;
            t->freq = Alpha[i].freq + Alpha[i+1].freq;
            for(stop = 0; stop < Ai; stop++){
                Alpha[stop] = Alpha[stop + 1];
                Ai--;
                Alpha[AC - 1];
            }

        }
    }
    
    return 0;
}
