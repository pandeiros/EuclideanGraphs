#pragma once

#include "Graph.h"
template<unsigned int Dimensions>
class AverageGraph : public Graph<Dimensions>
{
public:
	AverageGraph(const std::vector<Graph<Dimensions>> graphs);

	static void logHeaders();
	void logProperties() const;

private:
	AverageProperties averageProperties;
};

template<unsigned int Dimensions>
void AverageGraph<Dimensions>::logHeaders()
{
	LOG_DELIMITED_DEFAULT("Dimensions");
	LOG_DELIMITED_DEFAULT("Vertices");
	LOG_DELIMITED_DEFAULT("Edge probability");
	LOG_DELIMITED_DEFAULT("Connectivity prob.");
	LOG_DELIMITED_DEFAULT("Edges");
	LOG_DELIMITED_DEFAULT("Expected value of edge count");
	LOG_DELIMITED_DEFAULT("Average degree");
	LOG_DELIMITED_DEFAULT("Expected value of degree");
	LOG_DELIMITED_DEFAULT("Density");
	LOG_DELIMITED_DEFAULT("Average density");
	LOG_DELIMITED_DEFAULT("Average path length");
	LOG_DELIMITED_DEFAULT("Grouping factor");

	LOG("");
}

template<unsigned int Dimensions>
AverageGraph<Dimensions>::AverageGraph(const std::vector<Graph<Dimensions>> graphs)
{
	assert(graphs.size() > 0);
	n = graphs[0].getVerticesCount();
	xi = graphs[0].getEdgeProbability();

	for (auto & graph : graphs)
	{
		assert(dimensions == graph.getDimensions() &&
			   n == graph.getVerticesCount() &&
			   xi == graph.getEdgeProbability());

		averageProperties.connectedProbability += double(graph.getExactProperties().isConnected ? 1 : 0) / graphs.size();
		averageProperties.edgeCount += double(graph.getExactProperties().edgeCount) / graphs.size();
		averageProperties.expectedValueOfEdgeCount += graph.getApproximateProperties().expectedValueOfEdgeCount / graphs.size();
		averageProperties.averageDegree += graph.getExactProperties().averageDegree / graphs.size();
		averageProperties.expectedValueOfDegree += graph.getApproximateProperties().expectedValueOfDegree / graphs.size();
		averageProperties.density += graph.getExactProperties().density / graphs.size();
		averageProperties.averageDensity += graph.getApproximateProperties().averageDensity / graphs.size();
		averageProperties.averagePathLength += graph.getExactProperties().averagePathLength / graphs.size();
		averageProperties.groupingFactor += graph.getExactProperties().groupingFactor / graphs.size();
	}
}


template<unsigned int Dimensions>
void AverageGraph<Dimensions>::logProperties() const
{
	LOG_DELIMITED_DEFAULT(dimensions);
	LOG_DELIMITED_DEFAULT(n);
	LOG_DELIMITED_DEFAULT(xi);
	LOG_DELIMITED_DEFAULT(averageProperties.connectedProbability);
	LOG_DELIMITED_DEFAULT(averageProperties.edgeCount);
	LOG_DELIMITED_DEFAULT(averageProperties.expectedValueOfEdgeCount);
	LOG_DELIMITED_DEFAULT(averageProperties.averageDegree);
	LOG_DELIMITED_DEFAULT(averageProperties.expectedValueOfDegree);
	LOG_DELIMITED_DEFAULT(averageProperties.density);
	LOG_DELIMITED_DEFAULT(averageProperties.averageDensity);
	LOG_DELIMITED_DEFAULT(averageProperties.averagePathLength);
	LOG_DELIMITED_DEFAULT(averageProperties.groupingFactor);

	LOG("");
}

