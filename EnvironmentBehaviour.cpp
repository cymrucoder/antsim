#include "EnvironmentBehaviour.h"

EnvironmentBehaviour::~EnvironmentBehaviour()
{

}

/*int EnvironmentBehaviour::getHowManyAntsUpdate()
{
    return howManyAntsUpdate;
}*/

void EnvironmentBehaviour::processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts)
{
    processedAnts = ants;
}
