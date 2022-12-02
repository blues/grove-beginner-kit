// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_POTENTIOMETER

// Setup
bool potSetup() {
	pinMode(LED_BUILTIN, OUTPUT);
    pinMode(GBK_POTENTIOMETER_PIN, INPUT);
	return true;
}

// Convert pot reading to percentage, where left is 0 and right is 100
float potPosition() {
	unsigned position = analogRead(GBK_POTENTIOMETER_PIN);
	if (position > 1024)
		position = 1024;
	return  ((float) (1024-position)) / 1024;
}

// Give feedback as to pot level
void potLoop() {

	// Implement a PWM indicator on the built-in LED
	static unsigned long cycleBeganMs = 0;
	unsigned long pwmIntervalMs = 100;
	unsigned long onMs = (unsigned long) (((float) pwmIntervalMs) * potPosition());
	unsigned long nowMs = millis();
	if (nowMs >= (cycleBeganMs + pwmIntervalMs)) {
		cycleBeganMs = nowMs;
		digitalWrite(LED_BUILTIN, HIGH);
	}
	if (nowMs >= (cycleBeganMs + onMs)) {
		digitalWrite(LED_BUILTIN, LOW);
	}

}

// Measure
void potMeasure() {

	// Average the sensed value
	float value = potPosition();

	// Add to notecard
#if USE_NOTECARD
	J *req = NoteNewRequest("note.add");
	if (req != NULL) {
		J *body = JCreateObject();
		if (body != NULL) {
			JAddNumberToObject(body, "position", value);
			JAddItemToObject(req, "body", body);
		}
		JAddStringToObject(req, "file", "potentiometer.qo");
		NoteRequest(req);
	}
#endif

	// Done
	char buf[32];
	dtostrf(value, 0, 2, buf);
	_Print("pot:");
	_Println(buf);

}

#endif	// USE_GBK_LED

