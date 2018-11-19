#include <iostream>
#include <queue>
#include <vector>
#include "solve.h"

using namespace std;

// A helper class implementing a vertex in
// an adjacency-list-based graph.
class Vertex
{
public:
    Vertex(int r, int c, int index)
    {
        row = r;
        col = c;
        visited = false;
        prior = NULL;
        s = index;
    }
    
    // Corresponding row and column location in maze
    int row;
    int col;
    int s;
    bool visited;
    Vertex* prior;
    
    // List of neighboring vertices
    vector<Vertex*> neighs;
};



class Graph{
public:
    //Constructs a graph
    void createGraph(string maze){
        width = maze_width(maze);
        height = maze_height(maze);
        
        //create Vertex for ' ' spaces
        int rows = 0, cols=0;
        
        for(int i=0; i < maze.size(); i++){
            if(maze[i] == ' '){
                Vertex *newVertex = new Vertex(rows,cols,i);
                if(i-width <= 0 || maze[i-1] == '\n' || maze[i+1] == '\n'|| i+width >= maze.size()){
                    if(start == NULL)start = newVertex;
                    else if(goal== NULL) goal = newVertex;
                }
                ListOfVertex.push_back(newVertex);
            }
            cols++;
            
            if(maze[i] == '\n')
            {
                rows++;
                cols = 0;
            }
        }
        
        addNeighbors();
    }

    //find up down left right neighbors and add each other if there is one
    void addNeighbors(){
        //adding the neighbors
        int r = 0;
        int c = 0;
        Vertex* neigbor;
        for(int i=0; i < ListOfVertex.size(); i++){
            r = ListOfVertex[i]->row;
            c = ListOfVertex[i]->col;
            
            //check up
            // r - 1 > 0 to check its not the top row
            if( r > 0){
                neigbor = FindNeighbor(r-1, c);
                if(neigbor != NULL && !inNeighs(ListOfVertex[i], neigbor)){
                    ListOfVertex[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(ListOfVertex[i]);
                }
            }
            //Check down
            if( r < height-1){
                neigbor = FindNeighbor(r+1, c);
                if(neigbor != NULL && !inNeighs(ListOfVertex[i], neigbor)){
                    ListOfVertex[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(ListOfVertex[i]);
                }
            }
            
            //Check left
            if( c > 0){
                neigbor = FindNeighbor(r, c-1);
                if(neigbor != NULL && !inNeighs(ListOfVertex[i], neigbor)){
                    ListOfVertex[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(ListOfVertex[i]);
                }
            }
            
            //Check right
            if( c < width-1){
                neigbor = FindNeighbor(r, c+1);
                if(neigbor != NULL && !inNeighs(ListOfVertex[i], neigbor)){
                    ListOfVertex[i]->neighs.push_back(neigbor);
                    neigbor->neighs.push_back(ListOfVertex[i]);
                }
            }
            
//            cout << "For " << ListOfVertex[i]->row << " " << ListOfVertex[i]->col << "'s neighbor is " << endl;
//            for(int j=0; j< ListOfVertex[i]->neighs.size(); j++){
//                cout << ListOfVertex[i]->neighs[j]->row << " " << ListOfVertex[i]->neighs[j]->col << endl;
//            }
//            cout << endl;
        }
    }
    
    //too see if it gets correct info about maze
    void display(){
        cout << "empty spaces are " << endl;
        for(int i=0; i < ListOfVertex.size(); i++){
            cout<< "    " << ListOfVertex[i]->row << " " << ListOfVertex[i]->col << endl;
        }
        cout << "Width is " << width << endl;
        cout << "Height is " << height << endl;
        cout << "starting point is " << start->row << " " << start->col << endl;
        cout << "ending point is " << goal->row << " " << goal->col << endl;
    }
    
    void BFS(){
        //clear the visited to false
        reset();
        
        queue<Vertex*> Q;
        
        start->visited = true;
        
        Q.push(start);
        
        while(!Q.empty()){
            Vertex* front = Q.front();
            Q.pop();
            
            for(int i=0; i < front->neighs.size(); i++){
                if(front->neighs[i]->visited == false){
                    front->neighs[i]->visited = true;
                    front->neighs[i]->prior = front;
                    Q.push(front->neighs[i]);
                }
            }
        }
    }
    
    //Modify the maze
    string shortestPath(string maze){
        maze[goal->s] = 'o';
        maze[start->s] = 'o';
        for(Vertex* tmp = goal->prior; tmp->prior !=NULL; tmp = tmp->prior){
            maze[tmp->s] = 'o';
        }
        
//        for(int i = 0; i < maze.length(); i++){
//            cout << maze[i];
//        }
        return maze;
    }
    
private:
    Vertex* start = NULL;
    Vertex* goal = NULL;
    int width = 0;
    int height = 0;
    vector<Vertex*> ListOfVertex;

    //get maze width
    int maze_width(string maze){
        for(int i=0;i < maze.size(); i++){
            if(maze[i]== '\n'){
                return i;
            }
        }
        return -1;
    }
    
    //get maze columns
    int maze_height(string maze){
        int h = 0;
        for(int i=0;i < maze.size(); i++){
            if(maze[i]== '\n'){
                h++;
            }
        }
        return h;
    }
    
    //Check that neighbor is not already added
    bool inNeighs(Vertex* current, Vertex* neighbor){
        for(int i=0; i< current->neighs.size(); i++){
            if(current->neighs[i] == neighbor)
                return true;
        }
        return false;
    }
    
    //See if there is any neighbor
    Vertex* FindNeighbor(int neiRow, int neiCol){
        for(int i=0; i< ListOfVertex.size(); i++){
            if(ListOfVertex[i]->row == neiRow && ListOfVertex[i]->col == neiCol){
                return ListOfVertex[i];
            }
        }
        return NULL;
    }
    
    //Mark all the verticies as not visited
    void reset(){
        for(int i=0; i < ListOfVertex.size(); i++){
            ListOfVertex[i]->visited = false;
        }
    }
};



string solve(string maze){
    Graph g;
    g.createGraph(maze);
//    g.display();
    g.BFS();
    return g.shortestPath(maze);
}
