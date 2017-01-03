#include "Graph/AverageGraph.h"
#include <iostream>

int main()
{
	Logger::SetOutput(LogOutput::TO_FILE);
	Logger::SetFilename("dane.txt");

	AverageGraph<2>::logHeaders();

	// 2-dimensional graph with 50 vertices and 0.5 probability of
	// edge between any two vertices.
	Graph<2> G(50, 0.5);

	for (unsigned int n = 10; n <= 100; n+=10)
	{
		for (double ksi = 0.0; ksi < 0.5; ksi += 0.05)
		{
			AverageGraph<2> graph(
			{
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi),
				Graph<2>(n, ksi)
			});

			graph.logProperties();
		}
	}

	Logger::CloseStream();

	std::cout << "Ready.";
	std::cin.get();

	return 0;
}