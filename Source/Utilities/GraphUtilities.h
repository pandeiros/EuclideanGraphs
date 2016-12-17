#pragma once

#define DEFAULT_MIN_RANGE 0.f
#define DEFAULT_MAX_RANGE 1.f

#include <random>
#include "Utilities/Utilities.h"

class GraphStatics
{
public:
	static float GetRandomPosition(const float minRange, const float maxRange);

private:
	static std::mt19937 randomNumberGenerator;

	static std::uniform_real_distribution<float> distribution;
};