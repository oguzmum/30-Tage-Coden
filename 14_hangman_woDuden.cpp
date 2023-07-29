//das ohne Einbindung der duden.txt Datei, weil das bei VSCode iwie nicht funktioniert

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std; 

bool checkAlpha(string word)
{
    return std::all_of(word.begin(), word.end(), ::isalpha);
}

string randomWord()
{
    string words[] = {"apfel", "banane", "schnecke", "ampel", "schule", "schreibtisch", "computer", "hexadezimal", "zylinder"}; 
    srand(time(0));
    
    string randomW = words[ rand()% sizeof(words)/sizeof(words[0]) ];

    return randomW;
}

string askForLetter(vector<string> guessed)
{   
    string guessedChar, eingabe;
    bool valid = false;

    do 
    {
        cout << "\nRate einen Buchstaben: "; 
        cin >> eingabe;

        if(!checkAlpha(eingabe))
        {
            cout << "Du darfst nur Buchstaben eingeben!!!";
            continue;
        }

        bool guessedAlready = false;
        for(int i = 0; i < int(guessed.size()); i++)
        {
            if(eingabe == guessed[i])
            {
                cout << "Den Buchstaben hast du schonmal versucht";
                guessedAlready = true;
                break;
            }
        }

        if(eingabe.size() > 1)
        {
            cout << "\nDu darfst nur einen Buchstaben eingeben!";
        }


        if(eingabe.size() == 1 && checkAlpha(eingabe) && !guessedAlready)
        {
            valid = true;
        }

    } while(!valid);

    return eingabe;
}

vector<int> checkLetter(string word, vector<string> guessed)
{
    vector<int> indexe; //um die gefundenen Indexe zurückzugeben
    bool correct = false; 

    for(int i = 0; i < int(word.size()); i++)
    {
        //immer den zuletzt eingegebenen Buchstaben prüfen
        
        if(guessed.back()[0] == word[i])
        {
            indexe.push_back(i); 
            correct = true; 
        }
        
    }

    if(correct == false)
    {
        cout << "\nDein eingegebener Buchstabe " << guessed[guessed.size()-1] << " ist nicht im Wort enthalten"; 
    }   
    else
    {
        cout << "\nDein eingegebener Buchstabe " << guessed[guessed.size()-1] << " ist im Wort enthalten"; 
    }

    return indexe;
}

bool checkWin(vector<int> theIndexe, string rW, string wordButHidden)
{
    //prüfen obe rnutzer gewonnen hat und aktuellen status anzeigen
    for(int i = 0; i < int(theIndexe.size()); i++)
    {
        wordButHidden[theIndexe[i]] = rW[theIndexe[i]]; 
    }
    cout << endl << wordButHidden << endl; 

    for(int i = 0; i < int(wordButHidden.size()); i++)
    {
        if(wordButHidden[i] == '_')
        {

            return false;  
        }
    }
    cout << "\nHerzlichen Glückwunsch, du hast das Wort erraten\n"; 
    return true; 
}

int main()
{
    string rW = randomWord(), wordButHidden; 

    for(int i = 0; i < int(rW.size()); i++)
    {
        wordButHidden += '_';
    }
    vector<string> guessedChar; //buchstaben die der Nutzer bisher geraten hat hier speichern
    vector<int> theIndexe; //indexe der buchstaben die richtig geraten worden sind

    bool foundWord = false; 
    unsigned int rounds = 0, max = 12; 

    while(foundWord == false)
    {
        rounds += 1; 
        cout << "\naktuelle Runde: " << rounds << ". Du hast noch: " << max - rounds << " Runden!!";
        if(rounds > max)
        {
            cout << "\nDu hast zu viele Versuche gebraucht :(";
            break; 
        }

        vector<int> newIndexe;
        string newGuessed;
       
        newGuessed = askForLetter(guessedChar);
        guessedChar.push_back(newGuessed);

        newIndexe = checkLetter(rW, guessedChar); 
        theIndexe.insert(theIndexe.end(), newIndexe.begin(), newIndexe.end()); 

        foundWord = checkWin(theIndexe, rW, wordButHidden);
    }


    cout << "\nDas Wort ist: " << rW; 
    
    return 0; 
}