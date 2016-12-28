#include "Graph/Graph.h"
#include <iostream>

int main()
{
	Logger::SetOutput(LogOutput::TO_FILE);
	Logger::SetFilename("dane.txt");

	Graph<2>::logHeaders();

	// 2-dimensional graph with 50 vertices and 0.5 probability of
	// edge between any two vertices.
	Graph<2> graph(50, 0.5);

	// Log properties to output set in Logger.
	graph.logProperties();

	Logger::CloseStream();

	std::cout << "Ready.";
	std::cin.get();

	return 0;
}