#include "Node.h"
#include <iostream>
Node::Node(int connections) {
	init_connections(connections);

	std::vector<float> zero_weight (num_connections,0);
	update_weights(zero_weight);
	update_value(0);
}

void Node::init_connections(int connections) {
	num_connections = connections;
}

int Node::return_connections() {
	return num_connections;
}

int Node::return_value() {
	return value;
}

std::vector<float> Node::return_weights() {
	return weights;
}

void Node::update_weights(std::vector<float>& new_weights) {
	weights = new_weights;
}

void Node::update_value(int new_value) {
	value = new_value;
}

