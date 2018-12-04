#include <Wire.h> //I2C Arduino Library

#define addr 0x1E //I2C Address for The HMC5883


int xmax, ymax, zmax;
int xmin, ymin, zmin;

int z0 = -550;
  
void setup(){
  
  Serial.begin(9600);
  Wire.begin();
  
  
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x02); // Set the Register
  Wire.write(0x00); // Tell the HMC5883 to Continuously Measure
  Wire.endTransmission();

   //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x03); //start with register 3.
  Wire.endTransmission();
  
 
 //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if(6<=Wire.available()){
    xmax = Wire.read()<<8; //MSB  x 
    xmax |= Wire.read(); //LSB  x
    zmax = Wire.read()<<8; //MSB  z
    zmax |= Wire.read(); //LSB z
    ymax = Wire.read()<<8; //MSB y
    ymax |= Wire.read(); //LSB y
  }
  xmin = xmax;
  ymin = ymax;
  zmin = zmax;
}




void loop(){
  
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
  z = z - z0;

  Serial.print("X: ");
  Serial.print(x);
  Serial.print("  Y: ");
  Serial.print(y);
  Serial.print("  Z: ");
  Serial.println(z);
  
  
  
  if (x > xmax) xmax = x;
  if (x < xmin) xmin = x;
  if (y > ymax) ymax = y;
  if (y < ymin) ymin = y;
  if (z > zmax) zmax = z;
  if (z < zmin) zmin = z;
  
  // Show Values
  Serial.print("X min: ");
  Serial.print(xmin);
  Serial.print("  X max: ");
  Serial.println(xmax);
  Serial.print("Y min: ");
  Serial.print(ymin);
  Serial.print("  Y max: ");
  Serial.println(ymax);
  Serial.print("Z min: ");
  Serial.print(zmin);
  Serial.print("  Z max: ");
  Serial.println(zmax);

  Serial.println();

}
