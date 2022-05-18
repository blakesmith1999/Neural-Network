#include "Layer.h"
#include "Node.h"

Layer::Layer(int new_size, int num_connections) {
	set_size(new_size);
	for (int i = 0; i < size; i++) {
		Node new_node(num_connections);
		nodes.push_back(new_node);
	}
}

void Layer::set_size(int new_size) {
	size = new_size;
}

void Layer::set_nodes(std::vector<Node> new_nodes) {
	nodes = new_nodes;
}

int Layer::return_size() {
	return size;
}

std::vector<Node> Layer::return_nodes() {
	return nodes;
}

Node Layer::access_node(int node_num) {
	return nodes[node_num];
}