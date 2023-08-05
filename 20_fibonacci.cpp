/*Logik:Zahl vorher mit aktueller Zahl addieren
        also: (n-1) + n = (n+1)

    Fibonacci Folge: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55...
*/

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std; 


void printNumbers(vector<int> numbers)
{
    for(int i = 0; i < numbers.size(); i++)
    {
        cout << numbers[i] << ", "; 
    }
}

vector<int> fibonacci(int n)
{
    vector<int> fib; 
    int nFirst = 0, nSecond = 1, sum = 0; 
    fib.push_back(nFirst);
    fib.push_back(nSecond); 
    for(int i = 1; i < n; i++)
    {
        sum = nFirst + nSecond; 
        fib.push_back(sum); 
        nFirst = nSecond; 
        nSecond = sum; 
    }
    return fib; 
}


int fibonacciRecursive(int n)
{
    if(n == 0 || n == 1)
    {
        return n; 
    }
    else
    {
        return (fibonacciRecursive(n-1) + fibonacciRecursive(n-2));
    }
}

int main()
{
    unsigned int wahl; 
    while(true)
    {
        cout << "\nWie viele Iterationen: (0) -> beenden: "; 
        cin >> wahl;
        if(wahl == 0)
        {
            break; 
        }

        vector<int> fibN = fibonacci(wahl); 

        int i = 0; 
        vector<int> fibR; 
        while(i <= wahl)
        {
            fibR.push_back(fibonacciRecursive(i)); 
            i++;
        }

        cout << "\nIterativ: ";
        printNumbers(fibN); 

        cout << "\nRekursiv: ";
        printNumbers(fibR); 
    }
    return 0; 
}