#ifndef LAZTECH_H_
#define LAZTECH_H_

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include "Pt.cpp"

using namespace std;

//PIC32MX250F128B
//#byte	ADCON1=0x06 //Changes PORT A to Digital; turns off analog to digital converters
//#byte	CMCON =0x07 //Disable Analog Comparators
//#byte	TRISA=0x00 //Configure PORT A as Output
//#byte	TRISB=0x00 //Configure PORT B as Output
//#byte	TRISC=0x00 //Configure PORT C as Output
//#byte	TRISD=0x00 //Configure PORT D as Output
//#byte	TRISE=0x00 //Configure PORT E as Output
//#byte	PORTA=0
//#byte	PORTB=0
//#byte	PORTC=0
//#byte	PORTD=0
//#byte	PORTE=0
//#define MCLR 18 //Connect to RESET
//#define VSS 39 //Connect to EN
//#define VDD 40 //Connect to step
//#define //Connect to dir
//#define //Connect to MS1
//#define //Connect to MS2

//K40 CO2 Laser Engraver/Cutter
//#define X_MAX_POS 337
//#define X_MIN_POS 0
//#define Y_MAX_POS 230
//#define Y_MIN_POS 0

//communication speed of the printer; need to know the value
#define BAUDRATE  //value?

//Declare pin functions on the stepper motors (ES Package)
//Inputs
#define step 14
#define dir 17
#define MS1 8
#define MS2 9
#define EN  2
#define RESET 10
//Outputs to Motors
#define OUT1A 21
#define OUT1B 18
#define OUT2A 22
#define OUT2B 1

//Acceleration and velocity
#define STEPPER_VELOCITY_DEFAULT           500
#define STEPPER_ACCELERATION_DEFAULT       1000
#define STEPPER_DECELERATION_DEFAUL        1000
#define STEPPER_MINIMUM_VOLTAGE_DEFAULT    8000

//Time
#define MAX_TIMER_VALUE 0xFFFF

#define STEPPER_PWM_MAX_DUTY_CYCLE 128

//Modes
#define STEP_MODE_FULL       1 //MS1 = LOW; MS2 = LOW
#define STEP_MODE_HALF       2 //MS1 = HIGH; MS2 = LOW
#define STEP_MODE_QUARTER    4 //MS1 = LOW; MS2 = HIGH
#define STEP_MODE_EIGTH      8 //MS1 = HIGH; MS2 = HIGH

//States
#define STEPPER_STATE_OFF    1
#define STEPPER_STATE_STOP   2
#define STEPPER_STATE_DRIVE  3
#define STEPPER_STATE_STEPS  4
#define STEPPER_STATE_TARGET 5

//RAMP State??
#define STEPPER_SPEEDRAMP_STATE_FORWARD        1
#define STEPPER_SPEEDRAMP_STATE_BACKWARD      -1
#define STEPPER_SPEEDRAMP_STATE_STOP           2
#define STEPPER_SPEEDRAMP_STATE_ACCELERATION   3
#define STEPPER_SPEEDRAMP_STATE_RUN            4
#define STEPPER_SPEEDRAMP_STATE_DECELERATION   5

//Direction
#define STEPPER_DIRECTION_FORWARD   1
#define STEPPER_DIRECTION_BACKWARD -1


//Enabling
#define X_ON 1
#define Y_ON 1
#define STEP_ON 1
#define DIR_ON 1
#define MS1_ON 1
#define MS2_ON 1
#define EN_ON 0
#define RESET_ON 0

//Disabling
#define X_OFF 0
#define Y_OFF 0
#define STEP_OFF 0
#define DIR_OFF 0
#define MS1_OFF 0
#define MS2_OFF 0
#define EN_OFF 1
#define RESET_OFF 1

class LazTech
{
public:
	LazTech(double x, double y); //point (x,y)
	~LazTech();
	LazTech(); // default constructor
	void start(); // turns on the laser cutter
	void end(); // turns off the laser cutter regardless of state
	void delay(double a);
	double get_x();
	double get_y();
	void set_x(double x);
	void set_y(double y);
	void origin(double x, double y); //for calibration and reset purposes
	void cutLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);// input as an XYXYXYXY
	void cutCurve(double x, double y, string stroke);
	void defaultState(string stroke, double width); // default if selections are not filled before execution
	double bezierCurve(double, double, double, double, double, double, double, double); // bezier formula
	double getPt( double n1 , double n2 , float perc );
	double factorial(double num);
	double binomial_coeff( double a, double b);
	void getPt_2();
	Pt getBezierPoint(std::vector<Pt>& pts, double t);
	void add_curve(int a, int b, int c, int d, int e, int f);
	void stroke_line();


private:
	double x1, x2, x3, x4, y1, y2, y3, y4; // point (x1,y1) are original pt
	double stroke;
	double fill;
	double width;
	double scale;
	double velocity;
	//double acceleration;
	double input[];
};

#endif /* LAZTECH_H_ */
