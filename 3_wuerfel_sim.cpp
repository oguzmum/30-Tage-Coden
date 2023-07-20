#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::time;
using std::srand; 


int main()
{
    unsigned short int eingabe; 

    do 
    {   
        do
        {
            cout << "\n Wollen Sie würfeln ? \n 0: Nein \n 1: Ja \n Hier eingeben:";
            cin >> eingabe;
        } while (eingabe != 1);
        
        if (eingabe == 1)
        {
            srand(time(0));
            int zufallszahl = rand() % 6 + 1;
            cout << "\nGewürfelt: " << zufallszahl << endl; 
        }

    }while(eingabe == 1);
}