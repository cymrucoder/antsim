#ifndef _PHEROMONEBEHFACTORY_H_
#define _PHEROMONEBEHFACTORY_H_

#include "behaviours/pheromone/PheromoneAntSystem.h"
#include "behaviours/pheromone/PheromoneMaxMinAS.h"

#define PHEROMONE_BEH_TYPE_AS 0
#define PHEROMONE_BEH_TYPE_MMAS 1

class PheromoneBehFactory
{
	public:
		PheromoneBehFactory();
		//~PheromoneBehFactory();

        PheromoneBehaviour* makePheromoneBehaviour(int pheromoneBehType, EdgeArray* edges);

	private:

};

#endif // _PHEROMONEBEHFACTORY_H_

