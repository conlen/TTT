#include <iostream>
#include <map>

#include "ttt.hpp"
#include "bt.hpp"

using namespace std;

void fillTree(boardTree &t) 
{
	ttt<>	game(t.getBoard()), tmpGame;
	boardTree	newTree;
	int rc;

	for(auto i = 1; i<=9; i++) {
		tmpGame = game;
		rc = tmpGame.move(i);
		if(rc == 0) { newTree = t.insertBoard(tmpGame.getBoard()); }
		if(tmpGame.gameWon() == 0) { fillTree(newTree); }
	}
}

void test2()
{
	ttt<1> game, tmpGame; 
	Board	b;
	boardTree	t;
	int 		rc;

cout << "foo" << endl;
	b = game.getBoard();
cout << "foo" << endl;
	t.setBoard(b);
cout << "foo" << endl;
	fillTree(t);
cout << "foo" << endl;	
	// for(auto i = 1; i<= 9; i++) {
	// 	tmpGame = game;
	// 	rc = tmpGame.move(i);
	// 	if(rc == 0) { t.insertBoard(tmpGame.getBoard()); }
	// }

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
