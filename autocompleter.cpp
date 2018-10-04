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
    //    cout << "Looking for " << x << endl;
    T.clear();
    vector<Entry> TE;
    completions_recurse(x, root, TE); // This part takes log(n)
    
    if(TE.empty()){
        return;
    }
    int max = 0;
    int max_i = 0;
    int top_three = 0;
    Entry temp;
    while(top_three < 3){ // constant O(1)
        max = 0;
        for(int j = top_three; j < TE.size(); j++){ // loop k times where k is number of matches words.
            if(TE[j].freq > max){
                max = TE[j].freq;
                max_i = j;
            }
        }
        //        cout << TE[max_i].s  << " : " <<TE[max_i].freq << endl;
        T.push_back(TE[max_i].s);
        
        temp = TE[top_three];
        TE[top_three] = TE[max_i];
        TE[max_i] = temp;
        
        ++top_three;
        
        if(top_three >= TE.size()){
            break;
        }
    }
}

int Autocompleter::size_recurse(Node* root){
    if(root== NULL)
        return 0;
    else
        return 1+ size_recurse(root->left) + size_recurse(root->right);
}

void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &T){
    if(root == NULL){ //If tree is empty
        return;
    }
    else if(root->e.s.find(x) == 0){
        T.push_back(root->e);
        completions_recurse(x, root->left, T);
        completions_recurse(x, root->right, T);
    }
    else if(root->e.s > x){
        completions_recurse(x, root->left, T);
    }
    
    else if(root->e.s < x){
        completions_recurse(x, root->right, T);
    }
    else{
        return;
    }
}

void Autocompleter::insert_recurse(Entry e, Node*&root){
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
        else{ //duplicate do nothing
            return;
        }
        update_height(root);
        rebalance(root);
    }
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

    // if the left is greater
    if (root->left->height >= 2 + root->right->height){
        if(root->left->left->height >= root->left->right->height){ //single right rotation
            right_rotate(root);
        }
        else{ // left-right rotation
            left_rotate(root->left);
            right_rotate(root);
        }
    }
    else if(root->right->height >= 2 + root->left->height){
        if(root->right->right->height >= root->right->left->height){
            left_rotate(root);
        }
        else{ //right-left rotation
            right_rotate(root->right);
            left_rotate(root);
        }
    }
}

void Autocompleter::right_rotate(Node* root){
    Node* p = root->left;
    root->left = p->right;
    p->right = root;
    
    //needs to update the height
    root = p;
    update_height(root);
    update_height(p);
}

void Autocompleter::left_rotate(Node* root){
    Node* p = root->right;
    root->right = p->left;
    p->left = root;
    //    root = p;
    update_height(root);
    update_height(p);
}


