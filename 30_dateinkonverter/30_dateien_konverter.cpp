#include <iostream>
#include <string>
#include <Magick++.h>

using namespace std;

int main() 
{
    Magick::InitializeMagick(nullptr);

    string inputPath = "cpp.jpeg";
    string outputPath = "c.pdf";

    try 
    {
        Magick::Image inputImage(inputPath);

        inputImage.write(outputPath);

        cout << "\nKonvertiert zu PDF: " << outputPath << endl;
    } 
    catch (Magick::Exception& ex) 
    {
        cerr << "\nFehler: " << ex.what() << endl;
        return 1;
    }

    return 0;
}

/* über Terminal so ausführen: 

g++ -o 30_dateien_konverter 30_dateien_konverter.cpp -std=c++11 -I/opt/homebrew/include/ImageMagick-7 -L/opt/homebrew/lib -lMagick++-7.Q16HDRI

./30_dateien_konverter 
*/