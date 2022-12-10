#include <LiquidCrystal.h>

const int Ainput = 8;   
const int Binput = 7;   

int aState = 0;
int bState = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin (9600);
  pinMode(Ainput, INPUT);
  pinMode(Binput, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int s = getScrollState();
  lcd.print(String(s));
  delay (1000);
}

int getScrollState(){
  aState = digitalRead(Ainput);
  bState = digitalRead(Binput);
  if(bState == HIGH){
    if(aState == HIGH){
      return 0;
    }
    else{
      return 1;
    }
  }
  else{
    return 2;
  }
}
