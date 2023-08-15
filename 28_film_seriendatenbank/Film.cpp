#include "Film.h"
#include <iostream>

using namespace std; 

Film::Film() : Film{"k.A.", "k.A.", "k.A.", "k.A.", 0} {}
Film::Film(string titel, string regisseur, string typ, string genre, unsigned int erscheinungsdatum)
{
    setTitel(titel);
    setRegisseur(regisseur);
    setTyp(typ);
    setGenre(genre);
    setDatum(erscheinungsDatum);
}
Film::Film(string titel, string regisseur, string typ, string genre, unsigned int erscheinungsdatum, bool gesehen, float bewertung)
{
    setTitel(titel);
    setRegisseur(regisseur);
    setTyp(typ);
    setGenre(genre);
    setDatum(erscheinungsDatum);
    setGesehen(gesehen);
    setBewertung(bewertung);
}


//setter
void Film::setTitel(string titel)
{
    this->titel = titel;
}
void Film::setRegisseur(string regisseur)
{
    this->regisseur = regisseur;
}
void Film::setTyp(string typ)
{
    this->typ = typ; 
}
void Film::setGenre(string genre)
{
    this->genre = genre; 
}
void Film::setGesehen(bool gesehen)
{
    this->gesehen = gesehen;
}
void Film::setDatum(unsigned int datum)
{
    erscheinungsDatum = datum; 
}
void Film::setBewertung(float bewertung)
{
    this->bewertung = bewertung;
}
void Film::setId(unsigned int id)
{
    this->id = id;
}

//getter
string Film::getTitel() const
{
    return titel; 
}
string Film::getRegisseur() const
{
    return regisseur;
}
string Film::getTyp() const
{
    return typ;
}
string Film::getGenre() const
{
    return genre; 
}
bool Film::getGesehen() const
{
    return gesehen;
}
unsigned int Film::getDatum() const
{
    return erscheinungsDatum;
}
float Film::getBewertung() const
{
    return bewertung;
}
unsigned int Film::getId() const
{
    return id; 
}