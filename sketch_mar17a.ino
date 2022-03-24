#define redLED 8
#define pointLED 9
int temp = LOW;

void setup() {
  pinMode(redLED, OUTPUT);    // sets the digital pin 14 as output
  pinMode(pointLED, INPUT);     //sets the digital pin 15 as input
}

void loop() {
  temp = digitalRead(pointLED);
  if(temp == HIGH)
  { 
    digitalWrite(redLED, HIGH); // sets the digital pin 14 on
    delay(65);            // waits for a second
    digitalWrite(redLED, LOW);  // sets the digital pin 14 off
    delay(65;  
                // waits for a second
  }
  else ( temp == LOW);
  {
    digitalWrite(redLED, LOW);
  }
  temp = digitalRead(pointLED);
}
