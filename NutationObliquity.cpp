/*
 *  NutationObliquity.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <iostream>

#include "JulianDay.h"
#include "MathUtil.h"

#include "NutationObliquity.h"

double
NutationObliquity::calcMeanObliquityInArcsec(double jde)
{
	double t = ( jde - 2.451545e+06 ) / 3.6525e+04;
	
	double u = 1e-02 * t;
	
	double epsilon0 = 8.4381448e+04;
	
	double pow_u = 1e+00;
	
	for ( int i = 0 ; i < COEFF_OBLIQUITY_LIST_SIZE ; ++i )
	{
		pow_u *= u;
		epsilon0 += NutationObliquityNs::coeffObliquityList[i] * pow_u;
	}
	
	return epsilon0;
}

double
NutationObliquity::calcNutationLongitudeInArcsec(double jde)
{
	double t = ( jde - 2.451545e+06 ) / 3.6525e+04;
	
	// Mean elongation of the Moon from the Sun
	double d = 2.9785036e+02
		+ ( 4.45267111480e+05 * t )
		- ( 1.9142e-03 * t * t )
		+ ( t * t * t / 1.89474e+05 );
	
	// Mean anomaly of the Sun (Earth)
	double m = 3.5752772e+02
		+ ( 3.5999050340e+04 * t )
		- ( 1.603e-04 * t * t )
		- ( t * t * t / 3e+05 );
	
	// Mean anomaly of the Moon
	double mp = 1.3496298e+02
		+ ( 4.77198867398e+05 * t )
		- ( 8.6972e-03 * t * t )
		- ( t * t * t / 5.625e+04 );
	
	// Moon's argument of latitude
	double f = 9.327191e+01
		+ ( 4.83202017538e+05 * t )
		- ( 3.6825e-03 * t * t )
		+ ( t * t * t / 3.2727e+05 );
	
	// Longitude of the ascending node of the Moon's mean orbit on the ecliptic,
	// measured from the mean equinox of the date
	double omega = 1.2504452e+02
		- ( 1.934136261e+03 * t )
		+ ( 2.0708e-03 * t * t )
		+ ( t * t * t / 4.5e+05 );
	
	double trigArgElements[5] = {MathUtil::convDegToRad(d),
		MathUtil::convDegToRad(m),
		MathUtil::convDegToRad(mp),
		MathUtil::convDegToRad(f),
		MathUtil::convDegToRad(omega)};
	double trigArg;
	
	double deltaPsi = 0.0;
	
	for ( int i = 0 ; i < TABLE22A_SIZE ; ++i )
	{
		trigArg = 0.0;
		for ( int j = 0 ; j < 5 ; ++j )
		{
			trigArg += trigArgElements[j] * NutationObliquityNs::argumentTable[i][j];
		}
		deltaPsi += ( NutationObliquityNs::coeffSin[i][0] + ( NutationObliquityNs::coeffSin[i][1] * t) )
			* sin ( trigArg );
	}
	
	return deltaPsi;
}

double
NutationObliquity::calcNutationObliquityInArcsec(double jde)
{
	double t = ( jde - 2.451545e+06 ) / 3.6525e+04;
	
	// Mean elongation of the Moon from the Sun
	double d = 2.9785036e+02
		+ ( 4.45267111480e+05 * t )
		- ( 1.9142e-03 * t * t )
		+ ( t * t * t / 1.89474e+05 );
	
	// Mean anomaly of the Sun (Earth)
	double m = 3.5752772e+02
		+ ( 3.5999050340e+04 * t )
		- ( 1.603e-04 * t * t )
		- ( t * t * t / 3e+05 );
	
	// Mean anomaly of the Moon
	double mp = 1.3496298e+02
		+ ( 4.77198867398e+05 * t )
		- ( 8.6972e-03 * t * t )
		- ( t * t * t / 5.625e+04 );
	
	// Moon's argument of latitude
	double f = 9.327191e+01
		+ ( 4.83202017538e+05 * t )
		- ( 3.6825e-03 * t * t )
		+ ( t * t * t / 3.2727e+05 );
	
	// Longitude of the ascending node of the Moon's mean orbit on the ecliptic,
	// measured from the mean equinox of the date
	double omega = 1.2504452e+02
		- ( 1.934136261e+03 * t )
		+ ( 2.0708e-03 * t * t )
		+ ( t * t * t / 4.5e+05 );
	
	double trigArgElements[5] = {MathUtil::convDegToRad(d),
		MathUtil::convDegToRad(m),
		MathUtil::convDegToRad(mp),
		MathUtil::convDegToRad(f),
		MathUtil::convDegToRad(omega)};
	double trigArg;
	
	double deltaEpsilon = 0.0;
	
	for ( int i = 0 ; i < TABLE22A_SIZE ; ++i )
	{
		trigArg = 0.0;
		for ( int j = 0 ; j < 5 ; ++j )
		{
			trigArg += trigArgElements[j] * NutationObliquityNs::argumentTable[i][j];
		}
		deltaEpsilon += ( NutationObliquityNs::coeffCos[i][0] + ( NutationObliquityNs::coeffCos[i][1] * t) )
			* cos ( trigArg );
	}
	
	return deltaEpsilon;
}

double
NutationObliquity::calcTrueObliquityInArcsec(double jde)
{
	double epsilon0 = calcMeanObliquityInArcsec(jde);
	double deltaEpsilon = calcNutationObliquityInArcsec(jde);
	
	double epsilon = epsilon0 + deltaEpsilon;
	
	return epsilon;
}
