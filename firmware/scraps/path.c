#include "globals.h" // number stack
#include "path.h"

void path_move() {
        // TODO clear curve queue

        current_point.y = number_stack[number_stack_len--];
        current_point.x = number_stack[number_stack_len--];

        start_point.x = current_point.x;
        start_point.y = current_point.y;
}

void path_rectangle() {
        long double height = number_stack_pop();
        long double width = number_stack_pop();
}

