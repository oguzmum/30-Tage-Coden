#include "FilmVerwaltung.h"
#include "Film.h"
#include <iostream>

using namespace std; 
FilmVerwaltung fv; 

void filmInput()
{   
    //anordnung in txt datei: titel, regisseur, typ, genre, erscheinungsdatum, gesehen, bewertung, id
    string titel, regisseur, typ, genre; 
    unsigned int datum, gesehen;  
    float bewertung; 

    cout <<"\nTitel: "; 
    cin >> titel; 
    fflush(stdin); 

    cout <<"\nRegisseur: "; 
    cin >> regisseur;
    fflush(stdin); 

    cout <<"\nTyp(Serie oder Film): "; 
    cin >> typ;
    fflush(stdin); 

    cout <<"\nGenre: "; 
    cin >> genre;
    fflush(stdin); 

    cout <<"\nErscheinungsdatum: "; 
    cin >> datum;
    fflush(stdin); 

    cout <<"\nSchon gesehen? (0)Nein (1)Ja: "; 
    cin >> gesehen;
    fflush(stdin); 

    cout << "\nBewertung (0 - 10): "; 
    cin >> bewertung; 
    fflush(stdin); 

    cout << "\naktulle Id: " << fv.getFilmCount()+1;
    fv.writeFromUserInput(titel, regisseur, typ, genre, datum, gesehen, bewertung, fv.getFilmCount()+1); 
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

Film search()
{
    unsigned int theId; 
    string input; 
    cout << "\nWelchen Film willst du anpassen: "; 
    fv.showAllMovies(); 

    cout << "\nGib hier Titel oder Id nummer ein: "; 
    cin >> input; 
    
    if(getIfAlpha(input))
    {
        return fv.getFilm_wTitle(input); 
    }
    else
    {
        return fv.getFilm_wId(stoi(input)); 
    }
}


void werten(Film film)
{
   float wertung; 
    cout << "\nVon 0-10 welche Wertung würdest du geben: ";
    cin >> wertung; 
    film.setBewertung(wertung); 
}

void askUser()
{
    Film film;
    char choice; 
    do
    {
        cout << "\nOptionen:\n(s) Film eingeben und speichern\n(v) Alle Filme aus/in der Datenbank anzeigen"; 
        cout << "\n(g) Ein Film als gelesen markieren\n(b) Ein Film bewerten\n(u) Ein Film suchen";
        cout << "\nWas willst du machen: "; 
        cin >> choice; 
    } while (!isalpha(choice));
    
    switch(choice)
    {
        case 's': 
            fflush(stdin); 
            filmInput(); 
            break; 
        case 'v':
            fv.showAllMovies(); 
            break; 
        case 'g': 
            film = search();
            film.setGesehen(true); 
            cout << "\nDer Film: " << film.getTitel() << " wurde auf gesehen gesetzt!!"; 
            fv.printFilm(&film); 
            break; 
        case 'b': 
            film = search(); 
            werten(film); 
            fv.printFilm(&film); 
            break; 
        case 'u': 
            film = fv.searchByTitle();
            fv.printFilm(&film); 
            break; 
        default: 
            cout << "\nEtwas ist schief gelaufen"; 
    }
}

int main()
{   
    fv.readDatabase();
    
    unsigned int choice; 
    bool weiter;
    do
    {
        askUser(); 
        cout << "\nProgramm schließen (0) Nein; (1) Ja: "; 
        cin >> choice;
        weiter = (choice == 0) ? false : true;  
    } while (!weiter);
    
	return 0;
}