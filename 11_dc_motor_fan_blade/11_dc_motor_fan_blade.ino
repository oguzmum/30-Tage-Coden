
const int ENABLE = 5;
const int DIRA = 3;
const int DIRB = 4;

const int btn_for_normal = 10; //normal, in einer Richtung
const int btn_for_alt = 12; //alle paar sek. richtung ändern

void setup() 
{
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  pinMode(btn_for_normal,INPUT);
  pinMode(btn_for_alt,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  //für diesen Fall den Button gedrück halten
  if(digitalRead(btn_for_normal) == 1)
  {
    Serial.println("'normale' Fan Blade aktiviert");
    analogWrite(ENABLE,255); //schnellste einstellung
    digitalWrite(DIRA,HIGH); 
    digitalWrite(DIRB,LOW);
  }
  //bei diesem Fall reicht einmal drücken, außer man will es ganze zeit - dann gedrückt halten
  else if(digitalRead(btn_for_alt) == 1)
  {
    Serial.println("'alternierende' Fan Blade aktiviert");
    digitalWrite(ENABLE,HIGH);
    
    digitalWrite(DIRA,HIGH); // 2 sek in eine Richtung Uhrzeigersinn
    digitalWrite(DIRB,LOW);
    delay(2000);

    digitalWrite(DIRA,LOW); //kurz beides pausieren, damit man richtungswechsel besser erkennt
    digitalWrite(DIRB,LOW);
    delay(1000); 
    
    digitalWrite(DIRA,LOW);  //dann 2 sek in andere
    digitalWrite(DIRB,HIGH);
    delay(2000);
  }
  else
  {
    Serial.println("Fan Blade nicht aktiviert");
    analogWrite(ENABLE,LOW); 
    digitalWrite(DIRA,LOW); 
    digitalWrite(DIRB,LOW);
  }  
}
   
