#include"MyOption.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include"Random1.h"
#include <Rcpp.h>

using namespace std;


//definition of constructor
MyOption::MyOption(
  int nInt_,
  double strike_,
  double spot_,
  double vol_,
  double r_,
  double expiry_){
  nInt = nInt_;
  strike = strike_;
  spot = spot_;
  vol = vol_;
  r = r_;
  expiry = expiry_;
  generatePath();
}

//method definition
void MyOption::generatePath(){
  double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
  double cumShocks = 0;
  thisPath.clear();
  
  for(int i = 0; i < nInt; i++){
    cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * GetOneGaussianByBoxMuller());
    thisPath.push_back(spot * exp(cumShocks));
  }
}

//method definition
double MyOption::getMinFromPath(){
  
  double minVal = thisPath[0];
  
  for(int i = 0; i < nInt; i++){
    if (thisPath[i] < minVal) {
      minVal = thisPath[i];
    }
  }
  
  return minVal;
}


double MyOption::getPutDownAndIn(int nReps){
  
  double rSum = 0.0;
  double thisMin = 0.0;
  double barrier = 85;
  
  for(int i = 0; i < nReps; i++){
    generatePath();
    thisMin = getMinFromPath();
    if (thisMin < barrier){
      double thisPayoff = strike - thisPath[i-1];
      if (thisPayoff > 0) rSum += thisPayoff;
    }
  }
  
  return exp(-r * expiry) * rSum / double(nReps);
  
}


//overloaded operator ();
double MyOption::operator()(char char1, char char2, int nReps){
  if ((char1 == 'A') & (char2 =='C')) return getPutDownAndIn(nReps);
  else return -99;
}
