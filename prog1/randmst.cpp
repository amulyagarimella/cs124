// Programming problem set 1
// Nadine Han + Amulya Garimella

// TODO: Generate random graph of dim 0, 2, 3, 4
/* 
We will be considering complete, undirected graphs. A graph with n vertices is
complete if all n-choose-2 pairs of vertices are edges in the graph
(can an adjanceny matrix work? rather than a linked list we have to look thru???)

DIM 0: Complete graphs on n vertices, where the weight of each edge is a real
number chosen uniformly at random on [0, 1].

DIM 1: I guess we ignore this lol... would this just be points on a numberline?

DIM 2: Complete graphs on n vertices, where the vertices are points chosen
uniformly at random inside the unit square. (That is, the points are (x,y),
with x and y each a real number chosen uniformly at random from [0, 1].)
The weight of an edge is just the Euclidean distance between its endpoints.

DIM 3, 4: Complete graphs on n vertices, where the vertices are points chosen 
uniformly at random inside the unit cube (3 dimensions) and hypercube (4 
dimensions). As with the unit square case above, the weight of an edge is just 
the Euclidean distance between its endpoints.
*/

// TODO: MST function
// heap???!?!?!?!?
// k(n) estimator

// TODO: return average MST edge weight