/*
 *  MathUtil.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-08.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MathUtil_h
#define MathUtil_h

class MathUtil
{
public:
	static double convArcsecToDeg(double arcsec);
	static double convArcsecToRad(double arcsec);
	static void convDayToHm(double day,
							int* pHour,
							int* pMinute);
	static void convDayToHms(double day,
							 int* pHour,
							 int* pMinute,
							 double* pSecond);
	static double convDegToArcsec(double deg);
	static double convDegToDeg(double deg);
	static void convDegToDms(double deg,
							 int* pDeg,
							 int* pArcmin,
							 double* pArcsec);
	static double convDegToRad(double deg);
	static double convDmsToDeg(int deg,
							   int arcmin,
							   double arcsec);
	static double convRadToArcsec(double rad);
	static double convRadToDeg(double rad);
};

#endif // MathUtil_h
