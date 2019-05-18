
/*
After uploading program observe the NodeMCU board. 
Blue LED blinking is our main task running. 
Open Serial Monitor and Press Flash Button,
as soon as you press the button it will print the Interrupt Detected. 
Without disturbing main task of LED Blinking.

*/
const int interruptPin = 0; //GPIO 0 (Flash Button) 
const int LED = 16; //On board blue LED 

void setup() { 
  Serial.begin(9600); 
  pinMode(LED,OUTPUT); 
  pinMode(interruptPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, CHANGE); 
} 

void loop() 
{ 
    digitalWrite(LED,HIGH); //LED off 
    delay(1000); 
    digitalWrite(LED,LOW); //LED on 
    delay(1000); 
} 

//This program get executed when interrupt is occures i.e.change of input state
void handleInterrupt() { 
    Serial.println("Interrupt Detected"); 
}
