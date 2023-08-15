#include "FilmVerwaltung.h"
#include "Film.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 

unsigned FilmVerwaltung::filmCount = 0; 

string dateiName = "Filme.txt";

//anordnung in txt file:
// titel, regisseur, typ, genre, erscheinungsdatum, gesehen, bewertung, id

void FilmVerwaltung::writeFilm(Film* movie)
{
    ofstream database(dateiName, ios::app); //im append modus öffnen, um nicht zu überschreiben

    if(database.is_open() && database.good())
    {
        //mit komma trennen für die spezifische anordnung
        //anordnung: titel, regisseur, typ, genre, erscheinungsdatum, gesehen, bewertung, id
        database << movie->getTitel() << ", ";
        database << movie->getRegisseur() << ", ";
        database << movie->getTyp() << ", ";
        database << movie->getGenre() << ", ";
        database << movie->getDatum() << ", ";
        database << movie->getGesehen() << ", ";
        database << movie->getBewertung() << ", ";
        database << movie->getId() << endl;
        //geht das nicht iwie einfacher, als einzeiler oder so??
        database.close();
        filmCount += 1; 
        cout << "\nFilm/Serie wurde erfolgreich gespeichert"; 
    }
    else
    {
        cerr << "\nEs gab einen Fehler beim öffnen!"; 
    }
}

Film FilmVerwaltung::getFilm_wTitle(string title)
{
    //suchen, zurückgeben
    for(int i = 0; i < filmCount; i++)
    {
        if(filme[i].getTitel() == title)
        {   
            return filme[i]; 
        }
    }
    cout << endl << "\nFilm nicht gefunden"; 
    exit(0);
}

Film FilmVerwaltung::getFilm_wId(unsigned int id)
{
    for(int i = 0; i < filmCount; i++)
    {
        if(filme[i].getId() == id)
        {   
            return filme[i]; 
        }
    }
    cout << endl << "\nFilm/Serie nicht gefunden"; 
    exit(0);
}

void FilmVerwaltung::showAllMovies()
{
    readDatabase(); 
    
    cout << "\nFilme, die in der Datenbank liegen: " << filmCount << endl << endl; 
    for(int i = 0; i < filmCount; i++)
    {
        cout << endl; 
        cout << "=========== Film Id: " << filme[i].getId() << " ===========" << endl;
        cout << "Titel: " << "\t\t" << filme[i].getTitel() << endl;
        cout << "Regisseur:" << "\t" << filme[i].getRegisseur() << endl ;
        cout << "Typ:" << "\t\t" << filme[i].getTyp() << endl ;
        cout << "Genre:" << "\t\t" << filme[i].getGenre() << endl ;
        cout << "Erschienen: " << "\t" << filme[i].getDatum() << endl; 
        cout << "Gesehen?: " << "\t" << filme[i].getGesehen() << endl;
        cout << "Bewertung: " << "\t" << filme[i].getBewertung() << endl; 
    }
}


void FilmVerwaltung::readDatabase()
{
    //die Buecher.txt muss in einem bestimmten Format geschrieben werden, damit man auch die korrekten Werte in den passenden Attributen speichert
    //z.B mit Komma trennen und spezifische anordnung
    filme.clear(); 
    filmCount = 0; 

    ifstream filmdata(dateiName); 

    if(filmdata.is_open())
    {
        //alles als string, weil getline kann nur string einlesen - später entsprechend umwandeln
        string titelStr, regisseurStr, typStr, genreStr, gesehenStr, datumStr, bewertungStr, idStr;
        unsigned int numberofBooks = 0; //für id

        string line; 
        while(getline(filmdata, line))
        {
            //anordnung in txt datei: titel, regisseur, typ, genre, erscheinungsdatum, gesehen, bewertung, id
            stringstream ss(line);
            getline(ss, titelStr, ',');
            getline(ss, regisseurStr, ',');
            getline(ss, typStr, ',');
            getline(ss, genreStr, ',');
            getline(ss, datumStr, ',');
            getline(ss, gesehenStr, ',');
            getline(ss, bewertungStr, ',');
            getline(ss, idStr);
            
            //das leerzeichen muss bleiben, oder muss es beim eingeben in der Datenbank ändern; 
            //ohne leerzeichen wird vergleich immer false, also wird gelesen = true, obwohl es false sein müsste
            bool gesehen = (gesehenStr.compare(" 0") == 0) ? false : true; //wenn gelesen in txt 0, dann false, sonst true
            cout << "\nGesehen: " << gesehen; 
            //Buch(string titel, string autor, unsigned int erscheinungdatum, bool gelesen, unsigned int bewertung); 
            Film* newFilm = new Film(titelStr, regisseurStr, typStr, genreStr, stoi(datumStr), gesehen, stof(bewertungStr));
            newFilm->setId(stoi(idStr));
            filme.push_back(*newFilm); 
            filmCount += 1; 
        }
    }
}

unsigned FilmVerwaltung::getFilmCount()
{
    if(filmCount == 0)
    {
        readDatabase(); 
    }
    return filmCount; 
}

void FilmVerwaltung::writeFromUserInput(string titel, string regisseur, string typ, string genre, unsigned int datum, unsigned int gesehen, float bewertung, unsigned int id)
{
    //anordnung in txt file:
    // titel, regisseur, typ, genre, erscheinungsdatum, gesehen, bewertung, id
    ofstream database(dateiName, ios::app); //im append modus öffnen, um nicht zu überschreiben

    if(database.is_open() && database.good())
    {
        //mit komma trennen für die spezifische anordnung
        //anordnung: titel, autor, datum, gelesen?, bewertung, Id
        database << titel << ",";
        database << regisseur << ",";
        database << typ << ",";
        database << genre << ",";
        database << datum << ", ";
        database << gesehen << ", ";
        database << bewertung << ", ";
        database << id << endl;
        //geht das nicht iwie einfacher, als einzeiler oder so??
        database.close();
        cout << "\nFilm/Serie wurde erfolgreich gespeichert"; 
        filmCount += 1; 
    }
    else
    {
        cerr << "\nEs gab einen Fehler beim öffnen!"; 
    }
}

Film FilmVerwaltung::searchByTitle()
{
    string titel; 
    cout << "\nTitel des Film's welches du suchst: "; 
    cin >> titel; 
    for(int i = 0; i < filmCount; i++)
    {
        if(filme[i].getTitel() == titel)
        {
            return filme[i]; 
        }
    }
    cout << "\nFilm/Serie nicht gefunden"; 
    exit(0); 
}

void FilmVerwaltung::printFilm(Film* film)
{
    cout << endl; 
    
    cout << "=========== Film Id: " << film->getId() << " ===========" << endl;
    cout << "Titel: " << "\t\t" << film->getTitel() << endl;
    cout << "Regisseur:" << "\t" << film->getRegisseur() << endl ;
    cout << "Typ:" << "\t\t" << film->getTyp() << endl ;
    cout << "Genre:" << "\t\t" << film->getGenre() << endl ;
    cout << "Erschienen: " << "\t" << film->getDatum() << endl; 
    cout << "Gesehen?: " << "\t" << film->getGesehen() << endl;
    cout << "Bewertung: " << "\t" << film->getBewertung() << endl; 
}