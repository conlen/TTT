#include <iostream>
#include <memory>
#include <typeinfo>
#include <unordered_map>

#include "ttt.hpp"
#include "bt.hpp"
#include "tree.hpp"

using namespace std;


class hash_int {
public:
	size_t operator()(const int &i) const {
		return std::hash<int>()(i);
	}
	
};

void test4()
{
	shared_ptr<tree<int, hash_int>>	iTree(new tree<int, hash_int>), tmpTree;

	iTree->insert(12);
	(*iTree)[12].first->insert(4, iTree->getShared());
	(*iTree)[12].first->insert(3, iTree->getShared());
	(*(*iTree)[12].first)[4].first->insert(2, (*iTree)[12].first->getShared());

	cout << *iTree << endl;

}

typedef tree<ttt<>, hash_ttt<>> tttTree;

void fillTree2(tttTree &t, int depth = 0)
{
	ttt<>					game, tmpGame;
	shared_ptr<tttTree>		newTree;
	int 					rc;
	static int 				counter = 0;

	for(auto i : t) {
		if(i.first.gameWon() == 0)
		for(auto j = 1; j <= 9; j++) {
			tmpGame = i.first;
			rc = tmpGame.move(j);
			if(rc == 0) { i.second.first->insert(tmpGame, t.getShared()); }
		}
		fillTree2(*i.second.first, depth+1);
	}
	return;
}

void test3()
{
	ttt<> 					game, tmpGame;
	shared_ptr<tttTree>		gameTree(new tttTree), tmpTree;
	int 		rc;
	char 		move;

	gameTree->insert(game);
	cout << game;
	move = '7';
	cout << move << endl;
	tmpGame = game;
	tmpGame.move(move - '0');
	cout << tmpGame << endl;
	(*gameTree)[game].first->insert(tmpGame);
	cout << "filling tree" << endl;
	fillTree2(*(*gameTree)[game].first);



	tmpGame.move('8' - '0');
	tmpGame.move('9' - '0');
	tmpGame.move('1' - '0');
	tmpGame.move('2' - '0');
	tmpGame.move('3' - '0');
	tmpGame.move('4' - '0');
	tmpGame.move('5' - '0');
	tmpGame.move('6' - '0');

	cout << *gameTree << endl;
	cout << "finding game " << endl;
	cout << tmpGame << endl;
	tmpTree = gameTree->find(tmpGame);
	cout << "found tree at " << tmpTree << endl;
	if(tmpTree != NULL) { cout << *tmpTree << endl; }
	cout << "tree is " << endl;
	cout << *(*tmpTree)[tmpGame].second << endl;

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
	// test1();
	// test2();
	test3();
	test4();
}
