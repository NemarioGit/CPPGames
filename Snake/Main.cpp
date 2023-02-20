
#include <iostream>
#include <SDL.h>
#include <cmath>
#include "Main.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect render_grid[grid_area];
SDL_Event event;

int snake_length = 3; 
int snake_poses[grid_area]; //Positions of all snake segments

int food_pos;

bool is_running = true; //Is game currently running

/// <summary>
/// W = -GRID_WIDTH
/// S = GRID_WIDTH
/// A = -1
/// D = 1
/// </summary>
int direction = 1;

int head_position = grid_height / 2 * grid_width + grid_width / 2; //Position of the snake's head

int main(int argc, char* args[])
{   
	if (!init()) return -1;
		

    while (is_running)
    {
		handle_input();

        update_position();

		check_snake_collisions();

		//Clear and render snake & food
        render();


        SDL_Delay(132);
    }

    deinit();
    return 0;
}


bool init() {

	srand(static_cast<unsigned int>(time(nullptr)));

	//Filling array of cells to draw later
	for (int i = 0; i < grid_height; i++)
	{
		for (int j = 0; j < grid_width; j++)
		{
			render_grid[i * grid_width + j] = { cell_size * j, cell_size * i, cell_size, cell_size };
		}
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
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

	clear_window();

	snake_poses[0] = head_position;
	snake_poses[1] = head_position;
	snake_poses[2] = head_position;
	spawn_food();
	return true;
}

void deinit() {
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	std::cout << "Your length is " << snake_length << "!";
}

void clear_window() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void render() {

	clear_window();
	//Render snake
	for (int i = 0; i < snake_length; i++)
	{
		SDL_RenderFillRect(renderer, &render_grid[snake_poses[i]]);
	}

	//Render food
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &render_grid[food_pos]);

	SDL_RenderPresent(renderer);
}

void handle_input() {
	
	bool calledEvent = false;
	while (SDL_PollEvent(&event))
	{
		if (calledEvent) continue;

		switch (event.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				if (direction == grid_width || direction == -grid_width) break;
				direction = -grid_width;
				calledEvent = true;
				break;

			case SDL_SCANCODE_D:
				if (direction == -1 || direction == 1) break;
				direction = 1;
				calledEvent = true;
				break;

			case SDL_SCANCODE_S:
				if (direction == grid_width || direction == -grid_width) break;
				direction = grid_width;
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
			break;
		default:
			break;
		}
	}
}

void update_position() {
	for (int i = snake_length - 1; i > 0; i--)
	{
		snake_poses[i] = snake_poses[i - 1];
	}
	snake_poses[0] = head_position;
	head_position += direction;
}

void spawn_food() {
	do food_pos = rand() % grid_area; //Choose random position until it does not occupied by snake
	while (is_cell_snake(food_pos, true));
}

bool is_cell_snake(int check, bool food_check)
{
	for (int i = 0; i < snake_length; i++)
	{
		if (check == snake_poses[i])
		{
			return true;
		}
	}
	if (food_check) return check == head_position;
	return false;
}

void check_snake_collisions()
{
	if (head_position == food_pos)
	{
		increase_snake();
	}
	else if (is_cell_snake(head_position))
	{
		is_running = false;
	}
	else if ((head_position < 0) || //Checking top border
		(head_position > grid_area) || //Checking bottom border
		(abs(head_position % grid_width) - (head_position - direction) % grid_width) == grid_width - 1 || //Checking left border
		(head_position % grid_width == 0 && (head_position - direction) % grid_width == grid_width - 1)) //Checking right border
	{
		is_running = false;
	}
}

void increase_snake()
{
	snake_poses[snake_length] = snake_poses[snake_length - 1];
	snake_length++;
	spawn_food();
}