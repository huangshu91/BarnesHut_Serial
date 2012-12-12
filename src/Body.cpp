/*
 * Body.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */
#include "Body.h"
#include <iostream>
#include "Config.h"
using namespace std;

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
  /*
  if (myId == 31) {
    cout << "body update 31" << endl;
    cout << xAcc << " " << yAcc << endl;
    cout << xVel << " " << yVel << endl;
    cout << xPos << " " << yPos << endl;
  }
  */
  xVel += xAcc;
  yVel += yAcc;
  xPos += xVel;
  yPos += yVel;
  sprite.SetPosition(xPos, yPos);
  xAcc = 0;
  yAcc = 0;
}

void Body::Render() {
  //if (myId == 32)
  //std::cout << xPos << " " << yPos << std::endl;
  parent->AddDraw(sprite);
}

