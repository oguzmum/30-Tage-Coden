#include <SevSeg.h>

SevSeg sevseg;

const int startPin = A5; //muss man gedrückt halten :)

unsigned long startTime = 0;
unsigned long elapsedTime = 0;

void setup() 
{
  //aus der Dokumentation von github, brightness und hardwareconfig geändert
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5}; //d1 d2 d3 d4
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; //a b c d e f g dp
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = NP_COMMON_ANODE; // musste das auch 
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  sevseg.setBrightness(90);
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  
  pinMode(startPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  //mit Button
  if (digitalRead(startPin) == HIGH) 
  {
    elapsedTime = millis() - startTime;
    
    //sevseg.setNumber(elapsedTime/100);  
    //sevseg.refreshDisplay();
  
    Serial.print("Zeit: ");
    Serial.println(formatTime(elapsedTime));

    static unsigned long timer = millis();
    static int deciSeconds = 0;
    if (millis() - timer >= 100) 
    {
      timer += 100;
      deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
  
      if (deciSeconds == 10000) 
      { // Reset to 0 after counting for 1000 seconds.
        deciSeconds=0;
      }
      sevseg.setNumber(deciSeconds, 1);
    }
    delay(25); 
    sevseg.refreshDisplay();
      
  }
  
  if (digitalRead(startPin) == LOW) 
  {
      startTime = millis(); 
      elapsedTime = 0;      
      sevseg.setNumber(0);
      sevseg.refreshDisplay();
      Serial.println("Timer ist off");
      delay(200);           
  }


  //ohne ein Button
  /*
  static unsigned long timer = millis();
  static int deciSeconds = 0;

  if (millis() - timer >= 100) 
  {
    timer += 100;
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond

    if (deciSeconds == 10000) 
    { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 1);
  }

  sevseg.refreshDisplay(); 
  */
}

String formatTime(unsigned long milliseconds) 
{
  unsigned long seconds = milliseconds / 1000;
  unsigned long minutes = seconds / 60;
  seconds = seconds % 60;
  milliseconds = (milliseconds % 1000) / 10;  
  
  return String(minutes) + ":" + (seconds < 10 ? "0" : "") + String(seconds) + "." + (milliseconds < 10 ? "0" : "") + String(milliseconds);
}
