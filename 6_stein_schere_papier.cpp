#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::time;
using std::srand;
using std::string;

void getWinner(string fromUser, string fromBot, int ergebnis[])
{
    //fälle wo der nutzer gewinnt
    string cases[3][2] = {
                    {"stein", "schere"}, 
                    {"papier", "stein"}, 
                    {"schere", "papier"}
                    }; 
    bool userWon = false, equal = false; 

    if(fromUser.compare(fromBot) == 0)
    {
        cout << "\nUnentschieden!" << endl;
        equal = true; 
        ergebnis[0] += 1; 
    }

    for(int i = 0; i <= 3; i++)
    {
        if(fromUser.compare(cases[i][0]) == 0 && fromBot.compare(cases[i][1]) == 0)
        {
            cout << cases[i][0] << " schlägt " << cases[i][1] << "\nDu hast gewonnen!!!!!!!!\n\n";
            userWon = true;
            ergebnis[1] += 1; 
        }
    }

    if(userWon == false && equal == false)
    {
        cout << fromBot << " schlägt " << fromUser << "\nDer Bot hat gewonnen\n\n"; 
        ergebnis[2] += 1; 
    }
        
}
int main()
{
    string eingabe;
    int choice, count = 0;  
    static int ergebnisse[] = {0, 0, 0}; 
    //                      unentschieden, nutzer siege, bot siege
    do
    {
        if(count != 0)
        {
            cout << "\nWillst du weiter spielen?\n0:Nein\n1:Ja\n "; 
            cin >> choice; 
            if(choice == 0)
                break;
        }
        count += 1;

        do
        {
            cout << "\nWas möchtest du spielen: "; 
            cin >> eingabe;
            eingabe = string(eingabe); 
            
            if(eingabe.compare("stein") != 0 && eingabe.compare("schere") != 0 && eingabe.compare("papier") != 0)
            {
                cout << "\nDu kannst nur stein, schere oder papier eingeben \nBitte nochmal \n";
                continue; 
            }
            else
            {
                break;
            }
            
        }while(true);
        
        string liste[] = {"stein", "schere", "papier"};    
        srand(time(0));
        int zufallszahl = rand() % 3; 
        cout << "Der Bot hat: " << liste[zufallszahl] << "\n"; 

        getWinner(eingabe, liste[zufallszahl], ergebnisse);
    }while(true);

    cout << "\nDu hast " << count << " Runden gespielt.";
    cout << "\nDavon\nUnentschieden: " << ergebnisse[0] <<"\nNutzer Siege: " << ergebnisse[1] <<"\nBot Siege: " << ergebnisse[2]; 
}