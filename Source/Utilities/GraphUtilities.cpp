#include "GraphUtilities.h"

std::mt19937 GraphStatics::randomNumberGenerator = std::mt19937(std::random_device()());
std::uniform_real_distribution<float> GraphStatics::distribution = std::uniform_real_distribution<float>(0.f, 1.f);

float GraphStatics::GetRandomPosition(const float minRange, const float maxRange)
{
	if (distribution.a() != minRange || distribution.b() != maxRange)
		distribution = std::uniform_real_distribution<float>(minRange, maxRange);

	return distribution(randomNumberGenerator);
}
