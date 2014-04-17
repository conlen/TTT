#ifndef TTT_HPP
#define TTT_HPP

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <utility>


template<int DEBUG=0>
class ttt;

template<int DEBUG=0>
std::ostream& operator<<(std::ostream& s, ttt<DEBUG> &t);

template<int DEBUG>
class ttt {
	private:
		/* board[col][row] */
		std::vector<std::vector<char>>	board;
		std::vector<std::vector<std::vector<char>>>	history;

		std::vector<std::string>		player;
		int 							turn = 0;
		std::mt19937					mt;
	public:
		ttt();
		ttt(const std::vector<std::vector<char>> &b);
		ttt(const std::string &player1, const std::string &player2);
		~ttt();
		int move(int m);
		int moveRandom();
		int gameWon();
		void setBoard(const std::vector<std::vector<char>> &b);
		std::vector<std::vector<char>> getBoard();

	friend std::ostream& operator<<  <DEBUG>(std::ostream& s, ttt<DEBUG> &t);
};

template<int DEBUG>
ttt<DEBUG>::ttt()
{
	if(DEBUG) { std::cout << "ttt<DEBUG>::ttt();" << std::endl; }
	if(DEBUG) { std::cout << "ttt<DEBUG>::ttt(): setup board" << std::endl; }
	board.resize(3);
	for(auto &i: board) {
		i.resize(3);
		for(auto &j: i) {
			j = ' ';
		}
	}
	history.push_back(board);
	if(DEBUG) { std::cout << "ttt<DEBUG>::ttt(): setup players" << std::endl; }
	player.resize(2);
	player[0] = "";
	player[1] = "";
	if(DEBUG) { std::cout << "ttt<DEBUG>:ttt(): seed random number generator" << std::endl; }
	mt.seed(std::chrono::system_clock::now().time_since_epoch().count());
	if(DEBUG) { std::cout << "end" << "ttt<DEBUG>::ttt();" << std::endl; }
	return;
}

template<int DEBUG>
ttt<DEBUG>::ttt(const std::vector<std::vector<char>> &b)
	: ttt()
{
	board = b;
	return;
}
template<int DEBUG>
ttt<DEBUG>::ttt(const std::string &player1, const std::string &player2)
	: ttt()
{
	if(DEBUG) { std::cout << "ttt<DEBUG>::ttt(const std::string&, const std::string&);" << std::endl; }
	player.resize(2);
	player[0] = player1; player[1] = player2;
	return;
}

template<int DEBUG>
ttt<DEBUG>::~ttt()
{
	if(DEBUG) { std::cout << "ttt<DEBUG>::~ttt();" << std::endl; }
	return;
}

template<int DEBUG>
int ttt<DEBUG>::move(int m)
{
	int column, row;
	if(DEBUG) { std::cout << "ttt<DEBUG>::move(int);" << std::endl; }
	switch(m) {
		case 1:
			column = 0; row = 2;
			break;
		case 2:
			column = 1; row = 2;
			break;
		case 3:
			column = 2; row = 2;
			break;
		case 4:
			column = 0; row = 1;
			break;
		case 5:
			column = 1; row = 1;
			break;
		case 6:
			column = 2; row = 1;
			break;
		case 7:
			column = 0; row = 0;
			break;
		case 8:
			column = 1; row = 0;
			break;
		case 9:
			column = 2; row = 0;
			break;
		default:
			return(-2);
	}
	if(board[column][row] != ' ') return(-1);
	board[column][row] = (turn++ % 2 == 0 ? 'X' : 'O');
	history.push_back(board);
	return(0);
}

template<int DEBUG>
int ttt<DEBUG>::moveRandom()
{
	int		i, j, play, row, col;
	std::uniform_int_distribution<int> randomPlay(0, 8);

	if(DEBUG) { std::cout << "ttt<DEBUG>::moveRandom();" << std::endl; }
	if(gameWon() > 0) return(-1);
	while(true) {
		play = randomPlay(mt);
		row = play % 3; 
		col = play / 3;
		if(board[col][row] == ' ') break;
	}
	board[col][row] = (turn++ % 2 == 0 ? 'X' : 'O');
	history.push_back(board);
	return(0);
}

template<int DEBUG>
void ttt<DEBUG>::setBoard(const std::vector<std::vector<char>> &b)
{
	board = b;
	return;
}

template<int DEBUG>
int ttt<DEBUG>::gameWon()
{
	if(DEBUG) { std::cout << "ttt<DEBUG>::gameWon();" << std::endl; }
	if(board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] != ' ') return( board[0][0] == 'X' ? 1 : 2);
	if(board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] != ' ') return( board[0][1] == 'X' ? 1 : 2);
	if(board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] != ' ') return( board[0][2] == 'X' ? 1 : 2);

	if(board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] != ' ') return( board[0][0] == 'X' ? 1 : 2);
	if(board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] != ' ') return( board[1][0] == 'X' ? 1 : 2);
	if(board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] != ' ') return( board[2][0] == 'X' ? 1 : 2);

	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') return( board[0][0] == 'X' ? 1 : 2);
	if(board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != ' ') return( board[2][0] == 'X' ? 1 : 2);
	for(auto i = 0; i < 3; i++) {
		for(auto j = 0; j < 3; j++) {
			if(board[i][j] == ' ') goto noWinner;
		}
	}
	if(DEBUG) { std::cout << "ttt<DEBUG>::gameWon() == 0" << std::endl; }
	return(3);
noWinner:
	if(DEBUG) { std::cout << "ttt<DEBUG>::gameWon() == 0" << std::endl; }
	return(0);

}

template<int DEBUG>
std::vector<std::vector<char>> ttt<DEBUG>::getBoard()
{
	return(board);
}

template<int DEBUG>
std::ostream& operator<<(std::ostream& s, ttt<DEBUG> &t)
{
	if(DEBUG) { std::cout << "operator<<(std::ostream&, ttt<DEBUG> &);" << std::endl; }
	s << "X : " << t.player[0] << std::endl;
	s << "O : " << t.player[1] << std::endl;
	s << t.board[0][0] << "|" << t.board[1][0] << "|" << t.board[2][0] << std::endl;
	s << "-+-+-" << std::endl;
	s << t.board[0][1] << "|" << t.board[1][1] << "|" << t.board[2][1] << std::endl;
	s << "-+-+-" << std::endl;
	s << t.board[0][2] << "|" << t.board[1][2] << "|" << t.board[2][2] << std::endl;
	return s;
}
#endif
