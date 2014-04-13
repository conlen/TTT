#include <iostream>

#include "ttt.hpp"

using namespace std;

void test1()
{
	ttt<1>	gameDebug("Mike", "COMPUTER");
	ttt<>	game;

	cout << gameDebug;
	for(auto i = 0; i < 9; i++) {
		gameDebug.moveRandom();
		cout << gameDebug;
	}
}

int main(int argc, char *argv[], char *env[])
{
	test1();
}
