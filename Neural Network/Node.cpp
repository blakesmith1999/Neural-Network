#include "Node.h"
#include "Time.h"
#include <iostream>
Node::Node(int connections) {
	init_connections(connections);
	
	std::vector<float> zero_weight(num_connections, 0);

	for (int i(0); i < num_connections; i++) {
		srand((unsigned)time(NULL));
		zero_weight[i] = (float)rand() / RAND_MAX;
	}
	update_weights(zero_weight);
	update_value((float)rand() / RAND_MAX);
	update_delta((float)rand() / RAND_MAX);
	update_bias((float)rand() / RAND_MAX);
}

void Node::init_connections(int connections) {
	num_connections = connections;
}

int Node::return_connections() {
	return num_connections;
}

float Node::return_value() {
	return value;
}

std::vector<float> Node::return_weights() {
	return weights;
}

void Node::update_weights(std::vector<float>& new_weights) {
	weights = new_weights;
}

float Node::access_weight(int index) {
	return weights.at(index);
}

void Node::update_value(float new_value) {
	value = new_value;
}

float Node::return_delta() {
	return delta;
}

void Node::update_delta(float new_delta) {
	delta = new_delta;
}

float Node::return_bias() {
	return bias;
}

void Node::update_bias(float new_bias) {
	bias = new_bias;
}