#ifndef _ENVIRONMENTANTSYSTEM_H_
#define _ENVIRONMENTANTSYSTEM_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentAntSystem : public EnvironmentBehaviour
{
public:

	EnvironmentAntSystem();//float evaporationRate);

	void init(EdgeArray* edges);

	void updatePheromone();

private:

    EdgeArray* edges;

};

#endif // _ENVIRONMENTANTSYSTEM_H_
