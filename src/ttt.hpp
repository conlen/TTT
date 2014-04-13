#include <iostream>
#include <string>
#include <vector>

template<int DEBUG=0>
class ttt;

template<int DEBUG=0>
std::ostream& operator<<(std::ostream& s, ttt<DEBUG> &t);

template<int DEBUG>
class ttt {
	private:
		std::vector<std::vector<char>>	board;
		std::vector<std::string>		player;
		int 							turn = 0;
	public:
		ttt();
		ttt(const std::string &player1, const std::string &player2);
		~ttt();

	
	friend std::ostream& operator<<<DEBUG>(std::ostream& s, ttt<DEBUG> &t);
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
	if(DEBUG) { std::cout << "ttt<DEBUG>::ttt(): setup players" << std::endl; }
	player.resize(2);
	player[0] = "";
	player[1] = "";
	if(DEBUG) { std::cout << "end" << "ttt<DEBUG>::ttt();" << std::endl; }
	return;
}

template<int DEBUG>
ttt<DEBUG>::ttt(const std::string &player1, const std::string &player2)
	: ttt()
{
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
