#ifndef CHESS_HPP

#define CHESS_HPP

#include "Board.hpp"
#include "Pieces.hpp"
#include <string>

using std::string;

class Pieces;
class Board;

class Chess {
	public:
		// Big Three + Constructor
		Chess();
		Chess(const Chess &c);
		Chess &operator=(const Chess &c);
		~Chess();

		// **************** Setters and Getters ****************
		inline Board	getBoard() const { return (_board); }
		inline bool		getIsWhiteTurn() const { return (_isWhiteTurn); }
		inline bool		getIsCheck() const { return (_isCheck); }
		inline bool		getIsCheckMate() const { return (_isCheckMate); }
		string			getKingCoordinate(char color) const;

		inline void		setBoard(Board board) { _board = board; }
		inline void		setIsWhiteTurn(bool isWhiteTurn) { _isWhiteTurn = isWhiteTurn; }
		inline void		setIsCheck(bool isCheck) { _isCheck = isCheck; }
		inline void		setIsCheckMate(bool isCheckMate) { _isCheckMate = isCheckMate; }
		// ****************************************************************
		// ****************Input Control Functions****************
		string			getInput(char color) const;
		bool			isOccupied(const vector<int> &input, char c) const;
		bool			isSpecialMove(string input, char color) const;
		bool			isValidInput(string input, char c) const;
		bool			isInputsLetterValid(string input) const;
		bool			isCastling(string input, char color) const;
		bool			isValidMove(const vector<int> &a, char c) const;
		bool			isPromotion(string input, char color) const;
		// ****************************************************************
		// *************************Special Moves*******************
		void			loadGame(bool &_isWhiteTurn);
		void			saveGame(const bool &isW) const;
		void			makeCastling(const string &input, char color);
		// ****************************************************************
		// ****************Move Control Functions****************
		bool			isCheckedAfterMove(const string &input, char c) const;
		bool			isCheck(const string &enemyKingCoordinate, char color, const Board &tempBoard) const;
		bool			isCheckMate(const string &enemyKingCoordinate, char enemyColor) const ;
		bool			isStalemate(char c) const;
		bool			isStalemateNoMoves(char color) const;
		bool			isStalemateOnPieces(char color) const;
		vector<string>	getWholeValidMoves(char color) const;
		// ****************************************************************
		// *************************AI Functions*******************
		void			suggestMove(char c, char suggest, Board &b) const;
		double			getTotalPoint(char c, const Board &board) const;
		string			getSuggestRecur(char suggested, char playerColor, char enemyColor, int depth, Board &b, double min, double max) const;
		// ****************************************************************
		// Member Functions
		void			run(); // Main function
		void			takeMove(char color, char enemyColor, bool &_isWhiteTurn);
	private:
		Board	_board;
		bool	_isWhiteTurn;
		bool	_isCheck;
		bool	_isCheckMate;
};

#endif
