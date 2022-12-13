// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_PRESSURE_SENSOR
#include "Seeed_BMP280.h"

// Air Pressure Sensor
BMP280 bmp280;

// Setup
bool pressureSetup() {
    return bmp280.init();
}

// Perform an accelerator sensor measurement
void pressureMeasure() {

	float temp = bmp280.getTemperature();
	float pressure = bmp280.getPressure();
	float alt = bmp280.calcAltitude(pressure);

	// Add to notecard
#if USE_NOTECARD
	J *req = notecard.newRequest("note.add");
	if (req != NULL) {
		J *body = JCreateObject();
		if (body != NULL) {
			JAddNumberToObject(body, "temp", temp);
			JAddNumberToObject(body, "pressure", pressure);
			JAddNumberToObject(body, "altitude", alt);
			JAddItemToObject(req, "body", body);
		}
		JAddStringToObject(req, "file", "pressure.qo");
		notecard.sendRequest(req);
	}
#endif

	char buf[32];
	dtostrf(temp, 0, 2, buf);
    _Print("temp:"); _Print(buf); _Print("C ");
	dtostrf(pressure, 0, 2, buf);
    _Print("press:"); _Print(buf); _Print("Pa ");
    _Print("alt:"); _Print(buf); _Print("m");
	_Println("");

}

#endif	// USE_GBK_PRESSURE_SENSOR
