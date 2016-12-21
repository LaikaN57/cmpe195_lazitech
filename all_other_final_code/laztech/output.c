#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// utils
typedef struct {
	int32_t x;
	int32_t y;
} point_t;

// hardware abstraction
point_t current_point;
point_t current_dir;

int steps;

// hardware control
void step_x() {
	current_point.x += current_dir.x;
	
	// TODO Step

	steps++;
	printf("%d (X): (%d, %d)\n", steps, current_point.x, current_point.y);
}

void step_y() {
	current_point.y += current_dir.y;
	
	// TODO Step
	
	steps++;
	printf("%d (Y): (%d, %d)\n", steps, current_point.x, current_point.y);
}

void step_xy() {
	current_point.x += current_dir.x;
	current_point.y += current_dir.y;
	
	// TODO Step

	steps++;
	printf("%d (XY): (%d, %d)\n", steps, current_point.x, current_point.y);
}

void dir_x(int dir) {
	current_dir.x = dir < 0 ? -1 : 1;
	
	// TODO Dir
}

void dir_y(int dir) {
	current_dir.y = dir < 0 ? -1 : 1;
	
	// TODO Dir
}

void dir_xy(int x_dir, int y_dir) {
	current_dir.x = x_dir < 0 ? -1 : 1;
	current_dir.y = y_dir < 0 ? -1 : 1;
	
	// TODO Dir
}

/*
This function will either step the x or y motor per step. It traces a line by
choosing the major axis to always step and only steps the minor axis when
needed.

This function overshoots.
*/
/*
int trace_line(point_t end_point) {
	int x_diff;
	int y_diff;
	
	x_diff = end_point.x - current_point.x;
	y_diff = end_point.y - current_point.y;
	
	dir_x(x_diff);
	dir_y(y_diff);
	
	x_diff = abs(end_point.x - current_point.x);
	y_diff = abs(end_point.y - current_point.y);
	
	printf("%d %d\n", x_diff/y_diff, y_diff/x_diff);

	// determine if we are going to increment along x or y
	// TODO Speed enhancements here (loop unpacking)
	if(x_diff >= y_diff) {
		// inc along x
		for(int i = 0; i < x_diff; i++) {
			step_x();
			
			if(y_diff && i % (x_diff/y_diff) == 0) {
				step_y();
			}
		}
	} else {
		// inc along y
		for(int i = 0; i < y_diff; i++) {
			step_y();
			
			if(x_diff && i % (y_diff/x_diff) == 0) {
				step_x();
			}
		}
	}
}
*/

/*
Alternate version of above that will step diaginally if needed.
*/
/*
int trace_line_alt(point_t end_point) {
	int x_diff;
	int y_diff;
	
	x_diff = end_point.x - current_point.x;
	y_diff = end_point.y - current_point.y;
	
	dir_x(x_diff);
	dir_y(y_diff);
	
	x_diff = abs(end_point.x - current_point.x);
	y_diff = abs(end_point.y - current_point.y);
	
	printf("%d %d\n", x_diff/y_diff, y_diff/x_diff);

	// determine if we are going to increment along x or y
	// TODO Speed enhancements here (loop unpacking)
	if(x_diff >= y_diff) {
		// inc along x
		for(int i = 0; i < x_diff; i++) {
			if(y_diff && i % (x_diff/y_diff) == 0) {
				step_xy();
			} else {
				step_x();
			}
		}
	} else {
		// inc along y
		for(int i = 0; i < y_diff; i++) {
			if(x_diff && i % (y_diff/x_diff) == 0) {
				step_xy();
			} else {
				step_y();
			}
		}
	}
}
*/

/*
This function will step either the x or y motor or both per step. It calculates
if the best motion is in the x, y, or diag direction by compairing the
x and y differences to the target. If the angle exceeds 22.5 degrees within an
axis, it will step towards that axis. Otherwise it will step both axises.

This function may not be safe on end goals.

This function is not very good (consider these two versions):
(basically it will do a 45 degree line then curve over.)
*/
/*
int trace_line_diag(point_t end_point) {
	int x_diff;
	int y_diff;
	
	x_diff = end_point.x - current_point.x;
	y_diff = end_point.y - current_point.y;
	
	dir_x(x_diff);
	dir_y(y_diff);

	while(current_point.x != end_point.x
			|| current_point.y != end_point.y) {
		// calc diffs
		x_diff = abs(end_point.x - current_point.x);
		y_diff = abs(end_point.y - current_point.y);

		if(x_diff * 0.4142 > y_diff) {
			// x major
			step_x();
		} else if(y_diff * 0.4142 > x_diff) {
			// y major
			step_y();
		} else {
			// diag major
			step_xy();
		}
		
		if(steps > 100) {
			printf("Ran too long!\n");
			break;
		}
	}
}
*/

/*

*/
int trace_line_interpolate(point_t end_point) {
	int x_diff;
	int y_diff;
	int xy_bal;
	
	x_diff = end_point.x - current_point.x;
	y_diff = end_point.y - current_point.y;
	
	dir_x(x_diff);
	dir_y(y_diff);
	
	x_diff = abs(end_point.x - current_point.x);
	y_diff = abs(end_point.y - current_point.y);
	
	xy_bal = x_diff - y_diff;

	while(current_point.x != end_point.x
			|| current_point.y != end_point.y) {
		if(xy_bal > 0) {
			step_x();
			
			xy_bal -= y_diff;
		} else if(xy_bal < 0) {
			step_y();
			
			xy_bal += x_diff;
		} else {
			step_xy();
			
			xy_bal -= y_diff;
			xy_bal += x_diff;
		}
		
		if(steps > x_diff + y_diff) {
			printf("Ran too long!\n");
			break;
		}
	}
}

// testing only
//--------------------------------------------------------------------
int main() {
	time_t t;

	srand((unsigned) time(&t));

	point_t end = {
		(random() % 100) - 50,
		(random() % 100) - 50
	};
	
	/*
	current_point.x = 0;
	current_point.y = 0;
	
	printf("Trace Line\n");
	printf("(%d, %d) -> (%d, %d)\n", current_point.x, current_point.y, end.x, end.y);
	steps = 0;
	trace_line(end);
	
	
	current_point.x = 0;
	current_point.y = 0;
	
	printf("Trace Line (Alt)\n");
	printf("(%d, %d) -> (%d, %d)\n", current_point.x, current_point.y, end.x, end.y);
	steps = 0;
	trace_line_alt(end);
	
	
	current_point.x = 0;
	current_point.y = 0;
	
	printf("Trace Line (Diag)\n");
	printf("(%d, %d) -> (%d, %d)\n", current_point.x, current_point.y, end.x, end.y);
	steps = 0;
	trace_line_diag(end);
	*/
	
	
	current_point.x = 0;
	current_point.y = 0;
	
	printf("Trace Line (Interpolate)\n");
	printf("(%d, %d) -> (%d, %d)\n", current_point.x, current_point.y, end.x, end.y);
	steps = 0;
	trace_line_interpolate(end);
}

