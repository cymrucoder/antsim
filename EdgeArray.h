#ifndef _EDGEARRAY_H_
#define _EDGEARRAY_H_

class EdgeArray
{
public:

	EdgeArray(int noOfNodes, float initialPheromoneLevel);
	~EdgeArray();

	bool addEdge(int nodeA, int nodeB, float distance);

	int getNoOfNodes();

	float getLength(int nodeA, int nodeB);
	float getPheromone(int nodeA, int nodeB);

	void evaporate(float evaporationRate, float pheroMin = 0.0f);
	void incrementPheromone(int nodeA, int nodeB, float pheromoneIncrease);
	void incrementPheromone(int nodeA, int nodeB, float pheromoneIncrease, float pheroMax);

    void reset();

private:

    float **edgeLengths, **edgePheromones;
    int noOfNodes;
    float initialPheromoneLevel;
};

#endif // _EDGEARRAY_H_
