#pragma once

#include "Vertex.h"
#include <vector>

template<unsigned int Dimensions>
class Graph
{
public:
	Graph(const unsigned int vertexCount, const float xi)
	: vertexCount(vertexCount), xi(xi)
	{
		for (unsigned int i = 0; i < vertexCount; ++i)
		{
			vertices.push_back(Vertex<Dimensions>());
		}
	}

	void printVertices() const;

private:
	const unsigned int dimensions = Dimensions;
	unsigned int vertexCount = 0;
	float xi = 0.f;
	std::vector<Vertex<Dimensions>> vertices;
};

template<unsigned int Dimensions>
void Graph<Dimensions>::printVertices() const
{
	for (auto & vertex : vertices)
	{
		LOG(vertex.getPositionAsString());
	}
}

