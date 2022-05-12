#ifndef _8PUZZLE_H_
#define _8PUZZLE_H_

struct node
{
	//max of 4 children per node since puzzle only has 4 operations (left, right, up, down)
	node* child1;
	node* child2;
	node* child3;
	node* child4;
	node* parent;
	//vector< vector<char> > puzzle; //store vector of puzzles here
	int heuristic;
	int movementCost;
};



#endif
