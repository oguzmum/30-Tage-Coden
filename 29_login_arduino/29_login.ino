 #include "Keypad.h"

const byte ROWS = 3; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
                            {'1','2','3'},
                            {'4','5','6'},
                            {'7','8','9'},
                          }; 
byte rowPins[ROWS] = {9, 8, 7}; //Pins wie ich sie am arduino angeschlossen habe
byte colPins[COLS] = {5, 4, 3}; 

Keypad tastatur = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


char password[] = "1234";

unsigned int ledPin = 3;
void setup
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}


void loop
{
    char key = tastatur.getKey(); 
  
    if (key) 
    {
        Serial.println(key); 
    
        static int keyIndex = 0; 
        if (key == password[keyIndex]) 
        {
            keyIndex++; 
            
            if (keyIndex == sizeof(password) - 1) 
            {
                digitalWrite(ledPin, HIGH); 
                delay(3000); 
                digitalWrite(ledPin, LOW); 
                keyIndex = 0; 
            }
        } 
        else 
        {
            //bei falschem zeichen, eingabe zurücksetzen
            keyIndex = 0; 
        }
    }
}