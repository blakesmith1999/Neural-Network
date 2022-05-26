#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "Layer.h"

void print_weights(std::vector<float>);
void print_layer(Layer,int);
void print_network(std::vector<Layer>);
void update_layer(Layer, Layer&);
float transfer_derivative(float);
void activate_input(std::vector<Layer>&, float);
void propagate(std::vector<Layer>&);
void backpropagate_layer(Layer&, Layer);
void backpropagate_layer(Layer&, float);
void backpropagate(std::vector<Layer>&, float);
void correct_weights(std::vector<Layer>&, float);

int main() {
	//int first_layer_size = 784, second_layer_size = 16, third_layer_size = 16, output_layer_size = 10;
	
	Layer first_layer(4, 0);
	Layer second_layer(2, 4);
	Layer third_layer(2, 2);
	Layer output_layer(1, 2);
	float l_rate = 0.1;

	std::vector<Layer> network;
	network.push_back(first_layer);
	network.push_back(second_layer);
	network.push_back(third_layer);
	network.push_back(output_layer);


	const int training_data[4][2] = { 1,0, 2, 1, 3, 0, 4, 1 };
	for (int i(0); i < 4; i++) {
		for (int j(0); j < 2; j++) {
			std::cout << training_data[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for (int index = 0; index < 100; index++) {
		for (int answer = 0; answer < 4; answer++) {
			activate_input(network, training_data[answer][0]);
			//std::cout << "Activate Input" << std::endl;
			//print_network(network);

			propagate(network);

			//print_network(network);

			backpropagate(network, training_data[answer][1]);

			//print_network(network);
		}

		correct_weights(network, l_rate);
		//print_network(network);
		//std::cout << "Corrected Weights" << std::endl;
	}
	
	activate_input(network, 2);
	propagate(network);
	print_network(network);

	activate_input(network, 3);
	propagate(network);
	print_network(network);
}

//backpropagation should sum up the errors, to be corrected by the correct weights part at the end.
void backpropagate_layer(Layer& output_layer, float expected_number) {
	int size = output_layer.return_size();
	std::vector<Node> nodes = output_layer.return_nodes();
	for (int i = 0; i < size; i++) {
		float actual_value = output_layer.access_node(i).return_value();
		float delta = nodes.at(i).return_delta();

		nodes.at(i).update_delta(delta + ((actual_value - expected_number) * transfer_derivative(actual_value)));
		/*
		if (i == (expected_number - 1)) {
			nodes.at(i).update_delta(delta + (actual_value - 1) * transfer_derivative(actual_value));
		}
		else {
			nodes.at(i).update_delta(delta + (actual_value - 0) * transfer_derivative(actual_value));
		}
		*/
	}
	output_layer.set_nodes(nodes);
}

//error for one neuron is the sum of the weighted deltas of the neurons in the next layer
void backpropagate_layer(Layer& current_layer, Layer next_layer) {
	//since weights are now associated with the inputs to a node, backpropagation should begin with the last layer
	std::vector<Node> nodes = current_layer.return_nodes();
	std::vector<Node> next_nodes = next_layer.return_nodes();
	int size = current_layer.return_size();
	float error = 0;
	float actual_value = 0;
	for (int i = 0; i < size; i++) {
		actual_value = nodes.at(i).return_value();
		for (int j = 0; j < next_layer.return_size(); j++) {
			error += (next_layer.access_node(j).access_weight(i) * next_layer.access_node(j).return_delta());
		}
		nodes.at(i).update_delta((nodes.at(i).return_delta()+ error * transfer_derivative(actual_value)));
	}
	current_layer.set_nodes(nodes);
}

void backpropagate(std::vector<Layer>& network, float expected_value) {
	backpropagate_layer(network[3], expected_value);
	for (int i = network.size() - 2; i >= 0; i--) {
		backpropagate_layer(network[i], network[i+1]);
	}
}

void propagate(std::vector<Layer>& network) {
	for (int i = 1; i <network.size(); i++) {
		update_layer(network[i-1], network[i]);
	}
}

void activate_input(std::vector<Layer>& network, float input) {
	std::vector<Node> nodes = network[0].return_nodes();
	int size = network[0].return_size();
	for (int i = 0; i < size; i++) {
		if (i == input - 1) {
			nodes.at(i).update_value(1);
		}
		else {
			nodes.at(i).update_value(0);
		}
	}
	network[0].set_nodes(nodes);
}

void print_layer(Layer layer, int index) {
	std::cout << "Layer " << index << std::endl;
	std::cout << "Nodes: " << layer.return_size() << "\n\n";
	for (int i = 0; i < layer.return_size(); i++) {
		std::cout << "Node " << i << ":" << std::endl;
		Node node = layer.access_node(i);
		std::cout << "Value: " << node.return_value() << std::endl;
		std::cout << "Delta: " << node.return_delta() << std::endl;
		std::cout << "Bias: " << node.return_bias() << std::endl;
		for (int j = 0; j < layer.access_node(i).return_connections(); j++) {
			std::cout << "Weight " << j << ": " << layer.access_node(i).return_weights().at(j) << std::endl;
		}
		std::cout << "\n";
	}
	std::cout << "\n\n\n";
}

void print_network(std::vector<Layer> network) {
	for (int i = 0; i < network.size(); i++) {
		print_layer(network[i], i);
	}
}

void update_layer(Layer previous_layer, Layer& current_layer) {
	std::vector<Node> nodes = current_layer.return_nodes();

	for (int i = 0; i < current_layer.return_size(); i++) {
		//Updating the values in the second layer
		float node_sum = 0;
		for (int j = 0; j < previous_layer.return_size(); j++) {
			node_sum += (previous_layer.access_node(j).return_value() * nodes.at(i).access_weight(j));
		}
		node_sum += nodes.at(i).return_bias();
		float mod_sum = 0;
		mod_sum = 1 / (1 + exp(-node_sum));
		//mod_sum = log(1 + exp(node_sum));
		nodes.at(i).update_value(mod_sum);
	}
	current_layer.set_nodes(nodes);
}

float transfer_derivative(float output) {
	return output * ((float) 1 - output);
}

//all weights connected to a single node are all updated the same. Why?
//weights are based on the error of the next node
void correct_weights(std::vector<Layer>& network, float l_rate) {
	for (int i = 1; i < network.size(); i++) {
		//iterates through the layers
		std::vector<Node> nodes = network[i].return_nodes();
		for (int j = 0; j < network[i].return_size(); j++) {
			//iterates through the nodes in a layer
			std::vector<float> weights = nodes.at(j).return_weights();
			for (int k = 0; k < nodes.at(j).return_connections(); k++) {
				//iterates through the weights in a node
				weights.at(k) -= l_rate * nodes.at(j).return_delta() * network[static_cast<std::vector<Layer, std::allocator<Layer>>::size_type>(i) - 1].access_node(k).return_value();
			}
			nodes.at(j).update_weights(weights);
			float bias = nodes.at(j).return_bias();
			bias -= l_rate * nodes.at(j).return_delta();
			nodes.at(j).update_bias(bias);
			nodes.at(j).update_delta(0);

		}
		network[i].set_nodes(nodes);
	}
}