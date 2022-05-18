#include <iostream>
#include <fstream>
#include <vector>
#include "Layer.h"

void print_weights(std::vector<float>);
void print_layer(Layer);

int main() {
	int first_layer_size = 784, second_layer_size = 16, third_layer_size = 16, output_layer_size = 10;
	
	Layer first_layer(10, 4);
	Layer second_layer(4, 4);

	print_layer(first_layer);
	print_layer(second_layer);
}


void print_weights(std::vector<float> weights) {
	for (int i = 0; i < weights.size(); i++) {
		std::cout << "Weight of connection " << i << ": " << weights.at(i) << std::endl;

	}
}

void print_layer(Layer layer) {
	std::cout << "Layer" << std::endl;
	std::cout << "Nodes: " << layer.return_size() << "\n\n";
	for (int i = 0; i < layer.return_size(); i++) {
		std::cout << "Node " << i << ":" << std::endl;
		Node node = layer.access_node(i);
		std::cout << "Value: " << node.return_value() << std::endl;
		for (int j = 0; j < layer.access_node(i).return_connections(); j++) {
			std::cout << "Weight " << j << ": " << layer.access_node(i).return_weights().at(j) << std::endl;
		}
		std::cout << "\n";
	}
	std::cout << "\n\n\n";
}