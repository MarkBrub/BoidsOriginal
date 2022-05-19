#include "display.hpp"

Renderer::Renderer(const int width, const int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
	}

}

void Renderer::frameStart() {
	SDL_PollEvent(&event);

	// Start frame timing
	totalFrames++;

	SDL_SetRenderDrawColor(renderer, 44, 57, 75, 255);
	SDL_RenderClear(renderer);
}

void Renderer::drawBoids(std::vector<Boid>& boids) {
	double scale = 1;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (auto& boid : boids) {
		SDL_Vertex vert[3];

		Vector2 top(0, 8);
		Vector2 left(-5, -8);
		Vector2 right(5, -8);
		Vector2 topP(0, 0);
		Vector2 leftP(0, 0);
		Vector2 rightP(0, 0);

		double scaleA = scale;

		//if (boid.id == 0) scaleA = 1.5;

		top /= (static_cast<double>(1) / scaleA);
		left /= (static_cast<double>(1) / scaleA);
		right /= (static_cast<double>(1) / scaleA);
		
		
		double angle = boid.velocity.angle();
		if (boid.velocity.y >= 0) {
			angle += std::numbers::pi;
		}


		topP.x = top.x * std::cos(angle) - top.y * std::sin(angle);
		topP.y = top.y * std::cos(angle) + top.x * std::sin(angle);
		leftP.x = left.x * std::cos(angle) - left.y * std::sin(angle);
		leftP.y = left.y * std::cos(angle) + left.x * std::sin(angle);
		rightP.x = right.x * std::cos(angle) - right.y * std::sin(angle);
		rightP.y = right.y * std::cos(angle) + right.x * std::sin(angle);
		


		// center
		vert[0].position.x = boid.position.x + topP.x;
		vert[0].position.y = boid.position.y - topP.y;

		// left
		vert[1].position.x = boid.position.x + leftP.x;
		vert[1].position.y = boid.position.y - leftP.y;

		// right 
		vert[2].position.x = boid.position.x + rightP.x;
		vert[2].position.y = boid.position.y - rightP.y;
		

		for (int x = 0; x < 3; x++) {
			vert[x].color.r = boid.color[0];
			vert[x].color.g = boid.color[1];
			vert[x].color.b = boid.color[2];
		}

		//Vector2 dir = boid.velocity / boid.velocity.length() / .05;

		SDL_RenderGeometry(renderer, NULL, vert, 3, NULL, 0);
		//SDL_RenderDrawLine(renderer, boid.position.x, boid.position.y, boid.position.x + dir.x, boid.position.y + dir.y);
	}
}

void Renderer::frameEnd(bool& running) {
	// Display window
	SDL_RenderPresent(renderer);

	if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT) {
		//Quit the program
		running = false;
	}
}

void Renderer::kill() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
}