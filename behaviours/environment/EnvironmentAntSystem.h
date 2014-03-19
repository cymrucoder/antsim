#ifndef _ENVIRONMENTANTSYSTEM_H_
#define _ENVIRONMENTANTSYSTEM_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentAntSystem : public EnvironmentBehaviour
{
public:

	EnvironmentAntSystem(EdgeArray *edges, float evapRate);

	void updatePheromone();

	void updateParams(struct paramData *data);

private:

    EdgeArray* edges;

    float evapRate;
};

#endif // _ENVIRONMENTANTSYSTEM_H_
