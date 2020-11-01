#ifndef FIND_AND_IDENTIFY_H

#define FIND_AND_IDENTIFY_H

#include <Arduino.h>
#include <math.h>

struct Date {int d, m, y;};
//Find and Identify

// AD is angle of declination; RA is right ascension ; RA H M S hours minutes seconds

int countLeapYears(Date d);

int getDifference(Date dt1, Date dt2);

float angleBehindTheSun(float RAH,float RAM, float RAS,Date dt2);

float declinationAngle(float lattitude, float AD);
#endif