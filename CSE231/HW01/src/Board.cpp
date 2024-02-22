#include <string>
#include "../header/Board.hpp"
#include "../header/Pieces.hpp"

#ifndef SIZE
# define SIZE 8 // Size of the board
#endif

using namespace std;

// Though nobody recommanded our professor forced us to use static function instead of unnamed namespace.
// because he had not taught us about unnamed namespace when the homework was submitted.
// Post Conditions: Fills the board with black pieces
static void	fillBlack(vector<vector<Pieces> > &_board){
	for (int i = 0; i < SIZE; i++){
		if (i == 0 || i == 7)
			_board[0][i] = (Pieces(i, 0, 'B', PiecesType::ROOK));
		else if (i == 1 || i == 6)
			_board[0][i] = (Pieces(i, 0, 'B', PiecesType::KNIGHT));
		else if (i == 2 || i == 5)
			_board[0][i] = (Pieces(i, 0, 'B', PiecesType::BISHOP));
		else if (i == 3)
			_board[0][i] = (Pieces(i, 0, 'B', PiecesType::QUEEN));
		else if (i == 4)
			_board[0][i] = (Pieces(i, 0, 'B', PiecesType::KING));
	}
	for (int i = 0; i < SIZE; i++)
		_board[1][i] = (Pieces(i, 1, 'B', PiecesType::PAWN));
}

// Post Conditions: Fills the board with empty pieces
static void	fillEmpty(vector<vector<Pieces> > &_board){
	for (int i = 2; i < 6; ++i){
		for (int j = 0; j < SIZE; ++j){
			_board[i][j] = (Pieces(j, i, '.', PiecesType::EMPTY));
		}
	}
}

// Post Conditions: Fills the board with white pieces
static void	fillWhite(vector<vector<Pieces> > &_board){
	for (int i = 0; i < SIZE; i++)
		_board[6][i] = (Pieces(i, 6, 'W', PiecesType::PAWN));
	for (int i = 0; i < SIZE; i++){
		if (i == 0 || i == 7)
			_board[7][i] = (Pieces(i, 7, 'W', PiecesType::ROOK));
		else if (i == 1 || i == 6)
			_board[7][i] = (Pieces(i, 7, 'W', PiecesType::KNIGHT));
		else if (i == 2 || i == 5)
			_board[7][i] = (Pieces(i, 7, 'W', PiecesType::BISHOP));
		else if (i == 3)
			_board[7][i] = (Pieces(i, 7, 'W', PiecesType::QUEEN));
		else if (i == 4)
			_board[7][i] = (Pieces(i, 7, 'W', PiecesType::KING));
	}
}

// Post Conditions: Initializes the board
Board::Board() : _board(SIZE, vector<Pieces>(SIZE)) {
	fillBlack(_board);
	fillEmpty(_board);
	fillWhite(_board);
}

// Post Conditions: Copy constructor
Board::Board(const Board &b) : _board(b._board) {}

// Post Conditions: Assignment operator
Board	&Board::operator=(const Board &b)
{
	if (this != &b){
		for (int i = 0; i < SIZE; i++){
			for (int j = 0; j < SIZE; j++){
				_board[i][j] = b._board[i][j];
			}
		}
	}
	return (*this);
}

Board::~Board() {/*Body intentionally left empty*/}

// Post Conditions: Prints the board
ostream	&operator<<(ostream &os, const Board &b){
	for (int i = 0; i < SIZE; i++){
		os << SIZE - i << " |";
		for (int k = 0; k < SIZE; k++) {
			os << " " << b._board[i][k].getSymbol() << " ";
		}
		os << endl;
	}
	os << "    ";
	for (int i = 0; i < SIZE * 3; i++)
		os << "-";
	os << endl << "   ";
	for (int i = 0; i < SIZE; i++)
		os << " " << (char)(i + 'a') << " ";
	os << "\n" << endl;
	return os;
}

// Pre Conditions: Users want to load a the game from txt file
// Post Conditions: Reads the board and reinitializes it
istream &operator>>(istream &is, Board &b){
	string line;

	for (int i = 0; i < SIZE; i++){
		getline(is, line);
		for (int k = 0; k < SIZE; k++){
			char color;
			if (line[k] == '.')
				color = '.';
			else if (line[k] >= 'a' && line[k] <= 'z')
				color = 'B';
			else
				color = 'W';
			Pieces temp = Pieces(k,i,color, line[k]);
			b.getBoard()[i][k] = temp;

		}
	}
	return (is);
}

// Pre Condtions: Program wants to know the coordinate of the king of the given color
// Post Conditions: Returns the coordinate of the king of the given color
string	Board::getKingCoordinate(char color) const
{
	string	kingCoordinate;
	char	kingSymbol = (color == 'W') ? 'K' : 'k';

	for (const auto &row : _board)
	{
		for (const auto &piece : row)
		{
			if (piece.getSymbol() == kingSymbol)
			{
				kingCoordinate = piece.getCoordinate();
				break;
			}
		}
	}
	return (kingCoordinate);
}

// Pre Conditions: input is a valid move or simulated move
// Post Conditions: Moves the piece from the first coordinate to the second coordinate
void	Board::movePiece(string input){
	vector <int> inputV = {(input[0] - 'a'), 7 - (input[1] - '1'), input[2] - 'a', 7 -(input[3] - '1')};
	Pieces temp = Pieces(_board[inputV[1]][inputV[0]]);
	// everything is swapped except the coordinates because the coordinates are stable
	temp.setX(inputV[2]);
	temp.setY(inputV[3]);
	_board[inputV[1]][inputV[0]] = Pieces(input[0], input[1], '.', PiecesType::EMPTY);
	_board[inputV[3]][inputV[2]] = temp;
	_board[inputV[3]][inputV[2]].setIsMoved(true);
}

// Pre Conditions: Users want to save the game to txt file
// Post Conditions: Prints the board to a file
ofstream	&operator<<(ofstream &os, const Board &b){
	for (int i = 0; i < SIZE; i++){
		for (int k = 0; k < SIZE; k++) {
			os << b._board[i][k].getSymbol();
		}
		os << endl;
	}
	os << "\n" << endl;
	return os;
}

// Pre Conditions: input is a valid move or simulated move
// Post Conditions: Moves the piece from the first coordinate to the second coordinate
void	Board::promotion(string input, char c){
	string pieceInput;

	vector <int> inputV = {(input[0] - 'a'), 7 - (input[1] - '1'), input[2] - 'a', 7 -(input[3] - '1')};

	do {
		cout << "Congrats! You can promote your " << input.substr(0,2) << " pawn to a queen, rook, bishop, or knight." << endl;
		cout << "Promote to: ";
		getline(cin, pieceInput);
		if (pieceInput == "queen")
			_board[inputV[3]][inputV[2]] = Pieces(input[2], input[3], c, PiecesType::QUEEN);
		else if (pieceInput == "rook")
			_board[inputV[3]][inputV[2]] = Pieces(input[2], input[3], c, PiecesType::ROOK);
		else if (pieceInput == "bishop")
			_board[inputV[3]][inputV[2]] = Pieces(input[2], input[3], c, PiecesType::BISHOP);
		else if (pieceInput == "knight")
			_board[inputV[3]][inputV[2]] = Pieces(input[2], input[3], c, PiecesType::KNIGHT);
		else
			cout << "Invalid input. Please try again." << endl;
	} while (pieceInput != "queen" && pieceInput != "rook" && pieceInput != "bishop" && pieceInput != "knight");
}

