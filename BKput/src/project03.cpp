#include<Rcpp.h>
#include<vector>
#include"MyOption.h"
#include<ctime>
#include<cstdlib>

using std::vector;
using std::cout;
using std::cin;

using namespace Rcpp;

// [[Rcpp::export]]
double getPutDownAndIn(int nInt = 100,
                       double Strike = 100,
                       double Spot = 95,
                       double Vol = 0.2,
                       double Rfr = 0.06,
                       double Expiry = 0.5,
                       int nReps = 100){

	// // set the seed
	srand( time(NULL) );

	// create a new instance of class
	MyOption myOption(nInt, Strike, Spot, Vol, Rfr, Expiry);

	// call the method to get price
	double price =	myOption.getPutDownAndIn(nReps);

	// return the price
	return price;
}
