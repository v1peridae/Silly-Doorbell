#include "pitch.h"
#include "song.h"

#define BUTTON_PIN 2
#define SPEAKER_PIN 8

/* set up function */
void setup() {
  // put your setup code here, to run once:

  // enable input/output pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
}

/* main while loop function */
void loop() {
  // check to see if button is pressed
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // delay 50 ms to make sure it's still pressed
    // avoids any stray misreadings
    delay(50);
    if(digitalRead(BUTTON_PIN) == HIGH) {
      // play the Mii song
      play_song(miiLength, mii, miiDurations, miiTempo);
    }
  }
}

/* plays the song */
void play_song(int num_notes, int melody[], int noteDurations[], int tempo) {
  // step through and play all of the notes
  for (int i = 0; i < num_notes; i++) {
    int duration = 0;
    // calculate the duration of each note
    if (noteDurations[i] > 0) {
      duration = tempo / noteDurations[i];
    }
    // if it's a negative number, means dotted note
    // increases the duration by half for dotted notes
    else if (noteDurations[i] < 0) {
      duration = tempo / abs(noteDurations[i]) * 1.5;
    }
    tone(SPEAKER_PIN, melody[i], duration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }
}
