// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <queue>
#include <stack>
#include <set>
#include "pqueue.h"
using namespace std;
bool dfs(BasicGraph& graph, Vertex* start, Vertex* end, vector<Vertex*> path){

    start->visited = true;
    start->setColor(GREEN);
    path.push_back(start);

    for(Node* node: graph.getNeighbors(start)){
        if(start == end){
            return true;
        }else if(node->visited == false){
            node->setColor(GRAY);
            if(dfs(graph, node, end, path)){
                return true;
            }
            path.pop_back();
            node->setColor(GRAY);
        }
    }
    return false;

}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    dfs(graph, start, end, path);

    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    queue<Vertex*> theQueue;
    theQueue.push(start);
    start->visited = true;
    while(!theQueue.empty()){
        Vertex* checkNode = theQueue.front();
        theQueue.pop();
        checkNode->setColor(GREEN);
        if(checkNode == end){
            break;
        }
        for(Node* node: graph.getNeighbors(checkNode)){
            if(node->visited == false){
                theQueue.push(node);
                node->setColor(YELLOW);
                node->visited = true;
            }
        }
    }
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    start->setColor(GREEN);
    start->visited = true;
    PriorityQueue<Node*> pqueue;
    for(Vertex* node: graph.getNodeSet()){
        node->cost = INFINITY;
        pqueue.enqueue(node, INFINITY);
    }
    start->cost = 0.0;
    pqueue.enqueue(start, 0.0);

    while(!pqueue.isEmpty()){
        Node* node = pqueue.dequeue(); //First node in prioque, smallest
        node->setColor(GREEN);
        node->visited = true;
        if(node == end){ // found end
            break;
        }
        for(Vertex* edge: graph.getNeighbors(node)){
            if(edge->visited == false){
                double cost = node->cost + graph.getEdge(node, edge)->cost;
                if(cost < edge->cost){
                    edge->cost = cost;
                    edge->previous = node;
                    pqueue.changePriority(edge, cost);
                    edge->setColor(YELLOW);
                }}
        }
    }

    return path;
}


vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    start->setColor(GREEN);
    start->visited = true;
    PriorityQueue<Node*> pqueue;
    for(Vertex* node: graph.getNodeSet()){
        node->cost = INFINITY;
        pqueue.enqueue(node, INFINITY);
    }
    start->cost = 0.0;
    pqueue.enqueue(start, start->heuristic(end));

    while(!pqueue.isEmpty()){
        Node* node = pqueue.dequeue(); //First node in prioque, smallest
        node->setColor(GREEN);
        node->visited = true;
        if(node == end){ // found end
            break;
        }
        for(Vertex* edge: graph.getNeighbors(node)){
            if(edge->visited == false){
                double cost = node->cost + graph.getEdge(node, edge)->cost;
                if(cost < edge->cost){
                    edge->cost = cost;
                    edge->previous = node;
                    pqueue.changePriority(edge, cost+edge->heuristic(end));
                    edge->setColor(YELLOW);
                }}
        }
    }



    return path;
}

































