#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std; 

int randomIndex(int max)
{
    srand(time(0)); 
    return rand() % (max-1); //max -1, weil size von 1-? ausgeht, indexe aber von 0-(?-1) gehen :) 
}

vector<string> readFile(const string& fileName)
{
    ifstream duden(fileName);
    if(!duden.is_open())
    {
        cerr << "\nDatei konnte nicht geöffnet werden" << endl;
        exit(0);
    }

    string word;
    vector<string> allWords;

    for(string line; getline(duden, line);)
    {
        allWords.push_back(line);
    }
    duden.close();

    srand(time(0));
    if(allWords.empty())
    {
        cerr << "\nKeine Wörter gefunden";
        exit(0);
    }

    return allWords; 
}

void generateSentence()
{
    //ich finde keine txt datein im netz mit prädikaten, subjekten, adjektiven etc; werde deswegen englische Wörter benutzen
    //"normaler" satzaufbau: Subjekt, Prädikat, Objekt; zB Ich esse ein Apfel
    vector<string> pronoun = readFile("txt_dateien/pronoun.txt"); 
    vector<string> adverb = readFile("txt_dateien/adverb.txt");
    vector<string> verb = readFile("txt_dateien/verb.txt"); 
    vector<string> prepo = readFile("txt_dateien/preposition.txt"); 
    vector<string> adjective = readFile("txt_dateien/adjective.txt"); 
    vector<string> noun = readFile("txt_dateien/noun.txt"); 

    cout << pronoun[randomIndex(int(pronoun.size()))] << " ";
    cout << adverb[randomIndex(int(adverb.size()))] << " ";
    cout << verb[randomIndex(int(verb.size()))] << " ";
    cout << prepo[randomIndex(int(prepo.size()))] << " "; 
    cout << adjective[randomIndex(int(adjective.size()))] << " ";
    cout << noun[randomIndex(int(noun.size()))] << " ";
}

int main()
{
    generateSentence(); 
    return 0;   
}