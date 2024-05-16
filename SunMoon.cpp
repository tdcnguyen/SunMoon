/*
 *  SunMoon.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>

#include "JulianDay.h"
#include "MathUtil.h"
#include "RisingTransitSetting.h"

#include "SunMoon.h"

void
SunMoon::printMoonRisingSettingTimes(double longitude,
									 double latitude,
									 int year,
									 int month,
									 int day,
									 int timeZone,
									 FILE* pOutFile)
{
	double m[3];
	int hour, minute;
	
	RisingTransitSetting::calcRisingTransitSettingForMoon(longitude,
														  latitude,
														  year,
														  month,
														  day,
														  timeZone,
														  m);
	if ( m[1] < 0 )
	{
		fprintf(pOutFile, "-- --");
	}
	else
	{
		MathUtil::convDayToHm(m[1], &hour, &minute);
		fprintf(pOutFile, "%02d %02d", hour, minute);
	}
	
	fprintf(pOutFile, "  ");
	
	if ( m[2] < 0 )
	{
		fprintf(pOutFile, "-- --");
	}
	else
	{
		MathUtil::convDayToHm(m[2], &hour, &minute);
		fprintf(pOutFile, "%02d %02d", hour, minute);
	}
	
}


void
SunMoon::printMoonRisingSettingTimesForMonth(int year,
											 int month,
											 FILE* pOutFile)
{
	int numDays = SunMoonNs::monthDays[month - 1];
	if ( 2 == month && 1 == JulianDay::isLeapYear(year) )
	{
		++numDays;
	}
	
	int dayOfYear;
	int dayOfMonth;
	int dayOfWeek;
	double longitude, latitude;
	int timeZone;
	
	fprintf(pOutFile,"-----------------------------------------\n");
	fprintf(pOutFile,"\n");
	fprintf(pOutFile,"     MOONRISE AND MOONSET\n");
	fprintf(pOutFile,"       Local Mean Time         Day   Day\n");
	fprintf(pOutFile,"                               of    of\n");
	fprintf(pOutFile,"    Lat. 45       Lat. 50      Week  Mo.\n");
	fprintf(pOutFile,"  Rises  Sets   Rises  Sets\n");
	fprintf(pOutFile,"-----------------------------------------\n");
	fprintf(pOutFile,"  h  m   h  m   h  m   h  m\n");
	
	
	for ( dayOfMonth = 1 ; dayOfMonth <= numDays ; ++dayOfMonth )
	{
		dayOfYear = JulianDay::calcDayOfYear(year, month, dayOfMonth);
		dayOfWeek = JulianDay::calcDayOfWeek(year, month, dayOfMonth);

		fprintf(pOutFile, "  ");
		
		// Lat 45
		longitude = MathUtil::convDmsToDeg(75, 0, 0);
		latitude = MathUtil::convDmsToDeg(45, 0, 0);
		timeZone = -5;
		printMoonRisingSettingTimes(longitude,
									latitude,
									year,
									month,
									dayOfMonth,
									timeZone,
									pOutFile);
		fprintf(pOutFile, "  ");
		
		// Lat 50
		longitude = MathUtil::convDmsToDeg(75, 0, 0);
		latitude = MathUtil::convDmsToDeg(50, 0, 0);
		timeZone = -5;
		printMoonRisingSettingTimes(longitude,
								   latitude,
								   year,
								   month,
								   dayOfMonth,
								   timeZone,
								   pOutFile);
		
		fprintf(pOutFile,"   %s  %3d", SunMoonNs::weekDays[dayOfWeek], dayOfMonth);
		
		fprintf(pOutFile,"\n");
	}
}

void
SunMoon::printSunRisingSettingTimes(double longitude,
									double latitude,
									int year,
									int month,
									int day,
									int timeZone,
									FILE* pOutFile)
{
	double m[3];
	int hour, minute;
	
	RisingTransitSetting::calcRisingTransitSettingForSun(longitude,
														 latitude,
														 year,
														 month,
														 day,
														 timeZone,
														 m);
	if ( m[1] < 0 )
	{
		fprintf(pOutFile, "-- --");
	}
	else
	{
		MathUtil::convDayToHm(m[1], &hour, &minute);
		fprintf(pOutFile, "%02d %02d", hour, minute);
	}
	
	fprintf(pOutFile, "  ");
	
	if ( m[2] < 0 )
	{
		fprintf(pOutFile, "-- --");
	}
	else
	{
		MathUtil::convDayToHm(m[2], &hour, &minute);
		fprintf(pOutFile, "%02d %02d", hour, minute);
	}
	
}


void
SunMoon::printSunRisingSettingTimesForMonth(int year,
											int month,
											FILE* pOutFile)
{
	int numDays = SunMoonNs::monthDays[month - 1];
	if ( 2 == month && 1 == JulianDay::isLeapYear(year) )
	{
		++numDays;
	}
	
	int dayOfYear;
	int dayOfMonth;
	int dayOfWeek;
	double longitude, latitude;
	int timeZone;
	
	fprintf(pOutFile,"--------------------------------------------------------------------------\n");
	fprintf(pOutFile,"\n");
	fprintf(pOutFile,"                                  SUNRISE AND SUNSET\n");
	fprintf(pOutFile," Day Day Day\n");
	fprintf(pOutFile," of  of  of       Ottawa       Toronto      Winnipeg     Vancouver\n");
	fprintf(pOutFile," Yr. Mo. Wk.      E.S.T.        E.S.T.       C.S.T.        P.S.T.\n");
	fprintf(pOutFile,"               Rises  Sets   Rises  Sets   Rises  Sets   Rises  Sets\n");
	fprintf(pOutFile,"--------------------------------------------------------------------------\n");
	fprintf(pOutFile,"               h  m   h  m   h  m   h  m   h  m   h  m   h  m   h  m\n");
	
	for ( dayOfMonth = 1 ; dayOfMonth <= numDays ; ++dayOfMonth )
	{
		dayOfYear = JulianDay::calcDayOfYear(year, month, dayOfMonth);
		dayOfWeek = JulianDay::calcDayOfWeek(year, month, dayOfMonth);
		fprintf(pOutFile,"%3d %3d  %s   ", dayOfYear, dayOfMonth, SunMoonNs::weekDays[dayOfWeek]);
		
		// Ottawa
		longitude = MathUtil::convDmsToDeg(75, 43, 0);
		latitude = MathUtil::convDmsToDeg(45, 25, 0);
		timeZone = -5;
		printSunRisingSettingTimes(longitude,
								   latitude,
								   year,
								   month,
								   dayOfMonth,
								   timeZone,
								   pOutFile);
		fprintf(pOutFile, "  ");
		
		// Toronto
		longitude = MathUtil::convDmsToDeg(79, 25, 0);
		latitude = MathUtil::convDmsToDeg(43, 42, 0);
		timeZone = -5;
		printSunRisingSettingTimes(longitude,
								   latitude,
								   year,
								   month,
								   dayOfMonth,
								   timeZone,
								   pOutFile);
		fprintf(pOutFile, "  ");
		
		// Winnipeg
		longitude = MathUtil::convDmsToDeg(97, 10, 0);
		latitude = MathUtil::convDmsToDeg(49, 53, 0);
		timeZone = -6;
		printSunRisingSettingTimes(longitude,
								   latitude,
								   year,
								   month,
								   dayOfMonth,
								   timeZone,
								   pOutFile);
		fprintf(pOutFile, "  ");
		
		// Vancouver
		longitude = MathUtil::convDmsToDeg(123, 6, 0);
		latitude = MathUtil::convDmsToDeg(49, 13, 0);
		timeZone = -8;
		printSunRisingSettingTimes(longitude,
								   latitude,
								   year,
								   month,
								   dayOfMonth,
								   timeZone,
								   pOutFile);
		
		fprintf(pOutFile,"\n");
	}
}
