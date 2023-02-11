// Programming Problem Set 1
// Nadine Han & Amulya Garimella

/*
PROBLEM

Your goal in this Programming Assignment is to determine, in each of the three 
cases below, how the expected (average) weight of the minimum spanning tree
(not an edge, the whole MST) grows as a function of n.

We will be considering complete, undirected graphs. A graph with n vertices is
complete if all n-choose-2 pairs of vertices are edges in the graph.

Consider the following types of graphs:
• Complete graphs on n vertices, where the weight of each edge is a real number
chosen uniformly at random on [0, 1].

• Complete graphs on n vertices, where the vertices are points chosen uniformly
at random inside the unit square. (That is, the points are (x,y), with x and y
each a real number chosen uniformly at random from [0, 1].) The weight of an
edge is just the Euclidean distance between its endpoints.

• Complete graphs on n vertices, where the vertices are points chosen uniformly
at random inside the unit cube (3 dimensions) and hypercube (4 dimensions). As
with the unit square case above, the weight of an edge is just the Euclidean
distance between its endpoints.


This will require implementing an MST algorithm, as well as procedures that
generate the appropriate random graphs. You may implement any MST algorithm
(or algorithms!) you wish; however, we suggest you choose carefully.

For each type of graph, you must choose several values of n to test. For each
value of n, you must run your code on several randomly chosen instances of the
same size n, and compute the average value for your runs. Plot your values vs.
n, and interpret your results by giving a simple function f(n) that describes
your plot. 
For example, your answer might be f(n) = logn, f(n) = 1.5√n, or f(n) = 2n/logn. 
Try to make your answer as accurate as possible; this includes determining the
constant factors as well as you can. On the other hand, please try to make sure
your answer seems reasonable.
*/

/*
CODE SETUP

So that we may test your code ourselves as necessary, we prefer that your code
accepts the following command line form:
./randmst 0 numpoints numtrials dimension

Accepting that command line form is optional. If your code doesn’t and we need 
to test your code, we may need to contact you.

The flag 0 is meant to provide you some flexibility; you may use other values 
for your own testing, debugging, or extensions. 

The value numpoints is n, the number of points;

the value numtrials is the number of runs to be done;

the value dimension gives the dimension. (Use dimension 2 for the square, and
3 and 4 for cube and hypercube, respectively; use dimension 0 for the case where
weights are assigned randomly. Notice that dimension 1 is just not that
interesting, and that “dimension 0” is not actually the 0-dimensional version of
the 2-, 3-, and 4-dimensional cases.)

The output for the above command line should be the following:
average numpoints numtrials dimension

where average is the average minimum spanning tree weight over the trials.

It is convenient for us in grading to be able to run the programs without any
special per-student attention. The following three instructions make that easier
for us, but don’t spend more than a few minutes trying to satisfy them—we can
contact you to ask about seeing the code run on your machine if necessary.

• If possible, for compatibility reasons, the code should run on a Unix/Linux 
system, even if you code on another system.
• We expect the code as described above in its own file(s) separate from your
results/writeup.
• The code should compile with make; no instructions for humans. That is,
the command “make randmst” should produce an executable from your directory. You
may need to read up on makefiles to make this happen.

Note: you should test your program – design tests to make sure your program is 
working, for example by checking it on some small examples (or find other tests
of your choosing). You don’t need to put your tests in your writeup; 
that is for you.
*/