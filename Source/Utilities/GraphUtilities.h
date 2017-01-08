#pragma once

#define DEFAULT_DIMENSIONS 2
#define PI 3.14159265358979323846
#define DEFAULT_MIN_RANGE 0.0
#define DEFAULT_MAX_RANGE 1.0
#define INF 1000000

#include "Utilities/Utilities.h"
#include <random>

/**
 * Properties calculated approximately and may be very inaccurate in some marginal cases.
 */
struct ApproximateProperties
{
	double expectedValueOfDegree;
	double expectedValueOfEdgeCount;
	double averageDensity;
	std::vector<double> vertexProbability;
};

/**
 * Properties calculated with precise equations.
 */
struct ExactProperties
{
	double averageDegree;
	unsigned int edgeCount;
	double density;
	double averagePathLength;
	double groupingFactor;
	std::vector<double> vertexProbability;
	bool isConnected;
};

/**
 * Properties used in AverageGraph class to get the average of values of many test sets for the same
 * 'n' and 'xi' configuration.
 */
struct AverageProperties
{
	double connectedProbability = 0.0;
	double edgeCount = 0;
	double expectedValueOfEdgeCount = 0.0;
	double averageDegree = 0.0;
	double expectedValueOfDegree = 0.0;
	double density = 0.0;
	double averageDensity = 0.0;
	double averagePathLength = 0.0;
	double groupingFactor = 0.0;
};

/**
 * Collection of graph related math functions used in calculations.
 */
class GraphStatics
{
public:
	static double getRandomPosition(const double minRange, const double maxRange, const unsigned int dimension);
	static unsigned long long factorial(unsigned long long n);
	static unsigned int binomialCoefficient(unsigned int n, unsigned int k);
	static unsigned int min(unsigned int a, unsigned int b);
	static void divideByFactorial(double & value, unsigned int factor);

private:
	/** Variable used to uniformly distribute vertices positions. Each dimension is calculated separately.*/
	static std::vector<std::mt19937> randomNumberGenerators;
	static std::vector<std::uniform_real_distribution<double>> distributions;
};