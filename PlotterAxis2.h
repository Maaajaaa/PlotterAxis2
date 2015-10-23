/*
 * PlotterAxis.h - Library for plotter with stepper-motor-driven axis.
 * Created by Mattis Männel aka SparkyCola, October 8, 2015.
 */

#ifndef PlotterAxis_h
#define PlotterAxis_h

#include "Arduino.h"


class PlotterAxis2
{
public:
    PlotterAxis2(int NumberOfSteps, int Pin1,int Pin2, int Pin3 , int Pin4, int ForklightPin, int EnablePin);
    long position();
    void setPosition(int position_to_move);
    void reset();
    void setSpeed(long whatSpeed);   //speed in RPMs
    long getSpeed();
    void disable();
    void enable();
    bool isEnabled();
    int version();

private:
    void step(int Steps);

    int stepNumber, numberOfSteps;
    int pin1, pin2, pin3, pin4;
    long pos;
    int speed;
    int res;
    int forklightPin, enablePin;
    bool enabled;
};

#endif
