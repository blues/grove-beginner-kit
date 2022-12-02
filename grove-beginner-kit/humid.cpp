// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_HUMID_SENSOR
#include "DHT.h"

// Air Pressure Sensor
DHT dht(GBK_HUMID_SENSOR_PIN, GBK_HUMID_SENSOR_TYPE);

// Setup
bool humidSetup() {
	dht.begin();
	return true;
}

// Perform an accelerator sensor measurement
void humidMeasure() {

	float temp = dht.readTemperature();
	float humid = dht.readHumidity();

#if USE_NOTECARD
	J *req = NoteNewRequest("note.add");
	if (req != NULL) {
		J *body = JCreateObject();
		if (body != NULL) {
			JAddNumberToObject(body, "temp", temp);
			JAddNumberToObject(body, "humid", humid);
			JAddItemToObject(req, "body", body);
		}
		JAddStringToObject(req, "file", "humid.qo");
		NoteRequest(req);
	}
#endif

	char buf[32];
	dtostrf(temp, 0, 2, buf);
    _Print("temp:"); _Print(buf); _Print("C ");
	dtostrf(humid, 0, 2, buf);
    _Print("humid:"); _Print(buf); _Print("%");
	_Println("");

}

#endif	// USE_GBK_HUMID_SENSOR
