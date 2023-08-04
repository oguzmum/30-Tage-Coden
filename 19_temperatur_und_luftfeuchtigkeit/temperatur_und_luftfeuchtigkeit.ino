#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

const int dataPin = 12; 
const int buzzer = 10; 

DHT dht(dataPin, DHT11);

//LCD Display
/*
const int d7 = 2;
const int d6 = 3;
const int d5 = 4;
const int d4 = 5;

const int e = 6;
const int rs = 7;
*/
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

float getTemp()
{
  Serial.print("Temperatur: ");
  Serial.print(dht.readTemperature());                 
  return dht.readTemperature();
}

float getHum()
{
  Serial.print("\tLuftfeuchtigkeit: ");
  Serial.print(dht.readHumidity());
  Serial.print("\n");
  return dht.readHumidity();
}

void setDisplay(float temp, float hum)
{
  lcd.setCursor(0, 0); 
  lcd.print(temp); 
  lcd.print(" C");

  
  if(hum > 70)
  {
    digitalWrite(buzzer, HIGH);  
    lcd.setCursor(0, 1); 
    lcd.print(hum); 
    lcd.print("% - :(");   
    delay(1500); 
  }
  else
  {
    lcd.setCursor(0, 1); 
    lcd.print(hum); 
    lcd.print("% - :)");   
  }
  digitalWrite(buzzer, LOW); 
  
}


void setup() 
{
  Serial.begin( 9600);
  dht.begin(); 
  lcd.begin(16,2); 
  pinMode(buzzer, OUTPUT); 
}

void loop( )
{
  setDisplay(getTemp(), getHum());    
  delay(3000); 
}


/* erste Version ohne das LCD und mit DHT_U
 *  
 *  DHT_Unified dht( dataPin, DHT11);
 *  
 * float temp;
  float hum;
  sensors_event_t event; 
  
  dht.humidity().getEvent(&event);   
  hum = event.relative_humidity; 
  Serial.println("\nLuftfeuchtigkeit: "); 
  Serial.println(String(hum));

  dht.temperature().getEvent(&event);   
  temp = event.temperature; 
  Serial.println("\nTemperatur: "); 
  Serial.println(String(temp));

  delay(3000); 
 */
