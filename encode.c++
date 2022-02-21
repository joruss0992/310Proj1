// Jacob Russ
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "defns.h"

using namespace::std;

int *inSort(struct tree arr[], int size) {  // This is my insertion sort array, takes tree array and size
    struct tree key[1]; // Temporary key for replacing shifting elements
    for(int i = 1; i < size; i++){  // for loop iterates through whole array
        key[0] = arr[i];    // key = arr[i]
        int ii = i - 1;     // ii = i - 1
        while(ii >= 0 && arr[ii].freq > key[0].freq){   // while front of array hasn't been reached AND freq's need to be switched 
            arr[ii + 1] = arr[ii];  // shifts nodes to the right, creating space at current node i
            ii = ii - 1;    // ii decremented, checking if the front of the array has been passed
        }
        arr[ii + 1] = key[0];   // current element being observed put into proper place
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

    string sort = argv[2];  // This checks if the given command is either insertion or merge
    if(sort == "insertion") {
        int *b = inSort(Alpha, Ai);
        int *c = inSort(NonAlpha , NAi);
    }
    else {
        int *b = inSort(Alpha, Ai);     // Merge sort needs to be implemented still
        int *c = inSort(NonAlpha , NAi);   
    }









    //  Alpha Binary Tree Function
    while(Ai != 1){
        struct symbol *t = new symbol;  // t pointer  to act as placeholder while building binary tree
        t->parent = NULL;   // Initialize t's parent to Null
    
        t->left = Alpha[0].root;    // Initializes t's left and right at beginning of each loop as  
        t->right = Alpha[1].root;   // Alpha[0] and Alpha[1]
        t->freq = Alpha[0].freq + Alpha[1].freq;    // Adds the frequency together

        Alpha[0].root->parent = t;
        Alpha[1].root->parent = t;

        //  This section deletes nodes at A[0], and A[1]
        //  ----------------------------------------------------  //
       for(int stop = 0; stop < 2; stop++){ // Ensures the loop only runs twice
                for(int j = 0; j < Ai-1; j++){  // From the beginning,
                    Alpha[j] = Alpha[j + 1];    // every node is shifted over to the left
                }
            Alpha[Ai-1].freq = 1000000; // Ensures 'deleted' element isn't used
            Ai--;   // After each iteration Alpha's size decreases
        }            
        //  ----------------------------------------------------  // 

        // Inserting t to alpha! 
        //  ----------------------------------------------------  // 
        // Beginning by finding the correct position t will be inserted into alpha
        //  ------------------------  //
        int p = 0;
        for(int ii = Ai; ii >= 0; ii--){    // Loop goes from end of Alpha to beginning
            if(t->freq >= Alpha[ii].freq){  // If t's freq is >= Alpha's current position, the correct location has been found
                p = ii + 1; 
                break;
            }
        }
        //  ------------------------  //

        //  Next space is made in Alpha for t and added to position p
        //  ------------------------  //
        for(int i = Ai; i > p; i--){
            Alpha[i] = Alpha[i - 1];    // Until p is reached, space is made for it
        }
        Alpha[p].freq = t->freq;
        Alpha[p].index = 0;     // Index and symbol = 0 because their values aren't being used
        Alpha[p].symbol = 0;
        Alpha[p].root = t;
        Ai++;   // Alpha's size grows after t is inserted
        //  ------------------------  //
    }
    






    //  NonAlpha Binary Tree
    //  This function is a exact copy of previous function for NONAlpha instead
    while(NAi != 1){
        struct symbol *t = new symbol;  // t pointer  to act as placeholder while building binary tree
        t->parent = NULL;   // Initialize t's parent to Null
    
        t->left = NonAlpha[0].root;    // Initializes t's left and right at beginning of each loop as  
        t->right = NonAlpha[1].root;   // NonAlpha[0] and NonAlpha[1]
        t->freq = NonAlpha[0].freq + NonAlpha[1].freq;    // Adds the frequency together

        NonAlpha[0].root->parent = t;
        NonAlpha[1].root->parent = t;

        //  This section deletes nodes at NA[0], and NA[1]
        //  ----------------------------------------------------  //
       for(int stop = 0; stop < 2; stop++){ // Ensures the loop only runs twice
            for(int j = 0; j < NAi-1; j++){  // From the beginning,
                NonAlpha[j] = NonAlpha[j + 1];    // every node is shifted over to the left
            }
            NonAlpha[NAi-1].freq = 1000000; // Ensures 'deleted' element isn't used
            NAi--;   // After each iteration Alpha's size decreases
        }            
        //  ----------------------------------------------------  // 

        // Inserting t to NonAlpha! 
        //  ----------------------------------------------------  // 
        // Beginning by finding the correct position t will be inserted into NonAlpha
        //  ------------------------  //
        int p = 0;
        for(int ii = NAi; ii >= 0; ii--){    // Loop goes from end of NonAlpha to beginning
            if(t->freq >= NonAlpha[ii].freq){  // If t's freq is >= NonAlpha's current position, the correct location has been found
                p = ii + 1;
                break;
            }
        }
        //  ------------------------  //

        //  Next space is made in NonAlpha for t and added to position p
        //  ------------------------  //
        for(int i = NAi; i > p; i--){
            NonAlpha[i] = NonAlpha[i - 1];    // Until p is reached, space is made for it
        }
        NonAlpha[p].freq = t->freq;
        NonAlpha[p].index = 0;     // Index and symbol = 0 because their values aren't being used
        NonAlpha[p].symbol = 0;
        NonAlpha[p].root = t;
        NAi++;   // NonAlpha's size grows after t is inserted
        //  ------------------------  //
    }






    
    struct symbol *Root = new symbol;  // Root is initialized and roots are connected
    Root->left = Alpha[0].root;
    Root->right = NonAlpha[0].root;
    Root->freq = Alpha[0].freq + NonAlpha[0].freq;

    Alpha[0].root->parent = Root;       // Parent paremeters are set
    NonAlpha[0].root->parent = Root;


    struct symbol *current = new symbol;    // Temporary current symbol to help keep track of place
    int totalCount = 0; // Int to count total number of char's
    
    for(int i=0; i<NSYMBOLS; i++){  // Loops through all Symbols array finding used symbols...
        if(Symbols[i].freq != 0){
            totalCount++;
            int count = 0;
            current = Symbols[i].parent;
            if(Symbols[i].parent->left->symbol == Symbols[i].symbol){   // Figures out if current position is either left or right
                current = current->left;
            }
            else{
                current = current->right;
            }

            // Symbol found, now go up the tree through it's parent
            while(current->parent != NULL) {
                if(current->parent->left == current){
                    // The symbol is to the left!
                    Symbols[i].encoding[count] = '0';
                    count++;
                }
                else if(current->parent->right == current){
                    // The symbol is to the right!
                    Symbols[i].encoding[count] = '1';
                    count++;
                }
                current = current->parent;
            } 
            
            count = count - 1;
            for(int ii = 0; ii < count; ii++){      // Reversing the encoding to properly output
                char temp = Symbols[i].encoding[ii];
                Symbols[i].encoding[ii] = Symbols[i].encoding[count];
                Symbols[i].encoding[count] = temp;
                count--;
            }
        }
    }
    cout << totalCount << "\n";
    for(int i=0; i<NSYMBOLS; i++){  //Loops through Symbols array and prints according to the output!
        if(Symbols[i].freq != 0){
            cout << i << "\t" << Symbols[i].symbol << "\t";
            int ii = 0;
            while(Symbols[i].encoding[ii] == '0' || Symbols[i].encoding[ii] == '1'){
                cout << Symbols[i].encoding[ii];
                ii++;
            }
            cout << "\n";
        }
    }
    

    return 0;
}
