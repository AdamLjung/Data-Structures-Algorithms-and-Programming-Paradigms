// Adam Ljung. Liu-ID: Adalj586
// Isak Skott. Liu-ID: Isask052


#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"




Tour::Tour()
{
}

Tour::~Tour()
{
    if(headerPoint == nullptr){
        return;
    }
    Node* curr = headerPoint;
    while(curr->next != headerPoint){
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete curr;

}


void Tour::show() const
{
    if(headerPoint == nullptr){
        return;
    }
    Node* currPoint = headerPoint;
    while(currPoint->next != headerPoint){
        cout << currPoint->point << endl;
        currPoint = currPoint->next;
        //For the last node
        if(currPoint->next == headerPoint){
            cout << currPoint->point << endl;
        }
    }

}

//Draws the routes of the nodes
void Tour::draw(QGraphicsScene *scene) const
{
    if(headerPoint == nullptr){
        return;
    }
    //clears scene
    scene->clear();

    Node* curr = headerPoint;
    Node* nextNode = curr->next;

    while(nextNode->next != headerPoint){
        curr->point.drawTo(nextNode->point, scene);
        curr = curr->next;
        nextNode = nextNode->next;
    }

    //To draw last line, from last node to headernode
    curr->point.drawTo(headerPoint->point, scene);

}

int Tour::size() const
{
    if(headerPoint == nullptr){
        return 0;
    }
    int counter = 0;
    Node* currPoint = headerPoint;
    while(currPoint->next != headerPoint){

        counter++;
        currPoint = currPoint->next;
        //For the last node
        if(currPoint->next == headerPoint){
            counter++;
        }
    }
    return counter;
}

double Tour::distance() const
{

    double totalDistance = 0;
    double tempDistance = 0;
    Node* pointStart = headerPoint;
    Node* pointNext = pointStart->next;


    while(pointNext != headerPoint){

        tempDistance = pointStart->point.distanceTo(pointNext->point);
        totalDistance += tempDistance;
        pointStart = pointStart->next;
        pointNext = pointNext->next;
    }
    totalDistance += pointStart->point.distanceTo(pointNext->point);
    return totalDistance;
}

void Tour::insertNearest(Point p)
{
   if(headerPoint == nullptr){
      headerPoint = new Node(p, nullptr);
      headerPoint->next = headerPoint;
      return;
   }
   Node* curr = headerPoint;
   //To not point at null at the the end if the list only contains one node
   Node* nearestNeighbour = curr;
   double tempDistance;
   //first distance
   double minDistance = curr->point.distanceTo(p);

   curr = curr->next;
   while(curr != headerPoint){

        tempDistance = curr->point.distanceTo(p);
        if(tempDistance < minDistance){
           minDistance = tempDistance;
           nearestNeighbour = curr;
        }
        curr = curr->next;
   }
   Node* insertNearest = new Node(p,nearestNeighbour->next);
   nearestNeighbour->next = insertNearest;
}

void Tour::insertSmallest(Point p)
{
    if(headerPoint == nullptr){
       headerPoint = new Node(p, nullptr);
       headerPoint->next = headerPoint;
       return;
    }

    Node* curr = headerPoint;
    Node* winnerNode = curr;
    double nodeDistance = 0;
    double pointDistance = 0;
    double nextPointDistance = 0;
    double currentDistance = 0;
    double minDistance = 10000000;
    while(curr->next != headerPoint){

       if(curr->next != headerPoint){
           nodeDistance = curr->point.distanceTo(curr->next->point);
           pointDistance = curr->point.distanceTo(p);
           nextPointDistance = curr->next->point.distanceTo(p);
           currentDistance = pointDistance + nextPointDistance- nodeDistance;
       }
       if(currentDistance < minDistance){
           minDistance = currentDistance;
           winnerNode = curr;
       }
       curr = curr->next;
    }
    Node* insertNode = new Node(p, winnerNode->next);
    winnerNode->next = insertNode;
}



Tour::Tour(Point a, Point b, Point c, Point d){
    headerPoint = new Node(a, nullptr);
    headerPoint->next = new Node(b, nullptr);
    headerPoint->next->next = new Node(c, nullptr);
    headerPoint->next->next->next = new Node(d, nullptr);
}

