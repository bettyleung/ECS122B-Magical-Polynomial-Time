#include <iostream>
#include <complex>
#include <valarray>
#include <fstream>
#include <sstream>
#include "myt.h"



using namespace std;

typedef complex<double> Complex;
typedef valarray<Complex> complexArray;
const double PI = 3.1415926535897932;

void fft(complexArray& poly) {
    int n = poly.size();
    Complex t;

    if(n <= 1)
        return;
 
    complexArray evenPoly = poly[slice(0, n/2, 2)];
    complexArray oddPoly = poly[slice(1, n/2, 2)];
 
    fft(evenPoly);
    fft(oddPoly);

    for (int k = 0; k < n/2; ++k) {
        t = polar(1.0, -2 * PI * k / n) * oddPoly[k];
        poly[k] = evenPoly[k] + t;
        poly[k+n/2] = evenPoly[k] - t;
    }
}

int main(int argc, char* argv[]) {

    if(argc < 3 || argc > 3) {
        cerr << "ERROR 404: COMMANDLINE FORMAT SHOULD BE:" << endl;
        cerr << "./a.out input.txt output.txt" << endl;
        return 1;
    }

    int n;
    const char* fftInput = argv[1]; // Input file: 
                               // (1st line is integer n)
                               // (2nd line is double real coefficients)
    const char* fftOuput = argv[2]; // Output file: (x,y) == x + yi
    ifstream inFile(fftInput, std::ifstream::in); //cilk doesn't like normal ifstream
    ofstream outFile(fftOuput, std::ofstream::out); //cilk doesn't like normal ofstream
    if(!inFile || !outFile)
    {
        cout << "ERROR: Invalid file" << endl;
    }

    filebuf* pbuf = inFile.rdbuf(); //set up file pointer
    std::streamsize size = pbuf->pubseekoff(0,inFile.end); //determine size of file
    pbuf->pubseekoff(0, inFile.beg); //rewind
    char* contents = new char[size]; //get contents
    pbuf->sgetn (contents, size - 1); //puts size-1 into contents
    
    istringstream iss(contents); //make contents into a stringstream
    iss >> n; //take degree out, first line
    Complex *poly = new Complex[n];
    for(int i = 0; i < n; i++)
    {
        iss >> poly[i];
    }

    complexArray fftArray(poly,n);
    mytimer t;
    fft(fftArray); //time takes function's time
    double time = t.result();

    cout << "Standard FFT: " << time << endl;

    for (int i = 0; i < n; ++i)
    {
        outFile << fftArray[i] << " ";
    }
    outFile << "\n";

    inFile.close();
    outFile.close();
    delete contents;
    delete poly;
    return 0;
}
