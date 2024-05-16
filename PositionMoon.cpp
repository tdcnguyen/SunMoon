/*
 *  PositionMoon.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <iostream>

#include "MathUtil.h"
#include "NutationObliquity.h"
#include "TransformationCoordinates.h"

#include "PositionMoon.h"

double
PositionMoon::calcApparentDecInDeg(double jde)
{
	double longitude = calcApparentLongitudeInDeg(jde);
	double latitude = calcApparentLatitudeInDeg(jde);
	double obliquity = MathUtil::convArcsecToDeg(NutationObliquity::calcTrueObliquityInArcsec(jde));
	
	double dec = TransformationCoordinates::calcDecInRad(longitude,
														 latitude,
														 obliquity);
	double decDeg = MathUtil::convRadToDeg(dec);
	
	return decDeg;
}

double
PositionMoon::calcApparentLatitudeInDeg(double jde)
{
	// Geocentric Latitude (in degrees)
	double latitude = calcGeocentricLatitudeInDeg(jde);
	
	return latitude;
}

double
PositionMoon::calcApparentLongitudeInDeg(double jde)
{
	// Geocentric Longitude (in degrees)
	double longitude = calcGeocentricLongitudeInDeg(jde);

	// Nutation in Longitude (in arcsec)
	double nutationLongitude = NutationObliquity::calcNutationLongitudeInArcsec(jde);
	double nutationLongitudeDeg = MathUtil::convArcsecToDeg(nutationLongitude);

	// Apply corrections
	longitude += nutationLongitudeDeg;
	
	return longitude;
}

double
PositionMoon::calcApparentRAInDeg(double jde)
{
	double longitude = calcApparentLongitudeInDeg(jde);
	double latitude = calcApparentLatitudeInDeg(jde);
	double obliquity = MathUtil::convArcsecToDeg(NutationObliquity::calcTrueObliquityInArcsec(jde));
	
	double ra = TransformationCoordinates::calcRAInRad(longitude,
													   latitude,
													   obliquity);
	double raDeg = MathUtil::convRadToDeg(ra);

	return raDeg;
}

double
PositionMoon::calcDistanceInKm(double jde)
{
	double t = ( jde - 2.451545e+06 ) / 3.6525e+04;
	
	// Moon's mean longitude, mean equinox of the date (in degrees)
//	double lp = 2.183164477e+02
//		+ ( 4.8126788123421e+05 * t )
//		- ( 1.5786e-03 * t * t )
//		+ ( t * t * t / 5.38841e+05 )
//		- ( t * t * t * t / 6.5194000e+07 );
	
	// Mean elongation of the Moon (in degrees)
	double d = 2.978501921e+02
		+ ( 4.452671114034e+05 * t )
		- ( 1.8819e-03 * t * t )
		+ ( t * t * t / 5.45868e+05 )
		- ( t * t * t * t / 1.13065000e+08 );
	
	// Sun's mean anomaly (in degrees)
	double m = 3.575291092e+02
		+ ( 3.59990502909e+04 * t )
		- ( 1.536e-04 * t * t )
		+ ( t * t * t / 2.4490000e+07 );
	
	// Moon's mean anomaly (in degrees)
	double mp = 1.349633964e+02
		+ ( 4.771988675055e+05 * t )
		+ ( 8.7414e-03 * t * t )
		+ ( t * t * t / 6.9699e+04 )
		- ( t * t * t * t / 1.4712000e+07 );
	
	// Moon's argument of latitude, mean distance of the Moon from its ascending node (in degrees)
	double f = 9.32720950e+01
		+ ( 4.832020175233e+05 * t )
		- ( 3.6539e-03 * t * t )
		- ( t * t * t / 3.526000e+06 )
		+ ( t * t * t * t / 8.63310000e+08 );
	
//	double a1 = 1.1975e+02
//		+ ( 1.31849e+02 * t );
//	double a2 = 5.309e+01
//		+ ( 4.79264290e+05 * t );
//	double a3 = 3.1345e+02
//		+ ( 4.81266484e+05 * t );

	double trigArgElements[4] = {MathUtil::convDegToRad(d),
		MathUtil::convDegToRad(m),
		MathUtil::convDegToRad(mp),
		MathUtil::convDegToRad(f)};
	double trigArg;
	double term;

	double e = 1e+00
	- ( 2.516e-03 * t )
	- ( 7.4e-06 * t * t );

	double sigmaR = 0.0;	
	for ( int i = 0 ; i < TABLE47A_SIZE ; ++i )
	{
		trigArg = 0.0;
		for ( int j = 0 ; j < 4 ; ++j )
		{
			trigArg += trigArgElements[j] * PositionMoonNs::argumentTableA[i][j];
		}
		term = PositionMoonNs::coeffCosR[i] * cos ( trigArg );
		for ( int j = 0 ; j < fabs(PositionMoonNs::argumentTableA[i][1]) ; ++j )
		{
			term *= e;
		}
		sigmaR += term;
	}
	
	double distance = 3.8500056e+05 + ( 1e-03 * sigmaR );
	
	return distance;
}


double
PositionMoon::calcGeocentricLatitudeInDeg(double jde)
{
	double t = ( jde - 2.451545e+06 ) / 3.6525e+04;
	
	// Moon's mean longitude, mean equinox of the date (in degrees)
	double lp = 2.183164477e+02
		+ ( 4.8126788123421e+05 * t )
		- ( 1.5786e-03 * t * t )
		+ ( t * t * t / 5.38841e+05 )
		- ( t * t * t * t / 6.5194000e+07 );
	
	// Mean elongation of the Moon (in degrees)
	double d = 2.978501921e+02
		+ ( 4.452671114034e+05 * t )
		- ( 1.8819e-03 * t * t )
		+ ( t * t * t / 5.45868e+05 )
		- ( t * t * t * t / 1.13065000e+08 );
	
	// Sun's mean anomaly (in degrees)
	double m = 3.575291092e+02
		+ ( 3.59990502909e+04 * t )
		- ( 1.536e-04 * t * t )
		+ ( t * t * t / 2.4490000e+07 );
	
	// Moon's mean anomaly (in degrees)
	double mp = 1.349633964e+02
		+ ( 4.771988675055e+05 * t )
		+ ( 8.7414e-03 * t * t )
		+ ( t * t * t / 6.9699e+04 )
		- ( t * t * t * t / 1.4712000e+07 );
	
	// Moon's argument of latitude, mean distance of the Moon from its ascending node (in degrees)
	double f = 9.32720950e+01
		+ ( 4.832020175233e+05 * t )
		- ( 3.6539e-03 * t * t )
		- ( t * t * t / 3.526000e+06 )
		+ ( t * t * t * t / 8.63310000e+08 );
	
	double a1 = 1.1975e+02
		+ ( 1.31849e+02 * t );
//	double a2 = 5.309e+01
//		+ ( 4.79264290e+05 * t );
	double a3 = 3.1345e+02
		+ ( 4.81266484e+05 * t );

	double trigArgElements[4] = {MathUtil::convDegToRad(d),
		MathUtil::convDegToRad(m),
		MathUtil::convDegToRad(mp),
		MathUtil::convDegToRad(f)};
	double trigArg;
	double term;

	double e = 1e+00
	- ( 2.516e-03 * t )
	- ( 7.4e-06 * t * t );

	double sigmaB = 0.0;	
	for ( int i = 0 ; i < TABLE47B_SIZE ; ++i )
	{
		trigArg = 0.0;
		for ( int j = 0 ; j < 4 ; ++j )
		{
			trigArg += trigArgElements[j] * PositionMoonNs::argumentTableB[i][j];
		}
		term = PositionMoonNs::coeffSinB[i] * sin ( trigArg );
		for ( int j = 0 ; j < fabs(PositionMoonNs::argumentTableB[i][1]) ; ++j )
		{
			term *= e;
		}
		sigmaB += term;
	}
	
	// Additional terms
	sigmaB += -2.235e+03 * sin ( MathUtil::convDegToRad ( lp ) )
	+ 3.82e+02 * sin ( MathUtil::convDegToRad ( a3 ) )
	+ 1.75e+02 * sin ( MathUtil::convDegToRad ( a1 - f ) )
	+ 1.75e+02 * sin ( MathUtil::convDegToRad ( a1 + f ) )
	+ 1.27e+02 * sin ( MathUtil::convDegToRad ( lp - mp ) )
	- 1.15e+02 * sin ( MathUtil::convDegToRad ( lp + mp ) );

	double latitude = 1e-06 * sigmaB;
	
	return latitude;
}

double
PositionMoon::calcGeocentricLongitudeInDeg(double jde)
{
	double t = ( jde - 2.451545e+06 ) / 3.6525e+04;
	
	// Moon's mean longitude, mean equinox of the date (in degrees)
	double lp = 2.183164477e+02
		+ ( 4.8126788123421e+05 * t )
		- ( 1.5786e-03 * t * t )
		+ ( t * t * t / 5.38841e+05 )
		- ( t * t * t * t / 6.5194000e+07 );
	
	// Mean elongation of the Moon (in degrees)
	double d = 2.978501921e+02
		+ ( 4.452671114034e+05 * t )
		- ( 1.8819e-03 * t * t )
		+ ( t * t * t / 5.45868e+05 )
		- ( t * t * t * t / 1.13065000e+08 );
	
	// Sun's mean anomaly (in degrees)
	double m = 3.575291092e+02
		+ ( 3.59990502909e+04 * t )
		- ( 1.536e-04 * t * t )
		+ ( t * t * t / 2.4490000e+07 );
	
	// Moon's mean anomaly (in degrees)
	double mp = 1.349633964e+02
		+ ( 4.771988675055e+05 * t )
		+ ( 8.7414e-03 * t * t )
		+ ( t * t * t / 6.9699e+04 )
		- ( t * t * t * t / 1.4712000e+07 );
	
	// Moon's argument of latitude, mean distance of the Moon from its ascending node (in degrees)
	double f = 9.32720950e+01
		+ ( 4.832020175233e+05 * t )
		- ( 3.6539e-03 * t * t )
		- ( t * t * t / 3.526000e+06 )
		+ ( t * t * t * t / 8.63310000e+08 );
	
	double a1 = 1.1975e+02
		+ ( 1.31849e+02 * t );
	double a2 = 5.309e+01
		+ ( 4.79264290e+05 * t );
//	double a3 = 3.1345e+02
//		+ ( 4.81266484e+05 * t );

	double trigArgElements[4] = {MathUtil::convDegToRad(d),
		MathUtil::convDegToRad(m),
		MathUtil::convDegToRad(mp),
		MathUtil::convDegToRad(f)};
	double trigArg;
	double term;

	double e = 1e+00
	- ( 2.516e-03 * t )
	- ( 7.4e-06 * t * t );

	double sigmaL = 0.0;	
	for ( int i = 0 ; i < TABLE47A_SIZE ; ++i )
	{
		trigArg = 0.0;
		for ( int j = 0 ; j < 4 ; ++j )
		{
			trigArg += trigArgElements[j] * PositionMoonNs::argumentTableA[i][j];
		}
		term = PositionMoonNs::coeffSinL[i] * sin ( trigArg );
		for ( int j = 0 ; j < fabs(PositionMoonNs::argumentTableA[i][1]) ; ++j )
		{
			term *= e;
		}
		sigmaL += term;
	}
	
	// Additional terms
	sigmaL += 3.958e+03 * sin ( MathUtil::convDegToRad ( a1 ) )
	+ ( 1.962e+03 * sin ( MathUtil::convDegToRad ( lp - f ) ) )
	+ ( 3.18e+02 * sin ( MathUtil::convDegToRad ( a2 ) ) );

	double longitude = lp + ( 1e-06 * sigmaL );
	
	return longitude;
}

double
PositionMoon::calcHorizontalParallaxInDeg(double jde)
{
	double distance = calcDistanceInKm(jde);

	double horizontalParallax = asin ( 6.37814e+03 / distance );
	horizontalParallax = MathUtil::convRadToDeg(horizontalParallax);
	
	return horizontalParallax;
}
