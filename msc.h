#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#define MAXFLOAT FLT_MAX

#include <random>
static double drand48()
{
	static std::random_device seed_gen;
	static std::mt19937 engine(seed_gen());
	static std::uniform_real_distribution<> dist(0.0, 1.0);
	return dist(engine);
}
