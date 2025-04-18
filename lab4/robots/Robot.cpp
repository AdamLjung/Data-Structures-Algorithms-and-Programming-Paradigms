/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "Robot.h"
#include "constants.h"

Robot::Robot(){}

Robot::Robot(const Point &p): Unit(p){}

bool Robot::canMove() const{
    return !crashed;
}

void Robot::doCrash(){
    crashed = true;
}

bool Robot::justCrashed() const{
    return crashed;

}


void Robot::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
}

Robot* Robot::clone() const{
    return new Robot{*this};
}
