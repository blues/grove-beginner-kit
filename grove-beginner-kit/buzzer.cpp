// Copyright 2020 Blues Inc.  All rights reserved.
// Use of this source code is governed by licenses granted by the
// copyright holder including that found in the LICENSE file.
//
// Portions 2005 D. Cuartielles
// http://www.arduino.cc/en/Tutorial/Melody

#include "global.h"
#if USE_GBK_BUZZER

// If short tune, only play this many notes
#define SHORT_TUNE	7

// Tune to play, where a space represents a rest
char tune[] = "ccggaagffeeddc ";
uint8_t beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
#define tempo 300

// Setup
bool buzzerSetup() {
    pinMode(GBK_BUZZER_PIN, OUTPUT);
	return true;
}

// Play a tone of a specific frequency and duration
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(GBK_BUZZER_PIN, HIGH);
        delayMicroseconds(tone);
        digitalWrite(GBK_BUZZER_PIN, LOW);
        delayMicroseconds(tone);
    }
}

// Play a specific note
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
    for (unsigned i = 0; i < sizeof(names); i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}

// Perform the requested action
void buzzerAction() {
	int notes = strlen(tune);
#ifdef SHORT_TUNE
	notes = SHORT_TUNE;
#endif
    for (int i = 0; i < notes; i++) {
        if (tune[i] == ' ')
            delay(beats[i] * tempo); // rest
        else
            playNote(tune[i], beats[i] * tempo);
        delay(tempo / 2);
    }
}

#endif	// USE_GBK_BUZZER

