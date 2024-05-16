/*
 *  SunMoon.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SunMoon_h
#define SunMoon_h

class SunMoon
{
public:
	static void printMoonRisingSettingTimes(double longitude,
											double latitude,
											int year,
											int month,
											int day,
											int timeZone,
											FILE* pOutFile);
	static void printMoonRisingSettingTimesForMonth(int year,
													int month,
													FILE* pOutFile);
	static void printSunRisingSettingTimes(double longitude,
										   double latitude,
										   int year,
										   int month,
										   int day,
										   int timeZone,
										   FILE* pOutFile);
	static void printSunRisingSettingTimesForMonth(int year,
												   int month,
												   FILE* pOutFile);
};

namespace SunMoonNs
{
	const int monthDays[12] =
	{31,
		28,
		31,
		30,
		31,
		30,
		31,
		31,
		30,
		31,
		30,
		31};
	
	const char weekDays[7][4] =
	{"Mon",
		"Tue",
		"Wed",
		"Thu",
		"Fri",
		"Sat",
		"Sun"};
}

#endif // SunMoon_h