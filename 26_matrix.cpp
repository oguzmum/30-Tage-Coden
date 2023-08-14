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

vector<vector<float> > addMat(vector<vector<float> > mat1, vector<vector<float> > mat2)
{
    if(mat1.size() == mat2.size() && mat1[0].size() == mat2[0].size())
    {
        vector<vector<float> > erg(mat1.size(), vector<float>(mat1[0].size(), 0.0));
        for(int i = 0; i < mat1.size(); i++)
        {
            for(int j = 0; j < mat1[i].size(); j++)
            {
                erg[i][j] = mat1[i][j] + mat2[i][j];
            }
        }
        return erg; 
    }
    else
    {
        cout << "\nMatrix sind unterschiedlich groß, nicht addierbar";
        return vector<vector<float>>(); 
    } 
}

vector<vector<float> > subMat(vector<vector<float> > mat1, vector<vector<float> > mat2)
{
    if(mat1.size() == mat2.size() && mat1[0].size() == mat2[0].size())
    {
        vector<vector<float> > erg(mat1.size(), vector<float>(mat1[0].size(), 0.0));
        for(int i = 0; i < mat1.size(); i++)
        {
            for(int j = 0; j < mat1[i].size(); j++)
            {
                erg[i][j] = mat1[i][j] - mat2[i][j];
            }
        }
        return erg; 
    }
    else
    {
        cout << "\nMatrix sind unterschiedlich groß, nicht subtrahierbar";
        return vector<vector<float>>(); 
    } 
}

vector<vector<float> > multiplyMat(vector<vector<float> > mat1, vector<vector<float> > mat2)
{
    //multiplikation geht so: Zeile mal spalte; regel: Spalten von mat1 müssen spalten von mat2 entsprechen
    unsigned int rowMat1 = mat1.size();
    unsigned int colMat2 = mat2[0].size();

    if(rowMat1 == colMat2)
    {
        vector<vector<float> > erg(rowMat1, vector<float>(colMat2, 0.0));

        for(int i = 0; i < rowMat1; i++)
        {
            for(int j = 0; j < colMat2; j++)
            {
                for(int k = 0; k < mat1[0].size(); k++)
                {
                    erg[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return erg; 
    }
    else
    {
        cout << "\nZeilen und Spalten sind unterschiedlich Groß - nicht multiplizierbar";
        return vector<vector<float>>();
    }
}

float determinante(vector<vector<float>> mat)
{
    unsigned int size = mat.size();

    // Basisfall: 2x2-Matrix
    if (size == 2)
    {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    float erg = 0.0;
    for (size_t i = 0; i < size; ++i)
    {
        vector<vector<float>> submatrix(size - 1, vector<float>(size - 1, 0.0));
        for (int j = 1; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                if (k < i)
                    submatrix[j - 1][k] = mat[j][k];
                else if (k > i)
                    submatrix[j - 1][k - 1] = mat[j][k];
            }
        }
        erg += mat[0][i] * (i % 2 == 0 ? 1 : -1) * determinante(submatrix);
    }

    return erg;
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

    cout << "\nMatrix A: " << endl; 
    printMat(matrixA);
    cout << "\nMatrix B: " << endl; 
    printMat(matrixB);

    fflush(stdin); 
    char wahl;
    do
    {
        cout << "\nWas möchtest du machen?" << endl; 
        cout << "a Matrix A und B addieren\ns Matrix A und B subtrahieren\nm Matrix A und B multiplizieren\n";
        cout << "1 Determinante von Matrix A\n2 Determinante von Matrix B";
        cout <<"\nHier eingeben: ";
        cin >> wahl;
        if(wahl == 'a' || wahl == 's' || wahl == 'm' || wahl == '1' || wahl == '2')
        {
            break; 
        }
    } while (true);

    vector< vector<float> > ergMat;
    float det; 
    switch(wahl)
    {
        case 'a':
            ergMat = addMat(matrixA, matrixB); 
            cout << "\nResultierende matrix aus der addition: " << endl;
            printMat(ergMat);
            break;
        case 's':
            ergMat = subMat(matrixA, matrixB); 
            cout << "\nResultierende matrix aus der subtraktion: " << endl;
            printMat(ergMat);
            break; 
        case 'm':
            ergMat = multiplyMat(matrixA, matrixB); 
            cout << "\nResultierende matrix aus der Multiplikation: " << endl;
            printMat(ergMat);
            break; 
        case '1':   
            det = determinante(matrixA);
            cout << "\nDeterminante von Matrix A: " << det; 
            break; 
        case '2':
            det = determinante(matrixB);
            cout << "\nDeterminante von Matrix B: " << det; 
            break;
        default: 
            cout << "\nmmmmmogge";
    }
    
}

int main()
{
    askUser(); 
    return 0; 
}