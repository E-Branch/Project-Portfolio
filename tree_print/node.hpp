class node{
private:
	int data;
	node* left;
	node* right;
public:
	
	node();
	node(int i);
	~node();
	int getData();
	node* getLeft();
	node* getRight();
	void setChilds(node* nleft, node* nright);
};
