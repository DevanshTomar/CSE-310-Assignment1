#include <iostream>
#include "defns.h"
#include <string>
#include <fstream>

using namespace std;

#define EMPTY_STRING ""  

void codes(symbol *root, string str)
{
    // If root is Null then we simply return.
    if (root == NULL)
    {
        return;
    }
    // If the node's data is not '-' that means it's not an internal node and we have encoundtered a leaf node, so save the string formed by the path to the leaf node in root->encoding.
    if (root->symbol != '-')
    {
        for (int i = 0; i < str.length(); i++)
        {
            root->encoding[i] = str[i];
        }
    }
    // Recursively calling the function for the left subtree and concating 0 to the string formed by the path to the leaf node.
    codes(root->left, str + "0");
    // Recursively calling the function for the right subtree and concating 1 to the string formed by the path to the leaf node.
    codes(root->right, str + "1");
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
int insert(tree array[], symbol *parent, int size)
{
    int i = 0;
    tree *newElement = new tree;
    newElement->root = parent;
    newElement->freq = parent->freq;
    newElement->symbol = '-';
    newElement->index = 45;
    newElement->root->parent = NULL;

    int freq = 0;
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
    size = size + 1;
    for (int j = size; j > i; j--)
    {
        array[j] = array[j - 1];
    }
    array[i] = *newElement;
    return size + 1;
}

// function to to decode the encoded string and retun the decoded string as a string.
string decode(symbol *root, string s)
{
    symbol *curr = root;              // temporary pointer to the root node
    string ans = "";                  // string to store the decoded string
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '1')
            curr = curr->right;
        else
            curr = curr->left;

        // If the current node is a leaf node then we have reached the end of the path and we have found the character.
        if (curr->left == NULL && curr->right == NULL)
        {
            ans += curr->symbol;
            curr = root;
        }
    }

    return ans + '\0';               // returning the decoded string with null character at the end
}

// function to create the tree bottom up
symbol *encode(tree *arr, int size)
{
    symbol *p;                  // p for the parent node
    symbol *left = new symbol;  // left for the left child node
    symbol *right = new symbol; // right for the right child node
    int loopCounter = size;     // loopCounter to keep the loop runing until the size is 0
    while (loopCounter > 0)
    {
        left = &(*arr[0].root);
        right = &(*arr[1].root);
        int newSize = deleteItem(arr, loopCounter, 0); // delete the first element from the array
        int newSize2 = deleteItem(arr, newSize, 0);    // delete the first element from the updated array
        p = new symbol;                                // creating  a new parent node and initializing it
        p->symbol = '-';
        p->left = &(*left);
        p->right = &(*right);
        p->freq = left->freq + right->freq;
        left->parent = &(*p);
        right->parent = &(*p);
        // insert the new parent node in the array
        int sizeAfterInsertion = insert(arr, p, newSize2);
        loopCounter = newSize; // updating the loop counter to the new size of the array array after insertion
    }
    return p;
}

// Insertion sort
void insertionSort(tree arr[], int n)
{
    tree key;
    int i;
    int j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        if (arr[j].freq == key.freq) // test included to check for the elements with same frequency and then sorth them accordingly
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

void merge(tree arr[], int l, int m, int h) // Merge function of the merge sort
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

/////////////////////////////////Main programe///////////////////////////////////////////////
int main(int argc, char *argv[])
{
    char fileName[20] = "";
    char method[10] = "";

    // validation check for the command line input
    if (argc == 3)
    {
        if (argv[2] == "insertion" || argv[2] == "merge")
        {
            argv[1] = fileName;
            argv[2] = method;
        }
    }
    else
    {
        cout << "Usage: " << argv[0] << "[pre-file.txt] [insertion/merge]" << endl;
    }

    symbol *Symbols = new symbol[NSYMBOLS]; // array of symbols
    for (int i = 0; i < NSYMBOLS; i++)
    {
        Symbols[i].symbol = i;
        Symbols[i].freq = 0;
        Symbols[i].parent = NULL;
        Symbols[i].left = NULL;
        Symbols[i].right = NULL;
        Symbols[i].encoding[0] = ' ';
    }

    // reading the input file that contains the output of the preprocessing step
    fstream infile(argv[1], ios::in); // input file

    int index;     // index of the symbol
    int frequency; // frequency of the symbol
    tree *Alpha = new tree[56];
    tree *NonAlpha = new tree[128];
    int AlphaCount = -1;    // variable to count the number of alphabetic characters
    int NonAlphaCount = -1; // variable to count the number of non - alphabetic characters

    if (infile.is_open())
    {
        while (infile >> index >> frequency)
        {
            Symbols[index].freq = frequency;
            if (index >= 65 && index <= 90 || index >= 97 && index <= 122) // checks the incoming  index  if it falls in the alphabet range it the initilaizer an element in the alpha array
            {
                // initializing the members of the alpha array for specific indexes
                AlphaCount = AlphaCount + 1;
                Alpha[AlphaCount].index = index;
                Alpha[AlphaCount].symbol = Symbols[index].symbol;
                Alpha[AlphaCount].freq = Symbols[index].freq;
                Alpha[AlphaCount].root = &Symbols[index];
            }
            else // in the else part the  indexes that are not in the alphabet range are taken care of
            {
                // initializing the members of the non alpha array for specific indexes
                NonAlphaCount = NonAlphaCount + 1;
                NonAlpha[NonAlphaCount].index = index;
                NonAlpha[NonAlphaCount].symbol = Symbols[index].symbol;
                NonAlpha[NonAlphaCount].freq = Symbols[index].freq;
                NonAlpha[NonAlphaCount].root = &Symbols[index];
            }
        }
    }
    else
    {
        cerr << "Unable to open file";
    }

////////Sorting both the alpha and non alpha array based on the argument provinded///////////

    if (method == "insertion")
    {
        insertionSort(Alpha, AlphaCount + 1);
        insertionSort(NonAlpha, NonAlphaCount + 1);
    }
    else
    {
        mergeSort(Alpha, 0, AlphaCount);
        mergeSort(NonAlpha, 0, NonAlphaCount);
    }
   

///////////////////////////Combining the left and the right tree formed/////////////////////

    symbol *left = encode(Alpha, AlphaCount); // encoding the alpha array
    symbol *right = encode(NonAlpha, NonAlphaCount); // encoding the non alpha array
    symbol *root = new symbol;
    root->left = &(*left);
    root->right = &(*right);
    root->freq = left->freq + right->freq;
    root->symbol = '-';
    root->parent = NULL;
    left->parent = &(*root);
    right->parent = &(*root);

    // calling the funtion to store the encoded values of each letter in root->encoding
    codes(root, EMPTY_STRING);

////////////////////////////output of the decoding///////////////////////////////////////////
    string line;
    getline(cin, line);
    string decoded = decode(root, line);   // calling the decode function to decode the input string and storing the result in the variable decoded
    cout << decoded << endl;              // printing the decoded string
}
