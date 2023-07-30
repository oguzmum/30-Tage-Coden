/*
    28.07.2023: versuche die Algortihmen erstmal aus dem Kopf 
                    - mit den Inhalten aus Algorithmen und Datenstrukturen
                    - und allgemeine Logik, die die Algorithmen haben
                implementiere als: 
                    Such:       lineare Suche, binäre Suche
                    sortier:    bubblesort, selection sort, insertion sort

*/

#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::time;
using std::srand;
using std::vector; 


/*hiermit Zufallszahlen erstellt
    srand(time(0));
    for (int i = 0; i < 20; i++)
    {
        
        cout << rand() % 501 << " ,"; //zahl zwischen 0 und 500
    }
*/
int unsortiert[20] = {253 ,273 ,97 ,144 ,102 ,399 ,11 ,91 ,249 ,116 ,59 ,247 ,80 ,89 ,299 ,479 ,144 ,122 ,158 ,123};

int sortiert[20] = {11, 59, 80, 89, 91, 97, 102, 116, 122, 123, 144, 144, 158, 247, 249, 253, 273, 299, 399, 479};

//sortieralgorithmen
vector<int> bubbleSort(vector<int>& list)
{
    /*Logik: (klein -> groß)
        • unsortierte Liste A durchgehen, nachbarn vergleichen
        • A[n] < A[n+1] => bleibt so; nix machen
        • A[n] > A[n+1] => tauschen
    */

    for(int i = 0; i < int(list.size()-1); i++) //bei beiden nur bis -1, weil mit dem Letzten Element kann man keine Nachbarn vergleichen
    {
        for(int x = 0; x < int(list.size()-1); x++)
        {
            if(list[x] > list[x+1])
            {//dreieckstausch
                int temp = list[x]; 
                list[x] = list[x+1];
                list[x+1] = temp;  
            }
        }
    }
    return list;
}

vector<int> selectionSort(vector<int>& list)
{
    /*Logik: (klein -> groß)
        • zu Beginn alles unsortiert
        • den kleinsten Datensatz im unsortierten Bereich suchen
        • einen sortierten bereich erstellen, den Wert dort einsetzen
        • jz hat man einen sortierten und einen unsortierten bereich
        • im unsortierten Bereich nach dem kleinsten Datensatz suchen
        • ganz rechts im sortierten Bereich einsetzen
    */
    for(int i = 0; i < int(list.size()); i++)
    {
        //der sortierte Bereich
        int minIndex = i; //index für stelle des minimums, zu beginn der linke rand des unsortierten bereichs
        for(int x = i+1; x < int(list.size()); x++)
        {
            if(list[x] < list[minIndex])
            {//kleineres minimum gefunden, entsprechend index neu speichern
                minIndex = x; 
            }    
        }
        //dreieckstausch; das gefundene Minimum kommt an den rechten rand des sortierten bereichs
        //das dortige element kommt an die stelle des gefundenen Minimums
        int temp = list[i]; 
        list[i] = list[minIndex];
        list[minIndex] = temp;
    }

    return list; 
}

vector<int> insertionSort(vector<int>& list)
{
    /*Logik: (klein -> groß) 
        • ersten Datensatz ist der sortierte Bereich, rest unsortiert
        • ersten Datensatz im unsortierten Bereich (linker Rand) nehmen 
        • an passender Stelle in sortierten bereich einsetzen
        • entsprechend müsssen alle Datensätze im sortierten Bereich korrekt verschoben werden
    */

    for(int i = 0; i < int(list.size()-1); i++)
    {
        int fromUnsorted = list[i+1]; //datensatz aus unsortierten Bereich nehmen
        int sortedIndex = i; //index des sortierten bereichs speichern

        while(sortedIndex >= 0 && list[sortedIndex] > fromUnsorted)
        { //datensätze im sortierten bereich so verschieben, dass das Element an die passende Stelle reinpasst
            //für diese passende Stelle entsteht eine Lücke
            list[sortedIndex+1] = list[sortedIndex]; 
            sortedIndex -= 1; 
        }
        list[sortedIndex+1] = fromUnsorted; //die entstandenen Lücke füllen
    }

    return list; 
}

//suchalgorithmen
vector<int> linSearch(vector<int>& list, int key)
{
    /*Logik
        • Wann anwenden: liste unsortiert, oder man weiss nichts über Anordnung
        • jedes element druchgehen, von vorne bis hinten
    */
    vector<int> index; 
    for(int i = 0; i < int(list.size()); i++)
    {
        if(list[i] == key)
        { 
            index.push_back(i); 
        }
    }
    if (index.size() == 0)
    {
        cout << "\nDeine gesuchte Zahl ist nicht im Datensatz enthalten";     
        exit(0); 
    }
    else
    {
        cout << "\nDeine gesuchte Zahl wurde: " << index.size() << " mal gefunden"; 
        return index; 
    }
    
}

vector<int> binarySearch(vector<int>& list, int key)
{
    /*Logik: 
        • Wann: Liste muss sortiert sein
        • in der Datensatzmitte gucken ob gesuchte Zahl kleiner oder größer als Element in der Mitte ist
            list[mitte] == key -> gefunden
            list[mitte] < key -> nach rechts; im rechten Teil weiter suchen
            list[mitte] > key -> nach links; im linken Teil weiter suchen
        • solange suchen bis gewünschte Zahl gefunden wird
        • oder bis sich linke und rechte Rand "überkreuzen" (das reicht sogar)
            • im zweiten Fall ist die gesuchte Zahl nicht in der Liste
    */
    int left = 0, right = list.size(); 
    int middle = (left+right)/2; 
    vector<int> index; 

    while(left <= right)
    {
        middle = (left+right)/2; 
        if(list[middle] < key)
        {
            //rechts weiter suchen, das heisst linke bereich kann man "auslöschen"
            left = middle + 1; 
        }
        else if (list[middle] > key)
        {
            right = middle - 1; 
        }
        else 
        {
            index.push_back(middle); 
            //gucken ob die zahl mehrmals vorkommt
            for(int i = -3; i < 4; i++)
            { //pauschal einfach 3 weitere stellen vor der mitte und 3 nach der mitte
                if(middle+i < 0 || middle+i > int(list.size()) || middle+i == index[0]) 
                { //prüfen ob man sich noch im Array befindet; die bereits gefundende nicht mit einbeziehen
                    continue;
                }

                if(list[middle+i] == key)
                {
                    index.push_back(middle+i);
                }

                if(middle+i > middle && list[middle+i] != key)
                { //nach der gefunden stelle ist keine weitere mehr; dann brauch man nicht mehr zu suchen
                    break; 
                }
            }
            cout << "\nDeine gesuchte Zahl wurde " << index.size() << " mal gefunden\n"; 
            return index;
        }
    }    
}

int main()
{
    vector<int> unsorted(unsortiert, unsortiert + (sizeof(unsortiert)/sizeof(unsortiert[0]))); 
    vector<int> sorted(sortiert, sortiert + (sizeof(sortiert)/sizeof(sortiert[0]))); 
    //ich konnte die Liste unsortiert nicht direkt als vector<int> Datentyp initialisieren, sondern muss das so umständlich machen :(
    
    /*
    vector<int> forBubble(unsortiert, unsortiert + (sizeof(unsortiert)/sizeof(unsortiert[0]))); 
    forBubble = bubbleSort(forBubble);
    for (int i = 0; i < int(forBubble.size()); i++)
    {
        cout << forBubble[i] << " ";
    }
    

    vector<int> forSelection(unsortiert, unsortiert + (sizeof(unsortiert)/sizeof(unsortiert[0]))); 
    forSelection = selectionSort(forSelection); 
    for (int i = 0; i < int(forSelection.size()); i++)
    {
        cout << forSelection[i] << " ";
    }
    


    vector<int> forInsertion(unsortiert, unsortiert + (sizeof(unsortiert)/sizeof(unsortiert[0]))); 
    forInsertion = insertionSort(forInsertion); 
    for (int i = 0; i < int(forInsertion.size()); i++)
    {
        cout << forInsertion[i] << ", ";
    }
    

    vector<int> wLinSearch = linSearch(unsorted, 158);
    */
    vector<int> found = binarySearch(sorted, 144);
    cout << "\nIndexe: ";
    for (int i = 0; i < int(found.size()); i++)
    {
        cout << found[i] << " ";
    }
    return 0; 
}