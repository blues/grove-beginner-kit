// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#include "global.h"
#if USE_GBK_OLED
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Initial rotation, and no reset pin, using the "1" buffer size option to keep memory usage low
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE);

// Setup
bool oledSetup() {
	u8g2.begin();
	return true;
}

// Write a test string to the display
void oledTest() {

	char buf[32];
	dtostrf(millis(), 0, 0, buf);

	u8g2.firstPage();
	do {
		u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
		u8g2.drawStr(0,10,buf);				// write something to the internal memory
	} while (u8g2.nextPage());

}

#endif	// USE_GBK_OLED
