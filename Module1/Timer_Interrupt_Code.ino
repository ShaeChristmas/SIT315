const int interuptPin = 2; // Pin of interupt device.
const int ledPin = 12; // led pin for non-timer interrupts
const int ledPinTime = 13; // 13 is the default led.
const int motion = 3;

volatile int interuptState = 0; // current state of the interupt.

void setup() {
  Serial.begin(9600);
  
  //Clear registers
  noInterrupts(); // Stop Interrupts
  
  TCCR1A = 0; //set TCCR1A reg to 0
  TCCR1B = 0; // set TCCR1B reg to 0
  TCNT1 = 0; // init counter val to 0
  
  OCR1A = 46874; //16000000 / 1024 * (1/3) - 1; Changes once every 3 seconds
  TCCR1B |= (1 << WGM12); // turn on CTC mode (allows changes to resolution of timer)
  TCCR1B |= (1 << CS12) | (0  << CS11) | (1 << CS10); // set listed bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // enables the timer interrupt
  interrupts();
  
  PCICR |= 0b00000100; // Turning on PCMSK2
  
  PCMSK2 |= 0b00110000; // Turning on d4 and d5
  
  pinMode(4, INPUT_PULLUP); // Setting Pin 4 to pullup input. Used for the last Button.
  
  
  // led output pin init.
  pinMode(ledPin, OUTPUT); // Output led (not onboard)
  pinMode(ledPinTime, OUTPUT); // Default led used for timer (onboard)
  // Set motion sensor pin to 3
  pinMode(motion, INPUT);
  // First button pin init (pin 2)
  pinMode(interuptPin, INPUT);
  
  // Attaching interupt to the Button and motion Sensors.
  attachInterrupt(digitalPinToInterrupt(interuptPin), switchLed, CHANGE);
  attachInterrupt(digitalPinToInterrupt(motion), motionLed, CHANGE);
  
}

// Interrupt function for last Button.
ISR (PCINT2_vect) {
  Serial.print("Last Button toggle\n");
  interuptState = digitalRead(4);
  
  digitalWrite(ledPin, interuptState);
}

// Timer Interrupt Function
ISR(TIMER1_COMPA_vect) {
  Serial.print("Timer toggle\n");
  digitalWrite(ledPinTime, digitalRead(ledPinTime) ^ 1); 
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
