#include<Arduino.h>

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int led = 12;
// defines variables
long duration;
int distance;
int threshold = 0; // set threshold.

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(led, OUTPUT);
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // if the distance measured is greater than or equal to the threshold set then we turn on the LED for 5 seconds
  if(distance >= threshold)
  {
    digitalWrite(led, HIGH);
    delay(5000);
    digitalWrite(led, LOW);
  }
}