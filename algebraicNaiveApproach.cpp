#include <iostream>
#include <complex>
#include <valarray>
#include <fstream>
#include <sstream>
 

using namespace std;
typedef complex<double> Complex;
typedef valarray<Complex> complexArray;

int main(int argc, char* argv[]){

/*
    if(argc < 3 || argc > 3) {
        cerr << "ERROR 404: COMMANDLINE FORMAT SHOULD BE:" << endl;
        cerr << "./a.out input.txt output.txt" << endl;
        return 1;
    }
*/

   if(argc < 3 || argc > 3) {
        cerr << "ERROR 404: COMMANDLINE FORMAT SHOULD BE:" << endl;
        cerr << "./a.out input.txt output.txt" << endl;
        return 1;
    }

    string fftInput = argv[1]; // Input file: 
                               // (1st line is integer n)
                               // (2nd line is double real coefficients)
    string fftOuput = argv[2]; // Output file: (x,y) == x + yi

    ifstream inFile;
    ofstream outFile;
    
    inFile.open(fftInput.c_str());
    outFile.open(fftOuput.c_str());
    
    string buffer;
    string::size_type sz;
    int n;
    
    getline(inFile,buffer);    // first line of input file
    n = stoi(buffer, &sz);     // n is degree of polynomial
   // Complex *poly1 = new Complex[n];
    int A[n];

    getline(inFile,buffer);    // second line containing all coefficients
    istringstream iss(buffer);
    string currentComplex;
    int i = 0;
    while(getline( iss, currentComplex, ' ')) {
        
        A[i] = stod(currentComplex);
        
        i++;
    }
   // cout << endl;
    //complexArray A(poly1,n);

    //Complex *poly2 = new Complex[n];
    int B[n];
    string buffer2;
    getline(inFile,buffer2);    // third line containing all coefficients
    istringstream iss2(buffer2);
    string currentComplex2;
    i = 0;
    while(getline( iss2, currentComplex2, ' ')) {
        B[i] = stod(currentComplex2);
        //cout << B[i] << " ";
        i++;
    }

    //complexArray B(poly2,n);

	//int A[]={5, 0, 1  };					
	//int B[]={1, 2, 4 };						
	int Asize = sizeof(A)/sizeof(A[0]);
	int Bsize = sizeof(A)/sizeof(B[0]);

	int Csize = Asize + Bsize - 1;
	int C[Csize];
	//int C[Csize]  = {0};

	for(int ii = 0; ii < Csize; ii++){
		C[ii] = 0;
	}

	for(int i=0; i < Asize; i++){			//mutliplying the coefficients together
		
		for(int j = 0; j < Bsize; j++){
			C[i+j] = C[i+j] + (A[i] * B[j]);	
		}
		//add to C(x)
	}
	 //cout << "C(x): ";
/*	for(int k = 0; k < Csize; k++){
		cout << C[k];
		cout << " ";
	}*/
	//cout << endl;



    for (int kk = 0; kk < Csize; ++kk)		//print to output file
        outFile << C[kk] << " ";
    outFile << "\n";

    inFile.close();
    outFile.close();

/*	
    for (int i = 0; i < 4; ++i)
        outFile << fftArray[i] << " ";
    outFile << "\n";

    inFile.close();
    outFile.close();*/

}

