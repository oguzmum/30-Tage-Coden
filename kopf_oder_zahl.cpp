#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::time;
using std::srand; 


int main()
{
    string liste[] = {"Kopf", "Zahl"}; 
    
    srand(time(0));
    int zufallszahl = rand() % 2;
    //cout << zufallszahl << endl;
    
    cout << "Ergebnis: " << liste[zufallszahl] << endl; 

    return 0; 
}