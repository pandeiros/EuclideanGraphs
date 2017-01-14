#pragma once

#include "Graph.h"
template<unsigned int Dim>
class AverageGraph : public Graph<Dim>
{
public:
    /** Creates set of average values based on given collection of graphs. */
    AverageGraph(const std::vector<Graph<Dim>> graphs);

    /** Log readable names of the properties via the logger. */
    static void logHeaders();

    /** Log all the properties of this graph. */
    void logProperties() const;

private:
    /** Set of properties calculated as averages of properties of graphs specified in the constructor. */
    AverageProperties averageProperties;
};

template<unsigned int Dim>
AverageGraph<Dim>::AverageGraph(const std::vector<Graph<Dim>> graphs)
{
    assert(graphs.size() > 0);

    n = graphs[0].getVerticesCount();
    xi = graphs[0].getEdgeProbability();

    for (auto & graph : graphs)
    {
        // Check that every graph has the same parameters to achieve consistency.
        assert(n == graph.getVerticesCount() &&
            xi == graph.getEdgeProbability());

        // Calculate the properties.
        averageProperties.connectedProbability += double(graph.getExactProperties().isConnected ? 1 : 0) / graphs.size();
        averageProperties.edgeCount += double(graph.getExactProperties().edgeCount) / graphs.size();
        averageProperties.expectedValueOfEdgeCount += graph.getApproximateProperties().expectedValueOfEdgeCount / graphs.size();
        averageProperties.averageDegree += graph.getExactProperties().averageDegree / graphs.size();
        averageProperties.expectedValueOfDegree += graph.getApproximateProperties().expectedValueOfDegree / graphs.size();
        averageProperties.density += graph.getExactProperties().density / graphs.size();
        averageProperties.averageDensity += graph.getApproximateProperties().averageDensity / graphs.size();
        averageProperties.averagePathLength += graph.getExactProperties().averagePathLength / graphs.size();
        averageProperties.groupingFactor += graph.getExactProperties().groupingFactor / graphs.size();
        averageProperties.degreeVariance += graph.getExactProperties().degreeVariance / graphs.size();
        averageProperties.normalizedDegreeVariance += graph.getExactProperties().normalizedDegreeVariance / graphs.size();
        averageProperties.averageVertexProbability += graph.getExactProperties().averageVertexProbability / graphs.size();
        averageProperties.vertexProbabilityVariance += graph.getExactProperties().vertexProbabilityVariance / graphs.size();
    }
}


template<unsigned int Dim>
void AverageGraph<Dim>::logHeaders()
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
    LOG_DELIMITED_DEFAULT("Degree variance");
    LOG_DELIMITED_DEFAULT("Normalized degree variance");
    LOG_DELIMITED_DEFAULT("Average difference of vertex probability");
    LOG_DELIMITED_DEFAULT("Vertex probability difference variance");

    LOG("");
}


template<unsigned int Dim>
void AverageGraph<Dim>::logProperties() const
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
    LOG_DELIMITED_DEFAULT(averageProperties.degreeVariance);
    LOG_DELIMITED_DEFAULT(averageProperties.normalizedDegreeVariance);
    LOG_DELIMITED_DEFAULT(averageProperties.averageVertexProbability);
    LOG_DELIMITED_DEFAULT(averageProperties.vertexProbabilityVariance);

    LOG("");
}

