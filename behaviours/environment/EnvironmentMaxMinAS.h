#ifndef _ENVIRONMENTMAXMINAS_H_
#define _ENVIRONMENTMAXMINAS_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentMaxMinAS : public EnvironmentBehaviour
{
public:

	EnvironmentMaxMinAS(float pheroMin);//float evaporationRate);

	void init(EdgeArray* edges);

	void updatePheromone();

	void processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts);

private:

    EdgeArray* edges;
    float pheroMin;

};

#endif // _ENVIRONMENTMAXMINAS_H_
