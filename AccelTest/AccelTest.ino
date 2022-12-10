// these constants describe the pins. They won't change:
#include <LiquidCrystal.h>


const int xpin = A4;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);
  pinMode(xpin, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {

  // print the sensor values:

  /*int x = analogRead(xpin);
  lcd.setCursor(0,0);
  lcd.print("          ");
  delay(20);
  lcd.setCursor(0,0);
  lcd.print("x = " + String(x));  
  // delay before next reading:*/
  int sensorState = digitalRead(xpin);
  lcd.clear();
  if(sensorState == 1){
    lcd.print("Vibration");
  }
  else{
    lcd.print("None");
  }

  delay(50);
}
