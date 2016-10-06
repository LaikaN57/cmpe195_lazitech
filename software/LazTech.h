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

uint8_t STEPPER_PIN_XIN[6] = {11, 14, 5, 6, 23, 7};
//Declare pin functions on the stepper motors (ES Package)
//Inputs of the stepper motor drivers
//Pin 11 is STEP
//Pin 14 id DIR
//Pin 5 is MS1
//Pin 6 is MS2
//Pin 23 is EN
//Pin 7 is RESET

uint8_t STEPPER_PIN_YIN[6] = {11, 14, 5, 6, 23, 7};
//Declare pin functions on the stepper motors (ES Package)
//Inputs of the stepper motor drivers
//Pin 11 is STEP
//Pin 14 id DIR
//Pin 5 is MS1
//Pin 6 is MS2
//Pin 23 is EN
//Pin 7 is RESET

uint8_t STEPPER_PIN_OUT[4] = {18, 15, 19, 22};
//Outputs from stepper motor drivers
//Pin 18 is OUT1A
//Pin 15 is OUT1B
//Pin 19 is OUT2A
//Pin 22 is OUT2B

//States
uint8_t STEPPER_STATE_OFF = 0;
uint8_t STEPPER_STATE_STOP = 1;
uint8_t STEPPER_STATE_FORWARDS = 2;
uint8_t STEPPER_STATE_STEPS = 3;
uint8_t STEPPER_STATE_TARGET = 4;
uint8_t STEPPER_STATE_BACKWARDS = 5;

uint8_t STEPPER_TRACKER = 0;

//PIC32MX250F128B (28-pin SPDIP)
uint8_t ADCON1=0x06; //Changes PORT A to Digital; turns off analog to digital converters
uint8_t	CMCON =0x07; //Turns Analog Comparators
uint8_t	TRISA=0x00; //Configure PORT A as Output
uint8_t	TRISB=0x00; //Configure PORT B as Output
uint8_t	TRISC=0x00; //Configure PORT C as Output

uint8_t	PORTA=0x0F;
////PORTA is RA0 - RA10
//#byte	PORTB=0x0F
////PORTB is RB0 - RB10
//#byte	PORTC=0x0F
////PORTC is RC0 - RC10

uint8_t MIC_PIN_XIN[7] = {9, 10, 11, 32, 31, 30, 29};
//Pin 9 connected to Reset of X
//Pin 10 connected to EN of X
//Pin 11 connected to SLEEP of X
//Pin 32 connected to STEP of X
//Pin 31 connected to MS1 of X
//Pin 30 connected to MS2 of X
//Pin 29 connected to DIR of X

uint8_t MIC_PIN_YIN[7] = {12, 13, 14, 28, 27, 26, 25};
//Pin 12 connected to Reset of Y
//Pin 13 connected to EN of Y
//Pin 14 connected to SLEEP of Y
//Pin 28 connected to STEP of Y
//Pin 27 connected to MS1 of Y
//Pin 26 connected to MS2 of Y
//Pin 25 connected to DIR of Y

//K40 CO2 Laser Engraver/Cutter
//#define X_MAX_POS 337
//#define X_MIN_POS 0
//#define Y_MAX_POS 230
//#define Y_MIN_POS 0

//communication speed of the printer; need to know the value
#define BAUDRATE  //value?

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

//
////Enabling
//#define X_ON 1
//#define Y_ON 1
//#define STEP_ON 1
//#define DIR_ON 1
//#define MS1_ON 1
//#define MS2_ON 1
//#define EN_ON 0
//#define RESET_ON 0

//Disabling
//#define X_OFF 0
//#define Y_OFF 0
//#define STEP_OFF 0
//#define DIR_OFF 0
//#define MS1_OFF 0
//#define MS2_OFF 0
//#define EN_OFF 1
//#define RESET_OFF 1

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
	void cutLine(std::vector<Pt>& pts, double t, string stroke);
	void cutCurve(std::vector<Pt>& pts, double t, string stroke);
	void defaultState(string stroke, double width); // default if selections are not filled before execution
	double bezierCurve(double, double, double, double, double, double, double, double); // bezier formula
	double getPt( double n1 , double n2 , float perc );
	double factorial(double num);
	double binomial_coeff( double a, double b);
	void getPt_2();
	Pt getBezierPoint(std::vector<Pt>& pts, double t);
	void add_curve(std::vector<Pt>& pts);
	void stroke_line();


private:
	double x1, x2, x3, x4, y1, y2, y3, y4; // point (x1,y1) are original pt
	double stroke;
	double fill;
	double width;
	double scale;
	double velocity;
	//double acceleration;
	//double input[];
};

#endif /* LAZTECH_H_ */
