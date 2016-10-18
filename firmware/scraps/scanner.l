%option main noyywrap

%option 8bit

%{
#include <math.h>

#define GFX_STATE_SIZE 10
#define NUMBER_STACK_SIZE 10

typedef enum {
	DeviceGrey,
} color_space_t;

typedef enum {
	butt_cap = 0,
	round_cap = 1,
	projecting_square_cap = 2
} line_cap_t;

typedef enum {
	miter_join = 0,
	round_join = 1,
	bevel_join = 2
} line_join_t;

typedef struct {
	long double ctm[6];
	color_space_t color_space;
	long double color[4];
	long double line_width;
	line_cap_t line_cap;
	line_join_t line_join;
	long double miter_limit;
	unsigned long double dash_array[10];
	unsigned long double dash_phase;
} gfx_state_t;

// need to init gfx 0
gfx_state_t gfx_state_stack[GFX_STATE_SIZE];
uint8_t gfx_state_stack_len = 0;

uint8_t scanner_debug = 3;
long double number_stack[NUMBER_STACK_SIZE];
uint8_t number_stack_len = 0;

void stroke();

%}

%%

  /* General Graphics State */
"w" { number_stack_len -= 1; } // line width
"J" { number_stack_len -= 1; } // line cap style
"j" { number_stack_len -= 1; } // line join style
"M" { number_stack_len -= 1; } // miter limit
"d" { printf("Ignored an array.\n"); number_stack_len -= 1; } // line dash pattern
"gs" { printf("Ignored 'gs'.\n"); } // EXTERNAL GRAPHICS STATE

  /* Special Graphics State */
"q" { if(scanner_debug > 2) printf("Pushed gfx state.\n"); /* Push GFX State */ gfx_state_stack_len++; }
"Q" { if(scanner_debug > 2) printf("Popped gfx state.\n"); /* Pop GFX State */ gfx_state_stack_len--; }
"cm" { if(scanner_debug > 2) printf("Modified current transfromation matrix.\n"); number_stack_len -= 6; }

  /* Path Construction */
"m" { if(scanner_debug > 2) printf("Move.\n"); number_stack_len -= 2; } // move
"l" { if(scanner_debug > 2) printf("Line.\n"); number_stack_len -= 2; } // line
"c" { if(scanner_debug > 2) printf("Curve.\n"); number_stack_len -= 6; } // curve
"h" { if(scanner_debug > 2) printf("Close.\n"); } // close
"re" { if(scanner_debug > 2) printf("Rectangle.\n"); number_stack_len -= 4; } // rectangle

  /* Path Painting */
"S" {
	if(scanner_debug > 2)
		printf("CUT 'S'!\n");
	stroke();
} // Stroke
"B*" {
	if(scanner_debug > 2)
		printf("CUT 'B*'!\n");
	stroke();
} // [fill (even-odd) and] Stroke

  /* Color */
"RG" { if(scanner_debug > 2) printf("Modified stroke color.\n"); number_stack_len -= 3; }
"rg" { if(scanner_debug > 2) printf("Modified non-stoke color.\n"); number_stack_len -= 3; }

  /* Number */
(\+|-)?(([[:digit:]]*\.[[:digit:]]+)|([[:digit:]]+\.?)) {
	if(scanner_debug > 3)
		printf("Stored number '%s' in stack[%u].\n", yytext, number_stack_len);

	if(number_stack_len < NUMBER_STACK_SIZE)
		number_stack[number_stack_len++] = atof(yytext);
	else
		printf("ERROR: Stack out of bounds.\n");
}

  /* PDF Array */
\[(.*?)\] {
	if(scanner_debug > 2)
		printf("Matched PDF array '%s'.\n", yytext);
}

  /* PDF Name */
\/[^[:space:]]* {
	if(scanner_debug > 2)
		printf("Matched PDF name '%s'.\n", yytext);
}

  /* Whitespace */
[[:space:]] {
	if(scanner_debug > 4)
		printf("Matched whitespace.\n");
}

  /* Save time and eliminate pop/push */
Q[[:space:]]q {
	printf("Ignored a pop/push combo.\n");
}

  /* Other */
. {
	printf("Unknown character '%s'.\n", yytext);
}

%%

