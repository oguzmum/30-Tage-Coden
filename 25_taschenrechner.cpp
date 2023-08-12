/* was soll der TR können

    + - * /
    wurzel ziehen
    potenz; exponentialzahlen
    logarithmus
    trigonometrie
    fakultät

    wie? -> als string einlesen, nach schlüsselzeichen suchen, + - log ln uso. 
    entsprechend die Zahlen und die zeichen filtern
    -> passende funktionen aufrufen
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std; 

double calculate(const char sign)
{
    double z1, z2; 
    cout << "\nZahl 1: "; 
    cin >> z1; 

    cout << "\nZahl 2: "; 
    cin >> z2; 
    if (sign == '+') return z1 + z2;
    if (sign == '-') return z1 - z2;
    if (sign == '*') return z1 * z2;
    if (sign == '/') return z1 / z2;
    if (sign == '^') return pow(z1, z2);

    return 0.0; 
}

double calcAdvanced(const char sign)
{
    double z1, z2; 
    cout << "\nFaktor: "; 
    cin >> z1; 

    cout << "\nin der klammer: "; 
    cin >> z2; 

    if(sign == 'l') return z1*log(z2);
    if(sign == 's') return z1*sin(z2);
    if(sign == 'c') return z1*cos(z2);
    if(sign == 't') return z1*tan(z2);
    return 0.0; 
}

double rooten()
{
    double erg, z1, z2; 
    cout << "\nZahl in Wurzel: "; 
    cin >> z1; 

    cout << "\ndie wievielte wurzel: "; 
    cin >> z2; 
    erg = pow(z1, 1/z2);
    return erg; 
}

unsigned int fact()
{
    unsigned int zahl, erg = 1; 
    cout << "\nWelche Zahl: ";
    cin >> zahl; 
    for (int i = zahl; i > 1; i--) 
    {
        erg *= i;
    }
    return erg;
}

void askUser()
{
    char wahl; 
    do
    {
        cout << "\nWas möchtest du machen: "; 
        cout << "\n+ addieren\n- subtrahieren\n* subtrahieren\n/ dividieren";
        cout << "\nl logarithmus\nw wurzel ziehen\nf fakultät\np potenz"; 
        cout << "\ns sinus\nc cosinus\nt tangens"; 
        cout << "\nWahl: "; 
        cin >> wahl;
        if (wahl == '+' || wahl == '-' || wahl == '*' || wahl == '/' ||
            wahl == 'l' || wahl == 'w' || wahl == 'f' || wahl == 'p' ||
            wahl == 's' || wahl == 'c' || wahl == 't' ) 
        {
            
            break;
        } 
        else 
        {
            cout << "Ungültige Eingabe. Bitte wähle eine gültige Option." << endl;
        }

    } while (true);
    
    double erg; 
    unsigned int ferg; 
    switch (wahl) 
    {
    case '+':
        erg = calculate('+');
        cout << erg; 
        break;

    case '-':
        erg = calculate('-');
        cout << erg; 
        break;

    case '*':
        erg = calculate('*');
        cout << erg; 
        break;

    case '/':
        erg = calculate('/');
        cout << erg; 
        break;

    case 'l':
        erg = calcAdvanced('l');
        cout << erg; 
        break;

    case 'w':
        erg = rooten();
        cout << erg; 
        break;

    case 'f':
        ferg = fact(); 
        cout << ferg; 
        break;
    case 'p':
        erg = calculate('p');
        cout << erg; 
        break;

    case 's':
        erg = calcAdvanced('s');
        cout << erg; 
        break;

    case 'c':
        erg = calcAdvanced('c');
        cout << erg; 
        break;

    case 't':
        erg = calcAdvanced('t');
        cout << erg; 
        break;

    default:
        cout << "\nmmmmmogggge." << endl;
}

}


int main()
{
    askUser();
    return 0; 
}


// bool isOperator(const string &op) 
// {
//     vector<string> keys = {"+", "-", "*", "/", "sqrt", "^", "sin", "cos", "tan", "log", "ln"};
//     return find(keys.begin(), keys.end(), op) != keys.end();
// }

// void firstIdea()
// {
//     //erste idee
//     string eingabe; 
//     cout << "\nWas möchtest du berechnen: " << endl; 
//     cin >> eingabe; 

//     //hier die zahlen und operatinen speichern
//     vector<float> numbers;
//     vector<string> operations;
//     cout << "\neingabe size" << eingabe.size(); 
//     for(int i = 0; i < eingabe.size(); i++)
//     {
//         string nmbr;
//         cout << "\ni: " << i; 
//         if(isdigit(eingabe[i]))
//         {
//             int runner = 0; 
//             do
//             {
//                 nmbr += eingabe[i+runner];
//                 runner += 1;
//             } while (isdigit(eingabe[i+runner]));

            
//             numbers.push_back(stof(nmbr));
//         }
//         else
//         {
//             string op(1, eingabe[i]); // Convert char to string
//             if (i + 1 < eingabe.size() && isOperator(op + eingabe[i + 1])) {
//                 op += eingabe[i + 1];
//                 i++;
//             }
//             if (isOperator(op)) {
//                 operations.push_back(op);
//             }
//         }

        
//     }

//     for(int i = 0; i < numbers.size(); i++)
//     {
//         cout << "\nss " << numbers[i];
//     }

//     for(int i = 0; i < operations.size(); i++)
//     {
//         cout << "\nss " << operations[i];
//     }   
// }