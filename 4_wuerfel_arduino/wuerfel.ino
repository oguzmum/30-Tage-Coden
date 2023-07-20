/* Beschaltung des 7 Segment Displays
 *  Eingänge  a  b  c  d  e  f  g  dp
 *  Zahl 1:   0  1  1  0  0  0  0  0    
 *  Zahl 2:   1  1  0  1  1  0  1  0
 *  Zahl 3:   1  1  1  1  0  0  1  0
 *  Zahl 4:   0  1  1  0  0  1  1  0 
 *  Zahl 5:   1  0  1  1  0  1  1  0 
 *  Zahl 6:   1  0  1  1  1  1  1  0     
 */

//Pins am Arduino für die Ausgabe bzw Eingabe am 7 Segment Display
byte pin[] = {2, 3, 4, 5, 6, 7, 8, 9}; 
//            a  b  c  d  e  f  g  dp

int zahl [6][8] = {
                    {0, 1, 1, 0, 0, 0, 0, 0}, //1
                    {1, 1, 0, 1, 1, 0, 1, 0}, //2
                    {1, 1, 1, 1, 0, 0, 1, 0}, //3
                    {0, 1, 1, 0, 0, 1, 1, 0}, //4
                    {1, 0, 1, 1, 0, 1, 1, 0}, //5
                    {1, 0, 1, 1, 1, 1, 1, 0}, //6
                  };

const int button = 13; //am Pin 13 switch taster einlesen

int wuerfel(); 
void setDisplay(int number); 

void setup() 
{
  randomSeed(analogRead(A0));
  
  for(byte i = 0; i < 9; i++)
  {
    pinMode(pin[i], OUTPUT);
  }
  
  pinMode(button, INPUT);
  Serial.begin(9600); 
}

void loop() 
{
  if(digitalRead(button) == HIGH)
  {
    int ergebnis = wuerfel();
    Serial.println(ergebnis);
    setDisplay(ergebnis);
    delay(3000);
  }
  else
  {
    for(int i = 0; i < 9; i++)
    { 
      digitalWrite(pin[i], LOW); 
    }  
  }
}


int wuerfel()
{
  int zufallszahl = random(6) + 1;
  return zufallszahl;
}

void setDisplay(int number)
{
  for(int i = 0; i < 9; i++)
  { 
    digitalWrite(pin[i], zahl[number-1][i]); 
  }
  /* statt LOW, HIGH kann man auch 1 und 0 nutzen (die stehen in der Liste zahl
   * mit i iteriere ich zum eine durch die Pins für das 7 Segment display, 
   * und durch die einzelnen Werte der Zahl dür das 7 Segment Display
   */
}
