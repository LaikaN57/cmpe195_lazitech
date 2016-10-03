#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <cmath>

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
}

LazTech:: ~LazTech(){

}
void LazTech::start()
{
	delay(1); //start with a second delay

	//steps per revolution

	STEPPER_PIN_XIN[0] = 0x0F; // STEP set to 1
	STEPPER_PIN_XIN[1] = 0x0F; //DIR set to 1
	STEPPER_PIN_XIN[2] = 0x0F; //MS1 set to 1
	STEPPER_PIN_XIN[3] = 0x0F; //MS2 set to 1
	STEPPER_PIN_XIN[4] = 0x00; // EN set to 0
	STEPPER_PIN_XIN[5] = 0x0F; //RESET set to 1

	STEPPER_PIN_YIN[0] = 0x0F; // STEP set to 1
	STEPPER_PIN_YIN[1] = 0x0F; //DIR set to 1
	STEPPER_PIN_YIN[2] = 0x0F; //MS1 set to 1
	STEPPER_PIN_YIN[3] = 0x0F; //MS2 set to 1
	STEPPER_PIN_YIN[4] = 0x00; // EN set to 0
	STEPPER_PIN_YIN[5] = 0x0F; //RESET set to 1

	cout << "Enabling Stepper Motor";

	MIC_PIN_XIN[0] = 0x0F;
	MIC_PIN_XIN[1] = 0x00;
	MIC_PIN_XIN[2] = 0x0F;
	MIC_PIN_XIN[3] = 0x0F;
	MIC_PIN_XIN[4] = 0x0F;
	MIC_PIN_XIN[5] = 0x0F;
	MIC_PIN_XIN[6] = 0x0F;
	MIC_PIN_XIN[7] = 0x0F;

	MIC_PIN_YIN[0] = 0x0F;
	MIC_PIN_YIN[1] = 0x00;
	MIC_PIN_YIN[2] = 0x0F;
	MIC_PIN_YIN[3] = 0x0F;
	MIC_PIN_YIN[4] = 0x0F;
	MIC_PIN_YIN[5] = 0x0F;
	MIC_PIN_YIN[6] = 0x0F;
	MIC_PIN_YIN[7] = 0x0F;


	//start the velocity
}

void LazTech::end()
{
	STEPPER_PIN_XIN[0] = 0x00; // STEP set to 0
	STEPPER_PIN_XIN[1] = 0x00; //DIR set to 0
	STEPPER_PIN_XIN[2] = 0x00; //MS1 set to 0
	STEPPER_PIN_XIN[3] = 0x00; //MS2 set to 0
	STEPPER_PIN_XIN[4] = 0x0F; // EN set to 1
	STEPPER_PIN_XIN[5] = 0x00; //RESET set to 0

	STEPPER_PIN_YIN[0] = 0x00; // STEP set to 0
	STEPPER_PIN_YIN[1] = 0x00; //DIR set to 0
	STEPPER_PIN_YIN[2] = 0x00; //MS1 set to 0
	STEPPER_PIN_YIN[3] = 0x00; //MS2 set to 0
	STEPPER_PIN_YIN[4] = 0x0F; // EN set to 1
	STEPPER_PIN_YIN[5] = 0x00; //RESET set to 0

	delay(1);//end with a second delay
	cout << "Disabling Stepper Motor";
}

void LazTech::delay(double a)
{
	for (int i = 0; i < 1000; i++){
		for (int j = 0; j < i; j++){
			//intentionally left blank
		}
	}
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

	double input[8] = { x1, y1, x2, y2, x3, y3, x4, y4 }; // map the 8 pts as input
	double mid_x = ((x1 + x2)/2);
	double mid_y = ((y1 + y2)/2);

	for (int i = 0; i < STEPPER_PIN_XIN[0] ; i++){
		STEPPER_PIN_XIN[0] = 0x0F;
		delay(0.5);
		STEPPER_PIN_XIN[0] = 0x00;
		delay(0.5);
	}

	end();
}

void LazTech::cutCurve(double x, double y, string stroke)
{
	start();
	//cutLine();
	bezierCurve( x1,  y1,  x2,  y2,  x3,  y3,  x4,  y4);
	end();
}

void LazTech::defaultState(string stroke, double width)
{
	stroke = "black";
	width = 1;
	origin(0, 0); //start pt
}

//Bezier Curve formula calculates pt on curve with 4 controlpts
double LazTech::bezierCurve (double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	double Pt1 = ( x1,  y1);
	double Pt2 = ( x2,  y2);
	double Pt3 = ( x3,  y3);
	double Pt4 = ( x4,  y4);

	int t = 0;
	int t2 = t * t;
	int t3 = t2 * t;
	int tx = 1-t;
	int tx2 = tx * tx;
	int tx3 = tx2 * tx;
	int pt ((tx3 * Pt1) + (3 * t * tx2 * Pt2) + (3 * t2 * tx * Pt3) + (t3 * Pt4));

	return pt;

}

//http://stackoverflow.com/questions/785097/how-do-i-implement-a-bézier-curve-in-c
double LazTech:: getPt( double n1 , double n2 , float perc )
{
    double diff = n2 - n1;

    double result = n1 + ( diff * perc );

    return result;
}

double LazTech:: factorial(double num)
{
	if (num <= 1)
	{
		return 1;
	}
	else
	{
		num = num*factorial(num-1);
		return num;
	}
}

double LazTech:: binomial_coeff(double a, double b)
{
	double diff = a - b;
	double b_diff = factorial(b) * factorial(diff);
	double coeff = factorial(a) / (b_diff);
	return coeff;

}

void LazTech:: getPt_2(){
for( double i = 0 ; i < 1 ; i += 0.01 ){
    x1 = getPt( x1 , x2 , i );
    y1 = getPt( y1 , y2 , i );
    x2 = getPt( x2 , x3 , i );
    y2 = getPt( y2 , y3 , i );

   double x = getPt( x1 , x2 , i );
   double y = getPt( y1 , y2 , i );

   cutCurve( x , y , "black" );
}
}

//Curve with multiple points inputed

Pt LazTech:: getBezierPoint(std::vector<Pt>& pts, double t)
{
	Pt pt;
	//pt.x = 0;
	//pt.y = 0;
	std::size_t length = pts.size(); //size in bytes

	for(std::size_t i = 0; i < length; i++)
	{
		pt += pts[i] * binomial_coeff( length - 1, i) * pow(1 - t, length - 1 - i ) * pow(t,i);
//		pt.x = pow((1-t), 3) * pts[0].x + 3 * t * pow((1-t), 2) * pts[1].x + 3 * (1-t) * pow(t, 2) * pts[2].x + pow(t, 3) * pts[3].x;
//		pt.x = pow((1-t), 3) * pts[0].y + 3 * t * pow((1-t), 2) * pts[1].y + 3 * (1-t) * pow(t, 2) * pts[2].y + pow(t, 3) * pts[3].y;
	}

//	Pt* tmp = new Pt[numPoints];
//    memcpy(tmp, points, numPoints * sizeof(Pt));
//    int i = numPoints - 1;
//    while (i > 0) {
//        for (int k = 0; k < i; k++)
//            tmp[k] = tmp[k] + t * ( tmp[k+1] - tmp[k] );
//        i--;
//    }
//    Pt answer = tmp[0];
//    delete[] tmp;
    return pt;
}

void LazTech::add_curve(int a, int b, int c, int d, int e, int f)
{

}

void LazTech::stroke_line()
{

}
