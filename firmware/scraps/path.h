#ifndef PATH_H
#define PATH_H

#include "point.h"

fpoint_t current_point;
fpoint_t start_point;

/**
Sets the start_point and current_point
RESET the start_point and current_point
*/
void path_move();

/**
Starts a new path and creates a rectangle
RESET the start_point and current_point
*/
void path_rectangle(); // move, line, line, line, close

/**
Creates a line from the current_point to the start_point.
*/
void path_close();

#endif
