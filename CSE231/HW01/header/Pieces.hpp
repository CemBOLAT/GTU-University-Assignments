#ifndef PIECES_HPP
# define PIECES_HPP

#include <vector>
#include <string>
using std::vector;
using std::string;

// Strongly typed enum class for pieces type
enum class PiecesType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	EMPTY
};

// Strongly typed enum class for pieces point
enum class Point{
	PAWN = 1,
	ROOK = 5,
	KNIGHT = 3,
	BISHOP = 3,
	QUEEN = 9,
	KING = 0,
	EMPTY = 0
};

class Pieces {
	public:
		// Big Three + Constructors
		Pieces();
		explicit Pieces(int coordinateX, int coordinateY, char color, PiecesType type);
		explicit Pieces(int coordinateX, int coordinateY, char color, char symbol);
		Pieces(const Pieces &p);
		Pieces	&operator=(const Pieces &p);
		~Pieces();

		// **************** Setters and Getters ****************
		inline char			getSymbol() const { return (_symbol); }
		inline int			getX() const { return (_x); }
		inline int			getY() const { return (_y); }
		inline char			getColor() const { return (_color); }
		inline PiecesType	getType() const { return (_type); }
		inline Point		getPoint() const { return (_point); }
		inline bool			getIsMoved() const { return (_isMoved); }
		PiecesType			getSymbol(char _type) const;
		string				getCoordinate() const;

		inline void			setSymbol(char symbol) { _symbol = symbol;}
		inline void			setX(int x) { _x = x; }
		inline void			setY(int y) { _y = y; }
		inline void			setColor(char color) { _color = color; }
		inline void			setType(PiecesType type) { _type = type; }
		inline void			setPoint(Point point) { _point = point; }
		inline void			setIsMoved(bool isMoved) { _isMoved = isMoved; }
		void				setSymbol(PiecesType type, char color);
		void				setPoint(PiecesType type);
		// ****************************************************************
		// ****************Move Control Functions****************
		bool				isValidMove(const vector <int> &a, const vector<vector<Pieces> > &board, char color) const;
		bool				isValidMovePawn(const vector <int> &a , const vector<vector<Pieces> > &board, char color) const;
		bool				isValidMoveRook(const vector <int> &a , const vector<vector<Pieces> > &board, char color) const;
		bool				isValidMoveKnight(const vector <int> &a , const vector<vector<Pieces> > &board, char color) const;
		bool				isValidMoveBishop(const vector <int> &a , const vector<vector<Pieces> > &board, char color) const;
		bool				isValidMoveKing(const vector <int> &a , const vector<vector<Pieces> > &board, char color) const;
		bool				isReallyMoved() const; // Checks if the piece is moved after loading
		// ****************************************************************
	private:
		int			_x;
		int			_y;
		char		_symbol;
		char		_color;
		PiecesType	_type;
		Point		_point;
		bool		_isMoved;
};

#endif


