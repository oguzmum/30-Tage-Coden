#pragma once
#include <string>
using namespace std; 

class Buch
{
public:
	Buch(); //standardkonstruktor
    Buch(string titel, string autor, unsigned int erscheinungsdatum); 
    Buch(string titel, string autor, unsigned int erscheinungsdatum, bool gelesen, float bewertung); 
    //id nicht drin, weil das soll der nutzer nicht eingeben können

    //setter
    void setTitel(string titel);
    void setAutor(string autor); 
    void setGelesen(bool gelesen);
    void setDatum(unsigned int datum);
    void setBewertung(float bewertung); 
    void setId(unsigned int id);

    //getter
    string getTitel() const;
    string getAutor() const;
    bool getGelesen() const; 
    unsigned int getDatum() const; 
    float getBewertung() const; 
    unsigned int getId() const; 

private:
	string titel, autor; 
    bool schonGelesen; 
    unsigned int erscheinungsDatum, id;  
    float bewertung; 
};