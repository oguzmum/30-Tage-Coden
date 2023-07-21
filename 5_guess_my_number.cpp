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
    srand(time(0));
    int zufallszahl = rand() % 501; //zahl zwischen 0 und 500
    int eingabe, count = 0; 

    do 
    {    
        cout << "\nRaten Sie die Zahl: ";
        cin >> eingabe; 

        if(eingabe < zufallszahl)
        {
            cout << "Zu klein geraten" << endl; 
        }
        else if(eingabe > zufallszahl)
        {
            cout << "Zu hoch geraten" << endl; 
        }

        count += 1; 
    } while(eingabe != zufallszahl);

    cout << "\nSie haben " << count << " Schritte gebraucht" << endl; 
}