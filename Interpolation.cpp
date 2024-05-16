/*
 *  Interpolation.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-09.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "Interpolation.h"

double
Interpolation::calcThreeTabularInterpolation(double x0,
											 double x1,
											 double x2,
											 double n)
{
	double a = x1 - x0;
	double b = x2 - x1;
	double c = b - a;
	double x = x1 + ( n / 2e+00 ) * ( a + b + n * c );
	
	return x;
}
