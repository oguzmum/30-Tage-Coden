#pragma once
#include "Buch.h"
#include <string>
#include <vector>

using namespace std; 

class BuchVerwaltung
{
public: 
    void writeBook(Buch* book);
    void getBook_wTitle(Buch* book);
    void getBook_wId(unsigned int id);
    void showAllBooks(); 
    void readDatabase(); 
private:
    static unsigned bookCount; //das wird die id bestimmen
    
    vector<Buch> buecher; 
    Buch* bookLibrary[]; 
};

//getBookCount oder so noch machen