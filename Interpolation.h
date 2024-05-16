/*
 *  Interpolation.h
 *  SunMoon
 *
 *  Created by Duy Cuong Nguyen on 2005-06-09.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef Interpolation_h
#define Interpolation_h

class Interpolation
{
public:
	static double calcThreeTabularInterpolation(double x0,
												double x1,
												double x2,
												double n);
};

#endif // Interpolation_h
