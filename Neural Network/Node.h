#pragma once
#include <vector>

class Node
{
private:
	float value;
	int num_connections; //number of nodes in the previous layer
	std::vector<float> weights;
	float delta;
	float bias;
public:
	Node(int);
	void init_connections(int);
	int return_connections();
	void update_value(float);
	float return_value();
	void update_weights(std::vector<float>&);
	float access_weight(int);
	std::vector<float> return_weights();
	float return_delta();
	void update_delta(float);
	float return_bias();
	void update_bias(float);
};

