const int buttonPin = 2; // Pin of interupt device.
const int ledPin = 12; // led pin for non-timer interrupts
int ledState = 0;


void setup() {
  Serial.begin(9600);
  
  // led output pin init.
  pinMode(ledPin, OUTPUT); // Output led (not onboard)
  // First button pin init (pin 2)
  pinMode(buttonPin, INPUT);  
}

void loop() {
  ledState = digitalRead(buttonPin); //Sense
  Serial.print(String(ledState)+"\n"); // Some Thought
  digitalWrite(ledPin,ledState); //Act
}
