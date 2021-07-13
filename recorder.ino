/*
  Recorder

  Turns on and off two relays based on the changing state of a switch (or multiple switches)
  These relays activate the recording and pause feature remotely with a foot activated switch(s)
  The recording relay AKA Relay4 uses a 1K ohm resistor to activate recording and the rec/pause
  relay AKA Relay3 uses 22K ohm resistor to pause the recording 

  Tip of plug               Sleeve of plug
  ^                         ^
  |                         |                
  |                         |
  |                /        |
  |     22Kohm    /         |
  +----/\/\/\----/    ------+
  |               ###       |
  |      D6*<-----###       |
  |               ###       |
  |     gnd*<-----###       |
  |               ###       |
  |             Relay 3     |
  |                         |
  |                         |
  |                /        |
  |     1Kohm     /         |
  +----/\/\/\----/    ------+
                  ###
         D7*<-----###  
                  ###  
        gnd*<-----###
                  ###  
                Relay 4

               /
              /
gnd*<--------/    ------> D2*

*pin of arduino

                               
  The circuit:
  - Relays are attached to D6 and D7
  - Relay4 common attached to 1 Kohm resistor
  - Relay3 common attached to 22 Kohm resistor
  - Relay4 NO attached to Relay3 NO to Sleeve of plug
  - 1Kohm and 22Kohm attached to Tip of plug 
  - pushbutton attached to pin 2 and ground

  Components
  - Arduino uno  https://www.arduino.cc/en/Main/arduinoBoardUno&gt;
  - Relay shield https://wiki.seeedstudio.com/Relay_Shield_v3/
  - 22Kohm resistor
  - 1Kohm resistor

  created 2021
  by Tim Peterson
*/

// constants
const int buttonPin = 2;     // the number of the pushbutton pin
const int Relay3 = 6;     
const int Relay4 = 7;
const int onTime = 50;

// variables
int change = 0;
int previousButtonState = 0;  // previous pushbutton status
int currentButtonState = 0;   // variable for reading the pushbutton status
int timer = onTime;           // timer for activating the rlays
bool relayActive = false;     // relay activation status

void setup() {
  // initialize the LED pin as an output:
  pinMode(Relay4, OUTPUT);
  pinMode(Relay3, OUTPUT);   
  digitalWrite(Relay4, LOW);
  digitalWrite(Relay3, LOW);
  
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
        // turn Relay4 on
        digitalWrite(Relay4, HIGH);
        relayActive = true;
      }
      else {
        // turn   Relay3 on
        digitalWrite(Relay3, HIGH);
        relayActive = true;  
      }
    }
  previousButtonState = currentButtonState; 
  } 
  if (timer < onTime) {
    timer++; 
  }
  else {
    // turn Relay4 and Relay3 off:
    digitalWrite(Relay4, LOW);
    digitalWrite(Relay3, LOW);
    relayActive = false;
  }
}
