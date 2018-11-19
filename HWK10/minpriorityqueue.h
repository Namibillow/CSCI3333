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
    // For the mandatory running times below:
    //
    // n is the number of strings in the MinPriorityQueue.
    //
    // Assume the operations of map are O(1) time
    // (they are average case, but not worst-case).

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
//        cout << "SIze : " << H.size() << endl;
//        cout << "This size: " << numItems << endl;
        return numItems;
    }

    // Pushes a new element x with priority p
    // into the MinPriorityQueue.
    //
    // Must run in O(log(n)) time.
    void push(T x, int p)
    {
        H.push_back(make_pair(x, p));
        I.insert(make_pair(x, numItems));
        numItems++;
        while(true){
            auto n = I.find(x);
            int child_index = n->second;
            int parent_index = parent(child_index);
            //shifting up
            if(H[parent_index].second > H[child_index].second){
                swap(H[parent_index], H[child_index]);
                swap(I[H[parent_index].first], I[H[child_index].first]);
            }
            else{
                break;
            }
        }
    }

    // Returns the string at the front of the MinPriorityQueue.
    // Undefined behavior if the MinPriorityQueue is empty.
    //
    // Must run in O(1) time.
    T front()
    {
        return H[0].first;
    }

    // Removes the string at the front of the MinPriorityQueue.
    // Undefined behavior if the MinPriorityQueue is empty.
    //
    // Must run in O(log(n)) time.
    void pop()
    {
        if(size() == 0)
            return;
        T name = H[0].first;
        swap(H[0], H[H.size()-1]);
        swap(I[H[0].first], I[H[size()-1].first]); //swap the indexes
        H.pop_back();
        I.erase(name);
        name = H[0].first;
        numItems--;
        if(size() == 0)
            return;
        while(true){
            auto n = I.find(name);
            int lc= lchild(n->second); //left child
            int rc = rchild(n->second); //right child
            // no children
            if(lc > numItems-1){
                break;
            }
            // 1 children
            else if(rc == numItems){
                if(H[I[name]].second > H[lc].second){
                    swap(H[n->second], H[lc]);
                    swap(I[H[n->second].first], I[H[lc].first]);
                }
                else
                    break;
            }
            // 2 children exists
            else{
                if(H[I[name]].second > H[lc].second || H[I[name]].second > H[rc].second){
                    if(H[lc].second <= H[rc].second){
                        swap(H[n->second], H[lc]);
                        swap(I[H[n->second].first], I[H[lc].first]);
                    }
                    else{
                        swap(H[n->second], H[rc]);
                        swap(I[H[n->second].first], I[H[rc].first]);
                    }
                }
                else
                    break;
            }
        }
    }

    // If s is in the MinPriorityQueue
    // with current priority at least new_p,
    // then changes the priority of x to new_p.
    // Undefined behavior otherwise.
    //
    // Must run in O(log(n)) time.
    void decrease_key(T x, int new_p)
    {
        int i = I[x];
        H[i].second = new_p;
        while(true){
            auto n = I.find(x);
            int child_index = n->second;
            int p_index = parent(child_index);
            if(H[p_index].second > H[child_index].second){
                swap(H[p_index], H[child_index]);
                swap(I[H[p_index].first], I[H[child_index].first]);
            }
            else{
                break;
            }
        }
    }

private:
    // You don't need any other instance variables,
    // but you can add some if you want to.
    unordered_map<T, int> I; // Maps elements to indices in H.
    vector< pair<T, int> > H;     // The array containing the heap.
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

