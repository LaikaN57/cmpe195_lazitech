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
	x2 = 0;
	y2 = 0;
	x3 = 0;
	y3 = 0;
	x4 = 0;
	y4 = 0;
	stroke = 0;
	fill = 0;
	width = 0;
	scale = 0;
	velocity = 0;
	input = 0;
}

LazTech::LazTech()
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	x3 = 0;
	y3 = 0;
	x4 = 0;
	y4 = 0;
	stroke = 0;
	fill = 0;
	width = 0;
	scale = 0;
	velocity = 0;
	input = 0;
}

void LazTech::start()
{
	delay(1); //start with a second delay

	//steps per revolution

	STEP_ON; //STEP set to 1
	DIR_ON; //DIR set to 1
	MS1_ON; //MS1 set to 1
	MS2_ON; //MS2 set to 1
	EN_ON; //EN set to 1
	RESET_OFF; // RESET set to 0
	cout << "Enabling Stepper Motor";

	//start the velocity
}

void LazTech::end()
{
	STEP_OFF; // STEP set to 0
	DIR_OFF; //DIR set to 0
	MS1_OFF; //MS1 set to 0
	MS2_OFF; //MS2 set to 0
	EN_OFF; // EN set to 1
	RESET_OFF; //RESET set to 1

	delay(1);//end with a second delay
	cout << "Disabling Stepper Motor";
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

void LazTech::cutLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) // input as an XYXYXYXY
{
	start();

	input[8] = {  x1,  y1,  x2,  y2,  x3,  y3,  x4,  y4 }; // map the 8 pts as input
	double mid_x = ((x1 + x2)/2);
	double mid_y = ((y1 + y2)/2);

	for (int i = 0; i < step ; i++){
		STEP_ON;
		delay(0.5);
		STEP_OFF;
		delay(0.5);
	}

	end();
}

void LazTech::cutCurve()
{
	start();
	cutLine();
	bezierCurve( x1,  y1,  x2,  y2,  x3,  y3,  x4,  y4);
	end();
}

void LazTech::defaultState(string stroke, double width, double start)
{
	stroke = "black";
	width = 1;
	start = origin(0, 0);
}

//Bezier Curve formula calculates pt on curve with 4 controlpts
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
	int pt ((tx3 * Pt1) + (3 * t * tx2 * Pt2) + (3 * t2 * tx * Pt3) + (t3 * Pt4));

	return pt;

}

void LazTech::add_curve(int a, int b, int c, int d, int e, int f)
{

}

void LazTech::stroke_line()
{

}
