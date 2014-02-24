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

	void evaporate(float evaporationRate, float pheroMin = 0.0f);
	void incrementPheromone(int nodeA, int nodeB, float pheromoneIncrease);
	void incrementPheromone(int nodeA, int nodeB, float pheromoneIncrease, float pheroMax);// Should I do these as one function with = INFINITY?  Means an extra if in the shorter function if I do that

private:

    float **edgeLengths, **edgePheromones;
    int noOfNodes;
};

#endif // _EDGEARRAY_H_
