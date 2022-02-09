#include <iostream>
#include "defns.h"
#include <string>
#include <fstream>

using namespace std;

#define EMPTY_STRING " "

void printCodes(symbol root, string str)
{
    // If root is Null then return.
    if (root.left == NULL || root.right == NULL){
        return;
    }
    // If the node's data is not 45 that means  it's a leaf node so it gets printed.
    if (root.symbol != 45)
    {
        cout << root.symbol << ": " << str << endl;
    }

    printCodes(*root.left, str + "0");   //recursive call to the left subtree
    printCodes(*root.right, str + "1");  //recursive call to the right subree.
}

// function to delete an item from the tree array
int deleteItem(tree array[], int size, int index)
{
    for (int i = index; i < size; i++)
    {
        array[i] = array[i + 1];
    }
    return size - 1;
}

// function to insert an item in sorted order
int insert(tree array[],symbol *parent, int size)
{
    int i = 0;
    while (i <= size)
    {
        if (array[i].freq < parent->freq || array[i].freq == parent->freq)
        {
            i++;
        }
        else
        {
            break;
        }
    }
    for (int j = size; j > i; j--)
    {
        array[j] = array[j - 1];
    }
    array[i].root = &(*parent);
    array[i].freq = parent->freq;
    array[i].symbol = '$';
    array[i].index = 45;

    return size + 1;
}

void encoding(tree *arr,int size){      		//The main encoding function still not complete 

symbol left;
symbol right;
symbol parent;
int loopCounter = size;
while (loopCounter > 0)
{
    left = *arr[0].root;
    right = *arr[1].root;
    left.freq = arr[0].freq;
    right.freq = arr[1].freq;
    left.parent = &(parent);
    parent.left = &(left);
    parent.right = &(right);
    parent.freq = left.freq + right.freq;
    cout << "parent Freq: " << parent.freq << endl;
    parent.symbol = 45;
    int newSize = deleteItem(arr,loopCounter, 0);
    int newSize2 = deleteItem(arr, newSize, 0);
    int sizeAfterInsertion = insert(arr, &parent, newSize2);
    loopCounter = sizeAfterInsertion;
    // for testing
    cout << "\nTesting:\n"
         << endl;
    for (int i = 0; i <= loopCounter; i++)
    {
        cout << arr[i].index << "\t" << arr[i].freq << endl;
    }
}

    // symbol *nleft;
    // symbol *nright;
    // symbol *nparent;
    // int nloopCounter = nsize;
    // while (nloopCounter != 1)
    // {
    //     nleft = &(*nonarr[0].root);
    //     nright = &(*nonarr[1].root);
    //     nleft->parent = nparent;
    //     right->parent = parent;
    //     nparent->left = nleft;
    //     nparent->right = nright;
    //     nparent->freq = nleft->freq + nright->freq;
    //     nparent->symbol = '$';
    //     int newSize = deleteItem(nonarr, nloopCounter, 0);
    //     int newSize2 = deleteItem(nonarr, newSize, 0);
    //     int sizeAfterInsertion = insert(nonarr, *nparent, newSize2);
    //     loopCounter = sizeAfterInsertion;
    //     // for testing
    //     for (int i = 0; i <= nloopCounter; i++)
    //     {
    //         cout << nonarr[i].index << "\t" << nonarr[i].freq << endl;
    //     }
    // }

    // symbol *root;
    // root-> left = parent;
    // root-> right = nparent;
    // root-> freq = parent->freq + nparent->freq;
    // root-> symbol = '$';
    // root-> parent = NULL;
//     cout << "end" << endl;
    printCodes(parent, EMPTY_STRING);
 }

//Insertion sort
void insertionSort(tree arr[], int n)  				
{
    tree key;
    int i;
    int j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        if (arr[j].freq == key.freq)                                // test included to check for the elements with same frequency and then sorth them accordingly
        {
            while (j >= 0 && arr[j].index > key.index)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        }
        else
        {
            while (j >= 0 && arr[j].freq > key.freq)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
        }
        arr[j + 1] = key;
    }
}

void merge(tree arr[], int l, int m, int h)  //Merge function of the merge sort
{
    int n1 = m - l + 1;
    int n2 = h - m;
    tree left[n1];
    tree right[n2];

    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[i + l];
    }
    for (int j = 0; j < n2; j++)
    {
        right[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (left[i].freq == right[j].freq)
        {
            if (left[i].index < right[j].index)
            {
                arr[k++] = left[i++];
            }
            else
            {
                arr[k++] = right[j++];
            }
        }
        else if (left[i].freq < right[j].freq)
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }

    while (i < n1)
    {
        arr[k++] = left[i++];
    }
    while (j < n2)
    {
        arr[k++] = right[j++];
    }
}


// mergesort
void mergeSort(tree arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(int argc, char *argv[])
{

    //declaring varibales to hold the command line input
    char fileName[20] = "";
    char method[10] = "";

    //validation check for the  command line input 
    if(artc == 3){
	if(argv[2] == "insertion" || argv[2] == "merge"){
		argv[1] = fileName;
		argv[2] = method;
	}
	else{
		cout << "Sorting method name incorrect" << endl;
	}
    }
    else{
	cout << "Usage: " << argv[0] << "[pre-file.txt] [insertion/merge]" << endl;
    }


    symbol Symbols[NSYMBOLS]; // array of symbols
    for (int i = 0; i < NSYMBOLS; i++)
    {
        Symbols[i].symbol = i;
        Symbols[i].freq = 0;
        Symbols[i].parent = NULL;
        Symbols[i].left = NULL;
        Symbols[i].right = NULL;
        Symbols[i].encoding[0] = ' ';
    }

    fstream infile(fileName, ios::in); // input file
    //Declaring variables
    int index;
    int frequency;
    tree Alpha[56];
    tree NonAlpha[128];
    int AlphaCount = -1;   //variable to count the number of alphabetic characters
    int NonAlphaCount = -1; //variable to count the number of non - alphabetic characters

    if (infile.is_open())
    {
        while (infile >> index >> frequency)
        {
            Symbols[index].freq = frequency;
            if (index >= 65 && index <= 90 || index >= 97 && index <= 122)     //checks the incoming  index  if it falls in the alphabet range it the initilaizer an element in the alpha array
            {
                AlphaCount = AlphaCount + 1;
                Alpha[AlphaCount].index = index;
                Alpha[AlphaCount].symbol = index;
                Alpha[AlphaCount].freq = Symbols[index].freq;
                Alpha[AlphaCount].root = &Symbols[index];
            }
            else							//in the else part the  indexes that are not in the alphabet range are taken care of
            {
                NonAlphaCount = NonAlphaCount + 1;
                NonAlpha[NonAlphaCount].index = index;
                NonAlpha[NonAlphaCount].symbol = index;
                NonAlpha[NonAlphaCount].freq = Symbols[index].freq;
                NonAlpha[NonAlphaCount].root = &Symbols[index];
            }
        }
    }
    else
    {
        cerr << "Unable to open file";
    }

    // cout << "AlphaCount: " << AlphaCount << endl;
    // cout << "NonAlphaCount: " << NonAlphaCount << endl;

    // if else branch to check for whihc sorting method to go with 
    if (method == "insertion")
    {
        insertionSort(Alpha, AlphaCount + 1);
        insertionSort(NonAlpha, NonAlphaCount + 1);
    }
    else if (method == "merge")
    {
        mergeSort(Alpha, 0, AlphaCount);
        mergeSort(NonAlpha, 0, NonAlphaCount);
    }
    else
    {
        cout << "Invalid input";
    }

//  for testing
//  cout << "after sorting" << endl;
//  for (int i = 0; i <= AlphaCount; i++)
//    {
//      cout << Alpha[i].index << "\t" << Alpha[i].freq << endl;
//    }

//  cout  << endl;
    encoding(Alpha,AlphaCount);  //calls the encoding function
    return 0;
}

