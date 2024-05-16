/*
 *  DynamicalUniversalTime.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "DynamicalUniversalTime.h"

double
DynamicalUniversalTime::calcDeltaTInSec(int year)
{
	double t = ( year - 2.000e+03 ) / 1.00e+02;
	
	double deltaT;
	
	if ( year < 9.48e+02 )
	{
		deltaT = 2.177e+03
		+ ( 4.97e+02 * t )
		+ ( 4.41e+01 * t * t );
	}
	else
	{
		deltaT = 1.02e+02
		+ ( 1.02e+02 * t )
		+ ( 2.53e+01 * t * t )
		+ ( 3.7e-01 * ( year - 2.100e+03 ) );
	}
	
	return deltaT;
}
