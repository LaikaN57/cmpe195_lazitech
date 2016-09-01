//============================================================================
// Name        : LazTech.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "LazTech.h"
using namespace std;

LazTech::LazTech(double x, double y)
{
	x1 = x;
	y1 = y;
}

LazTech::LazTech()
{
	x1 = 0;
	y1 = 0;
}

void LazTech::start()
{

}

void LazTech::end()
{

}

double LazTech::get_x()
{
	return x1;
}

double LazTech::get_y()
{
	return y1;
}

void LazTech:: set_x(double x)
{
	x1 = x;
}

void LazTech:: set_y(double y)
{
	y1 = y;
}

void LazTech::origin (double x, double y)
{
	double length = 0; // default length of machine, value????
	double height = 0; // default height of machine, value????
	double xOffset =  x - length; // actual x - default
	double yOffset =  y - height; // actual y - default
}

void LazTech::cutLine()
{

}

void LazTech::cutCurve()
{

}

void LazTech::defaultState(string stroke, double width, double start)
{
	stroke = "black";
	width = 1;
	start = LazTech(0,0);
}

//Bezier Curve formula
double LazTech::bezierCurve (double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	double Pt1 = ( x1,  y1);
	double Pt2 = ( x2,  y2);
	double Pt3 = ( x3,  y3);
	double Pt4 = ( x4,  y4);

	int t;
	int t2 = t * t;
	int t3 = t2 * t;
	int tx = 1-t;
	int tx2 = tx * tx;
	int tx3 = tx2 * tx;
	return ((tx3 * Pt1) + (3 * t * tx2 * Pt2) + (3 * t2 * tx * Pt3) + (t3 * Pt4));

}

void LazTech::add_curve(int a, int b, int c, int d, int e, int f)
{

}

void LazTech::stroke_line()
{

}

