/*
 * Body.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */
#include "Body.h"
#include "Config.h"

int Body::NUMP = 0;

Body::Body(Simulation* sim) {
  parent = sim;

  sprite = sf::Shape::Circle(0, 0, 2, sf::Color(255, 255, 255));

  myId = NUMP++;

  parent->NUMP = this->NUMP;

  xPos = 0;
  yPos = 0;
  xVel = 0;
  yVel = 0;
  xAcc = 0;
  yAcc = 0;
  mass = 0;
}

void Body::Initialize(int x, int y, int xv, int yv, int xa, int ya, int m) {
  xPos = x;
  yPos = y;
  xVel = xv;
  yVel = yv;
  xAcc = xa;
  yAcc = ya;
  mass = m;
}

void Body::Update() {
  xVel += xAcc;
  yVel += yAcc;
  xPos += xVel;
  yPos += yVel;
  sprite.SetPosition(xPos, yPos);
  xAcc = 0;
  yAcc = 0;
}

void Body::Render() {
  parent->AddDraw(sprite);
}

