#ifndef _EDGEARRAY_H_
#define _EDGEARRAY_H_

class EdgeArray
{
public:

	EdgeArray(int noOfNodes);
	//~EdgeArray();

	void addEdge(int nodeA, int nodeB, float distance, float pheromoneLevel);

	int getNoOfNodes();

	float getLength(int nodeA, int nodeB);
	float getPheromone(int nodeA, int nodeB);

	void evaporate(float evaporationRate);
	void incrementPheromone(int nodeA, int nodeB, float pheromoneIncrease);

private:

    float **edgeLengths, **edgePheromones;
    int noOfNodes;
};

#endif // _EDGEARRAY_H_
