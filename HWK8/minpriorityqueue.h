
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
            numItems = 0;
		}
		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
            return numItems;
		}	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
            H.push_back(make_pair(x,p));
            
            I[x] = numItems; // key = string, value = index
            
            numItems++;
            
            int current = numItems -1;
            cursUp(current);
		}

        void cursUp(int current){
            while (H[current].second < H[parent(current)].second){
                swap(H[current], H[parent(current)]);
                swap(I[H[current].first], I[H[parent(current)].first]);
                current = parent(current);
                
            }
            
        }
    
		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
            if (empty() == true){
                return NULL;
            }
            else
                return H[0].first;
		}

        bool empty(){
            if (numItems == 0)
                return true;
            else
                return false;
        }
		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
            if(empty() == true){
                //if its already empty then do nothing
            }
            else{
                I.erase(H[0].first); //Erase from map first
                H[0] = H[numItems-1];
                numItems--;
                H.pop_back(); //decrease the size of the vector
                
                int current = 0;
                cursDown(current);
            }
		}

        void cursDown(int current){
            while(childProblem(current)){
                if(rchild(current) == numItems){
                    swap(H[current], H[lchild(current)]);
                    current = lchild(current);
                }
                else{
                    if (H[lchild(current)].second < H[rchild(current)].second){
                        swap(H[current], H[lchild(current)]);
                        swap(I[H[current].first], I[H[lchild(current)].first]);
                        current = lchild(current);
                    }
                    else{
                        swap(H[current], H[rchild(current)]);
                        swap(I[H[current].first], I[H[rchild(current)].first]);
                        current = rchild(current);
                    }
                }
            }
            I[H[current].first] = current;
        }
    
        bool childProblem(int i){
            if(lchild(i) >= numItems){
                // 0 child
                return false;
            }
            else if(rchild(i) == numItems){
                //  1 child
                if(H[lchild(i)].second < H[i].second)
                    return true;
                else
                    return false;
            }
            else{ //    2 children
                int smallerVal = min(H[lchild(i)].second, H[rchild(i)].second);
                if (smallerVal < H[i].second)
                    return true;
                else
                    return false;
            }
        }

		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
            if (I.find(x) == I.end()){
                //Not found, do nothing
            }
            
            else{
//                cout << x << " is found!!" << endl;
                int index = I[x];
//                cout << "index in vector is " << index << endl;
                int old_p = H[index].second;
//                cout << "old priority is " << old_p << endl;
                H[index].second = new_p;
//                cout << "new priority is " << H[index].second << endl;
                if (old_p < new_p){
                    cursDown(index);
                }
                else if(old_p > new_p){
                    cursUp(index);
                }
            }
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.
        int numItems;
    
        int parent(int i){
            return (i-1) /2;
        }
    
        int lchild(int i){
            return 2 * i + 1;
        }
    
        int rchild(int i){
            return lchild(i) + 1;
        }
};

#endif 

