#pragma once

#include "Utilities/GraphUtilities.h"
#include <array>
#include <sstream>

template<unsigned int Dim>
class Vertex
{
public:
	/** Default constructor, create positions for default range. */
	Vertex();

	/** Creates positions for specified range. */
	Vertex(const double minRange, const double maxRange);

	/** Add new connected vertex to this vertex (via its index) */
	void addConnectedVertex(unsigned int index);

	//////////////////////////////////////////////////////////////////////
	//// Getters
	//////////////////////////////////////////////////////////////////////

	/** Return position value for specified axis. */
	double getAxisValue(unsigned int axis) const;

	/** Return the euclidean distance between this and other vertex. */
	double getDistanceTo(Vertex<Dim> & other) const;

	/** Returns number of connected vertices with this vertex. */
	unsigned int getDegree() const;

	/** Return collection of indexes of vertices connected to this vertex. */
	std::vector<unsigned int> getConnectedVerticesIndexes() const;

private:
	/** Array of values describing vertex position in 'Dim' dimensions. */
	std::array<double, Dim> position;

	/** Indexes of connected vertices. */
	std::vector<unsigned int> connectedVerticesIndexes;
};

template<unsigned int Dim>
Vertex<Dim>::Vertex()
{
	for (unsigned int i = 0; i < position.size(); ++i)
	{
		position[i] = GraphStatics::getRandomPosition(DEFAULT_MIN_RANGE, DEFAULT_MAX_RANGE, i);
	}
}

template<unsigned int Dim>
Vertex<Dim>::Vertex(const double minRange, const double maxRange)
{
	for (unsigned int i = 0; i < position.size(); ++i)
	{
		position[i] = GraphStatics::getRandomPosition(minRange, maxRange, i);
	}
}

template<unsigned int Dim>
void Vertex<Dim>::addConnectedVertex(unsigned int index)
{
	connectedVerticesIndexes.push_back(index);
}

//////////////////////////////////////////////////////////////////////
//// Getters
//////////////////////////////////////////////////////////////////////

template<unsigned int Dim>
double Vertex<Dim>::getAxisValue(unsigned int axis) const
{
	if (axis < Dim)
	{
		return position[axis];
	}

	return 0.0;
}

template<unsigned int Dim>
double Vertex<Dim>::getDistanceTo(Vertex<Dim> & other) const
{
	double distance = 0.0;
	for (unsigned int i = 0; i < Dim; ++i)
	{
		distance += std::pow((other.getAxisValue(i) - position[i]), 2.0);
	}

	return std::sqrt(distance);
}

template<unsigned int Dim>
unsigned int Vertex<Dim>::getDegree() const
{
	return (unsigned)connectedVerticesIndexes.size();
}

template<unsigned int Dim>
std::vector<unsigned int> Vertex<Dim>::getConnectedVerticesIndexes() const
{
	return connectedVerticesIndexes;
}