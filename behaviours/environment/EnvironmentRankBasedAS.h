#ifndef _ENVIRONMENTRANKBASEDAS_H_
#define _ENVIRONMENTRANKBASEDAS_H_

#include "../../EnvironmentBehaviour.h"

class EnvironmentRankBasedAS : public EnvironmentBehaviour
{
public:

	EnvironmentRankBasedAS(int numberOfAntsThatUpdate, int numberOfElitistAnts);

	void init(EdgeArray* edges);

	void updatePheromone();

	void processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts);

private:

    EdgeArray* edges;
    int numberOfAntsThatUpdate, numberOfElitistAnts;

    float lengthOfBestPathSoFar;
    std::vector<int> nodesOfBestPathSoFar;

};

#endif // _ENVIRONMENTRANKBASEDAS_H_
