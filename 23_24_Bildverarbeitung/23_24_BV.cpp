/*Hatte heute nicht viel zeit, & musste erst OpenCV installieren, Quelle: https://youtu.be/Ozc3zWJ_NhQ

erst am terminal homewbre installieren, danach opencv

dann im terminal in vscode: 
touch CMakeLists.txt

das dann in die entstandene txt datei
cmake_minimum_required(VERSION 3.10)
project(MyProject)
find_package(OpenCV REQUIRED)
add_executable(MyProject main.cpp)
target_link_libraries(MyProject ${OpenCV_LIBS})

so projekt kompilieren über terminal:
mkdir build
cd build
cmake .. //dafür musste ich erst cmake installieren(über terminal macos)
make
./MyProject
*/


//selbst 
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

float mittelwert(Mat bild)
{
    //formel: mw = 1/(Pixelanzahl) * (alle grauwerte im bild aufsummieren)
    float mw;
    float summe = 0; 

    for(int row = 0; row < bild.rows; row++)
    {
        for(int col = 0; col < bild.cols; col++)
        {
            summe += bild.at<uchar>(row, col); 
        }
    }
    
    mw = summe/(bild.rows * bild.cols); 
    return mw; 
}

float varianz(Mat bild)
{
    //formel: var = 1/(Pixel) * (gw - mw)^2   ; gw = Grauwert, mw = Mittelwert
    float summe = 0; 
    float var;
    float mw = mittelwert(bild); 

    for(int row = 0; row < bild.rows; row++)
    {
        for(int col = 0; col < bild.cols; col++)
        {
            summe += pow((bild.at<uchar>(row, col) - mw), 2); 
        }
    }
    var = summe/(bild.rows * bild.cols);
    return var; 
}

void histogrammOpenCV(Mat bild)
{
    vector<Mat> channels;
    split(bild, channels); // Split the image into its color channels

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;

    for (int i = 0; i < channels.size(); i++)
    {
        //eig ist das bild schwarzweiss, aber musste rgb abdecken damit es kompiliert
        //deswegen das mit "channels"
        Mat hist;
        calcHist(&channels[i], 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

        int histWidth = 1920, histHeight = 1080; //größe des Fensters, wo das Histogramm dann ausgegeben wird
        int binWidth = cvRound((double)histWidth / histSize);

        Mat histImage(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));

        normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

        for (int j = 1; j < histSize; j++)
        {
            line(histImage, Point(binWidth * (j - 1), histHeight - cvRound(hist.at<float>(j - 1))),
                 Point(binWidth * (j), histHeight - cvRound(hist.at<float>(j))),
                 Scalar(0, 0, 255), 2, 8, 0);
        }

        imshow("Histogram for Channel " + to_string(i), histImage);
    }
}

void histogramm(Mat bild)
{
    vector<float> grauwerte(256, 0.0); 
    //grauwerte aufaddieren
    for(int row = 0; row < bild.rows; row++)
    {
        for(int col = 0; col < bild.cols; col++)
        {
            grauwerte[bild.at<uchar>(row, col)] += 1;
            //den wert als Index nutzen und die grauwerte aufaddieren
        }
    }

    vector<float> relGW(256, 0.0); 
    //relative häufigkeit
    //256; weil max GW ist 255, aber evtl gibt es weniger nicht so hohe werte in einem Bild
    for(int i = 0; i < grauwerte.size(); i++)
    {
        relGW[i] = grauwerte[i]/(bild.rows * bild.cols);
        cout << "\nGrauwert: " << i << " Häufigkeit: " << relGW[i] * 100 << "%";
    }
    //ich weiss nicht, ob man das geplottet bekommet, mache es jetzt erst als ausgabe auf dem terminal
    
    cout << endl; 

    int maxFrequency = *max_element(grauwerte.begin(), grauwerte.end());
    
    // histogramm als Text printen mit ***
    for(int i = 0; i < grauwerte.size(); i++)
    {
        float relFrequency = grauwerte[i] / maxFrequency;
        int asterisksCount = static_cast<int>(relFrequency * 50); // Scale to fit the terminal

        cout << i << ": ";
        for (int j = 0; j < asterisksCount; j++)
        {
            cout << "*";
        }
        cout << endl;
    }   


    //plotten als Bild :) - mitHilfe von ChatGPT gemacht
    int plotWidth = 1920;
    int plotHeight = 1080;
    Mat plot(plotHeight, plotWidth, CV_8UC3, Scalar(255, 255, 255));

    int numBins = relGW.size();
    int binWidth = cvRound(static_cast<double>(plotWidth) / numBins);

    float mf = *max_element(relGW.begin(), relGW.end());

    for (int i = 0; i < numBins; i++)
    {
        int binHeight = cvRound(static_cast<double>(relGW[i]) / mf * (plotHeight - 50));
        rectangle(plot, Point(i * binWidth, plotHeight - binHeight - 50), Point((i + 1) * binWidth, plotHeight - 50), Scalar(0, 0, 255), -1);
    }

    // x achse
    line(plot, Point(0, plotHeight - 50), Point(plotWidth, plotHeight - 50), Scalar(0, 0, 0), 2);

    // y achse
    line(plot, Point(50, 0), Point(50, plotHeight - 50), Scalar(0, 0, 0), 2);

    // X achsen beschriftung
    for (int i = 0; i < numBins; i+=10)
    {
        int x = i * binWidth + binWidth / 2;
        putText(plot, to_string(i), Point(x, plotHeight - 25), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
    }

    // y achse bschriftung
    for (int i = 0; i <= 10; i++)
    {
        int y = plotHeight - 50 - i * (plotHeight - 50) / 10;
        putText(plot, to_string(i * 10) + "%", Point(25, y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
    }

    imshow("Histogram Plot", plot);
}

void histoEbnen(Mat bild)
{
    /*ziel von histogramm ebnen: kontrast im bild erhöhen
        wie: das normale historgamm kummulieren und damit neue grauwerte (bzw. Farbwerte) berechnen - das ins neue Bild schreiben
    */

    vector<float> grauwerte(256, 0.0); 
    //grauwerte aufaddieren
    for(int row = 0; row < bild.rows; row++)
    {
        for(int col = 0; col < bild.cols; col++)
        {
            grauwerte[bild.at<uchar>(row, col)] += 1;
            //den wert als Index nutzen und die grauwerte aufaddieren
        }
    }

    vector<float> relGW(256, 0.0); 
    //relative häufigkeit
    //256; weil max GW ist 255, aber evtl gibt es weniger nicht so hohe werte in einem Bild
    for(int i = 0; i < grauwerte.size(); i++)
    {
        relGW[i] = grauwerte[i]/(bild.rows * bild.cols);
        cout << "\nGrauwert: " << i << " Häufigkeit: " << relGW[i] * 100 << "%";
    }

    vector<float> kumHisto(256, 0.0); 
    float summe = 0; 
    cout << endl; 
    for(int i = 0; i < relGW.size() ; i++)
    {
        cout << "Grauwerte: " << relGW[i] << endl;
        summe += relGW[i]; //kummulieren
        kumHisto[i] = summe; //an jeweilige stelle zuweisen
        cout << "Kumhisto: " << kumHisto[i] << endl;
        cout << "\nSumme: " << summe; 
    }

    
    Mat geebnet(bild.rows, bild.cols, CV_8UC1);  
    for(int i = 0; i < bild.rows; i++)
    {
        for(int x = 0; x < bild.cols; x++)
        {
            //formel: runden((256-1)*kummulierte Histogramm(gw))
            int newPixelValue = round(255 * kumHisto[bild.at<uchar>(i, x)]);
            geebnet.at<uchar>(i, x) = newPixelValue;
        }
    }

    // imshow("original Bild", bild); 
    
    // imshow("Histogramm geebnet", geebnet); 
    //ich bin 100% sicher, dass der rechenweg bis hierhin richtig ist - aber iwie ist diese ausgabe dann nur das erste linke drittel

    //versuchen mit resize
    namedWindow("Original Bild", WINDOW_NORMAL); // Create a resizable window
    imshow("Original Bild", bild); 

    namedWindow("Histogramm geebnet", WINDOW_NORMAL); // Create a resizable window
    imshow("Histogramm geebnet", geebnet); 

    // You can also resize the windows to a specific size if desired
    resizeWindow("Original Bild", bild.cols, bild.rows);
    resizeWindow("Histogramm geebnet", bild.cols, bild.rows);


    //imwrite("geebnet.jpg", geebnet);

    //bringt iwie alles nix, wird immer noch nur linkes drittel angeziegt :(
}

int main(int argc, char** argv)
{
    Mat bild = imread("seerose512.jpg");

    if(bild.empty())
    {
        cerr << "\nBild konnte nicht geöffnet werden";
        return -1; 
    }
    imshow("geöffnetes Bild", bild); 

    // float mw = mittelwert(bild); 
    // cout << "\nMittelwert: " << mw; 

    // Scalar mwCV = mean(bild); //von opencv selbst, zum vergleichen
    // cout << "\nVon Opencv Mittelwert: " << mwCV[0]; 


    // float var = varianz(bild); 
    // cout << "\nVarianz: " << var; 

    // histogramm(bild); 
    
    // histogrammOpenCV(bild); //mit calcHist von OpenCV


    histoEbnen(bild);

    waitKey(0); 
    destroyAllWindows();
    return 0; 
}

/*
//vom tutorial
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

    // Load the video file
    VideoCapture cap("testvideo.mp4");

    // Check if the video file was opened successfully
    if (!cap.isOpened()) {
        cerr << "Error: could not open video file" << endl;
        return -1;
    }

    // Create a window to display the video frames
    namedWindow("Video", WINDOW_NORMAL);

    // Loop over the video frames and display them in the window
    while (true) {

        // Read the next frame from the video file
        Mat frame;
        cap.read(frame);

        // Check if the frame was read successfully
        if (frame.empty()) {
            break;
        }

        // Display the current frame in the window
        imshow("Video", frame);

        // Wait for a key press (or 30 milliseconds) to allow the frame to be displayed
        if (waitKey(30) >= 0) {
            break;
        }
    }

    // Release the video file and destroy the window
    cap.release();
    destroyAllWindows();

    return 0;
}
*/