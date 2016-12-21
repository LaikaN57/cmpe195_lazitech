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

void curve2lines() {
#define MIN_SEGMENTS (10)
#define MAX_SEGMENT_LENGTH (30)
#define BASIC_SEGMETNS_WEIGHT (0.6)

double basic_segments = max_length / MAX_SEGMENT_LENGTH
int segments = (int) ceil( sqrt( pow( basic_segments, 2 ) * BASIC_SEGMENTS_WEIGHT, pow( MIN_SEGMENTS, 2 ) ) );

for(int i = 0; i < segments - 1; i++) {
	float t = (float) i / (segments - 1);

	// calculate line and add segment
}
}
