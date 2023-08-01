#include "BuchVerwaltung.h"
#include "Buch.h"
#include <iostream>

using namespace std; 
BuchVerwaltung bv; 

void bookInput()
{   
    //anordnung int txt datei: titel, autor, datum, gelesen?, bewertung, Id
    string titel, autor; 
    unsigned int datum, bewertung, gelesen;  

    cout <<"\nTitel: "; 
    cin >> titel; 
    fflush(stdin); 

    cout <<"\nAutor: "; 
    cin >> autor;
    fflush(stdin); 

    cout <<"\nErscheinungsdatum: "; 
    cin >> datum;
    fflush(stdin); 

    cout <<"\nSchon gelesen? (0)Nein (1)Ja: "; 
    cin >> gelesen;
    fflush(stdin); 

    cout << "\nBewertung (0 - 10): "; 
    cin >> bewertung; 
    fflush(stdin); 

    cout << "\naktulle Id: " << bv.getBookCount()+1;
    bv.writeFromUserInput(titel, autor, datum, gelesen, bewertung, bv.getBookCount()+1); 
}   

bool getIfAlpha(string& str)
{
    for(char c : str)
    {
        if(!isalpha(c))
        {
            return false; 
        }
    }
    return true; 
}

Buch search()
{
    Buch foundBook; 
    unsigned int theId; 
    string input; 
    cout << "\nWelches Buch willst du anpassen: "; 
    bv.showAllBooks(); 

    cout << "\nGib hier Titel oder Id nummer ein: "; 
    cin >> input; 
    
    if(getIfAlpha(input))
    {
        return bv.getBook_wTitle(input); 
    }
    else
    {
        return bv.getBook_wId(stoi(input)); 
    }
}


void werten(Buch buch)
{
    unsigned int wertung; 
    cout << "\nVon 0-10 welche Wertung würdest du geben: ";
    cin >> wertung; 
    buch.setBewertung(wertung); 
}

void askUser()
{
    Buch buch;
    char choice; 
    do
    {
        cout << "\nOptionen:\n(s) Buch eingeben und speichern\n(v) Alle Bücher aus/in der Datenbank anzeigen"; 
        cout << "\n(g) Ein Buch als gelesen markieren\n(b) Ein Buch bewerten\n(u) Ein Buch suchen";
        cout << "\nWas willst du machen: "; 
        cin >> choice; 
    } while (!isalpha(choice));
    
    switch(choice)
    {
        case 's': 
            fflush(stdin); 
            bookInput(); 
            break; 
        case 'v':
            bv.showAllBooks(); 
            break; 
        case 'g': 
            buch = search();
            buch.setGelesen(true); 
            cout << "\nDas Buch: " << buch.getTitel() << " wurde auf gelesen gesetzt!!"; 
            bv.printBook(&buch); 
            break; 
        case 'b': 
            buch = search(); 
            werten(buch); 
            bv.printBook(&buch); 
            break; 
        case 'u': 
            buch = bv.searchByTitle();
            bv.printBook(&buch); 
            break; 
        default: 
            cout << "\nEtwas ist schief gelaufen"; 
    }
}

int main()
{   
    //ToDo: muss noch testen ob er wenn zB letzten 2 elemte nicht einegegben sind; 
    //ob er dann autor.. von ächsten eintrag in txt datei für die atribute nimmt
    /*
        nach eingabe, v drücken - wird iwie nicht ausgegeben
        beweertung als float 
        ausgabenformatierung "schöner"
        Id's besser verwalten
    */
    bv.readDatabase(); //um schonmal bookCount undso rauszukriegen
    
    unsigned int choice; 
    bool weiter;
    do
    {
        askUser(); 
        cout << "\nProgramm schließen (0) Nein; (1) Ja: "; 
        cin >> choice;
        weiter = (choice == 0) ? false : true;  
    } while (!weiter);
    
    // //hier noch Nutzerabfrage

	// Buch b1("h", "t", 15, false, 1);
    // Buch b2("f", "g", 20, true, 10);
    // BuchVerwaltung bv; 
    // //b1.setTitel("HAllo"); 

    // //cout << b1.getTitel() << " " << b1.getAutor() << " " << b1.getDatum(); 
	
    // // bv.writeBook(&b1); 
    // // bv.writeBook(&b2); 
    // bv.readDatabase();
    // bv.showAllBooks(); 
	// //system("PAUSE");
	return 0;
}