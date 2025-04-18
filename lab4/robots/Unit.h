/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 * Adam Ljung. Liu-id: Adalj586
 * Isak Skott. Liu-id: Isask052
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>

/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:

    /*
     * Create a unit at a random position
     */
    Unit();

    /*
    * Create unit at given point
    */
    Unit(const Point& p);

    virtual ~Unit(){};

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;


    /*
    * Take one step closer to u
    */
    virtual void moveTowards(const Unit&);

    virtual void draw(QGraphicsScene* scene) const;
    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;
    private:
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();
};

#endif // UNIT_H
