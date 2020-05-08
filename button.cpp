// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_BUTTON

// Setup
bool buttonSetup() {
	pinMode(GBK_BUTTON_PIN, GBK_PRESSED_STATE == LOW ? INPUT_PULLUP : INPUT);
	return true;
}

// Button handling
int buttonState() {

	// Detect the "press" transition
	static bool buttonBeingDebounced = false;
	int buttonState = digitalRead(GBK_BUTTON_PIN);
	if (buttonState != GBK_PRESSED_STATE) {
		if (buttonBeingDebounced) {
			buttonBeingDebounced = false;
		}
		return BUTTON_IDLE;
	}
	if (buttonBeingDebounced)
		return BUTTON_IDLE;

	// Wait to see if this is a double-press
	bool buttonDoublePress = false;
	bool buttonReleased = false;
	unsigned long buttonPressedMs = millis();
	unsigned long ignoreBounceMs = 200;
	unsigned long doublePressMs = 750;
	while (millis() < buttonPressedMs+doublePressMs || digitalRead(GBK_BUTTON_PIN) == GBK_PRESSED_STATE) {
		if (millis() < buttonPressedMs+ignoreBounceMs)
			continue;
		if (digitalRead(GBK_BUTTON_PIN) != GBK_PRESSED_STATE) {
			if (!buttonReleased)
				buttonReleased = true;
			continue;
		}
		if (buttonReleased) {
			buttonDoublePress = true;
			if (digitalRead(GBK_BUTTON_PIN) != GBK_PRESSED_STATE)
				break;
		}
	}

	return (buttonDoublePress ? BUTTON_DOUBLEPRESS : BUTTON_PRESS);

}

#endif	// USE_GBK_BUTTON

