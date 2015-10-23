/*
 * PlotterAxis.cpp - Library for plotter with stepper-motor-driven axis.
 * Created by Mattis Männel aka SparkyCola, October 8, 2015.
 */

//only for autocomplete & hightlighting in qt
#if QT_VERSION <= 0x040000

#include "../../../arduino-1.6.5/hardware/arduino/avr/cores/arduino/Arduino.h"
#endif

#include "PlotterAxis2.h"

PlotterAxis2::PlotterAxis2(int NumberOfSteps, int Pin1,int Pin2, int Pin3 , int Pin4, int ForklightPin, int EnablePin)
{
    pin1 = Pin1;
    pin2 = Pin2;
    pin3 = Pin3;
    pin4 = Pin4;

    numberOfSteps = NumberOfSteps;
    forklightPin = ForklightPin;
    enablePin = EnablePin;
    stepNumber = 0;
    enabled = 255;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    pinMode(forklightPin, INPUT);       //set forklightPin as input
    digitalWrite(forklightPin, HIGH);   //activate pull-up resistors for forklightPin
    pinMode(enablePin, OUTPUT);
    analogWrite(enablePin, 255);
}

long PlotterAxis2::position()
{
    return pos;
}

void PlotterAxis2::setPosition(int position_to_move)
{
    Serial.print("...");
    if(position_to_move >= 0)
        for(int i = 0; i < position_to_move; i++){
            step(1);
            Serial.println(i+1);
        }
    else
        for(int i = 0; i < position_to_move * -1; i++){
            step(-1);
            Serial.println(i+1);
        }
    Serial.println("{done}");
    //pos = position_to_move;
}

void PlotterAxis2::reset()
{
    while(!digitalRead(forklightPin))
        step(-1);
    pos = 0;
}

void PlotterAxis2::setSpeed(long whatSpeed)
{
    speed = whatSpeed;
}

long PlotterAxis2::getSpeed()
{
    return speed;
}

void PlotterAxis2::disable()
{
    digitalWrite(enablePin, LOW);
    enabled = false;
}

void PlotterAxis2::enable()
{
    digitalWrite(enablePin, HIGH);
    enabled = true;
}

bool PlotterAxis2::isEnabled()
{
    return enabled;
}

int PlotterAxis2::version()
{
    return 2;
}

void PlotterAxis2::step(int Steps)
{
    if(Steps == 1)
        if(stepNumber == 3)
            stepNumber = 0;
        else
            stepNumber++;
    if(Steps == -1)
        if(stepNumber == 0)
            stepNumber = 3;
        else
            stepNumber--;

    //Serial.print("Step: "); Serial.print(stepNumber);
    switch (stepNumber) {
      case 0:  // 1010
        //Serial.println("- 1010");
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
      break;
      case 1:  // 0110
        //Serial.println("- 0110");
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, HIGH);
        digitalWrite(pin4, LOW);
      break;
      case 2:  //0101
        //Serial.println("- 0101");
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
      break;
      case 3:  //1001
        //Serial.println("- 1001");
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
        digitalWrite(pin3, LOW);
        digitalWrite(pin4, HIGH);
      break;
    }
    delay(60L * 1000L / numberOfSteps / speed);
}
