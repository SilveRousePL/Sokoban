#include <iostream>
#include "Engine.hpp"


int main()
{
	// for iostream boost
    std::ios_base::sync_with_stdio(0);

    Engine engine("Sokoban");

    if(engine.IsOk())
        engine.Run();

    return 0;
}