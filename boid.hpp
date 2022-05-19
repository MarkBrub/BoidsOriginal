#pragma once

#include "util.hpp"
#include "vector2.hpp"

struct Boid {
	int id = 0;
	Vector2 position;
	Vector2 velocity;
	std::vector<uint8_t> color = { 0, 0, 0 };
	Boid() {
		position.x = RandomNumberGenerator::getRandomNumber(100, 1180);
		position.y = RandomNumberGenerator::getRandomNumber(100, 620);
		velocity.x = RandomNumberGenerator::getRandomNumber(-1, 3);
		velocity.y = RandomNumberGenerator::getRandomNumber(-1, 3);
	}

	auto operator<=>(const Boid&) const = default;

	auto operator==(const Boid& rhs) const {
		return id == rhs.id;
	}

	auto operator!=(const Boid& rhs) const {
		return !(*this == rhs);
	}
};