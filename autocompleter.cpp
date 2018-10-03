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
        
    }
    else{
        if(root->e.s > e.s){
            insert_recurse(e, root->left);
            
        }
        else if(root->e.s < e.s){
            insert_recurse(e, root->right);
            
        }
        else{
            return;
        }
    }
    rebalance(root);
}


int Autocompleter::sub_height(Node* root){
    if(root == NULL){
        return -1;
    }
    else{
        return root->height;
    }
}

void Autocompleter::update_height(Node* root){
    root->height =  1 + max(sub_height(root->left), sub_height(root->right));
}


void Autocompleter::rebalance(Node* root){
    while(root != NULL){
        update_height(root);
        // if the left is greater
        if (root->left->height >= 2 + root->right->height){
            if(root->left->left >= root->left->right){ //single right rotation
                right_rotate(root);
            }
            else{ // left-right rotation
                left_rotate(root);
                right_rotate(root);
            }
        }
        else if(root->right->height >= 2 + root->left->height){
            if(root->right->height >= 2 + root->left->height){
                if(root->right->right >= root->right->left){
                    left_rotate(root);
                }
                else{ //right-left rotation
                    right_rotate(root);
                    left_rotate(root);
                }
            }
        }
//       root = root->
    }
    
}

void Autocompleter::right_rotate(Node* root){
    
}

void Autocompleter::left_rotate(Node* root){
    
}


