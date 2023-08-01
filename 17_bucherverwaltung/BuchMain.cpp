#include "BuchVerwaltung.h"
#include "Buch.h"
#include <iostream>

using namespace std; 

int main()
{
    //hier noch Nutzerabfrage

	Buch b1("h", "t", 15, false, 1);
    Buch b2("f", "g", 20, true, 10);
    BuchVerwaltung bv; 
    //b1.setTitel("HAllo"); 

    //cout << b1.getTitel() << " " << b1.getAutor() << " " << b1.getDatum(); 
	
    // bv.writeBook(&b1); 
    // bv.writeBook(&b2); 
    bv.readDatabase();
    bv.showAllBooks(); 
	//system("PAUSE");
	return 0;
}