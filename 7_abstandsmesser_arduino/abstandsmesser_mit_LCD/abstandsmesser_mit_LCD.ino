#include <LiquidCrystal.h>

/* Im Datenblatt
 *      pin
 * d7   12
 * d6   11
 * d5   10
 * d4   9
 * 
 * e    8
 * rs   7
 * 
 * LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
 */

/* meine Belegung für die Pins
const int d7 = 2;
const int d6 = 3;
const int d5 = 4;
const int d4 = 5;

const int e = 6;
const int rs = 7;
*/


//für abstandssensor
const int echo = 8; 
const int trig = 9; 

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


void setup() 
{
  lcd.begin(16,2); 

  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT); 
  
  Serial.begin(9600);
}

long getDistance();

void loop() 
{
  long dist = getDistance();
  lcd.setCursor(0,0);
  lcd.print(dist);
  lcd.print(" cm");
  lcd.setCursor(0,1);
  lcd.print("Abonniert");
}

long getDistance()
{
  long entfernung = 0, dauer = 0; 
  
  digitalWrite(trig, LOW); //trigger pin erst clearen
  delay(5);
  
  digitalWrite(trig, HIGH); //10 ms trigger setzen
  delay(10);
  digitalWrite(trig, LOW);
  
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer * 0.03432)/2;
  //0.03432 ist schallgeschwindigkeit; dauer ist zeit die echo hin un zurück braucht
  //brauchen die hälfte davon weil wir nur die zeit bis zum objekt brauchen
  
  
  if (entfernung >= 500 || entfernung <= 0)
  {
    Serial.println("Kein Messwert");
  }
  else
  {
    Serial.print(entfernung);
    Serial.println(" cm");

    return entfernung; 
  }
}
