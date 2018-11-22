#include <Wire.h> //I2C Arduino Library

#define addr 0x1E //I2C Address for The HMC5883

int WL = 11;
int WR = 12;
int NL = 5;
int NR = 6;
int EL = 7;
int ER = 8;
int SL = 9;
int SR = 10;
bool firstIteration = true;

void setup(){
    
    // initialize the digital pin as an output.
  pinMode(NL, OUTPUT);     
  pinMode(NR, OUTPUT);
  pinMode(EL, OUTPUT);
  pinMode(ER, OUTPUT);
  pinMode(SL, OUTPUT);
  pinMode(SR, OUTPUT);
  pinMode(WL, OUTPUT);
  pinMode(WR, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();
  
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
  }


void loop(){
//  if(firstIteration){
//    for(int i=0; i<10; i++){
//    digitalWrite(NL, HIGH);
//    digitalWrite(NR, HIGH);
//    digitalWrite(EL, HIGH);
//    digitalWrite(ER, HIGH);
//    digitalWrite(SL, HIGH);
//    digitalWrite(SR, HIGH);
//    digitalWrite(WL, HIGH);
//    digitalWrite(WR, HIGH);
//  
//    delay(100);
//      
//    digitalWrite(NL, LOW);
//    digitalWrite(NR, LOW);
//    digitalWrite(EL, LOW);
//    digitalWrite(ER, LOW);
//    digitalWrite(SL, LOW);
//    digitalWrite(SR, LOW);
//    digitalWrite(WL, LOW);
//    digitalWrite(WR, LOW);
//  
//    delay(100);
//    }
//    firstIteration = false;
//  }
  
  int x,y,z; //triple axis data

  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
 
 //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //MSB  x 
    x |= Wire.read(); //LSB  x
    z = Wire.read()<<8; //MSB  z
    z |= Wire.read(); //LSB z
    y = Wire.read()<<8; //MSB y
    y |= Wire.read(); //LSB y
  }
  
//  // Show Values
//Serial.print("X Value: ");
//Serial.println(x);
//Serial.print("Y Value: ");
Serial.println(y);
//Serial.print("Z Value: ");
//Serial.println(z);
//Serial.println();



if( x > 90){ // x->N
  digitalWrite(NL, HIGH);
  digitalWrite(NR, HIGH);

  digitalWrite(EL, LOW);
  digitalWrite(ER, LOW);
  digitalWrite(SL, LOW);
  digitalWrite(SR, LOW);
  digitalWrite(WL, LOW);
  digitalWrite(WR, LOW);
}
else if(x < -100){ // x->S -> "virtual south" = north
   digitalWrite(SL, HIGH);
  digitalWrite(SR, HIGH);

  digitalWrite(EL, LOW);
  digitalWrite(ER, LOW);
  digitalWrite(NL, LOW);
  digitalWrite(NR, LOW);
  digitalWrite(WL, LOW);
  digitalWrite(WR, LOW);
}
else if(y < -500){// x->W -> "virtual east" = north
   digitalWrite(EL, HIGH);
  digitalWrite(ER, HIGH);

  digitalWrite(WL, LOW);
  digitalWrite(WR, LOW);
  digitalWrite(SL, LOW);
  digitalWrite(SR, LOW);
  digitalWrite(NL, LOW);
  digitalWrite(NR, LOW);
}
else{ // x->E -> "virtual west" = north
    digitalWrite(WL, HIGH);
  digitalWrite(WR, HIGH);

  digitalWrite(NL, LOW);
  digitalWrite(NR, LOW);
  digitalWrite(SL, LOW);
  digitalWrite(SR, LOW);
  digitalWrite(EL, LOW);
  digitalWrite(ER, LOW);
}

 
  
//  delay(500);
}
