#ifndef BOARD_HPP

#define BOARD_HPP

#include <vector>
#include <fstream>
#include <iostream>

using std::vector;
using std::ostream;
using std::string;
using std::istream;
using std::ofstream;

class Pieces;

class Board {
	public:
		// Big Three + Constructor
		Board();
		Board(const Board &b);
		Board	&operator=(const Board &b);
		~Board();

		// ***** Operator Overloads for reading and writing *****
		friend ostream					&operator<<(std::ostream &os, const Board &b);
		friend istream					&operator>>(std::istream &is, Board &b);
		friend ofstream					&operator<<(ofstream &os, const Board &b);
		//*******************************************************
		// Setters and Getters
		inline vector<vector<Pieces> >	&getBoard() { return (_board); }
		inline vector<vector<Pieces> >	getBoard() const { return (_board); }
		inline void						setBoard(vector<vector<Pieces> > board) { _board = board; }
		// Member Functions
		void							movePiece(string input);
		string							getKingCoordinate(char c) const;
		// Special Move Functions
		void							promotion(string input, char c);
	private:
		vector<vector<Pieces> >			_board;
};

#endif
