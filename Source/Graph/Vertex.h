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
			position[i] = GraphStatics::GetRandomPosition(DEFAULT_MIN_RANGE, DEFAULT_MAX_RANGE);
		}
	}

	Vertex(const float minRange, const float maxRange)
	{
		for (unsigned int i = 0; i < position.size(); ++i)
		{
			position[i] = GraphStatics::GetRandomPosition(minRange, maxRange);
		}
	}

	std::string getPositionAsString() const;

private:
	std::array<float, Dimensions> position;
};

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

