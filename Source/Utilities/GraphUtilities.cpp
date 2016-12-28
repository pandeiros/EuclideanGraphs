#include "GraphUtilities.h"
#include "Graph/Graph.h"
#include <cassert>
#include <cmath>

std::mt19937 GraphStatics::randomNumberGenerator = std::mt19937(std::random_device()());
std::uniform_real_distribution<double> GraphStatics::distribution = std::uniform_real_distribution<double>(0.f, 1.f);

double GraphStatics::getRandomPosition(const double minRange, const double maxRange)
{
	if (distribution.a() != minRange || distribution.b() != maxRange)
		distribution = std::uniform_real_distribution<double>(minRange, maxRange);

	return distribution(randomNumberGenerator);
}

unsigned long long GraphStatics::factorial(unsigned long long n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

unsigned int GraphStatics::binomialCoefficient(unsigned int n, unsigned int k)
{
	assert(n >= k);

	std::vector<std::vector<unsigned int>> C = std::vector<std::vector<unsigned int>>(n + 1, std::vector<unsigned int>(k + 1, 0));

	//unsigned int C[n + 1][k + 1];
	unsigned int i, j;

	// Calculate value of Binomial Coefficient in bottom up manner
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= min(i, k); j++)
		{
			// Base Cases
			if (j == 0 || j == i)
				C[i][j] = 1;

			// Calculate value using previously stored values
			else
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}

	return C[n][k];
}

unsigned int GraphStatics::min(unsigned int a, unsigned int b)
{
	return a < b ? a : b;
}

void GraphStatics::divideByFactorial(double & value, unsigned int factor)
{
	for (unsigned int k = factor; k >= 2; --k)
	{
		value /= k;
	}
}

void ApproximateProperties::printValues() const
{
	LOG(expectedValueOfDegree);
	LOG(expectedValueOfEdgeCount);
	LOG(averageDensity);

	//for (auto & prob : vertexProbability)
	//{
	//	LOG(prob);
	//}
}

void ExactProperties::printValues() const
{
	LOG(isConnected);
	LOG(averageDegree);
	LOG(edgeCount);
	LOG(density);
	LOG(averagePathLength);
	LOG(groupingFactor);

	//for (auto & prob : vertexProbability)
	//{
	//	LOG_LINE(prob);
	//	LOG_LINE(" ");
	//}

	//LOG("");
}
