/*
 * quadtree.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */

#include "Quadtree.h"
#include "Config.h"
#include "math.h"
#include <iostream>
using namespace std;

Quadtree::Quadtree(int lev) {
  levels = lev;
  size = 0;
  isleaf = true;

  mass = 0;
  xcom = 0;
  ycom = 0;
}

void Quadtree::SetSize(int a, int b, int c, int d) {
  x = a;
  y = b;
  w = c;
  h = d;
}

void Quadtree::Insert(Body* obj) {
  float tempx = xcom*mass;
  float tempy = ycom*mass;

  tempx += obj->xPos*obj->mass;
  tempy += obj->yPos*obj->mass;
  mass += obj->mass;
  xcom = tempx/mass;
  ycom = tempy/mass;

  if (levels >= MAX_LEVEL) { objects.push_back(obj); size++; return; }

  if (objects.size() < MAX_OBJECTS && isleaf == true) {
    objects.push_back(obj);
    size++;
  } else if (isleaf == false) { // not a leaf, insert into child
    int ind = GetIndex(obj);
    children[ind].Insert(obj);
  } else { // need to split
    size = 0;
    objects.push_back(obj);
    Split();
    isleaf = false;
  }
}

int Quadtree::GetIndex(Body* obj) {
  int index = -1;
  float objx = obj->xPos;
  float objy = obj->yPos;
  float childw = children[0].Getw();
  float childh = children[0].Geth();

  if (objx < x+childw) {
    if (objy < y+childh) { //region 0, top left
      index = 0;
    } else { //region 2, bottom left
      index = 2;
    }
  } else { //obj >= childw
    if (objy < y+childh) { //region 1, top right
      index = 1;
    } else { //region 3, bottom right
      index = 3;
    }
  }


  return index;
}

void Quadtree::Clear() {
  mass = 0;
  xcom = 0;
  ycom = 0;

  objects.clear();
  isleaf = true;

  for (unsigned int i = 0; i < children.size(); i++) {
    children[i].Clear();
  }

  children.clear();
}

void Quadtree::Split() {
  int width = w/2;
  int height = h/2;

  for (int i = 0; i < 4; i++) {
    children.push_back(Quadtree(levels+1));
    children[i].SetParent(this);
  }

  children[0].SetSize(x, y, width, height);
  children[1].SetSize(x+width, y, width, height);
  children[2].SetSize(x, y+height, width, height);
  children[3].SetSize(x+width, y+height, width, height);

  for (unsigned int i = 0; i < objects.size(); i++) {
    int ind = GetIndex(objects[i]);

    children[ind].Insert(objects[i]);
  }

  objects.clear();

}

void Quadtree::Calculate(Body* obj) {
  //std::cout << "test " << obj->Getid() << std::endl;
  if (xcom == 0 && ycom == 0 && mass == 0) return; //empty space

  float dx = xcom-obj->xPos;
  float dy = ycom-obj->yPos;
  //std::cout << obj->xPos << " " << obj->yPos << std::endl;
  float D = sqrt((dx*dx)+(dy*dy));
  //std::cout << "test3" << std::endl;
  //DebugPrint();
  if (D == 0) return; // same object since distance = 0
  float thet = w/D; // ratio of bound box and distance between CoM

  if (thet > THETA || children.size() == 0) { //use aggregate
    float A = (G*mass)/(D*D);
    obj->xAcc += dx*A/D;
    obj->yAcc += dy*A/D;
  } else { //check children
    for (unsigned int i = 0; i < children.size(); i++) {
      children[i].Calculate(obj);
    }
  }
}

void Quadtree::DebugPrint() {
  std::cout << "level " << levels << std::endl;
  std::cout << "x: " << xcom << " , y: " << ycom << " , mass: " << mass << std::endl;
  for (unsigned int i = 0; i < objects.size(); i++ ) {
    std::cout << "obj" << i << " " << objects[i]->xPos << " " << objects[i]->yPos << std::endl;
  }
}

void Quadtree::Render(Simulation* sim) {
  if (DEBUG == true) {
    sf::Shape bound = sf::Shape::Rectangle(x+1, y+1, x+w-1, y+h-1,
        sf::Color::Blue, 1, sf::Color::Red);
    bound.EnableFill(false);
    sim->AddDraw(bound);

    for (unsigned int i = 0; i < children.size(); i++) {
      children[i].Render(sim);
    }
  }
}
