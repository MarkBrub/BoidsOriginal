#include <iostream>
#include <string>
#include <vector>

#include <SDL.h>

#include "display.hpp"
#include "vector2.hpp"
#include "util.hpp"
#include "boid.hpp"

Vector2 acceleration(double seperation, double alignment, double cohesion, const Boid& self, const std::vector<Boid>& boids);
void bound(Boid& boid);

int main(int argc, char** args) {
	const std::vector<std::vector<uint8_t>> colors = { {198, 46, 101}, {141, 169, 196}, {220, 133, 31}, {129, 244, 149} };
	std::vector<Boid> boids(450);

	for (int x = 0; x < boids.size(); x++) {
		boids[x].id = x;
		boids[x].color = colors[x % 4];
	}

	//boids[0].color = { 237, 255, 0 };

	const int WIDTH = 1280;
	const int HEIGHT = 720;
	double cohesion = 16;
	double alignment = 4;
	double seperation = 250;
	int maxSpeed = 5;
	Renderer renderer(WIDTH, HEIGHT);

	int xInput = 0;
	int yInput = 0;

	bool running = true;

	while (running) {
		renderer.frameStart();

		//Boids update
		renderer.drawBoids(boids);

		for (auto& boid : boids) {

			//SDL_GetMouseState(&xInput, &yInput);
			//cohesion = ((double)xInput / WIDTH * 60) + .01;
			//alignment = ((double)yInput / HEIGHT * 120) + .01;
			
			boid.velocity += acceleration(cohesion, seperation, seperation, boid, boids);
			if (boid.velocity.length() > maxSpeed) {
				boid.velocity = (boid.velocity / boid.velocity.length()) / (static_cast<double>(1) / maxSpeed);
			}

			boid.position += boid.velocity;
			bound(boid);
		}

		renderer.frameEnd(running);
	}

	renderer.kill();

	return 0;
}

Vector2 acceleration(double seperation, double alignment, double cohesion, const Boid& self, const std::vector<Boid>& boids) {
	Vector2 seperationVec;
	Vector2 alignmentVec;
	Vector2 cohesionVec;
	Vector2 trace;

	int closeBoids = 0;
	int reallyCloseBoids = 0;

	if (false && self.id % 4 == 1) {
		// Follow cursor
		int cursorX = 0;
		int cursorY = 0;
		SDL_GetMouseState(&cursorX, &cursorY);
		trace = (Vector2(cursorX, cursorY) - self.position) / 250;
	}

	for (auto& boid : boids) {
		// For all other boids in perception range
		if (boid != self && dist(boid.position, self.position) < 100) {
			if (dist(boid.position, self.position) < 20) {
				seperationVec -= boid.position - self.position;
				reallyCloseBoids++;
			}	

			if (self.id % 4 != boid.id % 4) continue;
			//if (self.id == 0) continue;

			alignmentVec += boid.velocity;
			cohesionVec += boid.position;
			closeBoids++;
		}
	}

	if (closeBoids > 0) {
		if (reallyCloseBoids > 0) seperationVec /= reallyCloseBoids * seperation;
		alignmentVec -= self.velocity;
		alignmentVec /= closeBoids * alignment;
		cohesionVec /= closeBoids;
	}
	cohesionVec -= self.position;
	cohesionVec /= cohesion;

	return seperationVec + alignmentVec + cohesionVec + trace;
}

void bound(Boid& boid) {
	int xmin = 0;
	int xmax = 1280;
	int ymin = 0;
	int ymax = 720;

	Vector2 vec;

	if (boid.position.x < xmin) {
		boid.position.x = xmax;
	}
	else if (boid.position.x > xmax) {
		boid.position.x = 0;
	}

	if (boid.position.y < ymin) {
		boid.position.y = ymax;
	}
	else if (boid.position.y > ymax) {
		boid.position.y = 0;
	}
}

