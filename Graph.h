#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>


struct edge{
    std::string name;
    int weight;
};

struct vertex{
    std::string name;
    std::vector<edge> edges;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        void displayEdges();
    protected:
    private:
        //vector<edge> edges;
        std::vector<vertex> vertices;

};

#endif // GRAPH_H
