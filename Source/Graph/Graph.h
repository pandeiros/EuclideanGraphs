﻿#pragma once

#include "Vertex.h"
#include <vector>
#include <cmath>
#include <queue>
#include <numeric>
#include <cassert>

template<unsigned int Dimensions>
class Graph
{
public:
	Graph()
	{

	};

	Graph(const unsigned int vertexCount, const double xi)
		: n(vertexCount), xi(xi)
	{
		assert(n > 1);

		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			vertices.push_back(Vertex<Dimensions>());
		}

		calculateExactProperties();
		calculateAppropximateProperties();
	};

	void printVertices() const;
	void printProperties() const;
	void logProperties() const;
	static void logHeaders();

	unsigned int getDimensions() const;
	unsigned int getVerticesCount() const;
	double getEdgeProbability() const;
	ApproximateProperties getApproximateProperties() const;
	ExactProperties getExactProperties() const;

protected:
	const unsigned int dimensions = Dimensions;
	unsigned int n = 0;
	double xi = 0.0;

private:
	void calculateExactProperties();
	void calculateAppropximateProperties();
	bool checkIfConnected();
	void visitNode(std::vector<unsigned int> & indexes, unsigned int index);
	std::vector<unsigned int> breadthFirstSearch(unsigned int rootIndex);

	std::vector<Vertex<Dimensions>> vertices;
	ApproximateProperties approximateProperties;
	ExactProperties exactProperties;
};

template<unsigned int Dimensions>
ExactProperties Graph<Dimensions>::getExactProperties() const
{
	return exactProperties;
}

template<unsigned int Dimensions>
ApproximateProperties Graph<Dimensions>::getApproximateProperties() const
{
	return approximateProperties;
}

template<unsigned int Dimensions>
double Graph<Dimensions>::getEdgeProbability() const
{
	return xi;
}

template<unsigned int Dimensions>
unsigned int Graph<Dimensions>::getVerticesCount() const
{
	return n;
}

template<unsigned int Dimensions>
unsigned int Graph<Dimensions>::getDimensions() const
{
	return dimensions;
}

template<unsigned int Dimensions>
void Graph<Dimensions>::logHeaders()
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

template<unsigned int Dimensions>
void Graph<Dimensions>::logProperties() const
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

template<unsigned int Dimensions>
std::vector<unsigned int> Graph<Dimensions>::breadthFirstSearch(unsigned int rootIndex)
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

template<unsigned int Dimensions>
void Graph<Dimensions>::visitNode(std::vector<unsigned int> & indexes, unsigned int index)
{
	indexes[index] = 1;
	for (unsigned int & i : vertices[index].getConnectedVerticesIndexes())
	{
		if (indexes[i] == 0)
			visitNode(indexes, i);
	}
}

template<unsigned int Dimensions>
bool Graph<Dimensions>::checkIfConnected()
{
	if (n == 0)
		return false;

	if (exactProperties.density == 1.0)
		return true;

	std::vector<unsigned int> indexes = std::vector<unsigned int>(vertices.size(), 0);
	for (unsigned int i = 0; i < indexes.size(); ++i)
	{
		if (indexes[i] == 0)
			visitNode(indexes, i);
	}

	for (auto index : indexes)
	{
		if (index == 0)
			return false;
	}

	return true;
}

template<unsigned int Dimensions>
void Graph<Dimensions>::printProperties() const
{
	exactProperties.printValues();
	std::cout << "================\n";
	approximateProperties.printValues();
}

template<unsigned int Dimensions>
void Graph<Dimensions>::calculateAppropximateProperties()
{
	double xi2 = std::pow(xi, 2.0);
	double pi_Xi2 = PI * xi2;

	approximateProperties.expectedValueOfDegree = (n - 1) * pi_Xi2;
	approximateProperties.expectedValueOfEdgeCount = pi_Xi2 * n * (n - 1) / 2.0;
	approximateProperties.averageDensity = pi_Xi2;

	approximateProperties.vertexProbability.clear();
	for (unsigned int k = 0; k <= n - 1; ++k)
	{
		double probability = std::exp(-1.0 * (n - 1) * pi_Xi2) * std::pow((n - 1) * pi_Xi2, double(k));
		GraphStatics::divideByFactorial(probability, k);
		approximateProperties.vertexProbability.push_back(probability);
	}
}

template<unsigned int Dimensions>
void Graph<Dimensions>::calculateExactProperties()
{
	double xi2 = std::pow(xi, 2.0);
	double pi_Xi2 = PI * xi2;

	bool isSurelyDisconnected = false;

	unsigned int degreeSum = 0;
	unsigned int distanceSum = 0;
	unsigned int vertexGroupingSum = 0;
	exactProperties.vertexProbability.clear();

	for (unsigned int i = 0; i < n; ++i)
	{
		Vertex<Dimensions> & v = vertices[i];
		for (unsigned int j = i + 1; j < n; ++j)
		{
			Vertex<Dimensions> & w = vertices[j];
			double distance = v.getDistanceTo(w);

			if (distance <= xi)
			{
				v.addConnectedVertex(j);
				w.addConnectedVertex(i);
				degreeSum += 2;
				exactProperties.edgeCount += 1;
			}
		}

		if (v.getDegree() == 0)
			isSurelyDisconnected = true;

		double probability = GraphStatics::binomialCoefficient(n - 1, i) *
			std::pow(pi_Xi2, double(i)) *
			std::pow(1.0 - pi_Xi2, double(n - 1 - i));
		exactProperties.vertexProbability.push_back(probability);

		auto indexes = v.getConnectedVerticesIndexes();

		for (unsigned int i1 = 0; i1 < indexes.size(); ++i1)
		{
			unsigned int index1 = indexes[i1];
			for (unsigned int i2 = i1 + 1; i2 < indexes.size(); ++i2)
			{
				unsigned int index2 = indexes[i2];
				auto & neighbours1 = vertices[index1].getConnectedVerticesIndexes();
				auto & neighbours2 = vertices[index2].getConnectedVerticesIndexes();

				if (std::find(neighbours1.begin(), neighbours1.end(), index2) != neighbours1.end() &&
					std::find(neighbours2.begin(), neighbours2.end(), index1) != neighbours2.end())
				{
					++vertexGroupingSum;
				}
			}
		}

		auto distances = breadthFirstSearch(i);
		for (unsigned int dist = i; dist < distances.size(); ++dist)
		{
			distanceSum += (distances[dist] != INF ? distances[dist] : 0);
		}

	}

	exactProperties.averageDegree = (double)degreeSum / n;
	exactProperties.density = 2.0 * exactProperties.edgeCount / (n * (n - 1));
	exactProperties.isConnected = isSurelyDisconnected ? false : checkIfConnected();
	exactProperties.averagePathLength = 2.0 * (double)distanceSum / (n * (n - 1));
	exactProperties.groupingFactor = (double)vertexGroupingSum / n;
}

template<unsigned int Dimensions>
void Graph<Dimensions>::printVertices() const
{
	for (auto & vertex : vertices)
	{
		LOG(vertex.getPositionAsString());
	}
}
