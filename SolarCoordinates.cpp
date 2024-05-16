/*
 *  SolarCoordinates.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-09.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <iostream>

#include "JulianDay.h"
#include "MathUtil.h"
#include "NutationObliquity.h"
#include "TransformationCoordinates.h"

#include "SolarCoordinates.h"

double
SolarCoordinates::calcAberrationInDeg(double jde)
{
	double t = ( jde - 2.4515450e+06 ) / 3.6525e+04;
	
	// Eccentricity of the Earth's orbit
	//	double e = 1.6708634e-02
	//		- ( 4.2037e-05 * t )
	//		- ( 1.267e-07 * t * t );
	
	// Sun's true anomaly
	//	double nu = calcAnomalyInDeg(jde);
	
	// Sun's radius vector
	//	double r = ( 1.000001018e+00 * ( 1e+00 - e * e ) ) /
	//		( 1e+00 + e * ( cos ( MathUtil::convDegToRad ( nu ) ) ) );
	double r = calcRadiusVector(jde);
	
	double tau = 1.0e-01 * t;
	
	// Daily variation, in arcseconds, of the geocentric longitude of the Sun
	// in a fixed reference frame
	double deltaLambda = 3.548193e+03
		+ ( 1.18568e+02 * sin ( MathUtil::convDegToRad ( 8.75287e+01 + 3.599937286e+05 * tau ) ) )
		+ ( 2.476e+00 * sin ( MathUtil::convDegToRad ( 8.50561e+01 + 7.199874571e+05 * tau ) ) )
		+ ( 1.376e+00 * sin ( MathUtil::convDegToRad ( 2.78502e+01 + 4.4526711152e+06 * tau ) ) )
		+ ( 1.19e-01 * sin ( MathUtil::convDegToRad ( 7.31375e+01 + 4.503688564e+05 * tau ) ) )
		+ ( 1.14e-01 * sin ( MathUtil::convDegToRad ( 3.372264e+02 + 3.296446718e+05 * tau ) ) )
		+ ( 8.6e-02 * sin ( MathUtil::convDegToRad ( 2.225400e+02 + 6.592893436e+05 * tau ) ) )
		+ ( 7.8e-02 * sin ( MathUtil::convDegToRad ( 1.628136e+02 + 9.2246597915e+06 * tau ) ) )
		+ ( 5.4e-02 * sin ( MathUtil::convDegToRad ( 8.25823e+01 + 1.0799811857e+06 * tau ) ) )
		+ ( 5.2e-02 * sin ( MathUtil::convDegToRad ( 1.715189e+02 + 2.251844282e+05 * tau ) ) )
		+ ( 3.4e-02 * sin ( MathUtil::convDegToRad ( 3.03214e+01 + 4.0926773866e+06 * tau ) ) )
		+ ( 3.3e-02 * sin ( MathUtil::convDegToRad ( 1.198105e+02 + 3.371814711e+05 * tau ) ) )
		+ ( 2.3e-02 * sin ( MathUtil::convDegToRad ( 2.475418e+02 + 2.992956151e+05 * tau ) ) )
		+ ( 2.3e-02 * sin ( MathUtil::convDegToRad ( 3.251526e+02 + 3.155595560e+05 * tau ) ) )
		+ ( 2.1e-02 * sin ( MathUtil::convDegToRad ( 1.551241e+02 + 6.755532846e+05 * tau ) ) )
		+ ( 7.311e+00 * tau * sin ( MathUtil::convDegToRad ( 3.334515e+02 + 3.599937286e+05 * tau ) ) )
		+ ( 3.05e-01 * tau * sin ( MathUtil::convDegToRad ( 3.309814e+02 + 7.199874571e+05 * tau ) ) )
		+ ( 1.0e-02 * tau * sin ( MathUtil::convDegToRad ( 3.285170e+02 + 1.0799811857e+06 * tau ) ) )
		+ ( 3.09e-01 * tau * tau * sin ( MathUtil::convDegToRad ( 2.414518e+02 + 3.599937286e+05 * tau ) ) )
		+ ( 2.1e-02 * tau * tau * sin ( MathUtil::convDegToRad ( 2.050482e+02 + 7.199874571e+05 * tau ) ) )
		+ ( 4e-03 * tau * tau * sin ( MathUtil::convDegToRad ( 2.978610e+02 + 4.4526711152e+06 * tau ) ) )
		+ ( 1.0e-02 * tau * tau * tau * sin ( MathUtil::convDegToRad ( 1.547066e+02 + 3.599937286e+05 * tau ) ) );
	double deltaLambdaDeg = MathUtil::convArcsecToDeg(deltaLambda);
	
	double aberration = -5.775518e-03 * r * deltaLambdaDeg;
	
	return aberration;
}

double
SolarCoordinates::calcAnomalyInDeg(double jde)
{
	double t = ( jde - 2.4515450e+06 ) / 3.6525e+04;
	
	// Mean anomaly of the Sun (in degrees)
	double m = 3.5752911e+02
		+ ( 3.599905029e+04 * t )
		- ( 1.537e-04 * t * t );
	double mRad = MathUtil::convDegToRad(m);
	
	// Sun's equation of the center C
	double c = ( 1.914602e+00 - 4.817e-03 * t - 1.4e-05 * t * t ) * sin ( mRad )
		+ ( 1.9993e-02 - 1.01e-04 * t ) * sin ( 2.0 * mRad )
		+ ( 2.89e-04 ) * sin ( 3.0 * mRad );
	
	double nu = m + c;
	
	return nu;
}

double
SolarCoordinates::calcApparentDecInDeg(double jde)
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
SolarCoordinates::calcApparentLatitudeInDeg(double jde)
{
	double latitude = calcGeometricLatitudeInDeg(jde);
	
	double t = ( jde - 2.4515450e+06 ) / 3.6525e+04;
	
	double lambdap = calcGeometricLongitudeInDeg(jde)
		- ( 1.397e+00 * t )
		- ( 3.1e-04 * t * t );
	double lambdapRad = MathUtil::convDegToRad(lambdap);
	
	double deltaBeta = 3.916e-02 * ( cos ( lambdapRad ) - sin ( lambdapRad ) );
	double deltaBetaDeg = MathUtil::convArcsecToDeg(deltaBeta);
	
	latitude += deltaBetaDeg;
	
	return latitude;
}

double
SolarCoordinates::calcApparentLongitudeInDeg(double jde)
{
	// Geometric Longitude (in degrees)
	double longitude = calcGeometricLongitudeInDeg(jde);
	longitude += MathUtil::convArcsecToDeg(-9.033e-02);
	
	// Nutation in Longitude (in arcsec)
	double nutationLongitude = NutationObliquity::calcNutationLongitudeInArcsec(jde);
	double nutationLongitudeDeg = MathUtil::convArcsecToDeg(nutationLongitude);
	
	// Aberration (in degrees)
	double aberration = calcAberrationInDeg(jde);
	
	// Apply corrections
	longitude += nutationLongitudeDeg + aberration;
	
	return longitude;
}

double
SolarCoordinates::calcApparentRAInDeg(double jde)
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
SolarCoordinates::calcGeometricLatitudeInDeg(double jde)
{
	double tau = ( jde - 2.4515450e+06 ) / 3.6525e+05;
	
	double a, b, c;
	
	double bigB[2] = {0.0, 0.0};
	for ( int i = 0 ; i < VSOP87EARTHB0_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthb0[i][0];
		b = SolarCoordinatesNs::vsop87earthb0[i][1];
		c = SolarCoordinatesNs::vsop87earthb0[i][2];
		
		bigB[0] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHB1_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthb1[i][0];
		b = SolarCoordinatesNs::vsop87earthb1[i][1];
		c = SolarCoordinatesNs::vsop87earthb1[i][2];
		
		bigB[1] += a * cos ( b + c * tau );
	}
	
	double latitude = 0.0;
	double pow_tau = 1e+00;
	for ( int i = 0 ; i < 2 ; ++i )
	{
		latitude += bigB[i] * pow_tau;
		pow_tau *= tau;
	}
	
	latitude = MathUtil::convRadToDeg( -1e-08 * latitude );
	
	return latitude;
}

double
SolarCoordinates::calcGeometricLongitudeInDeg(double jde)
{
	/*	double t = ( jde - 2.4515450e+06 ) / 3.6525e+04;
	
	// Geometric Mean Longitude of the Sun (in degrees)
	double l0 = 2.8046646e+02
	+ ( 3.600076983e+04 * t )
	+ ( 3.032e-04 * t * t);
	
	// Mean anomaly of the Sun (in degrees)
	double m = 3.5752911e+02
	+ ( 3.599905029e+04 * t )
	- ( 1.537e-04 * t * t );
	double mRad = MathUtil::convDegToRad(m);
	
	// Sun's equation of the center C (in degrees)
	double c = ( 1.914602e+00 - 4.817e-03 * t - 1.4e-05 * t * t ) * sin ( mRad )
	+ ( 1.9993e-02 - 1.01e-04 * t ) * sin ( 2.0 * mRad )
	+ ( 2.89e-04 ) * sin ( 3.0 * mRad );
	
	double longitude = l0 + c;
	*/
	double tau = ( jde - 2.4515450e+06 ) / 3.6525e+05;
	
	double a, b, c;
	
	double l[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	for ( int i = 0 ; i < VSOP87EARTHL0_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthl0[i][0];
		b = SolarCoordinatesNs::vsop87earthl0[i][1];
		c = SolarCoordinatesNs::vsop87earthl0[i][2];
		
		l[0] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHL1_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthl1[i][0];
		b = SolarCoordinatesNs::vsop87earthl1[i][1];
		c = SolarCoordinatesNs::vsop87earthl1[i][2];
		
		l[1] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHL2_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthl2[i][0];
		b = SolarCoordinatesNs::vsop87earthl2[i][1];
		c = SolarCoordinatesNs::vsop87earthl2[i][2];
		
		l[2] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHL3_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthl3[i][0];
		b = SolarCoordinatesNs::vsop87earthl3[i][1];
		c = SolarCoordinatesNs::vsop87earthl3[i][2];
		
		l[3] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHL4_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthl4[i][0];
		b = SolarCoordinatesNs::vsop87earthl4[i][1];
		c = SolarCoordinatesNs::vsop87earthl4[i][2];
		
		l[4] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHL5_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthl5[i][0];
		b = SolarCoordinatesNs::vsop87earthl5[i][1];
		c = SolarCoordinatesNs::vsop87earthl5[i][2];
		
		l[5] += a * cos ( b + c * tau );
	}
	
	double longitude = 0.0;
	double pow_tau = 1e+00;
	for ( int i = 0 ; i < 6 ; ++i )
	{
		longitude += l[i] * pow_tau;
		pow_tau *= tau;
	}
	
	longitude = MathUtil::convRadToDeg( 1e-08 * longitude ) + 1.80e+02;
	
	return longitude;
}

double
SolarCoordinates::calcRadiusVector(double jde)
{
	double tau = ( jde - 2.4515450e+06 ) / 3.6525e+05;
	
	double a, b, c;
	
	double r[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
	for ( int i = 0 ; i < VSOP87EARTHR0_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthr0[i][0];
		b = SolarCoordinatesNs::vsop87earthr0[i][1];
		c = SolarCoordinatesNs::vsop87earthr0[i][2];
		
		r[0] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHR1_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthr1[i][0];
		b = SolarCoordinatesNs::vsop87earthr1[i][1];
		c = SolarCoordinatesNs::vsop87earthr1[i][2];
		
		r[1] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHR2_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthr2[i][0];
		b = SolarCoordinatesNs::vsop87earthr2[i][1];
		c = SolarCoordinatesNs::vsop87earthr2[i][2];
		
		r[2] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHR3_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthr3[i][0];
		b = SolarCoordinatesNs::vsop87earthr3[i][1];
		c = SolarCoordinatesNs::vsop87earthr3[i][2];
		
		r[3] += a * cos ( b + c * tau );
	}
	for ( int i = 0 ; i < VSOP87EARTHR4_SIZE ; ++i )
	{
		a = SolarCoordinatesNs::vsop87earthr4[i][0];
		b = SolarCoordinatesNs::vsop87earthr4[i][1];
		c = SolarCoordinatesNs::vsop87earthr4[i][2];
		
		r[4] += a * cos ( b + c * tau );
	}
	
	double radiusVector = 0.0;
	double pow_tau = 1e+00;
	for ( int i = 0 ; i < 5 ; ++i )
	{
		radiusVector += r[i] * pow_tau;
		pow_tau *= tau;
	}
	
	radiusVector *= 1e-08;
	
	return radiusVector;
}
