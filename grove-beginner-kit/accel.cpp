// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_ACCEL_SENSOR
#include <LIS3DHTR.h>

// Accelerometer
LIS3DHTR<TwoWire> LIS;

// Setup
bool accelSetup() {
    LIS.begin(Wire, GBK_ACCEL_I2C_ADDRESS);
    if (!LIS)
		return false;
    delay(100);
    LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
	return true;
}

// Perform an accelerator sensor measurement
void accelMeasure() {

	float x = LIS.getAccelerationX();
	float y = LIS.getAccelerationY();
	float z = LIS.getAccelerationZ();

#if USE_NOTECARD
	J *req = NoteNewRequest("note.add");
	if (req != NULL) {
		J *body = JCreateObject();
		if (body != NULL) {
			JAddNumberToObject(body, "x", x);
			JAddNumberToObject(body, "y", y);
			JAddNumberToObject(body, "z", z);
			JAddItemToObject(req, "body", body);
		}
		JAddStringToObject(req, "file", "accel.qo");
		NoteRequest(req);
	}
#endif

	char buf[32];
	dtostrf(x, 0, 2, buf);
    _Print("x:"); _Print(buf); _Print(" ");
	dtostrf(y, 0, 2, buf);
	 _Print("y:"); _Print(buf);	_Print(" ");
	dtostrf(z, 0, 2, buf);
    _Print("z:"); _Print(buf);	_Print(" ");
	_Println("");

}


#endif	// USE_GBK_ACCEL_SENSOR
