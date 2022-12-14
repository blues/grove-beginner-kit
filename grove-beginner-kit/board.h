// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.

#pragma once

// Grove Beginner's Kit definitions
#define	USE_DEBUG					true
#define	USE_NOTECARD				true	// Install https://github.com/blues/note-arduino
#define USE_GBK_BUTTON				true
#define USE_GBK_BUZZER				true
#define USE_GBK_POTENTIOMETER		true
#define USE_GBK_LED					true
#define USE_GBK_LIGHT_SENSOR		true
#define USE_GBK_SOUND_SENSOR		true
#define USE_GBK_ACCEL_SENSOR		true	// Install https://github.com/Seeed-Studio/Seeed_Arduino_LIS3DHTR
#define USE_GBK_HUMID_SENSOR		true	// Install "Grove Temperature and Humidity Sensor library by Seeed Studio"
#define USE_GBK_PRESSURE_SENSOR		true	// install "Grove - Barometer Sensor BMP280 library"
#define USE_GBK_OLED				false	// Install "U8g2 by oliver" (leaves very little memory on Lotus))

// Notecard
#if USE_NOTECARD
#define	USE_NOTECARD_SERIAL			true
#define	USE_NOTECARD_TRACE			false
#endif

// Button
#if USE_GBK_BUTTON
#define	GBK_BUTTON_PIN					6
#define	GBK_PRESSED_STATE				HIGH
#endif

// Buzzer
#if USE_GBK_BUZZER
#define	GBK_BUZZER_PIN					5
#endif

// Accelerometer
#if USE_GBK_ACCEL_SENSOR
#define	GBK_ACCEL_I2C_ADDRESS			0x19
#endif

// LED
#if USE_GBK_LED
#define	GBK_LED_PIN						4
#endif

// Light sensor
#if USE_GBK_LIGHT_SENSOR
#define	GBK_LIGHT_SENSOR_PIN			A6
#endif

// Sound sensor
#if USE_GBK_SOUND_SENSOR
#define	GBK_SOUND_SENSOR_PIN			A2
#endif

// Potentiometer
#if USE_GBK_POTENTIOMETER
#define	GBK_POTENTIOMETER_PIN			A0
#endif

// Humidity Sensor
#if USE_GBK_HUMID_SENSOR
#define	GBK_HUMID_SENSOR_PIN			3
#define	GBK_HUMID_SENSOR_TYPE			DHT11
#endif

// Debug output
#if USE_DEBUG
#define serialDebugOut Serial
#endif

// Note that both of these definitions are optional; just prefix either line with // to remove it.
//  Remove serialNotecard if you wired your Notecard using I2C SDA/SCL pins instead of serial RX/TX
//  Remove serialDebug if you don't want the Notecard library to output debug information

#if USE_NOTECARD && USE_NOTECARD_SERIAL
#undef serialDebugOut
#define serialNotecard Serial
#endif

// This is the unique Product Identifier for your device.  This Product ID tells the Notecard what
// type of device has embedded the Notecard, and by extension which vendor or customer is in charge
// of "managing" it.  In order to set this value, you must first register with notehub.io and
// "claim" a unique product ID for your device.  It could be something as simple as as your email
// address in reverse, such as "com.gmail.smith.lisa.test-device" or "com.outlook.gates.bill.demo"

#ifndef PRODUCT_UID
#define PRODUCT_UID ""		// "com.my-company.my-name:my-project"
#pragma message "PRODUCT_UID is not defined in this example. Please ensure your Notecard has a product identifier set before running this example or define it in code here. More details at https://bit.ly/product-uid"
#endif
