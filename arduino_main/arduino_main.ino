/*
****************************************************
*@File: Automation Code For Esp8266
*@Assumption: INPUT>>OUTPUT
*              D4,D5,D5,D6 >>>D0,D1,D2,D3
*
*
****************************************************

*/



#define OUTPUT_RELAY1 D0
#define OUTPUT_RELAY2 D1
#define OUTPUT_RELAY3 D2
#define OUTPUT_RELAY4 D3

#define INPUT1 D4
#define INPUT2 D5
#define INPUT3 D6
#define INPUT4 D7

void setup() {
  Serial.begin(9600);
  pinMode(OUTPUT_RELAY1,HIGH);
    pinMode(OUTPUT_RELAY2,HIGH);
      pinMode(OUTPUT_RELAY3,HIGH);
        pinMode(OUTPUT_RELAY4,HIGH);
    pinMode(INPUT1,LOW);
    pinMode(INPUT2,LOW);
    pinMode(INPUT3,LOW);
    pinMode(INPUT4,LOW);      

}

void loop() {

  int M1=0,M2=0,M3=0,M4=0;
  while(Serial.available())
  {
    String Inaputdata;
    if(Serial.readStringUntil('@');//%%011000000@@
    {
      int partCounter;
       
      
      
      
      
    }
    //*****************************************************//
    if(INPUT1 == HIGH && M1 == OFF)
    {
      OUTPUT_RELAY1 = HIGH;
      Serial.print("G101");
    }
    if(INPUT2 == HIGH && M2 == ON)
    {
      OUTPUT_RELAY2 = LOW;
      Serial.print("G001");
    }
    //****************************************************//
    if(INPUT2 == HIGH && M2 == OFF)
    {
      OUTPUT_RELAY2 = HIGH;
      Serial.print("G102");
    }
    if(INPUT3 == HIGH && M3 == ON)
    {
      OUTPUT_RELAY3 = LOW;
      Serial.print("G002");
    }
    //*****************************************************//
    if(INPUT3 == HIGH && M3 == OFF)
    {
      OUTPUT_RELAY3 = HIGH;
      Serial.print("G103");
    }
    if(INPUT3 == HIGH && M3 == ON)
    {
      OUTPUT_RELAY3 = LOW;
      Serial.print("G003");
    }
    //**************************************************//
    if(INPUT4 == HIGH && M4 == OFF)
    {
      OUTPUT_RELAY4 = HIGH;
      Serial.print("G104");
    }
    if(INPUT4 == HIGH && M4 == ON)
    {
      OUTPUT_RELAY4 = LOW;
      Serial.print("G004");
    }
    
  }

}
