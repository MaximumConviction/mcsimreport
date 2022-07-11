//Calculating the value of Pi using Monte Carlo simulation for Buffon's Needle
//Using MC sim to pick random sin(theta)
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

float * mcpi(int N, float t, float l); //defining function which returns Pi
float mcsin(float l); //defining function which returns a random sin(theta) between 0 and pi

int main () {
	
	int N=10; //number of throws
	float spacing=1; //line spacing
	float length=1; //needle length
	srand(time(NULL)); //initializing PNRG seed at current time
	
	for (int i=0; i<5; i++) {
		N*=10;
		//calling montecarlosim function to return the approximation of pi and the mc error
		float * pi=mcpi(N, spacing, length);			
		//printing out result
		cout<<"For "<<N<<" throws, pi was calculated to be "<<*pi<<", with an error of "<<*(pi+1)<<endl;
	}

return 0;
}

float * mcpi(int N, float t, float l) {
	float x[N]; //array to store random x for every throw
	float sin[N]; //array to store random sin(theta) for every throw
	int counter=0;
	float sumx1=0;
	float sumx2=0;
	float sumsin1=0;
	float sumsin2=0;
	static float result[2]; 
	
	for (int i=0; i<N; i++) {
		x[i]=(t/2)*(float)rand()/RAND_MAX; //generating random values of x between 0 and t/2
		sin[i]=mcsin(l); //returns random sin(theta) value for 0<=theta<=pi/2
		
		sumx1+=pow(x[i],2); //for mc error calculations
                sumx2+=x[i];
                sumsin1+=pow(sin[i],2);
                sumsin2+=sin[i];
		
		if (x[i]<=l*sin[i]/2) {
			counter++; //incrementing the counter if needle hits line
		}
	}
	
	float xerr=pow((sumx1/N)-pow(sumx2/N,2),0.5);
	float sinerr=pow((sumsin1/N)-pow(sumsin2/N,2),0.5);
	float proberr=pow(N,-0.5)*(xerr*(t/2)+sinerr);
	
	float prob=(float)counter/(float)N; //probability that needle hits a line
	result[0]=(2*l)/(t*prob); //manipulation to derive pi from equation 22
	result[1]=proberr*result[0]/prob;	
return result;
}

float mcsin(float l) {	
	float xx, yy, sin;
	//keeps generating new points in square until their radius falls within l/2
	while (true) {
	xx=pow((l/2)*(float)rand()/RAND_MAX,2);
	yy=pow((l/2)*(float)rand()/RAND_MAX,2);
		if (pow(xx+yy,0.5)<=l/2){
			break;
		}
	}

	sin=pow(xx/(xx+yy),0.5);
	
return sin;
}
