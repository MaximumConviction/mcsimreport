//Calculating the value of Pi using Monte Carlo simulation for Buffon's Needle
//Attempt #1 to not use pi in calculation
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

float montecarlosim(int N, float t, float l); //defining function which returns Pi

int main () {
	
	int N=10; //number of throws
	float spacing=1; //line spacing
	float length=1; //needle length
	srand(time(NULL)); //initializing PNRG seed at current time
	
	for (int i=0; i<5; i++) {
		N*=10;
		//calling montecarlosim function to return the approximation of pi
		float piapprox=montecarlosim(N, spacing, length);			
		//printing out result
		cout<<"For "<<N<<" throws, pi was calculated to be "<<piapprox<<endl;
		//converges to 4 
	}

return 0;
}

float montecarlosim(int N, float t, float l) {
	float x[N]; //array to store random x for every throw
	float sin[N]; //array to store random sin for every throw
	int counter=0;
	
	for (int i=0; i<N; i++) {
		x[i]=(t/2)*(float)rand()/RAND_MAX; //generating random values of x between 0 and t/2
		sin[i]=(float)rand()/RAND_MAX; //generating random values of sin between 0 and 1
		
		if (x[i]<=l*sin[i]/2) {
			counter++; //incrementing the counter if needle hits line
		}
	}
	
	float prob=(float)counter/(float)N; //probability that needle hits a line
	float pi=(2*l)/(t*prob); //manipulation to derive pi from equation 22
		
return pi;
}
