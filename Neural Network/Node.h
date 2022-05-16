#pragma once
#include <vector>

class Node
{
private:
	int value;
	int num_connections; //number of nodes in the next layer
	std::vector<float> weights;
public:
	Node(int);
	void update_value(int);
	int return_value();
	void update_weights(std::vector<float>);
	std::vector<float> return_weights();

};

