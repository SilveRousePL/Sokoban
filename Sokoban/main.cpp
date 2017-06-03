#include <iostream>
#include "Engine.hpp"


int main()
{
	// for iostream boost
    std::ios_base::sync_with_stdio(0);

    Engine engine("Sokoban");

	if (engine.IsOk())
		engine.Run();
	else
		MessageBoxA(NULL, "Something goes wrong with assets.\nPlease try again or reinstall game.\n", "Error occurs!", MB_ICONERROR | MB_OK);

    return 0;
}