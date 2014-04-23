#include <iostream>
#include <typeinfo>
#include <memory>

#include "ttt.hpp"
#include "tree2.hpp"


using namespace std;

void fillTree2(shared_ptr<tree<ttt<>>> &t, int depth = 0)
{
	ttt<>					game, tmpGame;
	shared_ptr<tree<ttt<>>>	newTree;
	int 					rc;
	static int 				counter = 0;

	if(t->first.first.gameWon() == 0) {
		for(auto j = 1; j <= 9; j++) {
		 	tmpGame = t->first.first;
		 	rc = tmpGame.move(j);
		 	if(rc == 0) { t->insert(tmpGame); }
		}
		for(auto i : t->second) fillTree2(i, depth+1);
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
	tmpTree = t->find(game);
	cout << "filling tree " << endl;
	fillTree2(tmpTree);
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
//	test1();
	test2();
	return(0);
}