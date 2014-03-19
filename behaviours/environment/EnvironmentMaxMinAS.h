#ifndef _ENVIRONMENTMAXMINAS_H_
#define _ENVIRONMENTMAXMINAS_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentMaxMinAS : public EnvironmentBehaviour
{
public:

	EnvironmentMaxMinAS(EdgeArray *edges, float evapRate, float pheroMin);

	void updatePheromone();

	void processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts);

	void updateParams(struct paramData *data);

private:

    EdgeArray* edges;

    float pheroMin;
    float evapRate;
};

#endif // _ENVIRONMENTMAXMINAS_H_
