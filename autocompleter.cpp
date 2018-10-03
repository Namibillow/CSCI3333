#include <iostream>
#include "autocompleter.h"
using namespace std;

// O(1)
Autocompleter::Autocompleter(){
    root = NULL;
}

void Autocompleter::insert(string x, int freq){
    Entry n;
    n.s = x;
    n.freq = freq;
    insert_recurse(n, root);
}

int Autocompleter::size(){
    return size_recurse(root);
}

void Autocompleter::completions(string x, vector<string> &T){
    
}

int Autocompleter::size_recurse(Node* root){
    if(root== NULL)
        return 0;
    else
        return 1+ size_recurse(root->left) + size_recurse(root->right);
}

void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &C){
    
}

void Autocompleter::insert_recurse(Entry e, Node*root){
    if (root == NULL){
        root = new Node(e);
        root->height+= 1;
    }
    else{
        if(root->e.s > e.s){
            insert_recurse(e, root->left);
        }
        else if(root->e.s < e.s){
            insert_recurse(e, root->right);
        }
        else{
            //do nothing its duplicate!
            //update frequency
            root->e.freq+=1;
        }
    }
}

void Autocompleter::rebalance(Node* root){
    
}

void Autocompleter::right_rotate(Node* root){
    
}

void Autocompleter::left_rotate(Node* root){
    
}
