#ifndef _ENVIRONMENTRANKBASEDAS_H_
#define _ENVIRONMENTRANKBASEDAS_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentRankBasedAS : public EnvironmentBehaviour
{
public:

	EnvironmentRankBasedAS(EdgeArray *edges, float evapRate, int numberOfAntsThatUpdate, int numberOfElitistAnts);

	void updatePheromone();

	void processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts);

	void updateParams(struct paramData *data);

private:

    EdgeArray* edges;

    float evapRate;
    int numberOfAntsThatUpdate, numberOfElitistAnts;

    float lengthOfBestPathSoFar;
    std::vector<int> nodesOfBestPathSoFar;
};

#endif // _ENVIRONMENTRANKBASEDAS_H_
