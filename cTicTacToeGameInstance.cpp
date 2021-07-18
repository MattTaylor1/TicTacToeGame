#include "cTicTacToeGameInstance.h"
#include <random>	// for ranlux48()
#include <map>
#include <string>
#include <iostream>

cTicTacToeGameInstance::cTicTacToeGameInstance()
{
	// Is private, so is never called
}

cTicTacToeGameInstance::~cTicTacToeGameInstance()
{

}

cTicTacToeGameInstance::cTicTacToeGameInstance(unsigned int player_X, unsigned int player_O)
{
	this->m_Player_X_SIN = player_X;
	this->m_Player_O_SIN = player_O;
	this->m_bGameIsCurrentlyRunning = true;
	// No winner yet, so set to zero
	this->m_winner_SIN = 0;

	// Generate a unique ID for this game state
	this->m_GenerateUniqueGameID();

	if (m_Player_X_SIN == 0 || m_Player_O_SIN == 0) {
		this->endGameAndDeclareWinner(cTicTacToeGameInstance::GAME_IS_OVER);
	}
	//create the board
	sSquare defaultSquare;
	defaultSquare.state = eSquareState::IS_EMPTY;

	for (unsigned int i = 0; i < 3; i++) {

		std::vector<sSquare> theRow;

		for (unsigned int j = 0; j < 3; j++) {

			defaultSquare.row = i;
			defaultSquare.column = j;
			theRow.push_back(defaultSquare);
			
		}

		theBoard.push_back(theRow);
	} 

	std::cout << "Game Board Created" << std::endl;
	
}

bool cTicTacToeGameInstance::updateGameInList(cTicTacToeGameInstance updatedGame) {

	//update the game to the Updated game
	this->m_bGameIsCurrentlyRunning = updatedGame.m_bGameIsCurrentlyRunning;
	this->m_Player_O_SIN = updatedGame.m_Player_O_SIN;
	this->m_Player_X_SIN = updatedGame.m_Player_X_SIN;
	this->m_winner_SIN = updatedGame.m_winner_SIN;

	//update board
	for (unsigned int i = 0; i < this->theBoard.size(); i++) {
		for (unsigned int j = 0; j < this->theBoard[i].size(); j++) {
			this->theBoard[i][j] = updatedGame.theBoard[i][j];
		}
	}

	return true;
}

std::string cTicTacToeGameInstance::m_GenerateUniqueGameID(void)
{
	// Have we already created an instance of the random engine?
	if ( cTicTacToeGameInstance::m_pRandEngine == NULL )
	{
		// Nope. So let's make one...
		// (seed with the current time, too)
		std::random_device rd;
		cTicTacToeGameInstance::m_pRandEngine = new std::ranlux48( rd() );
	}//if (cGameState::m_pRandEngine

	// At this point the random engine and distributions are made

	// Have we already made a unique ID? (i.e. is it NOT blank?)
	if ( this->m_UniqueGameID == "" )
	{
		// Nope. So make one...
		std::set<std::string>::iterator itNewID = cTicTacToeGameInstance::m_setUsedIDs.end();
		do
		{
			// The unique ID is a set of letter+number pairs
			const unsigned int NUMBEROFCHARACTERPAIRS = 5;
			for ( unsigned int count = 0; count != NUMBEROFCHARACTERPAIRS; count++ )
			{
				// Add a random letter...
				unsigned long long randLetterRaw = (*cTicTacToeGameInstance::m_pRandEngine)();
				randLetterRaw %= ( 'Z' - 'A' );
				randLetterRaw += 'A';
				char randLetter = (char)randLetterRaw;

				// Add a random digit...
				unsigned long long randDigitRaw = (*cTicTacToeGameInstance::m_pRandEngine)();
				randDigitRaw %= 10;
				randDigitRaw += '0';
				char randDigit = (char)randDigitRaw;

				this->m_UniqueGameID += randLetter;
				this->m_UniqueGameID += randDigit;
			}//for (count...

			// See if we already have this ID...
			itNewID = cTicTacToeGameInstance::m_setUsedIDs.find(this->m_UniqueGameID);
			if ( itNewID == cTicTacToeGameInstance::m_setUsedIDs.end() )
			{
				// Didn't find a match, so we're good (it's unique)
				// Add it to the set
				cTicTacToeGameInstance::m_setUsedIDs.insert(this->m_UniqueGameID);
			}
			else
			{
				// Found a duplicate, make another ID
				cTicTacToeGameInstance::m_duplicateIDsFound++;
			}

		}while ( itNewID != cTicTacToeGameInstance::m_setUsedIDs.end() );


	}//if (this->m_UniqueGameID

	return this->m_UniqueGameID;
}

// This variable is "static" as it's shared by all instances of the class. 
// I'll go over this in class, but here's the TLDR:
// * The C++11 random has a massive amount of "state" compared with 
//   good old rand(). So you might now want to create it for every object.
// * "static" variables are shared with ALL instances of an class (all objects)
// * Here there's pointers to the one and only one random engine
// * The 1st time m_GenerateUniqueGameID() is called, by any object instance, 
//   we check if a random engine has been created by seeing if the pointer
//   to the engine is still NULL. If it is NULL, we create it. If not, skip.
//   FYI: this is called a "singleton" and is the most "basic"of software patterns.
//   (https://www.urbandictionary.com/define.php?term=Basic)
//
// A strange quirk of the language is this has to be *declared* static here...
// ...but has to be initialized as NULL in the CPP file (*because* it's static)
// 
std::ranlux48* cTicTacToeGameInstance::m_pRandEngine = NULL;
// This is here to make sure we don't get repeats 
// (which is surprisingly likely with any random)
std::set<std::string> cTicTacToeGameInstance::m_setUsedIDs;
// This is just for interests sake: when making an ID, 
//	how often did it find duplicates (relates to the period
//	of the random number generator)
unsigned int cTicTacToeGameInstance::m_duplicateIDsFound = 0;


// This ends the game and sets the winner. 
// Once this happens, no more moves can happen
bool cTicTacToeGameInstance::endGameAndDeclareWinner(eSquareState winner)
{
	// Have we already ended the game?
	if ( this->m_bGameIsCurrentlyRunning == false )
	{
		// !hat are you doing? The game is already done, yo!
		return false;
	}

	// Game is running, so end it...

	switch (winner)
	{
	case cTicTacToeGameInstance::X_PLAYER:
		this->m_winner_SIN = this->m_Player_X_SIN;
		break;
	case cTicTacToeGameInstance::O_PLAYER:
		this->m_winner_SIN = this->m_Player_O_SIN;
		break;
	case cTicTacToeGameInstance::GAME_IS_OVER:
		// It's a tie (draw)
		this->m_winner_SIN = 0;
		break;
	}
	
	this->m_bGameIsCurrentlyRunning = false;

	return true;
}

std::string cTicTacToeGameInstance::getUniqueGameID(void)
{
	return this->m_UniqueGameID;
}

// Returns the SIN of the winner. 
// If a draw (or game still running), returns 0
unsigned int cTicTacToeGameInstance::getWinnerSIN(void)
{
	return this->m_winner_SIN;
}

// Returns true if it's an actively running game.
bool cTicTacToeGameInstance::isGameCurrentlyRunning(void)
{
	return this->m_bGameIsCurrentlyRunning;
}

unsigned int cTicTacToeGameInstance::getPlayer_X_SIN(void) {

	return this->m_Player_X_SIN;
}

unsigned int cTicTacToeGameInstance::getPlayer_O_SIN(void) {

	return this->m_Player_O_SIN;
}

cTicTacToeGameInstance::eSquareState cTicTacToeGameInstance::whosTurnIsIt(void) {

	//validate the game
	if (!this->isGameCurrentlyRunning() && this->getWinnerSIN() != 0) {
		return cTicTacToeGameInstance::eSquareState::GAME_IS_OVER;
	}

	if (this->getPlayer_O_SIN() == 0) {
		return cTicTacToeGameInstance::eSquareState::IS_EMPTY;
	}

	int countX = 0;
	int countO = 0;
	
	for (unsigned int i = 0; i < this->theBoard.size(); i++) {

		for (unsigned int j = 0; j < this->theBoard[i].size(); j++) {

			if (this->theBoard.at(i).at(j).state == cTicTacToeGameInstance::eSquareState::X_PLAYER) {
				countX++;
			}
			if (this->theBoard.at(i).at(j).state == cTicTacToeGameInstance::eSquareState::O_PLAYER) {
				countO++;
			}
		}
	}

	//if count is 0, X goes first
	if (countX == 0 && countO == 0) {
		return cTicTacToeGameInstance::eSquareState::X_PLAYER;
	}

	//they are not zero and the same, X goes
	if (countX == countO) {
		return cTicTacToeGameInstance::eSquareState::X_PLAYER;
	}

	if (countX > countO) {
		return cTicTacToeGameInstance::eSquareState::O_PLAYER;
	}

	//idk default?
	else {
		return cTicTacToeGameInstance::eSquareState::GAME_IS_OVER;
	}

}

bool cTicTacToeGameInstance::placePiece(unsigned int row, unsigned int column,
	eSquareState player, std::string& errorString) {

	//check if game is still alive
	if (!this->isGameCurrentlyRunning()) {
		errorString = "ERROR: GAME IS OVER";
		return false;
	}

	//check player
	if (player == eSquareState::GAME_IS_OVER ) {
		errorString = "ERROR: GAME OVER";
		return false;
	}

	if (player == eSquareState::IS_EMPTY) {
		errorString = "ERROR: INVALID GAME";
		return false;
	}

	//check if its their move
	if (this->whosTurnIsIt() != player) {
		errorString = "ERROR: NOT YOUR TURN";
		return false;
	}

	//check if their move is valid
	if (row > 2 || row < 0) {
		errorString = "ERROR: INVALID ROW";
		return false;
	}

	if (column > 2 || column < 0) {
		errorString = "ERROR: INVALID COLUMN";
		return false;
	}

	//check if selected spot is empty
	if (this->theBoard.at(row).at(column).state != eSquareState::IS_EMPTY) {
		errorString = "ERROR: SPACE ALREADY TAKEN";
		return false;
	}
	//update their move
	this->theBoard[row][column].state = player;

	//check for win condition
	//father forgive me for I have sinned..........
	if (theBoard[0][0].state == eSquareState::X_PLAYER && theBoard[0][1].state == eSquareState::X_PLAYER &&
		theBoard[0][2].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);
	}

	else if (theBoard[1][0].state == eSquareState::X_PLAYER && theBoard[1][1].state == eSquareState::X_PLAYER &&
		theBoard[1][2].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);
	}
	else if (theBoard[2][0].state == eSquareState::X_PLAYER && theBoard[2][1].state == eSquareState::X_PLAYER &&
		theBoard[2][2].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);

	}
	else if (theBoard[0][0].state == eSquareState::X_PLAYER && theBoard[1][0].state == eSquareState::X_PLAYER &&
		theBoard[2][0].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);

	}
	else if (theBoard[0][1].state == eSquareState::X_PLAYER && theBoard[1][1].state == eSquareState::X_PLAYER &&
		theBoard[2][1].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);

	}
	else if (theBoard[0][2].state == eSquareState::X_PLAYER && theBoard[1][2].state == eSquareState::X_PLAYER &&
		theBoard[2][2].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);

	}
	else if (theBoard[0][0].state == eSquareState::X_PLAYER && theBoard[1][1].state == eSquareState::X_PLAYER &&
		theBoard[2][2].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);

	}
	else if (theBoard[2][2].state == eSquareState::X_PLAYER && theBoard[1][1].state == eSquareState::X_PLAYER &&
		theBoard[0][0].state == eSquareState::X_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::X_PLAYER);

	}
	else if (theBoard[0][0].state == eSquareState::O_PLAYER && theBoard[0][1].state == eSquareState::O_PLAYER &&
		theBoard[0][2].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[1][0].state == eSquareState::O_PLAYER && theBoard[1][1].state == eSquareState::O_PLAYER &&
		theBoard[1][2].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[2][0].state == eSquareState::O_PLAYER && theBoard[2][1].state == eSquareState::O_PLAYER &&
		theBoard[2][2].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[0][0].state == eSquareState::O_PLAYER && theBoard[1][0].state == eSquareState::O_PLAYER &&
		theBoard[2][0].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[0][1].state == eSquareState::O_PLAYER && theBoard[1][1].state == eSquareState::O_PLAYER &&
		theBoard[2][1].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[0][2].state == eSquareState::O_PLAYER && theBoard[1][2].state == eSquareState::O_PLAYER &&
		theBoard[2][2].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[0][0].state == eSquareState::O_PLAYER && theBoard[1][1].state == eSquareState::O_PLAYER &&
		theBoard[2][2].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}
	else if (theBoard[2][2].state == eSquareState::O_PLAYER && theBoard[1][1].state == eSquareState::O_PLAYER &&
		theBoard[0][0].state == eSquareState::O_PLAYER) {
		this->endGameAndDeclareWinner(eSquareState::O_PLAYER);

	}

	//check for winner...
	bool gameOver =  true;
	for (unsigned int i = 0; i < theBoard.size(); i++) {
		for (unsigned int j = 0; j < theBoard[i].size(); j++) {
			if (theBoard[i][j].state == eSquareState::IS_EMPTY) {
				gameOver = false;
			}
		}
	}
	if (gameOver) {
		this->endGameAndDeclareWinner(eSquareState::GAME_IS_OVER);
	}

	//wow you made it, congrats
	return true;
}



bool cTicTacToeGameInstance::printBoard(void) {
// 
//      |     |     
//  0,0 | 0,1 | 0,2
//      |     |     
// -----+-----+-----
//      |     |     
//  1,0 | 1,1 | 1,2
//      |     |     
// -----+-----+-----
//      |     |     
//  2,0 | 2,1 | 2,2
//      |     |     
//
	std::cout << "     |     |     " << std::endl;

	std::cout << " ";
	if (this->theBoard[0][0].state == eSquareState::X_PLAYER) {

	 std::cout << " X  | ";
	}
	else if (this->theBoard[0][0].state == eSquareState::O_PLAYER) {

	 std::cout << " O  | ";
	}
	else{
	 std::cout << "0,0 | ";
	}
////////////////////////////////////////////////////////////////////
	if (this->theBoard[0][1].state == eSquareState::X_PLAYER) {

		std::cout << " X  | ";
	}
	else if (this->theBoard[0][1].state == eSquareState::O_PLAYER) {

		std::cout << " O  | ";
	}
	else {
		std::cout << "0,1 | ";
	}
//////////////////////////////////////////////////////////////////
	if (this->theBoard[0][2].state == eSquareState::X_PLAYER) {

		std::cout << " X"<<std::endl;
	}
	else if (this->theBoard[0][2].state == eSquareState::O_PLAYER) {

		std::cout << " O" <<std::endl;
	}
	else {
		std::cout << "0,2" <<std::endl;
	}
	std::cout << "     |     |     " << std::endl;
	std::cout << "-----+-----+-----" << std::endl;
	std::cout << "     |     |     " << std::endl;
//////////////////////////////////////////////////////////////////

	std::cout << " ";
	if (this->theBoard[1][0].state == eSquareState::X_PLAYER) {

		std::cout << " X  | ";
	}
	else if (this->theBoard[1][0].state == eSquareState::O_PLAYER) {

		std::cout << " O  | ";
	}
	else {
		std::cout << "1,0 | ";
	}
	////////////////////////////////////////////////////////////////////
	if (this->theBoard[1][1].state == eSquareState::X_PLAYER) {

		std::cout << " X  | ";
	}
	else if (this->theBoard[1][1].state == eSquareState::O_PLAYER) {

		std::cout << " O  | ";
	}
	else {
		std::cout << "1,1 | ";
	}
	//////////////////////////////////////////////////////////////////
	if (this->theBoard[1][2].state == eSquareState::X_PLAYER) {

		std::cout << " X"<<std::endl;
	}
	else if (this->theBoard[1][2].state == eSquareState::O_PLAYER) {

		std::cout << " O" << std::endl;
	}
	else {
		std::cout << "1,2" << std::endl;
	}
	std::cout << "     |     |     " << std::endl;
	std::cout << "-----+-----+-----" << std::endl;
	std::cout << "     |     |     " << std::endl;
	//////////////////////////////////////////////////////////////////
	std::cout << " ";
	if (this->theBoard[2][0].state == eSquareState::X_PLAYER) {

		std::cout << " X  | ";
	}
	else if (this->theBoard[2][0].state == eSquareState::O_PLAYER) {

		std::cout << " O  | ";
	}
	else {
		std::cout << "2,0 | ";
	}
	////////////////////////////////////////////////////////////////////
	if (this->theBoard[2][1].state == eSquareState::X_PLAYER) {

		std::cout << " X  | ";
	}
	else if (this->theBoard[2][1].state == eSquareState::O_PLAYER) {

		std::cout << " O  | ";
	}
	else {
		std::cout << "2,1 | ";
	}
	//////////////////////////////////////////////////////////////////
	if (this->theBoard[2][2].state == eSquareState::X_PLAYER) {

		std::cout << " X" << std::endl;
	}
	else if (this->theBoard[2][2].state == eSquareState::O_PLAYER) {

		std::cout << " O" << std::endl;
	}
	else {
		std::cout << "2,2" << std::endl;
	}
	std::cout << "     |     |     " << std::endl;
	std::cout << "" << std::endl;


	//wow art
	return true;
}

bool cTicTacToeGameInstance::getCurrentBoardState(std::vector< std::vector<sSquare> >& theBoard) {

	for (unsigned int i = 0; i < 3; i++) {

		std::vector<sSquare> theRow;
		for (unsigned int j = 0; j < 3; j++) {
			
			sSquare theSquare;
			theSquare = this->theBoard[i][j];
			theRow.push_back(theSquare);
		}
		theBoard.push_back(theRow);
	}
	return true;
}
