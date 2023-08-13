#include <iostream>
#include <vector>

using namespace std; 

void printMat(vector<vector<float> > mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[i].size(); j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<float> > createMat(unsigned int z, unsigned int s)
{
    //z zeilen, und s spalten mir 0 gefüllt
    vector<vector<float> > matrix(z, vector<float>(s, 0));
    for(int i = 0; i < z; i++)
    {
        vector<float> zeile(s); //s weil eine zeile hat s spalten :) 
        float wert; 
        cout << "\nZeile " << i << " :";
        for(int x = 0; x < s; x++)
        {
            cout << "\nElement " << x << " :";
            cin >> wert; 
            zeile[x] = wert;
        }
        matrix[i] = zeile;
    }
    return matrix; 
}

void askUser()
{
    unsigned int za, sa, zb, sb; 
    cout << "\nMatrix A Zeilen: ";
    cin >> za; 
    cout << "\nMatrix A Spalten: ";
    cin >> sa; 
    vector< vector<float> > matrixA = createMat(za, sa); 

    cout << "\nMatrix B Zeilen: ";
    cin >> zb; 
    cout << "\nMatrix B Spalten: ";
    cin >> sb; 
    vector< vector<float> > matrixB = createMat(zb, sb);

    printMat(matrixA);
    printMat(matrixB);
}

int main()
{
    askUser(); 
    return 0; 
}