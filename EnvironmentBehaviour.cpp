#include "EnvironmentBehaviour.h"

EnvironmentBehaviour::~EnvironmentBehaviour()
{

}

void EnvironmentBehaviour::processAntList(std::vector<Ant*> *ants, std::vector<Ant*> *processedAnts)
{
    processedAnts = ants;
}
