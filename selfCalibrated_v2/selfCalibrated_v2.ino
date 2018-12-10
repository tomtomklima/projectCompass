#include <Wire.h> //I2C Arduino Library

#define addr 0x1E //I2C Address for The HMC5883


// TODO redo calibration, especially for z
//int xmax = 331;
//int xmin = -124;
//int ymax = 40;
//int ymin = -479;
int zmin_acceptable_upper = 520;
int zmax_acceptable_upper = 590;
int zmax_acceptable_lower = 60;
int zmin_acceptable_lower = -40;
int xmax = 575;
int xmin = -454;
int ymax = 290;
int ymin = -783;
int zmax = 722;
int zmin = -242;
int xrange;
int yrange;
int zrange;


int W = 11;
int NW = 12;
int N = 5;
int NE = 6;
int E = 7;
int SEast = 8;
int S = 9;
int SW = 10;

void turnOn(int port) {
    digitalWrite(W, LOW);
    digitalWrite(NW, LOW);
    digitalWrite(N, LOW);
    digitalWrite(NE, LOW);
    digitalWrite(E, LOW);
    digitalWrite(SEast, LOW);
    digitalWrite(S, LOW);
    digitalWrite(SW, LOW);

    digitalWrite(port, HIGH);
}


void setup(){
  
  Serial.begin(9600);
  Wire.begin();
  
    // initialize the digital pin as an output.
  pinMode(W, OUTPUT);
  pinMode(NW, OUTPUT);
  pinMode(N, OUTPUT);
  pinMode(NE, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(SEast, OUTPUT);
  pinMode(S, OUTPUT);
  pinMode(SW, OUTPUT);
    
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();
  
  xrange = (double)xmax-(double)xmin;
  yrange = (double)xmax-(double)xmin;
  zrange = (double)zmax-(double)zmin;
}


void loop(){
  
  int x,y,z; //triple axis data
  double xnorm, ynorm, znorm;
  
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

    // normalize: center the data
    xnorm = ((double)x-((double)xmin)-xrange/2)/xrange; 
    ynorm = ((double)y-((double)ymin)-xrange/2)/yrange;
    znorm = ((double)z-((double)zmin)-xrange)/zrange;
    double TSS = sqrt(xnorm*xnorm+ynorm*ynorm+znorm*znorm);
    xnorm = xnorm/TSS;
    ynorm = ynorm/TSS;
    znorm = znorm/TSS;
//    if (ynorm > 1) ynorm = 1;
//    if (ynorm < 0) ynorm = 0;
  }

  // skip this iteration if too much tilted
  if ( (z > zmin_acceptable_lower && z < zmax_acceptable_lower)  || (z > zmin_acceptable_upper && z < zmax_acceptable_upper) ){
      // Show Values
  Serial.print("X Value: ");
  Serial.println(xnorm);
  Serial.print("Y Value: ");
  Serial.println(ynorm);
  Serial.print("Z Value: ");
  Serial.println(znorm);
  Serial.println();

  double heading = atan2(ynorm,xnorm) *180/M_PI; // TODO this does not really work
  while(heading < 0){
    heading += 360;
  }
  while(heading >= 360){
    heading -= 360;
  }
  Serial.print("heading: ");
  Serial.println(heading);

     if (heading >= 23 && heading <= 67) {
      Serial.print("NE ");
      Serial.println(heading);

      turnOn(NE);
  } else
  if (heading >= 68 && heading <= 112) {
      Serial.print("E ");
      Serial.println(heading);

      turnOn(E);
  } else
  if (heading >= 113 && heading <= 157) {
      Serial.print("SE ");
      Serial.println(heading);

      turnOn(SEast);
  } else
  if (heading >= 158 && heading <= 202)
  {
      Serial.print("S ");
      Serial.println(heading);

      turnOn(S);
  } else
  if (heading >= 203 && heading <= 247) {
      Serial.print("SW ");
      Serial.println(heading);

      turnOn(SW);
  } else
  if (heading >= 248 && heading <= 292) {
      Serial.print("W ");
      Serial.println(heading);

      turnOn(W);
  } else
  if (heading >= 293 && heading <= 337) {
      Serial.print("NW ");
      Serial.println(heading);

      turnOn(NW);
  } else
  if ((heading >= 338 && heading <= 360) || (heading >= 0 && heading <= 22)) {
      Serial.print("N ");
      Serial.println(heading);

      turnOn(N);
  }

  delay(500);
  }
  else{
    // TODO maybe switch off all motors/LEDs
    Serial.print("Z = ");
    Serial.print(z);
    Serial.println(" - ignore value");
  }


 }
