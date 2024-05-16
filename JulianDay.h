/*
 *  JulianDay.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef JulianDay_h
#define JulianDay_h

class JulianDay
{
public:
	static void calcDateFromJD(double jd,
							   int* pYear,
							   int* pMonth,
							   double* pDay);
	static int calcDayOfWeek(int year,
							 int month,
							 int day);
	static int calcDayOfYear(int year,
							 int month,
							 int day);
	static double calcJD(int year,
						 int month,
						 double day);
	static double calcJDE(int year,
						  int month,
						  double day);
	static double convJDtoJDE(double jd);
	static int isLeapYear(int year);
};

#endif // JulianDay_h
