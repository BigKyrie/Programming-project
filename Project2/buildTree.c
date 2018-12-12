#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "TreeStructure.h"
#include "buildTree.h"
#include "writeTree.h"
int count1 = 0;
int count2 = 0;
int count3 = 0;
Node *makeNode(double x, double y, int level) {

	int i;

	Node *node = (Node *)malloc(sizeof(Node));

	node->level = level;

	node->xy[0] = x;
	node->xy[1] = y;

	for (i = 0; i < 4; ++i)
		node->child[i] = NULL;

	return node;
}

// split a leaf nodes into 4 children

void makeChildren(Node *parent) {

	double x = parent->xy[0];
	double y = parent->xy[1];

	int level = parent->level;

	double hChild = pow(2.0, -(level + 1));

	parent->child[0] = makeNode(x, y, level + 1);
	parent->child[1] = makeNode(x + hChild, y, level + 1);
	parent->child[2] = makeNode(x + hChild, y + hChild, level + 1);
	parent->child[3] = makeNode(x, y + hChild, level + 1);

	return;
}


void growTree(Node *head)
{
	int i;
	if (head->child[0] == NULL)
	{
		makeChildren(head);
		return;
	}
	for (i = 0; i < 4; i++)
	{
		growTree(head->child[i]);

	}

}


void destroyTree(Node *head)
{
	int i;

	if (head->child[0] == NULL)
	{
		free(head);
		return;
	}

	for (i = 0; i < 4; i++)
	{
		destroyTree(head->child[i]);
	}
	free(head);

}

void removeChildren(Node *parent)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		free(parent->child[i]);
		parent->child[i] = NULL;
	}
}

void auto_create1(Node *head) {
	int i;
	if (head->child[0] == NULL)
	{
		if (nodeValue(head, 0.0) > 0.5)
		{
			head->flag = 1;
		}
		else if (nodeValue(head, 0.0) < -0.5)
		{
			head->flag = -1;
		}
		else
		{
			head->flag = 0;
		}
	}
	else
	{
		head->flag = 0;

		for (i = 0; i < 4; i++)
		{
			auto_create1(head->child[i]);			
		}
	}
}

void auto_create2(Node *head) {
	int i;
	if (head->child[0] == NULL)
	{
		if (head->flag == 1&&head->level<6)
		{
			count1++;
			makeChildren(head);
		}
	}
	else
	{
		if (head->child[0]->flag == -1 && head->child[1]->flag == -1 && head->child[2]->flag == -1 && head->child[3]->flag == -1)
		{
			removeChildren(head);
			count2++;
		}
		else
		{
			for (i = 0; i < 4; i++)
			{
				auto_create2(head->child[i]);
			}
		}
	}
}

void print_nodes(void)
{
	printf("%d nodes have been added\n", count1*4);
	printf("%d nodes have been moved\n", count2*4);
}

void adapt(Node *head)
{
	int last_add, last_move, add_change, move_change;
	last_add = 0;
	last_move = 0;
	while (1)
	{
		auto_create1(head);
		auto_create2(head);
		add_change = count1 - last_add;
		move_change = count2 - last_move;
		last_add = count1;
		last_move = count2;
		printf("%d nodes have been added at this stage\n", add_change);
		printf("%d nodes have been removed at this stage\n\n", move_change);
		if (add_change == 0 && move_change == 0)
		{
			printf("Here are no nodes change at this stage\n");
			break;
		}

	}

}