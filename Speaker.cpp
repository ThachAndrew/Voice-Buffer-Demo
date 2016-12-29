#include <Arduino.h>
#include "Speaker.h"

void Speaker::playScale() {
  const int SPEAKER_PIN = 3;
  String scale = "cdefgabagfedc";
  for (int i = 0; i < scale.length(); i++) {
    tone(SPEAKER_PIN, getNote(scale[i]));
    delay(200);
  }
  noTone(SPEAKER_PIN);
  
}
/*
void Speaker::playDScale(){
  
}

*/

int Speaker::getNote(char note) {
  //Uppercase letters represent sharps
  switch (note) {
    case 'c': return 261; break;
    case 'C': return 277; break;
    case 'd': return 294; break;
    case 'D': return 311; break;
    case 'e': return 330; break;
    case 'f': return 349; break;
    case 'F': return 370; break;
    case 'g': return 392; break;
    case 'G': return 415; break;
    case 'a': return 440; break;
    case 'A': return 466; break;
    case 'b': return 494; break;

    default: return -1; break;
  }

}
