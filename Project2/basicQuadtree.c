
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "TreeStructure.h"
#include "buildTree.h"
#include "writeTree.h"


double nodeValue(Node *node, double time) {

	int level = node->level;
	double x = node->xy[0];
	double y = node->xy[1];

	double h = pow(2.0, -level);

	return(value(x + 0.5*h, y + 0.5*h, time));
}

// Data function

double value(double x, double y, double time) {

	return(2.0*exp(-8.0*(x - time)*(x - time)) - 1.0);
}

int main( int argc, char **argv ) {

  Node *head;

  // make the head node
  head = makeNode( 0.0,0.0, 0 );
  growTree(head);
  growTree(head);
  growTree(head);
  adapt(head);

  
  // make a tree
  
  
  // print the tree for Gnuplot
  writeTree( head );
  destroyTree(head);
	

  return 0;
}

// make a node at given location (x,y) and level



// write out the tree to file 'quad.out'


