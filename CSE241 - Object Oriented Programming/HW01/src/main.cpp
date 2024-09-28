#include "../header/Chess.hpp"

using namespace std;

static void	printMenu();
static void	prinOptions();

// Post Condition: Runs the game
int	main(void)
{
	Chess	chess;
	string	mInput;
	do {
		printMenu();
		getline(cin, mInput);
	} while (mInput != "1" && mInput != "2" && mInput != "3");

	if (mInput == "1"){
		chess.run();
	}
	else if (mInput == "2"){
		string	input;
		prinOptions();
		getline(cin, input);
		chess.run(); // run the game
	}
	else if (mInput == "3"){
		cout << "GoodBYE !" << endl;
	}

	return (0);
}

static void	printMenu()
{
	cout << "1. Game" << endl;
	cout << "2. Options" << endl;
	cout << "3. Exit" << endl;
	cout << "----> ";
}

static void	prinOptions()
{
	cout << "Here is explanation of special moves ." << endl;
	cout << "1. Saving : Typing 'save' is enough for saving board to .txt file at ./Board folder\n\
after typing 'save' program will prompt you to enter name of .txt file.\n" << endl;
	cout << "2. Loading : Typing 'load' is enough to start loading section.\n \
After typing load program will prompt you to enter name of .txt file\n" << endl;
	cout << "3. Suggestion : Typing 'suggest' is enough to get the\
best move on the board according to point.\n" << endl;
	cout << "4. Castling : Typing 'O-O-O' or 'O-O' enough for CASTLING\n" << endl;
	cout <<	"Press any key then 'enter' to continue..." << endl;
}
