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

bool init();
void deinit();
void render();
void handle_input();
void clear_window();
void update_position();
void spawn_food();
bool is_cell_snake(int check, bool food_check = false);
void check_snake_collisions();
void increase_snake();

#endif

