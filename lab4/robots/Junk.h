/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Adam Ljung. Liu-id: Adalj586
 * Isak Skott. Liu-id: Isask052
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>
#include "Robot.h"

class Junk : public Robot {
public:
    //Constructor
    Junk(const Point& p);
    void moveTowards(const Unit&) override; // Compiler will help to check if we really override this function, will crash if we dont
    void doCrash() override;
    bool justCrashed() const override;
    bool canMove() const override;
    //To be able to copy
    Junk* clone() const override;
    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
};

#endif // JUNK_H
