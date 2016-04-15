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
	square_butt_caps = 0,
	
};

enum line_join_t {
	mitered_joins = 0,
	
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
	void * dash_pattern,
	int stroke_adjustment = 0,
} gfx_state_t;
