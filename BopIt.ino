#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <LiquidCrystal.h>
//
const int Ainput = 8;   
const int Binput = 7;   

int aState = 0;
int bState = 0;
const int buttonPin = 6;     // the number of the pushbutton pin

const int xpin = A4;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis

const int vibratepin = A2;                  

const int flexpin = A1; 
const int stretchpin = A0; 

int buttonState = 0;         // variable forthat w reading the pushbutton status

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//
int level = 0;
int numCycle = 250; // Try to go from 5 sec => 0.5 sec
int cycleChange = 20;
int cycleLength = 10; //ms ?

int command = 0;

void setup () {
  Serial.begin (9600);
  mp3_set_serial (Serial); //set Serial for DFPlayer-mini mp3 module
  delay(1); // delay 1ms to set volume
  mp3_set_volume (10); // value 0~30
  
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  pinMode(flexpin, INPUT);
  
  pinMode(stretchpin, INPUT);
  
  pinMode(vibratepin, INPUT);
  
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  
}
//
void loop () {
  lcd.print("Game Begin!");
  mp3_play(106);
  delay(1500);
  lcd.clear();
  bool gameOver = false;
  int score = 0;
  int myCycle = numCycle;
  while(!gameOver){
    command = random(4); // 0 - cast it, 1 - fire it, 2 - slash it, 3 - dodge it
    sayCommand(command);
    
    lcdPrint(command);

    bool succeeded = false;
    
    // Current Values
    int currentX = analogRead(xpin);
    int currentY = analogRead(ypin);
    double currentAccel = sqrt(sq(currentX) + sq(currentY));
    int currentVibrate = digitalRead(vibratepin);
    int currentScrollState = getScrollState();
    int currentFlexState = analogRead(flexpin);
    int currentCordState = analogRead(stretchpin);

    int myCurrentCycle = myCycle;  
    while(myCurrentCycle > 0){
      
      int newX = analogRead(xpin);
      int newY = analogRead(ypin);
      
      double newAccel = sqrt(sq(currentX)+ sq(currentY));

      int newVibrate = digitalRead(vibratepin);

      int countDiff = 0;
      for (int i = 0; i < 10; i++){
        int newScrollState = getScrollState();
        if (newScrollState != currentScrollState){
          countDiff++;
        }
        delay(1);
      }
      int newFlexState = analogRead(flexpin);
      int newCordState = analogRead(stretchpin);

      // Check scroll first
      if (countDiff > 3){ //Arbitrary threshold
        if(command == 0){
          mp3_play(110);
          delay(1500);
          myCurrentCycle = 0;
          succeeded = true;
        }
        else{
          myCurrentCycle = 0;
        }
      }

      // Check cord
      if(abs(newCordState - currentFlexState) > 200){ // Another arbitrary threshold
        if(command == 2){
          mp3_play(109);
          delay(1500);
          myCurrentCycle = 0;
          succeeded = true;
        }
        else{
          myCurrentCycle = 0;
        }
      }
      
      // Check flex
      if(abs(newFlexState - currentCordState) > 200){ // Another arbitrary threshold
        if(command == 1){
          mp3_play(111);
          delay(1500);
          myCurrentCycle = 0;
          succeeded = true;
        }
        else{
          myCurrentCycle = 0;
        }
      }
      
      // Check accel
      if (newAccel > currentAccel + 1000){
        if(newVibrate != currentVibrate){
          if(command == 3){
            mp3_play(112);
            delay(1500);
            myCurrentCycle = 0;
            succeeded = true;
          }
          else{
            myCurrentCycle = 0;
          }
        }
      }
      //mp3_play(115);
      delay(cycleLength);
      myCurrentCycle--;
        
    }

    if(succeeded){
      myCycle = myCycle - cycleChange;
      score++;
    }
    else{
      gameOver = true;
    }

    if(score > 99){
      gameOver = true;
    }
  }
  
  if(score == 100){
    lcd.clear();
    lcd.print("You win!");
    mp3_play(114);
    delay(5000);
    mp3_play(107);
    delay(1200);
    sayScore(0);
    mp3_play(108);
    delay(1500);
  }
  else{
    lcd.clear();
    lcd.print("Game Over!");
    mp3_play(113);
    delay(2000);
    mp3_play(116);
    delay(1500);

    mp3_play(107);
    delay(1200);
    sayScore(100-score);
    mp3_play(108);
    delay(1500);
  }
  
}

void lcdPrint(int myCommand){
  if(myCommand == 0){
    lcd.clear();
    lcd.print("Cast It!");
    delay(1);
  }
  else if(myCommand == 1){
    lcd.clear();
    lcd.print("Fire It!");
    delay(1);
  }
  else if(myCommand == 2){
    lcd.clear();
    lcd.print("Slash It!");
    delay(1);
  }
  else if(myCommand == 3){
    lcd.clear();
    lcd.print("Dodge It!");
    delay(1);
  }
  else{
    
  }
}

void sayScore(int score){
  mp3_play(score);
  delay (1500);
}

void sayCommand(int myCommand){
  mp3_play(myCommand+102);
  delay (1500);
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
