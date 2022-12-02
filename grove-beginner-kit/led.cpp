// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_LED

// Setup
bool ledSetup() {
    pinMode(GBK_LED_PIN, OUTPUT);
	return true;
}

// Perform the requested action
void ledSet(bool on) {
	digitalWrite(GBK_LED_PIN, on ? HIGH : LOW);
}

#endif	// USE_GBK_LED

