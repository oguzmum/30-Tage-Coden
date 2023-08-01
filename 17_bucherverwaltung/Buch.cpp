#include "Buch.h"
#include <iostream>

using namespace std; 

// Buch(string titel, string autor, unsigned int erscheinungdatum); 
// standardkonstruktor wenn keine werte mitgegeben werden
Buch::Buch() : Buch{"k.A.", "k.A.", 0} {}

Buch::Buch(string titel, string autor, unsigned int erscheinungsdatum)
{
    setTitel(titel); 
    setAutor(autor); 
    setDatum(erscheinungsdatum); 
}
Buch::Buch(string titel, string autor, unsigned int erscheinungsdatum, bool gelesen, unsigned int bewertung)
{
    setTitel(titel); 
    setAutor(autor); 
    setDatum(erscheinungsdatum); 
    setGelesen(gelesen); 
    setBewertung(bewertung); 
}

//setter
void Buch::setTitel(string titel)
{
    this->titel = titel; 
}
void Buch::setAutor(string autor)
{
    this->autor = autor; 
}
void Buch::setGelesen(bool gelesen)
{
    schonGelesen = gelesen; 
}
void Buch::setDatum(unsigned int datum)
{
    erscheinungsDatum = datum; 
}
void Buch::setBewertung(unsigned int bewertung)
{
    this->bewertung = bewertung; 
}
void Buch::setId(unsigned int id)
{
    this->id = id; 
}

//getter
string Buch::getTitel() const
{
    return titel; 
}
string Buch::getAutor() const
{
    return autor; 
}
bool Buch::getGelesen() const
{
    return schonGelesen; 
}
unsigned int Buch::getDatum() const
{
    return erscheinungsDatum;
}
unsigned int Buch::getBewertung() const
{
    return bewertung; 
}
unsigned int Buch::getId() const
{
    return id; 
}