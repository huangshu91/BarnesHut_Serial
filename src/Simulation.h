/*
 * Simulation.h
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

#include "Quadtree.h"
#include "Body.h"

class Body;
class Quadtree;

class Simulation {
public:
  Simulation();

  void Setup();
  void Run();

  void CalculatePos();

  void AddDraw(sf::Shape);

  void DebugRender();

  int NUMP;

private:
  sf::RenderWindow gameWindow;

  std::vector<Body*> entities;

  Quadtree* world;
};


#endif /* SIMULATION_H_ */
