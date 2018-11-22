/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int D5 = 5;
int D6 = 6;
int D7 = 7;
int D8 = 8;
int D9 = 9;
int D10 = 10;
int D11 = 11;
int D12 = 12;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(D5, OUTPUT);     
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int t = 90;
  digitalWrite(D5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D5, LOW);    // turn the LED off by making the voltage LOW
  
   digitalWrite(D6, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D6, LOW);    // turn the LED off by making the voltage LOW
  
   digitalWrite(D7, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D7, LOW);    // turn the LED off by making the voltage LOW
  
   digitalWrite(D8, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D8, LOW);    // turn the LED off by making the voltage LOW
  
   digitalWrite(D9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D9, LOW);    // turn the LED off by making the voltage LOW
  
   digitalWrite(D10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D10, LOW);    // turn the LED off by making the voltage LOW
  
   digitalWrite(D11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D11, LOW);    // turn the LED off by making the voltage LOW  
  
  digitalWrite(D12, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
  digitalWrite(D12, LOW);    // turn the LED off by making the voltage LOW
}
