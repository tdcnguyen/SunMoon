/*
 *  SiderealTime.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SiderealTime_h
#define SiderealTime_h

class SiderealTime
{
public:
	static double calcApparentSiderealTimeInDeg(int year,
												int month,
												double day);
	static double calcApparentSiderealTimeInDeg(double jd);
	static double calcMeanSiderealTimeInDeg(int year,
											int month,
											double day);
	static double calcMeanSiderealTimeInDeg(double jd);
};

#endif // SiderealTime_h
