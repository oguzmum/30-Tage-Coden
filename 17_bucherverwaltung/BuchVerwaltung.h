#pragma once
#include "Buch.h"
#include <string>
#include <vector>

using namespace std; 

class BuchVerwaltung
{
public: 
    void writeBook(Buch* book);
    Buch getBook_wTitle(string title);
    Buch getBook_wId(unsigned int id);
    void showAllBooks(); 
    void readDatabase(); 

    unsigned getBookCount();

    void writeFromUserInput(string titel, string autor, unsigned int datum, unsigned int gelesen, float bewertung, unsigned int id); 

    Buch searchByTitle();

    void printBook(Buch* book); 
private:
    static unsigned bookCount; //das wird die id bestimmen
    
    vector<Buch> buecher; 
};

//getBookCount oder so noch machen