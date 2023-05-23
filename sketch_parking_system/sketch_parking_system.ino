// Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;

// LED
const int redLED = 7;
const int greenLED = 6;

// Buzzer
const int buzzerPin = 8;

// DISTANCE THRESHOLD
int distanceThreshold = 10;

// define functions
void turnOnLED(int led);
void turnOffLED(int led);
void printDistance(int distance);
void soundBuzzer(bool state);

// defines variables
long duration;
int distance;

bool isParked = false;
bool beeped = false;

void setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  // LED Setup
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, LOW);
  digitalWrite(redLED, LOW);

  // Buzzer Setup
  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin, 1000, 2000);

  Serial.begin(9600);  // Starts the serial communication
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

  printDistance(distance);

  if (distance <= distanceThreshold) {
    isParked = true;
  } else {
    isParked = false;
  }

  if (isParked && !beeped) {
    turnOffLED(greenLED);
    turnOnLED(redLED);
    soundBuzzer(isParked);
    beeped = true;
  } else if (!isParked) {
    turnOffLED(redLED);
    turnOnLED(greenLED);
    beeped = false;
  }

  delay(500);
}

// turn On LED
void turnOnLED(int led) {
  digitalWrite(led, HIGH);
}

// turns Off LED
void turnOffLED(int led) {
  digitalWrite(led, LOW);
}

// Prints the distance on the Serial Monitor
void printDistance(int distance) {
  Serial.print("Distance: ");
  Serial.println(distance);
}

// Plays a buzzer tone
void soundBuzzer(bool state) {
  if (state) {
    tone(buzzerPin, 784);  // A4
    delay(2000);
    tone(buzzerPin, 784);  // A4
    // delay(2000);
    noTone(buzzerPin);
  }
}