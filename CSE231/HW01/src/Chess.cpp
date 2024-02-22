#include "../header/Chess.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#ifndef SIZE
# define SIZE 8 // Size of the board
#endif

// Default constructor
Chess::Chess() : _board(), _isWhiteTurn(true), _isCheck(false), _isCheckMate(false)
{/*Body intentionally left empty*/}

// Copy constructor
Chess::Chess(const Chess &c) : _board(c._board), _isWhiteTurn(c._isWhiteTurn),
								_isCheck(c._isCheck), _isCheckMate(c._isCheckMate)
{/*Body intentionally left empty*/}

// Assignment operator
Chess	&Chess::operator=(const Chess &c)
{
	if (this != &c)
	{
		_board = c._board;
		_isWhiteTurn = c._isWhiteTurn;
		_isCheck = c._isCheck;
		_isCheckMate = c._isCheckMate;
	}
	return (*this);
}

Chess::~Chess() {/*Body intentionally left empty*/}

// Post Condition: Runs the game
void	Chess::run()
{
	cout << "Welcome to Chess!" << endl;
	cout << _board << endl;
	while (!_isCheckMate){ // Game loop until checkmate
		if (_isWhiteTurn)
		{
			if (isStalemate('W')){ // if Stalemate then control Stalemate
				cout << "-- Stalemate ! Draw !-- " << endl;
				exit(0);
			}
			takeMove('W', 'B', _isWhiteTurn); // Take the move
			string enemy = getKingCoordinate('B'); // Get the enemy king coordinate for checkMate
			if (_isCheck && isCheckMate(enemy,'B')){ // if checked then control checkmate
				cout << "-- CheckMate ! White Wins !-- " << endl;
				_isCheckMate = true;
			}
		}
		else
		{
			if (isStalemate('B')){ // if Stalemate then control Stalemate
				cout << "-- Stalemate ! Draw !-- " << endl;
				exit(0);
			}
			takeMove('B', 'W', _isWhiteTurn);
			string enemy = getKingCoordinate('W');
			if (_isCheck && isCheckMate(enemy, 'W')){
				cout << "-- CheckMate ! Black Wins !-- " << endl;
				_isCheckMate = true;
			}
		}
		cout << _board << endl;
	}
}

// Pre Condition: Program wants to take a move
// Post Condition: Takes a move and evaluates the move
void	Chess::takeMove(char color, char enemyColor, bool &_isWhiteTurn)
{
	string	input; // User input Ex: a2a4
	string	enemyKingCoordinate;

	input = getInput(color); // Get the input from user
	if (input == "save"){
		saveGame(_isWhiteTurn); // Save the game to .txt file
		return;

	}
	else if (input == "load"){
		loadGame(_isWhiteTurn); // Load the game from .txt file
		return;
	}
	else if (input == "suggest"){
		Board tempBoard = _board;
		suggestMove(color, enemyColor, _board); // Suggest a move
		_board = tempBoard;
		return;
	}
	else if (input == "resign")
		exit(0); // User resigns
	else if (isCastling(input, color)){
		makeCastling(input, color); // Make castling
	}
	else { // if the move is valid and not a special move
		if (isCheckedAfterMove(input, color)) // Check after the move moved Player's king is in check
		{
			cout << "Invalid move! Your king is in check." << endl;
			return; // Reject the move
		}
		_board.movePiece(input); // Move the piece
		if (isPromotion(input, color)){
			_board.promotion(input, color); // Promote the pawn
		}

		string	enemyKing = getKingCoordinate(enemyColor); // Get the enemy king coordinate
		_isCheck = isCheck(enemyKing, color, _board); // if the enemy king is in check
		if (_isCheck)
			cout << "Check !" << endl; // Screams check
	}
	_isWhiteTurn = !_isWhiteTurn; // Change the turn

}

// ****************Input Control Functions****************

// Pre Condition: Program wants to get the user input
// Post Condition: Returns the user input if it's valid
// if not valid warns the user and asks for input again
string	Chess::getInput(char color) const
{
	string			input;
	const string	player = (color == 'B') ? "Black" : "White"; // Player's color for prompt

	do {
		cout << "[" << player  << " 's Turn]\nEnter your move: ";
		getline(cin, input);
		if (isSpecialMove(input, color))
			return input;
	} while (!isValidInput(input, color));
	return input;
}

// Pre Condition: Program wants to check if the input is valid
// Post Condition: Returns true if the input is valid, false otherwise
bool	Chess::isValidInput(string input, char c) const
{
	if (input.length() != 4){ // Check if the input is 4 characters long
		cout << "Invalid Move " << input << " length is not valid! " << endl;
		return false;
	}
	else if (isInputsLetterValid(input) == false) { // Check if the input is in the range of the board
		cout << "Invalid Move " << input << " letter is not valid! " << endl;
		return false;
	}
	// Convert the input to vector coordinates
	vector <int> inputV = {(input[0] - 'a'), 7 - (input[1] - '1'), input[2] - 'a', 7 -(input[3] - '1')};
	if (isOccupied(inputV, c)){ // Check if the destination is occupied by the player or start is empty
		if (_board.getBoard()[inputV[1]][inputV[0]].getSymbol() == '.') // Check if the start is empty
			cout << "Start is empty !" << endl;
		else
			cout << "Destination is occupied by '" << _board.getBoard()[inputV[3]][inputV[2]].getSymbol() << "' !" << endl;
		return false;
	}
	else if (isValidMove(inputV, c) == false) { // Check if the move is valid
		cout << "Invalid Move by '" << _board.getBoard()[inputV[1]][inputV[0]].getSymbol() << "' at " << input.substr(0,2) << " coordinate !" << endl;
		return false;
	}
	return (true);
}

// Pre Condition: Program wants to check if the destination is occupied by the player
// Post Condition: Returns true if the destination is occupied by the player, false otherwise
bool	Chess::isOccupied(const vector<int> &input, char c) const
{

	if (_board.getBoard()[input[1]][input[0]].getColor() == c &&
		_board.getBoard()[input[3]][input[2]].getColor() != c){
		return (false);
	}
	return (true);
}

// Pre Condition: Program wants to check if the input is in the range of the board
// Post Condition: Returns true if the input is in the range of the board, false otherwise
bool Chess::isInputsLetterValid(string input) const {
	if ((input[0] < 'a' || input[0] > 'h') ||
		(input[2] < 'a' || input[2] > 'h'))
		return false;
	else if ((input[1] < '1' || input[1] > '8') ||
		(input[3] < '1' || input[3] > '8'))
		return false;
	else if (input[0] == input[2] && input[1] == input[3])
		return false;
	return true;
}

// Pre Condition: Program wants to check if the move is a special move
// Post Condition: Returns true if the move is a special move, false otherwise
bool	Chess::isSpecialMove(string input, char color) const
{
	if (input == "resign")
	{
		cout << ((color == 'W') ? "White" : "Black") << " resigns. " << ((color == 'W') ? "Black" : "White") << " wins." << endl;
		return (true);
	}
	else if (input == "load"){
		return (true);
	}
	else if (input == "save"){
		return (true);
	}
	else if (input == "suggest"){
		return (true);
	}
	else if (isCastling(input, color)){
		return (true);
	}
	return (false);
}

// Pre Condition: Program wants to check if the move is valid
// Post Condition: Returns true if the move is valid, false otherwise
bool	Chess::isValidMove(const vector<int> &input, char c) const
{
	if (_board.getBoard()[input[1]][input[0]].isValidMove(input, _board.getBoard(), c))
		return (true);
	return (false);
}

// Pre Condition: Program wants to check if the move is a promotion
// Post Condition: Returns true if the move is a promotion, false otherwise
// Promotion Condition: Pawn reaches the end of the board and it's a valid move
bool	Chess::isPromotion(string input, char color) const
{
	vector <int> inputV = {(input[0] - 'a'), 7 - (input[1] - '1'), input[2] - 'a', 7 -(input[3] - '1')};

	if (color == 'W'){
		if (_board.getBoard()[inputV[3]][inputV[2]].getSymbol() == 'P' && inputV[3] == 0){
			return (true);
		}
	}
	else if (color == 'B'){
		if (_board.getBoard()[inputV[3]][inputV[2]].getSymbol() == 'p' && inputV[3] == 7){
			return (true);
		}
	}
	return (false);
}


// Pre Condition: User wants to make castling
// Post Condition: Makes castling
bool	Chess::isCastling(string input, char color) const
{
	if (input == "O-O-O"){
		if (color == 'W'){
			if (_board.getBoard()[7][4].getSymbol() == 'K' && _board.getBoard()[7][0].getSymbol() == 'R'
				&& _board.getBoard()[7][1].getSymbol() == '.' && _board.getBoard()[7][2].getSymbol() == '.'
				&& _board.getBoard()[7][3].getSymbol() == '.' && !_board.getBoard()[7][4].getIsMoved()
				&& !_board.getBoard()[7][0].getIsMoved()){
				return (true);
			}
		}
		else if (color == 'B'){
			if (_board.getBoard()[0][4].getSymbol() == 'k' && _board.getBoard()[0][0].getSymbol() == 'r'
				&& _board.getBoard()[0][1].getSymbol() == '.' && _board.getBoard()[0][2].getSymbol() == '.'
				&& _board.getBoard()[0][3].getSymbol() == '.' && !_board.getBoard()[0][4].getIsMoved()
				&& !_board.getBoard()[0][0].getIsMoved()){
				return (true);
			}
		}
	}
	else if (input == "O-O"){
		if (color == 'W'){
			if (_board.getBoard()[7][4].getSymbol() == 'K' && _board.getBoard()[7][7].getSymbol() == 'R'
			&& _board.getBoard()[7][5].getSymbol() == '.' && _board.getBoard()[7][6].getSymbol() == '.'
			&& !_board.getBoard()[7][4].getIsMoved() && !_board.getBoard()[7][7].getIsMoved()){
				return (true);
			}
		}
		else if (color == 'B'){
			if (_board.getBoard()[0][4].getSymbol() == 'k' && _board.getBoard()[0][7].getSymbol() == 'r'
			&& _board.getBoard()[0][5].getSymbol() == '.' && _board.getBoard()[0][6].getSymbol() == '.'
			&& !_board.getBoard()[0][4].getIsMoved() && !_board.getBoard()[0][7].getIsMoved()){
				return (true);
			}
		}
	}
	return (false);
}

// ********************************************************************************
// *************************Move Control Functions*******************

// Pre Condition: Program wants to get algebraic notation of the move
// Ex:: 7252 -> a2a4
// Move[0] = fromColumn, Move[1] = fromRow, Move[2] = toColumn, Move[3] = toRow
// Post Condition: Returns the algebraic notation of the move
static string getAlgebraicNotation(const vector<int>& move) {
	string algebraicNotation = "";

	char fromColumn = static_cast<char>('a' + move[0]);
	char toColumn = static_cast<char>('a' + move[2]);

	int fromRow = SIZE - move[1];
	int toRow = SIZE - move[3];

	algebraicNotation += fromColumn;
	algebraicNotation += std::to_string(fromRow);
	algebraicNotation += toColumn;
	algebraicNotation += std::to_string(toRow);

	return algebraicNotation;
}

// Pre Condition: Program wants to get all valid moves for a color
// Post Condition: Returns all valid moves for a color
vector<string> Chess::getWholeValidMoves(char color) const
{
	vector<string>	validMoves;

	// Loop through the entire board
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			// Check if the piece belongs to the specified color
			if (_board.getBoard()[i][j].getColor() == color)
			{
				// Loop through all possible moves for the piece
				for (int m = 0; m < SIZE; m++)
				{
					for (int n = 0; n < SIZE; n++)
					{
						vector<int> move = {j, i, n, m};
						string input = getAlgebraicNotation(move); // Get the algebraic notation of the move
						// Check if the move is valid
						if (_board.getBoard()[i][j].isValidMove(move, _board.getBoard(), color)
						&& !isCheckedAfterMove(input, color))
						{
							validMoves.push_back(input);
						}
					}
				}
			}
		}
	}

	return validMoves;
}

// Pre Condition: Program wants to check if the king is in checkmate
// Post Condition: Returns true if the king is in checkmate, false otherwise
bool Chess::isCheckMate(const string &enemyKingCoordinate, char enemyColor) const
{
	vector<int>	enemyKingCoord = {(enemyKingCoordinate[0] - 'a'), 7 - (enemyKingCoordinate[1] - '1')};

	auto validMoves = getWholeValidMoves(enemyColor);

	for (const auto &input : validMoves)
	{
		// If the move is legal and doesn't break the check, the king is not in checkmate
		if (!isCheckedAfterMove(input, enemyColor))
		{	return false ; }
	}

	// If no valid moves are found, it's checkmate
	return true;
}


// Pre Condition: Program wants to check if the enemy king is in check
// Post Condition: Returns true if the enemy king is in check, false otherwise
bool Chess::isCheck(const string &enemyKingCoordinate, char color, const Board &tempBoard) const
{
	vector<int>	enemyKingCoord = {(enemyKingCoordinate[0] - 'a'), 7 - (enemyKingCoordinate[1] - '1')};
	vector<int>	tempInput;
	// Loop through the entire board to check for pieces threatening the enemy king
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			if (tempBoard.getBoard()[i][j].getColor() == color && tempBoard.getBoard()[i][j].getSymbol() != '.')
			{
				tempInput = {j, i, enemyKingCoord[0], enemyKingCoord[1]};
				if (tempBoard.getBoard()[i][j].isValidMove(tempInput, tempBoard.getBoard(), color))
				{
					return true;
				}
			}
		}
	}

	return false;
}

// Pre Condition: Program wants to check if the king is in check after the move
// Post Condition: Returns true if the king is in check after the move, false otherwise
bool Chess::isCheckedAfterMove(const string &input, char color) const
{
	// Clone the current board to simulate the move
	Board tempBoard = _board;
	tempBoard.movePiece(input);
	// Get the coordinates of the king of the moving color
	string kingCoordinate = tempBoard.getKingCoordinate(color);
	char enemy = (color == 'W') ? 'B' : 'W';
	// Check if the king is in check after the move
	return isCheck(kingCoordinate, enemy, tempBoard);
}


// Pre Condition: Program wants to get the count of the specified symbol while checking Stalemate
// Post Condition: Returns the count of the specified symbol
static int	getCount(char symbol, const Board &b){
	int count = 0;

	for (const auto &row : b.getBoard()){
		for (const auto &piece : row){
			if (piece.getSymbol() == symbol){
				count++;
			}
		}
	}
	return count;
}

// Pre Condition: Program wants to check if the game is in Stalemate with no legal moves
// Post Condition: Returns true if the game is in Stalemate with no legal moves, false otherwise
bool	Chess::isStalemateNoMoves(char color) const
{
	vector<string>	validMoves = getWholeValidMoves(color);

	if (validMoves.empty())
		return (true);
	return (false);
}

// Pre Condition: Program wants to check if the game is in Stalemate with limited pieces
// Post Condition: Returns true if the game is in Stalemate with limited pieces, false otherwise
bool	Chess::isStalemateOnPieces(char color) const
{	int knightCount = getCount((color == 'W') ? 'N' : 'n', _board);
	int bishopCount = getCount((color == 'W') ? 'B' : 'b', _board);
	int rookCount = getCount((color == 'W') ? 'R' : 'r', _board);
	int queenCount = getCount((color == 'W') ? 'Q' : 'q', _board);
	int pawnCount = getCount((color == 'W') ? 'P' : 'p', _board);

	int opponentKnightCount = getCount((color == 'B') ? 'n' : 'N', _board);
	int opponentBishopCount = getCount((color == 'B') ? 'b' : 'B', _board);
	int opponentRookCount = getCount((color == 'B') ? 'r' : 'R', _board);
	int opponentQueenCount = getCount((color == 'B') ? 'q' : 'Q', _board);
	int opponentPawnCount = getCount((color == 'B') ? 'p' : 'P', _board);

	if (knightCount == 0 && bishopCount == 0 && rookCount == 0 && queenCount == 0 && pawnCount == 0 &&
		opponentKnightCount == 0 && opponentBishopCount == 0 && opponentRookCount == 0 &&
		opponentQueenCount == 0 && opponentPawnCount == 0) {
		return true;
	}

	if (knightCount == 1 && bishopCount == 0 && rookCount == 0 && queenCount == 0 && pawnCount == 0 &&
		opponentKnightCount == 0 && opponentBishopCount == 0 && opponentRookCount == 0 &&
		opponentQueenCount == 0 && opponentPawnCount == 0) {
		return true;
	}

	if (knightCount == 0 && bishopCount == 1 && rookCount == 0 && queenCount == 0 && pawnCount == 0 &&
		opponentKnightCount == 0 && opponentBishopCount == 0 && opponentRookCount == 0 &&
		opponentQueenCount == 0 && opponentPawnCount == 0) {
		return true;
	}

	return false;
}

// Pre Condition: Program wants to check if the game is in Stalemate
// Post Condition: Returns true if the game is in Stalemate, false otherwise
bool	Chess::isStalemate(char color) const
{
	if (isStalemateNoMoves(color))
		return (true);
	if (isStalemateOnPieces('W') && isStalemateOnPieces('B'))
		return (true);
	return (false);
}

// ********************************************************************************
// ************************Special Moves*******************
void	Chess::makeCastling(const string &input, char color)
{
	if (input == "O-O-O"){
		if (color == 'W'){
			if (isCheckedAfterMove("e1c1", color) == false &&
				isCheckedAfterMove("a1d1", color) == false){
				_board.movePiece("e1c1");
				_board.movePiece("a1d1");
			}
			else {
				cout << "Invalid Move ! Pieces are threatened after move !" << endl;
				_isWhiteTurn = !_isWhiteTurn;
			}
		}
		else if (color == 'B'){
			if (isCheckedAfterMove("e8c8", color) == false &&
				isCheckedAfterMove("a8d8", color) == false){
				_board.movePiece("e8c8");
				_board.movePiece("a8d8");
			}
			else {
				cout << "Invalid Move ! Pieces are threatened after move !" << endl;
				_isWhiteTurn = !_isWhiteTurn;
			}
		}
	}
	else if (input == "O-O"){
		if (color == 'W'){
			if (isCheckedAfterMove("e1g1", color) == false &&
				isCheckedAfterMove("h1f1", color) == false){
				_board.movePiece("e1g1");
				_board.movePiece("h1f1");
			}
			else {
				cout << "Invalid Move ! Pieces are threatened after move !" << endl;
				_isWhiteTurn = !_isWhiteTurn;
			}
		}
		else if (color == 'B'){
			if (isCheckedAfterMove("e8g8", color) == false &&
				isCheckedAfterMove("h8f8", color) == false){
				_board.movePiece("e8g8");
				_board.movePiece("h8f8");
			}
			else {
				cout << "Invalid Move ! Pieces are threatened after move !" << endl;
				_isWhiteTurn = !_isWhiteTurn;
			}
		}
	}
}

// Pre Condition: User wants to load a game from a file
// Post Condition: Loads the game from the file
void	Chess::loadGame(bool &isWhite){
	std::ifstream ifs;
	string fileName;

	do {
		if (fileName.length() == 0) {
			cout << "Enter the name of the file: ";
			getline(cin, fileName);
		}
		if (fileName.length() != 0) {
			if (fileName.find(".txt") == string::npos) {
				fileName += ".txt";
			}
		}
	} while (fileName.length() == 0);
	fileName = "./Board/" + fileName;
	ifs.open(fileName);
	if (ifs.is_open()) {
		ifs >> _board;
		string color;
		ifs >> color;
		if (color == "White") { isWhite = true;}
		else if (color == "Black") {isWhite = false;}
		_isWhiteTurn = isWhite;
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

// Pre Condition: User wants to save the game to a file
// Post Condition: Saves the game to the file
void Chess::saveGame(const bool &isW) const {
	std::ofstream ofs;
	string fileName;

	do {
		if (fileName.length() == 0) {
			cout << "Enter the name of the file: ";
			getline(cin, fileName);
		}
		if (fileName.length() != 0) {
			if (fileName.find(".txt") == string::npos) {
				fileName += ".txt";
			}
		}
	} while (fileName.length() == 0);
	fileName = "./Board/" + fileName;
	ofs.open(fileName);
	if (ofs.is_open()) {
		ofs << _board;
		if (isW) ofs << "White";
		else ofs << "Black";
		ofs.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

// Pre Condition: Program wants to swap the x and y coordinates
// Post Condition: Returns the swapped coordinates as a string
static string	swapXandYtoStr(int x, int y) {
	char startX = 'a' + x;
	char startY = '1' + (7 - y);

	// Sonuç stringini oluştur
	string result = "";
	result += startX;
	result += startY;

	return result;
}

// Pre Condition: Program wants to get the total point of the pieces
// Post Condition: Returns the total point of the pieces
double	Chess::getTotalPoint(char c, const Board &b) const {
	double totalScore = 0.0;
	char enemy = (c == 'W') ? 'B' : 'W';

	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			if (b.getBoard()[i][j].getColor() == c){
				double piecesValue = static_cast<double>(b.getBoard()[i][j].getPoint());
				string swaped = swapXandYtoStr(j,i);
				if (isCheck(swaped, enemy, b)){ // if the piece is threatening the enemy piece
					totalScore += piecesValue / 2.0;
				}
				else {
					totalScore += piecesValue;
				}
			}
		}
	}
	return totalScore;
}

// Post Condition: Returns the depth of the minimax algorithm
static int getDepth(const Board &b) {
	int knightCount = getCount('N', b);
	int bishopCount = getCount('B', b);
	int rookCount = getCount('R', b);
	int queenCount = getCount('Q', b);
	int pawnCount = getCount('P', b);

	int opponentKnightCount = getCount('n', b);
	int opponentBishopCount = getCount('b', b);
	int opponentRookCount = getCount('r', b);
	int opponentQueenCount = getCount('q', b);
	int opponentPawnCount = getCount('p', b);

	int totalPieceCount = knightCount + bishopCount + rookCount + queenCount + pawnCount +
		opponentKnightCount + opponentBishopCount + opponentRookCount + opponentQueenCount + opponentPawnCount;

	if (totalPieceCount <= 10) {
		return 3;
	} else if (totalPieceCount <= 15) {
		return 2;
	} else {
		return 1;
	}
}

// pre Condition: Program wants to get the suggested move
// Post Condition: Returns the suggested move
string Chess::getSuggestRecur(char suggested, char playerColor, char enemyColor, int depth, Board &b, double min, double max) const {
	vector<string> validMoves = getWholeValidMoves(playerColor);
	string bestMove = "";
	char enemy = (suggested == 'W') ? 'B' : 'W';
	// if king is in threat then return the move that saves the king
	if (_isCheck) {
		for (const auto &input : validMoves) {
			if (!isCheckedAfterMove(input, playerColor)) {
				return input;
			}
		}
		return "";
	}

	for (const auto &input : validMoves) {
		Board tempBoard = b;
		b.movePiece(input);

		if (isCheckMate(getKingCoordinate(enemyColor), enemyColor) || isPromotion(input, playerColor)) {
			return input;
		}
		if (isCheck(input.substr(2,4), enemyColor, b)) {
			b = tempBoard;
			continue;
		}
		double newScorePlayer = getTotalPoint(suggested, b);
		double newScoreEnemy = getTotalPoint(enemy, b);
		double score = newScorePlayer - newScoreEnemy;

		if (depth > 1) {
			string bestMoveRecur = getSuggestRecur(suggested, enemyColor, playerColor, depth - 1, b, -max, -min);
			if (!bestMoveRecur.empty()) {
				b.movePiece(bestMoveRecur);
				double scoreAfterRecur = getTotalPoint(suggested, b) - getTotalPoint(enemy, b);
				if (-scoreAfterRecur > min) {
					min = -scoreAfterRecur;
					bestMove = input;
				}
			}
		}
		else if (score > min) {
			min = score;
			bestMove = input;
		}

		b = tempBoard;

		if (min >= max) {
			// min-max inValidation
			break;
		}
	}

	return bestMove;
}

// Pre Condition: Program wants to suggest a move
// Post Condition: Suggests a move
void	Chess::suggestMove(char c, char enemy, Board &b) const {
	int depth = getDepth(b);
	string bestMove = getSuggestRecur(c, c, enemy, depth, b, -450.0, 450.0);

	if (!bestMove.empty()) {
		cout << "Suggested Move : " << bestMove << endl;
	} else {
		cout << "No suggested move available." << endl;
	}
}

// ********************************************************************************

// ****************Setters and Getters****************

// Pre Condition: Program wants to get the coordinate of the king of the specified color
// Post Condition: Returns the coordinate of the king of the specified color
string	Chess::getKingCoordinate(char color) const
{
	string	kingCoordinate;
	char	kingSymbol = (color == 'W') ? 'K' : 'k';

	for (const auto &row : _board.getBoard())
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
// ****************************************************************
