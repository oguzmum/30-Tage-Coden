#include "BuchVerwaltung.h"
#include "Buch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 

unsigned BuchVerwaltung::bookCount = 0; 

string dateiName = "Buecher.txt";

void BuchVerwaltung::writeBook(Buch* book)
{
    ofstream database(dateiName, ios::app); //im append modus öffnen, um nicht zu überschreiben

    if(database.is_open() && database.good())
    {
        //mit komma trennen für die spezifische anordnung
        //anordnung: titel, autor, datum, gelesen?, bewertung, Id
        database << book->getTitel() << ", ";
        database << book->getAutor() << ", ";
        database << book->getDatum() << ", ";
        database << book->getGelesen() << ", ";
        database << book->getBewertung() << ", ";
        database << book->getId() << endl;
        //geht das nicht iwie einfacher, als einzeiler oder so??
        database.close();
        bookCount += 1; 
        cout << "\nBuch wurde erfolgreich gespeichert"; 
    }
    else
    {
        cerr << "\nEs gab einen Fehler beim öffnen!"; 
    }
}

Buch BuchVerwaltung::getBook_wTitle(string title)
{
    //suchen, zurückgeben
    for(int i = 0; i < bookCount; i++)
    {
        if(buecher[i].getTitel() == title)
        {   
            return buecher[i]; 
        }
    }
    cout << endl << "Buch nicht gefunden"; 
    exit(0);
}
Buch BuchVerwaltung::getBook_wId(unsigned int id)
{
    for(int i = 0; i < bookCount; i++)
    {
        if(buecher[i].getId() == id)
        {   
            return buecher[i]; 
        }
    }
    cout << endl << "Buch nicht gefunden"; 
    exit(0);
}
void BuchVerwaltung::showAllBooks()
{
    readDatabase(); 
    
    cout << "\nBücher, die in der Datenbank liegen: " << bookCount << endl << endl; 
    for(int i = 0; i < bookCount; i++)
    {
        cout << endl; 
        cout << "=========== Buch Id: " << buecher[i].getId() << " ===========" << endl;
        cout << "Titel: " << "\t\t" << buecher[i].getTitel() << endl;
        cout << "Autor:" << "\t\t" << buecher[i].getAutor() << endl ;
        cout << "Erschienen: " << "\t" << buecher[i].getDatum() << endl; 
        cout << "Gelesen?: " << "\t" << buecher[i].getGelesen() << endl;
        cout << "Bewertung: " << "\t" << buecher[i].getBewertung() << endl; 
    }
}

void BuchVerwaltung::readDatabase()
{
    //die Buecher.txt muss in einem bestimmten Format geschrieben werden, damit man auch die korrekten Werte in den passenden Attributen speichert
    //z.B mit Komma trennen und spezifische anordnung
    buecher.clear(); 
    bookCount = 0; 

    ifstream bookdata(dateiName); 

    if(bookdata.is_open())
    {
        //alles als string, weil getline kann nur string einlesen - später entsprechend umwandeln
        string titelStr, autorStr, gelesenStr, datumStr, bewertungStr, idStr;
        unsigned int numberofBooks = 0; //für id

        string line; 
        while(getline(bookdata, line))
        {
            //anordnung int txt datei: titel, autor, datum, gelesen?, bewertung, Id
            stringstream ss(line);
            getline(ss, titelStr, ',');
            getline(ss, autorStr, ',');
            getline(ss, datumStr, ',');
            getline(ss, gelesenStr, ',');
            getline(ss, bewertungStr, ',');
            getline(ss, idStr);
            
            //das leerzeichen muss bleiben, oder muss es beim eingeben in der Datenbank ändern; 
            //ohne leerzeichen wird vergleich immer false, also wird gelesen = true, obwohl es false sein müsste
            bool gelesen = (gelesenStr.compare(" 0") == 0) ? false : true; //wenn gelesen in txt 0, dann false, sonst true
            cout << "\nGelesen: " << gelesen; 
            //Buch(string titel, string autor, unsigned int erscheinungdatum, bool gelesen, unsigned int bewertung); 
            Buch* newBook = new Buch(titelStr, autorStr, stoi(datumStr), gelesen, stof(bewertungStr));
            newBook->setId(stoi(idStr));
            buecher.push_back(*newBook); 
            bookCount += 1; 
        }
    }
}

unsigned BuchVerwaltung::getBookCount()
{
    if(bookCount == 0)
    {
        readDatabase(); //bei readDatabase kriegt man bookCount raus
    }
    return bookCount; 
}

void BuchVerwaltung::writeFromUserInput(string titel, string autor, unsigned int datum, unsigned int gelesen, float bewertung, unsigned int id)
{ //anordnung int txt datei: titel, autor, datum, gelesen?, bewertung, Id
    cout << "\nGelsen beim schreiben: " << gelesen; 
    ofstream database(dateiName, ios::app); //im append modus öffnen, um nicht zu überschreiben

    if(database.is_open() && database.good())
    {
        //mit komma trennen für die spezifische anordnung
        //anordnung: titel, autor, datum, gelesen?, bewertung, Id
        database << titel << ",";
        database << autor << ",";
        database << datum << ", ";
        database << gelesen << ", ";
        database << bewertung << ", ";
        database << id << endl;
        //geht das nicht iwie einfacher, als einzeiler oder so??
        database.close();
        cout << "\nBuch wurde erfolgreich gespeichert"; 
        bookCount += 1; 
    }
    else
    {
        cerr << "\nEs gab einen Fehler beim öffnen!"; 
    }
}

Buch BuchVerwaltung::searchByTitle()
{
    string titel; 
    cout << "\nTitel des Buch's welches du suchst: "; 
    cin >> titel; 
    for(int i = 0; i < bookCount; i++)
    {
        if(buecher[i].getTitel() == titel)
        {
            return buecher[i]; 
        }
    }
    cout << "\nBuch nicht gefunden"; 
    exit(0); 
}

void BuchVerwaltung::printBook(Buch* book)
{
    cout << endl; 
    cout << "=========== Buch Id: " << book->getId() << " ===========" << endl;
    cout << "Titel: " << "\t\t" << book->getTitel() << endl;
    cout << "Autor: " << "\t\t" << book->getAutor() << endl ;
    cout << "Erschienen: " << "\t" << book->getDatum() << endl; 
    cout << "Gelesen?: " << "\t" << book->getGelesen() << endl;
    cout << "Bewertung: " << "\t" << book->getBewertung() << endl;
}