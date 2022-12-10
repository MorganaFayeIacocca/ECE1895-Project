#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
//

const int buttonPin = 8;     // the number of the pushbutton pin

int buttonState = 0;         // variable forthat w reading the pushbutton status

void setup () {
 Serial.begin (9600);
 mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module
 delay(1); // delay 1ms to set volume
 mp3_set_volume (10); // value 0~30
}
//
void loop () {
  buttonState = digitalRead(buttonPin);

  if(buttonState == LOW) {
    mp3_play (1);
    delay (1000);
    mp3_play (2);
    delay (1000);
    mp3_play (3);
    delay (1000);
    mp3_play (4);
    delay (1000);
    mp3_play (5);
    delay (1000);
  }
}
