/*
 *  MathUtil.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>

#include "MathUtil.h"

double
MathUtil::convArcsecToDeg(double arcsec)
{
	double deg = arcsec / 3.600e+03;
	
	return deg;
}

double
MathUtil::convArcsecToRad(double arcsec)
{
	double rad = arcsec * ( M_PI / 6.48000e+05 ) ;
	
	return rad;
}

void
MathUtil::convDayToHm(double days,
					   int* pHour,
					   int* pMinute)
{
	days -= int(days);
	if ( days < 0 )
	{
		days += 1e+00;
	}
	
	double hours = 2.4e+01 * days;
	*pHour = int ( hours );
	
	double minutes = 6.0e+01 * ( hours - int ( hours ) );
	*pMinute = int ( round ( minutes ) );
	
	if ( 60 == *pMinute )
	{
		*pMinute = 0;
		++(*pHour);
	}
	
	if ( *pHour > 24 )
	{
		*pHour %= 24;
	}
}

void
MathUtil::convDayToHms(double days,
					   int* pHour,
					   int* pMinute,
					   double* pSecond)
{
	days -= int(days);
	if ( days < 0 )
	{
		days += 1e+00;
	}
	
	double hours = 2.4e+01 * days;
	*pHour = int ( hours );
	
	double minutes = 6.0e+01 * ( hours - int ( hours ) );
	*pMinute = int ( minutes );
	
	double seconds = 6.0e+01 * ( minutes - int ( minutes ) );
	*pSecond = seconds;
}

double
MathUtil::convDegToArcsec(double deg)
{
	double arcsec = deg * 3.600e+03;
	
	return arcsec;
}

double
MathUtil::convDegToDeg(double deg)
{
	if ( deg > 0 )
	{
		return fmod ( deg, 3.60e+02 );
	}
	else if ( deg < 0 )
	{
		return fmod ( deg, 3.60e+02 ) + 3.60e+02;
	}
	else
	{
		return 0.0;
	}
}

void
MathUtil::convDegToDms(double deg,
					   int* pDeg,
					   int* pArcmin,
					   double* pArcsec)
{
	deg = convDegToDeg(deg);
	*pDeg = int ( deg );
	
	double arcminutes = 6.0e+01 * ( deg - int ( deg ) );
	*pArcmin = int ( arcminutes );
	
	*pArcsec = 6.0e+01 * ( arcminutes - int ( arcminutes ) );
}

double
MathUtil::convDegToRad(double deg)
{
	double rad = deg * ( M_PI / 1.80e+02 );
	
	return rad;
}

double
MathUtil::convDmsToDeg(int deg,
					   int arcmin,
					   double arcsec)
{
	double degOut = deg
	+ ( 1e+00 * arcmin / 6.0e+01 )
	+ ( arcsec / 3.600e+03 );
	
	return degOut;
}

double
MathUtil::convRadToArcsec(double rad)
{
	double arcsec = rad * ( 6.48000e+05 / M_PI );
	
	return arcsec;
}

double
MathUtil::convRadToDeg(double rad)
{
	double deg = rad * ( 1.80e+02 / M_PI );
	
	return deg;
}
/*
 void
 MathUtil::convRadToHms(double rad,
						int* pHour,
						int* pMinute,
						double* pSecond)
 {
	 double days = rad / (2.0 * M_PI);
	 
	 days -= int(days);
	 if ( days < 0 )
	 {
		 days += 1e+00;
	 }
	 
	 double hours = 2.4e+01 * days;
	 *pHour = int ( hours );
	 
	 double minutes = 6.0e+01 * ( hours - int ( hours ) );
	 *pMinute = int ( minutes );
	 
	 double seconds = 6.0e+01 * ( minutes - int ( minutes ) );
	 *pSecond = seconds;
 }
 */