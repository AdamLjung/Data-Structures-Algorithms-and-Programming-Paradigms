// Adam Ljung. Liu-ID: Adalj586
// Isak Skott. Liu-ID: Isask052

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    //Constructor
    Tour();
    //Constructor
    Tour(Point a, Point b, Point c, Point d);
    //Destructor
    ~Tour();
    //Prints the points in the linked list
    void show() const;
    //Draws the routes between points
    void draw(QGraphicsScene* scene) const;
    //Returns the size of the linked list
    int size() const;
    //Returns the total distance of the linked list
    double distance() const;
    //Inserts a point using nearest neighbour algorithm
    void insertNearest(Point p);
    //Inserts a point using smallest insertion algorithm
    void insertSmallest(Point p);

private:
    //First point
    Node* headerPoint = nullptr;
};

#endif // TOUR_H
