#include <iostream>

#include "DynamicalUniversalTime.h"
#include "JulianDay.h"
#include "MathUtil.h"
#include "NutationObliquity.h"
#include "PositionMoon.h"
#include "RisingTransitSetting.h"
#include "SiderealTime.h"
#include "SolarCoordinates.h"
#include "TransformationCoordinates.h"

#include "SunMoon.h"

int main (int argc, char * const argv[]) {
    // insert code here...
//    std::cout << "Hello, World!\n";
	/*	
	// Dynamical Universal Time tests
	 printf("\nDynamical Universal Time test (Year 2000):\n");
	 double deltaT = DynamicalUniversalTime::calcDeltaTInSec(2000);
	 printf("deltaT [65] = %le\n", deltaT);
	 
	 // Julian Day tests
	 printf("\nJulian Day test (JD 2 436 116.31):\n");
	 int year, month;
	 double day;
	 JulianDay::calcDateFromJD(2.43611631e+06, &year, &month, &day);
	 printf("date [1957 10 4.81] = %d %d %.12le\n", year, month, day);
	 
	 printf("\nJulian Day test (Date 1957 October 4.81):\n");
	 double jd = JulianDay::calcJD(1957, 10, 4.81);
	 printf("jd [2 436 116.31] = %.12le\n", jd);
	 
	 // Nutation Obliquity tests
	 printf("\nNutation Obliquity test (Date 1987 April 10 at 0h TD):\n");
	 double deltaPsi = NutationObliquity::calcNutationLongitudeInArcsec(2.4468955e+06);
	 double deltaEpsilon = NutationObliquity::calcNutationObliquityInArcsec(2.4468955e+06);
	 double epsilon0 = NutationObliquity::calcMeanObliquityInArcsec(2.4468955e+06);
	 epsilon0 = MathUtil::convArcsecToDeg(epsilon0);
	 int intdeg, arcmin;
	 double arcsec;
	 MathUtil::convDegToDms(epsilon0, &intdeg, &arcmin, &arcsec);
	 printf("deltaPsi [-3.778""] = %.12le\n", deltaPsi);
	 printf("deltaEpsilon [+9.443""] = %.12le\n", deltaEpsilon);
	 printf("epsilon0 [23d 26" 27.407""] = %.12le = %dd %d" %.12le""\n", epsilon0, intdeg, arcmin, arcsec);
	 double epsilon = NutationObliquity::calcTrueObliquityInArcsec(2.4468955e+06);
	 epsilon = MathUtil::convArcsecToDeg(epsilon);
	 MathUtil::convDegToDms(epsilon, &intdeg, &arcmin, &arcsec);
	 printf("epsilon [23d 26" 27.850""] = %.12le = %dd %d" %.12le""\n", epsilon, intdeg, arcmin, arcsec);
	 
	 // Sidereal Time tests
	 printf("\nSidereal Time test (Date 1987 April 10 at 0h UT):\n");
	 double siderealTime = SiderealTime::calcMeanSiderealTimeInDeg(1987, 4, 10);
	 jd = JulianDay::calcJD(1987, 4, 10);
	 int hour, minute;
	 double second;
	 day = siderealTime / 3.60e+02;
	 MathUtil::convDayToHms(day, &hour, &minute, &second);
	 printf("jd [2 446 895.5] = %.12le\n", jd);
	 printf("Mean Sidereal Time [13h 10m 46.3668s] = %dh %dm %.12es\n", hour, minute, second);
	 siderealTime = SiderealTime::calcApparentSiderealTimeInDeg(1987, 4, 10);
	 day = siderealTime / 3.60e+02;
	 MathUtil::convDayToHms(day, &hour, &minute, &second);
	 printf("Apparent Sidereal Time [13h 10m 46.1351s] = %dh %dm %.12es\n", hour, minute, second);
	 
	 // Transformation Coordinates tests
	 printf("\nTransformation Coordinates test (lon 113.215630d, lat +6.684170d):\n");
	 epsilon = MathUtil::convArcsecToDeg(NutationObliquity::calcTrueObliquityInArcsec(JulianDay::calcJD(2000, 1, 1)));
	 double ra = TransformationCoordinates::calcRAInRad(1.13215630e+02, 6.684170e+00, epsilon);
	 ra = MathUtil::convRadToDeg(ra);
	 double dec = TransformationCoordinates::calcDecInRad(1.13215630e+02, 6.684170e+00, epsilon);
	 dec = MathUtil::convRadToDeg(dec);
	 printf("epsilon [23.4392911d] = %.12le\n", epsilon);
	 printf("ra [116.328942d] = %.12le\n", ra);
	 printf("dec [28.026183d] = %.12le\n", dec);
	 
	 // Solar Coordinates tests
	 printf("\nSolar Coordinates test (1992 October 13 at 0th TD):\n");
	 double jde = JulianDay::calcJD(1992, 10, 13);
	 double geoSolarLongitude = SolarCoordinates::calcGeometricLongitudeInDeg(jde);
	 geoSolarLongitude = MathUtil::convDegToDeg(geoSolarLongitude);
	 double geoSolarLatitude = SolarCoordinates::calcGeometricLatitudeInDeg(jde);
	 geoSolarLatitude = MathUtil::convDegToDeg(geoSolarLatitude);
	 double appSolarLongitude = SolarCoordinates::calcApparentLongitudeInDeg(jde);
	 appSolarLongitude = MathUtil::convDegToDeg(appSolarLongitude);
	 double appSolarLatitude = SolarCoordinates::calcApparentLatitudeInDeg(jde);
	 appSolarLatitude = MathUtil::convDegToDeg(appSolarLatitude);
	 
	 ra = SolarCoordinates::calcApparentRAInDeg(jde);
	 ra = MathUtil::convDegToDeg(ra);
	 dec = SolarCoordinates::calcApparentDecInDeg(jde);
	 
	 printf("geoSolar longitude [199.907372d] = %.12le\n", geoSolarLongitude);
	 printf("geoSolar latitude [0.000179d] = %.12le\n", geoSolarLatitude);
	 MathUtil::convDegToDms(appSolarLongitude, &intdeg, &arcmin, &arcsec);
	 printf("appSolar longitude [199d 54" 21.818""] = %.12le = %dd %dm %.12les\n", appSolarLongitude, intdeg, arcmin, arcsec);
	 MathUtil::convDegToDms(appSolarLatitude, &intdeg, &arcmin, &arcsec);
	 printf("appSolar latitude [0d 0" 0.62""] = %.12le = %dd %dm %.12les\n", appSolarLatitude, intdeg, arcmin, arcsec);
	 printf("ra [198.378178d] = %.12le\n", ra);
	 printf("dec [-7.783871d] = %.12le\n", dec);
	 
	 // Position Moon tests
	 printf("\nPosition Moon test (1992 April 12 at 0th TD):\n");
	 jde = JulianDay::calcJD(1992, 4, 12);
	 double geoLunarLongitude = PositionMoon::calcGeocentricLongitudeInDeg(jde);
	 geoLunarLongitude = MathUtil::convDegToDeg(geoLunarLongitude);
	 double geoLunarLatitude = PositionMoon::calcGeocentricLatitudeInDeg(jde);
	 double distance = PositionMoon::calcDistanceInKm(jde);
	 double horizontalParallax = PositionMoon::calcHorizontalParallaxInDeg(jde);
	 double appLunarLongitude = PositionMoon::calcApparentLongitudeInDeg(jde);
	 appLunarLongitude = MathUtil::convDegToDeg(appLunarLongitude);
	 double appLunarLatitude = PositionMoon::calcApparentLatitudeInDeg(jde);
	 
	 ra = PositionMoon::calcApparentRAInDeg(jde);
	 ra = MathUtil::convDegToDeg(ra);
	 dec = PositionMoon::calcApparentDecInDeg(jde);
	 
	 printf("geoLunar longitude [133.162655d] = %.12le\n", geoLunarLongitude);
	 printf("geoLunar latitude [-3.229126d] = %.12le\n", geoLunarLatitude);
	 printf("distance [368409.7 km] = %.12le\n", distance);
	 printf("horizontal parallax [0.991990d] = %.12le\n", horizontalParallax);
	 printf("appLunar longitude [133.167265d] = %.12le\n", appLunarLongitude);
	 printf("appLunar latitude [-3.229126d] = %.12le\n", appLunarLatitude);
	 printf("ra [134.688470d] = %.12le\n", ra);
	 printf("dec [13.768368d] = %.12le\n", dec);
	 */
/*	
	// Rising, Transit, Setting tests
	printf("\nRising, Transit, Setting (2005 03 23):\n");
	double m[3];
	RisingTransitSetting::calcRisingTransitSettingForSun(79.41666667, 43.7, 2005, 6, 20, -5, m);
	int hour, minute;
	for ( int i = 0 ; i < 3 ; ++i )
	{
		MathUtil::convDayToHm(m[i], &hour, &minute);
		if ( hour < 0 )
		{
			hour += 24;
		}
		printf("Sun m[%d]: %.12le = %02d %02d\n", i, m[i], hour, minute);
	}

	
	RisingTransitSetting::calcRisingTransitSettingForMoon(0, 50, 2006, 1, 1, 0, m);
	for ( int i = 0 ; i < 3 ; ++i )
	{
		MathUtil::convDayToHm(m[i], &hour, &minute);
		if ( hour < 0 )
		{
			hour += 24;
		}
		printf("Moon m[%d]: %.12le = %02d %02d\n", i, m[i], hour, minute);
	}
*/

    printf("Choose options\n\n");
    printf("1 for sunset and sunrise times only\n");
    printf("2 for moonrise and moonset times only\n");
	printf("0 to exit program\n\n");
	int choice;
	scanf("%d", &choice);
	
	if ( 1 == choice )
	{
		printf("Enter the year and month for sun rise/set times\n");
		int year, month;
		scanf("%d %d", &year, &month);
		
		printf("Enter the name of file with sun times\n");
		char outFileName[256];
		scanf("%s", outFileName);

		FILE* pOutFile;
		if ( ! (pOutFile = fopen(outFileName, "w") ) )
		{
			printf("Cannot open file '%s'.\n", outFileName);
		}
		SunMoon::printSunRisingSettingTimesForMonth(year, month, pOutFile);
		fclose(pOutFile);		
	}
	else if ( 2 == choice )
	{
		printf("Enter the year and month for moon rise/set times\n");
		int year, month;
		scanf("%d %d", &year, &month);
		
		printf("Enter the name of file with moon times\n");
		char outFileName[256];
		scanf("%s", outFileName);

		FILE* pOutFile;
		if ( ! (pOutFile = fopen(outFileName, "w") ) )
		{
			printf("Cannot open file '%s'.\n", outFileName);
		}
		SunMoon::printMoonRisingSettingTimesForMonth(year, month, pOutFile);
		fclose(pOutFile);		
	}


    return 0;
}
