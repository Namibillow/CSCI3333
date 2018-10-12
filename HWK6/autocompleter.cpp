//Nami Akazawa
//TRIE HWK Oct 11
#include <iostream>
#include "autocompleter.h"

using namespace std;

Autocompleter::Autocompleter(){
    root = new Node();
    count = 0;
}

//O(1)
void Autocompleter::insert(string x, int freq){
    int i = 0;
    Node* current = root;
    
    Entry n;
    n.s = x;
    n.freq = freq;
    
    while(i < x.length()){
        //Insert the word as top three and compare and do shifting
        top_three(current, n);
        
        if(current->children[x[i]] == NULL){
            //If the path didn't exist yet,
            current->children[x[i]] = new Node();
            
        }
        
        current = current->children[x[i]]; //points to next node
        i++; //move to next char
    }

    current->marked = true; //mark true
    count++; //Update Number of marked nodes
    
    top_three(current,n);
}

//O(1)
int Autocompleter::size(){
    return count;
}


//O(1)
void Autocompleter::completions(string x, vector<string> &T){
    T.clear();
    Node* curr = root;
    for(int i = 0; i< x.length(); i++){
        curr = curr->children[x[i]];
        
        if(curr == NULL){
            return;
        }
    }

    for(int j = 0; j < curr->top.size(); j++){
        T.push_back(curr->top[j].s);
        
        if(T.size() == 3){
            break;
        }
    }
}

//Helper function to sort top three runs O(1)
void Autocompleter::top_three(Node* current, Entry n){
    if(current->top.size()== 0){
        current->top.push_back(n);
    }
    else if(current->top.size()== 1){
        if(current->top[0].freq < n.freq){
            current->top.push_back(current->top[0]);
            current->top[0] = n;
        }
        else{
            current->top.push_back(n);
        }
    }
    else if(current->top.size()== 2){
        if(current->top[0].freq < n.freq){
            Entry temp = current->top[0];
            current->top.push_back(current->top[1]);
            current->top[0] = n;
            current->top[1] = temp;
        }
        else if(current->top[1].freq < n.freq){
            current->top.push_back(current->top[1]);
            current->top[1] = n;
        }
        else{
            current->top.push_back(n);
        }
    }
    else if(current->top.size()== 3){
        if(current->top[0].freq < n.freq){
            for(int i= 2; i > 0; i--){
                current->top[i] = current->top[i-1];
            }
            current->top[0] = n;
        }
        else if(current->top[1].freq < n.freq){
            for(int i= 2; i < 3; i++){
                current->top[i] = current->top[i-1];
            }
            current->top[1] = n;
        }
        else if(current->top[2].freq < n.freq){
            current->top[2] = n;
        }
    }
}
