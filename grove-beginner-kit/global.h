// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include <Arduino.h>
#include "board.h"
#if USE_NOTECARD
#include <Notecard.h>
extern Notecard notecard;
#endif

// Debug output prefers to go out to serial, unless it isn't available and we need trace
#if USE_DEBUG && defined(serialDebugOut)
#define _Print		serialDebugOut.print
#define _Printf		serialDebugOut.printf
#define _Println	serialDebugOut.println
#elif USE_DEBUG && USE_NOTECARD && USE_NOTECARD_TRACE
#define _Print		NotePrint
#define _Printf		NotePrintf
#define _Println	NotePrintln
#else
#define _Print(x)
#define _Printf(x, ...)
#define _Println(x)
#endif

// Button handling
#if USE_GBK_BUTTON
#define BUTTON_IDLE						0
#define BUTTON_PRESS					1
#define BUTTON_DOUBLEPRESS				2
int buttonState(void);
bool buttonSetup(void);
#endif

// Buzzer
#if USE_GBK_BUZZER
bool buzzerSetup(void);
void buzzerAction(void);
#endif

// LED
#if USE_GBK_LED
bool ledSetup(void);
void ledSet(bool);
#endif

// OLED
#if USE_GBK_OLED
bool oledSetup(void);
void oledTest();
#endif

// Accel
#if USE_GBK_ACCEL_SENSOR
bool accelSetup(void);
void accelMeasure(void);
#endif

// Pressure
#if USE_GBK_PRESSURE_SENSOR
bool pressureSetup(void);
void pressureMeasure(void);
#endif

// Light
#if USE_GBK_LIGHT_SENSOR
bool lightSetup(void);
void lightMeasure(void);
#endif

// Sound
#if USE_GBK_SOUND_SENSOR
bool soundSetup(void);
void soundMeasure(void);
#endif

// Temp/Humidity
#if USE_GBK_HUMID_SENSOR
bool humidSetup(void);
void humidMeasure(void);
#endif

// Potentiometer
#if USE_GBK_POTENTIOMETER
bool potSetup(void);
void potLoop(void);
void potMeasure(void);
#endif
