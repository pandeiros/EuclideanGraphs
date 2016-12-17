#include "Graph/Graph.h"
#include <iostream>

int main()
{
	Graph<5> graph(30, 0.1f);
	graph.printVertices();

	std::cin.get();

	return 0;
}