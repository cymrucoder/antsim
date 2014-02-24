#ifndef _ENVIRONMENTAMAXMINAS_H_
#define _ENVIRONMENTAMAXMINAS_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentMaxMinAS : public EnvironmentBehaviour
{
public:

	EnvironmentMaxMinAS(float pheroMin);//float evaporationRate);

	void init(EdgeArray* edges);

	void updatePheromone();

private:

    EdgeArray* edges;
    float pheroMax, pheroMin;

};

#endif // _ENVIRONMENTAMAXMINAS_H_

