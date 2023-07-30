#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std; 

int sortiert1[20] = {11, 59, 80, 89, 91, 97, 102, 116, 122, 123, 144, 144, 158, 247, 249, 253, 273, 299, 399, 479};
int sortiert2[20] = {1, 20, 21, 27, 29, 31, 32, 43, 63, 83, 156, 212, 307, 314, 314, 334, 388, 409, 463, 490};

vector<int> mergeThese(vector<int> first, vector<int> second)
{
    vector<int> merged;
    int i = 0; 
    int j = 0; //um indexe der zuletzt benutzen Elemente aus den Arrays zu speichern

    //beide Arrays/Vectors durchgehen und entsprechend zahl an passender stelle in merged einsetzen
    while (i < int(first.size()) && j < int(second.size())) 
    {
        //das von first ist kleiner öder gleich von second, dann wird das bei merged eingefügt, sonst das von second
        if (first[i] <= second[j]) 
        {
            merged.push_back(first[i]);
            i++;
        } 
        else 
        {
            merged.push_back(second[j]);
            j++; 
        }
    }

    return merged;
}

int main()
{
    vector<int> un1(sortiert1, sortiert1 + (sizeof(sortiert1)/sizeof(sortiert1[0]))); 
    vector<int> un2(sortiert2, sortiert2 + (sizeof(sortiert2)/sizeof(sortiert2[0]))); 
    vector<int> gemerged = mergeThese(un1, un2); 
    for(int i = 0; i < int(gemerged.size()); i++)
    {
        cout << gemerged[i] << " "; 
    }

    return 0; 
}