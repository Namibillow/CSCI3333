
#include <vector>

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

