#include <iostream>
#include <stdlib.h>
#include <math.h>  

using namespace std;

int evalA(int x, int *A, int Asize ){
	int outputA = 0;
	for(int i = 0; i < Asize; i++){
		outputA = outputA + A[i] * pow(x, i); 	//the evaluation of A(x) at some point, x
	}

	return outputA;
}

int main(){

	int A[]={5, 0, 10, 6 };					//coefficients of A(x)
	int B[]={1, 2, 4};						//coefficients of B(x)
	int Asize = sizeof(A)/sizeof(A[0]);
	int Bsize = sizeof(A)/sizeof(B[0]);

	int d = Asize;
	if(Bsize > Asize)
		d = Bsize;

	//randomly generate 2d+1 create array of size n >= 2d + 1 points
	d = 2*d + 1;
	srand (time(NULL));
	int sizeN = rand() % d + 1; //pick n
	//pick the n number of point and evaluate A(x) and B(x) to get C(x)
	int C[sizeN];
	for(int x = 0; x<sizeN - 1; x++){	//hope its ok i choose x0, x1,..,xn be consecutive numbers since i technically can choose *some* points
		C[x] = evalA(x, A, Asize);
	}

 	cout << "size: ";
 	cout << sizeN;
	cout << " and C(x) is:" << endl;

	for(int i=0; i< sizeN; i++){
		cout << C[i]; 
		cout << ", ";
	}
	cout << endl;

	//evaluate A(x) at 2d +1 points
}

