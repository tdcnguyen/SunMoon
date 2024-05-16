/*
 *  TransformationCoordinates.cpp
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-09.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <iostream>

#include "MathUtil.h"
#include "TransformationCoordinates.h"

double
TransformationCoordinates::calcAltInRad(double obsLatitude,
										double dec,
										double lha)
{
	obsLatitude = MathUtil::convDegToRad(obsLatitude);
	dec = MathUtil::convDegToRad(dec);
	lha = MathUtil::convDegToRad(lha);

	double alt = asin ( sin ( obsLatitude ) * sin ( dec ) + cos ( obsLatitude ) * cos ( dec ) * cos ( lha ) );
	
	return alt;
}

double
TransformationCoordinates::calcDecInRad(double longitude,
										double latitude,
										double obliquity)
{
	longitude = MathUtil::convDegToRad(longitude);
	latitude = MathUtil::convDegToRad(latitude);
	obliquity = MathUtil::convDegToRad(obliquity);

	double dec = asin ( sin ( latitude ) * cos ( obliquity ) + cos ( latitude ) * sin ( obliquity ) * sin ( longitude ) );
	
	return dec;
}

double
TransformationCoordinates::calcRAInRad(double longitude,
									   double latitude,
									   double obliquity)
{
	longitude = MathUtil::convDegToRad(longitude);
	latitude = MathUtil::convDegToRad(latitude);
	obliquity = MathUtil::convDegToRad(obliquity);

	double ra = atan2 ( ( sin ( longitude ) * cos( obliquity ) - tan ( latitude ) * sin( obliquity ) ), cos ( longitude ) );
	
	return ra;
}
