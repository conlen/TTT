#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <utility>
#include <memory>

#include "ttt.hpp"

typedef std::vector<std::vector<char>>	Board;

class boardTree;

std::ostream& operator<<(std::ostream& s, boardTree &b);

class boardTree {
	private:
		Board	node;
		std::vector<boardTree>		leafs;

	public:
		boardTree();
		boardTree(const Board &b);
		~boardTree();
		void setBoard(const Board &b);
		Board getBoard();
		Board &insertBoard(const Board &b);

	friend std::ostream& operator<<(std::ostream& s, boardTree &b);

};

boardTree::boardTree()
{
	return;
}

boardTree::boardTree(const Board &b)
	: boardTree()
{
	node = b;
	return;
}

boardTree::~boardTree()
{
	return;
}

void boardTree::setBoard(const Board &b)
{
	node = b;
	return;
}

Board &boardTree::insertBoard(const Board &b)
{
	boardTree	bt(b);
	leafs.push_back(bt);
	return(leafs[leafs.size()-1].node);
}
Board boardTree::getBoard()
{
	std::cout << "boardTree::getBoard()" << std::endl;
	return(node);
}

std::ostream& operator<<(std::ostream& s, boardTree &b)
{
	ttt<>	*g;
	g = new ttt<>(b.node);

	s << *g;
	for(auto &i : b.leafs) {
		s << i;
	}
	return s;
}