#include "BuchVerwaltung.h"
#include "Buch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//ToDo: hier noch nachIndex suchen, id verwaltung, (auf doppelte achten?)
using namespace std; 

unsigned BuchVerwaltung::bookCount = 0; 

void BuchVerwaltung::writeBook(Buch* book)
{
    ofstream database("Buecher.txt", ios::app); //im append modus öffnen, um nicht zu überschreiben

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
        cout << "\nBuch wurde erfolgreich gespeichert"; 
    }
    else
    {
        cerr << "\nEs gab einen Fehler beim öffnen!"; 
    }
}

void BuchVerwaltung::getBook_wTitle(Buch* book)
{
    //suchen, (speichern), ausgeben
}
void BuchVerwaltung::getBook_wId(unsigned int id)
{
    //
}
void BuchVerwaltung::showAllBooks()
{
    cout << "\nAlle Bücher, die in der Datenbank liegen: "; 
    cout << "\nId \t Titel \t\t Autor \t Erscheinungsdatum \t Gelesen? \t Bewertung";
    for(int i = 0; i < bookCount; i++)
    {
        cout << endl << buecher[i].getId() << "\t   " << buecher[i].getTitel() << "\t\t   " << buecher[i].getAutor() << "\t\t" 
        << buecher[i].getDatum() << "\t\t     " << buecher[i].getGelesen() << "\t\t     " << buecher[i].getBewertung();
    }
}
void BuchVerwaltung::readDatabase()
{
    //die Buecher.txt muss in einem bestimmten Format geschrieben werden, damit man auch die korrekten Werte in den passenden Attributen speichert
    //z.B mit Komma trennen und spezifische anordnung
    ifstream bookdata("Buecher.txt"); 

    if(bookdata.is_open())
    {
        //alles als string, weil getline kann nur string einlesen - später entsprechend umwandeln
        string titelStr, autorStr, gelesenStr, datumStr, bewertungStr, idStr;
        unsigned int numberofBooks = 0; //für id

        string line; 
        while(getline(bookdata, line))
        {
            //anordnung: titel, autor, datum, gelesen?, bewertung, Id
            cout << line << endl; 
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
