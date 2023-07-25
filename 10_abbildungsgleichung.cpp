#include <cstdlib>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/*
    Formeln:    
        1/b + 1/g = 1/f
        β = B/G = b/g 
        f = (g•B)/(G+B) 
        g = f/B • (G+B) 

    Bedeutungen: 
        b: Bildweite (Abstand Sensor zum Objektiv - steht im Datenblatt, oder googlen je nach Objektiv Anschluss/Bajonett)
        g: Gegenstandsweite (Abstand Objekt zum Objektiv)
        B: Bildgröße (Sensorgröße)
        G: Gegenstandsgröße (Größe des zu fotografierenden Gegenstands)
        f: Brennweite
        β: Abbildungsmaßstab
*/

float getB()
{
    unsigned short int choice; 
    float B; 
    cout << "\nKennst du deine Sensorgröße (steht im Datenblatt)\n0: Nein\n1: Ja\nHier eingeben: "; 
    cin >> choice; 

    switch (choice)
    {
        case 0:
            float b, g, G; 
            unsigned short int wahl; 
            cout << "\nKennst du den Abstand von Sensor und Objektiv (b), Gegendstandsweite (g), Objektgröße (G)\n0: Nein\n1: Ja\nHier eingeben: "; 
            cin >> wahl; 
            if (wahl == 0)
            {
                cout << "Tut mir leid, da kann man dann nix machen :(" << endl; 
                exit(0);
            }
            cout << "\nAbstand von Sensor und Objektiv (b): "; 
            cin >> b; 

            cout << "\nGegendstandsweite (g): "; 
            cin >> g; 

            cout << "\nObjektgröße (G)): "; 
            cin >> G; 

            B = b/g * G;
            fflush(stdin); //eingabe buffer löschen
            break;
        case 1: 
            cout << "\nWie groß ist der Sensor: "; 
            cin >> B; 
            fflush(stdin);
            break; 
        default:
            fflush(stdin);
            cout << "\nUngültige Eingabe" << endl; 
    }

    return B; 
}

float calc_f(float B)
{
    // f = (g•B)/(G+B)
    float f, g, G; 
    cout << "\nWie weit ist dein Objekt vom Objekiv entfernt (g): "; 
    cin >> g; 
    cout << "\nWie Groß ist dein Objekt (G): "; 
    cin >> G; 

    f = (g * B)/(G + B); 
    return f; 
}

float calc_g(float B)
{
    float g, f, G; 
    cout << "\nWie Groß ist dein Objekt (G): "; 
    cin >> G; 
    cout << "\nWelche Brennweite hat dein Objektiv (f): "; 
    cin >> f;
    
    cout<< "\n f: " << f << " B: "<< B << " G: " << G ; 
    g = f/B * (G+B);

    return g; 
}


float askForB()
{
 
    unsigned short int knowB; 
    float B; 
    cout << "\nWeisst du wie groß deine Bildgröße (B) ist?\n0: Nein\n1: Ja\nHier eingeben: "; 
    cin >> knowB;

    switch (knowB)
    {
        case 0:
            B = getB(); 
            fflush(stdin);
            break;
        case 1: 
            cout << "\nWie groß ist dein B: "; 
            cin >> B; 
            fflush(stdin);
            break; 
        default:
            fflush(stdin);
            cout << "\nUngültige Eingabe" << endl; 
    }

    return B;
}

void calculate(float B)
{
    float g, f;
    unsigned short int what;
    cout << "Was möchtest du berechnen: ";
    cout << "\n0: g - Die Gegenstandsweite, also wie weit das Objekt vom Objektiv entfernt sein musst um es formatfüllend aufzunehmen";
    cout << "\n1: f - Die Brennweite für das Objektiv, um dein Objekt formatfüllend aufzunehmen"; 
    cout << "\nDeine Wahl: ";
    cin >> what;  

    switch(what)
    {
        case 0:
            g = calc_g(B);
            cout << "\nDein Objekt sollte " << g << " mm vom Objektiv entfernt sein"<< endl;
            fflush(stdin);
            break; 
        case 1:
            f = calc_f(B); 
            cout << "\nDeine Brennweite sollte <= " << f << " mm sein" << endl;
            fflush(stdin);
            break; 

        default: 
            fflush(stdin);
            cout << "\nUngültige Eingabe" << endl;  
    }

}

int main()
{
    cout << "\n!!!!!!!! Bitte alle Angaben in mm !!!!!!!!\nNachkommastellen mit Punkt (.) darstellen!!!\n\n"; 

    float B = askForB(); 
    
    calculate(B);

    return 0; 
}