#ifndef MAIN_H
#define MAIN_H

#pragma region CONSTANTS
constexpr int screen_width = 640;
constexpr int screen_height = 480;
constexpr int cell_size = 16;
constexpr int grid_width = screen_width / cell_size;
constexpr int grid_height = screen_height / cell_size;
constexpr int grid_area = grid_height * grid_width;
#pragma endregion

//Initialize the game
bool init();
//Deinitialize the game
void deinit();
void render();
void handle_input();
void clear_window();
void update_position();
void spawn_food();

/**
 * \brief Checks if given position is occupied by snake
 * \param check Value to check
 * \param food_check Is this check called by food_spawn()?
 * \return True - if cell is occupied by snake, False - if not
 */
bool is_cell_snake(int check, bool food_check = false);
void check_snake_collisions();
void increase_snake();

#endif

