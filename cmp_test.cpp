//--------------------CONDENSED MATTER PHYSICS ASSIGNMENT-3---------------------
//SUBMIITED BY : YOGESH RANA
//ROLL-NO. : V23103
//DATE : 03rd MAY,2024
//------------------------------------------------------------------------------
#include<iostream>
#include<cmath>
#include<fstream>
#include<string>

double U_K(double K,double a,double u);

using namespace std;
int main()
{
	
	string of_name = "test"; 
	
	cout<<"Enter set of possible lattice vector's i.e., 'N' & 'U'\t:\t"<<endl;
	int N ; double u ;
	cin>>N>>u;
	double a = 1;
	double K[2*N+1];
	
	int j=0;
	//assigning value to 'K' i.e., lattice vectors (-N to N)
	for(int i = -N; i <=N ; i++)
	{
		K[j] = (2*3.14*i)/a;
		j++;
	}
	
	int r = 2*N+1, c = 2*N+1;
	double mat[r][c],k=0;
	
	ofstream ofs(of_name+".txt");
	//varying wave-vector i.e., "k"
	for(double k = (-3.14)/a ; k < (3.14/a) ; k += 0.1)
	{
		for(int i=0; i < r ; i++)
		{
			for(int j=0; j < c ; j++)
			{
				if (i == j) mat[i][j] = (0.5)*pow((k - K[i]),2);
				else mat[i][j] = U_K(K[j] - K[i],a,u);
			}
		}
		
		double ftr;
		//digonalizing matrix to find energy eigen-values
		for(int i=0;i<r;i++)
		{
			ftr =0;
			for(int j=0 ; j<c ;j++)
			{
				if(i>j)
				{
					ftr = mat[i][j]/mat[j][j];
					for( int k=0; k<c;k++)
					{
						mat[i][k] -= ftr*mat[j][k];
					}
				}
				
			}
		}
		
		for(int i=r-1;i>=0;i--)
		{	
			ftr =0;
			for(int j=c-1 ; j>=0 ;j--)
			{
				if(i<j) 
				{
					ftr = mat[i][j]/mat[j][j];
					for( int k=0; k<c;k++)
					{
						mat[i][k] -= ftr*mat[j][k];
					}
				}
			}

		}
		ofs<<k<<"\t\t";
		for(int i =0 ; i< r;i++)
		{
			for(int j =0 ; j < c ; j++)
			{	
				if(i == j) ofs<<mat[i][j]<<"\t\t";
			}	
		}
		ofs<<endl;		
	}
	ofs.close();
	
	
	ofstream plot(of_name+".gnu");
	plot<<"plot ";
	for(int i=0 ; i < 2*N+1 ; i++)
	{
		plot<< " \"" + of_name+".txt"+"\""<<" using 1:"<< i+2 <<" w l,";
	}
	plot<<"\nunset key\nset terminal pdf\n";
	plot<<"set output "<<"\"" <<of_name<<".pdf"<<"\""<<endl;
	plot<<"replot\n";
	plot<<"unset terminal\n";
	plot<<"replot\n";
	
	plot.close();
	
	return 0;
}

double U_K(double K,double a,double u)
{
	return u*exp(-K)/a;
}
