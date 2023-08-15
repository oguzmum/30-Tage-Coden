#pragma once
#include <string>
using namespace std; 

class Film
{
public:
	Film(); //standardkonstruktor
    Film(string titel, string regisseur, string typ, string genre, unsigned int erscheinungsdatum); 
    Film(string titel, string regisseur, string typ, string genre, unsigned int erscheinungsdatum, bool gesehen, float bewertung); 
    //id nicht drin, weil das soll der nutzer nicht eingeben können

    //setter
    void setTitel(string titel);
    void setRegisseur(string regisseur); 
    void setTyp(string typ); 
    void setGenre(string genre); 
    void setGesehen(bool gesehen);
    void setDatum(unsigned int datum);
    void setBewertung(float bewertung); 
    void setId(unsigned int id);

    //getter
    string getTitel() const;
    string getRegisseur() const;
    string getTyp() const;
    string getGenre() const; 
    bool getGesehen() const; 
    unsigned int getDatum() const; 
    float getBewertung() const; 
    unsigned int getId() const; 

private:
	string titel, regisseur, typ, genre; 
    bool gesehen; 
    unsigned int erscheinungsDatum, id;  
    float bewertung; 
};