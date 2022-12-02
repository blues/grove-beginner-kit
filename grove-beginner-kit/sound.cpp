// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_SOUND_SENSOR

// Setup
bool soundSetup() {
	return true;
}

// Measure
void soundMeasure() {

	// Average the sensed value
	float soundLevel = 0;
	int averagedValues = 100;
	for (int i=0; i<averagedValues; i++) {
		soundLevel += analogRead(GBK_SOUND_SENSOR_PIN);
		delay(25);
	}
	unsigned observed = (unsigned) (soundLevel / averagedValues);

	// Convert it to a percentage of that maximum
	unsigned minimumObserved = 250;
	unsigned maximumObserved = 625;
	if (observed < minimumObserved)
		observed = minimumObserved;
	if (observed > maximumObserved)
		observed = maximumObserved;
	observed -= minimumObserved;
	unsigned range = maximumObserved - minimumObserved;
	float pct = (float) observed / (range/2);

	// Add to notecard
#if USE_NOTECARD
	J *req = NoteNewRequest("note.add");
	if (req != NULL) {
		J *body = JCreateObject();
		if (body != NULL) {
			JAddNumberToObject(body, "level", pct);
			JAddItemToObject(req, "body", body);
		}
		JAddStringToObject(req, "file", "sound.qo");
		NoteRequest(req);
	}
#endif

	// Done
	char buf[32];
	dtostrf(pct, 0, 2, buf);
	_Print("sound:");
	_Println(buf);

}

#endif	// USE_GBK_SOUND_SENSOR

