#include "Util.hpp"

std::random_device   RandomNumberGenerator::m_rd;
std::mt19937         RandomNumberGenerator::m_rng(RandomNumberGenerator::m_rd());

//between start and end
//incluseive of start but not end
double RandomNumberGenerator::getRandomNumber(const double& rangeStart, const double& rangeEnd) {
	std::uniform_real_distribution<> randomizer(rangeStart, rangeEnd);
	return randomizer(m_rng);
}