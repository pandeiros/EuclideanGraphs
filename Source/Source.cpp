#include "Graph/AverageGraph.h"
#include <iostream>

#define DIMS 2

int main()
{
	// Prepare files for data.
	Logger::SetOutput(LogOutput::TO_FILE);
	Logger::SetFilename("dane.txt");
	AverageGraph<DIMS>::logHeaders();

	const unsigned int testSets = 10;

	// Generate graphs.
	for (unsigned int n = 10; n <= 100; n+=10)
	{
		for (double xi = 0.0; xi < 0.5; xi += 0.05)
		{
			// For each pair of n and xi, create <testSets> graphs and calculate average values.
			std::vector<Graph<DIMS>> graphs;
			for (unsigned i = 0; i < testSets; ++i)
			{
				graphs.push_back(Graph<DIMS>(n, xi));
			}

			AverageGraph<DIMS> graph(graphs);
			graph.logProperties();
		}
	}

	Logger::CloseStream();
	std::cout << "Ready.";
	std::cin.get();

	return 0;
}