#pragma once

#include "Utilities/GraphUtilities.h"
#include <array>
#include <sstream>

template<unsigned int Dimensions>
class Vertex
{
public:
	Vertex()
	{
		for (unsigned int i = 0; i < position.size(); ++i)
		{
			position[i] = GraphStatics::getRandomPosition(DEFAULT_MIN_RANGE, DEFAULT_MAX_RANGE);
		}
	}

	Vertex(const double minRange, const double maxRange)
	{
		for (unsigned int i = 0; i < position.size(); ++i)
		{
			position[i] = GraphStatics::getRandomPosition(minRange, maxRange);
		}
	}

	double getAxisValue(unsigned int index) const;
	std::string getPositionAsString() const;
	double getDistanceTo(Vertex<Dimensions> & other) const;
	void addConnectedVertex(unsigned int index);
	unsigned int getDegree() const;
	std::vector<unsigned int> getConnectedVerticesIndexes() const;

private:
	std::array<double, Dimensions> position;
	std::vector<unsigned int> connectedVerticesIndexes;
};

template<unsigned int Dimensions>
std::vector<unsigned int> Vertex<Dimensions>::getConnectedVerticesIndexes() const
{
	return connectedVerticesIndexes;
}

template<unsigned int Dimensions>
void Vertex<Dimensions>::addConnectedVertex(unsigned int index)
{
	connectedVerticesIndexes.push_back(index);
}

template<unsigned int Dimensions>
unsigned int Vertex<Dimensions>::getDegree() const
{
	return connectedVerticesIndexes.size();
}

template<unsigned int Dimensions>
double Vertex<Dimensions>::getAxisValue(unsigned int index) const
{
	if (index < Dimensions)
	{
		return position[index];
	}

	return 0.0;
}

template<unsigned int Dimensions>
double Vertex<Dimensions>::getDistanceTo(Vertex<Dimensions> & other) const
{
	double distance = 0.0;
	for (unsigned int i = 0; i < Dimensions; ++i)
	{
		distance += std::pow((other.getAxisValue(i) - position[i]), 2.0);
	}

	return std::sqrt(distance);
}

template<unsigned int Dimensions>
std::string Vertex<Dimensions>::getPositionAsString() const
{
	if (position.size() < 1)
	{
		LOG("Vertex position is empty!");
	}

	std::stringstream ss;
	ss << "(";

	for (unsigned int i = 0; i < position.size() - 1; ++i)
	{
		ss << position[i] << ", ";
	}

	ss << position[position.size() - 1] << ")";

	return ss.str();
}

