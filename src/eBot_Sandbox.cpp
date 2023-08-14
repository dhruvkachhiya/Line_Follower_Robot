/*
 * eBot_Sandbox.cpp
 *
 *  Created on: 23-Feb-2022
 *      Author: TAs of CS 684 Spring 2021
 */


//---------------------------------- INCLUDES -----------------------------------

#include "eBot_Sandbox.h"
#include <stdlib.h>
#include <queue>


//------------------------------ GLOBAL VARIABLES -------------------------------

// To store data of left, center and right white line sensors
unsigned char left_wl_sensor_data, center_wl_sensor_data, right_wl_sensor_data;

int speed_PID;
const int Max_speed = 130; // just taken as [255/2]

float Kp = 10;
float Ki = 2;
float Kd = 2;

// global variables for sum of last 9 variables
float Ksr = 0.75;
int lastNineErrorSum = 0;
int lastNineAbsoluteErrorSum = 0;
std::queue<int> errors;
//---------------------------------- FUNCTIONS ----------------------------------

/*
*
* Function Name: calculate_pid
* Input: void
* Output: void
* Logic: Uses white line sensors to calculate the speed value
* Example Call: calculate_pid();
*	
*/
void calculate_pid(void)
{
int integral = 0, derivative = 0, previous_error = 0;

int error = error_make(left_wl_sensor_data, center_wl_sensor_data, right_wl_sensor_data);

// add to the last 9 sum
lastNineErrorSum += error;
lastNineAbsoluteErrorSum += abs(error);
errors.push(error);
if (errors.size() > 9) {
	lastNineErrorSum -= errors.front();
	lastNineAbsoluteErrorSum -= abs(errors.front());
	errors.pop();
}

integral = lastNineErrorSum;
derivative = error - previous_error;
previous_error = error;


speed_PID = (Kp*error) + (Ki*integral) + (Kd*derivative);

if (speed_PID > Max_speed) // limiter for controler output
{
speed_PID = Max_speed;
}
if(speed_PID < (-1*Max_speed))
{
speed_PID = -1*Max_speed;
}


}

/*
*
* Function Name: actuation
* Input: void
* Output: void
* Logic: Uses speed value to decide the pwm frequency for two motors and in turn actuation
* Example Call: actuation();
*
*/
void actuation(void)
{
const int speed = 125; // <= 255-Max_speed;
unsigned char left_speed, right_speed;

// calculate Srn
//int Srn = Ksr*(lastNineErrorSum); not required
int SrnAbs = Ksr*(lastNineAbsoluteErrorSum);

if(speed_PID>0) // bot need to make right turn
{
left_speed = (speed+speed_PID) - SrnAbs;
right_speed = (speed) - SrnAbs;
} else
{
left_speed = (speed) - SrnAbs;
right_speed = (speed+speed_PID) - SrnAbs;
}

velocity(left_speed, right_speed);
}

/**
 * @brief      Executes the logic to achieve the aim of Lab 4
 */
void traverse_line(void)
{
	forward();
	while (1)
	{
		left_wl_sensor_data = convert_analog_channel_data(left_wl_sensor_channel);
		center_wl_sensor_data = convert_analog_channel_data(center_wl_sensor_channel);
		right_wl_sensor_data = convert_analog_channel_data(right_wl_sensor_channel);

		calculate_pid();

		actuation();

	}
}

// error making fuction
int error_make(char L, char C, char R)
{
if(L>0 && C==0 && R>0 ) // center (bot should go straight)
{
return 0; 
} else if(L>0 && C==0 && R==0) //soft left (bot should take slight right turn)
{
return 500;
} else if(L==0 && C==0 && R>0) // soft rght (bot should take slight left turn)
{
return -500;
} else if(L>0 && C>0 && R==0) // left (bot should take right turn)
{
return 1000;
} else if (L==0 && C>0 && R>0) // Right (bot should take lest turn)
{
return -1000;
} else if(L>0 && C>0 && R>0) // no line detect (bot should go straight)
{
return 0;
} else if(L==0 && C==0 && R==0) // all sensor sence line(bot should take sharp turn let say right) 
{
return -1000;
} else
{
return 0;
}

}
