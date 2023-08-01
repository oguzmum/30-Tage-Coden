#include "BuchVerwaltung.h"
#include "Buch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//ToDo: hier noch nachIndex suchen, id verwaltung, (auf doppelte achten?)
//      datenbank löschen, zurücksetzen können; o auch ein Buch nur löschen
//          - beim löschen dann verschiebung der ID's beachten (o. eigene datenbank für ID's)
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
    //ToDo: besser formattieren
    cout << "\nAlle Bücher, die in der Datenbank liegen: "; 
    cout << "\nId \t Titel \t\t Autor \t Erscheinungsdatum \t Gelesen? \t Bewertung";
    for(int i = 0; i < bookCount+1; i++)
    {
        cout << endl << buecher[i].getId() << "\t   " << buecher[i].getTitel() << "\t\t   " << buecher[i].getAutor() << "\t\t" 
        << buecher[i].getDatum() << "\t\t     " << buecher[i].getGelesen() << "\t\t     " << buecher[i].getBewertung();
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
            

            // cout << "\ntitel: " << titelStr; 
            // cout << "\nautor: " << autorStr; 
            // cout << "\nDatum: " << datumStr; 
            // cout << "\ngelesen: " << gelesenStr; 
            // cout << "\nbewertung: " << bewertungStr; 
            // cout << "\nid: " << idStr; 

            bool gelesen = (gelesenStr == "0") ? false : true; //wenn gelesen in txt 0, dann false, sonst true

            //Buch(string titel, string autor, unsigned int erscheinungdatum, bool gelesen, unsigned int bewertung); 
            Buch* newBook = new Buch(titelStr, autorStr, stoi(datumStr), gelesen, stoi(bewertungStr));
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

void BuchVerwaltung::writeFromUserInput(string titel, string autor, unsigned int datum, unsigned int gelesen, unsigned int bewertung, unsigned int id)
{ //anordnung int txt datei: titel, autor, datum, gelesen?, bewertung, Id
    ofstream database(dateiName, ios::app); //im append modus öffnen, um nicht zu überschreiben

    if(database.is_open() && database.good())
    {
        //mit komma trennen für die spezifische anordnung
        //anordnung: titel, autor, datum, gelesen?, bewertung, Id
        cout << "\nbei userinput: " << titel << " " << autor << " " << datum << " " << gelesen << " " << id; 
        database << titel << ", ";
        database << autor << ", ";
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
    cout << "\nId \t Titel \t\t Autor \t Erscheinungsdatum \t Gelesen? \t Bewertung";
    cout << endl << book->getId() << "\t" << book->getTitel() << "\t" << book->getAutor() << book->getDatum() << "\t" << book->getGelesen() << "\t" << book->getBewertung(); 
}