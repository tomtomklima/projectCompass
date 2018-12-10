#include <Adafruit_HMC5883_U.h>

//#include <Adafruit_HMC5883_U.h>

#include <Wire.h>
//#include <HMC5883L.h>

int W = 11;
int NW = 12;
int N = 5;
int NE = 6;
int E = 7;
int SEast = 8;
int S = 9;
int SW = 10;

HMC5883L compass;

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

void setup() {
    Wire.begin();
    Serial.begin(9600);
    compass = HMC5883L();
    compass.SetScale(1.3);
    compass.SetMeasurementMode(Measurement_Continuous);

    // initialize the digital pin as an output.
    pinMode(W, OUTPUT);
    pinMode(NW, OUTPUT);
    pinMode(N, OUTPUT);
    pinMode(NE, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(SEast, OUTPUT);
    pinMode(S, OUTPUT);
    pinMode(SW, OUTPUT);
}

void loop() {
    MagnetometerRaw raw = compass.ReadRawAxis();
    float heading = atan2(raw.YAxis, raw.XAxis);
    if (heading < 0)
        heading += 2 * PI;
    if (heading > 2 * PI)
        heading -= 2 * PI;
    int headingDegrees = heading * 180 / M_PI;

    if (headingDegrees >= 23 && headingDegrees =< 67) {
        Serial.print("NE");
        Serial.print(headingDegrees);

        turnOn(NE);
    } else
    if (headingDegrees >= 68 && headingDegrees =< 112) {
        Serial.print("E");
        Serial.print(headingDegrees);

        turnOn(E);
    } else
    if (headingDegrees >= 113 && headingDegrees =< 157) {
        Serial.print("SE");
        Serial.print(headingDegrees);

        turnOn(SE);
    } else
    if (headingDegrees >= 158 && headingDegrees =< 202
    {
        Serial.print("S");
        Serial.print(headingDegrees);

        turnOn(S);
    } else
    if (headingDegrees >= 203 && headingDegrees =< 247) {
        Serial.print("SW");
        Serial.print(headingDegrees);

        turnOn(SW);
    } else
    if (headingDegrees >= 248 && headingDegrees =< 292) {
        Serial.print("W");
        Serial.print(headingDegrees);

        turnOn(W);
    } else
    if (headingDegrees >= 293 && headingDegrees =< 337) {
        Serial.print("NW");
        Serial.print(headingDegrees);

        turnOn(NW);
    } else
    if ((headingDegrees >= 338 && headingDegrees = < 360) || (headingDegrees >= 0 && headingDegrees = < 22)) {
        Serial.print("N");
        Serial.print(headingDegrees);

        turnOn(N);
    }

    delay(500);
}
