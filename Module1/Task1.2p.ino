const int interuptPin = 2; // Pin of interupt device.
const int ledPin = 12; // led pin for non-timer interrupts

volatile int interuptState = 0; // current state of the interupt.

void setup() {
  Serial.begin(9600);
  
  // led output pin init.
  pinMode(ledPin, OUTPUT); // Output led (not onboard)
  // First button pin init (pin 2)
  pinMode(interuptPin, INPUT);
  
  // Attaching interupt to the Button and motion Sensors.
  attachInterrupt(digitalPinToInterrupt(interuptPin), switchLed, CHANGE);
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
