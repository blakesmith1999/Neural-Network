#pragma once
#include "Node.h"

class Layer
{
private:
	int size;
	std::vector<Node> nodes;
public:
	Layer(int,int);
	int return_size();
	std::vector<Node> return_nodes();
	void set_size(int);
	void set_nodes(std::vector<Node>);
	Node access_node(int);
};

