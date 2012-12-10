/*
 * QuadTree.h
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_
#include "Body.h"
#include "Simulation.h"
#include <vector>

class Body;
class Simulation;

class Quadtree {
public:
  Quadtree(int);

  void SetParent(Quadtree* p) { parent = p; }

  void SetSize(int, int, int, int);

  int Getx() {return x;}
  int Gety() {return y;}
  int Getw() {return w;}
  int Geth() {return h;}


  // quad tree core functionality
  void Split();
  void Insert(Body* obj);
  int GetIndex(Body* obj);
  void Render(Simulation*);
  void DebugPrint();
  void Clear();

  void Calculate(Body* obj);

  int Numobj() { return objects.size(); }

private:
  static const unsigned int MAX_OBJECTS = 1; //number of obj before split
  int levels; //current level of tree

  bool isleaf;

  float mass; //aggregate mass of subnodes
  float xcom; //x center of mass
  float ycom; //y center of mass

  // arranged in this order
  // [0] = top left, [1] = top right, [2] = bottom left, [3] = bottom right
  std::vector<Quadtree> children;
  Quadtree* parent;

  int size;

  int x;
  int y;
  int w;
  int h;

  std::vector<Body*> objects;
};


#endif /* QUADTREE_H_ */
