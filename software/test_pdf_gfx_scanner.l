%option noyywrap 
%option never-interactive batch
%option yylineno
%option bison-bridge bison-locations
%option nounistd
%option ecs meta-ecs
%option debug
%option nodefault

%{
#include <math.h>	// atof

double* number_stack;

gfx_state_t current_gfx_state;
gfx_state_t* gfx_state_stack;

point_t start_point;
point_t current_point;

curve_t* curve_queue;

%}

%%

[[:digit:]]+"."[[:digit:]]+	{ number_push(atof(yytext)); }	// save digit to stack

// general graphics state ops
"w"		{ gfx.lineWidth = number_pop(); }	// set lineWidth
"J"		{ gfx.lineCap = number_pop(); }		// set lineCap
"j"		{ gfx.lineJoin = number_pop(); }	// set lineJoin
"M"		{ gfx.miterLimit = number_pop(); }	// set miterLimit
"d"		{ number_pop(); }					// ignore / kill dashPhase
"ri"	{  }	// 
"i"		{ number_pop(); }					// ignore / kill flatness
"gs"	{  }	// 

// special graphics state ops
"q"		{ gfx_push(); }		// gfx push
"Q"		{ gfx_pop(); }		// gfx pop
"cm"	{
		int f = number_pop();
		int e = number_pop();
		int d = number_pop();
		int c = number_pop();
		int b = number_pop();
		int a = number_pop();
	
		gfx_append_ctm(a, b, c, d, e, f); // TODO: make this do math stuff
	}	// append the CTM

// color ops
"CS"	{  }	// set stroke color space
"cs"	{  }	// set fill color space
// TODO: find color space names?
"SC"	{
		switch(gfx.color_space) {
			case DeviceGray:
			case CalGray:
			case Indexed:
				int g = number_pop();
				
				gfx.color_stroke[0] = g;
				break;
			case DeviceRGB:
			case CalRGB:
			case Lab:
				int b = number_pop();
				int g = number_pop();
				int r = number_pop();

				gfx.color_stroke[0] = r;
				gfx.color_stroke[1] = g;
				gfx.color_stroke[2] = b;
				break;
			case DeviceCMYK:
				int k = number_pop();
				int y = number_pop();
				int m = number_pop();
				int c = number_pop();

				gfx.color_stroke[0] = c;
				gfx.color_stroke[1] = m;
				gfx.color_stroke[2] = y;
				gfx.color_stroke[3] = k;
				break;
			default:
				break;
		}
	}	// set stroke color value
"SCN"	{  }	// set stroke color value
"sc"	{
		switch(gfx.color_space) {
			case DeviceGray:
			case CalGray:
			case Indexed:
				int g = number_pop();
				
				gfx.color_fill[0] = g;
				break;
			case DeviceRGB:
			case CalRGB:
			case Lab:
				int b = number_pop();
				int g = number_pop();
				int r = number_pop();

				gfx.color_fill[0] = r;
				gfx.color_fill[1] = g;
				gfx.color_fill[2] = b;
				break;
			case DeviceCMYK:
				int k = number_pop();
				int y = number_pop();
				int m = number_pop();
				int c = number_pop();

				gfx.color_fill[0] = c;
				gfx.color_fill[1] = m;
				gfx.color_fill[2] = y;
				gfx.color_fill[3] = k;
				break;
			default:
				break;
		}
	}	// set fill color value
"scn"	{  }	// set fill color value
"G"		{
		gfx.color_space = DeviceGray;
		
		int g = number_pop();

		gfx.color_stroke[0] = g;
	}	// xs
"g"		{
		gfx.color_space = DeviceGray;
		
		int g = number_pop();

		gfx.color_fill[0] = g;
	}	// xf
"RG"	{
		gfx.color_space = DeviceRGB;
		
		int b = number_pop();
		int g = number_pop();
		int r = number_pop();

		gfx.color_stroke[0] = r;
		gfx.color_stroke[1] = g;
		gfx.color_stroke[2] = b;
	}	// xs
"rg"	{
		gfx.color_space = DeviceRGB;
		
		int b = number_pop();
		int g = number_pop();
		int r = number_pop();

		gfx.color_fill[0] = r;
		gfx.color_fill[1] = g;
		gfx.color_fill[2] = b;
	}	// xf
"K"		{
		gfx.color_space = DeviceCMYK;
		
		int k = number_pop();
		int y = number_pop();
		int m = number_pop();
		int c = number_pop();

		gfx.color_stroke[0] = c;
		gfx.color_stroke[1] = m;
		gfx.color_stroke[2] = y;
		gfx.color_stroke[3] = k;
	}	// xs
"k"		{
		gfx.color_space = DeviceCMYK;
		
		int k = number_pop();
		int y = number_pop();
		int m = number_pop();
		int c = number_pop();

		gfx.color_fill[0] = c;
		gfx.color_fill[1] = m;
		gfx.color_fill[2] = y;
		gfx.color_fill[3] = k;
	}	// xf

// path construction ops
"m"		{
		// kill current list
		curve_empty();

		int y = number_pop();
		int x = number_pop();
		
		start_point = {x, y};
		current_point = {x, y};
	}	// move
"l"		{
		int y = number_pop();
		int x = number_pop();
		
		curve_add(current_point.x, current_point.y, current_point.x, current_point.y, x, y, x, y);
		
		current_point = {x, y};
	}	// line
"c"		{
		int y3 = number_pop();
		int x3 = number_pop();
		int y2 = number_pop();
		int x2 = number_pop();
		int y1 = number_pop();
		int x1 = number_pop();
		
		curve_add(current_point.x, current_point.y, x1, y1, x2, y2, x3, y3);
		
		current_point = {x3, y3};
	}	// curve123
"v"		{
		int y3 = number_pop();
		int x3 = number_pop();
		int y2 = number_pop();
		int x2 = number_pop();
		
		curve_add(
				current_point.x, current_point.y, current_point.x, current_point.y,
				x2, y2, x3, y3);
		
		current_point = {x3, y3};
	}	// curve23
"y"		{
		int y3 = number_pop();
		int x3 = number_pop();
		int y1 = number_pop();
		int x1 = number_pop();
		
		curve_add(current_point.x, current_point.y, x1, y1, x3, y3, x3, y3);
		
		current_point = {x3, y3};
	}	// curve13
"h"		{
		if(current_point.x != start_point.x || current_point.y != start_point.y) {
			curve_add(
					current_point.x, current_point.y, current_point.x, current_point.y,
					start_point.x, start_point.y, start_point.x, start_point.y);
			
			current_point.x = start_point.x;
			current_point.y = start_point.y;
		}
	}	// close
"re"	{
		// kill current list
		curve_empty();

		int h = number_pop();
		int w = number_pop();
		int y = number_pop();
		int x = number_pop();
		
		start_point = {x, y};
		current_point = {x, y};
		
		curve_add(x, y, x, y, x+w, y, x+w, y);
		curve_add(x+w, y, x+w, y, x+w, y+h, x+w, y+h);
		curve_add(x+w, y+h, x+w, y+h, x, y+h, x, y+h);
		curve_add(x, y+h, x, y+h, x, y, x, y);
	}	// rectangle

// cliping paths ops
"W"		{ set_clipping_curve(); }	// ignore?
"W*"	{ set_clipping_curve(); }	// ignore?

// path painting ops
"S"		{ stroke(); }	// stroke
"s"		{
		if(current_point.x != start_point.x || current_point.y != start_point.y) {
			curve_add(
					current_point.x, current_point.y, current_point.x, current_point.y,
					start_point.x, start_point.y, start_point.x, start_point.y);
			
			current_point.x = start_point.x;
			current_point.y = start_point.y;
		}
		
		stroke();
	}	// close and stroke
"f"|"F"		{
		if(current_point.x != start_point.x || current_point.y != start_point.y) {
			curve_add(
					current_point.x, current_point.y, current_point.x, current_point.y,
					start_point.x, start_point.y, start_point.x, start_point.y);
			
			current_point.x = start_point.x;
			current_point.y = start_point.y;
		}
	}	// close and fill / ignore fill
"f*"		{  }	// fill / ignore
"B"|"B*"	{ stroke(); }	// fill and stroke
"b"|"b*"	{
		if(current_point.x != start_point.x || current_point.y != start_point.y) {
			curve_add(
					current_point.x, current_point.y, current_point.x, current_point.y,
					start_point.x, start_point.y, start_point.x, start_point.y);
			
			current_point.x = start_point.x;
			current_point.y = start_point.y;
		}
		
		stroke();
	}	// close, fill, and stroke
"n"			{  }	// end (no op used for clipping paths)

// text objects ops
// text state ops
// text positinging ops
// text showing ops
// type 3 fonts
// shading patterns ops
// inline images ops
// xobjects ops
// marked content ops
// compatability ops

"["((.|\n)*)"]"	{  }	// ignore arrays

\n		{  }	// ignore
.		{  }	// ignore

%%

int main() {
	//the last two bytes of which must be YY_END_OF_BUFFER_CHAR
	//YY_BUFFER_STATE hdlr = yy_scan_buffer((char *) base, (yy_size_t) size);
	yylex();
	//yy_delete_buffer(hdlr);
}
