/*
 * Simulation.cpp
 *
 *  Created on: Dec 8, 2012
 *      Author: Maiev
 */

#include "Simulation.h"
#include "Config.h"
#include "math.h"
#include <cstdlib>
#include <sstream>

float fabs(float a) {
  return (a < 0) ? -1*a : a;
}

Simulation::Simulation() {

  gameWindow.Create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_COLOR_DEPTH), "Barnes Hut 0.1");

  gameWindow.SetFramerateLimit(60);
  gameWindow.UseVerticalSync(true);
  gameWindow.ShowMouseCursor(true);

  Setup();
}

void Simulation::Setup() {
  static float midx = WINDOW_WIDTH/2;
  static float midy = WINDOW_HEIGHT/2;

  Body* tempobj;

  for (int i = 0; i < NUM_STAR; i++) {
    tempobj = new Body(this);
    entities.push_back(tempobj);
  }

  entities[0]->xPos = midx; entities[0]->yPos = midy;  entities[0]->xVel = 0;
  entities[0]->yVel = -0.00000015; entities[0]->mass = 19.89; //sun

  entities[1]->xPos = midx - 5.7;    entities[1]->mass = 0.00000330; //mercury
  entities[2]->xPos = midx - 10.8;   entities[2]->mass = 0.0000487; //venus
  entities[3]->xPos = midx + 14.9;   entities[3]->mass = 0.00005974; //earth
  entities[4]->xPos = midx + 22.8;   entities[4]->mass = 0.00000642; //mars
  entities[5]->xPos = midx - 77.8;   entities[5]->mass = 0.01899; //jupiter
  entities[6]->xPos = midx + 142.4;  entities[6]->mass = 0.00568; //saturn
  entities[7]->xPos = midx + 287.2;  entities[7]->mass = 0.000866; //uranus
  entities[8]->xPos = midx + 449.9;  entities[8]->mass = 0.00103; //neptune
/*
  for (int i = 1; i < NUMP; i++) {
    entities[i]->xVel = 0;
    entities[i]->yPos = midy;
    entities[i]->yVel = sqrt(G * 19.89 / fabs(entities[i]->xPos - midx));
    if (entities[i]->xPos > midx) {
      entities[i]->yVel *= -1;
    }
  }
*/


  std::srand(9);

  // for sufficiently large numbers of NUMP, xpos and ypos collisions will happen which
  // not only cause distance to be a problem but insertion will cause crash.  need to figure
  // out a good distribution

  for (int i = 1; i < NUMP; i++) {
    entities[i]->xVel = 0;
    entities[i]->yPos = std::rand() % 1000 + 10;
    entities[i]->xPos = std::rand() % 1000 + 10;
    if (entities[i]->xPos == 512) entities[i]->xPos += 5;
    entities[i]->mass = ((float)(std::rand() % 100 + 1)) / 10000;
    entities[i]->yVel = sqrt(G * 19.89 / fabs(entities[i]->xPos - midx));
    if (entities[i]->xPos > midx) {
      entities[i]->yVel *= -1;
    }
  }


  /*
  int startx = 100;
  int starty = 100;
  for (int i = 0; i < NUMP; i++) {
    entities[i]->xVel = 0;
    entities[i]->xPos = startx;
    startx += 10;
    if (startx > WINDOW_WIDTH-100) { startx = 100; starty+= 10; }
    entities[i]->yPos = starty;
    entities[i]->mass = ((float)(std::rand() % 100 + 1)) / 10000;
    entities[i]->yVel = sqrt(G * 19.89 / fabs(entities[i]->xPos - midx));
    if (entities[i]->xPos > midx) {
      entities[i]->yVel *= -1;
    }
  }
  */

  //std::cout << entities[31]->xPos << " " << entities[31]->yPos << " " << entities[31]->mass << std::endl;

  world = new Quadtree(0);
  world->SetParent(NULL);
  world->SetSize(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

}

void Simulation::AddDraw(sf::Shape obj) {
  gameWindow.Draw(obj);
}

void Simulation::CalculatePos() {

  float dx = 0;
  float dy = 0;
  float D = 0;
  float A = 0;

  for (int i = 0; i < NUMP; i++) {
    entities[i]->xAcc = 0;
    entities[i]->yAcc = 0;
    for (int j = 0; j < NUMP; j++) {
      if (i != j) {
        dx = entities[j]->xPos - entities[i]->xPos;
        dy = entities[j]->yPos - entities[i]->yPos;
        D = sqrt((dx*dx) + (dy*dy));
        A = (G*entities[j]->mass)/ (D*D);
        entities[i]->xAcc += dx*A/D;
        entities[i]->yAcc += dy*A/D;
      }
    }
  }

}

void Simulation::DebugRender() {
  if (DEBUG == true) {
    float delta = gameWindow.GetFrameTime();
    std::stringstream ss;
    ss << 1.f / delta;
    sf::String fps;
    fps.SetText(ss.str());
    fps.SetFont(sf::Font::GetDefaultFont());
    fps.SetSize(14);
    fps.SetPosition(20, 10);
    gameWindow.Draw(fps);
  }
}

void Simulation::Run() {
  while (gameWindow.IsOpened()) {
    sf::Event ev;

    while (gameWindow.GetEvent(ev)) {
          switch (ev.Type) {

          case sf::Event::Closed:
            gameWindow.Close();
            break;

          default:
            break;

          }

    }

    gameWindow.Clear(sf::Color(0, 0, 0));

    //CalculatePos();
    world->Clear();
    for (unsigned int i = 0; i < entities.size(); i++) {
      entities[i]->Update();
      entities[i]->Render();
      world->Insert(entities[i]);
      world->Calculate(entities[i]);

      //std::cout << "test3" << std::endl;

    }
    //world->Render(this);
    DebugRender();
    gameWindow.Display();
  }

}
