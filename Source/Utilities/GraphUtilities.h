#pragma once

#define PI 3.14159265358979323846
#define DEFAULT_MIN_RANGE 0.0
#define DEFAULT_MAX_RANGE 1.0
#define INF 1000000

#include "Utilities/Utilities.h"
#include <random>

template<unsigned int Dimensions>
class Graph;

struct ApproximateProperties
{
	double expectedValueOfDegree;
	double expectedValueOfEdgeCount;
	double averageDensity;
	std::vector<double> vertexProbability;

	void printValues() const;
};

struct ExactProperties
{
	double averageDegree;
	unsigned int edgeCount;
	double density;
	double averagePathLength;
	double groupingFactor;
	std::vector<double> vertexProbability;
	bool isConnected;

	void printValues() const;
};

class GraphStatics
{
public:
	static double getRandomPosition(const double minRange, const double maxRange);

	static unsigned long long factorial(unsigned long long n);

	static unsigned int binomialCoefficient(unsigned int n, unsigned int k);

	static unsigned int min(unsigned int a, unsigned int b);

	static void divideByFactorial(double & value, unsigned int factor);

private:
	static std::mt19937 randomNumberGenerator;

	static std::uniform_real_distribution<double> distribution;
};