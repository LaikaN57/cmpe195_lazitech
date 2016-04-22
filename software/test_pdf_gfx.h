enum color_space_t {
	DeviceGray,
	DeviceRGB,
	DeviceCMYK,
	CalGray,
	CalRGB,
	Lab,
	ICCBased,
	Pattern,
	Indexed,
	Seperation,
	DeviceN
};

enum line_cap_t {
	square_butt_caps = 0, // ends of path squared off without projection
	square_projecting_caps = 1, // ends of path squared off with projection
	round_caps = 2 // ends of path circled off 
};

enum line_join_t {
	mitered_joins = 0, // angled edge (sharp edge)
	rounded_joins = 1, // rounded edge
	bevel_joins = 2 // butt caps
	
};

enum dash_pattern_t {
	no_dash = 0, //no dash; solid 	
	equal_dash = 1, // 3 units off, 3 units on
	dash_pattern_a = 2; // 1 unit on, 2 units off
	dash_pattern_b = 3; // 2 units on, 1 unit off
	dash_pattern_c = 4; // 2 units off, 3 units on, 5 units off
	dash_pattern_d = 5; // 1 unit on, 3 units off, 2 units on
};

// graphics state
typedef struct {
	double ctm[6],
	void * clipping_path,
	color_space_t color_space = DeviceGray,
	double color_stroke[4] = {0},
	double color_fill[4] = {0},
	double line_width = 1.0,
	line_cap_t line_cap = square_butt_caps,
	line_join_t line_join = mitered_joins,
	double miter_limit = 10.0,
	//void * dash_pattern,
	dash_pattern_t dash_pattern = no_dash,
	int stroke_adjustment = 0,
} gfx_state_t;
