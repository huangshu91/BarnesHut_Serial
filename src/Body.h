/*
 * Body.h
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */

#ifndef BODY_H_
#define BODY_H_

#include "Simulation.h"

class Simulation;

class Body {
public:
  Body(Simulation*);
  void Initialize(int x, int y, int xv, int yv, int xa, int ya, int m);
  void Render();
  void Update();
  int Getid() { return myId; }

  static int NUMP;

  float xPos;
  float yPos;
  float zPos;
  float xVel;
  float yVel;
  float xAcc;
  float yAcc;

  float mass;

private:
  Simulation* parent;
  sf::Shape sprite;

  int myId;
};

#endif /* BODY_H_ */
