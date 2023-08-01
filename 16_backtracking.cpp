#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std; 

char freeMark = ' '; //in diese "zellen" darf man rein
char escapeMark = 'E'; //das Ziel
vector<string> field; //hier das spielfeld speichern

void printField()
{
    for(int i = 0; i < int(field.size()); i++)
    {
        for(int x = 0; x < int(field[i].size()); x++)
        {
            cout << field[i][x]; 
        }
        cout << endl;
    }
}

vector<string> readField()
{
    ifstream txtFile("forBacktracking.txt"); 

    if(!txtFile.is_open())
    {
        cerr << "\nDatei konnte nicht geöffnet werden" << endl;
        exit(0);
    }

    vector<string> lines;
    string line; 
    while(getline(txtFile, line))
    {
        lines.push_back(line);  
    } 
    txtFile.close(); 

    return lines; 
}

bool isFree(int row, int col)
{
    if(field[row][col] == freeMark || field[row][col] == escapeMark)
    {
        return true;
    }
    else
    {
        return false; 
    }
}

bool isDestination(int row, int col)
{
    cout << "\nIn isDes: " << field[row][col] << " " << "escapeMark"; 
    if(field[row][col] == escapeMark)
    {
        cout << "\nist Escape"; 
        return true; 
    }
    else
    {
        cout << "HAllo"; 
        return false; 
    }
}

bool isInField(int row, int col)
{
    if(row >= 0 && row < int(field[row].size()) && col >= 0 && col < int(field.size()))
    {
        return true;
    }
    else
    {
        return false; 
    }
    
}

vector<pair<int, int> > backtrack(int row, int col, vector<pair<int, int> >& route)
{
    route.push_back((make_pair(row, col)));
    
    if (isDestination(row, col))
    {
        return route;
    }

    //hatte nachbarn vorher so: {{0, 1}, {0, -1}, {1, 0}, {-1, 0}} -- da wurde dann die wirklich kürzeste Route nicht gefunden; 
    //bei dieser "NachbarReihenfolge" findet er die tatsächlich kürzeste Route
    vector<pair<int, int> > nachbarn = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 
    vector<vector< pair<int, int> > > possibleRoutes;
    for (const auto& n : nachbarn) 
    {
        int rowNumberNew = row + n.first; //n "übernimmt" quasi nachbarn, statt nachbarn[?].first kann man n.first schreiben
        int columnNumberNew = col + n.second;

        //gucken ob man sich noch im feld befindet, und ob man noch schon an der neu berechneten Stelle war oder nicht
        if (isFree(rowNumberNew, columnNumberNew) && isInField(rowNumberNew, columnNumberNew) 
        && find(route.begin(), route.end(), make_pair(rowNumberNew, columnNumberNew)) == route.end())
        {
            vector<pair<int, int>> temp = backtrack(rowNumberNew, columnNumberNew, route); //rekursiver aufruf
            if (!temp.empty()) 
            {
                possibleRoutes.push_back(temp);
            }
        }
    }

    if (!possibleRoutes.empty()) 
    {   
        int minSteps = possibleRoutes[0].size(); //etwas nehmen das als vergleich für kürzesten weg
        vector<pair<int, int>> shortest = possibleRoutes[0]; //die kooridnaten diesen weges
        for (int i = 1; i < possibleRoutes.size(); ++i) 
        { //die möglichen routen durchgehen und gucken ob es etwsa kürzeres gibt
            if (possibleRoutes[i].size() < minSteps) 
            {
                //etwas kürzeres gefunden
                minSteps = possibleRoutes[i].size();
                shortest = possibleRoutes[i];
            }
        }
        return shortest;
    }
    else
    {
        //keine route gefunden
        return {};
    }
}

int main()
{
    //hier startkoordinaten einstellen
    vector<pair <int, int> > firstPair(1, make_pair(1, 1));
    field = readField(); 
    printField();
    
    vector<pair<int, int>> route = backtrack(firstPair[0].first, firstPair[0].second, firstPair); 

    //den gefundenen Weg im Feld markieren
    for (int i = 0; i < int(route.size()) - 1; ++i) 
    {
        field[route[i].first][route[i].second] = '.';
    } 
    printField();


    cout << "\nKoordinaten des kürzesten Weges:\n";
    for (const auto& p : route) 
    {
        cout << p.first << " " << p.second << "\n";
    }
    

    return 0; 
}