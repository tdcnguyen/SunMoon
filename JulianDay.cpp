/*
 *  JulianDay.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "DynamicalUniversalTime.h"

#include "JulianDay.h"

void
JulianDay::calcDateFromJD(double jd,
						  int* pYear,
						  int* pMonth,
						  double* pDay)
{
	jd += 0.5;
	
	int z = int ( jd );
	double f = jd - z;
	
	int a;
	if ( z < 2.299161e+06 )
	{
		a = z;
	}
	else
	{
		int alpha = int ( ( z - 1.86721625e+06 ) / 3.652425e+04 );
		a = z + 1 + alpha - int ( alpha / 4 );
	}
	
	int b = a + 1524;
	int c = int ( ( -1.221e+02 + b ) / 3.6525e+02 );
	int d = int ( 3.6525e+02 * c );
	int e = int ( 1e+00 * ( b - d ) / 3.06001e+01 );
	
	*pDay = f + b - d - int ( 3.06001e+01 * e );
	
	if ( e < 14 )
	{
		*pMonth = e - 1;
	}
	else // e == 14 || e == 15
	{
		*pMonth = e - 13;
	}
	
	if ( *pMonth > 2 )
	{
		*pYear = c - 4716;
	}
	else // m == 1 || m == 2
	{
		*pYear = c - 4715;
	}
}

int
JulianDay::calcDayOfWeek(int year,
						 int month,
						 int day)
{
	int jd = int ( calcJD( year, month, day) + 0.5e+00 );
	
	int dayOfWeek = jd % 7;
	
	return dayOfWeek;
}

int
JulianDay::calcDayOfYear(int year,
						 int month,
						 int day)
{
	int dayOfYear = int ( 275 * month / 9 )
	- ( ( 2 - isLeapYear(year) ) * int ( ( month + 9 ) / 12 ) )
	+ day
	- 30;
	
	return dayOfYear;
}

double
JulianDay::calcJD(int year,
				  int month,
				  double day)
{
	if ( 1 == month || 2 == month )
	{
		--year;
		month += 12;
	}
	
	int a = int ( year / 100 );
	int b = 2 - a + int ( a / 4 );
	
	double jd = int ( 3.6525e+02 * ( year + 4.716e+03 ) )
		+ int ( 3.06001e+01 * ( month + 1e+00 ) )
		+ day
		+ b
		- 1.5245e+03;
	
	return jd;
}

double
JulianDay::calcJDE(int year,
				   int month,
				   double day)
{
	double jd = calcJD(year,
					   month,
					   day);
	
	double jde = jd
		+ ( DynamicalUniversalTime::calcDeltaTInSec(year) / 8.6400e+04 );
	
	return jde;
}

double
JulianDay::convJDtoJDE(double jd)
{
	int year, month;
	double day;
	
	calcDateFromJD(jd,
				   &year,
				   &month,
				   &day);
	
	double jde = calcJDE(year,
						 month,
						 day);
	
	return jde;
}

int
JulianDay::isLeapYear(int year)
{
	int leapYearFlag = ( year % 4 == 0 ) && ( ( year % 100 != 0 ) || ( year % 400 == 0 ) ) ? 1 : 0;
	
	return leapYearFlag;
}
