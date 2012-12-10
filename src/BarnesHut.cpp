//============================================================================
// Name        : BarnesHut.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFML/System.hpp>
#include <iostream>
#include "Simulation.h"

int main()
{
    sf::Clock Clock;
    /*
    while (Clock.GetElapsedTime() < 5.f)
    {
        std::cout << Clock.GetElapsedTime() << std::endl;
        sf::Sleep(1.0f);
    }
     */
    Simulation* engine = new Simulation();
    engine->Run();

    return 0;
}
