#include <iostream>
#include <map>

#include "ttt.hpp"
#include "bt.hpp"

using namespace std;

void fillTree(boardTree &t, int depth = 0) 
{
	ttt<>	game = t.getBoard(), tmpGame;
	boardTree	*newTree;
	int rc;
	static int counter = 0;

	for(auto i = 1; i<=9; i++) {
		tmpGame = game;
		rc = tmpGame.move(i);
		if(rc == 0) { 
			newTree = t.insertBoard(tmpGame); 
			if(tmpGame.gameWon() == 0) { fillTree(*newTree, depth+1); }
		}
		
	}
}

void test2()
{
	ttt<> game, tmpGame; 
	boardTree	t;
	int 		rc;
	char		move;

	cout << game;
	cin >> move;
	cout << (int)move << endl;
	game.move(move - '0');

	t.setBoard(game);
	fillTree(t);

	cout << t;
}

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
	//test1();
	test2();
}
