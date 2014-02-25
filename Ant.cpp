#include "Ant.h"

Ant::Ant(int nodeCurrent, EdgeArray *edges, MoveBehaviour *moveBeh, PheromoneBehaviour *pheroBeh)
{
    this->nodeCurrent = nodeCurrent;
    this->edges = edges;
    this->moveBeh = moveBeh;
    this->pheroBeh = pheroBeh;

    nodesVisited.push_back(nodeCurrent);

    lengthOfPath = 0.0f;
}

void Ant::move()
{
    int nodeToMoveTo = moveBeh->generateMove(&nodesVisited);

    // Maybe have some way to return "done" or "stuck" or whatever from here, can check if -1 is returned to here as well (or just done when actually finished)

    lengthOfPath += edges->getLength(nodeCurrent, nodeToMoveTo);

    nodeCurrent = nodeToMoveTo;
    nodesVisited.push_back(nodeCurrent);
}

void Ant::updatePheromone()
{
    pheroBeh->updatePheromone(&nodesVisited, lengthOfPath);// Don't like passing arguments here as there's it's not easy to have different args for different behaviours
}

float Ant::getLengthOfPath()
{
    return lengthOfPath;
}

void Ant::reset()// Reset to original node
{
    lengthOfPath = 0;
    nodeCurrent = nodesVisited.at(0);

    nodesVisited.clear();
    nodesVisited.push_back(nodeCurrent);
}

void Ant::reset(int nodeNew)// Reset to a specified node
{
    lengthOfPath = 0;
    nodeCurrent = nodeNew;

    nodesVisited.clear();
    nodesVisited.push_back(nodeCurrent);
}

std::vector<int> Ant::getNodesVisited()
{
    return nodesVisited;
}
