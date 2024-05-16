/*
 *  SiderealTime.cpp
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

#include "SiderealTime.h"

double
SiderealTime::calcApparentSiderealTimeInDeg(int year,
											int month,
											double day)
{
	double jd = JulianDay::calcJD(year,
								  month,
								  day);
	
	double theta0 = calcApparentSiderealTimeInDeg(jd);
	
	return theta0;
}

double
SiderealTime::calcApparentSiderealTimeInDeg(double jd)
{
	// Apparent Sidereal Time = Mean Sidereal Time + Nutation Correction
	
	// Calculate Mean Sidereal Time
	double theta0 = calcMeanSiderealTimeInDeg(jd);
	
	// Calculate Nutation
	double jde = JulianDay::convJDtoJDE(jd);
	double deltaPsi = NutationObliquity::calcNutationLongitudeInArcsec(jde);
	deltaPsi = MathUtil::convArcsecToDeg(deltaPsi);
	double epsilon = NutationObliquity::calcTrueObliquityInArcsec(jde);
	epsilon = MathUtil::convArcsecToRad(epsilon);
	
	// Apply Correction
	theta0 += ( deltaPsi * cos(epsilon) );
	
	return theta0;
}

double
SiderealTime::calcMeanSiderealTimeInDeg(int year,
										int month,
										double day)
{
	double jd = JulianDay::calcJD(year,
								  month,
								  day);
	
	/*
	 double t = ( jd - 2.4515450e+06 ) / 3.6525e+04;
	 
	 double theta0 = 1.0046061837e+02
	 + ( 3.6000770053608e+04 * t )
	 + ( 3.87933e-04 * t * t )
	 - ( ( t * t * t ) / 3.8710000e+07 );
	 
	 return theta0;
	 */
	
	double theta0 = calcMeanSiderealTimeInDeg(jd);
	
	return theta0;
}

double
SiderealTime::calcMeanSiderealTimeInDeg(double jd)
{
	double t = ( jd - 2.4515450e+06 ) / 3.6525e+04;
	
	double theta0 = 2.8046061837e+02
		+ ( 3.6098564736629e+02 * ( jd - 2.4515450e+06 ) )
		+ ( 3.87933e-04 * t * t )
		- ( ( t * t * t ) / 3.8710000e+07 );
	
	return theta0;
}
