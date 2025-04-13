/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 * Adam Ljung. Liu-Id: Adalj586
 * Isak Skott. Liu-Id: IsaSk052
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {

   for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot = new Robot(); //Creates a new robot
        while(!isEmpty(*robot)){ //Checks if there is a position
           delete robot; //Deletes old robot in this spot
           robot = new Robot(); // creates a new robot
        }
        robots.push_back(robot); //Pushes robot into the vector of robots
    }
    teleportHero(); //Places hero
}

GameState::~GameState(){
        for(Robot* robot: robots){
            delete robot;
        }
}

GameState::GameState(const GameState& other){
    copyOther(other);
}

GameState& GameState::operator=(const GameState& other){
    if(this != &other){
        for(Robot* robot: this->robots){
            delete robot;
        }
        robots.clear();
        copyOther(other);
    }
    return *this;
}

//Pushes a new robot to this->vector from other->vector. Creates a new robot from other
void GameState::copyOther(const GameState& other){
    for(Robot* robot: other.robots){
        this->robots.push_back(robot->clone());
    }
    hero = other.hero;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot* robot: robots)
        robot->draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Robot* robot: robots)
        robot->moveTowards(hero);
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < robots.size(); ++i){
        for(unsigned o=i+1; o < robots.size(); ++o){
            if(robots[i]->at(*robots[o])){ // Checks if 2 robots has the same coordinates, crashes both if they have
                robots[i]->doCrash();
                robots[o]->doCrash();
            }
        }
    }
}

int GameState::countJustCrashed()const{
    int numberDestroyed =0;
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->justCrashed())
            numberDestroyed++;
    return numberDestroyed;
}

void GameState::junkTheCrashed(){
    for(unsigned i=0; i < robots.size(); ++i){
        if (robots[i]->justCrashed()) {
            Point crash = robots[i]->asPoint();
            delete robots[i];
            robots[i] = new Junk(crash);
        }
    }
}

bool GameState::stillLiveRobots() const {
    for(unsigned i=0; i < robots.size(); ++i)
        if(robots[i]->canMove())
            return true;
    return false;
}


bool GameState::heroDead() const {
    for(const Robot* robot: robots){
        if(hero.at(*robot)){
            return true;
        }
    }

    return false;
}

void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(const Robot* robot: robots)
        if(robot->at(unit))
            return false;
    return true;
}

