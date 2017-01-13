#pragma once

#include "Vertex.h"
#include <vector>
#include <cmath>
#include <queue>
#include <numeric>
#include <cassert>

template<unsigned int Dim>
class Graph
{
public:
    /** Default constructor. */
    Graph()
    {};

    /** Create graph with specified number of vertices and probability xi. */
    Graph(const unsigned int vertexCount, const double xi);

    //////////////////////////////////////////////////////////////////////
    //// Logging
    //////////////////////////////////////////////////////////////////////

    /** Log readable names of the properties to specified file. */
    static void logHeaders();

    /** Log all properties to specified file via Logger. */
    void logProperties() const;

    //////////////////////////////////////////////////////////////////////
    //// Getters
    //////////////////////////////////////////////////////////////////////

    /** Get number of vertices (n). */
    unsigned int getVerticesCount() const;

    /** Get the probability of edge between two vertices (xi). */
    double getEdgeProbability() const;

    /** Get the calculated approximate properties of the graph. */
    ApproximateProperties getApproximateProperties() const;

    /** Get the calculated exact properties of the graph. */
    ExactProperties getExactProperties() const;

protected:
    //////////////////////////////////////////////////////////////////////
    //// Parameters
    //////////////////////////////////////////////////////////////////////

    /** Number of dimensions in which vertices are defined. */
    const unsigned int dimensions = Dim;

    /** Number of vertices. */
    unsigned int n = 0;

    /** Probability of edge between every two vertices. */
    double xi = 0.0;

private:
    //////////////////////////////////////////////////////////////////////
    //// Helper methods.
    //////////////////////////////////////////////////////////////////////

    /** Performs the calculations for the set of exact parameters (i.e. density or average degree). */
    void calculateExactProperties();

    /** Performs the calculations for the set of approximate parameters (i.e. expected value of degree). */
    void calculateAppropximateProperties();

    /** Returns true if the graph is connected. */
    bool checkIfConnected();

    /** Helper function visiting a node (used with checkIfConnected function). */
    void visitNode(std::vector<unsigned int> & indexes, unsigned int index);

    /**  Breadth-first search function used to calculate path lengths from given vertex to every other vertex. */
    std::vector<unsigned int> breadthFirstSearch(unsigned int rootIndex);

    //////////////////////////////////////////////////////////////////////
    //// Properties
    //////////////////////////////////////////////////////////////////////

    /** Collection of vertices (matching template parameter of the graph). */
    std::vector<Vertex<Dim>> vertices;

    /** Set of approximate parameters of this graph calculated in constructor. */
    ApproximateProperties approximateProperties;

    /** Set of exact properties of this graph calculated in constructor. */
    ExactProperties exactProperties;
};

template<unsigned int Dim>
Graph<Dim>::Graph(const unsigned int vertexCount, const double xi)
    : n(vertexCount), xi(xi)
{
    assert(n > 1);

    // Generate random vertices.
    for (unsigned int i = 0; i < vertexCount; ++i)
    {
        vertices.push_back(Vertex<Dim>());
    }

    // Calculate properties.
    calculateAppropximateProperties();
    calculateExactProperties();
};

//////////////////////////////////////////////////////////////////////
//// Logging
//////////////////////////////////////////////////////////////////////

template<unsigned int Dim>
void Graph<Dim>::logHeaders()
{
    LOG_DELIMITED_DEFAULT("Dimensions");
    LOG_DELIMITED_DEFAULT("Vertices");
    LOG_DELIMITED_DEFAULT("Edge probability");
    LOG_DELIMITED_DEFAULT("Connected?");
    LOG_DELIMITED_DEFAULT("Average degree");
    LOG_DELIMITED_DEFAULT("Expected value of degree");
    LOG_DELIMITED_DEFAULT("Edges");
    LOG_DELIMITED_DEFAULT("Expected value of edge count");
    LOG_DELIMITED_DEFAULT("Density");
    LOG_DELIMITED_DEFAULT("Average density");
    LOG_DELIMITED_DEFAULT("Average path length");
    LOG_DELIMITED_DEFAULT("Grouping factor");

    LOG("");
}

template<unsigned int Dim>
void Graph<Dim>::logProperties() const
{
    LOG_DELIMITED_DEFAULT(dimensions);
    LOG_DELIMITED_DEFAULT(n);
    LOG_DELIMITED_DEFAULT(xi);
    LOG_DELIMITED_DEFAULT(exactProperties.isConnected ? "yes" : "no");
    LOG_DELIMITED_DEFAULT(exactProperties.averageDegree);
    LOG_DELIMITED_DEFAULT(approximateProperties.expectedValueOfDegree);
    LOG_DELIMITED_DEFAULT(exactProperties.edgeCount);
    LOG_DELIMITED_DEFAULT(approximateProperties.expectedValueOfEdgeCount);
    LOG_DELIMITED_DEFAULT(exactProperties.density);
    LOG_DELIMITED_DEFAULT(approximateProperties.averageDensity);
    LOG_DELIMITED_DEFAULT(exactProperties.averagePathLength);
    LOG_DELIMITED_DEFAULT(exactProperties.groupingFactor);
    LOG("");
}

//////////////////////////////////////////////////////////////////////
//// Getters
//////////////////////////////////////////////////////////////////////

template<unsigned int Dim>
unsigned int Graph<Dim>::getVerticesCount() const
{
    return n;
}

template<unsigned int Dim>
double Graph<Dim>::getEdgeProbability() const
{
    return xi;
}

template<unsigned int Dim>
ApproximateProperties Graph<Dim>::getApproximateProperties() const
{
    return approximateProperties;
}

template<unsigned int Dim>
ExactProperties Graph<Dim>::getExactProperties() const
{
    return exactProperties;
}

//////////////////////////////////////////////////////////////////////
//// Helper methods
//////////////////////////////////////////////////////////////////////

template<unsigned int Dim>
void Graph<Dim>::calculateExactProperties()
{
    // Common constants.
    double xi2 = std::pow(xi, 2.0);
    double pi_Xi2 = PI * xi2;

    // If we find vertex with degree 0, the graph is surely disconnected.
    bool isSurelyDisconnected = false;

    // Prepare properties.
    unsigned int degreeSum = 0;
    unsigned int distanceSum = 0;
    unsigned int vertexGroupingSum = 0;
    exactProperties.vertexProbability.clear();
    std::vector<double> vertexProbabilityDiff;

    // For each vertex...
    for (unsigned int i = 0; i < n; ++i)
    {
        Vertex<Dim> & v = vertices[i];

        // ...get all other vertices...
        for (unsigned int j = i + 1; j < n; ++j)
        {
            Vertex<Dim> & w = vertices[j];

            //...check the distance between them and update information about them.
            double distance = v.getDistanceTo(w);
            if (distance <= xi)
            {
                v.addConnectedVertex(j);
                w.addConnectedVertex(i);
                degreeSum += 2;
                exactProperties.edgeCount += 1;
            }
        }

        // Connected graphs have no 0-degree vertices.
        if (v.getDegree() == 0)
            isSurelyDisconnected = true;

        // We're checking the probability for every 0 <= k < n (which is the value of 'i' in this case).
        double probability = GraphStatics::binomialCoefficient(n - 1, i) *
            std::pow(pi_Xi2, double(i)) *
            std::pow(1.0 - pi_Xi2, double(n - 1 - i));
        exactProperties.vertexProbability.push_back(probability);

        // Get all of vertex 'v' neighbors. For every pair of neighbors (nested loops), check if they are connected.
        // If they are, increment the grouping sum.
        auto indexes = v.getConnectedVerticesIndexes();
        for (unsigned int i1 = 0; i1 < indexes.size(); ++i1)
        {
            unsigned int index1 = indexes[i1];
            for (unsigned int i2 = i1 + 1; i2 < indexes.size(); ++i2)
            {
                unsigned int index2 = indexes[i2];

                // Neighbor i1 and i2 are connected, if the distance between them is equal or less than xi.
                if (vertices[index1].getDistanceTo(vertices[index2]) <= xi)
                {
                    ++vertexGroupingSum;
                }
            }
        }

        // Check paths from vertex v to every other vertex (but not the same pair of vertices more than once).
        auto distances = breadthFirstSearch(i);
        for (unsigned int dist = i; dist < distances.size(); ++dist)
        {
            distanceSum += (distances[dist] != INF ? distances[dist] : 0);
        }

        // Add difference between approximate and exact probability.
        double probabilityDiff = probability - approximateProperties.vertexProbability[i];
        vertexProbabilityDiff.push_back(probabilityDiff);
        exactProperties.averageVertexProbability += probabilityDiff;
    }

    // Save the properties from the calculated parameters.
    exactProperties.averageDegree = (double)degreeSum / n;
    exactProperties.density = 2.0 * exactProperties.edgeCount / (n * (n - 1));
    exactProperties.isConnected = isSurelyDisconnected ? false : checkIfConnected();
    exactProperties.averagePathLength = 2.0 * (double)distanceSum / (n * (n - 1));
    exactProperties.groupingFactor = (double)vertexGroupingSum / n;
    exactProperties.degreeVariance = pi_Xi2 * (1.0 - xi2) * (n - 1.0);

    // Calculate normalized degree value and variance of differences between exact and approximate vertex probabilities.
    exactProperties.averageVertexProbability /= n;
    for (unsigned int i = 0; i < n; ++i)
    {
        exactProperties.normalizedDegreeVariance += std::pow(vertices[i].getDegree() / (n - 1.0) - exactProperties.averageDegree / (n - 1.0), 2.0);
        exactProperties.vertexProbabilityVariance += std::pow(vertexProbabilityDiff[i] - exactProperties.averageVertexProbability, 2.0);
    }
    exactProperties.normalizedDegreeVariance /= n;
    exactProperties.vertexProbabilityVariance /= n;
}

template<unsigned int Dim>
void Graph<Dim>::calculateAppropximateProperties()
{
    // Common constants.
    double xi2 = std::pow(xi, 2.0);
    double pi_Xi2 = PI * xi2;

    // Properties calculated right away.
    approximateProperties.expectedValueOfDegree = (n - 1) * pi_Xi2;
    approximateProperties.expectedValueOfEdgeCount = pi_Xi2 * n * (n - 1) / 2.0;
    approximateProperties.averageDensity = pi_Xi2;

    // Vertex probabilities for every k (0 <= k <= n-1).
    approximateProperties.vertexProbability.clear();
    for (unsigned int k = 0; k <= n - 1; ++k)
    {
        double probability = std::exp(-1.0 * (n - 1) * pi_Xi2) * std::pow((n - 1) * pi_Xi2, double(k));
        GraphStatics::divideByFactorial(probability, k);
        approximateProperties.vertexProbability.push_back(probability);
    }
}

template<unsigned int Dim>
bool Graph<Dim>::checkIfConnected()
{
    // No vertices, graph is disconnected.
    if (n == 0)
        return false;

    // Max probable density - surely connected.
    if (exactProperties.density == 1.0)
        return true;

    // Visit every vertex and set its value in the vector to 1...
    std::vector<unsigned int> indexes = std::vector<unsigned int>(vertices.size(), 0);
    for (unsigned int i = 0; i < indexes.size(); ++i)
    {
        if (indexes[i] == 0)
            visitNode(indexes, i);
    }

    // ...if at least one vertex has value 0 (has not been visited), the graph is disconnected.
    for (auto index : indexes)
    {
        if (index == 0)
            return false;
    }

    return true;
}

template<unsigned int Dim>
void Graph<Dim>::visitNode(std::vector<unsigned int> & indexes, unsigned int index)
{
    indexes[index] = 1;
    for (unsigned int & i : vertices[index].getConnectedVerticesIndexes())
    {
        if (indexes[i] == 0)
            visitNode(indexes, i);
    }
}

template<unsigned int Dim>
std::vector<unsigned int> Graph<Dim>::breadthFirstSearch(unsigned int rootIndex)
{
    std::vector<unsigned int> distances = std::vector<unsigned int>(vertices.size(), INF);
    std::queue<unsigned int> indexQueue;

    distances[rootIndex] = 0;
    indexQueue.push(rootIndex);

    while (!indexQueue.empty())
    {
        unsigned int current = indexQueue.front();
        indexQueue.pop();
        for (auto & adjacent : vertices[current].getConnectedVerticesIndexes())
        {
            if (distances[adjacent] == INF)
            {
                distances[adjacent] = distances[current] + 1;
                indexQueue.push(adjacent);
            }
        }
    }

    return distances;
}
