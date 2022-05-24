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
	Layer third_layer(4, 10);
	Layer output_layer(10, 0);

	print_layer(first_layer);
	print_layer(second_layer);
	print_layer(third_layer);
	print_layer(output_layer);

	
	for (int i = 0; i < second_layer.return_size(); i++) {
		std::vector<float> current_weights(0, 0);

		for (int j = 0; j < first_layer.return_size(); j++) {
			current_weights.push_back(first_layer.access_node(j).return_weights().at(i));
		}
		second_layer.access_node(i).update_value()
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