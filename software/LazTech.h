/*
 * LazTech.h
 *
 *  Created on: Sep 1, 2016
 *  Author: yasminejamjoum
 */

#ifndef LAZTECH_H_
#define LAZTECH_H_
#include <iostream>
using namespace std;

class LazTech
{
public:
	LazTech(double x, double y); //point (x,y)
	LazTech(); // default constructor
	void start(); // turns on the laser cutter
	void end(); // turns off the laser cutter regardless of state
	double get_x();
	double get_y();
	void set_x(double x);
	void set_y(double y);
	void origin(double x, double y); //for calibration and reset purposes
	void cutCurve();
	void cutLine();
	void defaultState(string stroke, double width, double start); // default if selections are not filled before execution
	double bezierCurve(double, double, double, double, double, double, double, double); // bezier formula

private:
	double x1, x2, x3, x4, y1, y2, y3, y4; // point (x1,y1) are original pt
	double stroke;
	double fill;
	double width;
	double scale;
	double velocity;
};

#endif /* LAZTECH_H_ */
