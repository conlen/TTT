#include <iostream>
#include <typeinfo>
#include <unordered_map>

#include "ttt.hpp"
#include "bt.hpp"
#include "tree.hpp"

using namespace std;


typedef tree<ttt<>, hash_ttt<>> tttTree;

void fillTree2(tttTree &t, int depth = 0)
{
	ttt<>					game, tmpGame;
	shared_ptr<tttTree>		newTree;
	int 					rc;
	static int 				counter = 0;

	cout << "depth = " << depth << ", count = " << counter++ << endl;
	for(auto i : t) {
		if(i.first.gameWon() == 0)
		for(auto j = 1; j <= 9; j++) {
			cout << "depth = " << depth << ", count = " << counter << " number : " << j << endl;
			tmpGame = i.first;
			rc = tmpGame.move(j);
			if(rc == 0) { i.second->insert(pair<ttt<>, shared_ptr<tttTree>>(tmpGame, make_shared<tttTree>())); }
		}
		fillTree2(*i.second, depth+1);
	}
	return;

}

void test3()
{
	ttt<> 		game, tmpGame;
	tttTree		gameTree, tmpTree;
	int 		rc;
	char 		move;

	gameTree.insert(pair<ttt<>, shared_ptr<tttTree>>(game, make_shared<tttTree>()));
	cout << game;
	move = '7';
	cout << move << endl;
	tmpGame = game;
	tmpGame.move(move - '0');
	cout << tmpGame << endl;
	gameTree[game]->insert(pair<ttt<>, shared_ptr<tttTree>>(tmpGame, make_shared<tttTree>()));

	fillTree2(*gameTree[game]);

}

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
	// test2();
	test3();
}
