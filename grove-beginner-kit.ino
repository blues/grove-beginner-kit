// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"

// Set if any of the sensors fails to initialize
const char *failure = NULL;

// Forwards
void actionPress(void);
void actionDoublePress(void);

// Arduino one-time setup
void setup() {
	
	// Debug
#ifdef serialDebugOut
    serialDebugOut.begin(115200);
    while (!serialDebugOut) {};
	serialDebugOut.println("");
#if USE_NOTECARD
    NoteSetDebugOutputStream(serialDebugOut);
#endif
#endif

	// Initialize the physical I/O channel to the Notecard
#if USE_NOTECARD
#ifdef serialNotecard
	NoteInitSerial(serialNotecard, 9600);
#else
	NoteInitI2C();
#endif
#endif

	// Initialize the Notecard so that it communicates with our account on Notehub and stays online
#if USE_NOTECARD
	J *req = NoteNewRequest("service.set");
	if (req == NULL) {
		failure = "note";
	} else {
		JAddStringToObject(req, "product", myProductID);
		JAddStringToObject(req, "mode", "continuous");
		NoteRequest(req);
	}
#endif

#if USE_GBK_ACCEL_SENSOR
    if (!accelSetup())
		failure = "accel";
#endif

#if USE_GBK_PRESSURE_SENSOR
    if (!pressureSetup())
		failure = "pressure";
#endif

#if USE_GBK_BUTTON
    if (!buttonSetup())
		failure = "button";
#endif

#if USE_GBK_BUZZER
    if (!buzzerSetup())
		failure = "buzzer";
#endif

#if USE_GBK_LED
    if (!ledSetup())
		failure = "led";
#endif

#if USE_GBK_OLED
    if (!oledSetup())
		failure = "oled";
#endif

#if USE_GBK_LIGHT_SENSOR
    if (!lightSetup())
		failure = "light";
#endif

#if USE_GBK_SOUND_SENSOR
    if (!soundSetup())
		failure = "sound";
#endif

#if USE_GBK_HUMID_SENSOR
    if (!humidSetup())
		failure = "humid";
#endif

#if USE_GBK_POTENTIOMETER
    if (!potSetup())
		failure = "pot";
#endif

	// Done
	if (failure) {
		_Print(failure);
        _Println(" failure");
		return;
	}
	
}

// Arduino loop
void loop() {

	// Init failure
	if (failure)
		return;

	// Wait to perform an action
#if USE_GBK_BUTTON
	switch (buttonState()) {
	case BUTTON_PRESS:
		actionPress();
		return;
	case BUTTON_DOUBLEPRESS:
		actionDoublePress();
		return;
	}
#else
    delay(5000);
	actionPress();
#endif

	// Things to be polled
#if USE_GBK_POTENTIOMETER
    potLoop();
#endif

}

// Actions to be taken upon a button press action
void actionPress() {

	// LED
#if USE_GBK_LED
	ledSet(true);
#endif

	// OLED
#if USE_GBK_OLED
	oledTest();
#endif
	
	// Accel
#if USE_GBK_ACCEL_SENSOR
	accelMeasure();
#endif

	// Air Pressure
#if USE_GBK_PRESSURE_SENSOR
	pressureMeasure();
#endif

	// Light Level
#if USE_GBK_LIGHT_SENSOR
	lightMeasure();
#endif

	// Sound Level
#if USE_GBK_LIGHT_SENSOR
	soundMeasure();
#endif

	// Temp/Humidity
#if USE_GBK_HUMID_SENSOR
	humidMeasure();
#endif

	// Potentiometer
#if USE_GBK_POTENTIOMETER
    potMeasure();
#endif

	// LED
#if USE_GBK_LED
	ledSet(false);
#endif
	
}

// Actions to be taken upon a button double-press action
void actionDoublePress() {
#if USE_GBK_BUZZER
	buzzerAction();
#endif
}
