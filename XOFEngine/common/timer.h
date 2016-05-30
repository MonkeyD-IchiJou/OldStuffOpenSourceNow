#ifndef _TIMER_H
#define _TIMER_H
/******************************************************************************/
/*!
\file	Timer.h
\author Chuk Yih Jou
\brief
Calculate time and frame
*/
/******************************************************************************/
#include <windows.h>

/******************************************************************************/
/*!
		Class Stopwatch:
\brief	Calculate time 
*/
/******************************************************************************/
class StopWatch
{
 
 private:
     
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double getElapsedTime(); // get time in seconds since the last call to this function
     void waitUntil(double time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H