#pragma once
#include "Film.h"
#include <string>
#include <vector>

using namespace std; 

class FilmVerwaltung
{
public: 
    void writeFilm(Film* movie);
    Film getFilm_wTitle(string title);
    Film getFilm_wId(unsigned int id);
    void showAllMovies(); 
    void readDatabase(); 

    unsigned getFilmCount();

    void writeFromUserInput(string titel, string regisseur, string typ, string genre, unsigned int datum, 
    unsigned int gesehen, float bewertung, unsigned int id); 

    Film searchByTitle();

    void printFilm(Film* film); 
private:
    static unsigned filmCount; //das wird die id bestimmen
    vector<Film> filme; 
};

//getBookCount oder so noch machen