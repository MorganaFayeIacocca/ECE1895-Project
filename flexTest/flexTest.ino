// these constants describe the pins. They won't change:
#include <LiquidCrystal.h>


const int flexpin = A1;    

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);
  pinMode(flexpin, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {

  // print the sensor values:

  int x = analogRead(flexpin);
  lcd.setCursor(0,0);
  lcd.print("          ");
  delay(100);
  lcd.setCursor(0,0);
  lcd.print("x = " + String(x));  
  // delay before next reading:

  delay(100);
}
