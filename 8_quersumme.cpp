#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool containsDigits(string zahl)
{
    return std::all_of(zahl.begin(), zahl.end(), ::isdigit);
    //durch ganzes String iterieren und an jeder Stelle prüfen obs eine zahl ist
}

int querSumme(string zahl)
{
    int laenge = int(zahl.length()), quer = 0; 
    for(int i = 0; i < laenge; i++)
    {
        quer += zahl[i] - '0'; //character zu integer konvertiert man wohl mit dem - '0' 
    }
    return quer; 
}


bool isDigitFirst(string zahl);
int main()
{
    bool isZahl;
    string eingabe; 
    do
    {
        cout << "Gib eine Zahl ein: ";
        cin >> eingabe;
        isZahl = containsDigits(eingabe); 
        cout << endl << isZahl; 

        //bool first = isDigitFirst(eingabe);
    } while (!isZahl);
    
    int qs = querSumme(eingabe);
    cout << "\nDie Quersumme der Zahl: " << eingabe << " ist: " << qs << endl; 
    
    return 0; 
}


//erste Idee um zu prüfen ob string nur zahlen enthält
bool isDigitFirst(string zahl)
{
    int laenge = int(zahl.length()), isDigit = 0; 
    string allnumbers = "0123456789";
    
    for(int i = 0; i < laenge ; i++)
    {
        int isNumberCount = 0; 
        for(int x = 0; x < 10; x++)
        {   
            cout << "\nDie zahlen: " << allnumbers[x] << x << endl; 
            //prüfen ob eine der 10 zahlen vorkommt; eine Stelle in zahl (zahl[i]) kann ja nur eine der 10 sein
            // am ende dann prüfen ob isDigit anzahl mit lange des string übereinstimmt
            //  -> wenn ja, sind alle einträge eine Zahl
            if(zahl[i] == allnumbers[x])
            {
                isNumberCount += 1; 
            }   
        }
        if (isNumberCount == 1) //s. Begrüdnung oben; Eintrag des String an jeweiligem Index war eine Zahl
        {
            isDigit += 1; 
        }
    }

    if(isDigit == laenge)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}