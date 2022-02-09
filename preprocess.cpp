
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "defns.h"
#include <string>
#include <fstream>


using namespace std;

int main(){
    symbol Symbols[NSYMBOLS];                    // array of symbols;
    char str[30000];         			// array  of characters for string the input provided

    
    //initializing the members of the sturct sysmbol	
    for(int i = 0; i < NSYMBOLS; i++){
        Symbols[i].symbol = i;
        Symbols[i].freq = 0;
        Symbols[i].parent = NULL;
        Symbols[i].left = NULL;
        Symbols[i].right = NULL;
        Symbols[i].encoding[0] = ' ';
    }

    cin.getline(str, 30000, '\0');               // reding the input using the getline method 
    int size = 0;

    for(int i = 0; str[i] != '\0'; i++){   	//cunting the number of characters in the input array
	size++;
    }

    for(int i = 0; i < size; i++){   		//using the size obtained from the last step to increase the frequency of the characters
	Symbols[str[i]].freq++;
    }
    
   Symbols[10].freq++;
    
    //printing out all the characters with their frequencies
    for(int i = 0; i < NSYMBOLS; i++) {
         if(Symbols[i].freq != 0){                     		//checks  if the frquency at that particular index is  greater than 0
             cout  << i << "\t" << Symbols[i].freq << "\n";
         }
     }
	
    return 0;
}
