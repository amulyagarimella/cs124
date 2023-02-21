#include <iostream>
#include <cmath>
#include <stdlib.h> 
#include <vector>

namespace std {
    class item {
        // should pt to the vertex not store it b/c unnecessary space probs
        public:

            int vertex;
            int dist;
            int parentVertex;

            int compare (item item2);
            void print();
    };

    class PriorityQueue {
        // initialize this for push function
        public: 
            item value;
            vector<item> heap;
            // TODO maybe make long
            vector<int> positions;

            // debugging purpose
            void print_heap();

            void push(int v, int d);

            item top();

            item pop();

            bool empty() const;

        private:
            void bubble_up(int i);

            void bubble_down(int i);
    };

    struct MST {
        vector <vector<int> > adjList;
    };

    MST MST_prim (vector<vector<float> > G, int s);
}