#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std; 

vector<string> fieldNum = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};


/*Spielfeld soll so aussehen
    1 2 3 
    4 5 6 
    7 8 9
*/

void printField()
{
    int run = 0; 
    for (int i = 0; i < 3; i++)
    {
        for(int x = 0; x < 3; x++)
        {
            cout << fieldNum[run];
            run++;
        }   
        cout << endl; 
    }
}

bool checkInput(int wahl, vector<string> feld)
{
    if(wahl < 1 || wahl > 9)
    {
        return false; 
    }
    else if((feld[wahl-1][0]) == 'X' || (feld[wahl-1][0]) == 'O')
    {
        cout << "\nFeld bereits besetzt!";
        return false; 
    }
    else
    {
        return true; 
    }
}

void askUser(int spieler, char mark)
{
    int wahl; 
    bool correct = false; 
    do
    {
        cout << "\nSpieler " << spieler << " wo möchtest du setzen: "; 
        cin >> wahl;
        correct = checkInput(wahl, fieldNum);
    } while (!correct);
    fieldNum[wahl-1] = mark; 
}

bool checkWinner()
{
    /*
    1 2 3 
    4 5 6 
    7 8 9
    */
    // Horizontale   
    // 1 2 3 
    if(fieldNum[0] == fieldNum[1] && fieldNum[1] == fieldNum[2])
    {
        return true; 
    }
    //4 5 6 
    if(fieldNum[3] == fieldNum[4] && fieldNum[4] == fieldNum[5])
    {
        return true; 
    }
    //7 8 9 
    if(fieldNum[6] == fieldNum[7] && fieldNum[7] == fieldNum[8])
    {   
        return true; 
    }

    //Vertikale
    //1 4 7
    if(fieldNum[0] == fieldNum[3] && fieldNum[3] == fieldNum[6])
    {   
        return true; 
    }
    //2 5 8 
    if(fieldNum[1] == fieldNum[4] && fieldNum[4] == fieldNum[7])
    {   
        return true; 
    }
    //3 6 9
    if(fieldNum[2] == fieldNum[5] && fieldNum[5] == fieldNum[8])
    {   
        return true; 
    }

    //Diagonale
    //1 5 9 
    if(fieldNum[0] == fieldNum[4] && fieldNum[4] == fieldNum[8])
    {
        return true; 
    }
    //3 5 7
    if(fieldNum[2] == fieldNum[4] && fieldNum[4] == fieldNum[6])
    {   
        return true; 
    }

    return false; 
}

bool checkIfPlayable()
{
    int counter = 0; 
    for(const string& num : fieldNum)
    {
        if(!isdigit(num[0]))
        {
            counter++;
        }
    }
    if (counter == 8)
    {
        return false;
    }
    else
    {
        return true; 
    }
}

int main()
{
    printField();
    int spieler, runde = 0;
    char marker; 
    bool winner = false, playable = true; 

    do 
    {
        bool playable = checkIfPlayable(); 
        if(playable == false)
        {
            cout << "\nKein Spielzug mehr machbar!" << endl; 
            winner = false; 
            break;
        }

        spieler = (runde%2 ==0) ? 1 : 2; //jede runde spieler wechseln
        cout << "Spieler " << spieler << " du bist dran!"; 
        marker = (spieler == 1) ? 'X' : 'O'; //entsprechend markierung wechseln
        cout << " Dein Markierungzeichen: " << marker << endl; 

        askUser(spieler, marker); 
        winner = checkWinner(); 

        printField();
        runde++; 
    } while(!winner);

    if(winner == false)
    {
        cout << "\nUnentschieden";
    }
    else if(spieler == 1)
    {
        cout << "\nSpieler 1 hat gewonnen! Markierung: " << marker;
    }
    else if(spieler == 2)
    {
        cout << "\nSpieler 2 hat gewonnen! Markierung: " << marker;
    }
}