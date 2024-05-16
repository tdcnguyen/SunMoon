/*
 *  RisingTransitSetting.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef RisingTransitSetting_h
#define RisingTransitSetting_h

class RisingTransitSetting
{
public:
	static void calcRisingTransitSettingForMoon(double longitude,
											   double latitude,
											   int year,
											   int month,
											   int day,
											   int timeZone,
											   double m[]);
	static void calcRisingTransitSettingForSun(double longitude,
											   double latitude,
											   int year,
											   int month,
											   int day,
											   int timeZone,
											   double m[]);
};

#endif // RisingTransitSetting_h
