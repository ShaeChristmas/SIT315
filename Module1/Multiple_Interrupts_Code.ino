const int interuptPin = 2; // Pin of interupt device.
const int ledPin = 12; // led pin for non-timer interrupts
const int motion = 3;

volatile int interuptState = 0; // current state of the interupt.

void setup() {
  Serial.begin(9600);
  
  // led output pin init.
  pinMode(ledPin, OUTPUT); // Output led (not onboard)
  // Set motion sensor pin to 3
  pinMode(motion, INPUT);
  // First button pin init (pin 2)
  pinMode(interuptPin, INPUT);
  
  // Attaching interupt to the Button and motion Sensors.
  attachInterrupt(digitalPinToInterrupt(interuptPin), switchLed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motion), motionLed, CHANGE);
}

void loop() {
  // We are running outside the execution loop, so no code is needed here
}

// Function to change the led output (first button).
void switchLed() {
  Serial.print("First Button toggle\n");
  interuptState = digitalRead(interuptPin);
  
  digitalWrite(ledPin, interuptState);
}

// Function to change the led output (Motion Sensor)
void motionLed() {
  Serial.print("Motion toggle\n");
  interuptState = digitalRead(motion);
  
  digitalWrite(ledPin, interuptState);
}
