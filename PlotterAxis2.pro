TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    PlotterAxis2.cpp \


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    PlotterAxis2.h \
    ../../../arduino-1.6.5/hardware/arduino/avr/cores/arduino/Arduino.h \
    ../../../arduino-1.6.5/libraries/Stepper/src/Stepper.h \
    ../../../arduino-1.6.5/hardware/arduino/avr/cores/arduino/HardwareSerial.h

