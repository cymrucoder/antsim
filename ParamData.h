#ifndef _PARAMDATA_H_
#define _PARAMDATA_H_

struct paramData
{
    float importancePhero;
    float importanceDistance;
    float evapRate;
    float pheroNumerator;

    int noOfElitistAnts;
    int noOfRankedAnts;
    float pheroMax;
    float pheroMin;
};

#endif // _PARAMDATA_H_
