#include "Board.h"

// Constructor
Board::Board() {}

// Destructor
Board::~Board() {}

// Function to create header for the game
void Board::CreateHeader() {
	cout << "Tic Tac Toe " << endl;
	cout << "Player = X  AI Computer = O" << endl;
}

// Function to initialize the board
void Board::CreateBoard() {
	cout << endl;
	cout << this->board[0][0] << " " << this->board[0][1] << " " << this->board[0][2] << endl;
	cout << this->board[1][0] << " " << this->board[1][1] << " " << this->board[1][2] << endl;
	cout << this->board[2][0] << " " << this->board[2][1] << " " << this->board[2][2] << endl;
}

// Function to print the board
void Board::PrintBoard() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			cout << this->board[i][j] << ' ';
		}
		cout << endl;
	}
}

// Function to run the game
void Board::Run() {
	this->CreateHeader();
	this->CreateBoard();
	this->BeginGame();
}

// Function to begin the game
void Board::BeginGame() {
	bool status = true;
	while (status) {
		while (!this->CheckGameState().second) {
			this->UpdateMove();
		}
		status = this->PlayAgain();
	}
}

// Function to determine if play again
bool Board::PlayAgain() {
	char decision;
	bool booleanDecision = false;
	cout << "Do you want to play again? (Y/N): ";
	cin >> decision;
	// Need error handling here
	if (decision == 'Y' || decision == 'y') {
		this->RestartGame();
		booleanDecision = true;
	}
	else if (decision == 'N' || decision == 'n') {
		booleanDecision = false;
	}
	return booleanDecision;
}

// Function to restart the game
void Board::RestartGame() {
	this->ClearTerminal();
	this->CreateHeader();
	// Reset the board
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			this->board[i][j] = BLANK_MARKER;
		}
	}
	this->PrintBoard();
}

// Function to check the state of the game
std::pair<int,bool> Board::CheckGameState() {
	if (this->IsGameWon(this->board, PLAYER_MARKER)) {
		return std::make_pair(WIN, true);
	}
	if (this->IsGameLoss(this->board, PLAYER_MARKER)) {
		return std::make_pair(LOSS, true);
	}
	if (this->IsBoardFull(this->board)) {
		return std::make_pair(DRAW,true);
	}
	return std::make_pair(INPROGESS, false);
}

// Function to check if game is won
bool Board::IsGameWon(char(&board)[3][3], char player) {
	// Check rows and columns
	for (int i = 0; i < 3; ++i) {
		if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
			(board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
			cout << "You Won!" << endl;
			return true; // Win in row or column
		}
	}

	// Check diagonals
	if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
		(board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
		cout << "You Won!" << endl;
		return true; // Win in diagonal
	}
	return false;
}

// Function to check if game is lost
bool Board::IsGameLoss(char(&board)[3][3], char player) {
	// Check rows and columns for the opponent (not player)
	char opponent = (player == PLAYER_MARKER) ? AI_MARKER : PLAYER_MARKER;
	for (int i = 0; i < 3; ++i) {
		if ((board[i][0] == opponent && board[i][1] == opponent && board[i][2] == opponent) ||
			(board[0][i] == opponent && board[1][i] == opponent && board[2][i] == opponent)) {
			cout << "You Loss!" << endl;
			return true; // Loss in row or column for the opponent
		}
	}

	// Check diagonals for the opponent
	if ((board[0][0] == opponent && board[1][1] == opponent && board[2][2] == opponent) ||
		(board[0][2] == opponent && board[1][1] == opponent && board[2][0] == opponent)) {
		cout << "You Loss!" << endl;
		return true; // Loss in diagonal for the opponent
	}

	return false;
}

// Function to check if board is full
bool Board::IsBoardFull(char(&board)[3][3]) {
	// Check if the board is full (no BLANK_MARKER left)
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == BLANK_MARKER) {
				return false; // Board is not full
			}
		}
	}
	cout << "Tie!" << endl;
	return true; // Board is full
}

// Function to refresh the board displayed on the terminal
void Board::RefreshScreen() {
	this->ClearTerminal();
	this->CreateHeader();
	this->PrintBoard();
}

// Function to update the move
void Board::UpdateMove() {
	std::pair<int, int> playerMove = this->GetPlayerMove();
	if (this->IsLegalMove(playerMove.first, playerMove.second)) {
		this->PlayerMakeMove(playerMove.first, playerMove.second);
		this->AIMakeMove();
		this->RefreshScreen();
	}
	else {
		this->RefreshScreen();
		cout << "Postion: " << playerMove.first << "," << playerMove.second << " is not a legal move." << endl;
		this->UpdateMove();
	}
}

// Check if player move is legal
bool Board::IsLegalMove(int row, int col) {
	if (this->board[row][col] == BLANK_MARKER) {
		return true;
	}
	return false;
}

// Function to get the player's desired move
std::pair<int, int> Board::GetPlayerMove() {
	int row, col;
	cout << "Row position: ";
	cin >> row;
	cout << "Col play: ";
	cin >> col;
	cout << endl << endl;

	return std::make_pair(row, col);
}

// Function to make the move
void Board::PlayerMakeMove(int row, int col) {
	this->board[row][col] = PLAYER_MARKER;
}

// Function for AI to make moves
void Board::AIMakeMove() {
	std::pair<int, int> bestMoves = this->aiInstance.getBestMove(this->board);
	this->board[bestMoves.first][bestMoves.second] = AI_MARKER;

}

// Function to check is the position is occupired
bool Board::IsPositionOccupied(std::pair<int, int> pos) {
	return false;
}

// Function to clear the terminal
void Board::ClearTerminal() {
	// Clearing the terminal
	#ifdef _WIN32
		system("cls"); // For Windows
	#else
		system("clear"); // For Unix/Linux
	#endif
}