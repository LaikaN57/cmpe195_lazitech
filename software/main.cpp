#include "LazTech.cpp"
#include "LazTech.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <cstdio>

using namespace std;

int main()
{
	//User inputs the pts manually
//	double input[8];
//	cout << "Enter 8 pts" << input[8];
//	cin >> input[8];

	//pts inputed without user interface
	std::vector<std::vector<Pt> > pts;
	double x_input;
	double y_input;
	double delta; //delta time variable; 0-1; the smaller the more points calculated across the curve
	int endpt; // control point
	int count_pts = 0;
	char count_endpts = 0;

	cin >> count_pts >> delta; // # of lines inputed and delta time variable; 0-1

	for(int i = 0; i < count_pts; i++)
	{
		cin >> x_input >> y_input >> endpt; // x and y pt with 0 or 1 for hard/soft control point
		Pt pt(x_input, y_input);
		if (count_endpts != 0 && endpt == 1)//make sure the counter is not empty and end point flag is enabled and the last number is included in the input
				{
					pts.push_back(std::vector<Pt>()); //push inputs on to stack in the (x, y) format
					pts[pts.size() - 1].push_back(pt); //size of the inputs
					count_endpts++;
					continue;
				}
				pts[pts.size() - 1].push_back(pt);
		 if (count_endpts != 0 && endpt == 1 && i != count_pts -1)//make sure the counter is not empty and end point flag is enabled and the last number is included in the input
		{
			pts.push_back(std::vector<Pt>()); //push inputs in the (x, y) format
			pts[pts.size() - 1].push_back(pt); //size of the inputs
			count_endpts++;
		}
	}

	for(std::size_t i = 0; i < pts.size(); i++) // size in bytes
	{
		for(double t = 0; t <= 1; t += delta)
		{
			getBezierPoint(pts[i], t);
			cout << endl;
		}

	}
	return 0;
}
//	while (1)
//	{
//		PORTB = 0b00000001;
//	    delay(1);
//	    PORTB = 0b00000010;
//	    delay(1);
//	    PORTB = 0b00000100;
//	    delay(1);
//	    PORTB = 0b00001000;
//	    delay(1);
//	}
