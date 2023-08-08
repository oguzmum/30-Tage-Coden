#include "LedControl.h" //für LED matrix
#include "Keypad.h" // für folientastaturmodul
/*
 * Anschluss: 
 * DIn 12
 * CS 11
 * CLK 10
 */
LedControl lc = LedControl(12,10,11,1);


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


char field[9];
void setField()
{
  for(int i = 0; i < 9; i++)
  {
    char mm = (i + '0')+1; 
    field[i] = mm; 
  }
}

void setup() 
{
  Serial.begin(9600);
  //hochfahren
  lc.shutdown(0,false);
  //die helligkeit anpassen
  lc.setIntensity(0,2);
  lc.clearDisplay(0);
}


void loop() 
{
  int runde = 0, spieler;   
  bool winner = false; 
  char marker; 
  
  lc.clearDisplay(0);
  setField(); 

  do
  {
    spieler = (runde%2 == 0) ? 1 : 2; 
    
    marker = (spieler == 1) ? 'X' : 'O'; 
    
    printInfo(spieler, runde, marker);
    getUserInput(marker); 
    
    winner = checkWinner(); //nur txt gerade
    showTxtField(); 
    runde += 1; 
    
    if(runde == 9 && !winner)
    {
      Serial.print("\nUnentschieden"); 
      sadFace();
      break; 
    }
  } while(!winner);

  if(winner)
  {
    Serial.print("\nGewonnen hat der Spieler ");   
    Serial.print(spieler);   
    Serial.print(" Mit der Markierung: ");
    Serial.print(marker);   
    fancyWinAnimation(spieler); 
  }
    
  delay(5000); 
}


//Hilfsfunktionen
void getUserInput(char mark)
{
  //hier immer linke obere ecke mitgeben an setTheLed - zb '1' -> (0, 7), zB '8' -> (3, 1)
  
  int indizes[9][2] = {{0, 7}, {3, 7}, {6, 7}, 
                       {0, 4}, {3, 4}, {6, 4},
                       {0, 1}, {3, 1}, {6, 1},
                      };

  bool correct = false; 
  int converted;
  do
  {
    char input = tastatur.getKey();
    if (input)
    {
      Serial.print("\nEs wurde eingelesen: ");
      Serial.print(input);
      converted = (input - '0') - 1;
      correct = checkInput(converted);
    }
   
  } while(!correct);
  
  field[converted] = mark; 
  
  setTheLed(indizes[converted][0], indizes[converted][1], mark); 
  //statt mit if abfragen; char in int umwandeln; die linken oberen ecken in einem array speichern und input entsprechend als  index betrachten
}

bool checkInput(int choice)
{
  //für TxtField
  if((field[choice] == 'X')||(field[choice] == 'O'))
  { 
    return false;
  }
  return true;
}

void setTheLed(int row, int col, char mark)
{
  //von der linken oberen ecke ausgehend jeweils die LED's anleuchten
  if(mark == 'X')
  {
    //das für das X symbol (also diagonale)
    lc.setLed(0, row, col-1, HIGH);
    lc.setLed(0, row+1, col, HIGH);  
  }
  if(mark == 'O')
  {
    //das für das O symbol (also viereck)
    lc.setLed(0, row, col, HIGH);
    lc.setLed(0, row+1, col, HIGH);
    lc.setLed(0, row, col-1, HIGH);
    lc.setLed(0, row+1, col-1, HIGH);
  }
}

void printInfo(int spieler, int runde, char mark)
{
  Serial.print("\nSpieler "); 
  Serial.print(spieler); 
  Serial.print(" du bist dran! Deine Markierung ist: "); 
  Serial.print(mark); 
  Serial.print("\nAktuelle Runde: "); 
  Serial.print(runde); 
}

bool checkWinner()
{
    // Horizontale   
    // 1 2 3 
    if(field[0] == field[1] && field[1] == field[2])
    {
        return true; 
    }
    //4 5 6 
    if(field[3] == field[4] && field[4] == field[5])
    {
        return true; 
    }
    //7 8 9 
    if(field[6] == field[7] && field[7] == field[8])
    {   
        return true; 
    }

    //Vertikale
    //1 4 7
    if(field[0] == field[3] && field[3] == field[6])
    {   
        return true; 
    }
    //2 5 8 
    if(field[1] == field[4] && field[4] == field[7])
    {   
        return true; 
    }
    //3 6 9
    if(field[2] == field[5] && field[5] == field[8])
    {   
        return true; 
    }

    //Diagonale
    //1 5 9 
    if(field[0] == field[4] && field[4] == field[8])
    {
        return true; 
    }
    //3 5 7
    if(field[2] == field[4] && field[4] == field[6])
    {   
        return true; 
    }

    return false; 
}


void showTxtField()
{
  Serial.println("\nDas Feld: \n");
  for(int i = 0; i < 9; i++)
  {
    Serial.print(field[i]);
    if(i == 2 || i == 5)
    {
      Serial.println("\n");
    }
  }
  Serial.println("\n");
}

void fancyWinAnimation(int spieler)
{
  lc.clearDisplay(0); 
  unsigned long startTime = millis();
  if(spieler == 1)
  {
     
     while (millis() - startTime < 5000) 
     {
        for (int i = 0; i < 8; i++) 
        {
          lc.setLed(0, i, i, HIGH); 
        }
        delay(500);
        
        for (int i = 0; i < 8; i++) 
        {
          lc.setLed(0, i, i, LOW);   
        }
        delay(500);
      }
   }

   if(spieler == 2)
   {
      while (millis() - startTime < 5000) 
      {
        lc.setLed(0, 3, 4, HIGH);  
        lc.setLed(0, 4, 3, HIGH);  
        lc.setLed(0, 4, 4, HIGH);  
        lc.setLed(0, 3, 3, HIGH);  
        
        delay(500);
        
        lc.setLed(0, 3, 4, LOW);   
        lc.setLed(0, 4, 3, LOW);   
        lc.setLed(0, 4, 4, LOW);  
        lc.setLed(0, 3, 3, LOW);  
        
        delay(500);
      }
    }
}
void sadFace()
{
  byte sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};
  for(int i = 0 ; i < 8; i++)
  {
    lc.setColumn(0,i,sad[i]);
  }
}

/*
mache das doch nicht, weil dann zu wenig platz für die markierungen
void spielFeldMarkierung()
{
  lc.setColumn(0,2,0xFF);
  lc.setColumn(0,5,0xFF);
  lc.setRow(0,2,0xFF);
  lc.setRow(0,5,0xFF);
}
*/
