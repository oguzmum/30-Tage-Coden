/* Rechne hier nicht jede beliebige Einheit um zB Zeit, Yard, Flächen.. undso
    sondern rechne allgemein 10er Potenzen um
    also:
    - bestimmen welche 10er Potenz man vorliegen hat und in welche man umrechnen will
    - dann anwendbar auf: längen, ampere, volt, leistung, masse u.v.m

    die Logik zur Umrechnung der 10er Potenzen steht als Kommentar in der Funktion calcNewUnit
*/
void calcNewUnit(int from, int to); //cmd gedrückt halten und linke maustaste; springt dann zur Funktion

#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;



//die wichtigsten 10er Potenzen (die Namen)
const string praefixe[17] = {"Exa", "Peta", "Tera", "Giga", "Mega", "Kilo", "Hekto", "Deka", "- ", "Dezi", "Zenti", "Milli", "Mikro", "Nano", "Pico", "Femto", "Atto"};  
// die abkürzungen
const string inshort[17] = {"E", "P", "T", "G", "M", "k", "h", "da", "-", "d", "c", "m", "mi", "n", "p", "f", "a"};  
//bei mikro ist eig: µ, habs jz mi gemacht, damit es beim vergleich leichter ist

//die dezimalwertefür ausgabe bei der Tabelle
const double value[17] = {pow(10, 18), pow(10, 15), pow(10, 12), pow(10, 9), pow(10, 6), pow(10, 3), pow(10, 2), pow(10, 1), pow(10, 0), pow(10, -1), pow(10, -2), pow(10, -3), pow(10, -6), pow(10, -9), pow(10, -12), pow(10, -15), pow(10, -18)};

//die Exponenten um leichten zur gewünschten Potenz umzurechnen
const int exponent[17] = {18, 15, 12, 9, 6, 3, 2, 1, 0, -1, -2, -3, -6, -9, -12, -15, -18};


int getIndex(string abkuerzung)
{
    //index suchen, wo der Präfix ist - und den entsprechenden index zurückgeben
    cout << "\nabkuerzung: " << abkuerzung; 

    unsigned short int index; 
    for(int i = 0; i < int(sizeof(inshort) / sizeof(inshort[0])); i++)
    {
        if(inshort[i] == abkuerzung)
        {
            index = i; 
        }
    }
    return index; 
}

int getIndex_w_Expo(int exp)
{
    //index suchen, wo der Präfix ist - und den entsprechenden index zurückgeben
    unsigned short int index; 
    for(int i = 0; i < int(sizeof(exponent) / sizeof(exponent[0])); i++)
    {
        if(exponent[i] == exp)
        {
            index = i; 
        }
    }
    return index; 
}

void showUnits()
{
    cout << "\nPräfix \t Abkürzung  \t Dezimal";     
    cout << "\n------------------------------------------------";
    for(int i = 0; i < int(sizeof(praefixe) / sizeof(praefixe[0])); i++)
    {
        cout << "\n" << praefixe[i] << "\t\t" << inshort[i] << "\t" << value[i];
    }
}

int help()
{
    int fromPot;
    string theSign;
    unsigned short int theIndex; 

    showUnits(); 
    cout << "\nBitte gib die entsprechende Abkürzung ein, der zu deinem vorliegenden Wert passt, hier ein: "; 
    cin >> theSign; 

    theIndex = getIndex(theSign); 
    fromPot = exponent[theIndex]; 
    return fromPot; 
}

int fromUnit()
{
    //erstmal fragen, in welcher Einheit die Zahl/der Wert vorliegt
    unsigned short int knows, theIndex;
    int fromPot;
    string theSign;
     
    cout << "\nWeißt du in welcher 10er Potenz dein Wert vorliegt?\n0: Nein\n1: Ja\n?: ";
    cin >> knows;

    switch(knows)
    {
        case 0: 
            fromPot = help(); 
            break; 

        case 1: 
            cout << "\nWelchen Präfix hat dein Wert?\nBitte gib einer dieser Zeichen ein (von den Abkürzungen)\n";
            for(int i = 0; i < int(sizeof(praefixe) / sizeof(praefixe[0])); i++)
            {  
                cout << praefixe[i] << "\t";  
            }
            cout << "\n"; 
            for(int i = 0; i < int(sizeof(inshort) / sizeof(inshort[0])); i++)
            {  
                cout << inshort[i] << "\t";  
            }
            cout << "\n "; 
            cin >> theSign;

            theIndex = getIndex(theSign); 
            fromPot = exponent[theIndex]; 
            break; 

        default:
            cout << "\nUngültige Eingabe"; 

    }
    return fromPot; 
}

int wishedUnit()
{
    string getTo; 
    cout << "\nIn welche Einheit möchtest du umrechnen?"; 
    showUnits(); 
    cout << "\nHier die Abkürzung eingeben: ";
    cin >> getTo; 

    unsigned short int theIndex;
    int toExpo; 
    theIndex = getIndex(getTo); 
    toExpo = exponent[theIndex]; 
    return toExpo; 
}

void calcNewUnit(int from, int to)
{
    /* Beispiel: 500 mm in m -> 0,5m        hier: von 10^(-3) nach 10^0         im Prinzp wurde gerechnet: 500 * 10^(-3)
                                wie wurden die Exponenten also miteinander arithmetisiert: -3 - 0
                          km -> 0,0005 km   hier: von 10^(-3) nach 10^3         im Prinzp wurde gerechnet: 500 * 10^(-6)
                                wie wurden die Exponenten also miteinander arithmetisiert: -3 - 3
                          µm -> 500.000 µm  hier: von 10^(-3) nach 10^(-6)      im Prinzp wurde gerechnet: 500 * 10^3
                                wie wurden die Exponenten also miteinander arithmetisiert: -3 - (-6)

        daraus abzuleitende allgemeine Regel: 
            - Exponenten immer subtrahieren, um neuen Exponenten zu bestimmen
            - den neu berechneten Exponenten als 10er Potenz nehmen
            - diese 10er Potenz mit dem vorhandenen Wert (im Bsp: 500) multiplizieren

        ist auch mathematisch über Bruchgesetze begründbar
            Potenzgesetz für Zahlen mit gleicher Basis: a^m/a^n = a^(m-n)

            um eine neue 10er Potenz für ein gegebenen Wert zu berechnen, kann man die Potenzen miteinander teilen (also Exponenten subtrahieren)
            zum Bsp oben: 
                von mm in m: 500•(10^(-3)/10^(0)) = 500•(10^(-3-0)) = 500•10^(-3)

                von mm in km: 500•(10^(-3)/10^(3)) = 500•(10^(-3-3)) = 500•10^(-6)

                von mm in µm: 500•(10^(-3)/10^(-6)) = 500•(10^(-3-(-6))) = 500•10^3
    */

    double given, newcalc; 
    string unit; 
    cout << "\nWelchen Zahlenwert hat dein gegebener Wert: ";
    cin >> given;
    cout << "\nWas ist das für eine Einheit (meter, kilo, volt...), gib es als Abkürzung ein: "; 
    cin >> unit; 

    int newExpo = from - to; //den neuen Exponenten berechnen
    newcalc = given * pow(10, newExpo); //den neuen Dezimalwert in der gewünschten Einheit berechnen


    //nochmal index raussuchen, um bei der finalen Ausgabe auch die Einheiten mit anzugeben
    int fi, ti; //fi = fromIndex, ti = toIndex
    fi = getIndex_w_Expo(from); 
    ti = getIndex_w_Expo(to); 

    cout << "\n " << given << " " << inshort[fi] + unit << " sind " <<  newcalc << " " << inshort[ti] + unit; 

    //return newcalc; 
}

int main()
{
    int getfrom, getto;
    getfrom = fromUnit(); 
    
    getto = wishedUnit(); 
    calcNewUnit(getfrom, getto); 
    
    return 0; 
}