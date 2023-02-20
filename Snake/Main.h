#ifndef MAIN_H
#define MAIN_H

#pragma region CONSTANTS
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int CELL_SIZE = 16;
const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;
const int GRID_AREA = GRID_HEIGHT * GRID_WIDTH;
#pragma endregion

bool init();
void deinit();
void render();
void handleInput();
void clearWindow();
void updatePosition();

#endif

