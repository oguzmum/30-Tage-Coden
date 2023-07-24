#include <iostream>
#include <string>
#include <vector>
#include <utility>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;

string marker = "x", empty = " "; 
int zeilen = 10, spalten = 10; 

vector<vector<string> > createField()
{
    vector<vector<string> > theField(zeilen, vector<string>(spalten, empty));
    //feld erstellen, als Array, zu beginn gefüllt mit leerzeichen (empty = " ")

    for(int i = 0; i < zeilen; i++)
    {
        for(int x = 0; x < spalten; x++)
        {
            //obere und untere "Zeilenkante"
            if(i == 1 || i == zeilen - 2)
            {
                theField[i][x] = marker; 
            }
            else
            {
                theField[i][x] = empty; 
            }

            //linke und rechte "Spaltenkante"
            if(x == 1 || x == spalten - 2)
            {
                theField[i][x] = marker; 
            }
        }
    }

    return theField; 
}

void printField(vector<vector<string> > field)
{
    for (int i = 0; i < zeilen; i++)
    {
        for (int x = 0; x < spalten; x++)
        {
            cout << field[i][x];
        }
        cout << endl;
    }
    cout << endl; 
}

bool checkIfFull(vector<vector<string> > field)
{
    for (int i = 2; i < zeilen-2; i++) //von 3ten zeile bis vorvorletze zeile
    {
        for (int x = 2; x < spalten-2; x++) //von 3 spalte bis vorvorletze spalte
        {
            if(field[i][x] == marker)
            {
                return false;
            }
        }
    }
    return true; 
}

vector<vector<string> > floodFill(vector<vector<string> > field)
{
    bool full;
    vector<pair <int, int> > lastPosition;
    lastPosition.push_back(make_pair(zeilen-3, spalten-3));
    //mit startkoordinaten beginnen - unten rechts in der ecke; 
    //die Koordinaten werden nach jedem Durchlauf überschrieben
    int nachbarn[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; 

    do
    {
        vector<pair <int, int> > newFill; //jedes mal mit leeren liste an neuen koordinaten speichern
        
        full = checkIfFull(field);
        if(!full)
        {
            cout << "\nFlood Fill erfolgreich :)\n"; 
            break; 
        }
        

        for(int x = 0; x < int(lastPosition.size()); x++)
        {
            
            for(int i = 0; i < 4; i++) // bei nachbarn alle 4 durchiterieren
            {   
                //mit ersten Elementen neue X Koordinate berechnen
                int newX = lastPosition[x].first + nachbarn[i][0];

                // zweite Elemente aus den Listen
                int newY = lastPosition[x].second + nachbarn[i][1];

                //prüfen ob man sich noch innerhalb der feldes befindent
                if(newX < 0 || newX >= zeilen-1 || newY < 0 || newY >= spalten-1)
                {
                    continue; 
                }

                //wenn die Stelle noch leerzeichen hat, Stelle füllen
                if(field[newX][newY] == empty)
                {
                    field[newX][newY] = marker; 
                    newFill.push_back(make_pair(newX, newY)); //koordinaten speichern
                }
            }
            lastPosition = newFill; //zuletzt gefüllte koordinaten übergeben
            printField(field); 
        }
        
    }while(true);
    return field; 
}


int main()
{
    vector<vector<string> > field = createField(); 
    printField(field); 
    
    field = floodFill(field); 

    return 0;
}

