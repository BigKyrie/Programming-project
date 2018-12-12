Node *makeNode(double x, double y, int level);
void makeChildren(Node *parent);
void growTree(Node *head);
void destroyTree(Node *head);
void removeChildren(Node *parent);
void auto_create1(Node *head);
void auto_create2(Node *head);
double nodeValue(Node *node, double time);
double value(double x, double y, double time);
void print_nodes(void);
void adapt(Node *head);

