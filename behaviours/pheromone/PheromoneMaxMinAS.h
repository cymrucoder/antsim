#ifndef _PHEROMONEMAXMINAS_H_
#define _PHEROMONEMAXMINAS_H_

#include "../../PheromoneBehaviour.h"

class PheromoneMaxMinAS : public PheromoneBehaviour
{
public:

	PheromoneMaxMinAS(EdgeArray* edges, float pheroMax);

	void updatePheromone(std::vector<int> *nodesVisited, float lengthOfPath);

	void updateParams(struct paramData *data);

private:

    EdgeArray* edges;

    float pheroMax;
};

#endif // _PHEROMONEMAXMINAS_H_
