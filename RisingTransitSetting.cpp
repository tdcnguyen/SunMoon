/*
 *  RisingTransitSetting.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <iostream>

#include "DynamicalUniversalTime.h"
#include "Interpolation.h"
#include "JulianDay.h"
#include "MathUtil.h"
#include "PositionMoon.h"
#include "SiderealTime.h"
#include "SolarCoordinates.h"
#include "TransformationCoordinates.h"

#include "RisingTransitSetting.h"

void
RisingTransitSetting::calcRisingTransitSettingForMoon(double longitude,
													  double latitude,
													  int year,
													  int month,
													  int day,
													  int timeZone,
													  double m[])
{
	// Geographic longitude and latitude of the observer (in radians)
	double latitudeRad = MathUtil::convDegToRad(latitude);
	
	double jd = JulianDay::calcJD(year,
								  month,
								  ( longitude / 3.60e+02 ) + day);
	
	// Calculate the apparent sidereal time Theta0 at 0h Universal Time on day D
	// for the meridian of Greenwich, converted into degrees
	double bigTheta0 = SiderealTime::calcApparentSiderealTimeInDeg(jd);
	bigTheta0 = MathUtil::convDegToDeg(bigTheta0);
	
	// Calculate the right ascensions and declinations of the Sun
	double ra1 = PositionMoon::calcApparentRAInDeg(jd-1e+00);
	double dec1 = PositionMoon::calcApparentDecInDeg(jd-1e+00);
	double ra2 = PositionMoon::calcApparentRAInDeg(jd);
	double dec2 = PositionMoon::calcApparentDecInDeg(jd);
	double ra3 = PositionMoon::calcApparentRAInDeg(jd+1e+00);
	double dec3 = PositionMoon::calcApparentDecInDeg(jd+1e+00);
	double dec2Rad = MathUtil::convDegToRad(dec2);
	
	// Produce ra1 < ra2 < ra3, for interpolation feasibility
	if ( ra2 < ra1 )
	{
		ra2 += 3.60e+02;
	}
	if ( ra3 < ra2 )
	{
		ra3 += 3.60e+02;
	}
	
	// Calculate Moon's horizontal parallax
	double horizontalParallax = PositionMoon::calcHorizontalParallaxInDeg(jd);
	
	// Geometric altitude of the center of the Moon at the time of apparent
	// rising or setting (in degrees)
	double h0 = ( 7.275e-01 * horizontalParallax ) - 5.667e-01;
	double h0Rad = MathUtil::convDegToRad(h0);
	
	// Calculate approximate times
	double cosBigH0 = ( ( sin ( h0Rad ) - sin ( latitudeRad ) * sin ( dec2Rad ) ) / ( cos ( latitudeRad ) * cos ( dec2Rad ) ) );
	if ( fabs(cosBigH0) > 1e+00 )
	{
		m[0] = 5e-01;
		m[1] = 0.0;
		m[2] = 1e+00;
		return;
	}
	double bigH0 = acos ( cosBigH0 );
	double bigH0Deg = MathUtil::convRadToDeg(bigH0);
	bigH0Deg = MathUtil::convDegToDeg(bigH0Deg);
	
	m[0] = ( ra2 + longitude - bigTheta0 ) / 3.60e+02;
	m[1] = m[0] - bigH0Deg / 3.60e+02;
	m[2] = m[0] + bigH0Deg / 3.60e+02;
	
	double deltaT = DynamicalUniversalTime::calcDeltaTInSec(year);
	
	double theta0[3];
	double n[3];
	double ra[3];
	double dec[3];
	double lha[3];
	double h[3];
	double deltaM[3] = {1e+00, 1e+00, 1e+00};
	for ( int i = 0 ; i < 3 ; ++i )
	{
		for ( int j = 0 ; fabs(deltaM[i]) > 1.0e-10 && j < 100 ; ++j )
		{
			m[i] -= int(m[i]);
			if ( m[i] < 0 )
			{
				++m[i];
			}

			theta0[i] = bigTheta0 + 3.60985647e+02 * m[i];
			n[i] = m[i] + deltaT / 8.6400e+04;
			ra[i] = Interpolation::calcThreeTabularInterpolation(ra1,
																 ra2,
																 ra3,
																 n[i]);
			dec[i] = Interpolation::calcThreeTabularInterpolation(dec1,
																  dec2,
																  dec3,
																  n[i]);
			
			lha[i] = theta0[i] - longitude - ra[i];
			for ( ; lha[i] > 180 ; lha[i] -= 360 );
			for ( ; lha[i] < -180 ; lha[i] += 360 );
			h[i] = TransformationCoordinates::calcAltInRad(latitude,
														   dec[i],
														   lha[i]);
			h[i] = MathUtil::convRadToDeg(h[i]);
			
			if ( 0 == i )
			{
				deltaM[i] = -lha[i] / 3.60e+02;
			}
			else
			{
				deltaM[i] = ( h[i] - h0 ) / ( 3.60e+02 * cos ( MathUtil::convDegToRad( dec[i] ) ) * cos ( latitudeRad ) * sin ( MathUtil::convDegToRad( lha[i] ) ) );
			}
			
			m[i] += deltaM[i];
		}
		m[i] += ( longitude / 3.60e+02) + ( 1e+00 * timeZone / 2.4e+01 );
	}
}

void
RisingTransitSetting::calcRisingTransitSettingForSun(double longitude,
													 double latitude,
													 int year,
													 int month,
													 int day,
													 int timeZone,
													 double m[])
{
	// Geographic longitude and latitude of the observer (in radians)
	double latitudeRad = MathUtil::convDegToRad(latitude);
	
	double jd = JulianDay::calcJD(year,
								  month,
								  ( longitude / 3.60e+02 ) + day);
	
	// Calculate the apparent sidereal time Theta0 at 0h Universal Time on day D
	// for the meridian of Greenwich, converted into degrees
	double bigTheta0 = SiderealTime::calcApparentSiderealTimeInDeg(jd);
	bigTheta0 = MathUtil::convDegToDeg(bigTheta0);
	
	// Calculate the right ascensions and declinations of the Sun
	double ra1 = SolarCoordinates::calcApparentRAInDeg(jd-1e+00);
	double dec1 = SolarCoordinates::calcApparentDecInDeg(jd-1e+00);
	double ra2 = SolarCoordinates::calcApparentRAInDeg(jd);
	double dec2 = SolarCoordinates::calcApparentDecInDeg(jd);
	double ra3 = SolarCoordinates::calcApparentRAInDeg(jd+1e+00);
	double dec3 = SolarCoordinates::calcApparentDecInDeg(jd+1e+00);
	double dec2Rad = MathUtil::convDegToRad(dec2);
	
	// Produce ra1 < ra2 < ra3, for interpolation feasibility
	if ( ra2 < ra1 )
	{
		ra2 += 3.60e+02;
	}
	if ( ra3 < ra2 )
	{
		ra3 += 3.60e+02;
	}
	
	// Geometric altitude of the center of the Sun at the time of apparent
	// rising or setting (in degrees)
	double h0 = -8.333e-01;
	double h0Rad = MathUtil::convDegToRad(h0);
	
	// Calculate approximate times
	double cosBigH0 = ( ( sin ( h0Rad ) - sin ( latitudeRad ) * sin ( dec2Rad ) ) / ( cos ( latitudeRad ) * cos ( dec2Rad ) ) );
	if ( fabs(cosBigH0) > 1e+00 )
	{
		m[0] = 5e-01;
		m[1] = 0.0;
		m[2] = 1e+00;
		return;
	}
	double bigH0 = acos ( cosBigH0 );
	double bigH0Deg = MathUtil::convRadToDeg(bigH0);
	bigH0Deg = MathUtil::convDegToDeg(bigH0Deg);
	
	m[0] = ( ra2 + longitude - bigTheta0 ) / 3.60e+02;
	m[1] = m[0] - bigH0Deg / 3.60e+02;
	m[2] = m[0] + bigH0Deg / 3.60e+02;
	
	double deltaT = DynamicalUniversalTime::calcDeltaTInSec(year);
	
	double theta0[3];
	double n[3];
	double ra[3];
	double dec[3];
	double lha[3];
	double h[3];
	double deltaM[3] = {1e+00, 1e+00, 1e+00};
	for ( int i = 0 ; i < 3 ; ++i )
	{
		for ( int j = 0 ; fabs(deltaM[i]) > 1.0e-10 && j < 100 ; ++j )
		{
			m[i] -= int(m[i]);
			if ( m[i] < 0 )
			{
				++m[i];
			}

			theta0[i] = bigTheta0 + 3.60985647e+02 * m[i];
			n[i] = m[i] + deltaT / 8.6400e+04;
			ra[i] = Interpolation::calcThreeTabularInterpolation(ra1,
																 ra2,
																 ra3,
																 n[i]);
			dec[i] = Interpolation::calcThreeTabularInterpolation(dec1,
																  dec2,
																  dec3,
																  n[i]);
			
			lha[i] = theta0[i] - longitude - ra[i];
			for ( ; lha[i] > 180 ; lha[i] -= 360 );
			for ( ; lha[i] < -180 ; lha[i] += 360 );
			h[i] = TransformationCoordinates::calcAltInRad(latitude,
														   dec[i],
														   lha[i]);
			h[i] = MathUtil::convRadToDeg(h[i]);
			
			if ( 0 == i )
			{
				deltaM[i] = -lha[i] / 3.60e+02;
			}
			else
			{
				deltaM[i] = ( h[i] - h0 ) / ( 3.60e+02 * cos ( MathUtil::convDegToRad( dec[i] ) ) * cos ( latitudeRad ) * sin ( MathUtil::convDegToRad( lha[i] ) ) );
			}
			
			m[i] += deltaM[i];
		}
		m[i] += ( longitude / 3.60e+02) + ( 1e+00 * timeZone / 2.4e+01 );
	}
}
