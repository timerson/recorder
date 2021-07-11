/*
  Recorder

  Turns on and off two relays based on the changing state of a switch (or multiple switches)
  These relays activate the recording and pause feature remotely with a foot activated switch(s)
  The recording relay AKA relay1 uses a 1K ohm resistor to activate recording and the rec/pause
  relay AKA relay2 uses 22K ohm resistor to pause the recording 

  The circuit:
  - Relays are attached to D4 and D5
  - Relay1 common attached to 1 Kohm resistor
  - Relay2 common attached to 22 Kohm resistor
  - Relay1 NO attached to Relay2 NO to Sleeve of plug
  - 1Kohm and 22Kohm attached to Tip of plug 
  - pushbutton attached to pin 2 and ground

  created 2021
  by Tim Peterson
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int Relay2 = 6;     
const int Relay1 = 7;
const int onTime = 50;

// variables will change:
int change = 0;
int previousButtonState = 0;
int currentButtonState = 0;         // variable for reading the pushbutton status
int timer = onTime;
bool relayActive = false;
void setup() {
  // initialize the LED pin as an output:
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);   
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  
  // read the state of the pushbutton value:
  currentButtonState = digitalRead(buttonPin);
  previousButtonState = currentButtonState;
}

void loop() {
  delay(10);
  if (!relayActive){
     // read the state of the pushbutton value:
    currentButtonState = digitalRead(buttonPin);
    // did button changed states?
    if (currentButtonState ^ previousButtonState) {
      timer = 0;
      if (currentButtonState == HIGH) {
        // turn Relay1 on
        digitalWrite(Relay1, HIGH);
        relayActive = true;
      }
      else {
        // turn   Relay2 on
        digitalWrite(Relay2, HIGH);
        relayActive = true;  
      }
    }
  previousButtonState = currentButtonState; 
  } 
  if (timer < onTime) {
    timer++; 
  }
  else {
    // turn Relay1 and Relay2 off:
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, LOW);
    relayActive = false;
  }
}
