#include <iostream>
#include <memory>

#include "ttt.hpp"
#include "tree2.hpp"


using namespace std;

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

void test2()
{
	ttt<> game, tmpGame;
	shared_ptr<tree<ttt<>>>	t(new tree<ttt<>>(game)), tmpTree;

	game.move('7' - '0');
	t->insert(game);
	cout << *t << endl;
	return;
}


void test1()
{
	shared_ptr<tree<int>>	t(new tree<int>(12)), tmpTree;
	t->insert(4);
	t->insert(3);
	cout << *t << endl;
	
	tmpTree = t->find(4);
	tmpTree->insert(2);

	cout << *tmpTree << endl;
	
	cout << *t << endl;
	return;
}

int main(int argc, char *argv[], char *envp[])
{
	test1();
	test2();
	return(0);
}