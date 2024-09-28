#include <iostream>
#include "../header/Pieces.hpp"
using namespace std;

#ifndef SIZE
# define SIZE 8 // Size of the board
#endif

// Big Three + Constructors
Pieces::Pieces()
	: _x(0), _y(0), _color('.'),
	_type(PiecesType::EMPTY), _point(Point::EMPTY), _isMoved(false)
{
	_symbol = '.';
}

Pieces::Pieces(int x, int y, char color, PiecesType type)
	: _x(x), _y(y), _color(color),_type(type)
{
	setSymbol(type, color);
	setPoint(type);
	_isMoved = isReallyMoved();
}

Pieces::Pieces(int x, int y, char color, char sym)
	: _x(x), _y(y), _color(color)
{
	_symbol = sym;
	_type = getSymbol(sym);
	setPoint(_type);
	_isMoved = isReallyMoved();
}

Pieces::Pieces(const Pieces &p)
: _x(p._x), _y(p._y), _symbol(p._symbol), _color(p._color), _type(p._type),
_point(p._point), _isMoved(p._isMoved)
{/*Body intentionally left empty*/}

Pieces	&Pieces::operator=(const Pieces &p)
{
	if (this != &p)
	{
		_x = p._x;
		_y = p._y;
		_color = p._color;
		_type = p._type;
		_point = p._point;
		_isMoved = p._isMoved;
		_symbol = p._symbol;
	}
	return (*this);
}

// Pre Condition: Program wants to initialize a piece at loading from file
// and the piece must be a rook, king, or pawn.
// Because only these pieces has rule on moving.
// Post Condition: Returns true if the piece is moved, false otherwise.
bool	Pieces::isReallyMoved() const {
	if (_type == PiecesType::ROOK){
		if (_color == 'W'){
			if (_x == 0 && _y == 7) return (false);
			else if (_x == 7 && _y == 7) return (false);
		}
		else if (_color == 'B'){
			if (_x == 0 && _y == 0) return (false);
			else if (_x == 7 && _y == 0) return (false);
		}
	}
	else if (_type == PiecesType::KING){
		if (_color == 'W'){
			if (_x == 4 && _y == 7) return (false);
		}
		else if (_color == 'B'){
			if (_x == 4 && _y == 0) return (false);
		}
	}
	else if (_type == PiecesType::PAWN){
		if (_color == 'W'){
			if (_y == 6) return (false);
		}
		else if (_color == 'B'){
			if (_y == 1) return (false);
		}
	}
	return (true);
}

Pieces::~Pieces() {/*Body intentionally left empty*/}


// Post Condition: Sets the symbol of the piece according to the type and color
void	Pieces::setSymbol(PiecesType type, char color)
{
	if (type == PiecesType::PAWN)
	{
		if (color == 'W') _symbol = 'P';
		else _symbol = 'p';
	}
	else if (type == PiecesType::ROOK)
	{
		if (color == 'W') _symbol = 'R';
		else _symbol = 'r';
	}
	else if (type == PiecesType::KNIGHT)
	{
		if (color == 'W') _symbol = 'N';
		else _symbol = 'n';
	}
	else if (type == PiecesType::BISHOP)
	{
		if (color == 'W') _symbol = 'B';
		else _symbol = 'b';
	}
	else if (type == PiecesType::QUEEN)
	{
		if (color == 'W') _symbol = 'Q';
		else _symbol = 'q';
	}
	else if (type == PiecesType::KING)
	{
		if (color == 'W') _symbol = 'K'; else _symbol = 'k';
	}
	else if (type == PiecesType::EMPTY) _symbol = '.';
}


// Post Condition: Sets the point of the piece according to the type
void	Pieces::setPoint(PiecesType type)
{
	if (type == PiecesType::PAWN) _point = Point::PAWN;
	else if (type == PiecesType::ROOK) _point = Point::ROOK;
	else if (type == PiecesType::KNIGHT) _point = Point::KNIGHT;
	else if (type == PiecesType::BISHOP) _point = Point::BISHOP;
	else if (type == PiecesType::QUEEN) _point = Point::QUEEN;
	else if (type == PiecesType::KING) _point = Point::KING;
	else if (type == PiecesType::EMPTY) _point = Point::EMPTY;
}

// Pre Condition: User must enter a move.
// Post Condition: Returns true if the move is valid, false otherwise.
bool	Pieces::isValidMove(const vector<int> &input, const vector<vector<Pieces> > &board, char color) const
{
	if (input[0] == input[2] && input[1] == input[3]) return (false);
	switch(this->getType()){
		case PiecesType::PAWN: return (isValidMovePawn(input, board, color));
		case PiecesType::ROOK: return (isValidMoveRook(input, board, color));
		case PiecesType::KNIGHT: return (isValidMoveKnight(input, board, color));
		case PiecesType::BISHOP: return (isValidMoveBishop(input, board, color));
		case PiecesType::QUEEN: return (isValidMoveBishop(input, board, color)
										|| isValidMoveRook(input, board, color));
		case PiecesType::KING: return (isValidMoveKing(input, board, color));
		default: return (false);
	}
}

// Pre Condition: User must enter a move. And the piece must be a king.
// Post Condition: Returns true if the move is valid, false otherwise.
bool Pieces::isValidMoveKing(const vector <int> &input, const vector<vector<Pieces>> &board, char color) const {
	int	startX = getX();
	int	startY = getY();
	int	endX = input[2];
	int	endY = input[3];

	int	deltaX = abs(startX - endX);
	int	deltaY = abs(startY - endY);

	if (deltaX <= 1 && deltaY <= 1 && board[endY][endX].getColor() != color) {
		return (true);
	}
	else {
		return (false);
	}
}

// Pre Condition: User must enter a move. And the piece must be a knight.
// Post Condition: Returns true if the move is valid, false otherwise.
bool Pieces::isValidMoveKnight(const vector <int> &input, const vector<vector<Pieces>> &board, char color) const {
	int	startX = input[0];
	int	startY = input[1];
	int	endX = input[2];
	int	endY = input[3];

	int	deltaX = abs(startX - endX);
	int	deltaY = abs(startY - endY);

	if (deltaX == 2 && deltaY == 1 && board[endY][endX].getColor() != color) {
		return (true);
	}
	else if (deltaX == 1 && deltaY == 2 && board[endY][endX].getColor() != color) {
		return (true);
	}
	return (false);
}

// Pre Condition: User must enter a move. And the piece must be a bishop.
// Post Condition: Returns true if the move is valid, false otherwise.
bool Pieces::isValidMoveBishop(const vector<int> &input, const vector<vector<Pieces>> &board, char color) const {

	char		enemy = (color == 'W') ? 'B' : 'W';
	vector<int>	aX = {1,1,-1,-1}; // Bishop can move in 4 diagonal directions
	vector<int>	aY = {1,-1,1,-1};
	int			x = getX();
	int			y = getY();
	int			deltaX = abs(input[0] - input[2]);
	int			deltaY = abs(input[1] - input[3]);

	if (deltaX != deltaY)
		return false;
	for (int i = 0; i < 4; i++){
		int nX = aX[i] + x;
		int nY = aY[i] + y;
		// is the space between the start and end empty?
		while (nX >= 0 && nX < SIZE && nY >= 0 && nY < SIZE){
			if (board[nY][nX].getSymbol() != '.'){
				if (nY == input[3] && nX == input[2] && board[nY][nX].getColor() == enemy){
					return(true); // capture
				}
				break;
			}
			else if (nY == input[3] && nX == input[2]){
				return (true); // no capture
			}
			nX += aX[i];
			nY += aY[i];
		}
	}
	return (false); // invalid move
}


// Pre Condition: User must enter a move. And the piece must be a rook.
// Post Condition: Returns true if the move is valid, false otherwise.
bool Pieces::isValidMoveRook(const vector<int>& input, const vector<vector<Pieces>>& board, char color) const {
	// X or Y must be the same
	if ((input[0] != input[2] && input[1] != input[3]) || (input[0] == input[2] && input[1] == input[3])) {
		return false;
	}

	if (input[0] == input[2]) { // X is the same
		int minY = min(input[1], input[3]);
		int maxY = max(input[1], input[3]);

		for (int i = minY + 1; i < maxY; ++i) {
			if (board[i][input[0]].getSymbol() != '.') {
				return false;
 			}
		}
	} else { // Y is the same
		int minX = min(input[0], input[2]);
		int maxX = max(input[0], input[2]);

		for (int i = minX + 1; i < maxX; ++i) {
			if (board[input[1]][i].getSymbol() != '.') {
				return false;
			}
		}
	}

	// Check if the destination square is empty or has an opponent's piece
	return (!(board[input[3]][input[2]].getColor() == color));
}


// Pre Condition: User must enter a move. And the piece must be a pawn.
// Post Condition: Returns true if the move is valid, false otherwise.
bool	Pieces::isValidMovePawn(const vector <int> &input, const vector<vector<Pieces> > &board, char color) const
{
	int		x = this->getX();
	int		y = this->getY();
	int		direction = (color == 'W') ? -1 : 1; // White moves up, Black moves down

	if (input[2] == x && input[3] == y + direction && board[input[3]][input[2]].getType() == PiecesType::EMPTY) // Move forward
		return (true);
	else if (input[2] == x && input[3] == y + (direction * 2) && board[input[3]][input[2]].getType() == PiecesType::EMPTY && !this->getIsMoved() &&
			board[input[3] - direction][input[2]].getType() == PiecesType::EMPTY) // Move forward 2
		return (true);
	if (input[2] == x - 1 && input[3] == y + direction && board[input[3]][input[2]].getType() != PiecesType::EMPTY
			&& board[input[3]][input[2]].getColor() != color) // Capture left
		return (true);
	else if (input[2] == x + 1 && input[3] == y + direction && board[input[3]][input[2]].getType() != PiecesType::EMPTY
			&& board[input[3]][input[2]].getColor() != color) // Capture right
		return (true);
	return (false);
}

// Post Condition: Returns the type of the piece according to the symbol
PiecesType Pieces::getSymbol(char symbol)const{
	PiecesType type = (symbol == 'p' || symbol == 'P') ? PiecesType::PAWN :
				(symbol == 'r' || symbol == 'R') ? PiecesType::ROOK :
				(symbol == 'n' || symbol == 'N') ? PiecesType::KNIGHT :
				(symbol == 'b' || symbol == 'B') ? PiecesType::BISHOP :
				(symbol == 'q' || symbol == 'Q') ? PiecesType::QUEEN :
				(symbol == 'k' || symbol == 'K') ? PiecesType::KING :
				PiecesType::EMPTY;
	return (type);
}

// Post Condition: Returns the coordinate of the piece in the form of a string
string	Pieces::getCoordinate() const
{
	string coordinate;
	coordinate += (char)('a' + getX());
	coordinate += (char)('1' + (7 - getY()));
	return (coordinate);
}
