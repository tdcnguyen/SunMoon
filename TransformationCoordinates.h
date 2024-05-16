/*
 *  TransformationCoordinates.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-09.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TransformationCoordinates_h
#define TransformationCoordinates_h

class TransformationCoordinates
{
public:
	static double calcAltInRad(double obsLatitude,
							   double dec,
							   double lha);
	static double calcDecInRad(double longitude,
							   double latitude,
							   double obliquity);
	static double calcRAInRad(double longitude,
							  double latitude,
							  double obliquity);
};

#endif // TransformationCoordinates_h
