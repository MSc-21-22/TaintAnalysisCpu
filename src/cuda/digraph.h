#pragma once
#include "cuda_data.h"
#include <iostream>
#include <stdint.h>

namespace cuda {

template<typename Node>
void print_link(Node& from, Node& to) {
	std::cout << ((uintptr_t)&from) << "->" << ((uintptr_t)&to) << '\n';
}

template<typename Node>
void print_digraph(DynamicArray<Node> nodes) {
	for (int i = 0; i < nodes.size(); ++i) {
		Node& node = nodes[i];

		for (int succ_index = 0; succ_index < 5 && node.successor_index[succ_index] != -1; ++succ_index) {
			int index = node.successor_index[succ_index];
			print_link(node, nodes[index]);
		}

		std::cout << (uintptr_t)&node << "[label = \"Index: " << i << "\\n" << node.data << "\"]\n";
	}
}

}
