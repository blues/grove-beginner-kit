// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_LIGHT_SENSOR

// Setup
bool lightSetup() {
	return true;
}

// Measure
void lightMeasure() {

	// Average the sensed value
	float lightLevel = 0;
	int averagedValues = 10;
	for (int i=0; i<averagedValues; i++) {
		lightLevel += analogRead(GBK_LIGHT_SENSOR_PIN);
		delay(25);
	}
	lightLevel /= averagedValues;

	// Convert it to a percentage
	if (lightLevel > 750)
		lightLevel = 750;
	lightLevel = lightLevel/750;

	// Add to notecard

#if USE_NOTECARD
	J *req = notecard.newRequest("note.add");
	if (req != NULL) {
		J *body = JCreateObject();
		if (body != NULL) {
			JAddNumberToObject(body, "level", lightLevel);
			JAddItemToObject(req, "body", body);
		}
		JAddStringToObject(req, "file", "light.qo");
		notecard.sendRequest(req);
	}
#endif

	// Done
	char buf[32];
	dtostrf(lightLevel, 0, 2, buf);
	_Print("light:");
	_Println(buf);

}

#endif	// USE_GBK_LIGHT_SENSOR

