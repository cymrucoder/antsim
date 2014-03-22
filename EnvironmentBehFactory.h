#ifndef _ENVIRONMENTBEHFACTORY_H_
#define _ENVIRONMENTBEHFACTORY_H_

#include "behaviours/environment/EnvironmentAntSystem.h"
#include "behaviours/environment/EnvironmentMaxMinAS.h"
#include "behaviours/environment/EnvironmentRankBasedAS.h"

#define ENVIRONMENT_BEH_TYPE_AS 0
#define ENVIRONMENT_BEH_TYPE_MMAS 1
#define ENVIRONMENT_BEH_TYPE_RBAS 2

class EnvironmentBehFactory
{
	public:
		EnvironmentBehFactory();
		//~EnvironmentBehFactory();

        EnvironmentBehaviour* makeEnvironmentBehaviour(int environmentBehaviourType, EdgeArray *edges);

	private:

};


#endif // _ENVIRONMENTBEHFACTORY_H_

