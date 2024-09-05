#include<iostream>
#include<cmath>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<iomanip>

long double p(double m_o,double energy);

using namespace std;

int main()
{
	srand(time(0));
	double energy = sqrt( pow((rand()%256)*931.5*1e-6,2) + 25)/4;  //taking collision % randomly and calculating energy
	
	//-----------------------------------
	long double ul = 134.2 + 10,  ll =  134.2 - 10;
	
	/*we are assuming 4 particles are formed in an event and assuming for pion+ particle,taking mass of pion+ randomly */
	long double m_o = (rand()%(int)(ul - ll) + ll)*1e-6;     
	
	long double pz,theta,eta,h=0.01;
	
	int n = (2*p(m_o,energy)) / h;
	
	long double eta_data[n];
	

	ofstream ofs("data-momentum.txt");
	int j=0;
	
	// taking limit of z-component of momentum as modulus of total momentum

	for(long double x = -p(m_o,energy); x < p(m_o,energy); x += h)
	{
		pz = sqrt(pow(p(m_o,energy),2) - x*x); // calculating pz 
		theta = acos(pz/p(m_o,energy)); // calculating polar angle theta
		eta = -log(tan(theta/2)); // calculating pseudo-rapidity
		eta_data[j] = eta;
		ofs<<pz<<"\t\t"<<theta<<"\t\t"<<eta<<endl;
		j++;
	}
	ofs.close();
	
	ofstream ofs1("eta_vs_density.txt");
	//calculating no. of events in certain range of pseudo-rapidity
	for(double i=1 ; i <= 11; i+= 1)
	{
		int count=0;
		for(int k=0 ; k < n ;k++)
		{
			if( eta_data[k] > i-1 && eta_data[k] < i )
			{
				count++;
			}
		}
		ofs1<<i<<"\t\t"<<count<<endl;
	}
	ofs1.close();
	return 0;
}

long double p(double m_o,double energy)
{
	return sqrt(pow(energy,2) - pow(m_o,2));
}
