#include <Rcpp.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Random1.h"
using namespace Rcpp;
using namespace std;


double GetOneGaussianByBoxMuller()
{
  double result;
  
  double x;
  double y;
  
  double sizeSquared;
  do
  {
    x = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
    sizeSquared = x * x + y * y;
  }
  while
    ( sizeSquared >= 1.0);
  
  result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);
  
  return result;
  
}



double SimpleMonteCarlo1(double Expiry,
                         double Strike,
                         double Spot,
                         double Vol,
                         double r,
                         unsigned long NumberOfPaths);

// [[Rcpp::export]]
double getDownInPutPrice(
    double Expiry = 0.5,
    double Strike = 100,
    double Spot   = 95,
    double Vol    = 0.2,
    double r      = 0.06,
    unsigned long nReps = 100) {
  
  
  double result = SimpleMonteCarlo1(Expiry,
                                    Strike,
                                    Spot,
                                    Vol,
                                    r,
                                    nReps);
  return result;
}


// definition of the function
double SimpleMonteCarlo1(double Expiry,
                         double Strike,
                         double Spot,
                         double Vol,
                         double r,
                         unsigned long NumberOfPaths){
  
  double variance = Vol * Vol * Expiry;
  double rootVariance = sqrt(variance);
  double itoCorrection = -0.5 * variance;
  
  double movedSpot = Spot * exp(r * Expiry + itoCorrection);
  double thisSpot;
  double runningSum = 0;
  
  bool activateOption = false;
  double barrier = 70;
  
  for (unsigned long i = 0; i < NumberOfPaths; i++)
  {
    double thisGaussian = GetOneGaussianByBoxMuller();
    thisSpot = movedSpot * exp(rootVariance * thisGaussian);
    if (thisSpot < barrier) activateOption = true;
    if (activateOption) {
      double thisPayoff = Strike - thisSpot;
      if (thisPayoff > 0) runningSum += thisPayoff;
    }
  }
  
  double mean = runningSum / NumberOfPaths;
  mean = mean * exp(-r * Expiry);
  return mean;
}


