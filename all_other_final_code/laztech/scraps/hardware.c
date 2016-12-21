// these must be on the same port
#define STEP_PORT 0
#define X_STEP_PIN 0
#define Y_STEP_PIN 1

#define X_DIR_PORT 0
#define X_DIR_PIN 2
#define Y_DIR_PORT 0
#define Y_DIR_PIN 3

#define X_HOME_PORT 1
#define X_HOME_PIN 0
#define Y_HOME_PORT 1
#define Y_HOME_PIN 1

// fake enums
#define X_DIR_POS 0
#define X_DIR_NEG 1
#define Y_DIR_POS 0
#define Y_DIR_NEG 1

void step_x();
void step_y();
void step_xy();

void x_dir(uint8_t dir);
void y_dir(uint8_t dir);

void move_n() { y_dir(Y_DIR_NEG); step_y(); }
void move_s() { y_dir(Y_DIR_POS); step_y(); }
void move_w() { x_dir(X_DIR_NEG); step_x(); }
void move_e() { x_dir(X_DIR_POS); step_x(); }
void move_nw() { x_dir(X_DIR_NEG); y_dir(Y_DIR_NEG); step_xy(); }
void move_ne() { x_dir(X_DIR_POS); y_dir(Y_DIR_NEG); step_xy(); }
void move_sw() { x_dir(X_DIR_NEG); y_dir(Y_DIR_POS); step_xy(); }
void move_se() { x_dir(X_DIR_POS); y_dir(Y_DIR_POS); step_xy(); }

void trace_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
	// move to (x1, y1)

	// compute which direction has more travel
	uint32_t x = abs(x1 - x2);
	uint8_t x_dir = x2 - x1 < 0 ? X_DIR_NEG : X_DIR_POS; x_dir(x_dir);
	uint32_t y = abs(y1 - y2);
	uint32_t i;
	int32_t step;

	if(x > y) {
		// major step dir is X
		step = x1 > x2 ? -1 : 1;
		for(i = x1; i < x2; i += step) {
			if(j+1 < m*i+b) {
				step_y();
			}
			step_x();
		}
	} else {
		// major step dir is Y
	}
	
}

void home() {
	dir_x(X_DIR_NEG);
	dir_y(Y_DIR_NEG);

	while(!is_x_home() && !is_y_home()) {
		if(!is_x_home()) {
			step_x();
		}

		if(!is_y_home()) {
			step_y();
		}
	}
}

void move(uint32_t x, uint32_t y) {

}
