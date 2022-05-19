#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>

#include "boid.hpp"
#include "vector2.hpp"

class Renderer {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;

	int totalFrames = 0;

public:
	Renderer(const int width, const int height);
	
	void frameStart();
	void drawBoids(std::vector<Boid>& boids);
	void frameEnd(bool& running);
	void kill();
};