#include <iostream>

#include "ttt.hpp"

using namespace std;

void test1()
{
	ttt<1>	gameDebug("Mike", "COMPUTER");
	ttt<>	game;
	char	move;

	cout << gameDebug;
	while(!gameDebug.gameWon()) {
		cin >> move;
		cout << (int)move << endl;
		gameDebug.move(move - '0');
		gameDebug.moveRandom();
		cout << gameDebug;
	}
}

int main(int argc, char *argv[], char *env[])
{
	test1();
}
