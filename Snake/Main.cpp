
#include <iostream>
#include <SDL.h>
#include "Main.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect renderGrid[GRID_AREA];
SDL_Event event;

int snakeLength = 3;
int snakePoses[GRID_AREA]; 
bool isRunning = true;

/// <summary>
/// W = -GRID_WIDTH
/// S = GRID_WIDTH
/// A = -1
/// D = 1
/// </summary>
int direction = 1;

int headPosition = GRID_HEIGHT / 2 * GRID_WIDTH + GRID_WIDTH / 2; //Setting head to the center

int main(int argc, char* args[])
{   
	if (!init()) return -1;
		

    while (isRunning)
    {
		handleInput();

        updatePosition();

		//Clear and render snake & food
        render();

        SDL_Delay(150);
    }

    deinit();
    return 0;
}


//initialize game
bool init() {

	//Filling array of cells to draw later
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
		{
			renderGrid[i * GRID_WIDTH + j] = { CELL_SIZE * j, CELL_SIZE * i, CELL_SIZE, CELL_SIZE };
		}
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	clearWindow();

	snakePoses[0] = headPosition;
	snakePoses[1] = headPosition;
	snakePoses[2] = headPosition;
	return true;
}

void deinit() {
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

void clearWindow() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void render() {

	clearWindow();
	for (int i = 0; i < snakeLength; i++)
	{
		SDL_RenderFillRect(renderer, &renderGrid[snakePoses[i]]);
	}
	SDL_RenderPresent(renderer);
}

void handleInput() {
	
	bool calledEvent = false;
	while (SDL_PollEvent(&event))
	{
		if (calledEvent) continue;

		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				if (direction == GRID_WIDTH || direction == -GRID_WIDTH) break;
				direction = -GRID_WIDTH;
				calledEvent = true;
				break;

			case SDL_SCANCODE_D:
				if (direction == -1 || direction == 1) break;
				direction = 1;
				calledEvent = true;
				break;

			case SDL_SCANCODE_S:
				if (direction == GRID_WIDTH || direction == -GRID_WIDTH) break;
				direction = GRID_WIDTH;
				calledEvent = true;
				break;

			case SDL_SCANCODE_A:
				if (direction == -1 || direction == 1) break;
				direction = -1;
				calledEvent = true;
				break;

			default:
				break;
			}
		
		if (calledEvent) std::cout << direction << std::endl;
		default:
			break;
		}
	}
}

void updatePosition() {
	for (int i = snakeLength - 1; i > 0; i--)
	{
		snakePoses[i] = snakePoses[i - 1];
	}
	snakePoses[0] = headPosition;
	headPosition += direction;
	
}