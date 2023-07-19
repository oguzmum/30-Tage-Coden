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
    int number_to_be;
    cout << "Welche Zahl willst du erreichen (0 bis 5): "; 
    cin >> number_to_be;
    int count = 0;
    int zufallszahl = -237147203; //einfach iwas genommen was numbertobe nicht sein kann :) bzw. sollte

    do 
    {
        count += 1; 
        // hiermit sicherstellen, dass bei jedem mal neue Zufallszahlen generiert werden
        srand(time(0));

        // Zufallszahl zwischen 0 und 5 generieren
        zufallszahl = rand() % 5;
        //cout << zufallszahl << "\n";

    } while (number_to_be != zufallszahl);

    cout << "Iterationen: " << count << "\n" << endl;
    return 0;   
}